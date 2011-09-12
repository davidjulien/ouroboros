#include <stdio.h>
#include <stdlib.h>

#define NOLOG
#include "log.h"

#include "int_list.h"

t_list_int cons_list_int(int pos, t_list_int l)
{
    t_list_int nl = malloc(sizeof(*nl));
    if (nl == NULL) {
        ERROR("Erreur d'allocation mémoire : %s", strerror(errno));
        return EMPTY_IL;
    } else {
        HEAD_IL(nl) = pos;
        NEXT_IL(nl) = l;
        return nl;
    }
}

void free_list_int(t_list_int *l)
{
    while(!IS_EMPTY_IL(*l)) {
        t_list_int nl = NEXT_IL(*l);
        free(*l);
        *l = nl;
    }
}



static t_list_int reverse_aux(t_list_int l, t_list_int res)
{
    if (IS_EMPTY_IL(l)) {
        return res;
    } else {
        t_list_int temp = NEXT_IL(l);
        NEXT_IL(l) = res;
        return reverse_aux(temp, l);
    }
}

t_list_int reverse_list_int(t_list_int *l)
{
    *l = reverse_aux(*l, EMPTY_IL);
    return *l;
}

void display_list_int(t_list_int l)
{
    if (IS_EMPTY_IL(l)) {
    } else {
        printf("%d\n", HEAD_IL(l));
        display_list_int(NEXT_IL(l));
    }
}

