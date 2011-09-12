#ifndef _INT_LIST_H
#define _INT_LIST_H

typedef struct __ilist {
    int pos;
    struct __ilist *next;
} *t_list_int;

#define EMPTY_IL	(t_list_int)NULL
#define HEAD_IL(L)	((L)->pos)
#define NEXT_IL(L)	((L)->next)
#define IS_EMPTY_IL(L)	((L) == EMPTY_IL)

t_list_int cons_list_int(int pos, t_list_int l);
t_list_int reverse_list_int(t_list_int *l);
void display_list_int(t_list_int l);
void free_list_int(t_list_int *l);

#endif
