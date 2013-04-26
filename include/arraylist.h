#ifndef __ARRAYLIST_H__
#define __ARRAYLIST_H__

#include <stdbool.h>

typedef struct ArrayList_t {
	void* array;
	int count;
	int capacity;
} ArrayList;

/* Creates a new, empty list */
ArrayList* array_list_new();

/* Append element to end of list */
bool array_list_add(ArrayList *list, const void *data);

/* Insert element at specified index. 0 is the start */
bool array_list_add_at(ArrayList *list, const void *data, int index);

/* Appends all of the elements in the specified collection to the end 
	 of this list, in the order that they are stored. You can get rid of 
	 any pointers to the memory associated with the elements, but DO NOT
	 FREE the underlying data, as the data is not copied. */
bool array_list_add_all(ArrayList *list, const void **elements, int count);

/* Inserts all of the elements in the specified collection into this list, 
	 starting at the specified position. */
bool array_list_add_all_at(ArrayList *list, int index, const void **elements, int count);

/* Removes all of the elements from this list. */
void array_list_clear(ArrayList *list, bool deep);

void array_list_clear_custom(ArrayList *list, void (*destroy_func)(void *data));

/* Returns a copy of this ArrayList. */
ArrayList* array_list_clone(ArrayList *list);

/* Returns true if this list contains the specified element. */
bool array_list_contains(ArrayList *list, const void *data);

bool array_list_contains_custom(ArrayList *list, const void *data, 
																					int (*compare_func)(void *a, void *b));

/* TODO: deal with iterators */

/* Returns the element at the specified position in this list. */
void* array_list_get(ArrayList *list, int index);

/* Returns the index of the first occurrence of the specified element 
	 in this list, or -1 if this list does not contain the element. */
int array_list_index_of(ArrayList *list, void *data);

/* Returns the index of the first occurrence of the specified element 
	 in this list, or -1 if this list does not contain the element. Uses
	 custom comparison function. */
int array_list_index_of_custom(ArrayList *list, void *data, int (*compare_func)(void *a, void *b));

/* Returns true if this list contains no elements. */
bool array_list_is_empty(ArrayList *list);

/* Returns the index of the last occurrence of the specified element in 
	 this list, or -1 if this list does not contain the element. */
int array_list_last_index_of(ArrayList *list, void *data);

/* Returns the index of the last occurrence of the specified element in 
	 this list, or -1 if this list does not contain the element. Uses
	 compare_func to compare elements. */
int array_list_last_index_of_custom(ArrayList *list, void *data
																				, int (*compare_func)(void *a, void *b));

/* Removes the element at the specified position in this list. */
void* array_list_remove(ArrayList *list, int index);

/* Removes the first occurrence of the specified element 
	 from this list, if it is present. */
void* array_list_remove_with_data(ArrayList *list, void *data);

/* Removes the first occurrence of the specified element 
	 from this list, if it is present. */
void* array_list_remove_with_data_custom(ArrayList *list, void *data,
																					int (*compare_func)(void *a, void *b));

/* Removes from this list all of its elements that are 
	 contained in the specified collection (optional operation). */
bool array_list_remove_all(ArrayList *list, void** elements, int count); 

/* Removes from this list all of its elements that are 
	 contained in the specified collection (optional operation). */
bool array_list_remove_all_custom(ArrayList *list, void** elements, int count,
																	int (*compare_func)(void *a, void *b)); 

/* Retains only the elements in this list that are contained 
	 in the specified collection (optional operation). */
bool array_list_retain_all(ArrayList *list, void **elements, int count);

/* Retains only the elements in this list that are contained 
	 in the specified collection (optional operation). */
bool array_list_retain_all_custom(ArrayList *list, void **elements, int count,
																	int (*compare_func)(void *a, void *b));

/* Replaces the element at the specified position in 
	 this list with the specified element. */
void* array_list_set(ArrayList *list, int index, void *data);

/* Size of list */
int array_list_size(ArrayList *list);

/* Returns a view of the portion of this list between the 
	 specified fromIndex, inclusive, and toIndex, exclusive. */
ArrayList* array_list_sub_list(ArrayList *list, int from, int to);

/* Returns a view of the portion of this list between the 
	 specified fromIndex, inclusive, and toIndex, exclusive. */
ArrayList* array_list_sub_list_deep(ArrayList *list, int from, int to,
																							void *(*copy_func)(void *data));

/* Returns an array containing all of the elements in this 
	 list in proper sequence (from first to last element). deep specifies
	 whether or not to make a deep copy of the data elements */
void** array_list_to_array(ArrayList *list);

/* Returns an array containing all of the elements in this 
	 list in proper sequence (from first to last element). deep specifies
	 whether or not to make a deep copy of the data elements */
void** array_list_to_array_deep(ArrayList *list, void *(*copy_func)(void *data));

/* Method that frees the list, all nodes and 
	 underlying data in the nodes IF deep is true, otherwise
	 it takes care of the list and the nodes */
void array_list_free(ArrayList *list, bool deep);

/* Method that frees the list, all nodes and. Calls destroy_func
	 on every data pointer it has for custom cleanup. Since we're 
	 giving the user the option for custom cleanup, no need to specify
	 whether the cleanup is deep or shallow. */
void array_list_free_custom(ArrayList *list, void (*destroy_func)(void *data));

/* method in the place of iterator. Style copied from Glib */
void array_list_for_each(ArrayList *list, void (*operation)(void *data));

#endif /* __ARRAYLIST_H__ */
