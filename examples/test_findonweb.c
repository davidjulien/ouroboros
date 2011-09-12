/*
 * Requête vers le site www.google.fr
 *
 */

#include <stdio.h>
#include <stdlib.h>

#include <websearch.h>
#include <findonweb.h>

int main(int argc, char *argv[])
{
    t_websearch google = new_websearch("www.google.com", 80, 
	    "/search?q=%s", "<a href=\"([^\"]*)\" class=l");

    t_list_single l;
    int nbr_seq;

    if (argc != 2) {
	printf("%s fichier.txt\n", argv[0]);
	return 1;
    }

    l = find_on_web(argv[1], google, 10, 5, &nbr_seq); 

    display_single_list(l);
    printf("Pour %d séquences recherchées\n", nbr_seq);

    free_single_list(&l);

    return 0;
}
