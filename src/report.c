#include <stdio.h>
#include <stdlib.h>
#include <png.h>
#include <sys/types.h>
#include <limits.h>
#include <sys/stat.h>
#include "database.h"
#include "log.h"
#include "file_analysis.h"

#include "report.h"

void fill_line(unsigned char line[], int start, int end)
{
    int i;
    for(i=start;i<=end;i++) {
        line[i] = 255;
    }
}

int save_image_report(const char *filename, unsigned char data[], int length)
{
    FILE *fp;
    png_structp png_ptr;
    png_infop info_ptr;

    fp = fopen(filename, "wb");
    if (!fp) {
        ERROR("file not opened");
        return 0;
    }

    png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if (!png_ptr) {
        ERROR("png_create_write_struct");
        fclose(fp);
        return 0;
    }

    info_ptr = png_create_info_struct(png_ptr);
    if (!info_ptr) {
        ERROR("png_create_info_struct");
        png_destroy_write_struct(&png_ptr, (png_infopp)NULL);
        fclose(fp);
        return 0;
    }

    if (setjmp(png_jmpbuf(png_ptr))) {
        png_destroy_write_struct(&png_ptr, &info_ptr);
        fclose(fp);
        return 0;
    }

    png_init_io(png_ptr, fp);

    png_set_IHDR(png_ptr, info_ptr, length, 1, 8, 
            PNG_COLOR_TYPE_GRAY, PNG_INTERLACE_NONE, 
            PNG_COMPRESSION_TYPE_DEFAULT, PNG_FILTER_TYPE_DEFAULT);
    png_set_swap(png_ptr);

    png_write_info(png_ptr, info_ptr);

    png_write_row(png_ptr, data);

    png_write_end(png_ptr, info_ptr);
    png_destroy_write_struct(&png_ptr, &info_ptr);


    fclose(fp);

    return 1;
}

void generate_local_report(const char *filename, int size, unsigned char *line, 
        unsigned char *global_line, const char *positions, int generate_image)
{
    int i;
    char *p_positions;
    char *local;
    int start, end, previous;

    INFO("ENTER");

    previous = 0;
    for (p_positions = (char *)positions; (local = strsep(&p_positions, "\n")) != NULL; ) {
        if (*local != '\0') {
            sscanf(local, "%d - %d", &start, &end);
            INFO("READ : %d,%d", start,end);
            for (i=previous;i<start;i++) {
                line[i] = 0;
            }
            fill_line(line, start, end);
            previous = end+1;

            if (global_line != NULL) {
                fill_line(global_line, start, end);
            }
        }
    }

    for (i=previous;i<size;i++) {
	line[i] = 0;
    }

    if (generate_image) {
	INFO("Document %d : save image in %s", i, filename);
	save_image_report(filename, line, size);
    }

    INFO("LEAVE");
}

int generate_final_report(const char *filename, unsigned char *global_line, int size)
{
    int plagiat;
    int i;

    INFO("ENTER");
    save_image_report(filename, global_line, size);

    plagiat = 0;
    for (i=0; i<size; i++) {
	if (global_line[i] > 0) {
	    plagiat++;
	}
    }
    INFO("Plagiat global : %d", plagiat);

    return plagiat;
}

#define QUERY_WORDS \
    "SELECT d.nbr_words FROM documents d, submissions s WHERE d.id = s.document_id AND s.document_id = %d"
#define QUERY_DOCS \
    "SELECT ds.reference_id, ds.positions, ds.rev_positions, r.nbr_words " \
    "FROM documents d, documents r, submissions s, documents_sources ds " \
    "WHERE (d.id = s.document_id AND s.document_id = %d) AND ds.document_id = %d AND ds.included = 1 " \
    "AND r.id = ds.reference_id"

