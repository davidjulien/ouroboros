/*
 * Structure de données stockant une liste de mots. A chaque mot est associé un
 * entier pouvant servir de compteur.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define NOLOG
#include "log.h"

#include "stream.h"
#include "word_list.h"

t_list_single cons_single(char *e, t_list_single l)
{
    t_list_single nl = malloc(sizeof(*nl));
    if (nl == NULL) {
        ERROR("Erreur d'allocation mémoire : %s", strerror(errno));
        return EMPTY_SL;
    } else {
        HEAD_SL(nl) = e;
        COUNT_SL(nl) = 1;
        WEIGHT_SL(nl) = 0;
        NEXT_SL(nl) = l;
        return nl;
    }
}



int add_single_sorted(char *word, int weight, t_list_single *l)
{
    if (IS_EMPTY_SL(*l)) {
        *l = cons_single(word, *l);
        WEIGHT_SL(*l) += weight;
        return 1;
    } else if (strcmp(word, HEAD_SL(*l)) < 0) {
        *l = cons_single(word, *l);
        WEIGHT_SL(*l) += weight;
        return 1;
    } else if (strcmp(word, HEAD_SL(*l))==0) {
        COUNT_SL(*l)++;
        WEIGHT_SL(*l) += weight;
        return 0;
    } else {
        return add_single_sorted(word, weight, &NEXT_SL(*l));
    }
}

/*
   void free_single_list(t_list_single *l) 
   {
   if (IS_EMPTY_SL(*l)) {
   return ;
   } else {
   t_list_single *nl = &NEXT_SL(*l);

   free(HEAD_SL(*l));
   free(*l);
 *l = EMPTY_SL;

 return free_single_list(nl);
 }
 }
 */

void free_single_list(t_list_single *l)
{
    while(!IS_EMPTY_SL(*l)) {
        t_list_single nl = NEXT_SL(*l);

        free(HEAD_SL(*l));
        free(*l);
        *l = nl;
    }
}


void display_single_list(t_list_single l)
{
    if (IS_EMPTY_SL(l)) {
        printf("FIN\n");
    } else {
        printf("%d %d %s\n", COUNT_SL(l), WEIGHT_SL(l), HEAD_SL(l));
        display_single_list(NEXT_SL(l));
    }
}



void divide_single_list(t_list_single *l, t_list_single *l1, t_list_single *l2)
{
    if (IS_EMPTY_SL(*l)) {
        return ;
    } else {
        t_list_single temp = NEXT_SL(*l);
        NEXT_SL(*l) = *l1;
        *l1 = *l2;
        *l2 = *l;
        *l = temp;
        divide_single_list(l, l1, l2);
    }
}




void merge_aux(t_list_single l1, t_list_single l2, t_list_single *r)
{
    if (IS_EMPTY_SL(l1)) {
        *r = l2;
    } else if (IS_EMPTY_SL(l2)) {
        *r = l1;
    } else if (COUNT_SL(l1) > COUNT_SL(l2)) {
        *r = l1;
        merge_aux(NEXT_SL(l1), l2, &NEXT_SL(*r));
    } else {
        *r = l2;
        merge_aux(l1, NEXT_SL(l2), &NEXT_SL(*r));
    }
}

t_list_single merge(t_list_single l1, t_list_single l2)
{
    t_list_single r;
    merge_aux(l1, l2, &r);
    return r;
}



void sort_single_list_by_count(t_list_single *l)
{
    if (IS_EMPTY_SL(*l) || IS_EMPTY_SL(NEXT_SL(*l))) {
        return ;
    } else {
        t_list_single l1 = EMPTY_SL;
        t_list_single l2 = EMPTY_SL;
        divide_single_list(l, &l1, &l2);
        sort_single_list_by_count(&l1);
        sort_single_list_by_count(&l2);
        *l = merge(l1, l2);
    }
}

void merge_weight_aux(t_list_single l1, t_list_single l2, t_list_single *r)
{
    if (IS_EMPTY_SL(l1)) {
        *r = l2;
    } else if (IS_EMPTY_SL(l2)) {
        *r = l1;
    } else if (WEIGHT_SL(l1) > WEIGHT_SL(l2)) {
        *r = l1;
        merge_weight_aux(NEXT_SL(l1), l2, &NEXT_SL(*r));
    } else {
        *r = l2;
        merge_weight_aux(l1, NEXT_SL(l2), &NEXT_SL(*r));
    }
}

t_list_single merge_weight(t_list_single l1, t_list_single l2)
{
    t_list_single r;
    merge_weight_aux(l1, l2, &r);
    return r;
}


void sort_single_list_by_weight(t_list_single *l)
{
    if (IS_EMPTY_SL(*l) || IS_EMPTY_SL(NEXT_SL(*l))) {
        return ;
    } else {
        t_list_single l1 = EMPTY_SL;
        t_list_single l2 = EMPTY_SL;
        divide_single_list(l, &l1, &l2);
        sort_single_list_by_weight(&l1);
        sort_single_list_by_weight(&l2);
        *l = merge_weight(l1, l2);
    }
}


void save_aux(t_list_single l, FILE *f)
{
    if (IS_EMPTY_SL(NEXT_SL(l))) {
        fprintf(f, "%s", HEAD_SL(l));
        return ;
    } else {
        fprintf(f, "%s ", HEAD_SL(l));
        save_aux(NEXT_SL(l), f);
    }
}

void save_list(t_list_single l, const char *filename)
{
    FILE *f;

    INFO("Ouverture du fichier en écriture : %s", filename);
    f = fopen(filename,"w");

    save_aux(l, f);

    INFO("Fermeture du fichier : %s", filename);
    fclose(f);
}




