/*
 * Requête vers le site www.google.com
 *
 */

#include <stdio.h>
#include <stdlib.h>

#include <websearch.h>

int main()
{
    t_websearch google = new_websearch("www.google.com", 80, 
	    "/search?q=%s", "<a href=\"([^\"]*)\" class=l");
    const char *request = "publiée+dans+le+magazine+de+son+école+lorqu'il+avait+13+ans";
    char *results[10];
    int nbr_max = 10;
    int nbr;
    int i;

    nbr = websearch(google, request, results, nbr_max);

    printf("Nbr: %d\n", nbr);
    for(i=0;i<nbr;i++) {
	printf("Site : %s\n", results[i]);
    }

    for(i=0;i<nbr;i++) {
	free(results[i]);
    }

    return 0;
}
