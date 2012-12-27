#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "linkedlist.h"
#include "common.h"

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

/* internal method to add a node before a node. The naming is a little
	 confusing; suggestions welcome */
static bool add_node_before(LinkedList *list, ListNode *node, void *data) {

	ListNode *new, *prev;

	prev = node->prev;

	new = malloc(sizeof(ListNode));
	if(!new) {
		fprintf(stderr,"Couldn't allocate memory for new node.\n");
		return false;
	}
	new->data = data;

	// fix prev pointers
	new->prev = prev;
	node->prev = new;

	// fix next pointers
	new->next = node;
	prev->next = new;

	// the sole reason we have to pass that list pointer here
	++(list->count);

	return true;
}

static void* remove_node(LinkedList *list, ListNode *node) {
	ListNode *prev, *next;
	prev = node->prev;
	next = node->next;
	next->prev = prev;
	prev->next = next;
	void *data = node->data;
	free(node);
	--(list->count);
	return data;
}


bool linked_list_add(LinkedList *list, void *data) {

	assert(NULL != list);
	assert(NULL != data);

	return add_node_before(list, list->tail, data);
}

bool linked_list_add_at(LinkedList *list, void *data, int index) {

	ListNode *current_node;
	int counter;

	assert(NULL != list);
	assert(NULL != data);
	assert(index >= 0);
	assert((index + 1) <= list->count);

	current_node = list->head->next;
	// for some reason, a for loop seems more intuitive here
	// just to convey that everything is index based
	// rather than the not-null status of the next.
	for(counter = 0; counter < list->count; counter++) {
		if(counter == index) {
			return add_node_before(list, current_node, data);
		}
		current_node = current_node->next;
	}

	return false;
}

bool linked_list_add_all(LinkedList *list, void **elements, int count) {

	int counter;

	assert(NULL != list);
	assert(NULL != elements);
	assert(count >= 0); // if it's 0, nothing below will run

	for(counter = 0; counter < count; ++counter) {
		if(!add_node_before(list, list->tail, elements[counter])) {
			return false;
		}
	}
	return true;
}

bool linked_list_add_all_at(LinkedList *list, int index, void **elements, int count) {

	int counter;
	ListNode *current_node;

	assert(NULL != list);
	assert(NULL != elements);
	assert(count >= 0);
	assert((index + 1) <= list->count);

	/* get to the right place */
	current_node = list->head->next;
	for(counter = 0; counter < list->count; ++counter) {
		if(counter == index) {
			break;
		}
		current_node = current_node->next;
	}

	for(counter = 0; counter < count; ++counter) {
		if(!add_node_before(list, current_node, elements[counter])) {
			// This will not exit cleanly; the transaction will not be aborted in the middle.
			return false;	
		}
	}

	return true;
}

/* Removes all of the elements from this list. */
void linked_list_clear(LinkedList *list, bool deep) {

	/* leave the head and tail as is */
	ListNode *current_node;
	ListNode *next_node;
	void *data;
	
	assert(NULL != list);

	current_node = list->head->next;
	while(current_node->next) {
		next_node = current_node->next;
		data = remove_node(list, current_node);
		if(deep) {
			free(data);
		}
		current_node = next_node;
	}
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

void* linked_list_get(LinkedList *list, int index) {

	ListNode *current_node;
	int counter;

	// assert list is not null, index >=0 & index is valid
	assert(NULL != list);
	assert(index >= 0);
	assert((index + 1) <= list->count);

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

bool linked_list_is_empty(LinkedList *list) {
	assert(NULL != list);
	return list->count == 0 ? true : false;
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
	return -1;
}

void* linked_list_remove(LinkedList *list, int index) {

	ListNode *current_node;
	int counter;

	assert(NULL != list);

	current_node = list->head->next;
	counter = 0;
	/* again, when iterating with indices, for some reason a 
		 for loop seems nicer */
	for(counter = 0; counter < list->count; counter++) {
		if(counter == index) {
			return remove_node(list, current_node);
		}
		current_node = current_node->next;
	}
	return NULL;
}

void* linked_list_remove_with_data(LinkedList *list, void *data) {

	ListNode* current_node;

	assert(NULL != list);
	assert(NULL != data);

	current_node = list->head->next;
	while(current_node->next) {
		if(data == current_node->data) {
			return remove_node(list, current_node);
		}
		current_node = current_node->next;
	}
	return NULL;
}

bool linked_list_remove_all(LinkedList *list, void** elements, int index) {
	NYI(__func__);
	return false;
}

bool linked_list_retail_all(LinkedList *list, void** elements, int index) {
	NYI(__func__);
	return false;
}

void* linked_list_set(LinkedList *list, int index, void *data) {
	NYI(__func__);
	return NULL;
}

int linked_list_size(LinkedList *list) {

	assert(NULL != list);
	return list->count;
}

LinkedList* linked_list_sub_list(LinkedList *list, int from, int to) {
	NYI(__func__);
	return NULL;
}

void** linked_list_to_array(LinkedList *list, bool deep) {
	NYI(__func__);
	return NULL;
}

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
/*int main(int argc, char** argv) {
	LinkedList *list = linked_list_new();
	int i = 5, j = 10, q = 25;
	linked_list_add(list, &i);
	linked_list_add(list, &j);
	print_list(list);
	linked_list_add_at(list, &q, 1);
	print_list(list);
	linked_list_remove_with_data(list, &q);
	print_list(list);
	LOG_DEBUG("Hello World!", __FILE__, __LINE__);
	linked_list_free(list, false);
	return 0;
}*/
