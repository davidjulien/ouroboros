#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

#include "log.h"

#include "char_filter.h"
#include "stream.h"

#include "transform.h"


#define TMPFN "/tmp/plagiat.XXXXXX"

int file_exists(const char *dest_path) {
    struct stat sb;
    if (stat(dest_path, &sb) == 0) {
        INFO("Taille du fichier : %d", sb.st_size);
        return sb.st_size > 1;
    } else {
        return 0;
    }
}

void transform_text(const char *source_path, const char *dest_path)
{
    FILE *source;
    FILE *dest;
    char *word;
    int offset;

    INFO("Début transformation TEXTE");

    INFO("Ouverture du fichier source : %s", source_path);
    source = fopen(source_path, "r");

    INFO("Ouverture du fichier destination : %s", dest_path);
    dest = fopen(dest_path, "w");

    INFO("Transformation du fichier");
    word = extract_word(source, &islatin1, &latin1_to_ascii, &offset);
    if (word != NULL) {
        fprintf(dest,"%s", word);
        free(word);

        while((word=extract_word(source, &islatin1, &latin1_to_ascii, &offset))
                != NULL){
            fprintf(dest, " %s", word);
            free(word);
        }
    }

    INFO("Fermeture des fichiers");
    fclose(source);
    fclose(dest);

    INFO("Fin transformation TEXTE");
}

#define PDFTOTEXT "pdftotext -nopgbrk -raw -q %s - | ./remove_bad_chars > %s"
#define PDFTOTEXT2 "pdftops -q %s - | pstotext | ./remove_bad_chars > %s"

void transform_pdf(const char *source_path, const char *dest_path)
{
    char *buffer;

    INFO("Début transformation PDF");

    buffer = malloc(
            (strlen(PDFTOTEXT)+strlen(source_path)+strlen(dest_path)+1)
            *sizeof(char));
    if (buffer == NULL) {
        FATAL("Erreur d'allocation mémoire : %s", strerror(errno));
        exit(100);
    }

    sprintf(buffer, PDFTOTEXT, source_path, dest_path);
    INFO("Exécution de la commande : %s", buffer);
    system(buffer);

    free(buffer);

    if (file_exists(dest_path)) {
        return ;
    } else {
        INFO("Fichier vide : deuxième tentative");
        buffer = malloc(
                (strlen(PDFTOTEXT2)+strlen(source_path)+strlen(dest_path)+1)
                *sizeof(char));
        if (buffer == NULL) {
            FATAL("Erreur d'allocation mémoire : %s", strerror(errno));
            exit(100);
        }

        sprintf(buffer, PDFTOTEXT2, source_path, dest_path);
        INFO("Exécution de la commande : %s", buffer);
        system(buffer);

        free(buffer);
    }

    INFO("Fin transformation PDF");
}

#define WORDTOTEXT "antiword -m 8859-1.txt %s > %s 2>/dev/null"
int transform_word(const char *source_path, const char *dest_path)
{
    char *buffer;
    int status;

    INFO("Début transformation WORD");

    buffer = malloc(
            (strlen(WORDTOTEXT)+strlen(source_path)+strlen(dest_path)+1)
            *sizeof(char));
    if (buffer == NULL) {
        FATAL("Erreur d'allocation mémoire : %s", strerror(errno));
        exit(100);
    }

    sprintf(buffer, WORDTOTEXT, source_path, dest_path);
    INFO("Exécution de %s", buffer);
    system(buffer);

    free(buffer);

    status = file_exists(dest_path);

    INFO("Fin transformation WORD : %d", status);
    return status;
}

#define PPTTOTEXT "catppt -d 8859-1 %s > %s"
int transform_ppt(const char *source_path, const char *dest_path)
{
    char *buffer;
    int status;

    INFO("Début transformation PPT");

    buffer = malloc(
            (strlen(PPTTOTEXT)+strlen(source_path)+strlen(dest_path)+1)
            *sizeof(char));
    if (buffer == NULL) {
        FATAL("Erreur d'allocation mémoire : %s", strerror(errno));
        exit(100);
    }

    sprintf(buffer, PPTTOTEXT, source_path, dest_path);
    INFO("Exécution de %s", buffer);
    system(buffer);

    free(buffer);

    status = file_exists(dest_path);

    INFO("Fin transformation PPT");
    return status;
}

#define XLSTOTEXT "xls2csv -d 8859-1 %s > %s"
void transform_xls(const char *source_path, const char *dest_path)
{
    char *buffer;

    INFO("Début transformation XLS");

    buffer = malloc(
            (strlen(XLSTOTEXT)+strlen(source_path)+strlen(dest_path)+1)
            *sizeof(char));
    if (buffer == NULL) {
        FATAL("Erreur d'allocation mémoire : %s", strerror(errno));
        exit(100);
    }

    sprintf(buffer, XLSTOTEXT, source_path, dest_path);
    INFO("Exécution de %s", buffer);
    system(buffer);

    free(buffer);

    INFO("Fin transformation XLS");
}


