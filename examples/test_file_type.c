#include <stdio.h>

#include <word_list.h>
#include <file_analysis.h>

int main(int argc, char *argv[])
{
    char *filetype;
    char *encoding;

    if (argc!=2) {
	printf("%s filename\n", argv[0]);
	return 1;
    }

    filetype = file_type(argv[1], &encoding);
    printf("Type de    %s : %s\n", argv[1], filetype);
    printf("Charset de %s : %s\n", argv[1], encoding);

    free(filetype);
    free(encoding);

    return 0;
}
