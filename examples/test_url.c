#include <stdio.h>

#include <websearch.h>

int main(int argc, char *argv[])
{
    char *host;
    short int port;
    char *filename;


    if (argc != 2) {
	printf("%s url\n", argv[0]);
	return 1;
    }

    host = decompose_url(argv[1], &port, &filename);

    printf("Host: %s\nPort : %d\nFilename: %s\n", host, port, filename);

    return 0;
}

