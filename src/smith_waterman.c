#include <stdio.h>
#include <string.h>
#include <math.h>
#include <png.h>

#include "word_list.h"
#include "file_analysis.h"
#include "stream.h"
#include "char_filter.h"

#include "smith_waterman.h"

#define IMAGE

//#define DEBUGLEVEL
#include "log.h"

#define VALUE	int
#define MAX	2000000000

#define STRONG_MIN_LENGTH	8
#define STRONG_REAL_MIN_LENGTH	5
#define DISTANCE_MAX_LENGTH	3

#define SAME		+4
#define SUBSTITUTE 	-2
#define REMOVE		-1
#define ADD		-3
#define HOLE		0

#define MAXLINE		100
#define RECOUVREMENT	10

typedef struct {
    unsigned int x;
    unsigned int y;
} t_coord;

typedef struct {
    unsigned int nbr_points;
    t_coord points[STRONG_MIN_LENGTH];
} t_previous_info;

typedef struct {
    png_structp png_ptr;
    png_infop info_ptr;
    FILE *fp;
} t_matrix;

t_matrix *open_matrix(const char *filename, int columns, int lines)
{
    t_matrix *matrix;

    matrix = malloc(sizeof(t_matrix));
    if (matrix == NULL) {
        FATAL("Erreur lors de l'allocation mémoire");
        return NULL;
    }

    matrix->fp = fopen(filename, "wb");
    if (!matrix->fp) {
        ERROR("write_matrix : file not opened");
        free(matrix);
        return NULL;
    }

    matrix->png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if (!matrix->png_ptr) {
        ERROR("png_create_write_struct");
        fclose(matrix->fp);
        free(matrix);
        return NULL;
    }

    matrix->info_ptr = png_create_info_struct(matrix->png_ptr);
    if (!matrix->info_ptr) {
        ERROR("png_create_info_struct");
        png_destroy_write_struct(&matrix->png_ptr, (png_infopp)NULL);
        fclose(matrix->fp);
        free(matrix);
        return NULL;
    }

    if (setjmp(png_jmpbuf(matrix->png_ptr))) {
        png_destroy_write_struct(&matrix->png_ptr, &matrix->info_ptr);
        fclose(matrix->fp);
        free(matrix);
        return NULL;
    }

    png_set_gray_to_rgb(matrix->png_ptr);
    png_init_io(matrix->png_ptr, matrix->fp);

    png_set_IHDR(matrix->png_ptr, matrix->info_ptr, columns, lines, 8, 
            PNG_COLOR_TYPE_GRAY, PNG_INTERLACE_NONE, 
            PNG_COMPRESSION_TYPE_DEFAULT, PNG_FILTER_TYPE_DEFAULT);
    png_set_swap(matrix->png_ptr);

    png_write_info(matrix->png_ptr, matrix->info_ptr);

    return matrix;
}

void close_matrix(t_matrix *matrix)
{
    png_write_end(matrix->png_ptr, matrix->info_ptr);
    png_destroy_write_struct(&matrix->png_ptr, &matrix->info_ptr);

    fclose(matrix->fp);
    free(matrix);
}

void write_matrix(t_matrix *matrix, unsigned char *line)
{
    png_write_row(matrix->png_ptr, line);
}

