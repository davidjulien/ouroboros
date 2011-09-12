#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "log.h"

#include "stream.h"
#include "document_list.h"

/* Construction d'une liste à partir d'une séquence de mots */
t_ldoc cons_ldoc(char *words, int start_offset, int end_offset, 
        t_list_single ref, t_ldoc l, int nbr)
{
    t_ldoc nl = malloc(sizeof(*nl));

    if (nl == NULL) {
        FATAL("Erreur d'allocation mémoire : %s", strerror(errno));
        exit(100);
    } else {
        LDOC_WORDS(nl) = words;
        LDOC_NBR(nl) = nbr;
        LDOC_START(nl) = start_offset;
        LDOC_END(nl) = end_offset;
        LDOC_REF(nl) = ref;
        LDOC_NEXT(nl) = l;
        return nl;
    }
}

/* Libération de la mémoire occupée par la liste des mots */
void free_ldoc(t_ldoc *l) 
{
    if (IS_LDOC_EMPTY(*l)) {
        return ;
    } else {
        t_ldoc next = LDOC_NEXT(*l);
        free(LDOC_WORDS(*l));
        free_single_list(&LDOC_REF(*l));
        free(*l);

        *l = EMPTY_LDOC;
        free_ldoc(&next);
    }
}

/* Affichage d'une liste de séquences de mots */
void display_ldoc(t_ldoc l)
{
    if (IS_LDOC_EMPTY(l)) {
        printf("FIN\n");
    } else {
        printf("Entre %d et %d : <%s>\n", LDOC_START(l), LDOC_END(l), 
                LDOC_WORDS(l));
        display_ldoc(LDOC_NEXT(l));
    }
}

t_ldoc reverse_ldoc_aux(t_ldoc l, t_ldoc res)
{
    if (IS_LDOC_EMPTY(l)) {
        return res;
    } else {
        t_ldoc temp = LDOC_NEXT(l);
        LDOC_NEXT(l) = res;
        return reverse_ldoc_aux(temp, l);
    }
}

t_ldoc reverse_ldoc(t_ldoc *l)
{
    *l = reverse_ldoc_aux(*l, EMPTY_LDOC);
    return *l;
}


#define STRONG	1
#define WEAK	0

int remove_too_small_aux(t_ldoc l, t_ldoc block, int count, char strong,
        int minwords, int maxdist, int status, int *nbr)
{
    if (block == EMPTY_LDOC) {
        if (IS_LDOC_EMPTY(l)) {
            return status;
        } else if (IS_EMPTY_SL(LDOC_REF(l))) { /* Texte sans intérêt */
            return remove_too_small_aux(LDOC_NEXT(l), block,
                    count + LDOC_NBR(l), strong,
                    minwords, maxdist, status, nbr);
        } else if (LDOC_NBR(l) >= minwords) {
            *nbr += LDOC_NBR(l);
            DEBUG("%s is STRONG (empty)", LDOC_WORDS(l));
            return remove_too_small_aux(LDOC_NEXT(l), l, 0, STRONG,
                    minwords, maxdist, 
                    status+1, nbr);
        } else {
            *nbr += LDOC_NBR(l);
            DEBUG("%s is WEAK (empty)", LDOC_WORDS(l));
            return remove_too_small_aux(LDOC_NEXT(l), l, 0, WEAK,
                    minwords, maxdist, 
                    status+1, nbr);
        }
    } else {
        if (IS_LDOC_EMPTY(l)) {
            if (!strong) {
                DEBUG("Elimination de (%d) %s", count, LDOC_WORDS(block));
                LDOC_REF(block) = EMPTY_SL;
                *nbr -= LDOC_NBR(block);
                status -= 1;
            }
            return status; 
        } else if (IS_EMPTY_SL(LDOC_REF(l))) {
            DEBUG("ESTVIDE : %d %s", LDOC_NBR(l), LDOC_WORDS(l));
            return remove_too_small_aux(LDOC_NEXT(l), block,
                    count + LDOC_NBR(l), strong,
                    minwords, maxdist, status, nbr);
        } else if (count <= maxdist) {
            *nbr += LDOC_NBR(l);
            DEBUG("%d %s is STRONG (notempty)", count, LDOC_WORDS(l));
            return remove_too_small_aux(LDOC_NEXT(l), l, 0, STRONG,
                    minwords, maxdist, status, nbr);
        } else {
            *nbr += LDOC_NBR(l);
            if (strong == WEAK) {
                DEBUG("Elimination de (%d) %s", count, LDOC_WORDS(block));
                LDOC_REF(block) = EMPTY_SL;
                *nbr -= LDOC_NBR(block);
                status -= 1;
            }
            DEBUG("%s is WEAK/STRONG", LDOC_WORDS(l));
            return remove_too_small_aux(LDOC_NEXT(l), l, 0, 
                    LDOC_NBR(l) >= minwords ? STRONG : WEAK,
                    minwords, maxdist, status+1, nbr);
        }
    }
}


int remove_too_small(t_ldoc l, int minwords, int maxdist, int *nbr)
{
    *nbr = 0;
    return remove_too_small_aux(l, EMPTY_LDOC, 0, 0, minwords, maxdist, 0, nbr);
}

void save_ldoc_positions(t_ldoc l, FILE *f)
{
    if (IS_LDOC_EMPTY(l)) {
        return ;
    } else {
        save_ldoc_positions(LDOC_NEXT(l), f);
        if (!IS_EMPTY_SL(LDOC_REF(l))) {
            printf("%d-%d\n", LDOC_START(l), LDOC_END(l));
        }
    }
}

void generate_report_aux(t_ldoc l, FILE *f)
{
    if (IS_LDOC_EMPTY(l)) {
        return ;
    } else {
        char *ptr;

        generate_report_aux(LDOC_NEXT(l), f);

        if (!IS_EMPTY_SL(LDOC_REF(l))) {
            fprintf(f,"&nbsp;<a href=\"%s\">", HEAD_SL(LDOC_REF(l)));
        }

        ptr = LDOC_WORDS(l);
        while(*ptr != '\0') {
            if (*ptr == '\n') {
                fprintf(f,"<br/>\n");
            } else {
                fputc(*ptr, f);
            }
            ptr += 1;
        }

        if (!IS_EMPTY_SL(LDOC_REF(l))) {
            fprintf(f,"</a>&nbsp;");
        }
    }
}

void generate_report(const char *filename, t_ldoc l, const char *source)
{
    FILE *f;

    INFO("Ouverture en écriture du fichier <%s>", filename);
    f = fopen(filename, "w");

    if (f==NULL) {
        ERROR("Erreur d'ouverture");
        return ;
    } else {
        fprintf(f,"<html><head><title>%s</title></head>\n", source);
        fprintf(f,"<body>\n");
        generate_report_aux(l, f);
        fprintf(f,"\n</body>\n");
        fprintf(f,"</html>");
        fclose(f);
    }
}
