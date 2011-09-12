typedef struct {
    unsigned int pos;
    unsigned int value;
} t_sm_node;


typedef struct _line {
    t_sm_node node;
    struct _line *next;
} *t_sm_line;

#define EMPTY_SM_LINE		(t_sm_line)NULL
#define IS_EMPTY_SM_LINE(SL)	((SL) == EMPTY_SM_LINE)
#define POS_SM_LINE(SL)		((SL)->node.pos)
#define VALUE_SM_LINE(SL)	((SL)->node.value)
#define NODE_SM_LINE(SL)	((SL)->node)
#define NEXT_SM_LINE(SL)	((SL)->next)


typedef struct {
    unsigned int nbr_lines;
    t_sm_line *lines;
} *t_sparse_matrix;

#define SM_NBR_LINES(SM)	((SM)->nbr_lines)
#define SM_LINE(SM,I)		((SM)->lines[I])


t_sparse_matrix new_sparse_matrix(int lines);
void free_sparse_matrix(t_sparse_matrix *sm);
unsigned int sm_get_value(t_sparse_matrix sm, int column, int line);
void sm_set_value(t_sparse_matrix sm, int column, int line, unsigned int value);
