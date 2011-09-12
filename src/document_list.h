/*
 * Structure de données représentant un document sous la forme d'une liste de
 * séquences de mots.
 *
 */

#ifndef _DOC_LIST_H
#define _DOC_LIST_H

#include <stdlib.h>

#include "distance.h"
#include "word_list.h"
#include "words.h"

/* Liste de séquences de mots */
typedef struct __list {
    char *words;		/* Séquence de mots */
    int nbr;			/* Nombre de mots */
    int start_offset;		/* Offset du début de la séquence */
    int end_offset;		/* Offset de fin de la séquence */
    t_list_single references;	/* Liste pouvant servir à stocker les origines 
                                   possibles de la séquence */
    struct __list *next;
} *t_ldoc;

#define EMPTY_LDOC		(t_ldoc)NULL
#define LDOC_WORDS(L)		((L)->words)
#define LDOC_NBR(L)		((L)->nbr)
#define LDOC_START(L)		((L)->start_offset)
#define LDOC_END(L)		((L)->end_offset)
#define LDOC_REF(L)		((L)->references)
#define LDOC_NEXT(L)		((L)->next)
#define IS_LDOC_EMPTY(L)	((L)==EMPTY_LDOC)

t_ldoc cons_ldoc(char *words, int start_offset, int end_offset, 
        t_list_single references, t_ldoc l, int nbr);
void free_ldoc(t_ldoc *l);


int remove_too_small(t_ldoc l, int minwords, int maxdist, int *nbr);

void display_ldoc(t_ldoc l);
t_ldoc reverse_ldoc(t_ldoc *l);

void generate_report_aux(t_ldoc l, FILE *f);
void generate_report(const char *filename, t_ldoc l, const char *source);

void save_ldoc_positions(t_ldoc l, FILE *f);
#endif
