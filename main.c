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
   int diropt_s = 0;
   
	while((option = getopt(argc, argv, ":rs:t")) != -1){ //get option from the getopt() method
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
                diropt_s = 1;
                if(strcmp(optarg , "date") == 0) {
                    diropt_s = 11;
                    printf("show dir sorted by %s\n", optarg);
                } else if (strcmp(optarg , "size") == 0) {
                    diropt_s = 12;
                    printf("show dir sorted by %s\n", optarg);
                } else if (strcmp(optarg , "name") == 0) {
                    diropt_s = 13;
                    printf("show dir sorted by %s\n", optarg);
                } else {
                    diropt_s = -1;
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
    

    List rootdir = create_node("/home/ninad/test2");
    list_recursively("/home/ninad/test2", &rootdir);

    printf("----------------------\n");

    if (diropt_r == 1) {
        printf("show dir in recursive mode\n");
        display_recursively(rootdir);
    } else if (diropt_t == 1) {
        printf("show dir in tree mode\n");
        int level = -1;
        display_tree(rootdir, &level);
    }

    //list_dir_content("/home/ninad/test2");

    return 0;
    }
