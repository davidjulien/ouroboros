/*
 * Séquence de mots
 *
 */

#ifndef _WORDS_H
#define _WORDS_H

#include <stdlib.h>

#include "distance.h"
#include "word_list.h"

/* Séquence de mots contenant un compteur indiquant le nombre de fois où la
 * séquence a été trouvée */
typedef struct {
    int count;			/* Nombre de fois où cette séquence existe */
    int nbr_words;		/* Nombre de mots dans la séquence */
    char **words;		/* Stockage des mots */
} *t_words;

#define COUNT(W)	((W)->count)
#define NBR_WORDS(W)	((W)->nbr_words)
#define WORDS(W)	((W)->words)

t_words build_words(int nbr, char **words);
void free_words(t_words *pwords);
void deep_free_words(t_words *pwords);

void display_words(t_words p);
int eq_words(t_words p1, t_words p2);
int lower_words(t_words p1, t_words p2);

#endif
