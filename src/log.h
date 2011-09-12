#include <string.h>
#include <errno.h>

void start_log(char *filename);
void end_log();

/* Définition par défaut d'un fichier de log */
#ifndef LOGFILE
#define LOGFILE "log"
#endif

typedef enum { TDEBUG, TINFO, TWARNING, TERROR, TFATAL } t_log_level;

/* Ajoute un message dans les logs */
void log_msg(t_log_level level, const char *file, int line, 
        const char *format, ...);

/* 
 * En fonction du niveau de log désiré, on ne va activer que certaines fonctions
 */ 
#ifdef NOLOG

#define DEBUG(...)
#define INFO(...)
#define WARNING(...)
#define ERROR(...)
#define FATAL(...)

#else

#ifdef DEBUGLEVEL
#define DEBUG(...)	log_msg(TDEBUG, __FILE__, __LINE__, __VA_ARGS__)
#define INFO(...)	log_msg(TINFO,__FILE__, __LINE__, __VA_ARGS__)
#define WARNING(...)	log_msg(TWARNING,__FILE__, __LINE__, __VA_ARGS__)
#define ERROR(...)	log_msg(TERROR,__FILE__, __LINE__, __VA_ARGS__)
#define FATAL(...)	log_msg(TFATAL,__FILE__, __LINE__, __VA_ARGS__)

#else

#define DEBUG(...)
#define INFO(...)	log_msg(TINFO,__FILE__, __LINE__, __VA_ARGS__)
#define WARNING(...)	log_msg(TWARNING,__FILE__, __LINE__, __VA_ARGS__)
#define ERROR(...)	log_msg(TERROR,__FILE__, __LINE__, __VA_ARGS__)
#define FATAL(...)	log_msg(TFATAL,__FILE__, __LINE__, __VA_ARGS__)

#endif

#endif
