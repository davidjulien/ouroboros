#include <stdlib.h>
#include <string.h>
#include <compression.h>
#include <substring_matching.h>

double distance_lancaster(t_file_info *info1, t_file_info *info2)
{
    return distance_substring_matching(info1, info2, 2, 1);
}

int main(int argc, char *argv[])
{
    t_file_info *files_info; /* Tableau contenant la liste des fichiers */
    int nbr;
    int i;

    nbr = argc - 1;
    files_info = malloc(nbr*sizeof(*files_info));
    for(i = 0;i < nbr;i++) {
	files_info[i].filepath = malloc(strlen(argv[i+1])*sizeof(char)+1);
	files_info[i].compressed_size = -1;
	strcpy(files_info[i].filepath, argv[i+1]);
    }

    compute_distances(files_info, nbr, distance_compression);
    /*compute_distances(files_info, nbr, distance_lancaster);*/

    for(i = 0;i < nbr; i++) {
	free(files_info[i].filepath);
    }
    free(files_info);

    return 0;
}
