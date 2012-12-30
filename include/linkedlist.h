#ifndef __LINKEDLIST_H__
#define __LINKEDLIST_H__

#include <stdbool.h>

typedef struct ListNode_t {
	struct ListNode_t *next;
	struct ListNode_t *prev;
	void *data;    
} ListNode;

typedef struct LinkedList_t {
	ListNode *head;
	ListNode *tail;
	int count;
} LinkedList;

/* Creates a new, empty list */
LinkedList* linked_list_new();

/* Append element to end of list */
bool linked_list_add(LinkedList *list, const void *data);

/* Insert element at specified index. 0 is the start */
bool linked_list_add_at(LinkedList *list, const void *data, int index);

/* Appends all of the elements in the specified collection to the end 
	 of this list, in the order that they are stored. You can get rid of 
	 any pointers to the memory associated with the elements, but DO NOT
	 FREE the underlying data, as the data is not copied. */
bool linked_list_add_all(LinkedList *list, const void **elements, int count);

/* Inserts all of the elements in the specified collection into this list, 
	 starting at the specified position. */
bool linked_list_add_all_at(LinkedList *list, int index, const void **elements, int count);

/* Removes all of the elements from this list. */
void linked_list_clear(LinkedList *list, bool deep);

void linked_list_clear_custom(LinkedList *list, void (*destroy_func)(void *data));

/* Returns a copy of this LinkedList. */
LinkedList* linked_list_clone(LinkedList *list);

/* Returns true if this list contains the specified element. */
bool linked_list_contains(LinkedList *list, const void *data);

bool linked_list_contains_custom(LinkedList *list, const void *data, 
																					int (*compare_func)(void *a, void *b));

/* TODO: deal with iterators */

/* Returns the element at the specified position in this list. */
void* linked_list_get(LinkedList *list, int index);

/* Returns the index of the first occurrence of the specified element 
	 in this list, or -1 if this list does not contain the element. */
int linked_list_index_of(LinkedList *list, void *data);

/* Returns the index of the first occurrence of the specified element 
	 in this list, or -1 if this list does not contain the element. Uses
	 custom comparison function. */
int linked_list_index_of_custom(LinkedList *list, void *data, int (*compare_func)(void *a, void *b));

/* Returns true if this list contains no elements. */
bool linked_list_is_empty(LinkedList *list);

/* Returns the index of the last occurrence of the specified element in 
	 this list, or -1 if this list does not contain the element. */
int linked_list_last_index_of(LinkedList *list, void *data);

/* Returns the index of the last occurrence of the specified element in 
	 this list, or -1 if this list does not contain the element. Uses
	 compare_func to compare elements. */
int linked_list_last_index_of_custom(LinkedList *list, void *data
																				, int (*compare_func)(void *a, void *b));

/* Removes the element at the specified position in this list. */
void* linked_list_remove(LinkedList *list, int index);

/* Removes the first occurrence of the specified element 
	 from this list, if it is present. */
void* linked_list_remove_with_data(LinkedList *list, void *data);

/* Removes the first occurrence of the specified element 
	 from this list, if it is present. */
void* linked_list_remove_with_data_custom(LinkedList *list, void *data,
																					int (*compare_func)(void *a, void *b));

/* Removes from this list all of its elements that are 
	 contained in the specified collection (optional operation). */
bool linked_list_remove_all(LinkedList *list, void** elements, int count); 

/* Removes from this list all of its elements that are 
	 contained in the specified collection (optional operation). */
bool linked_list_remove_all_custom(LinkedList *list, void** elements, int count,
																	int (*compare_func)(void *a, void *b)); 

/* Retains only the elements in this list that are contained 
	 in the specified collection (optional operation). */
bool linked_list_retain_all(LinkedList *list, void **elements, int count);

/* Retains only the elements in this list that are contained 
	 in the specified collection (optional operation). */
bool linked_list_retain_all_custom(LinkedList *list, void **elements, int count,
																	int (*compare_func)(void *a, void *b));

/* Replaces the element at the specified position in 
	 this list with the specified element. */
void* linked_list_set(LinkedList *list, int index, void *data);

/* Size of list */
int linked_list_size(LinkedList *list);

/* Returns a view of the portion of this list between the 
	 specified fromIndex, inclusive, and toIndex, exclusive. */
LinkedList* linked_list_sub_list(LinkedList *list, int from, int to);

/* Returns a view of the portion of this list between the 
	 specified fromIndex, inclusive, and toIndex, exclusive. */
LinkedList* linked_list_sub_list_deep(LinkedList *list, int from, int to,
																							void *(*copy_func)(void *data));

/* Returns an array containing all of the elements in this 
	 list in proper sequence (from first to last element). deep specifies
	 whether or not to make a deep copy of the data elements */
void** linked_list_to_array(LinkedList *list, bool deep);

/* Method that frees the list, all nodes and 
	 underlying data in the nodes IF deep is true, otherwise
	 it takes care of the list and the nodes */
void linked_list_free(LinkedList *list, bool deep);

/* Method that frees the list, all nodes and. Calls destroy_func
	 on every data pointer it has for custom cleanup. Since we're 
	 giving the user the option for custom cleanup, no need to specify
	 whether the cleanup is deep or shallow. */
void linked_list_free_custom(LinkedList *list, void (*destroy_func)(void *data));

#endif /* __LINKEDLIST_H__ */
