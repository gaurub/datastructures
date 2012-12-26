#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "linkedlist.h"

LinkedList* linked_list_new() {

    /* Set up the list structure */
    LinkedList *list = malloc(sizeof(LinkedList));


    /* conditions to fail somewhat gracefully */
    if(!list) {
        fprintf(stderr, "Big problems, Could not allocate list.\n");
        return NULL;
    }
    list->count = 0;

    /* set up head and tail node */
    ListNode *head = malloc(sizeof(ListNode));
    if(!head) {
        free(list);
        fprintf(stderr, "Big problems, Could not allocate head node.\n");
        return NULL;
    }

    ListNode *tail = malloc(sizeof(ListNode));
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

ListNode* linked_list_node_at(LinkedList *list, int index) {

    ListNode *current_node;
    int counter;

    assert(NULL != list);
    assert(index >= 0);
    
   /* see if we're getting asked for something that's not there */
   if((list->count < (index + 1))) {
        fprintf(stderr, "Element does not exist in list. Please specify a valid index.");
        return NULL;
   }

   current_node = list->head->next;
   counter = 0;
   while(current_node->next) {
        if(counter == index) {
            return current_node;
        }

        ++counter;
        current_node = current_node->next;
   }
   return NULL;
}

ListNode* linked_list_node_with_data(LinkedList *list, void *data) {

    assert(NULL != list);
    assert(NULL != data);

    /* we start at the "next" of the head node 
    because the head node will never contain data */
    ListNode *current_node = list->head->next;
    while(current_node->next) {
        if(data == current_node->data) {
            return current_node;
        }
        current_node = current_node->next;
    }
    return NULL;
}

int linked_list_size(LinkedList *list) {

    assert(NULL != list);
    return list->count;
}

ListNode* linked_list_add(LinkedList *list, void *data) {

    assert(NULL != list);
    assert(NULL != data);

    /* Always insert before tail */
    ListNode *new_node = malloc(sizeof(ListNode));
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
void linked_list_free_deep(LinkedList *list) {

    assert(NULL != list);

    ListNode *current_node = list->head;
    ListNode *next_node;
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
void linked_list_free_shallow(LinkedList *list) {

    assert(NULL != list);
    
    ListNode *current_node = list->head;
    ListNode *next_node;
    while(current_node->next) {
        next_node = current_node->next;
        free(current_node);
        current_node = next_node;
    }

    /* remember to grab that tail node */
    free(current_node);
    free(list);
}

static void print_list(LinkedList *list) {
    printf("Size of list= %d\n", list->count);
    ListNode *current_node = list->head->next;
    while(current_node->next) {
        printf("Value of data = %d.\n", *((int *) current_node->data));
        current_node = current_node->next;
    }
}

/* Main function to test functionality */
int main(int argc, char** argv) {
    LinkedList *list = linked_list_new();
    int i = 5, j = 10;
    linked_list_add(list, &i);
    linked_list_add(list, &j);
    print_list(list);
    linked_list_free_shallow(list);
	return 0;
}
