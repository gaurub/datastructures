#include "include/arraylist.h"
#include <stdlib.h>
#include <stdio.h>

#define NYI(x) fprintf(stderr, "Function %s not implemented.", x);
#define START_SIZE 8

ArrayList* array_list_new() {	

	ArrayList *list = malloc(sizeof(ArrayList));
	if(!list) {
		fprintf(stderr, "Could not allocate memory for list.");
		return NULL;
	}

	list->array = malloc(START_SIZE * sizeof(void *));
	if(!list->array) {
		fprintf(stderr, "Could not allocate memory for array for list.");
		free(list);
		return NULL;
	}

	list->count = 0;
	list->capacity = START_SIZE;

	return list;
}

bool array_list_add(ArrayList *list, const void *data) {
	NYI(__func__);
    return false;
}

int main(int argc, char **argv) {
	ArrayList *list;
	void *data;
	list = array_list_new();
	array_list_add(list, data);
	return 0;
}
