#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>

#include "linked_list.h"
#include "dir_entry.h"

void list_recursively(char *dirname, List *dirlist, int filetypeopt, char *filetype) {

    struct stat file_info;
    
    node *dirhead = *dirlist;

    DIR *dir = opendir(dirname);
    if (dir == NULL) {
        return;
    }

    struct dirent *entity;
    entity = readdir(dir);

    node *branchnode = NULL;

    
    node *tempnode = NULL;

    while (entity != NULL ) {
	
        if( entity->d_type == DT_REG){
            char path[1024] = {0};
            strcat(path, dirname);
            strcat(path, "/");
            strcat(path, entity->d_name);
            if(stat(path, &file_info) != 0) {
                return;
            }

            int exetype = 0;
            if( file_info.st_mode & S_IXUSR){
                exetype = 1;
            }
            int addfile = (filetypeopt == 0) ? 1 : 0;
            if( filetypeopt == 1){
                char *dot = strrchr(entity->d_name, '.');

                if (dot && 0 == strcmp(dot+1,filetype))
                {
                    addfile = 1; 
                }
            }
            if( addfile == 1){
                branchnode = create_file_node(entity->d_name,file_info.st_size, file_info.st_ctim.tv_sec , exetype);
                if (tempnode == NULL) {
                    dirhead->branch = branchnode;
                    tempnode = branchnode;
                } else {
                    tempnode->next = branchnode;
                    tempnode = branchnode;
                }
            }
        } else {
            
            if (entity->d_type == DT_DIR && strcmp(entity->d_name, ".") != 0 && strcmp(entity->d_name, "..") != 0) {

                branchnode = create_directory_node( entity->d_name);

                if (tempnode == NULL) {
                    dirhead->branch = branchnode;
                    tempnode = branchnode;
                } else {
                    tempnode->next = branchnode;
                    tempnode = branchnode;
                }
            }
        
            
        }
        

        if (entity->d_type == DT_DIR && strcmp(entity->d_name, ".") != 0 && strcmp(entity->d_name, "..") != 0) {
            if (entity->d_name[0] != '.') {
                char path[100] = {0};
                strcat(path, dirname);
                strcat(path, "/");
                strcat(path, entity->d_name);
                list_recursively(path, &branchnode,filetypeopt,filetype);
            }
        }
        entity = readdir(dir);
    }
    
    closedir(dir);
    return;
}