#if 0
void write_image(const char *filename, VALUE *matrix, int columns, int lines, VALUE max)
{
    FILE *fp = fopen(filename, "wb");
    png_byte *row_pointers[lines];
    int i, j;
    for(i=0;i<lines;i++) {
	row_pointers[i] = malloc(columns*sizeof(unsigned char));
	for (j=0;j<columns;j++) {
	    row_pointers[i][j] = (255*(ARRAY(matrix, i, j, columns))) / max;
	}
    }

    if (!fp) {
        ERROR("write_matrix : file not opened");
	return ;
    }

    png_structp png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if (!png_ptr) {
	ERROR("png_create_write_struct");
	return ;
    }

    png_infop info_ptr = png_create_info_struct(png_ptr);
    if (!info_ptr) {
	ERROR("png_create_info_struct");
	png_destroy_write_struct(&png_ptr, (png_infopp)NULL);
	return ;
    }

    if (setjmp(png_jmpbuf(png_ptr))) {
	png_destroy_write_struct(&png_ptr, &info_ptr);
	fclose(fp);
	return ;
    }

    png_set_gray_to_rgb(png_ptr);
    png_init_io(png_ptr, fp);

    png_set_IHDR(png_ptr, info_ptr, columns, lines, 8, 
	    PNG_COLOR_TYPE_GRAY, PNG_INTERLACE_NONE, 
	    PNG_COMPRESSION_TYPE_DEFAULT, PNG_FILTER_TYPE_DEFAULT);
    png_set_swap(png_ptr);

    png_write_info(png_ptr, info_ptr);
    png_write_image(png_ptr, row_pointers);
    png_write_end(png_ptr, info_ptr);
    png_destroy_write_struct(&png_ptr, &info_ptr);

    fclose(fp);

    for(i=0;i<lines;i++) {
	free(row_pointers[i]);
    }
}
#endif

VALUE max(VALUE a, VALUE b)
{
    if (a < b) {
	return b;
    } else {
	return a;
    }
}

VALUE max3(VALUE a, VALUE b, VALUE c)
{
    if (a>b) {
	if (a>c) {
	    if (a>0) {
		return a;
	    } else {
		return 0;
	    }
	} else if (c>0) {
	    return c;
	} else {
	    return 0;
	}
    } else if (b>c) {
	if (b>0) {
	    return b;
	} else {
	    return 0;
	}
    } else {
	if (c>0) {
	    return c;
	} else {
	    return 0;
	}
    }
}

#if 0
int backtrack(VALUE *array, int colonnes, int lignes, int x, int y, int count, int hole)
{
//    printf("  (%d,%d)\n", x, y);
    if (x==0) {
	return count;
    } else if (y==0) {
	return count;
    } else {
	int current = ARRAY(array, y, x, colonnes);
	if (current == 0) {
	    return count;
	} else {
	    //int val1 = ARRAY(array, y-1, x, colonnes);
	    int val2 = ARRAY(array, y-1, x-1, colonnes);
	    //int val3 = ARRAY(array, y, x-1, colonnes);
	    if (current >= val2) {
		return backtrack(array, colonnes, lignes, x-1, y-1, count+1, HOLE);
	    } else if (hole > 0) {
		return backtrack(array, colonnes, lignes, x-1, y-1, count, hole-1);
	    } else {
		return count;
	    }
/*	    } else if (val3 >= val1) {
		return backtrack(array, colonnes, lignes, x-1, y, count);
	    } else {
		return backtrack(array, colonnes, lignes, x, y-1, count);
	    } */
	}
    }
}
#endif


typedef enum { BREAK, FOLLOW_LEFT, FOLLOW_UP, FOLLOW_DIAG } t_follow;

t_follow follow_best_line(VALUE *array[], int colonnes, int posx, int posy)
{
    VALUE current = array[posy][posx];
    VALUE value_diag = array[posy-1][posx-1];
    VALUE value_left = array[posy][posx-1];
    VALUE value_up = array[posy-1][posx];
    DEBUG("FOLLOW : cur=%d / diag=%d / up=%d / left=%d\n", current, value_diag, value_up, value_left);
    if (current == 0) {
	return BREAK;
    } else if (value_up > value_diag) {
	if (value_up > value_left) {
	    return FOLLOW_UP;
	} else if (value_left > current) {
	    return BREAK;
	} else {
	    return FOLLOW_LEFT;
	}
    } else if (value_diag >= value_left) {
	if (value_diag > current) {
	    return BREAK;
	} else {
	    return FOLLOW_DIAG;
	}
    } else if (value_left > current) {
	return BREAK;
    } else {
	return FOLLOW_LEFT;
    }
}