int generate_image_report(int subid, int docid, 
	const char *doc_path, const char *report_path, int generate_all)
{
    unsigned char *line;
    unsigned char *global_line;
    int size;
    MYSQL_RES *res;
    MYSQL_ROW row;
    int plagiat;
    char *filename;
    char *docname;
    char *query;
    t_list_single document;
    char *rev_docname;

    INFO("ENTER");

    INFO("Récupération du nombre de mots");
    query = malloc(strlen(QUERY_WORDS)+20);
    if (query == NULL) {
	ERROR("Unable to allocate memory");
	return 0;
    }
    sprintf(query, QUERY_WORDS, docid);
    res = db_read_query(query, strlen(query));
    free(query);
    size = strtol(db_next(res)[0], NULL, 10);

    INFO("Allocate simple memory");
    line = malloc(size*sizeof(*line));
    if (line == NULL) {
	ERROR("Unable to allocate memory");
	return -1;
    }

    INFO("Allocate global memory");
    global_line = calloc(1, size*sizeof(*line));
    if (global_line == NULL) {
	ERROR("Unable to allocate memory");
	free(line);
	return -1;
    }

    INFO("Allocate docname memory");
    docname = malloc(strlen(doc_path)+50);
    if (docname == NULL) {
	ERROR("Unable to allocate memory");
	free(line);
	free(global_line);
	return -1;
    }

    INFO("Allocate reference docname memory");
    rev_docname = malloc(strlen(doc_path)+50);
    if (rev_docname == NULL) {
	ERROR("Unable to allocate memory");
	free(docname);
	free(line);
	free(global_line);
	return -1;
    }


    INFO("Open document");
    sprintf(docname,"%s/%d.txt", doc_path, docid);
    document = file_to_word_list(docname);

    INFO("Allocate filename memory");
    filename = malloc(strlen(report_path)+50);
    if (filename == NULL) {
	ERROR("Unable to allocate memory");
	free(line);
	free(global_line);
	free(docname);
	free(rev_docname);
	return -1;
    }


    INFO("Récupération des documents");
    query = malloc(strlen(QUERY_DOCS)+20);
    sprintf(query, QUERY_DOCS, docid, docid);
    res = db_read_query(query, strlen(query));
    free(query);
    while ((row=db_next(res))!=NULL) {
	char *local_id = row[0];
	char *positions = row[1];

	char *rev_positions = row[2];
	int rev_size = strtol(row[3], NULL, 10);
	unsigned char *rev_line;
	t_list_single rev_document;

	INFO("Document %s", local_id);
	sprintf(filename,"%s/%d/%d_%s.png", report_path, subid, docid, local_id);
	generate_local_report(filename, size, line, global_line, positions, generate_all);
	if (generate_all) {
	    sprintf(filename,"%s/%d/%d_%s.html", report_path, subid, docid, local_id);
	    generate_text_report(docname, document, line, size, filename);
	}

	INFO("Allocate simple memory");
	rev_line = malloc(rev_size*sizeof(*rev_line));
	if (rev_line == NULL) {
	    ERROR("Unable to allocate memory");
	    return -1;
	}

	INFO("Open reference document");
	sprintf(rev_docname,"%s/%s.txt", doc_path, local_id);
	rev_document = file_to_word_list(rev_docname);

	sprintf(filename,"%s/%d/rev_%d_%s.png", report_path, subid, docid, local_id);
	generate_local_report(filename, rev_size, rev_line, NULL, rev_positions, generate_all);
	if (generate_all) {
	    sprintf(filename,"%s/%d/rev_%d_%s.html", report_path, subid, docid, local_id);
	    generate_text_report(rev_docname, rev_document, rev_line, rev_size, filename);
	}

	free(rev_line);
	free_single_list(&rev_document);
    }


    INFO("Final report");
    sprintf(filename, "%s/%d/%d.png", report_path, subid, docid);
    plagiat = generate_final_report(filename, global_line, size);
    sprintf(filename, "%s/%d/%d.html", report_path, subid, docid);
    generate_text_report(docname, document, global_line, size, filename);

    INFO("Free memory");
    free(filename);
    free(docname);
    free(line);
    free(global_line);
    free(rev_docname);
    free_single_list(&document);

    INFO("LEAVE (%d)", plagiat);
    return plagiat;
}

