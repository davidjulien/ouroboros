/*
 * Structure de données stockant une liste de séquences de mots. A chaque 
 * séquence est associée un entier comptant le nombre de fois où cette séquence
 * est apparue.
 *
 */

#ifndef _WORDS_LIST_H
#define _WORDS_LIST_H

#include <stdlib.h>

#include "distance.h"
#include "word_list.h"
#include "words.h"

/* Liste de séquences de mots */
typedef struct __words_list {
    t_words elt;		/* Séquence de mots */
    char first;			/* 1 si c'est la première occurence, 0 sinon */
    struct __words_list *next;
} *t_list_words;

#define EMPTY_LIST	(t_list_words)NULL
#define FIRST(L)	((L)->first)
#define HEAD(L)		((L)->elt)
#define NEXT(L)		((L)->next)
#define IS_EMPTY(L)	((L)==EMPTY_LIST)

t_list_words cons(char first, t_words e, t_list_words l);
t_list_words cons_new_words(int nbr, char **words, t_list_words l);
void add_sorted(t_words p, t_list_words *l);

void free_list(t_list_words *l);

void display_list(t_list_words l);
int length_list(t_list_words l);
#endif
