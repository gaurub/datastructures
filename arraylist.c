#include "include/arraylist.h"
#include <stdlib.h>
#include <stdio.h>

#define NYI(x) fprintf(stderr, "Function %s not implemented.", x);

ArrayList* array_list_new() {	
	NYI(__func__);
    return NULL;
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