#if 0
t_follow follow_reverse_best_line(VALUE *array, int colonnes, int posx, int posy)
{
    int value_diag = ARRAY(array, posy-1, posx-1, colonnes);
    int value_left = ARRAY(array, posy, posx-1, colonnes);
    int value_up = ARRAY(array, posy-1, posx, colonnes);
    if (value_left >= value_up) {
	if (value_left >= value_diag) {
	    return FOLLOW_LEFT;
	} else {
	    return FOLLOW_DIAG;
	}
    } else if (value_up > value_diag) {
	return FOLLOW_UP;
    } else {
	return FOLLOW_DIAG;
    }
}

void connect(VALUE *array2, int colonnes, int posx, int posy, int targetx, int targety)
{
    double fposy = (double)posy;
    double ratio;
    if (posx == targetx) {
	ratio = 0;
    } else {
	ratio = (double)(posy - targety) / (double)(posx - targetx);
    }
    printf("Ratio : %f\n", ratio);
    printf("%d,%d -> %d,%d\n", posx, posy, targetx, targety);
    while (posx != targetx) {
	int nposy = (int)round(fposy);
	printf("%d,%d\n", posx, nposy);
	ARRAY(array2, nposy, posx, colonnes) = 127;
	ARRAY(array2, nposy, 0, colonnes) = max(127, ARRAY(array2, nposy, 0, colonnes));
	posx = posx - 1;
	fposy = fposy - ratio;
    }
}
#endif

void detect_plagiat(VALUE *array[], int colonnes, int lignes, 
	t_coord extremum[], int nbr_extremum,
	unsigned char *result[], unsigned char reverse[])
{
    int i;
    int j;
    t_coord points[colonnes+lignes];

    for (i = 0; i < nbr_extremum; i++) {
	int posx = extremum[i].x;
	int posy = extremum[i].y;
	int strong_length;
	int keep = 1;
	t_follow status = BREAK;

	strong_length = 0;

	/*printf("%d : (%d,%d) : ", i, extremum[i].x, extremum[i].y);
	fflush(stdout);*/
	while (posx != 0 && posy != 0 && keep) {
	    status = follow_best_line(array, colonnes, posx, posy);
	    switch(status) {
		case FOLLOW_LEFT:
		    points[strong_length].x = posx;
		    points[strong_length].y = posy;
		    strong_length++;
		    posx = posx - 1;
		    break;
		case FOLLOW_UP:
		    keep = 0;
		    break;
		case FOLLOW_DIAG:
		    points[strong_length].x = posx;
		    points[strong_length].y = posy;
		    posx = posx - 1;
		    posy = posy - 1;
		    strong_length++;
		    break;
		case BREAK:
		    keep = 0;
		    break;
	    }
	}

#if 0
	if (posy == 0) {
	    INFO("Raccordement");
	    for (i = 0; i < previous_line[posx].nbr_points; i++) {
		points[i+strong_length] = previous_line[posx].points[i];
	    }
	    strong_length = strong_length + previous_line[posx].nbr_points;
	}
#endif

	switch(status) {
	    case FOLLOW_LEFT:
		posx = posx + 1;
		break;
	    case FOLLOW_UP:
		posy = posy + 1;
		break;
	    case FOLLOW_DIAG:
		posx = posx + 1;
		posy = posy + 1;
		break;
	    case BREAK:
		break;
	}

	DEBUG("Plagiat fort sur %d (vers %d,%d)", strong_length, posx, posy);

	DEBUG("Distance du plus proche extremum");
	int distancey = lignes + 1;
	int distancex = 0;
	int plusproche = -1;
	for (j = 0; j < nbr_extremum; j++) {
	    if (i != j && extremum[j].x <= posx && extremum[j].y <= posy 
		    && (posy-extremum[j].y) < distancey 
		    && posx != extremum[j].x && posy != extremum[j].y) {
		distancey = posy - extremum[j].y;
		distancex = posx - extremum[j].x;
		plusproche = j;
	    }
	}

	if (plusproche == -1) {
	    DEBUG("Aucun sommet proche trouvé");
	} else {
	    DEBUG("Plus proche sommet : (%d,%d)", extremum[plusproche].x, extremum[plusproche].y);
	}

	if (strong_length < STRONG_MIN_LENGTH) {
	    DEBUG("Zone de plagiat fort trop courte : %d < %d", strong_length, STRONG_MIN_LENGTH);
	    if (plusproche == -1 || distancey >= DISTANCE_MAX_LENGTH) {
		DEBUG("Distance vers le prochain sommet trop longue : inutile");
	    } else if (strong_length > STRONG_REAL_MIN_LENGTH) {
		DEBUG("Distance courte vers le prochain sommet : plagiat faible");
		for(j=0;j<strong_length;j++) {
		    result[points[j].y][points[j].x] = 127;
		    result[points[j].y][0] = max(127, result[points[j].y][0]);
		    reverse[points[j].x-1] = max(127, reverse[points[j].x-1]);
		}
		//connect(array2, colonnes, posx, posy, extremum[plusproche].x, extremum[plusproche].y);
	    }
	} else {
	    INFO("Zone de plagiat fort assez longue : %d >= %d", strong_length, STRONG_MIN_LENGTH);
	    for(j=0;j<strong_length;j++) {
		result[points[j].y][points[j].x] = 255;
		result[points[j].y][0] = 255;
		reverse[points[j].x-1] = 255;
	    }
	    if (distancey >= DISTANCE_MAX_LENGTH) {
		INFO("Distance longue vers le prochain sommet : %d >= %d", distancey, DISTANCE_MAX_LENGTH);
	    } else {
		INFO("Distance courte vers le prochain sommet : %d < %d", distancey, DISTANCE_MAX_LENGTH);
		//connect(array2, colonnes, posx, posy, extremum[plusproche].x, extremum[plusproche].y);
	    }
	}
    }
}

