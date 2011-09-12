#ifndef __COMMON_H
#define __COMMON_H

typedef struct {
    char *file1;
    char *file2;
    double distance;
} t_comparaison;

typedef struct {
    char *filepath;
    int compressed_size;
} t_file_info;

typedef double fnc_distance(t_file_info *, t_file_info*);

void compute_distances(t_file_info files_info[], int nbr, fnc_distance dist);

#endif
