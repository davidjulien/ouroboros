#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>


#include "log.h"

#include "websearch.h"
#include "findonweb.h"
#include "document_list.h"
#include "annotate_doc.h"
#include "transform.h"
#include "file_analysis.h"

#include "plagiat.h"


#define SOURCES_DIR	"sources"
#define TEXTES_DIR	"texts"
#define REPORTS_DIR	"reports"





#define REPORTINDEX	"%s/%s/index.html"
#define REPORTNAME	"%s/%s/reportS__%s__.html"
#define REPORTNAME2	"%s/%s/reportR__%s__.html"

void save_source(t_list_single l, FILE *f, int nbr_words)
{
    if (IS_EMPTY_SL(l)) {
        return ;
    } else {
        char *info = HEAD_SL(l);
        char *source = malloc(strlen(info)+1);
        char *filename = malloc(strlen(info)+1);
        char *filenameR = malloc(strlen(info)+1);
        float ratio, ratio2;
        float ratio_bloc, ratio_bloc2;
        int found, found2;
        int nbr_blocs, nbr_blocs2;
        int nbr_words, nbr_words2;

        if(source == NULL) {
            FATAL("Erreur d'allocation mémoire : %s", strerror(errno));
            exit(100);
        }
        if(filename == NULL) {
            FATAL("Erreur d'allocation mémoire : %s", strerror(errno));
            exit(100);
        }
        if(filenameR == NULL) {
            FATAL("Erreur d'allocation mémoire : %s", strerror(errno));
            exit(100);
        }

        sscanf(info, "%[^,],%[^,],%d,%d,%d,%[^,],%d,%d,%d", source, 
                filename, &nbr_blocs, &found, &nbr_words,
                filenameR, &nbr_blocs2, &found2, &nbr_words2);

        ratio = ((float)found) / nbr_words;
        ratio2 = ((float)found2) / nbr_words2;

        ratio_bloc = ((float)found) / nbr_blocs;
        ratio_bloc2 = ((float)found2) / nbr_blocs2;

        fprintf(f, "<a href=\"%s\">%2.f %% (%d / %d - %d blocs - %.2f)</a>",
                filename, 100.*ratio, found, nbr_words, nbr_blocs, ratio_bloc);
        fprintf(f," <a href=\"%s\">%2.f %% (%d / %d - %d blocs -%.2f)</a>",
                filenameR,100.*ratio2,found2,nbr_words2,nbr_blocs2,ratio_bloc2);
        fprintf(f," <a href=\"%s\">%s</a> <br/>", source, source);

        free(source);
        free(filename);
        free(filenameR);

        save_source(NEXT_SL(l), f, nbr_words);
    }
}

void save_index(t_list_single l, const char *doc, int nbr_words)
{
    FILE *f;
    char *filename;

    DEBUG("Allocation de la mémoire");
    filename = malloc((strlen(REPORTINDEX)+strlen(doc)+strlen(REPORTS_DIR)+1)
            *sizeof(char));
    if(filename == NULL) {
        FATAL("Erreur d'allocation mémoire : %s", strerror(errno));
        exit(100);
    }
    sprintf(filename, REPORTINDEX, REPORTS_DIR, doc);

    INFO("Ouverture du fichier en écriture <%s>", filename);
    f = fopen(filename,"w");

    fprintf(f, "<HTML><HEAD><TITLE>Analyse de %s</TITLE></HEAD>\n", doc);

    fprintf(f, "<BODY>\n");

    fprintf(f, "<H2>Analyse de <a href=\"%s.txt\">%s</a></H2>\n", doc, doc);

    save_source(l, f, nbr_words);

    fprintf(f,"</BODY></HTML>");

    INFO("Fermeture du fichier");
    fclose(f);

    DEBUG("Libération de la mémoire");
    free(filename);
}



