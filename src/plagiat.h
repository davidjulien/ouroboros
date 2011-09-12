#include "websearch.h"

/* Détection du plagiat d'un document
 * - doc_filepath : chemin vers le fichier à analyser
 * - websearch : moteur de recherche à utiliser
 * - searchwords : nombre de mots à chercher sur le moteur
 * - searchskip : nombre de mots à avancer après chaque recherche (à partir du
 *   premier mot de la recherche précédente)
 * - threshold : nombre minimum de mots en commun pour considérer qu'une partie
 *   du texte est un plagiat potentiel
 * - minwords : nombre minimum de mots pour valider la séquence
 * - maxgap : nombre maximum de mots entre deux petites séquences pour décider
 *   s'il est intéressant de les conserver malgré tout.
 *
 * La fonction retourne 1 si tout se passe bien, 0 sinon */
int detect_plagiat(const char *doc_filepath,
        t_websearch websearch, int searchwords, int searchskip,
        int threshold, int minwords, int maxgap);
