/*
 * Calcul de la distance entre deux fichiers par compression 
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>

#include "log.h"

#include "compression.h"

/* Retourne la taille du fichier dont le chemin est passé en paramètre */
int filesize(const char *path)
{
    struct stat info;
    if(stat(path,&info)==-1) {
        perror("filesize");
        return 0;
    } else {
        return info.st_size;
    }
}

/* On compresse le fichier path_src vers path_dst. Le chemin path_dst est
 * retourné */
char *compression(const char *path_src, char *path_dst)
{
    char *buffer;

    buffer = malloc(strlen(path_src)+strlen(path_dst)+30);
    if (buffer == NULL) {
        FATAL("Erreur d'allocation mémoire : %s",strerror(errno));
        exit(100);
    }

    sprintf(buffer,"gzip < '%s' > '%s'", path_src, path_dst);
    system(buffer);

    free(buffer);

    return path_dst;
}

/* Concatène les fichiers file1 et file2 dans le fichier dest */
char *concat(const char *file1, const char *file2, char *dest)
{
    char *buffer;

    buffer = malloc(strlen(file1)+strlen(file2)+strlen(dest)+30);
    if (buffer == NULL) {
        FATAL("Erreur d'allocation mémoire");
        exit(100);
    }

    sprintf(buffer,"cat '%s' '%s' > '%s'", file1, file2, dest);
    system(buffer);

    free(buffer);

    return dest;
}

double min(double v1, double v2)
{
    return v1 < v2 ? v1 : v2;
}

/* Retourne la taille du fichier une fois compressé */
int compression_size(t_file_info *file_info)
{
    if (file_info->compressed_size != -1) {
        return file_info->compressed_size;
    } else {
        char *cmp_filepath;
        int size;

        cmp_filepath = malloc(strlen(file_info->filepath)*sizeof(char)+3);
        if (cmp_filepath == NULL) {
            FATAL("Erreur d'allocation mémoire : %s", strerror(errno));
            exit(100);
        }

        sprintf(cmp_filepath,"%s.gz",file_info->filepath);
        size = filesize(compression(file_info->filepath, cmp_filepath));
        file_info->compressed_size = size;

        remove(cmp_filepath);
        free(cmp_filepath);

        return size;
    }
}


/* Calcul la distance entre deux fichiers */
double distance_compression(t_file_info *file1, t_file_info *file2)
{
    int size1;
    int size2;

    char *concat_filepath;
    char *cmp_concat_filepath;
    int size3;

    /* Taille du premier fichier compressé */
    size1 = compression_size(file1);

    /* Taille du deuxième fichier compressé */
    size2 = compression_size(file2);

    /* Taille des deux fichiers compressés */
    concat_filepath = malloc(strlen(file1->filepath)+1+strlen(file2->filepath));
    if (concat_filepath == NULL) {
	FATAL("Erreur d'allocation mémoire : %s",strerror(errno));
	exit(100);
    }
    sprintf(concat_filepath,"%s-%s", file1->filepath, file2->filepath);
    cmp_concat_filepath = malloc(strlen(concat_filepath)+3);
    if (cmp_concat_filepath == NULL) {
	FATAL("Erreur d'allocation mémoire : %s",strerror(errno));
	exit(100);
    }
    sprintf(cmp_concat_filepath,"%s.gz", concat_filepath);

    /* On teste les deux ordres de concaténation et on prend la plus petite des
     * distances */
    size3 = min(
	    filesize(compression(
		    concat(file1->filepath, file2->filepath, concat_filepath), 
		    cmp_concat_filepath)),
	    filesize(compression(
		    concat(file2->filepath, file1->filepath, concat_filepath), 
		    cmp_concat_filepath)));

    /* Suppression des fichiers */
    remove(cmp_concat_filepath);
    remove(concat_filepath);

    /* Libération de la mémoire */
    free(cmp_concat_filepath);
    free(concat_filepath);

    /* Calcul de la distance */
    if (size1 < size2) {
	return 1.0 - ((double)(size1+size2-size3)) / (double)size1;
    } else {
	return 1.0 - ((double)(size1+size2-size3)) / (double)size2;
    }
}
