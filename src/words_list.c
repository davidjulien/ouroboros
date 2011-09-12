#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define NOLOG
#include "log.h"

#include "stream.h"
#include "words_list.h"

/* Construction d'une liste à partir d'une séquence de mots */
t_list_words cons(char first, t_words e, t_list_words l)
{
    t_list_words nl = malloc(sizeof(*l));

    if (nl == NULL) {
        ERROR("Erreur d'allocation mémoire : %s", strerror(errno) );
        return EMPTY_LIST;
    } else {
        FIRST(nl) = first;
        HEAD(nl) = e;
        NEXT(nl) = l;
        return nl;
    }
}

/* Ajoute une nouvelle séquence de mots dans une liste triée */
void add_sorted(t_words p, t_list_words *l)
{
    if (IS_EMPTY(*l)) {
        *l = cons(0, p, *l);
    } else if (lower_words(p, HEAD(*l))) {
        *l = cons(0, p, *l);
    } else if (eq_words(p, HEAD(*l))) {
        COUNT(HEAD(*l))++;
    } else {
        add_sorted(p, &NEXT(*l));
    }
}

t_words search_words(t_list_words l, int nbr, char **words)
{
    if (IS_EMPTY(l)) {
        return NULL;
    } else if (NBR_WORDS(HEAD(l)) == nbr) {
        int i;
        for(i=0; i<nbr; i++) {
            if (strcmp(WORDS(HEAD(l))[i], words[i]) != 0) {
                break;
            }
        }
        if (i == nbr) {
            return HEAD(l);
        } else {
            return search_words(NEXT(l), nbr, words);
        }
    } else {
        return search_words(NEXT(l), nbr, words);
    }
}

t_list_words cons_new_words(int nbr, char **words, t_list_words l)
{
    t_words w = search_words(l, nbr, words);
    if (w != NULL) {
        COUNT(w) += 1;
        return cons(0, w, l);
    } else {
        return cons(1, build_words(nbr, words), l);
    }
}

/* Libération de la mémoire occupée par la liste des mots. */
void free_list(t_list_words *l) 
{
    if (IS_EMPTY(*l)) {
        return ;
    } else {
        /* On ne supprime pas les mots car une autre liste s'en charge */
        t_list_words next = NEXT(*l);
        if (COUNT(HEAD(*l)) == 1) {
            free(WORDS(HEAD(*l)));
            free(HEAD(*l));
        } else {
            COUNT(HEAD(*l)) -= 1;
        }
        free(*l);

        *l = EMPTY_LIST;
        free_list(&next);
    }
}

/* Affichage d'une liste de séquences de mots */
void display_list(t_list_words l)
{
    if (IS_EMPTY(l)) {
        printf("FIN\n");
    } else {
	if (FIRST(l)) {
	    printf("FIRST ");
	}
	display_words(HEAD(l));
	display_list(NEXT(l));
    }
}

/* Calcul de la longueur de la liste */
int length_list(t_list_words l)
{
    if (IS_EMPTY(l)) {
	return 0;
    } else {
	return 1+length_list(NEXT(l));
    }
}

/* Recherche la position et la taille de la plus longue sous séquence */
