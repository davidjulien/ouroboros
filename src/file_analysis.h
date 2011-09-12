#include "words_list.h"
#include "word_list.h"
#include "int_list.h"

/* Analyse un fichier pour en extraire une liste de séquences de mots, avec un
 * saut de <skip_words> mots entre deux séquences (minimum 1) */
t_list_words analyse_file(const char *filepath, int nbr_words, int skip_words,
        t_list_single *allwords, char sorted);

/* Analyse un fichier pour en extraire la liste des mots ainsi que leur position
 * dans le fichier :
 * - filepath : fichier à analyser
 * - Retourne la liste
 */
t_list_single file_to_word_list(const char *filepath);

/* Analyse un fichier pour en extraire un tableau de mots
 * - filepath : fichier à analyser
 * - nbr : nombre de mots trouvés
 */
char **file_to_word_array(const char *filepath, int *nbr);

/* Retourne le type du fichier */
char *file_type(const char *filepath, char **encoding);

/* Construit la carte d'un fichier c'est à dire le numéro du mot se trouvant au
 * début de chaque ligne */
t_list_int build_map(const char *docname, t_list_single doc, int max_column);
