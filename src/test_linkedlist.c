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

static void setup_empty_list(void) {
	list = linked_list_new();
}

static void setup_list_with_items(LinkedList *l) {

	l = linked_list_new();
	linked_list_add(l, &a);
	linked_list_add(l, &b);
	linked_list_add(l, &c);
	printf("Set up total list with 3 items.");
}

static void setup_list_with_items2(LinkedList **l) {

	*l = linked_list_new();
	linked_list_add(*l, &a);
	linked_list_add(*l, &b);
	linked_list_add(*l, &c);
	printf("Set up total list with 3 items.");
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

void (*setup)(LinkedList **l) = &setup_list_with_items2;

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

//	CU_set_output_filename("linked_list");
	CU_basic_run_tests();
	CU_cleanup_registry();
	LinkedList *list2;
	return CU_get_error();
}

