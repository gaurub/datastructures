#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "linkedlist.h"

#define NYI(x) printf("Not yet implemented: %s.\n", x);

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

bool linked_list_add(LinkedList *list, void *data) {

	assert(NULL != list);
	assert(NULL != data);

	/* Always insert before tail */
	ListNode *new_node = malloc(sizeof(ListNode));
	if(!new_node) {
			fprintf(stderr, "Big problems, Could not allocate new node for insertion.\n");
			return false;
	}
	new_node->data = data;

	/* manipulate pointers */
	new_node->next = list->tail;
	new_node->prev = list->tail->prev;
	new_node->prev->next = new_node;
	list->tail->prev = new_node;
	++(list->count);
	return true;
}

bool linked_list_add_at(LinkedList *list, void *data, int index) {

	ListNode *current_node;
	int counter;

	assert(NULL != list);
	assert(NULL != data);
	assert(index >= 0);
	assert(list->count <= (index + 1));

	

}

bool linked_list_add_all(LinkedList *list, void **elements, int count) {
	NYI(__func__);
	return false;
}

bool linked_list_add_all_at(LinkedList *list, int index, void **elements, int count) {
	NYI(__func__);
	return false;
}


/* Inserts the specified element at the beginning of this list. */
bool linked_list_add_first(LinkedList *list, void *data) {
	NYI(__func__);
	return 0;
}

/* Appends the specified element to the end of this list. */
bool linked_list_add_last(LinkedList *list, void *data) {
	NYI(__func__);
	return 0;
}

/* Removes all of the elements from this list. */
void linked_list_clear(LinkedList *list) {
	NYI(__func__);
}

/* Returns a shallow copy of this LinkedList. */
LinkedList* linked_list_clone(LinkedList *list, bool deep) {
	NYI(__func__);
	return NULL;
}

/* Returns true if this list contains the specified element. */
/* TODO: this should take a comparison function */
bool linked_list_contains(LinkedList *list, void *data) {

	ListNode *current_node;

	assert(NULL != list);
	assert(NULL != data);

	/* we start at the "next" of the head node 
	   because the head node will never contain data */
	current_node = list->head->next;

	while(current_node->next) {
			if(data == current_node->data) {
					return true;
			}
			current_node = current_node->next;
	}
	return false;

}

/* Retrieves, but does not remove, the head (first element) of this list. */
void* linked_list_element(LinkedList *list) {
	return linked_list_get_first(list);
}

void* linked_list_get(LinkedList *list, int index) {

	ListNode *current_node;
	int counter;

	// assert list is not null, index >=0 & index is valid
	assert(NULL != list);
	assert(index >= 0);
	assert(list->count <= (index + 1));

	current_node = list->head->next;
	counter = 0;
	while(current_node->next) {
			if(counter == index) {
					return current_node->data;
			}

			++counter;
			current_node = current_node->next;
	}
	return NULL;
}

/* Retrieves, but does not remove, the head (first element) of this list. */
void* linked_list_get_first(LinkedList *list) {
	// doing this for performance instead of just calling linked_list_get
	assert(NULL != list);
	assert(list->count > 0);

	return list->head->next->data;
}

/* Returns the last element in this list. */
void* linked_list_get_last(LinkedList *list) {
	assert(NULL != list);
	assert(list->count > 0);
	return list->tail->prev->data;
}


/* Returns the index of the first occurrence of the specified element 
in this list, or -1 if this list does not contain the element. */
int linked_list_index_of(LinkedList *list, void *data) {

	ListNode *current_node;
    int counter;

	assert(NULL != list);
	assert(NULL != data);

	/* we start at the "next" of the head node 
	   because the head node will never contain data */
	current_node = list->head->next;
    counter = 0;

	while(current_node->next) {
		if(data == current_node->data) {
				return counter;
		}
        ++counter;
		current_node = current_node->next;
	}
	return -1;

}

/* Returns the index of the last occurrence of the specified element in 
this list, or -1 if this list does not contain the element. */
int linked_list_last_index_of(LinkedList *list, void *data) {
	ListNode *current_node;
	int counter;

	assert(NULL != list);
	assert(NULL != data);

	/* traverse backwards and return first occurence */
	current_node = list->tail->prev;
	counter = 0;
	while(current_node->prev) {
		if(data == current_node->data) {
			return counter;
		}
		++counter;
		current_node = current_node->prev;
	}
}

/* Adds the specified element as the tail (last element) of this list. */
bool linked_list_offer(LinkedList *list, void *data) {
	ListNode *node = linked_list_add_
}

/* Inserts the specified element at the front of this list. */
bool linked_list_offer_first(LinkedList *list, void *data);

/* Inserts the specified element at the end of this list. */
bool linked_list_offer_last(LinkedList *list, void *data);

ListNode* linked_list_node_with_data(LinkedList *list, void *data) {

	ListNode *current_node;

	assert(NULL != list);
	assert(NULL != data);

	/* we start at the "next" of the head node 
	   because the head node will never contain data */
	current_node = list->head->next;

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

/* function that frees list along with all data */
void linked_list_free(LinkedList *list, bool deep) {

	assert(NULL != list);

	ListNode *current_node = list->head;
	ListNode *next_node;
	while(current_node->next) {
       	if(deep) {
       		free(current_node->data);
        }
		next_node = current_node->next;
		free(current_node);
		current_node = next_node;
	}

	/* remember to get rid of that tail node */
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
	linked_list_add_all(list, NULL, 0);
	linked_list_add_all_at(list, 0, NULL, 0);
	linked_list_free(list, false);
	return 0;
}
