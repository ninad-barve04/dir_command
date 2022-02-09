#define ANSI_COLOR_DIR    "\x1b[34m"
#define ANSI_COLOR_EXE    "\x1b[32m"
#define ANSI_COLOR_RESET   "\x1b[0m"

typedef enum ENTRY_TYPE
{
    FILE_TYPE,
    EXE_TYPE,
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
node *create_file_node(char *file_name, int size, time_t createDate, int exetype);
node *create_directory_node(char *file_name);
void append_at_next(List *list, node *addnode);
void append_at_branch(List *list, node *addnode);
void display_tree(List treelist, int *lvl);
void display_recursively(List treelist);
void display_default(List list);
void swap_data(node **n1, node **n2);
void sort_list_name(List *list, int sortorder);
void sort_list_size(List *list, int sortorder);
void sort_list_date(List *list, int sortorder);