int generate_text_report_aux(FILE *fdoc, int fpos, t_list_single doc,
	int current_word, int nbr_words, unsigned char *line, int previous, FILE *freport)
{
    DEBUG("%d", current_word);
    if (current_word == nbr_words) {
	if (previous == 1) {
	    fprintf(freport,"</span>");
	}
	return 1;
    } else if (IS_EMPTY_SL(doc)) {
	ERROR("Fin inattendu");
	return 0;
    } else {
	if (line[current_word] != previous && previous != 0) {
	    fprintf(freport,"</span>");
	}

	int offset = COUNT_SL(doc);
	while (fpos < offset) {
	    char c;
	    fread(&c, 1, 1, fdoc);
	    if (c == '\n') {
		fprintf(freport,"<br/>\n");
	    } else {
		fputc(c, freport);
	    }
	    fpos++;
	}

	if (line[current_word] != previous && previous == 0) {
	    fprintf(freport,"<span style=\"color:red;\">");
	}

	DEBUG("start = %d, end = %d", fpos, offset);
	int final_pos = offset+strlen(HEAD_SL(doc));
	while (fpos < final_pos) {
	    char c;
	    fread(&c, 1, 1, fdoc);
	    if (c == '\n') {
		INFO("New line inside word ???");
		fprintf(freport,"<br/>\n");
	    } else {
		fputc(c, freport);
	    }
	    fpos++;
	}

	return generate_text_report_aux(fdoc, fpos, NEXT_SL(doc), 
		current_word + 1, nbr_words, line, line[current_word], freport);
    }
}

int generate_text_report(const char *docname, t_list_single doc, 
	unsigned char *line, int size,
	const char *reportname)
{
    FILE *freport;
    FILE *fdoc;
    int status;

    INFO("ENTER");

    INFO("Open file report");
    freport = fopen(reportname, "w");
    if (freport == NULL) {
	ERROR("Can't open document <%s>", reportname);
	return 0;
    }

    INFO("Open file doc");
    fdoc = fopen(docname, "r");
    if (fdoc == NULL) {
	ERROR("Can't open document <%s>", docname);
	return 0;
    }

    status = generate_text_report_aux(fdoc, 0, doc, 0, size, line, 0, freport);

    INFO("Close file doc");
    fclose(fdoc);

    INFO("Close file report");
    fclose(freport);

    INFO("LEAVE");
    return status;
}


#if 0
int generate_image_report(const char *global_filename)
{
    int plagiat;
    int size;
    int nbr;
    int i;
    int start, end;
    unsigned char *line;
    unsigned char *global_line = NULL;
    char filename[30];

    INFO("ENTER");

    INFO("Read size and number of documents");
    if (scanf("%d\n", &size) != 1) {
	ERROR("Invalid size");
	return -1;
    }
    if (scanf("%d\n", &nbr) != 1) {
	ERROR("Invalid number of documents !");
	return -1;
    }

    INFO("Allocate simple memory");
    line = malloc(size*sizeof(*line));
    if (line == NULL) {
	ERROR("Unable to allocate memory");
	return -1;
    }

    if (global_filename != NULL) {
	INFO("Allocate global memory");
	global_line = calloc(1, size*sizeof(*line));
	if (global_line == NULL) {
	    ERROR("Unable to allocate memory");
	    return -1;
	}
    }

    for (i = 0; i < nbr; i++) {
	int j, k;
	int nbr2;
	int previous = 0;

	INFO("Document %d : read", i);
	scanf(":%[^:]:%d", filename, &nbr2);
	for (k = 0; k < nbr2; k++) {
	    scanf("%d - %d\n", &start, &end);
	    INFO("READ : %d,%d", start,end);
	    for (j=previous;j<start;j++) {
		line[j] = 0;
	    }
	    fill_line(line, start, end);
	    previous = end+1;

	    if (global_filename != NULL) {
		fill_line(global_line, start, end);
	    }
	}
	for (j=previous;j<size;j++) {
	    line[j] = 0;
	}

	INFO("Document %d : save image", i);
	save_image_report(filename, line, size);
    }

    free(line);

    if (global_filename == NULL) {
	plagiat = 0;
    } else {
	INFO("Image globale");
	save_image_report(global_filename, global_line, size);

	plagiat = 0;
	for (i=0; i<size; i++) {
	    if (global_line[i] > 0) {
		plagiat++;
	    }
	}
	INFO("Plagiat global : %d", plagiat);

	printf("%d\n", plagiat);

	free(global_line);
    }

    INFO("LEAVE");

    return plagiat;
}
#endif