t_list_single reverse_aux(t_list_single l, t_list_single res)
{
    if (IS_EMPTY_SL(l)) {
        return res;
    } else {
        t_list_single temp = NEXT_SL(l);
        NEXT_SL(l) = res;
        return reverse_aux(temp, l);
    }
}

t_list_single reverse(t_list_single *l)
{
    *l = reverse_aux(*l, EMPTY_SL);
    return *l;
}


int longuest_sublist_aux(t_list_single doc, t_list_single ref, int count) 
{
    if (IS_EMPTY_SL(doc) || IS_EMPTY_SL(ref)) {
        return count;
    } else if (strcmp(HEAD_SL(doc), HEAD_SL(ref)) != 0) {
        return count;
    } else {
        return longuest_sublist_aux(NEXT_SL(doc), NEXT_SL(ref), count+1);
    }
}

int longuest_sublist_aux2(t_list_single doc, t_list_single ref, int best_count)
{
    if (IS_EMPTY_SL(ref)) {
        return best_count;
    } else {
        int local_count = longuest_sublist_aux(doc, ref, 0);
        return longuest_sublist_aux2(doc, NEXT_SL(ref), 
                local_count > best_count ? local_count : best_count);
    }
}

int longuest_sublist(t_list_single doc, t_list_single ref)
{
    return longuest_sublist_aux2(doc, ref, 0);

}

/* Calcul de la longueur de la liste */
int length_single_list(t_list_single l)
{
    if (IS_EMPTY_SL(l)) {
        return 0;
    } else {
        return 1+length_single_list(NEXT_SL(l));
    }
}


#if 0
t_list_single longuest_sublist_aux(t_list_single doc, t_list_single ref, 
        t_list_single start_doc, t_list_single start_ref,
        t_list_single next_try_doc,
        int current_count, t_list_single current_list,
        int *best_count, t_list_single *best_list)
{
    if (IS_EMPTY_SL(doc)) {
        return *best_list;
    } else if (IS_EMPTY_SL(ref)) {
        if (current_count <= *best_count) {
            /*	    printf("ENDMATCH (%d) : %p\n", current_count, next_try_doc);*/
            return longuest_sublist_aux(next_try_doc, start_ref, 
                    start_doc, start_ref, EMPTY_SL,
                    0, EMPTY_SL, best_count, best_list);
        } else {
            printf("ENDMATCH BEST (%d): %p\n", current_count, next_try_doc);
            *best_count = current_count;
            *best_list = current_list;
            return longuest_sublist_aux(next_try_doc, start_ref, 
                    start_doc, start_ref, EMPTY_SL,
                    0, EMPTY_SL, best_count, best_list);
        }
    } else if (strcmp(HEAD_SL(doc), HEAD_SL(ref)) == 0) {
        printf("MATCH (%d): %s ", current_count, HEAD_SL(doc));
        if (next_try_doc != EMPTY_SL 
                || (strcmp(HEAD_SL(doc), HEAD_SL(start_doc)) != 0 &&
                    current_count == 0)) {
            /* Si un autre point de départ n'a pas été trouvé et que le terme
             * courant ne peut l'être OU BIEN le départ est déjà trouvé */
            return longuest_sublist_aux(NEXT_SL(doc), NEXT_SL(ref), 
                    start_doc, start_ref,
                    next_try_doc, current_count+1, 
                    current_count == 0 ? doc : current_list, 
                    best_count, best_list);
        } else {
            return longuest_sublist_aux(NEXT_SL(doc), NEXT_SL(ref),
                    start_doc, start_ref,
                    EMPTY_SL, current_count+1,
                    current_count == 0 ? doc : current_list, 
                    best_count, best_list);
        }
    } else {
        if (current_count <= *best_count) {
            /*	    printf("ENDMATCH (%d) : %p\n", current_count, next_try_doc);*/
            return longuest_sublist_aux(start_doc, NEXT_SL(ref),
                    start_doc, NEXT_SL(ref), EMPTY_SL,
                    0, EMPTY_SL, best_count, best_list);
        } else {
            printf("ENDMATCH BEST (%d): %p\n", current_count, next_try_doc);
            *best_count = current_count;
            *best_list = current_list;
            return longuest_sublist_aux(start_doc, NEXT_SL(ref),
                    start_doc, NEXT_SL(ref), EMPTY_SL,
                    0, EMPTY_SL, best_count, best_list);
        }
        /*
           return longuest_sublist_aux(doc, NEXT_SL(ref), start_doc, start_ref,
           next_try_doc, 0, EMPTY_SL, best_count, best_list);
           */
    }
}

/* Fonction auxilliaire parcourant les différents points de départ de la liste
 * de référence
 */
t_list_single longuest_sublist_aux1(t_list_single doc, t_list_single ref,
        int *best_count, t_list_single best_list)
{
    if (IS_EMPTY_SL) {
        return best_list;
    } else {
        int local_count = 0;
        t_list_single local_best = 
            longuest_sublist_aux(doc, ref, doc, ref, EMPTY_SL);
        if (local_count > *best_count) {
            return longuest_sublist_aux1(doc,NEXT_SL(ref), 
                    local_count, local_best);
        } else {
            return longuest_sublist_aux1(doc, NEXT_SL(ref),
                    best_count, best_list);
        }
    }
}

t_list_single longuest_sublist(t_list_single doc, t_list_single ref, int *count)
{
    if (EMPTY_SL(ref))
        t_list_single l;
    *count = 0;
    l = EMPTY_SL;

    return longuest_sublist_aux(doc, ref, doc, ref, EMPTY_SL, 0, EMPTY_SL,
            count, &l);
}

#endif
