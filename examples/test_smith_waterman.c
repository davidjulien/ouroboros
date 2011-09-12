#include <stdio.h>
#include <string.h>
#include <math.h>

#include <word_list.h>
#include <file_analysis.h>
#include <stream.h>
#include <char_filter.h>
#include <smith_waterman.h>

//#define DEBUGLEVEL
#include <log.h>

int main(int argc, char *argv[])
{
    char **doc1;
    int nbr_words1;
    int i;
    char doc2name[1000];
    char image_filepath[1000];
    unsigned char *plagiat_words;
    unsigned char *reverse_plagiat_words;

    if (argc!=2) {
	printf("%s filename1\n", argv[0]);
	return 1;
    }

    doc1 = file_to_word_array(argv[1], &nbr_words1);

    while (scanf("%s", doc2name) == 1) {
	char **doc2;
	int nbr_words2;
	int plagiat;

	printf("Document de référence : %s\n", doc2name);
	doc2 = file_to_word_array(doc2name, &nbr_words2);

	sprintf(image_filepath,"%s_%s.png", argv[1], doc2name);

	plagiat_words = NULL;
	plagiat = comparaison(doc1, nbr_words1, image_filepath, doc2, nbr_words2, 
		&plagiat_words, &reverse_plagiat_words);
	printf("Analyse terminée : %s (%d/%d = %d %%)\n", doc2name,
		plagiat, nbr_words1, (plagiat*100)/nbr_words1);
	display_plagiat_words(nbr_words1, plagiat_words);
	printf("Reverse:\n");
	display_plagiat_words(nbr_words2, reverse_plagiat_words);

	INFO("Libération de la mémoire du document de référence");
	for(i=0;i<nbr_words2;i++) {
	    free(doc2[i]);
	}
	free(doc2);
	free(plagiat_words);
	free(reverse_plagiat_words);
    }

    INFO("Libération de la mémoire du document analysé");
    for (i=0;i<nbr_words1;i++) {
	free(doc1[i]);
    }
    free(doc1);

    return 0;
}
