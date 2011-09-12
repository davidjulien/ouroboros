#include <stdio.h>
#include <string.h>
#include <log.h>
#include <word_list.h>
#include <substring_matching.h>

char *build_word(char *w)
{
    char *p = malloc((1+strlen(w))*sizeof(char));
    strcpy(p, w);
    return p;
}

int main()
{
    t_list_single l = EMPTY_SL;
    t_list_single l1 = EMPTY_SL;
    t_list_single l2 = EMPTY_SL;

    INFO("DEBUT");
    add_single_sorted(build_word("encore"), 0, &l);
    add_single_sorted(build_word("des"), 0, &l);
    add_single_sorted(build_word("mauvais"), 0, &l);
    add_single_sorted("des", 0, &l);
    add_single_sorted("des", 0, &l);
    add_single_sorted("des", 0, &l);
    add_single_sorted("mauvais", 0, &l);
    add_single_sorted("mauvais", 0, &l);
    add_single_sorted("encore", 0, &l);
    add_single_sorted(build_word("plagiats"), 0, &l);

    INFO("display");
    display_single_list(l);

    INFO("divide");
    divide_single_list(&l, &l1, &l2);

    INFO("display list");
    printf("Liste\n");
    display_single_list(l);
    INFO("display list1");
    printf("Liste 1\n");
    display_single_list(l1);
    INFO("display list2");
    printf("Liste 2\n");
    display_single_list(l2);

    INFO("merge");
    printf("Merge\n");
    l = merge(l1,l2);
    display_single_list(l); 

    INFO("sort");
    printf("sort\n");
    sort_single_list_by_count(&l);
    display_single_list(l);

    INFO("reverse");
    reverse(&l);
    display_single_list(l);

    INFO("free list");
    free_single_list(&l);
    return 0;
}
