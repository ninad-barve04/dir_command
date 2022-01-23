typedef enum ENTRY_TYPE
{
    FILE_TYPE,
    DIR_TYPE
} ENTRY_TYPE;

typedef struct node{
    char* name;
    int size;
    time_t create_date;
    ENTRY_TYPE type;
    struct node *branch;
    struct node *next;
}node;

typedef node * List;

node *create_node( char * file_name);
node *create_file_node(char *file_name, int size, time_t createDate);
node *create_directory_node(char *file_name);
void append_at_next(List *list, node *addnode);
void append_at_branch(List *list, node *addnode);
void display_tree(List treelist, int *lvl);

