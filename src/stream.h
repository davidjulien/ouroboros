#include <stdio.h>

typedef int (*fnc_filter)(int c);
typedef unsigned char (*fnc_transform)(int c);

/* Prend en paramètre une zone mémoire, un buffer, et réalloue une nouvelle zone
 * mémoire pouvant contenir l'ancienne + le buffer. Le buffer est lu à partir de
 * la position pos */
char *realloc_word(char *word, char *buffer, int size, int pos);

/* Prend en paramètre un flux et une fonction de filtrage et extrait les
 * séquences validant le filtre et rejetant les autres */
char *extract_word(FILE *f, fnc_filter filter, fnc_transform transform,
        int *offset);

/* Extraction d'une zone d'un fichier */
char *extract_zone(FILE *f, int start_offset, int end_offset);

/* Prend en paramètre un flux et extrait les données dans un buffer */
char *extract_text(FILE *f);

/* Prend en paramètre un flux et extrait des données brutes. size sera
 * initialisé avec les données lues */
char *extract_raw(FILE *f, int *size,
        fnc_filter filter, fnc_transform transform);
