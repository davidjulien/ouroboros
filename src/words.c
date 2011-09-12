#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include <errno.h>
#include "log.h"

#include "stream.h"
#include "words_list.h"

/* Construction d'un bloc de mots */
t_words build_words(int nbr, char **words)
{
    t_words p = malloc(sizeof(*p));

    COUNT(p) = 1;
    NBR_WORDS(p) = nbr;
    WORDS(p) = words;

    return p;
}

void free_words(t_words *p)
{
    free(*p);
    *p = NULL;
}

void deep_free_words(t_words *p)
{
    int i;
    for(i=0;i<NBR_WORDS(*p); i++) {
        free(WORDS(*p)[i]);
    }
    free(WORDS(*p));
    free(*p);
    *p = NULL;
}

void display_words(t_words p)
{
    int i;
    printf("Bloc de %d mots (%d) : ", NBR_WORDS(p), COUNT(p));
    for(i=0;i<NBR_WORDS(p);i++) {
        printf("%s ", WORDS(p)[i]);
    }
    printf("\n");
}

/* Comparaison de deux éléments par égalité */
int eq_words(t_words p1, t_words p2)
{
    int i;
    for(i=0;i<NBR_WORDS(p1);i++) {
        if (strcmp(WORDS(p1)[i], WORDS(p2)[i]) != 0) {
            return 0;
        }
    }
    return 1;
}

/* Comparaison de deux éléments par < */
int lower_words(t_words p1, t_words p2)
{
    int i;
    for(i=0;i<NBR_WORDS(p1);i++) {
        int cmp = strcmp(WORDS(p1)[i], WORDS(p2)[i]);
        if (cmp < 0) {
            return 1;
        } else if (cmp > 0) {
            return 0;
        }
    }
    return 0;
}
