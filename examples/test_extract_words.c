#include <stdio.h>

#include <word_list.h>
#include <file_analysis.h>

int main(int argc, char *argv[])
{
    t_list_single l1;

    if (argc!=2) {
	printf("%s filename\n", argv[0]);
	return 1;
    }

    l1 = file_to_word_list(argv[1]);

    display_single_list(l1);

    free_single_list(&l1);

    return 0;
}