int find_extremum(VALUE *array[], int colonnes, int lignes, t_coord extremum[], int *nbr_extremum)
{
    int x,y;
    int max = 0;

    *nbr_extremum = 0;
    for(y=1;y<lignes-1;y++) {
	for(x=1;x<colonnes-1;x++) {
	    int current = array[y][x];
	    if (current >= STRONG_MIN_LENGTH*SAME 
		    && current >= array[y][x-1]
		    && current >= array[y-1][x-1]
		    && current >= array[y-1][x]
		    && current >= array[y-1][x+1]
		    && current >  array[y][x+1]
		    && current >  array[y+1][x+1]
		    && current >  array[y+1][x]
		    && current >= array[y+1][x-1]) {
		extremum[*nbr_extremum].x = x;
		extremum[*nbr_extremum].y = y;
		(*nbr_extremum)++;
		/*printf("(%d,%d) : %d - %d\n", x, y, current, 
			backtrack(array, colonnes, lignes, x, y, 0, HOLE));*/
		if (current > max) {
		    max = current;
		}
	    }
	}
	int current = array[y][x];
	if (current >= STRONG_MIN_LENGTH*SAME
		&& current >= array[y][x-1]
		&& current >= array[y-1][x-1]
		&& current >= array[y-1][x]
		&& current >  array[y+1][x]
		&& current >= array[y+1][x-1]) {
	    //printf("(%d,%d) : %d - %d\n", x, y, current, backtrack(array, colonnes, lignes, x, y, 0, HOLE));
	    extremum[*nbr_extremum].x = x;
	    extremum[*nbr_extremum].y = y;
	    (*nbr_extremum)++;
	    if (current > max) {
		max = current;
	    }
	}
    }	
    for(x=1;x<colonnes-1;x++) {
	int current = array[y][x];
	if (current >= STRONG_MIN_LENGTH*SAME
		&& current >= array[y][x-1]
		&& current >= array[y-1][x-1]
		&& current >= array[y-1][x]
		&& current >= array[y-1][x+1]
		&& current >  array[y][x+1]) {
	    extremum[*nbr_extremum].x = x;
	    extremum[*nbr_extremum].y = y;
	    (*nbr_extremum)++;
	    /*printf("(%d,%d) : %d - %d\n", x, y, current, 
		    backtrack(array, colonnes, lignes, x, y, 0, HOLE));*/
	    if (current > max) {
		max = current;
	    }
	}
    }
    int current = array[y][x];
    if (current >= 4
	    && current >= array[y][x-1]
	    && current >= array[y-1][x-1]
	    && current >= array[y-1][x]) {
	extremum[*nbr_extremum].x = x;
	extremum[*nbr_extremum].y = y;
	(*nbr_extremum)++;
	/*printf("(%d,%d) : %d - %d\n", x, y, current, 
		backtrack(array, colonnes, lignes, x, y, 0, HOLE));*/
	if (current > max) {
	    max = current;
	}
    }
    return max;
}

