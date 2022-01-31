#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <time.h>
#include "linked_list.h"

node *create_node(char *file_name) {
    node *newnode = (node *)malloc(sizeof(node));
    newnode->name = (char *)malloc(sizeof(char) * (strlen(file_name)+1));
    strcpy(newnode->name, file_name);
    newnode->branch = NULL;
    newnode->next = NULL;
    return newnode;
}

node *create_file_node(char *file_name, int size, time_t create_date, int exetype) {
    node *file_node = create_node( file_name);
    if( exetype == 1){
        file_node->type = EXE_TYPE;
    }else{
        file_node->type = FILE_TYPE;
    }
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
    return;
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
    return;
}


char *get_file_time(time_t longtime) {
    
    struct tm *tmp = localtime(&longtime);
    char *date = (char*) malloc(sizeof(char)*32);
    strftime(date, 13, "%^b %d %H:%M", tmp);
     
    return date;
}


void print_tab( int d) {
    for( int i =0; i < d; i++){
        printf("|- ");
    }
    return;
}


void display_tree(List treelist ,int *lvl) {
    node *head = treelist;
    node *bnode = NULL;
    if (head == NULL) {
        printf("Empty tree\n");
        return;
    }
    
    *lvl = *lvl +1;
    print_tab( *lvl);
    printf("%s%s%s  \n",ANSI_COLOR_DIR ,head->name,ANSI_COLOR_RESET);
   
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
    while( br != NULL){
       
        if( br->type == FILE_TYPE || br->type == EXE_TYPE){
            print_tab( *lvl);
            char *timestr = get_file_time(br->create_date);
	        int padd = 40 - 3*(*lvl);
            if( br->type == EXE_TYPE){
                printf("%s%-*s%s  %s %10d\n",ANSI_COLOR_EXE ,padd, br->name, ANSI_COLOR_RESET,timestr, br->size);
            }else{
                printf("%-*s  %s %10d\n",padd, br->name,timestr, br->size);
            }

            free(timestr);
            timestr = NULL;
        }
        br= br->next;
    }
    

    *lvl = *lvl -1;

    return;
}


void display_recursively(List list) {
    node *head = list;
    
    if (head == NULL) {
        printf("Empty tree\n");
        return;
    }
    
   
    head = list;
    node *hptr = head->branch;
    
    printf(". %s:\n", list->name);
    while (hptr != NULL) {
        if (hptr->type == DIR_TYPE) {
            printf("%s%s%s\t", ANSI_COLOR_DIR, hptr->name, ANSI_COLOR_RESET);
        } else if (hptr->type == EXE_TYPE) {
            printf("%s%s%s\t", ANSI_COLOR_EXE, hptr->name, ANSI_COLOR_RESET);
        } else {
            printf("%s\t", hptr->name);
        }

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
    return;
}


void display_default(List list) {
    node *head = list;
    
    if (head == NULL) {
        printf("Empty tree\n");
        return;
    }
    
   
    head = list;
    node *hptr = head->branch;
    while (hptr != NULL) {
        if (hptr->type == DIR_TYPE) {
            printf("%s%s%s\t", ANSI_COLOR_DIR, hptr->name, ANSI_COLOR_RESET);
        } else if (hptr->type == EXE_TYPE) {
            printf("%s%s%s\t", ANSI_COLOR_EXE, hptr->name, ANSI_COLOR_RESET);
        } else {
            printf("%s\t", hptr->name);
        }
        hptr = hptr->next;
    }
    printf("\n");
    return;
    
}


void print_node(node *n) {
    printf("Node name : %s\n", n->name);
    return;
}

void swap_data(node **n1, node **n2) {

    char *tempname = (*n1)->name;
    (*n1)->name = (*n2)->name;
    (*n2)->name = tempname;

    time_t tempdate = (*n1)->create_date;
    (*n1)->create_date = (*n2)->create_date;
    (*n2)->create_date = tempdate;

    int tempsize = (*n1)->size;
    (*n1)->size = (*n2)->size;
    (*n2)->size = tempsize;

    ENTRY_TYPE temptype = (*n1)->type;
    (*n1)->type = (*n2)->type;
    (*n2)->type = temptype;

    node *tempbranch = (*n1)->branch;
    (*n1)->branch = (*n2)->branch;
    (*n2)->branch = tempbranch;

    return;
}


void sort_list_name(List *list, int sortorder) {
    int i = 0;
    node *num = (*list)->branch;

    while (num != NULL) {
        char *minstr = num->name;
        node *temp = num->next;

        while (temp != NULL) {
            
            if (sortorder == 1) {
                if (strcmp(temp->name, minstr) >= 0) {
                    minstr = temp->name;
                    swap_data(&num, &temp);
                }
            } else {
                if (strcmp(temp->name, minstr) < 0) {
                    minstr = temp->name;
                    swap_data(&num, &temp);
                }
            }
            
            temp = temp->next;
            i = i + 1;
        }
        sort_list_name(&num, sortorder);
        num = num->next;
    }

    return;
}


void sort_list_size(List *list, int sortorder) {
    
    node *num = (*list)->branch;

    while (num != NULL) {
        int minsize = num->size;
        node *temp = num->next;

        while (temp != NULL) {
            if (sortorder == 1) {
                if ((temp->size) >= minsize) {
                    minsize = temp->size;
                    swap_data(&num, &temp);
                }
            } else {
                if ((temp->size) < minsize) {
                    minsize = temp->size;
                    swap_data(&num, &temp);
                }
            }
            temp = temp->next;
            
        }
        sort_list_size(&num, sortorder);
        num = num->next;
    }

    return;
}

void sort_list_date(List *list, int sortorder) {
    
    node *num = (*list)->branch;

    while (num != NULL) {
        time_t mindate = num->create_date;
        node *temp = num->next;

        while (temp != NULL) {

            if (sortorder == 1) {
                if ((temp->create_date) <= mindate) {
                    mindate = temp->create_date;
                    swap_data(&num, &temp);
                }
            } else {
                if ((temp->create_date) > mindate) {
                    mindate = temp->create_date;
                    swap_data(&num, &temp);
                }
            }
            temp = temp->next;
            
        }
        sort_list_date(&num, sortorder);
        num = num->next;
    }
    return;
}




