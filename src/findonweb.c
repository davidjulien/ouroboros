#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NOLOG
#include "log.h"

#include "stream.h"
#include "words_list.h"
#include "word_list.h"
#include "file_analysis.h"
#include "substring_matching.h"

#include "findonweb.h"

#define NBR_WEBSITES 5 // 10

char *build_request(t_words w)
{
    int i;
    char *buffer = NULL;
    int size = 0;
    for(i=0;i<NBR_WORDS(w);i++) {
        int ln = strlen(WORDS(w)[i]);
        char *lbuff = malloc((ln+2)*sizeof(char));
        if (lbuff == NULL) {
            FATAL("Erreur d'allocation mémoire : %s", strerror(errno));
            exit(100);
        }
        sprintf(lbuff, "%s+", WORDS(w)[i]);
        buffer = realloc_word(buffer, lbuff, size, ln+1);
        size += ln+1;
        free(lbuff);
    }

    return buffer;
}

void free_request(char *req)
{
    free(req);
}

t_list_single find_aux(t_list_words l, t_websearch search_engine, 
        t_list_single sites)
{
    if (IS_EMPTY(l)) {
        return sites;
    } else {
        char *results[NBR_WEBSITES];
        int count;
        char *request;
        int i;

        INFO("Construction de la requête");
        request = build_request(HEAD(l));

        INFO("Requête : %s", request);
        count = websearch(search_engine, request, results, NBR_WEBSITES);
        INFO("Documents trouvés : %d", count);

        INFO("Stockage des sites trouvés");
        for(i=0;i<count;i++) {
            if (add_single_sorted(results[i], NBR_WEBSITES-i, &sites) == 0) {
                free(results[i]);
            }
        }

        INFO("Libération de la requête");
        free_request(request);

        return find_aux(NEXT(l), search_engine, sites);
    }
}

t_list_single find_on_web(const char *filepath, t_websearch search_engine, 
        int nbr_words, int skip_words, int *nbr_seq)
{
    t_list_single single;
    t_list_words l;
    t_list_single sites;

    INFO("Découpage du fichier");
    l = analyse_file(filepath, nbr_words, skip_words, &single, 0);

    *nbr_seq = length_list(l);

    INFO("Récupération des sites");
    sites = find_aux(l, search_engine, EMPTY_SL);

    INFO("Tri les sites trouvés");
    sort_single_list_by_weight(&sites);

    DEBUG("Libération de la mémoire");
    free_list(&l);
    free_single_list(&single);

    return sites;
}
