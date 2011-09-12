#include <stdio.h>

#include <word_list.h>
#include <file_analysis.h>

int main(int argc, char *argv[])
{
    t_list_single l1, l2;
    int count;

    if (argc!=3) {
	printf("%s filename filename\n", argv[0]);
	return 1;
    }

    l1 = file_to_word_list(argv[1]);
    l2 = file_to_word_list(argv[2]);

    /*
    display_single_list(l1);
    display_single_list(l2);
    */

    count = longuest_sublist(l1, l2);

    printf("Count : %d\n", count);

    free_single_list(&l1);
    free_single_list(&l2);

    return 0;
}