#define COPY "cp %s %s"
void copy(const char *source_path, const char *dest_path)
{
    char *buffer;

    INFO("Début transformation copy");

    buffer = malloc(
            (strlen(COPY)+strlen(source_path)+strlen(dest_path)+1)
            *sizeof(char));
    if (buffer == NULL) {
        FATAL("Erreur d'allocation mémoire : %s", strerror(errno));
        exit(100);
    }

    sprintf(buffer, COPY, source_path, dest_path);
    system(buffer);

    free(buffer);

    INFO("Fin transformation copy");
}

#define PSTOTEXT "pstotext %s > %s"
void transform_ps(const char *source_path, const char *dest_path)
{
    char *buffer;

    INFO("Début transformation PS");

    buffer = malloc(
            (strlen(PSTOTEXT)+strlen(source_path)+strlen(dest_path)+1)
            *sizeof(char));
    if (buffer == NULL) {
        FATAL("Erreur d'allocation mémoire : %s", strerror(errno));
        exit(100);
    }

    sprintf(buffer, PSTOTEXT, source_path, dest_path);
    system(buffer);

    free(buffer);

    INFO("Fin transformation PS");
}

//#define ODTTOTEXT "unzip -o %s content.xml ; html2text content.xml | iconv -c -f UTF-8 -t ISO-8859-1 > %s ; rm content.xml"
//#define ODTTOTEXT "unzip -o %s content.xml ; python html2text.py < content.xml | iconv -c -f UTF-8 -t ISO-8859-1 | ./remove_bad_chars > %s ; rm content.xml"
//#define ODTTOTEXT "unzip -o %s content.xml ; links -force-html -html-tables 0 -html-frames 0 -codepage latin1 -dump content.xml > %s ; rm content.xml"
#define ODTTOTEXT "odt2txt --encoding=latin1 --output=%s %s"
int transform_odt(const char *source_path, const char *dest_path)
{
    char *buffer;
    int status;

    INFO("Début transformation ODT");

    buffer = malloc(
            (strlen(ODTTOTEXT)+strlen(source_path)+strlen(dest_path)+1)
            *sizeof(char));
    if (buffer == NULL) {
        FATAL("Erreur d'allocation mémoire : %s", strerror(errno));
        exit(100);
    }

    sprintf(buffer, ODTTOTEXT, dest_path, source_path);
    system(buffer);

    free(buffer);

    if (file_exists(dest_path)) {
        status = 1;
    } else {
        status = 0;
    }

    INFO("Fin transformation ODT");
    return status;
}

//#define RTFTOTEXT "rtf2html %s 2>/dev/null | html2text -nobs | ./remove_bad_chars > %s"
//#define RTFTOTEXT "rtf2html %s 2>/dev/null | python html2text.py | iconv -c -f UTF-8 -t ISO-8859-1 | ./remove_bad_chars > %s"
#define RTFTOTEXT "rtf2html %s > %s 2>/dev/null ; links -force-html -html-tables 0 -html-frames 0 -codepage latin1 -dump %s > %s"
int transform_rtf(const char *source_path, const char *dest_path)
{
    char *buffer;
    int status;
    char tmpfn[sizeof(TMPFN)] = TMPFN;
    int tmpfd;

    INFO("Début transformation RTF");

    DEBUG("Création d'un fichier temporaire");
    if ((tmpfd = mkstemp(tmpfn)) == -1) {
        ERROR("Erreur de création du fichier temporaire : %s", strerror(errno));
        return 0;
    }

    buffer = malloc(
            (strlen(RTFTOTEXT)+strlen(source_path)+strlen(dest_path)+1)
            *sizeof(char));
    if (buffer == NULL) {
        FATAL("Erreur d'allocation mémoire : %s", strerror(errno));
        exit(100);
    }

    sprintf(buffer, RTFTOTEXT, source_path, tmpfn, tmpfn, dest_path);
    INFO("Exécution de %s", buffer);
    system(buffer);

    free(buffer);

    DEBUG("Libération du fichier temporaire");
    close(tmpfd);
    unlink(tmpfn);

    status = file_exists(dest_path);

    INFO("Fin transformation RTF : %d", status);
    return status;
}


/* Changement de l'encodage d'un fichier */
#if 0
#define CONVERT		"iconv -c -f %s -t %s %s > %s"
void transform_encoding(const char *source_path, const char *dest_path,
        const char *source_encoding, const char *dest_encoding)
{
    char *buffer;

    INFO("Début transformation encodage");

    buffer = malloc(
            (strlen(CONVERT)
             +strlen(source_path)
             +strlen(dest_path)
             +strlen(source_encoding)
             +strlen(dest_encoding)+1)
            *sizeof(char));

    if (strcmp(source_encoding,"unknown")==0 || strcmp(source_encoding,"")==0) {
        sprintf(buffer, CONVERT, "UTF-8", dest_encoding,
                source_path, dest_path);
    } else {
        sprintf(buffer, CONVERT, source_encoding, dest_encoding,
                source_path, dest_path);
    }
    INFO("Exécution de %s", buffer);
    system(buffer);

    free(buffer);

    INFO("Fin transformation encodage");
}
#endif
#define CONVERT		"recode %s..%s %s"
void transform_encoding(const char *path, const char *source_encoding, const char *dest_encoding)
{
    char *buffer;

    INFO("Début transformation encodage");

    buffer = malloc(
            (strlen(CONVERT)
             +strlen(path)
             +strlen(source_encoding)
             +strlen(dest_encoding)
             +1)
            *sizeof(char));

    sprintf(buffer, CONVERT, source_encoding, dest_encoding, path);
    INFO("Exécution de %s", buffer);
    system(buffer);

    free(buffer);

    INFO("Fin transformation encodage");
}

