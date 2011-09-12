/*
 * Cette méthode va découper le texte en séquences de N mots et comparer
 * l'apparition de ces séquences dans les deux fichiers.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "log.h"

#include "char_filter.h"
#include "words_list.h"
#include "file_analysis.h"
#include "substring_matching.h"

/* Analyse les deux listes pour compter le nombre de séquences en commun et le
 * nombre total de séquences */
void analyse_lists(t_list_words l1, t_list_words l2, int *common, int *total)
{
    if (IS_EMPTY(l1)) {
        *total += length_list(l2);
    } else if (IS_EMPTY(l2)) {
        *total += length_list(l1);
    } else if (eq_words(HEAD(l1),HEAD(l2))) {
        *common += 1;
        *total += 1;
        display_words(HEAD(l1));
        analyse_lists(NEXT(l1),NEXT(l2), common, total);
    } else if (lower_words(HEAD(l1),HEAD(l2))) {
        *total += 1;
        analyse_lists(NEXT(l1), l2, common, total);
    } else {
        *total += 1;
        analyse_lists(l1, NEXT(l2), common, total);
    }
}

double distance_substring_matching(t_file_info *file1, t_file_info *file2, 
        int nbr_words, int skip_words)
{
    int common, total;
    t_list_single l1_single;
    t_list_single l2_single;
    t_list_words l1;
    t_list_words l2;

    INFO("Analyse du fichier 1 : %s", file1->filepath);
    l1 = analyse_file(file1->filepath, nbr_words, skip_words, &l1_single, 1);

    INFO("Analyse du fichier 2 : %s", file2->filepath);
    l2 = analyse_file(file2->filepath, nbr_words, skip_words, &l2_single, 1);

    common = 0;
    total = 0;
    INFO("Analyse des listes de séquences");
    analyse_lists(l1, l2, &common, &total);

    INFO("Distance substring matching : Paires communes : %d / Total : %d",
            common, total);

    free_single_list(&l1_single);
    free_single_list(&l2_single);
    free_list(&l1);
    free_list(&l2);

    return 1.0 - ((double)common) / ((double)total);
}
