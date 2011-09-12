#include <stdio.h>
#include <stdlib.h>
#include "distance.h"

#include "log.h"

/* Calcul la distance entre nbrFiles dont le chemin est contenu dans files.
 * distances sert à stocker les distances calculées. */
void multiple_distances(t_file_info files[], int nbrFiles, 
        t_comparaison distances[], fnc_distance distance)
{
    int i,j;
    int count;
    /*int total = nbrFiles*(nbrFiles-1)/2;*/

    count = 0;
    for(i=0;i<nbrFiles-1;i++) {
        for(j=i+1;j<nbrFiles;j++) {
            /*    printf("%2.d%%\r", (100*count)/total);*/
            distances[count].file1 = files[i].filepath;
            distances[count].file2 = files[j].filepath;
            distances[count].distance = distance(&(files[i]), &(files[j]));
            count += 1;
        }
    }
}

/* Comparaison de deux flottants : ne vérifie pas s'ils sont identiques */
int cmp_distance(const void *dist1, const void *dist2)
{
    t_comparaison *cmp1 = (t_comparaison*)dist1;
    t_comparaison *cmp2 = (t_comparaison*)dist2;
    if (cmp1->distance < cmp2->distance) {
        return -1;
    } else {
        return 1;
    }
}

void sort_distances(t_comparaison distances[], int nbr)
{
    qsort(distances, nbr, sizeof(t_comparaison), cmp_distance);
}

void display_distances(t_comparaison distances[], int nbr)
{
    int i;
    for(i=0;i<nbr;i++) {
        printf("%s\t%s\t : %.3f\n", distances[i].file1,
                distances[i].file2,
                distances[i].distance);
    }
}

void compute_distances(t_file_info files_info[], int nbr, fnc_distance distance)
{
    t_comparaison *distances;
    int nbr_distances;

    nbr_distances = (nbr * (nbr - 1)) / 2;

    distances = malloc(nbr_distances*sizeof(*distances));
    if (distances == NULL) {
        FATAL("Erreur d'allocation mémoire : %s",strerror(errno));
        exit(100);
    }

    multiple_distances(files_info, nbr, distances, distance);
    sort_distances(distances, nbr_distances);
    display_distances(distances, nbr_distances);

    free(distances);
}
