#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <string.h>

#include "linked_list.h"
#include "dir_entry.h"

int main(int argc, char *argv[])
{

    int option;
    int diropt_r = 0;
    int diropt_t = 0;
    int filetypeopt = 0;
    int sort_order = 0;
    SORT_OPT diropt_s = SORT_UNDEF;
    char fextension[32];
    
	while((option = getopt(argc, argv, "Rrs:tf:")) != -1){ //get option from the getopt() method
        switch(option){
            //For option i, r, l, print that these are options
            case 'R':
                
                if (diropt_t == 1) {
                    printf("Invalid option combination\n");
                    diropt_r = -1;
                    diropt_t = -1;
                } else {
                    diropt_r = 1;
                }
                break;

            case 'r':
                sort_order = 1;
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
            case 'f':
                printf("show files by extension\n");
                filetypeopt = 1;
                if( optarg){
                    sprintf(fextension, "%s", optarg);
                }
                printf("fie ext %s",fextension);
                break;
            default:
                break;
        }
    }
    

    List rootdir = create_node(".");
    list_recursively(".",&rootdir, filetypeopt , fextension);

    printf("----------------------\n");

    switch (diropt_s) {
        case SORT_NAME:
            sort_list_name(&rootdir, sort_order);
            break;
        case SORT_DATE:
            sort_list_date(&rootdir, sort_order);
            break;
        case SORT_SIZE:
            sort_list_size(&rootdir, sort_order);
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
