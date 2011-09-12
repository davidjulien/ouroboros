/*
 * Récupération d'un fichier
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <websearch.h>

int main(int argc, char *argv[])
{
    FILE *f;
    char *doc;
    //char *realdoc;
    //char *filetype;
    int size;

    if (argc != 4) {
	printf("%s serveur document fichier\n", argv[0]);
	return 0;
    }

    doc = webget(argv[1], 80, argv[2], &size);

    f = fopen(argv[3], "w");
    fwrite(doc, sizeof(unsigned char), size, f);
    fclose(f);

    free(doc);

    return 0;
}
