/*
 * Fonctions utilisant une connexion web
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define DEBUGLEVEL
//#define NOLOG
#include "log.h"

#include "char_filter.h"
#include "socket.h"
#include "stream.h"
#include "file_analysis.h"
#include "websearch.h"

t_websearch new_websearch(const char *host, unsigned short int port, 
        const char *http_request, const char *str_regex)
{
    t_websearch w = malloc(sizeof(*w));

    if (w == NULL) {
        FATAL("Erreur d'allocation mémoire : %s", strerror(errno));
        exit(100);
    } else {
        w->host = host;
        w->portnum = port;
        w->http_request = http_request;
        w->str_regex = str_regex;

        if (regcomp(&(w->preg), w->str_regex, REG_EXTENDED) != 0) {
            ERROR("Echec de l'initialisation de l'expression rationnelle");
            return NULL;
        } else {
            return w;
        }
    }
}

void free_websearch(t_websearch *websearch)
{
    regex_t p;
    DEBUG("Libération de la regexp");
    p = (*websearch)->preg;
    regfree(&p);
    free(*websearch);
    *websearch = NULL;
}

int websearch(t_websearch websearch, const char *request,
        char *websites[], int nbr)
{
    int match;
    size_t nmatch = 0;
    int count = 0;
    regmatch_t *pmatch = NULL;

    DEBUG("Allocation de la mémoire pour la réponse de la regexp");
    nmatch = (websearch->preg).re_nsub + 1;
    pmatch = malloc (sizeof (*pmatch) * nmatch);
    if (pmatch == NULL) {
        FATAL("Erreur d'allocation mémoire : %s", strerror(errno));
        exit(100);
    } else {
        char *text;
        char *http_request;
        int size;

        DEBUG("Allocation de mémoire pour la requête HTTP");
        http_request = malloc(
                (strlen(websearch->http_request)+strlen(request)+1)
                *sizeof(char));
        if (http_request == NULL) {
            FATAL("Erreur d'allocation mémoire : %s", strerror(errno));
            exit(100);
        }

        sprintf(http_request, websearch->http_request, request);

        INFO("Récupération du résultat de la recherche");
        text = webget(websearch->host, websearch->portnum, http_request, 
                &size);

        INFO("Libération de la mémoire de la requête HTTP");
        free(http_request);

        if (text != NULL) {
            char *current;

            DEBUG("Extraction des liens contenus dans la réponse: %s", text);
            current = text;
            count = 0;
            while (count < nbr &&
                    (match = regexec(&(websearch->preg), current, 
                                     nmatch, pmatch, 0))==0) {
                INFO("Nouveau lien trouvé");
                /* Le champ 1 contient la sous-partie à extraire */
		int start = pmatch[1].rm_so;
		int end = pmatch[1].rm_eo;
		size_t size = end - start;

		/* Réservation de la place nécessaire */
		websites[count] = malloc (sizeof (char) * (size + 1));
		if (websites[count] == NULL) {
		    ERROR("Erreur d'allocation mémoire : %s", 
			    strerror(errno));
		} else {
		    strncpy(websites[count], &current[start], size);
		    websites[count][size] = '\0';
		    INFO("Ajout du lien : %s", websites[count]);
		    count += 1;
		}

		/* On saute toute la zone filtrée par la regexp */
		current = current + pmatch[0].rm_eo;
	    }
	    INFO("Fin de l'extraction des liens");

	    if (count < nbr && match != REG_NOMATCH) {
		WARNING("Erreur lors de l'extraction des liens : %d", 
			match);
	    }

	    /* Libération du texte */
	    DEBUG("Libération buffer du texte");
	    free(text);
	}
    }

    DEBUG("Libération réponse au filtrage");
    free(pmatch);

    return count;
}

/*
 * Récupération d'un fichier à travers le web
 */
