#include "document_list.h"

/*
 * Fonction comparant un document (doc_filepath) par rapport à un document de 
 * référence (ref_filepath) et retournant une liste indiquant les parties du 
 * document issues du document de référence. Le paramètre found contient le
 * nombre de blocs trouvés. Le paramètre threshold indique le nombre minimum de
 * mots pour accepter la séquence commune.
 */ 
t_ldoc compare_document(const char *doc_filepath, const char *ref_filepath,
        const char *ref_name, int threshold, int *found);

t_ldoc compare_document2(t_list_single doc, const char *doc_filepath, 
        const char *ref_filepath, const char *ref_name, int threshold,
        int *found);
