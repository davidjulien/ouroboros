#include <stdio.h>
#include <time.h>
#include <stdarg.h>

#include "log.h"

#define TIMESTAMP_BUFFERSIZE 200

char *get_timestamp(char *buffer)
{
    time_t t = time(NULL);
    if (strftime(buffer, TIMESTAMP_BUFFERSIZE, "%F %T", localtime(&t)) == 0) {
        fprintf(stderr,"get_timestamp : ERROR\n");
    }
    return buffer;
}

FILE *logfile = NULL;

void start_log(char *filename)
{
    /* Si le fichier est déjà ouvert, ne fait rien */
    if (logfile != NULL) {
        return ;
    } else {
        /* Ouverture du fichier en mode concaténation */
        logfile = fopen(filename,"a");
        INFO("Log start");
    }
}

void end_log()
{
    /* Si le fichier n'est pas déjà ouvert, ne fait rien */
    if (logfile == NULL) {
        return ;
    } else {
        INFO("Log end");

        fclose(logfile);
        logfile = NULL;
    }
}

void log_msg(t_log_level level, const char *filename, int line, 
        const char* format, ...)
{
    char timestamp[TIMESTAMP_BUFFERSIZE];
    va_list ap;

    /* Ouvrir le fichier de log s'il n'est pas encore ouvert */
    if (logfile == NULL) {
        start_log(LOGFILE);
    }

    /* Affiche l'heure */
    get_timestamp(timestamp);
    fprintf(logfile,"%s : %s (ligne %d) : ", timestamp, filename, line);

    /* Affichage du message formaté */
    va_start(ap, format);
    vfprintf(logfile, format, ap);
    va_end(ap);

    fprintf(logfile,"\n");

    /*fprintf(logfile, "%s : %s\n", timestamp, msg);*/
    fflush(logfile);
}
