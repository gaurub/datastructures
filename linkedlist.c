#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "linkedlist.h"
#include "common.h"

LinkedList* linked_list_new() {

	/* Set up the list structure */
	LinkedList *list;
	ListNode *head, *tail;

	list = malloc(sizeof(LinkedList));
	/* conditions to fail somewhat gracefully */
	if(!list) {
		LOG_DEBUG("Could not allocate list structure.", __FILE__, __LINE__);
		return NULL;
	}
	list->count = 0;

	/* set up head and tail node */
	head = malloc(sizeof(ListNode));
	if(!head) {
		free(list);
		LOG_DEBUG("Big problems, Could not allocate head node.", __FILE__, __LINE__);
		return NULL;
	}

	tail = malloc(sizeof(ListNode));
	if(!tail) {
		free(list);
		free(head);
		LOG_DEBUG("Big problems, Could not allocate tail node.", __FILE__, __LINE__);
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
static bool add_node_before(LinkedList *list, ListNode *node, const void *data) {

	ListNode *new, *prev;

	prev = node->prev;

	new = malloc(sizeof(ListNode));
	if(!new) {
		LOG_DEBUG("Couldn't allocate memory for new node.", __FILE__, __LINE__);
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


bool linked_list_add(LinkedList *list, const void *data) {

	assert(NULL != list);
	assert(NULL != data);

	return add_node_before(list, list->tail, data);
}

bool linked_list_add_at(LinkedList *list, const void *data, int index) {

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

bool linked_list_add_all(LinkedList *list, const void **elements, int count) {

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

bool linked_list_add_all_at(LinkedList *list, int index, const void **elements, int count) {

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

	ListNode *current_node;
	ListNode *next_node;
	void *data;
	
	assert(NULL != list);

	/* leave the head and tail as is, so grabbing "next" */
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

/* Removes all of the elements from this list. */
void linked_list_clear_custom(LinkedList *list, void (*destroy_func)(void *data)) {

	ListNode *current_node;
	ListNode *next_node;
	void *data;
	
	assert(NULL != list);
	assert(NULL != destroy_func);

	/* leave the head and tail as is, so grabbing "next" */
	current_node = list->head->next;
	while(current_node->next) {
		next_node = current_node->next;
		data = remove_node(list, current_node);
		destroy_func(data);
		current_node = next_node;
	}
}

/* Returns a shallow copy of this LinkedList. */
LinkedList* linked_list_clone(LinkedList *list) {

	LinkedList *new_list;
	ListNode *current_node;

	assert(NULL != list);

	new_list = linked_list_new();
	if(!new_list) {
		LOG_DEBUG("Could not allocate new list for cloning.", __FILE__, __LINE__);
		return NULL;
	}

	/* copy node stuff in */
	current_node = list->head->next;
	while(current_node->next) {

		/* if a node fails; free everything and then bail */
		if(!add_node_before(new_list, new_list->tail, current_node->data)) {
			linked_list_free(new_list, false);
			return NULL;
		}
		current_node = current_node->next;
	}

	return new_list;
}

/* Returns a deep copy of this LinkedList. */
LinkedList* linked_list_clone_deep(LinkedList *list, void *(*copy_func)(void *data)) {

	LinkedList *new_list;
	ListNode *current_node;
	void *data;

	assert(NULL != list);
	assert(NULL != copy_func);

	new_list = linked_list_new();
	if(!new_list) {
		LOG_DEBUG("Could not allocate new list for cloning.", __FILE__, __LINE__);
		return NULL;
	}

	/* copy node stuff in */
	current_node = list->head->next;
	while(current_node->next) {

		data = copy_func(current_node->data);
		if(!data) {
			LOG_DEBUG("Error copying data while cloning list. Aborting clone...", __FILE__, __LINE__);
			linked_list_free(new_list, true); /* attemt cleanup */
			return NULL;
		}

		/* if a node fails; free everything and then bail */
		if(!add_node_before(new_list, new_list->tail, data)) {
			LOG_DEBUG("Error adding new node to list. Aborting clone...", __FILE__, __LINE__);
			linked_list_free(new_list, true);
			return NULL;
		}
	}

	return new_list;
}

/* Returns true if this list contains the specified element. */
/* TODO: this should take a comparison function */
bool linked_list_contains(LinkedList *list, const void *data) {

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

/* Returns true if this list contains the specified element. */
/* TODO: this should take a comparison function */
bool linked_list_contains_custom(LinkedList *list, const void *data,
																		int (*compare_func)(void *a, void* b)) {

	ListNode *current_node;

	assert(NULL != list);
	assert(NULL != data);
	assert(NULL != compare_func);

	/* we start at the "next" of the head node 
		 because the head node will never contain data */
	current_node = list->head->next;
	while(current_node->next) {
		if(EQUALS == compare_func(data,current_node->data)) {
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

/* Returns the index of the first occurrence of the specified element 
	 in this list, or -1 if this list does not contain the element. 
	 Uses custom comparison function. */
int linked_list_index_of_custom(LinkedList *list, void *data,
																		int (*compare_func)(void *a, void *b)) {

	ListNode *current_node;
	int counter;

	assert(NULL != list);
	assert(NULL != data);
	assert(NULL != compare_func);

	/* we start at the "next" of the head node 
		 because the head node will never contain data */
	current_node = list->head->next;
	counter = 0;

	while(current_node->next) {
		if(EQUALS == compare_func(data,current_node->data)) {
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

/* Returns the index of the last occurrence of the specified element in 
	 this list, or -1 if this list does not contain the element. */
int linked_list_last_index_of_custom(LinkedList *list, void *data,
																		int (*compare_func)(void *a, void *b)) {

	ListNode *current_node;
	int counter;

	assert(NULL != list);
	assert(NULL != data);
	assert(NULL != compare_func);

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

void *linked_list_remove_with_data_custom(LinkedList *list, void *data,
																					int (*compare_func)(void *a, void *b)) {
	ListNode *current_node;	

	assert(NULL != list);
	assert(NULL != data);

	current_node = list->head->next;
	while(current_node->next) {
		if(EQUALS == compare_func(data, current_node->data)) {
			return remove_node(list, current_node);
		}
		current_node = current_node->next;
	}

	return NULL;
}

bool linked_list_remove_all(LinkedList *list, void** elements, int count) {

	int counter;

	assert(NULL != list);
	assert(NULL != elements);
	assert(count >= 0 && count <= list->count);

	for(counter = 0; counter < count; ++counter) {
		if(NULL == linked_list_remove_with_data(list, elements[counter])) {
			return false;
		}
	}

	return true;
}

bool linked_list_remove_all_custom(LinkedList *list, void** elements, int count, 
																							int (*compare_func)(void *a, void *b)) {
	int counter;

	assert(NULL != list);
	assert(NULL != elements);
	assert(count >= 0 && count <= list->count);

	for(counter = 0; counter < count; ++counter) {
		if(NULL == linked_list_remove_with_data_custom(list, elements[counter], 
																												compare_func)) {
			return false;
		}
	}

	return true;
}


bool linked_list_retain_all(LinkedList *list, void** elements, int count) {
	
	ListNode *current_node, *placeholder_node;
	int counter;
	bool node_remove;

	assert(NULL != list);
	assert(NULL != elements);
	assert(count >= 0 && count <= list->count);

	current_node = list->head->next;
	node_remove = true;
	while(current_node->next) {
		for(counter = 0; counter < count; ++counter) {
			if(elements[counter] == current_node->data) {
				node_remove = false;		
				break;
			}
		}
		if(true == node_remove) {
			placeholder_node = current_node->prev;
			remove_node(list, current_node);
			current_node = placeholder_node;
		}
		current_node = current_node->next;
		node_remove = true;
	}

	return true;
}

bool linked_list_retain_all_custom(LinkedList *list, void** elements, int count,
																							int (*compare_func)(void *a, void *b)) {
	ListNode *current_node, *placeholder_node;
	int counter;
	bool node_remove;

	assert(NULL != list);
	assert(NULL != elements);
	assert(count >= 0 && count <= list->count);

	current_node = list->head->next;
	node_remove = true;
	while(current_node->next) {
		for(counter = 0; counter < count; ++counter) {
			if(EQUALS == compare_func(elements[counter],current_node->data)){
				node_remove = false;		
				break;
			}
		}
		if(true == node_remove) {
			placeholder_node = current_node->prev;
			remove_node(list, current_node);
			current_node = placeholder_node;
		} 
		current_node = current_node->next;
		node_remove = true; /* really debated whether putting this in an "else"
												block above; did this for simplicity */
	}

	return true;

}

void* linked_list_set(LinkedList *list, int index, void *data) {

	int counter;
	ListNode *current_node;
	void *old_data;
	
	assert(NULL != list);
	assert((index + 1) <= list->count);
	assert(NULL != data);

	current_node = list->head->next;
	for(counter = 0; counter < list->count; ++counter) {
		if(counter == index) {
			old_data = current_node->data;
			current_node->data = data;
			return old_data;
		}
		current_node = current_node->next;
	}

	return NULL;
}

int linked_list_size(LinkedList *list) {

	assert(NULL != list);
	return list->count;

}

LinkedList* linked_list_sub_list(LinkedList *list, int from, int to) {

	LinkedList *sub_list;
	int counter;

	assert(NULL != list);
	assert(from < to);
	assert(to < (list->count - 1));
	assert(from >= 0);

	sub_list = linked_list_new();
	if(!sub_list) {
		LOG_DEBUG("Error creating new list.", __FILE__, __LINE__);
		return NULL;
	}

	for(counter = from; counter <= to; ++counter) {
		if(!add_node_before(sub_list, sub_list->tail, linked_list_get(list, counter))) {
			LOG_DEBUG("Error adding node.", __FILE__, __LINE__);
			linked_list_free(sub_list, false);
			return NULL;
		}
	}

	return sub_list;
}

LinkedList* linked_list_sub_list_deep(LinkedList *list, int from, int to,
																			void *(*copy_func)(void *data)) {
	LinkedList *sub_list;
	int counter;

	assert(NULL != list);
	assert(from < to);
	assert(to < (list->count - 1));
	assert(from >= 0);

	sub_list = linked_list_new();
	if(!sub_list) {
		LOG_DEBUG("Error creating new list.", __FILE__, __LINE__);
		return NULL;
	}

	for(counter = from; counter <= to; ++counter) {
		void *data = copy_func(linked_list_get(list, counter));
		if(!data) {
			LOG_DEBUG("Deep copy of node data failed.", __FILE__, __LINE__);
			linked_list_free(sub_list, true);
			return NULL;
		}
		if(!add_node_before(sub_list, sub_list->tail, data)) {
			LOG_DEBUG("Error adding node.", __FILE__, __LINE__);
			linked_list_free(sub_list, true);
			return NULL;
		}
	}

	return sub_list;
}

void** linked_list_to_array(LinkedList *list) {

	void **elements;
	ListNode *current_node;
	int counter;

	assert(NULL != list);
	
	*elements = malloc(sizeof(void *) * list->count);
	if(!elements) {
		LOG_DEBUG("Allocation of array failed.", __FILE__, __LINE__);
		return NULL;
	}

	current_node = list->head->next;
	counter = 0;
	while(current_node->next) {
		elements[counter] = current_node->data;		
		current_node = current_node->next;
		++counter;
	}

	return elements;
}

void** linked_list_to_array_deep(LinkedList *list, void *(*copy_func)(void *data)) {

	void **elements;
	ListNode *current_node;
	int counter;
	int free_counter;

	assert(NULL != list);
	
	*elements = malloc(sizeof(void *) * list->count);
	if(!elements) {
		LOG_DEBUG("Allocation of array failed.", __FILE__, __LINE__);
		return NULL;
	}

	current_node = list->head->next;
	counter = 0;
	while(current_node->next) {
		void *data = copy_func(current_node->data);
		if(!data) {
			LOG_DEBUG("Error copying data for insertion into array.", __FILE__, __LINE__);
			// free memory for nodes already copied
			for(free_counter = 0; free_counter < counter; ++free_counter) {
				free(elements[free_counter]);
			}
			free(elements);  
		}
		elements[counter] = data;		
		current_node = current_node->next;
		++counter;
	}

	return elements;
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

ListNode* linked_list_node_with_data_custom(LinkedList *list, void *data,
																						int (*compare_func)(void *a, void *b)) {

	ListNode *current_node;

	assert(NULL != list);
	assert(NULL != data);

	/* we start at the "next" of the head node 
		 because the head node will never contain data */
	current_node = list->head->next;

	while(current_node->next) {
		if(EQUALS == compare_func(data,current_node->data)) {
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

/* function that frees list along with all data */
void linked_list_free_custom(LinkedList *list, void (*destroy_func)(void *data)) {

	assert(NULL != list);
	assert(NULL != destroy_func);

	ListNode *current_node = list->head;
	ListNode *next_node;
	while(current_node->next) {
		destroy_func(current_node->data);
		next_node = current_node->next;
		free(current_node);
		current_node = next_node;
	}

	/* remember to get rid of that tail node */
	free(current_node);
	free(list);
}

void linked_list_for_each(LinkedList *list, void (*operation)(void *data)) {

	ListNode *current_node;

	assert(NULL != list);
	assert(NULL != operation);

	current_node = list->head->next;
	while(current_node->next) {
		operation(current_node->data);
		current_node = current_node->next;
	}

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
