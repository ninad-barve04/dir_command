typedef enum SORT_OPT {
    SORT_UNDEF,
    SORT_NAME,
    SORT_DATE,
    SORT_SIZE
} SORT_OPT;


void list_recursively(char *dirname, List *dirlist);