t_list_single foreach_source(t_list_single sources, 
        t_list_single doc, const char *doc_filepath, const char *doctext, 
        int nbr_words, t_list_single resultat,
        int threshold, int minwords, int maxgap)
{
    if (IS_EMPTY_SL(sources) || COUNT_SL(sources) <= 1) {
        return resultat;
    } else {
        char *encoding;
        char *type;
        char *ref_filepath;
        char *filename;
        char *source_filepath;
        char *source;
        t_ldoc ldoc;
        FILE *f;
        int status;

        source = HEAD_SL(sources);
        filename = url_to_filename(source);

        source_filepath = malloc((strlen(SOURCES_DIR)+strlen(filename)+2)
                *sizeof(char));
        if(source_filepath == NULL) {
            FATAL("Erreur d'allocation mémoire : %s", strerror(errno));
            exit(100);
        }
        sprintf(source_filepath,"%s/%s", SOURCES_DIR, filename);

        INFO("Récupération du fichier <%s> (%d)", 
                source_filepath, COUNT_SL(sources));
        if ((f=fopen(source_filepath, "r")) != NULL) {
            fclose(f);
            type = file_type(source_filepath, &encoding);
            INFO("Fichier existant");
        } else {
            webget_file(source, source_filepath, &type, &encoding);
            INFO("Récupération réussie");
        }

        DEBUG("Allocation de mémoire pour le fichier de référence");
        ref_filepath = malloc((strlen(TEXTES_DIR)+strlen(filename)+6)
                *sizeof(char));
        if(ref_filepath == NULL) {
            FATAL("Erreur d'allocation mémoire : %s", strerror(errno));
            exit(100);
        }
        sprintf(ref_filepath,"%s/%s.txt", TEXTES_DIR, filename);

        INFO("Transformation du fichier en texte dans <%s>", ref_filepath);
        if ((f=fopen(ref_filepath, "r")) != NULL) {
            fclose(f);
            status = 1;
            INFO("Fichier transformé existant");
        } else if (transform(source_filepath, ref_filepath, type, encoding)==1){
            status = 1;
        } else {
            status = 0;
            WARNING("Erreur de transformation");
        }

        if (status) {
            int found;
            INFO("Comparaison du document (%s) avec l'original (%s)",
                    doctext, ref_filepath);
            ldoc = compare_document2(doc, doctext, ref_filepath, source, 
                    threshold, &found);
            INFO("Nombre de mots trouvés : %d", found);

            if (found > 0) {
                int nbr_blocs;
                int offsetdir;

                INFO("Nettoyage du résultat");
                nbr_blocs = remove_too_small(ldoc, minwords, maxgap, &found);
                INFO("Nettoyage du résultat : %d mots dans %d blocs", 
                        found, nbr_blocs);

                if (nbr_blocs > 0) {
                    char *reportname;
                    char *info;

                    t_list_single doc2;
                    t_ldoc ldoc2;
                    char *reportname2;
                    int nbr_words2;
                    int found2;
                    int nbr_blocs2;

                    DEBUG("Allocation de la mémoire pour le nom du rapport");
                    reportname = malloc((strlen(REPORTNAME)
                                +strlen(doc_filepath)+strlen(REPORTS_DIR)
                                +strlen(filename)+1)*sizeof(char));
                    sprintf(reportname, REPORTNAME, REPORTS_DIR, doc_filepath, 
                            filename);

                    INFO("Génération du rapport : <%s>", reportname);
                    generate_report(reportname, ldoc, source);



                    INFO("Analyse inverse");

                    INFO("Analyse de <%s>", ref_filepath);
                    doc2 = file_to_word_list(ref_filepath);
                    nbr_words2 = length_single_list(doc2);

                    INFO("Comparaison");
                    ldoc2 = compare_document2(doc2, ref_filepath, doctext, 
                            "original", threshold, &found2);
                    INFO("Nombre de mots trouvés en inverse : %d", found2);

                    INFO("Nettoyage du résultat");
                    nbr_blocs2 = remove_too_small(ldoc2, minwords, maxgap, 
                            &found2);
                    INFO("Nettoyage du résultat : %d mots dans %d blocs", 
                            found2, nbr_blocs2);


                    DEBUG("Allocation de la mémoire pour le nom du rapport");
                    reportname2 = malloc((strlen(REPORTNAME2)
                                +strlen(doc_filepath)+strlen(REPORTS_DIR)
                                +strlen(filename)+1)*sizeof(char));
                    sprintf(reportname2, REPORTNAME2, 
                            REPORTS_DIR, doc_filepath, filename);

                    INFO("Génération du rapport : <%s>", reportname2);
                    generate_report(reportname2, ldoc2, filename);

                    DEBUG("Libération de la mémoire");
                    free_ldoc(&ldoc2);
                    free_single_list(&doc2);

                    INFO("Fin de l'analyse inverse");


                    DEBUG("Allocation de la mémoire pour le texte d'info");
                    info = malloc((strlen(source)+strlen(reportname)
                                +strlen(reportname2)+3)*sizeof(char));
                    offsetdir = strlen(REPORTS_DIR) +strlen(doc_filepath)+2;
                    sprintf(info,"%s,%s,%d,%d,%d,%s,%d,%d,%d", source, 
                            reportname+offsetdir, nbr_blocs, found, nbr_words,
                            reportname2+offsetdir,nbr_blocs2,found2,nbr_words2);

                    INFO("Ajout du document dans le résultat : %s : %d", 
                            info, found);
                    resultat = cons_single(info, resultat);
                    COUNT_SL(resultat) = found;

                    DEBUG("Libération de la mémoire");
                    free(reportname);
                    free(reportname2);
                }
            }
            free_ldoc(&ldoc);
        }

        DEBUG("Libération de la mémoire");
        free(encoding);
        free(type);
        free(ref_filepath);
        free(source_filepath);
        free(filename);

        return foreach_source(NEXT_SL(sources), doc, doc_filepath, doctext,
                nbr_words, resultat, threshold, minwords, maxgap);
    }
}

