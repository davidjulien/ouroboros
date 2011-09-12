#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <document_list.h>

char *build_word(char *w)
{
    char *p = malloc((1+strlen(w))*sizeof(char));
    strcpy(p, w);
    return p;
}



int main()
{
    t_ldoc l;

    l = cons_ldoc(build_word("Bonjour"), 0, 10, EMPTY_SL,
		cons_ldoc(build_word("David"), 12, 20, EMPTY_SL, EMPTY_LDOC, 1),
	       	1);
    display_ldoc(l);
    free_ldoc(&l);

    return 0;
}