int comparaison(char **doc1, int length_doc1, const char *name, char **doc2, int length_doc2,
	unsigned char **plagiat_words, unsigned char **reverse_plagiat_words)
{
    VALUE **array;
    int line;
    int col;
    t_coord *extremum;
    unsigned char **result;
#ifdef IMAGE
    t_matrix *matrix;
#endif
    int pos_file;
    int start_write_image;
    int absolute_pos;

    INFO("Initialisation du tableau d'analyse");
    array = malloc((MAXLINE+RECOUVREMENT)*sizeof(*array));
    if (array == NULL) {
	FATAL("Erreur d'allocation mémoire (%d octets)", ((MAXLINE+RECOUVREMENT)*sizeof(*array)));
	return -1;
    }
    for (line = 0; line < MAXLINE+RECOUVREMENT; line++) {
	DEBUG("Allocation des lignes d'analyse", );
	array[line] = malloc((length_doc2+1)*sizeof(VALUE));
	if (array[line] == NULL) {
	    FATAL("Echec de l'allocation (%d octets)", (length_doc2+1)*sizeof(VALUE));
	    return -1;
	}
    }

    INFO("Initialisation des premières lignes");
    for(line = 0; line < RECOUVREMENT; line++) {
	for (col = 0; col <= length_doc2; col++) {
	    array[line][col] = 0;
	}
    }

    INFO("Initialisation de la table des sommets");
    extremum = malloc((MAXLINE*100)*sizeof(*extremum));
    if (extremum == NULL) {
	FATAL("Echec de l'allocation mémoire (%d octets)", (MAXLINE*100)*sizeof(*extremum));
	return -1;
    }

    INFO("Initialisation de la zone de résultat");
    result = malloc((MAXLINE+RECOUVREMENT)*sizeof(*result));
    if (result == NULL) {
	FATAL("Echec de l'allocation mémoire (%d octets)",
	    (MAXLINE+RECOUVREMENT)*sizeof(*result));
	return -1;
    }
    for (line = 0; line < MAXLINE+RECOUVREMENT; line++) {
	DEBUG("Allocation mémoire");
	result[line] = calloc(1, (length_doc2+1)*sizeof(unsigned char));
	if (result[line] == NULL) {
	    FATAL("Echec de l'allocation (%d octets)", (length_doc2+1)*sizeof(unsigned char));
	    return -1;
	}
    }

    INFO("Initialisation de l'analyse inverse");
    *reverse_plagiat_words = malloc(length_doc2*sizeof(**reverse_plagiat_words));
    if (reverse == NULL) {
	FATAL("Echec de l'allocation mémoire (%d octets)", length_doc2*sizeof(**reverse_plagiat_words));
	return -1;
    }

    INFO("Initialisation de la zone de plagiat");
    *plagiat_words = malloc(length_doc1*sizeof(**plagiat_words));
    if (*plagiat_words == NULL) {
	FATAL("Echec de l'allocation mémoire (%d octets)", length_doc1*sizeof(**plagiat_words));
	return -1;
    }

#ifdef IMAGE
    INFO("Ouverture de l'image");
    matrix = open_matrix(name, length_doc2+1, length_doc1);
    if (matrix == NULL) {
	FATAL("Echec d'ouverture de l'image");
	return -1;
    }
#endif

    INFO("Lancement de la comparaison");
    pos_file = 0;
    start_write_image = RECOUVREMENT;
    absolute_pos = 0;
    while (pos_file + MAXLINE < length_doc1) {
	INFO("Remplir le tableau");
	for (line = RECOUVREMENT; line < MAXLINE+RECOUVREMENT; line++) {
	    array[line][0] = 0;
	    for (col = 1; col <= length_doc2; col++) {
		VALUE val1 = array[line][col-1] + REMOVE;
		VALUE val2 = array[line-1][col] + ADD;
		VALUE val3 = array[line-1][col-1] +
		    (strcmp(doc1[pos_file+line-RECOUVREMENT], doc2[col-1]) == 0 ? SAME : SUBSTITUTE); /* Substitution */
		array[line][col] = max3(val1, val2, val3);
		DEBUG("array[%d][%d] = %d", line, col, array[line][col]);
	    }
	}

	INFO("Recherche des sommets");
	int nbr_extremum;
	VALUE max = find_extremum(array, length_doc2+1, MAXLINE+RECOUVREMENT, extremum, &nbr_extremum);

	INFO("Nombre d'extremum : %d", nbr_extremum);
	INFO("Maximum : %d", max);

	detect_plagiat(array, length_doc2+1, MAXLINE+RECOUVREMENT, extremum, nbr_extremum, result, 
		*reverse_plagiat_words);

	INFO("Ecriture de l'image");
	for (line = start_write_image; line < MAXLINE; line++) {
#ifdef IMAGE
	    write_matrix(matrix, result[line]);
#endif
	    if (result[line][0] > 0) {
		(*plagiat_words)[absolute_pos] = 1;
	    } else {
		(*plagiat_words)[absolute_pos] = 0;
	    }
	    absolute_pos++;
	}
	start_write_image = 0;

	INFO("Préparation pour l'itération suivante");
	INFO("Copie des dernières lignes dans les premières");
	for (line = 0; line < RECOUVREMENT; line++) {
	    for (col = 0; col <= length_doc2; col++) {
		array[line][col] = array[MAXLINE+line][col];
		result[line][col] = result[MAXLINE+line][col];
	    }
	}

	INFO("Réinitialisation du résultat");
	for (line = RECOUVREMENT; line < MAXLINE+RECOUVREMENT; line++) {
	    for (col = 0; col <= length_doc2; col++) {
		result[line][col] = 0;
	    }
	}

	pos_file += MAXLINE;
    }

    INFO("Traitement du reste");

    int still_lines = length_doc1 - pos_file;
    for (line = RECOUVREMENT; line < RECOUVREMENT+still_lines; line++) {
	array[line][0] = 0;
	for (col = 1; col <= length_doc2; col++) {
	    VALUE val1 = array[line][col-1] + REMOVE;
	    VALUE val2 = array[line-1][col] + ADD;
	    VALUE val3 = array[line-1][col-1] + 
		(strcmp(doc1[pos_file+line-RECOUVREMENT], doc2[col-1]) == 0 ? SAME : SUBSTITUTE); /* Substitution */
	    array[line][col] = max3(val1, val2, val3);
	    DEBUG("array[%d][%d] = %d", line, col, array[line][col]);
	}
    }

    INFO("Recherche des sommets");
    int nbr_extremum;
    VALUE max = find_extremum(array, length_doc2+1, still_lines+RECOUVREMENT, extremum, &nbr_extremum);

    INFO("Nombre d'extremum : %d", nbr_extremum);
    INFO("Maximum : %d", max);

    INFO("Détection du plagiat");
    detect_plagiat(array, length_doc2+1, still_lines+RECOUVREMENT, extremum, nbr_extremum, result, 
	    *reverse_plagiat_words);

    INFO("Ecriture de l'image");
    for (line = start_write_image; line < still_lines+RECOUVREMENT; line++) {
#ifdef IMAGE
	write_matrix(matrix, result[line]);
#endif
	if (result[line][0] > 0) {
	    (*plagiat_words)[absolute_pos] = 1;
	} else {
	    (*plagiat_words)[absolute_pos] = 0;
	}
	absolute_pos++;
    }

    //INFO("Taux de plagiat : %d/%d (%d %%)", plagiat, length_doc1, (plagiat*100)/length_doc1);

#ifdef IMAGE
    INFO("Fermeture de l'image");
    close_matrix(matrix);
#endif

    INFO("Libération du tableau d'analyse");
    for (line = 0; line < MAXLINE+RECOUVREMENT; line++) {
	free(array[line]);
    }
    free(array);

    INFO("Libération de la table des sommets");
    free(extremum);

    INFO("Libération de la zone de résultat");
    for (line = 0; line < MAXLINE+RECOUVREMENT; line++) {
	free(result[line]);
    }
    free(result);

    INFO("Analyse terminée");

    return 1;

    //    write_image("real.png",array, length_l1+1, length_l2+1, max);
}