int detect_plagiat(const char *doc_filepath,
        t_websearch websearch, int searchwords, int searchskip,
        int threshold, int minwords, int maxgap)
{
    t_list_single sources;
    t_list_single final_sources;
    int nbr_seq;
    char *doctext;
    char *filetype;
    char *fileencoding;
    //    FILE *fdoc;
    t_list_single doc;
    int nbr_words;
    char *path;

    DEBUG("Allocation mémoire");
    path = malloc((strlen(REPORTS_DIR)+strlen(doc_filepath)+2)*sizeof(char));
    sprintf(path,"%s/%s", REPORTS_DIR, doc_filepath);
    if (opendir(path)==NULL && mkdir(path, 0700)==-1) {
        ERROR("Erreur lors de la création du répertoire %s : %s", 
                path, strerror(errno));
        return 0;
    }

    INFO("Détection des sources de <%s>", doc_filepath);
    doctext = malloc(strlen(path)+strlen(doc_filepath)+6);
    sprintf(doctext,"%s/%s.txt", path, doc_filepath);

    DEBUG("Désallocation de la mémoire");
    free(path);

    INFO("Conversion du document source <%s> en texte <%s>",
            doc_filepath, doctext);
    filetype = file_type(doc_filepath, &fileencoding);
    if (transform(doc_filepath, doctext, filetype, fileencoding)==0) {
        free(filetype);
        free(doctext);
        return 0;
    } else {
        free(filetype);
    }

    INFO("Recherche des sources");
    sources = find_on_web(doctext, websearch, searchwords, searchskip, 
            &nbr_seq);

    //    INFO("Ouverture du document <%s>", doctext);
    //    fdoc = fopen(doctext, "r");
    INFO("Analyse de <%s>", doctext);
    doc = file_to_word_list(doctext);
    nbr_words = length_single_list(doc);
    //    INFO("Fermeture du document");
    //    fclose(fdoc);

    display_single_list(sources);

    INFO("Analyse des sources");
    final_sources = 
        foreach_source(sources, doc, doc_filepath,doctext, nbr_words, EMPTY_SL,
                threshold, minwords, maxgap);


    INFO("Création de l'index");
    sort_single_list_by_count(&final_sources);
    save_index(final_sources, doc_filepath, nbr_words);

    DEBUG("Libération des listes des sources");
    free_single_list(&sources);
    free_single_list(&final_sources);

    DEBUG("Libération de la liste du document");
    free_single_list(&doc);

    DEBUG("Libération du fichier temporaire");
    free(doctext);

    return 1;
}