/*
 * Faire :
 * iconv -f utf-8 -t ISO-8859-1 Programmation_orientée_objet > res
 * html2text -nobs 
 */

//#define HTMLTOTEXT  "html2text -nobs %s > %s"
//#define HTMLTOTEXT  "python html2text.py %s | iconv -c -f UTF-8 -t ISO-8859-1 | ./remove_bad_chars > %s"
#define HTMLTOTEXT  "links -force-html -html-assume-codepage %s -html-tables 0 -html-frames 0 -codepage latin1 -dump %s > %s"
void transform_html(const char *source_path, const char *dest_path, 
        const char *encoding)
{
    char *buffer;

    INFO("Début transformation HTML");

    buffer = malloc(
            (strlen(HTMLTOTEXT)+strlen(source_path)+strlen(dest_path)+strlen(encoding)+1)
            *sizeof(char));
    if (buffer == NULL) {
        FATAL("Erreur d'allocation mémoire : %s", strerror(errno));
        exit(100);
    }

    sprintf(buffer, HTMLTOTEXT, encoding, source_path, dest_path);
    INFO("Exécution de %s", buffer);
    system(buffer);

    free(buffer);

    /*
       DEBUG("Création d'un fichier temporaire");
       if ((tmpfd = mkstemp(tmpfn)) == -1) {
       ERROR("Erreur de création du fichier temporaire : %s", strerror(errno));
       return ;
       }
       transform_encoding(source_path, tmpfn, encoding, "ISO-8859-1");

       buffer = malloc(
       (strlen(HTMLTOTEXT)+strlen(tmpfn)+strlen(dest_path)+1)
     *sizeof(char));

     sprintf(buffer, HTMLTOTEXT, tmpfn, dest_path);
     INFO("Exécution de %s", buffer);
     system(buffer);

     free(buffer);

     DEBUG("Libération du fichier temporaire");
     close(tmpfd);
     unlink(tmpfn);
     */

    INFO("Fin transformation HTML");
}


/*
 * Transformation d'un fichier par rapport à un format et un encodage
 * TODO : application/x-gzip
 */
int transform(const char *source_path, const char *dest_path, 
        const char *format, const char *encoding)
{
    if (strcmp(format,"text/html")==0) {
        transform_html(source_path, dest_path, encoding);
        //transform_encoding(dest_path, "latin1");
        return 1;
    } else if (strcmp(format,"text/xml")==0) {
        transform_html(source_path, dest_path, encoding);
        //transform_encoding(dest_path, "latin1");
        return 1;
    } else if (strcmp(format,"text/plain")==0) {
        copy(source_path, dest_path);
        transform_encoding(dest_path, encoding, "latin1");
        //transform_encoding(source_path, dest_path, encoding, "ISO-8859-1");
        return 1;
    } else if (strcmp(format,"text/rtf")==0) {
        transform_rtf(source_path, dest_path);
        //transform_encoding(dest_path, encoding, "latin1");
        return 1;
    } else if (strstr(format,"text/")==format) {
        copy(source_path, dest_path);
        transform_encoding(dest_path, encoding, "latin1");
        //transform_encoding(source_path, dest_path, encoding, "ISO-8859-1");
        return 1;
    } else if (strcmp(format,"application/msword")==0) {
        // pas besoin de transformer l'encoding
        /* Si la transformation word marche pas, c'est peut-être un PPT */
        if (transform_word(source_path, dest_path) == 0) {
            /* Si la transformation word et ppt marchent pas, c'est peut-être un XLS */
            if (transform_ppt(source_path, dest_path) == 0) {
                transform_xls(source_path, dest_path);
                return 1;
            } else {
                return 1;
            }
        } else {
            return 1;
        }
    } else if (strcmp(format,"application/msppt")==0) {
        // pas besoin de transformer l'encoding
        transform_ppt(source_path, dest_path);
        return 1;
    } else if (strcmp(format,"application/pdf")==0) {
        // pas besoin de transformer l'encoding
        transform_pdf(source_path, dest_path);
        return 1;
    } else if (strcmp(format,"application/postscript")==0) {
        // pas besoin de transformer l'encoding
        transform_ps(source_path, dest_path);
        return 1;
    } else if (strcmp(format,"application/x-zip")==0) {
        // pas besoin de transformer l'encoding
        return transform_odt(source_path, dest_path);
    } else {
        ERROR("Format inconnu : %s", format);
        return 0;
    }
}
