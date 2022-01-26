#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <time.h>
#include "linked_list.h"

node *create_node(char *file_name) {
    //printf("Creating %s\n", file_name);
    node *newnode = (node *)malloc(sizeof(node));
    newnode->name = (char *)malloc(sizeof(char) * (strlen(file_name)+1));
    strcpy(newnode->name, file_name);
    newnode->branch = NULL;
    newnode->next = NULL;
    return newnode;
}

node *create_file_node(char *file_name, int size, time_t create_date) {
    node *file_node = create_node( file_name);
    file_node->type = FILE_TYPE;
    file_node->create_date = create_date;
    file_node->size = size;
}

node *create_directory_node(char *file_name) {
    node *file_node = create_node( file_name);
    file_node->type = DIR_TYPE;
}




void append_at_next(List *list, node *addnode) {
    node *head = *list;
    if (head == NULL) {
        head = addnode;
    } else {
        while (head->next != NULL) {
            head = head->next;
        }
        head->next = addnode;
    }
}

void append_at_branch(List *list, node *addnode) {
    node *head = *list;
    if (head == NULL) {
        head = addnode;
    } else {
        while (head->next != NULL) {
            head = head->next;
        }
        head->next = addnode;
    }
}


void print_tab( int d) {
    for( int i =0; i < d; i++){
        printf("|-- ");
    }
}


void display_tree(List treelist ,int *lvl) {
    node *head = treelist;
    node *bnode = NULL;
    if (head == NULL) {
        printf("Empty tree\n");
        return;
    }
    
    *lvl = *lvl +1;
 //   printf("%d\n", *lvl);
    print_tab( *lvl);
    printf("Name: %s\n", head->name);
   
    head = treelist;
    node *br = head->branch;   
    while( br != NULL){
        
        if( br->type == DIR_TYPE){
            display_tree(br, lvl);
            *lvl = *lvl -1;
        }
        br= br->next;
    }
    br = head->branch;
    *lvl = *lvl +1;
 //   printf("%d\n", *lvl);
    while( br != NULL){
       
        if( br->type == FILE_TYPE){
            //printf("Name: %s  %p, %p\n", br->name, br->branch, br->next);
            print_tab( *lvl);
            printf("Name: %-40s  %10d\n", br->name, br->size);
        }
        br= br->next;
    }
    

    *lvl = *lvl -1;

}


void display_recursively(List list) {
    node *head = list;
    node *bnode = NULL;
    if (head == NULL) {
        printf("Empty tree\n");
        return;
    }
    
    //printf("Name: %s\n", head->name);
   
    head = list;
    node *hptr = head->branch;
    
    printf("./%s:\n", list->name);
    while (hptr != NULL) {
        printf("%s\t", hptr->name);
        hptr = hptr->next;
    }
    printf("\n\n");
    
    
    node *br = list->branch;

    while( br != NULL){
        
        if( br->type == DIR_TYPE){
            display_recursively(br);
        }
        br= br->next;

    }
    
   


}


