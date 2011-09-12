#ifndef _FINDONWEB_H
#define _FINDONWEB_H

#include "word_list.h"
#include "websearch.h"

/* Rechercher un fichier filepath découpé en blocs de seqsize grâce au 
 * search_engine. nbr_seq contient le nombre de séquences recherchés sur le web
 * à la fin de la recherche
 */
t_list_single find_on_web(const char *filepath, t_websearch search_engine, 
        int seqsize, int skip_words, int *nbr_seq);

#endif