#define BUFFERSIZE 8192
char *webget(const char *host, unsigned short int portnum, 
	const char *file_requested, int *size)
{
    int fd;
    FILE *socket_read;
    FILE *socket_write;
    char *doc;
    int length;
    char buffer[BUFFERSIZE];
    int position;
    int is_chuncked;

    INFO("Connexion au serveur %s:%d", host, portnum);
    fd = establish(host, portnum);
    if (fd == -1) {
	*size = 0;
	return NULL;
    }

    INFO("Ouverture des flux lecture/écriture");
    socket_read = fdopen(fd, "r");
    if (socket_read == NULL) {
	ERROR("Echec de l'ouverture en lecture");
	*size = 0;
	return NULL;
    }

    socket_write = fdopen(fd, "w");
    if (socket_write == NULL) {
	ERROR("Echec de l'ouverture en écriture");
	*size = 0;
	return NULL;
    }

    INFO("Envoie de la requête HTTP au serveur pour récupérer %s", 
	    file_requested);
    fprintf(socket_write, "GET %s HTTP/1.1\nHost: %s\n\n", //Connection: close\n\n",
	    file_requested, host);
    fflush(socket_write);

    INFO("Lecture de la réponse à la requête HTTP");
    fgets(buffer, BUFFERSIZE, socket_read);
    DEBUG("Réponse : %s", buffer);
    if (strcmp(buffer, "HTTP/1.1 200 OK\r\n") == 0) {
        DEBUG("Transfert fractionné");
        is_chuncked = 1;
    } else {
        DEBUG("Transfert non fractionné");
        is_chuncked = 0;
    }

    INFO("Lecture de l'entête");
    while(fgets(buffer, BUFFERSIZE, socket_read) != NULL && strcmp(buffer, "\r\n") != 0) {
	DEBUG("En-tête : %s", buffer);
    }
    if (buffer == NULL) {
	ERROR("Erreur de lecture : %s", strerror(errno));
	*size = 0;
	return NULL;
    }

    INFO("Lecture du document");
    if (is_chuncked) {
        position = 0;
        doc = malloc(sizeof(char));
        if (doc == NULL) {
            FATAL("Erreur d'allocation mémoire : %s", strerror(errno));
            exit(100);
        }
        *size = 0;
        while (fscanf(socket_read,"%x", &length) == 1 && length > 0) {
            char *newptr;
            DEBUG("Taille du chunk : %d", length);
            fscanf(socket_read,"\r\n");
            *size += length;
            newptr = realloc(doc, *size+1);
            if (newptr == NULL) {
                ERROR("Erreur d'allocation mémoire");
                free(doc);
                *size = 0;
                return NULL;
            } else {
                doc = newptr;
            }
            while(length > 0) {
                int s = fread(doc+position, sizeof(char), length, socket_read);
                if (s == 0) {
                    ERROR("Erreur de lecture d'un chunk : %s", strerror(errno));
                    free(doc);
                    return NULL;
                }
                length -= s;
                position += s;
            }
        }
        doc[*size] = '\0';
    } else {
        char buffer[BUFFERSIZE];
        int s;
        doc = malloc(sizeof(char));
        if (doc == NULL) {
            FATAL("Erreur d'allocation mémoire : %s", strerror(errno));
            exit(100);
        }
        *size = 0;
        while ((s = fread(buffer, sizeof(char), BUFFERSIZE, socket_read)) > 0) {
            int old_size = *size;
            *size += s;
            char *newptr = realloc(doc, *size+1);
            if (newptr == NULL) {
                ERROR("Erreur d'allocation mémoire");
                free(doc);
                *size = 0;
                return NULL;
            } else {
                doc = newptr;
            }
            memcpy(doc + old_size, buffer, s);
        }
        doc[*size] = '\0';
    }

    //doc = extract_raw(socket_read, size, &everything, &stable_transform);
    DEBUG("Réponse : %s", doc);

    INFO("Fermeture des flux de lecture/écriture");
    fclose(socket_read);
    fclose(socket_write);

    INFO("Fermeture de la socket");
    close_socket(fd);

    return doc;
}

