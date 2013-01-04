#include "linkedlist.h"
#include <stdlib.h>
#include <stdbool.h>
#include "CUnit/Basic.h"
#include "CUnit/CUnit.h"

static LinkedList *list;

int a = 5, b = 6, c = 11;

static void print_list(LinkedList *list) {
	printf("Size of list= %d\n", list->count);
	ListNode *current_node = list->head->next;
	while(current_node->next) {
		printf("Value of data = %d.\n", *((int *) current_node->data));
		current_node = current_node->next;
	}
}

int init_suite_linked_list(void) {
	return 0;
}

int clean_suite_linked_list(void) {
	return 0;
}

static void setup_empty_list() {
	list = linked_list_new();
}

static void setup_list_with_items(LinkedList *l) {

	l = linked_list_new();
	linked_list_add(l, &a);
	linked_list_add(l, &b);
	linked_list_add(l, &c);
}

static void destroy_old_list(bool deep) {
	linked_list_free(list, deep);
}

void test_linked_list_new(void) {
	setup_empty_list();
	//list is already newed, so we can just use it
	// MUST destroy after each function to make it a 
	// proper unit test.
	CU_ASSERT(list->count == 0);
	CU_ASSERT(NULL != list->head);
	CU_ASSERT(NULL != list->tail);
	CU_ASSERT(list->head->next == list->tail);
	CU_ASSERT(list->tail->prev == list->head);
	CU_ASSERT(NULL == list->head->prev);
	CU_ASSERT(NULL == list->tail->next);
	destroy_old_list(false);
}

void test_linked_list_add(void) {	

	int a=5, b=6, c=7;
	ListNode *current_node;
	int current_size;

	setup_empty_list();
	current_size = list->count;
	linked_list_add(list,&a);
	CU_ASSERT(list->count == ++current_size);
	CU_ASSERT(list->head->next->data == &a);

	// add one more
	linked_list_add(list, &b);
	CU_ASSERT(list->count == ++current_size);
	current_node = list->head->next;
	CU_ASSERT(current_node->data == &a);
	CU_ASSERT(current_node->next->data == &b);

	// add one more node to be sure
	linked_list_add(list, &c);
	CU_ASSERT(list->count == ++current_size);
	current_node = list->head->next;
	CU_ASSERT(current_node->data == &a);
	current_node = current_node->next;
	CU_ASSERT(current_node->data == &b);
	CU_ASSERT(current_node->next->data == &c);
	destroy_old_list(false);
}

void test_linked_list_add_at(void) {

	int a = 2;
	int current_size;
	ListNode *current_node;

	setup_list_with_items(list);
	current_size = list->count;
	linked_list_add_at(list, &a, 1);
	CU_ASSERT(list->count == ++current_size);
	//make sure it was put in the right place
	current_node = list->head->next->next;
	CU_ASSERT(current_node->data == &a);

	destroy_old_list(false);
}

void test_linked_list_add_all(void) {
	int j = 1, k = 2, l = 6, m = 4;
	int* array[] = {&j, &k, &l, &m}; 
	void *test_data;

	setup_empty_list();
	linked_list_add_all(list,(const void **) array, 4);
	CU_ASSERT(list->count == 4);
	test_data = list->head->next->data;
	int *data = (int *) test_data;
	CU_ASSERT(*data == 1);
	destroy_old_list(false);
}

void test_linked_list_add_all_at(void) {
	int j = 1, k = 2, l = 6, m = 4;
	int *array[] = {&j, &k, &l, &m};
	int current_size;
	
	setup_list_with_items(list);
	current_size = list->count;
	linked_list_add_all_at(list, 1, (const void **) array, 4);
	current_size += 4;
	CU_ASSERT(current_size == list->count);
	// TODO: really test this
	destroy_old_list(false);
}

void test_linked_list_clear(void) {
	setup_list_with_items(list);
	linked_list_clear(list, false);
	CU_ASSERT(list->count == 0);
	CU_ASSERT(list->head->next == list->tail);
	CU_ASSERT(list->tail->prev == list->head);
}

void destroy_node(void *data) {
	int *intptr = (int *) data;
	free(intptr);
}

void test_linked_list_clear_custom(void) {
	int *test = malloc(sizeof(int));
	*test = 5;
	setup_empty_list();
	linked_list_add(list, (void *) test);
	linked_list_clear_custom(list, &destroy_node);
	CU_ASSERT(list->count == 0);
	CU_ASSERT(list->head->next == list->tail);
	CU_ASSERT(list->tail->prev == list->head);
}

