#include <stdio.h>
#include <time.h>

#include "linked_list.h"
#include "dir_entry.h"



int main(void)
{
    /*printf("List dir content\n");
    list_dir_content("../../../test");
    printf("\n\nList recursively\n");
    list_recursively("../../../test");*/

    List rootdir = create_node("/home/ninad/test2");

    list_recursively("/home/ninad/test2", &rootdir);

    int level = -1;
    display_tree(rootdir, &level);

    return 0;
}
