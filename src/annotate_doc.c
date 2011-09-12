#include <stdio.h>
#include <ctype.h>
#include <string.h>

/*#define DEBUGLEVEL*/
#include "log.h"

#include "stream.h"
#include "document_list.h"
#include "file_analysis.h"
#include "annotate_doc.h"

char *alloc_word(const char *word)
{
    char *copy = malloc(strlen(word)+1);
    if (copy == NULL) {
        FATAL("Erreur d'allocation mémoire : %s",strerror(errno));
        exit(100);
    }
    strcpy(copy, word);
    return copy;
}

t_ldoc compare_document2(t_list_single doc, const char *doc_filepath,
        const char *ref_filepath, const char *ref_name, int threshold, 
        int *found)
{
    t_list_single ref;
    t_list_single sources;
    t_ldoc ldoc;
    int count;
    FILE *fdoc;

    INFO("Ouverture du document <%s>", doc_filepath);
    fdoc = fopen(doc_filepath, "r");

    INFO("Analyse de <%s>", ref_filepath);
    ref = file_to_word_list(ref_filepath);

    INFO("Comparaison des deux documents");
    ldoc = EMPTY_LDOC;
    *found = 0;
    while (!IS_EMPTY_SL(doc)) {
        int start_offset;
        int end_offset;

        DEBUG("Recherche à partir de %s", HEAD_SL(doc));
        count = longuest_sublist(doc, ref);
        DEBUG("Trouver %d mots", count);

        start_offset = COUNT_SL(doc);
        if (count < threshold) {
            sources = EMPTY_SL;

            if (IS_EMPTY_SL(NEXT_SL(doc))) {
                end_offset = start_offset + strlen(HEAD_SL(doc)) + 1;
            } else {
                end_offset = COUNT_SL(NEXT_SL(doc));
            }
            doc = NEXT_SL(doc);
            count = 1;
        } else {
            int i;
            sources = cons_single(alloc_word(ref_name), EMPTY_SL);
            *found += count;

            end_offset = 0;

            for(i=0; i<count; i++) {
                end_offset = COUNT_SL(doc) + strlen(HEAD_SL(doc));
                doc = NEXT_SL(doc);
            }

            if (!IS_EMPTY_SL(doc)) {
                end_offset = COUNT_SL(doc);
            } else {
                end_offset += 1;
            }
        }

        ldoc = cons_ldoc(extract_zone(fdoc, start_offset, end_offset),
                start_offset, end_offset, sources, ldoc, count);
    }

    DEBUG("Libération de la mémoire");
    free_single_list(&ref);

    INFO("Fermeture du document");
    fclose(fdoc);

    return ldoc;
}

t_ldoc compare_document(const char *doc_filepath, const char *ref_filepath,
        const char *ref_name, int threshold, int *found)
{
    t_list_single doc;
    FILE *fdoc;
    t_ldoc ldoc;

    INFO("Ouverture du document <%s>", doc_filepath);
    fdoc = fopen(doc_filepath, "r");

    INFO("Analyse de <%s>", doc_filepath);
    doc = file_to_word_list(doc_filepath);

    INFO("Fermeture du document");
    fclose(fdoc);

    ldoc = compare_document2(doc, doc_filepath, 
            ref_filepath, ref_name, threshold, found);

    free_single_list(&doc);

    return ldoc;
}
