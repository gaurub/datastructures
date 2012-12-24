#include <stdio.h>
#include <stdlib.h>
#include "list.h"

List* new_list() {

    /* Set up the list structure */
    List *list = malloc(sizeof(List));
    if(!list) {
        fprintf(stderr, "Big problems, Could not allocate list.\n");
        return NULL;
    }
    list->count = 0;

    /* set up head and tail node */
    Node *head = malloc(sizeof(Node));
    if(!head) {
        free(list);
        fprintf(stderr, "Big problems, Could not allocate head node.\n");
        return NULL;
    }

    Node *tail = malloc(sizeof(Node));
    if(!tail) {
        free(list);
        free(head);
        fprintf(stderr, "Big problems, Could not allocate tail node.\n");
        return NULL;
    }

    /* set our pointers */
    head->next = tail;
    head->data = NULL;
    head->prev = NULL;

    tail->prev = head;
    tail->next = NULL;
    tail->data = NULL;

    list->head = head;
    list->tail = tail;

    return list;
}

Node* node_with_data(List *list, void *data) {

    /* some sanity checking */
    if(list == NULL) {
        fprintf(stderr, "List was null.");
        return NULL;
    }

    /* more sanity checking */
    if(data == NULL) {
        fprintf(stderr, "Data was null.");
        return NULL;
    }

    /* we start at the "next" of the head node 
    because the head node will never contain data */
    Node *current_node = list->head->next;
    while(current_node->next) {
        if(data == current_node->data) {
            return current_node;
        }
        current_node = current_node->next;
    }
    return NULL;
}

int list_size(List *list) {
    return list->count;
}

Node* insert_node_with_data(List *list, void *data) {

    /* some sanity checking */
    if(list == NULL) {
        fprintf(stderr, "List was null.");
        return NULL;
    }

    /* more sanity checking */
    if(data == NULL) {
        fprintf(stderr, "Data was null.");
        return NULL;
    }

    /* Always insert before tail */
    Node *new_node = malloc(sizeof(Node));
    if(!new_node) {
        fprintf(stderr, "Big problems, Could not allocate new node for insertion.\n");
        return NULL;
    }
    new_node->data = data;

    /* manipulate pointers */
    new_node->next = list->tail;
    new_node->prev = list->tail->prev;
    new_node->prev->next = new_node;
    list->tail->prev = new_node;
    ++(list->count);
    return new_node;
}

/* function that frees list along with all data */
void free_list_deep(List *list) {
    Node *current_node = list->head;
    Node *next_node;
    while(current_node->next) {
        free(current_node->data);
        next_node = current_node->next;
        free(current_node);
        current_node = next_node;
    }

    /* remember to get rid of that tail node */
    free(current_node);
    free(list);
}

/* function that frees list but does not free data */
void free_list_shallow(List *list) {
    Node *current_node = list->head;
    Node *next_node;
    while(current_node->next) {
        next_node = current_node->next;
        free(current_node);
        current_node = next_node;
    }

    /* remember to grab that tail node */
    free(current_node);
    free(list);
}

static void print_list(List *list) {
    printf("Size of list= %d\n", list->count);
    Node *current_node = list->head->next;
    while(current_node->next) {
        printf("Value of data = %d.\n", *((int *) current_node->data));
        current_node = current_node->next;
    }
}

/* Main function to test functionality */

int main(int argc, char** argv) {
    List *list = new_list();
    int i = 5, j = 10;
    insert_node_with_data(list, &i);
    insert_node_with_data(list, &j);
    print_list(list);
    free_list_shallow(list);
	return 0;
}
