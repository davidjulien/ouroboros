#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <magic.h>

#define DEBUGLEVEL
#include "log.h"
#include "stream.h"
#include "char_filter.h"
#include "file_analysis.h"

/* Extrait d'un fichier une liste de séquences */
t_list_words analyse_file(const char *filepath, int nbr_words, int skip_words,
        t_list_single *allwords, char sorted)
{
    FILE *f;
    t_list_words l;
    char **buffer_words;
    int posbuff;
    int i;
    int count;
    int offset;

    INFO("Analyse du fichier <%s> longueur séquence = %d, décalage = %d", 
            filepath, nbr_words, skip_words);

    /* Ouverture du fichier */
    INFO("Ouverture du fichier %s", filepath);
    f = fopen(filepath, "r");
    if (f==NULL) {
        ERROR("Erreur d'ouverture du fichier %s : %s", filepath, 
                strerror(errno));
        return EMPTY_LIST;
    }

    /* Initialisation d'un buffer contenant les N derniers mots */
    DEBUG("Initialisation d'un buffer pour %d mots", nbr_words);
    buffer_words = malloc(nbr_words*sizeof(char*));
    if (buffer_words == NULL) {
        ERROR("Erreur d'allocation mémoire : %s", strerror(errno));
        exit(100);
    }
    posbuff = nbr_words - 1;

    INFO("Construction de la liste de mots");
    l = EMPTY_LIST;
    *allwords = EMPTY_SL;

    INFO("Amorçage");
    for(i=0;i<nbr_words-1;i++) {
        buffer_words[i] = extract_word(f, &islatin1, &latin1_to_ascii, &offset);
        *allwords = cons_single(buffer_words[i], *allwords);
    }

    INFO("Itération");
    count = 0;
    while((buffer_words[posbuff] = extract_word(f, &islatin1, &latin1_to_ascii,
                    &offset))) {
        *allwords = cons_single(buffer_words[posbuff], *allwords);

        if (count == 0) {
            char **words = malloc(nbr_words*sizeof(char *));
            if (words == NULL) {
                FATAL("Erreur d'allocation mémoire : %s",strerror(errno));
                exit(100);
            }

            for(i = 0; i < nbr_words; i++) {
                words[i] = buffer_words[(posbuff+1+i)%nbr_words];
            }

            if (sorted) {
                add_sorted(build_words(nbr_words, words), &l);
            } else {
                l = cons_new_words(nbr_words, words, l);
            }

            count = skip_words;
        }

        posbuff = (posbuff+1)%nbr_words;
        count -= 1;
    }
    INFO("Fin de la construction de la liste de mots");

    /* Libération de la mémoire */
    DEBUG("Libération du buffer de mots");
    free(buffer_words);

    /* Fermeture du fichier */
    INFO("Fermeture du fichier %s", filepath);
    fclose(f);

    DEBUG("Nombre de séquences : %d", length_list(l));

    return l;
}

/* Extrait d'un fichier une liste de séquences */
t_list_single file_to_word_list(const char *filepath)
{
    FILE *f;
    t_list_single l;
    char *word;
    int offset;

    INFO("Ouverture du fichier %s", filepath);
    f = fopen(filepath, "r");
    if (f==NULL) {
        ERROR("Erreur d'ouverture du fichier %s : %s", filepath, 
                strerror(errno));
        return EMPTY_SL;
    }

    INFO("Construction de la liste de mots");
    l = EMPTY_SL;

    INFO("Itération");
    while((word = extract_word(f, &islatin1, &latin1_to_ascii, &offset))) {
        l = cons_single(word, l);
        COUNT_SL(l) = offset;
    }
    INFO("Fin de la construction de la liste de mots");

    /* Fermeture du fichier */
    INFO("Fermeture du fichier %s", filepath);
    fclose(f);

    INFO("Inversion de la liste");
    return reverse(&l);
}