void test_linked_list_clone(void) {

	ListNode *current_node, *current_node2;
	int i = 5, j = 7, k = 9;
	setup_empty_list();

	/* to the purist:
	Yes, I know I shouldn't be testing a data structure using other methods of 
	that data structure, but I wanted to give the data structure a work out
	so I am sorry that you have to see this. Don't think of these as unit tests;
	the goal is to fully test and give the structure a workout; this accomplishes that.
	*/
	linked_list_add(list, &i);
	linked_list_add(list, &j);
	linked_list_add(list, &k);
	LinkedList *new_list = linked_list_clone(list);
	current_node = new_list->head->next;
	current_node2 = list->head->next;
	while(current_node->next) {
		CU_ASSERT(current_node->data == current_node2->data);
		current_node = current_node->next;
		current_node2 = current_node2->next;
	}
	CU_ASSERT(list->head != new_list->head);
	CU_ASSERT(list->tail != new_list->tail);
	destroy_old_list(false);
}

void test_linked_list_clone_custom(void) {
}

void test_linked_list_contains(void) {
	int j = 1, k = 2, l = 6, m = 4;
	int test_out = 2;
	int* array[] = { &j, &k, &l, &m }; 

	setup_empty_list();

	linked_list_add_all(list,(const void **) array, 4);
	CU_ASSERT(linked_list_contains(list, &j));
	CU_ASSERT(linked_list_contains(list, &k));
	CU_ASSERT(linked_list_contains(list, &l));
	CU_ASSERT(linked_list_contains(list, &m));
	CU_ASSERT(!linked_list_contains(list, &test_out));
}

static int test_compare_contains_custom(void *a, void *b) {
	int *a1 = (int *) a;
	int *b1 = (int *) b;
	if(*a1 < *b1) return -1;
	else if(*a1 == *b1) return 0;
	else return 1;
}

void test_linked_list_contains_custom(void) {
	int j = 1, k = 2, l = 6, m = 4;
	int test_out = 2;
	int* array[] = { &j, &k, &l, &m }; 

	setup_empty_list();

	linked_list_add_all(list,(const void **) array, 4);
	CU_ASSERT(linked_list_contains_custom(list, &j, &test_compare_contains_custom));
	CU_ASSERT(linked_list_contains_custom(list, &k, &test_compare_contains_custom));
	CU_ASSERT(linked_list_contains_custom(list, &l, &test_compare_contains_custom));
	CU_ASSERT(linked_list_contains_custom(list, &m, &test_compare_contains_custom));
	CU_ASSERT(linked_list_contains_custom(list, &test_out, &test_compare_contains_custom));
}

void test_linked_list_get(void) {
}

void test_linked_list_index_of(void) {
}

void test_linked_list_index_of_custom(void) {
}

void test_linked_list_is_empty(void) {
}

void test_linked_list_last_index_of(void) {
}

void test_linked_list_last_index_of_custom(void) {
}

void test_linked_list_remove(void) {
}

void test_linked_list_remove_with_data(void) {
}

void test_linked_list_remove_with_data_custom(void) {
}

void test_linked_list_remove_all(void) {
}

void test_linked_list_remove_all_custom(void) {
}

void test_linked_list_retain_all(void) {
}

void test_linked_list_retain_all_custom(void) {
}

void test_linked_list_set(void) {
}

void test_linked_list_size(void) {
}

void test_linked_list_sub_list(void) {
}

void test_linked_list_sub_list_deep(void) {
}

void test_linked_list_to_array(void) {
}

void test_linked_list_to_array_deep(void) {
}

void test_linked_list_free(void) {
}

void test_linked_list_free_custom(void) {
}

int main(int argc, char **argv) {

	if(CUE_SUCCESS != CU_initialize_registry())
		return CU_get_error();

	CU_TestInfo linked_list_test_array [] = {
			{ "TestNew", test_linked_list_new },
			{ "TestAdd", test_linked_list_add },
			{ "TestAddAt", test_linked_list_add_at },
			{ "TestAddAll", test_linked_list_add_all },
			{ "TestAddAllAt", test_linked_list_add_all_at },
			{ "TestClear" , test_linked_list_clear },
			{ "TestClearCustom", test_linked_list_clear_custom },
			{ "TestClone", test_linked_list_clone },
			{ "TestCloneCustom", test_linked_list_clone_custom },
			{ "TestContains", test_linked_list_contains },
			{ "TestContainsCustom", test_linked_list_contains_custom },
			CU_TEST_INFO_NULL,
		};

	CU_SuiteInfo suites[] = {
		{ "LinkedListSuite", init_suite_linked_list, clean_suite_linked_list,
																									linked_list_test_array},
		CU_SUITE_INFO_NULL,
	};

	if(CUE_SUCCESS != CU_register_suites(suites)) {
		CU_cleanup_registry();
		return CU_get_error();
	}

	CU_basic_run_tests();
	CU_cleanup_registry();
	return CU_get_error();
}

