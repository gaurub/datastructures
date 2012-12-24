#ifndef __LIST_H__
#define __LIST_H__

typedef struct Node_t {
    struct Node_t *next;
    struct Node_t *prev;
    void *data;    
} Node;

typedef struct List_t {
    Node *head;
    Node *tail;
    int count;
} List;

List* new_list();
void free_list_deep(List *list);
void free_list_shallow(List *list);
int list_size(List *list);
Node* insert_node_with_data(List *list, void *data);
Node* node_at(List *list, int index);
Node* node_with_data(List *list, void *data); // this should take a comparison function as a parameter


#endif /* __LIST_H__ */