char *skip_header(char *data, int *size)
{
    char *new_data;

    new_data = strstr(data, "\r\n\r\n") + 4;
    *size = *size - (new_data - data);

    return new_data;
}

#if 0
void webget_file(const char *url, const char *host, short int portnum,
	const char *filename, char **filetype, char **encoding)
{
    char *ref;
    char *realdoc;
    int size;
    FILE *f;

    INFO("Récupération de %s depuis %s:%d", url, host, portnum);
    ref = webget(host, portnum, url, &size);
    INFO("Récupération réussie");

    /*
     *filetype = extract_filetype(ref);
     INFO("Type : %s", *filetype);

     *encoding = extract_fileencoding(ref);
     INFO("Encodage : %s", *encoding);
     */

    INFO("Stockage dans le fichier : %s", filename);
    realdoc = skip_header(ref, &size);
    f = fopen(filename, "w");
    fwrite(realdoc, sizeof(unsigned char), size, f);
    fclose(f);

    *filetype = file_type(filename);
    *encoding = malloc(sizeof(char));
    *encoding[0] = '\0';

    free(ref);
}
#endif

#define WGET	"wget -t 3 --connect-timeout=60 -q -O \"%s\" \"%s\""
void webget_file(const char *url, const char *filename, 
	char **filetype, char **encoding)
{
    char *buffer;
    INFO("Récupération de <%s> dans <%s>", url, filename);

    DEBUG("Réservation de la mémoire");
    buffer = malloc(sizeof(WGET)+strlen(url)+strlen(filename)+1);
    if (buffer == NULL) {
	FATAL("Erreur d'allocation mémoire : %s", strerror(errno));
	exit(100);
    }
    sprintf(buffer, WGET, filename, url);

    INFO("Exécution de la commande : %s", buffer);
    system(buffer);

    DEBUG("Libération de la mémoire");
    free(buffer);

    *filetype = file_type(filename, encoding);
}

char *extract_filetype(char *data)
{
    char *new_data;
    char *filetype;
    int count;

    INFO("extract_filetype");

    new_data = strstr(data, "Content-Type: ") + 14;
    if (new_data == NULL) {
	INFO("Unknown");
	filetype = malloc(8*sizeof(char));
	if (filetype == NULL) {
	    FATAL("Erreur d'allocation mémoire : %s", strerror(errno));
	    exit(100);
	}
	strcpy(filetype,"unknown");
	return filetype;
    } else {
	INFO("Extract");
	count = 0;
	while(new_data[count] != '\r' && new_data[count] != '\n' && 
		new_data[count] != ';') {
	    printf("Skip : %c\n", new_data[count]);
	    count++;
	}
	DEBUG("TEXTE : %d %s", count, new_data);
	filetype = malloc((1+count)*sizeof(char));
	if (filetype == NULL) {
	    FATAL("Erreur d'allocation mémoire : %s", strerror(errno));
	    exit(100);
	}
	strncpy(filetype, new_data, count);
	filetype[count] = '\0';

	return filetype;
    }
}

char *extract_fileencoding(char *data)
{
    char *new_data;
    char *fileencoding;

    new_data = strstr(data, "charset=") + 8;
    if (new_data == NULL) {
	INFO("Unknown encoding");
	fileencoding = malloc(8*sizeof(char));
	if (fileencoding == NULL) {
	    FATAL("Erreur d'allocation mémoire : %s", strerror(errno));
	    exit(100);
	}
	strcpy(fileencoding,"unknown");
	return fileencoding;
    } else {
	int count;
	count = 0;
	while(new_data[count] != '\r' && new_data[count] != '\n' 
		&& new_data[count] != '"') {
	    count++;
	}
	fileencoding = malloc((1+count)*sizeof(char));
	if (fileencoding == NULL) {
	    FATAL("Erreur d'allocation mémoire : %s", strerror(errno));
	    exit(100);
	}
	strncpy(fileencoding, new_data, count);
	fileencoding[count] = '\0';

	return fileencoding;
    }
}

