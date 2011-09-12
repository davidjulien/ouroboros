#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <words_list.h>

char **build_single(char *s)
{
    char **pt = malloc(sizeof(char*));
    pt[0] = malloc(strlen(s)+1);
    strcpy(pt[0], s);
    return pt;
}

int main()
{
    t_list_words l = EMPTY_LIST;

    l = cons_new_words(1, build_single("Bonjour"), l);
    l = cons_new_words(1, build_single("Au revoir"), l);
    l = cons_new_words(1, build_single("Salut"), l);
    display_list(l);

    l = cons_new_words(1, build_single("Bonjour"), l);
    display_list(l);

    l = cons_new_words(1, build_single("Au revoir"), l);
    display_list(l);

    printf("Longueur : %d\n", length_list(l));

    free_list(&l);

    return 0;
}
