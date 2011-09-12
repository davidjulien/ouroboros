#include "word_list.h"

/* Génère le ou les images des rapports
 * Les intervalles sont lus sur l'entrée standard
 */
void generate_local_report(const char *filename, int size, unsigned char *line, 
        unsigned char *global_line, const char *positions, int generate_image);

int generate_text_report(const char *docname, t_list_single doc, 
        unsigned char *line, int size, const char *reportname);

int generate_final_report(const char *filename, unsigned char *global_line, int size);
int generate_image_report(int subid, int docid, 
        const char *doc_path, const char *report_path, int generate_all);
