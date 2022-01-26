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
    //list_dir_content("/home/ninad/test2");
    int level = -1;
//    display_tree(rootdir, &level);

    printf("----------------------\n");
    display_recursively(rootdir);
    return 0;
}