char *url_to_filename(const char *url)
{
    char *filename;
    int i;

    filename = malloc(sizeof(char)*(strlen(url)+1));
    if (filename == NULL) {
	FATAL("Erreur d'allocation mémoire : %s", strerror(errno));
	exit(100);
    }

    i = 0;
    while (url[i] != '\0') {
	if (isalnum(url[i]) || url[i]=='.') {
	    filename[i] = url[i];
	} else {
	    filename[i] = '_';
	}
	i+=1;
    }
    filename[i] = '\0';

    return filename;
}

char *decompose_url(const char *url, short int *portnum, char **filename)
{
    char *hostname = NULL;
    regex_t preg;

    INFO("Analyse de %s", url);
    if (regcomp(&preg, "(http|ftp|https)://([^/]*).*/([^?]*).*$", REG_EXTENDED)
	    !=0){
	ERROR("Echec de l'initialisation de l'expression rationnelle");
	return NULL;
    } else {
	int match;
	size_t nmatch = 0;
	regmatch_t *pmatch = NULL;

	nmatch = preg.re_nsub + 1;
	pmatch = malloc(sizeof (*pmatch) * nmatch);
	if (pmatch == NULL) {
	    FATAL("Erreur d'allocation mémoire : %s", strerror(errno));
	    exit(100);
	} else {
	    if ((match=regexec(&preg, url, nmatch, pmatch, 0))!=0) {
		INFO("Erreur lors de l'analyse de l'URL : %d", match);
	    } else {
		/* Le champ 1 contient le protocole */
		int start = pmatch[1].rm_so;
		int end = pmatch[1].rm_eo;
		size_t size = end - start;

		if (strncmp("http", &url[start], size)==0) {
		    INFO("Protocole HTTP");
		    *portnum = 80;
		} else if (strncmp("https", &url[start], size)==0) {
		    INFO("Protocole HTTPS");
		    *portnum = 443;
		} else if (strncmp("ftp", &url[start], size)==0) {
		    INFO("Protocole FTP");
		    *portnum = 25;
		} else {
		    ERROR("Protocole inconnu : %s", &url[start]);
		    *portnum = 0;
		}

		if (*portnum != 0) {
		    INFO("Extraction de l'hôte");
		    start = pmatch[2].rm_so;
		    end = pmatch[2].rm_eo;
		    size = end - start;

		    /* Réservation de la place nécessaire */
		    hostname = malloc (sizeof (char) * (size + 1));
		    if (hostname == NULL) {
			FATAL("Erreur d'allocation mémoire : %s", 
				strerror(errno));
			exit(100);
		    } else {
			strncpy (hostname, &url[start], size);
			hostname[size] = '\0';
		    }

		    /* Extraction du nom de fichier */
		    INFO("Extraction du nom de fichier");
		    start = pmatch[3].rm_so;
		    end = pmatch[3].rm_eo;
		    size = end - start;

		    if (size == 0) {
			*filename = malloc(8*sizeof(char));
			if (filename == NULL) {
			    FATAL("Erreur d'allocation mémoire : %s", strerror(errno));
			    exit(100);
			}
			strcpy(*filename, "default");
		    } else {
			/* Réservation de la place nécessaire */
			*filename = malloc(sizeof (char) * (size + 1));
			if (*filename == NULL) {
			    FATAL("Erreur d'allocation mémoire : %s", 
				    strerror(errno));
			    exit(100);
			} else {
			    strncpy(*filename, &url[start], size);
			    (*filename)[size] = '\0';
			    INFO("Nom du fichier : %s", *filename);
			}
		    }
		}
	    }
	}

	INFO("Libération réponse au filtrage");
	free(pmatch);

	return hostname;
    }
}