/* Extrait d'un fichier une liste de séquences */
char **file_to_word_array(const char *filepath, int *nbr)
{
    FILE *f;
    t_list_single l;
    char **array;
    int offset;
    int current_size;

    INFO("Ouverture du fichier %s", filepath);
    f = fopen(filepath, "r");
    if (f==NULL) {
        ERROR("Erreur d'ouverture du fichier %s : %s", filepath, 
                strerror(errno));
        *nbr = 0;
        return NULL;
    }

    INFO("Construction de la liste de mots");
    l = EMPTY_SL;

    INFO("Itération");
    *nbr = 0;
    current_size = 256;
    array = malloc(current_size*sizeof(*array));
    while((array[*nbr] = extract_word(f, &islatin1, &latin1_to_ascii, &offset))) {
        (*nbr)++;
        if (*nbr == current_size) {
            current_size = 2*current_size;
            INFO("Réallocation %d", current_size);
            array = realloc(array, current_size*sizeof(*array));
            if (array == NULL) {
                return NULL;
            }
        }
    }
    INFO("Fin de la construction de la liste de mots");

    /* Fermeture du fichier */
    INFO("Fermeture du fichier %s", filepath);
    fclose(f);

    array = realloc(array, (*nbr)*sizeof(*array));
    return array;
}


#define FILETYPE "file -b -i '%s' > %s"
#define TMPFN "/tmp/plagiat.XXXXXX"
char *file_type(const char *filepath, char **encoding)
{
    magic_t ms = magic_open(MAGIC_ERROR|MAGIC_MIME);
    const char *result;
    *encoding = NULL;

    if (magic_load(ms,NULL) < 0 ||
            (result = magic_file(ms, filepath)) == NULL) {
        int error = magic_errno(ms);
        if (error == 0) {
            ERROR("%s:%s", filepath, magic_error(ms));
        } else {
            ERROR("%s:%s", filepath, strerror(error));
        }
        return NULL;
    } else {
        char fileinfo[1000];
        char *filetype;

        INFO("Récupération du type");
        if (sscanf(result, "%[^;\n]", fileinfo)==1) {
            filetype = malloc(sizeof(char)*(strlen(fileinfo)+1));
            if (filetype == NULL) {
                FATAL("Erreur d'allocation mémoire : %s", strerror(errno));
                exit(100);
            }
            strcpy(filetype, fileinfo);
        } else {
            INFO("Pas de type, html par défaut");
            filetype = malloc(sizeof(char)*(strlen("text/html")+1));
            if (filetype == NULL) {
                FATAL("Erreur d'allocation mémoire : %s", strerror(errno));
                exit(100);
            }
            strcpy(filetype,"text/html");
        }
        INFO("Type : <%s>", filetype);

        INFO("Récupération de l'encodage");
        if (sscanf(result+strlen(filetype), "; charset=%s", fileinfo)==1) {
            *encoding = malloc(sizeof(char)*(strlen(fileinfo)+1));
            if (*encoding == NULL) {
                FATAL("Erreur d'allocation mémoire : %s", strerror(errno));
                exit(100);
            }
            strcpy(*encoding, fileinfo);
        } else {
            *encoding = malloc(sizeof(char));
            if (*encoding == NULL) {
                FATAL("Erreur d'allocation mémoire : %s", strerror(errno));
                exit(100);
            }
            (*encoding)[0] = '\0';
        }
        INFO("Encodage : <%s>", *encoding);

        magic_close(ms);

        return filetype;
    }
#if 0
    char *buffer;
    char *filetype;
    char tmpfn[strlen(TMPFN)+1] = TMPFN;
    char fileinfo[100];
    int tmpfd;
    FILE *f;

    INFO("Détermination du type du fichier %s", filepath);

    DEBUG("Création d'un fichier temporaire");
    if ((tmpfd = mkstemp(tmpfn)) == -1) {
        ERROR("Erreur de création du fichier temporaire : %s", strerror(errno));
        return NULL;
    }
    f = fdopen(tmpfd,"r");

    DEBUG("Allocation de la mémoire");
    buffer = malloc((strlen(FILETYPE)
                +strlen(filepath)
                +strlen(tmpfn)+1)
            *sizeof(char));
    if (buffer == NULL) {
        FATAL("Erreur d'allocation mémoire : %s", strerror(errno));
        exit(100);
    }
    sprintf(buffer, FILETYPE, filepath, tmpfn);
    INFO("Exécution de la commande : %s", buffer);
    system(buffer);

    INFO("Récupération du type");
    if (fscanf(f, "%[^;\n]", fileinfo)==1) {
        filetype = malloc(sizeof(char)*(strlen(fileinfo)+1));
        if (filetype == NULL) {
            FATAL("Erreur d'allocation mémoire : %s", strerror(errno));
            exit(100);
        }
        strcpy(filetype, fileinfo);
    } else {
        INFO("Pas de type, html par défaut");
        filetype = malloc(sizeof(char)*(strlen("text/html")+1));
        if (filetype == NULL) {
            FATAL("Erreur d'allocation mémoire : %s", strerror(errno));
            exit(100);
        }
        strcpy(filetype,"text/html");
    }
    INFO("Type : <%s>", filetype);

    INFO("Récupération de l'encodage");
    if (fscanf(f, "; charset=%s", fileinfo)==1) {
        *encoding = malloc(sizeof(char)*(strlen(fileinfo)+1));
        if (*encoding == NULL) {
            FATAL("Erreur d'allocation mémoire : %s", strerror(errno));
            exit(100);
        }
        strcpy(*encoding, fileinfo);
    } else {
        *encoding = malloc(sizeof(char));
        if (*encoding == NULL) {
            FATAL("Erreur d'allocation mémoire : %s", strerror(errno));
            exit(100);
        }
        (*encoding)[0] = '\0';
    }
    INFO("Encodage : <%s>", *encoding);

    DEBUG("Libération de la mémoire");
    free(buffer);

    DEBUG("Libération du fichier temporaire");
    close(tmpfd);
    unlink(tmpfn);

    return filetype;
#endif
}


