#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define DEBUGLEVEL
#include "log.h"

#include "stream.h"

#define BUFFERSIZE 1024

char *realloc_word(char *word, char *buffer, int size, int pos)
{
    char *temp;
    temp = realloc(word, (size+pos+1)*sizeof(char));
    if (temp == NULL) {
        FATAL("Erreur d'allocation dans realloc_word : %s", strerror(errno));
        exit(255);
    } else {
        word = temp;
        memcpy(&(word[size]), buffer, pos);
        word[size+pos] = '\0';
    }

    return word;
}

int stop_or_continue(FILE *f, int *c)
{
    *c = fgetc(f);
    switch(*c) {
        case EOF:
            return 0;
        case '-':
            {
                int temp = fgetc(f);
                if (temp=='\n' || temp=='\r') {
                    return stop_or_continue(f, c);
                } else {
                    ungetc(temp, f);
                    return 1;
                }
            }
        default:
            return 1;
    }
}

char *extract_word(FILE *f, fnc_filter filter, fnc_transform transform,
        int *offset)
{
    char *word;
    char *buffer;
    int c;
    int pos;
    int size;

    INFO("Extraction d'un mot");

    DEBUG("Position actuelle : %d", ftell(f));
    /* on saute tous les caractères qui ne nous intéressent pas */
    while((c=fgetc(f)) != EOF && !filter(c)); /*isalnum(c));*/
    DEBUG("Position en sortie : %d", ftell(f));

    /* s'il n'y a plus rien, on renvoie un mot vide */
    if (c==EOF) {
        INFO("Fin de fichier : retourne un mot vide");
        return NULL;
    }

    /* extraction du mot */
    *offset = ftell(f) - 1; /* on est allé un cran trop loin */
    DEBUG("Offset : %d", *offset);
    DEBUG("Réservation de mémoire");
    buffer = malloc((BUFFERSIZE+1)*sizeof(char));
    if (buffer == NULL) {
        FATAL("Erreur d'allocation mémoire : %s", strerror(errno));
        exit(100);
    }

    word = NULL;
    size = 0;
    pos = 0;
    do {
        buffer[pos] = transform(c); /*lower(c);*/
        pos += 1;
        if (pos == BUFFERSIZE) {
            word = realloc_word(word, buffer, size, pos);
            size += pos;
            pos = 0;
        }
    } while (stop_or_continue(f, &c) && filter(c)); /* isalnum(c)); */
    //    } while ((c=fgetc(f)) != EOF && filter(c)); /* isalnum(c)); */

if (pos != 0) {
    word = realloc_word(word, buffer, size, pos);
}

DEBUG("Libération de la mémoire");
free(buffer);

return word;
}

char *extract_zone(FILE *f, int start_offset, int end_offset)
{
    int current;
    char *zone;
    int size;

    size = end_offset - start_offset;

    zone = malloc(sizeof(char)*(size+1));
    if(zone == NULL) {
        FATAL("Erreur d'allocation mémoire : %s", strerror(errno));
        exit(100);
    }

    current = ftell(f);
    fseek(f, start_offset, SEEK_SET);

    fread(zone, sizeof(char), size, f);
    zone[size] = '\0';

    fseek(f, current, SEEK_SET);

    return zone;
}

char *extract_raw(FILE *f, int *size, 
        fnc_filter filter, fnc_transform transform)
{
    char *word;
    char *buffer;
    int c;
    int pos;

    INFO("Extraction de données brutes");

    INFO("Réservation de mémoire");
    buffer = malloc((BUFFERSIZE+1)*sizeof(char));
    if (buffer == NULL) {
        FATAL("Erreur d'allocation mémoire : %s", strerror(errno));
        exit(100);
    }

    INFO("Récupération des données");
    word = NULL;
    *size = 0;
    pos = 0;
    while ((c=fgetc(f)) != EOF) {
        if (filter(c)) {
            buffer[pos] = transform(c);
            pos += 1;
            if (pos == BUFFERSIZE) {
                word = realloc_word(word, buffer, *size, pos);
                *size += pos;
                pos = 0;
            }
        }
    };

    INFO("Récupération terminée");
    if (pos != 0) {
        word = realloc_word(word, buffer, *size, pos);
        *size += pos;
    } else {
        word = NULL;
    }

    INFO("Libération de la mémoire");
    free(buffer);

    return word;
}
