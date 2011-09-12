#include <stdio.h>
#include <stdlib.h>

#include <log.h>

#include "sparse_matrix.h"

t_sm_node new_node(unsigned int pos, unsigned int value)
{
    t_sm_node node;
    node.pos = pos;
    node.value = value;
    return node;
}

void free_node(t_sm_node *node)
{
/*    free(*node);
    *node = NULL; */
}

void print_node(t_sm_node n)
{
    printf("(%u,%u)", n.pos, n.value);
}

t_sm_line cons_line(t_sm_node node, t_sm_line previous)
{
    t_sm_line nl = malloc(sizeof(*nl));
    if (nl == NULL) {
	//FATAL("Not enough memory");
	exit(1);
    } else {
	NODE_SM_LINE(nl) = node;
	NEXT_SM_LINE(nl) = previous;
	return nl;
    }
}

void free_line(t_sm_line *line)
{
    if (IS_EMPTY_SM_LINE(*line)) {
	return ;
    } else {
	t_sm_line *next = &NEXT_SM_LINE(*line);
	free_node(&NODE_SM_LINE(*line));
	free_line(next);
	free(*line);
    }
}

void display_line_aux(t_sm_line l)
{
    if (IS_EMPTY_SM_LINE(l)) {
    } else {
	print_node(NODE_SM_LINE(l));
	display_line_aux(NEXT_SM_LINE(l));
    }
}

void display_line_nl(t_sm_line l)
{
    printf("<");
    display_line_aux(l);
    printf(">\n");
}

unsigned int sm_line_get_value(t_sm_line line, int column)
{
    if (IS_EMPTY_SM_LINE(line)) {
	return 0;
    } else if (column < POS_SM_LINE(line)) {
	return 0;
    } else if (POS_SM_LINE(line) == column) {
	return VALUE_SM_LINE(line);
    } else {
	return sm_line_get_value(NEXT_SM_LINE(line), column);
    }
}

void sm_line_set_value(t_sm_line *line, int column, unsigned int value)
{
    if (IS_EMPTY_SM_LINE(*line)) {
	*line = cons_line(new_node(column, value), *line);
	return ;
    } else if (column < POS_SM_LINE(*line)) {
	*line = cons_line(new_node(column, value), *line);
	return ;
    } else if (POS_SM_LINE(*line) == column) {
	VALUE_SM_LINE(*line) = value;
	return ;
    } else {
	sm_line_set_value(&NEXT_SM_LINE(*line), column, value);
	return ;
    }
}



/*************************************/

t_sparse_matrix new_sparse_matrix(int lines)
{
    int i;
    t_sparse_matrix sm = malloc(sizeof(*sm));
    sm->nbr_lines = lines;
    sm->lines = malloc(lines*sizeof(t_sm_line));
    for (i = 0; i < lines; i++) {
	SM_LINE(sm, i) = EMPTY_SM_LINE;
    }
    return sm;

}

void free_sparse_matrix(t_sparse_matrix *sm)
{
    int i;
    for (i = 0; i < SM_NBR_LINES(*sm); i++) {
	free_line(&SM_LINE(*sm, i));
    }
    free((*sm)->lines);
    free(*sm);
    *sm = NULL;
}

unsigned int sm_get_value(t_sparse_matrix sm, int column, int line)
{
    return sm_line_get_value(sm->lines[line], column);
}

void sm_set_value(t_sparse_matrix sm, int column, int line, unsigned int value)
{
    if (value > 0) {
	return sm_line_set_value(&(sm->lines[line]), column, value);
    }
}

#if 0
int main()
{
    t_sm_line line = EMPTY_SM_LINE;
    t_sparse_matrix sm;


    display_line_nl(line);

    sm_line_set_value(&line, 5, 17);
    display_line_nl(line);

    sm_line_set_value(&line, 3, 27);
    display_line_nl(line);

    sm_line_set_value(&line, 7, 14);
    display_line_nl(line);

    sm_line_set_value(&line, 7, 27);
    display_line_nl(line);

    sm_line_set_value(&line, 3, 23);
    display_line_nl(line);

    sm_line_set_value(&line, 5, 25);
    display_line_nl(line);

    printf("%u\n", sm_line_get_value(line, 3));
    printf("%u\n", sm_line_get_value(line, 4));
    printf("%u\n", sm_line_get_value(line, 5));
    printf("%u\n", sm_line_get_value(line, 9));

    free_line(&line);


    printf("TEST SM\n");

    sm = new_sparse_matrix(20);

    printf("%u\n\n", sm_get_value(sm, 5, 10));

    sm_set_value(sm, 5, 10, 14);
    printf("%u\n", sm_get_value(sm, 5, 10));
    printf("%u\n\n", sm_get_value(sm, 5, 12));

    sm_set_value(sm, 5, 12, 15);
    sm_set_value(sm, 5, 8, 13);
    printf("%u\n", sm_get_value(sm, 5, 8));
    printf("%u\n", sm_get_value(sm, 5, 10));
    printf("%u\n", sm_get_value(sm, 5, 11));
    printf("%u\n", sm_get_value(sm, 5, 12));

    free_sparse_matrix(&sm);

    return 0;
}
#endif
