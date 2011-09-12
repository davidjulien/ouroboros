#include <stdio.h>

#include <plagiat.h>

#define SEARCHWORDS	10
#define SEARCHSKIP	5
#define THRESHOLD	3

#define MINWORDS 	6
#define MAXGAP		2

int main(int argc, char *argv[])
{
    t_websearch google = new_websearch("www.google.com", 80, 
	    "/search?q=%s", "<a href=\"([^\"]*)\" class=l");

    if (argc != 2) {
	printf("%s doc", argv[0]);
	return 1;
    }

    detect_plagiat(argv[1], google, SEARCHWORDS, SEARCHSKIP, 
	    THRESHOLD, MINWORDS, MAXGAP);

    return 0;
}
