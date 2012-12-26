#ifndef __LINKEDLIST_H__
#define __LINKEDLIST_H__

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

/* Append element to end of list */
ListNode* linked_list_add(LinkedList *list, void *data);

/* Insert element at specified index. 0 is the start */
ListNode* linked_list_add(LinkedList *list, int index, void *data)

/* Creates a new, empty list */
LinkedList* linked_list_new();

/* Method that frees the list, all nodes and 
underlying data in the nodes */
void linked_list_free_deep(LinkedList *list);

/* Method that frees the list and all nodes.
The data in the nodes is not freed */
void linked_list_free_shallow(LinkedList *list);

/* Method that returns size in a thread-safe method */
int linked_list_size(LinkedList *list);

ListNode* linked_list_node_at(LinkedList *list, int index);
ListNode* linked_list_node_with_data(LinkedList *list, void *data); // this should take a comparison function as a parameter


#endif /* __LINKEDLIST_H__ */
