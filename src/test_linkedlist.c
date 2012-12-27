#include "linkedlist.h"
#include <stdlib.h>
#include <stdbool.h>
#include "CUnit/Basic.h"
#include "CUnit/CUnit.h"

static LinkedList *list;

int init_suite_linked_list(void) {
	return 0;
}

int clean_suite_linked_list(void) {
	return 0;
}

static void setup_empty_list(void) {
	list = linked_list_new();
}

static void setup_list_with_items(void) {

	int a=5, b=6, c=7;

	list = linked_list_new();
	linked_list_add(list,&a);
	linked_list_add(list, &b);
	linked_list_add(list, &c);
}

static void destroy_old_list(void) {
	linked_list_free(list, false);
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
	destroy_old_list();
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
	destroy_old_list();
}

void test_linked_list_add_at(void) {

	int a = 2;
	int current_size;
	ListNode *current_node;

	setup_list_with_items();
	current_size = list->count;
	linked_list_add_at(list, &a, 1);
	CU_ASSERT(list->count == ++current_size);
	//make sure it was put in the right place
	current_node = list->head->next->next;
	CU_ASSERT(current_node->data == &a);

	destroy_old_list();
}

int main(int argc, char **argv) {
	CU_pSuite pSuite = NULL;
	if(CUE_SUCCESS != CU_initialize_registry())
		return CU_get_error();

	pSuite = CU_add_suite("LinkedList", init_suite_linked_list, 
																	clean_suite_linked_list);
	if(NULL == pSuite) {
		CU_cleanup_registry();
		return CU_get_error();
	}

	if(NULL == CU_add_test(pSuite, "Testing linked_list_new",
																	test_linked_list_new) ||
		 NULL == CU_add_test(pSuite, "Testing linked_list_add", 
																		test_linked_list_add) ||
		 NULL == CU_add_test(pSuite, "Testing linked_list_add_at",
		 																test_linked_list_add_at)) {
		CU_cleanup_registry();
		return CU_get_error();
	}

//	CU_set_output_filename("linked_list");
	CU_basic_run_tests();
	CU_cleanup_registry();
	return CU_get_error();
}

