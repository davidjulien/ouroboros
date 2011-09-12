#include <stdio.h>

#include <stream.h>
#include <char_filter.h>
#include <annotate_doc.h>

int main(int argc, char *argv[])
{
    t_ldoc l;
    int found;

    if (argc != 4) {
	printf("%s doc original reportname", argv[0]);
	return 1;
    }

    /*l = compare_document("TEXTE_CHICHI2", "TEXTE_CHICHI");*/
    l = compare_document(argv[1], argv[2], "ORIGINAL", 4, &found);

    generate_report(argv[3], l, argv[2]);
    /*
    printf("Résultat : \n");
       display_ldoc(l);*/

    printf("%d\n", found);
    free_ldoc(&l);

    return 0;
}
