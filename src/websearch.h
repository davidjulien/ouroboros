#ifndef _WEBSEARCH_H
#define _WEBSEARCH_H

#include <regex.h>

typedef struct {
    const char *host;			/* Nom du serveur */
    unsigned short int portnum;		/* Port de connexion */
    const char *http_request;		/* Requête HTTP complète */
    const char *str_regex;		/* Expression régulière de filtrage */
    regex_t preg;			/* Expression régulière compilée */
} *t_websearch;

/* Construit une structure décrivant un moteur de recherche */
t_websearch new_websearch(const char *host, unsigned short int port, 
        const char *http_request, const char *str_regex);
void free_websearch(t_websearch *websearch);

/* Lance une recherche sur un site web pour récupérer des URL :
 * - websearch : info pour rechercher sur le web
 * - request : mots à chercher
 * - websites : tableau pour contenir les résultats
 * - nbr : nombre maximum de résultats
 */
int websearch(t_websearch websearch, const char *request, 
        char *websites[], int nbr);

/* Récupération d'un document par une requête HTTP
 * - host : nom du serveur
 * - portnum : port de connexion
 * - file_requested : fichier demandé
 * - Retourne un pointeur vers le document (NULL en cas de problème) et la
 *   taille dans size
 */
char *webget(const char *host, unsigned short int port, 
        const char *file_requested, int *size);

/* Retire l'entête web
 * - data : données venant du web
 * - size : pointeur sur la taille de la zone
 * - Retourne le pointeur sur le début réel et met à jour la zone
 */
//char *skip_header(char *data, int *size);

/* Extraction du type du fichier. La mémoire doit être désallouée */
//char *extract_filetype(char *data);

/* Extraction de l'encodage du fichier */
//char *extract_fileencoding(char *data);

/* Décomposition d'une URL pour extraire l'host, le port et le nom du fichier */
char *decompose_url(const char *url, short int *portnum, char **filename);

/* Récupération d'un fichier via une URL et stockage :
 * - url : URL 
 * - host : nom du serveur
 * - portnum : port de connexion 
 * - filename : nom du fichier local
 * - filetype : contiendra le type du fichier
 * - encoding : contiendra l'encodage du fichier */
/*void webget_file(const char *url, const char *host, short int portnum,
  const char *filename, char **filetype, char **encoding);*/
void webget_file(const char *url, const char *filename, 
        char **filetype, char **encoding);


char *url_to_filename(const char *url);
#endif
