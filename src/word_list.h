#ifndef _WORD_LIST_H
#define _WORD_LIST_H

#include <stdlib.h>

/* Liste de mots simples */
typedef struct __slist {
    char *elt;
    int count;
    int weight;
    struct __slist *next;
} *t_list_single;

#define EMPTY_SL	(t_list_single)NULL
#define HEAD_SL(L)	((L)->elt)
#define COUNT_SL(L)	((L)->count)
#define WEIGHT_SL(L)	((L)->weight)
#define NEXT_SL(L)	((L)->next)
#define IS_EMPTY_SL(L)	((L)==EMPTY_SL)

t_list_single cons_single(char *e, t_list_single l);
int add_single_sorted(char *word, int weight, t_list_single *l);
void free_single_list(t_list_single *);
void display_single_list(t_list_single);
void divide_single_list(t_list_single *l, t_list_single *l1, t_list_single *l2);
t_list_single merge(t_list_single l1, t_list_single l2);
void sort_single_list_by_count(t_list_single *l);
void sort_single_list_by_weight(t_list_single *l);

void save_list(t_list_single l, const char *filename);

t_list_single reverse(t_list_single *l);

int longuest_sublist(t_list_single doc, t_list_single ref); 

int length_single_list(t_list_single l);

#endif