void display_plagiat_words(int length, unsigned char *plagiat_words)
{
    int start = 0;
    int activate = 0;
    int i;
    int plagiat;

    INFO("START");

    plagiat = 0;
    for (i = 0; i < length; i++) {
	if (plagiat_words[i] > 0) {
	    plagiat++;
	}
    }

    printf("%d\n", plagiat);

    start = 0;
    for (i = 0; i < length; i++) {
	DEBUG("%d", i);
	if (plagiat_words[i] > 0) {
	    if (!activate) {
		start = i;
		activate = 1;
	    }
	} else {
	    if (activate) {
		printf("%d-%d\n", start, i-1);
		activate = 0;
	    }
	}
    }

    if (activate) {
	printf("%d-%d\n", start, i-1);
    }

    INFO("END");
}

#if 0
int main(int argc, char *argv[])
{
    char **doc1;
    int nbr_words1;
    int i;
    char doc2name[1000];
    char image_filepath[1000];

    if (argc!=2) {
	printf("%s filename1\n", argv[0]);
	return 1;
    }

    doc1 = file_to_word_array(argv[1], &nbr_words1);

    while (scanf("%s", doc2name) == 1) {
	char **doc2;
	int nbr_words2;
	int plagiat;

	printf("Document de référence : %s\n", doc2name);
	doc2 = file_to_word_array(doc2name, &nbr_words2);

	sprintf(image_filepath,"%s_%s.png", argv[1], doc2name);

	plagiat = comparaison(doc1, nbr_words1, image_filepath, doc2, nbr_words2);
	printf("Analyse terminée : %s (%d/%d = %d %%)\n", doc2name,
		plagiat, nbr_words1, (plagiat*100)/nbr_words1);

	INFO("Libération de la mémoire du document de référence");
	for(i=0;i<nbr_words2;i++) {
	    free(doc2[i]);
	}
	free(doc2);
    }

    INFO("Libération de la mémoire du document analysé");
    for (i=0;i<nbr_words1;i++) {
	free(doc1[i]);
    }
    free(doc1);

    return 0;
}
#endif
