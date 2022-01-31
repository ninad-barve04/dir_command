#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <string.h>

#include "linked_list.h"
#include "dir_entry.h"

// int main(int argc, char const *argv[])
// {
//     time_t longtime = time(NULL);
//     struct tm *tmp = localtime(&longtime);
//     char date[24];
//     strftime(date, sizeof(date), "%^b %d %H:%M\n", tmp);

//     printf("%s\n", date);

//     return 0;
     
//}


int main(int argc, char *argv[])
{

    int option;
    int diropt_r = 0;
    int diropt_t = 0;
    SORT_OPT diropt_s = SORT_UNDEF;
    
	while((option = getopt(argc, argv, "rs:t")) != -1){ //get option from the getopt() method
        switch(option){
            //For option i, r, l, print that these are options
            case 'r':
                
                if (diropt_t == 1) {
                    printf("Invalid option combination\n");
                    diropt_r = -1;
                    diropt_t = -1;
                } else {
                    diropt_r = 1;
                }
                break;

            case 't':
                
                if (diropt_r == 1) {
                    printf("Invalid option combination\n");
                    diropt_t = -1;
                    diropt_r = -1;
                } else {
                    diropt_t = 1;
                    
                }
                break;

            case 's': //here f is used for some file name

                if(strcmp(optarg , "date") == 0) {
                    diropt_s = SORT_DATE;
                    printf("show dir sorted by %s\n", optarg);
                } else if (strcmp(optarg , "size") == 0) {
                    diropt_s = SORT_SIZE;
                    printf("show dir sorted by %s\n", optarg);
                } else if (strcmp(optarg , "name") == 0) {
                    diropt_s = SORT_NAME;
                    printf("show dir sorted by %s\n", optarg);
                } else {
                    printf("Invalid sort option %s\n", optarg);
                }
                break;

            case ':':
                printf("sort option 's' needs value ( size/date/name )");
                break;

            case '?': //used for some unknown options
                printf("unknown option: %c\n", optopt);
                break;
        }
    }
    

    List rootdir = create_node(".");
    list_recursively(".", &rootdir);

    printf("----------------------\n");

    switch (diropt_s) {
        case SORT_NAME:
            sort_list_name(&rootdir);
            break;
        case SORT_DATE:
            sort_list_date(&rootdir);
            break;
        case SORT_SIZE:
            sort_list_size(&rootdir);
            break;
        
        default:
            break;
    }

    if (diropt_r == 1) {
        printf("show dir in recursive mode\n");
        display_recursively(rootdir);
    } else if (diropt_t == 1) {
        printf("show dir in tree mode\n");
        int level = -1;
        display_tree(rootdir, &level);
    } else {
        display_default(rootdir);
    }


    
    return 0;
}
