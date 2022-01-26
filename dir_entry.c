#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>

#include "linked_list.h"
#include "dir_entry.h"

void list_recursively(char *dirname, List *dirlist) {

    struct stat file_info;
    
    

    node *dirhead = *dirlist;

    DIR *dir = opendir(dirname);
    if (dir == NULL) {
        return;
    }

    

    struct dirent *entity;
    entity = readdir(dir);

    node *branchnode = NULL;

    //printf("Reading files in : %s\n", dirname);
    node *tempnode = NULL;

    while (entity != NULL) {
        if( entity->d_type == DT_REG){
            char path[100] = {0};
            strcat(path, dirname);
            strcat(path, "/");
            strcat(path, entity->d_name);
            if(stat(path, &file_info) != 0) {
                return;
            }
            //printf("Size of %s : %ld\n", path, file_info.st_size);
            //printf("%d\t%s\t%ld\n", entity->d_type, entity->d_name, file_info.st_size);
            branchnode = create_file_node(entity->d_name,file_info.st_size, file_info.st_ctim.tv_sec );
        } else {
            //printf("%d\t%s\n", entity->d_type, entity->d_name);
            if (entity->d_type == DT_DIR && strcmp(entity->d_name, ".") != 0 && strcmp(entity->d_name, "..") != 0) {

                branchnode = create_directory_node( entity->d_name);
            }
        }

        if (tempnode == NULL) {
            dirhead->branch = branchnode;
            tempnode = branchnode;
        } else {
            tempnode->next = branchnode;
            tempnode = branchnode;
        }
            

        if (entity->d_type == DT_DIR && strcmp(entity->d_name, ".") != 0 && strcmp(entity->d_name, "..") != 0) {
            if (entity->d_name[0] != '.') {
                char path[100] = {0};
                strcat(path, dirname);
                strcat(path, "/");
                strcat(path, entity->d_name);
                list_recursively(path, &branchnode);
            }
        }
        
        entity = readdir(dir);
    }
    
    closedir(dir);
    return;
}


void list_dir_content(char *dirname) {
    DIR *dir = opendir(dirname);
    if (dir == NULL) {
        return;
    }

    struct dirent *entity;
    entity = readdir(dir);

    while (entity != NULL) {
        if (strcmp(entity->d_name, "..") == 0) {
            entity = readdir(dir);
            continue;
        } else if (strcmp(entity->d_name, ".") == 0) {
            printf("%s:\n", entity->d_name);
        } else {
            printf("%s\t", entity->d_name);
        }
        
        entity = readdir(dir);
    }
    printf("\n");

    closedir(dir);
    return;
}