t_list_int build_map_aux(FILE *fdoc, int fpos, t_list_single doc, int current_word, 
        int current_line, int current_column, int max_column, t_list_int map)
{
    if (IS_EMPTY_SL(doc)) {
        return map;
    } else {
        int offset = COUNT_SL(doc);
        DEBUG("Current : %d Offset : %d", fpos, offset);
        while (fpos < offset) {
            char c;
            fread(&c, 1, 1, fdoc);
            if (c == '\n') {
                current_line++;
                current_column = 0;
                DEBUG("last word : %d (%s) real newline %d",  current_word, HEAD_SL(doc), current_line);
                map = cons_list_int(current_word, map);
            } else {
                current_column++;
                if (current_column == max_column) {
                    current_line++;
                    current_column = 0;
                    DEBUG("last word : %d (%s) simu newline %d",  current_word, HEAD_SL(doc), current_line);
                    map = cons_list_int(current_word, map);
                }
            }
            fpos++;
        }

        DEBUG("start = %d, end = %d", fpos, offset);
        if (current_column+strlen(HEAD_SL(doc)) >= max_column) {
            current_line++;
            current_column = 0;
            DEBUG("last word : %d (%s) simu newline %d",  current_word, HEAD_SL(doc), current_line);
            map = cons_list_int(current_word, map);
        }
        int final_pos = offset+strlen(HEAD_SL(doc));
        while (fpos < final_pos) {
            char c;
            fread(&c, 1, 1, fdoc);
            if (c == '\n') {
                DEBUG("New line inside word ???");
                current_line++;
                current_column = 0;
                DEBUG("last word : %d (%s) inside newline %d",  current_word, HEAD_SL(doc), current_line);
                map = cons_list_int(current_word, map);
            } else {
                current_column++;
            }
            fpos++;
        }

        return build_map_aux(fdoc, fpos, NEXT_SL(doc),
                current_word+1, current_line, current_column, max_column, map);
    }
}

t_list_int build_map(const char *docname, t_list_single doc, int max_column)
{
    FILE *fdoc;
    t_list_int map;

    INFO("START");

    INFO("Open file <%s>", docname);
    fdoc = fopen(docname, "r");
    if (fdoc == NULL) {
        ERROR("Can't open document <%s>", docname);
        return 0;
    }

    map = build_map_aux(fdoc, 0, doc, 0, 0, 0, max_column, EMPTY_IL);
    reverse_list_int(&map);

    INFO("Close file doc");
    fclose(fdoc);

    INFO("END");
    return map;
}
