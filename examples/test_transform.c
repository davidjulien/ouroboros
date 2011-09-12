#include <stdio.h>
#include <string.h>

#include <transform.h>

int main(int argc, char *argv[])
{
    if (argc != 5) {
	printf("%s source dest.txt type encoding\n", argv[0]);
	return 1;
    }

    transform(argv[1], argv[2], argv[3], argv[4]);

    return 0;
}
