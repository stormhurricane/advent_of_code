#include <stdlib.h>
//#include <stdio.h>

typedef struct Node {
    void* data;
    struct Node *next;
} Node;

typedef struct LinkedList{
    size_t length;
    struct Node *head;
} LinkedList;

LinkedList* createLinkedList() {
    LinkedList *list = (LinkedList*) malloc(sizeof(LinkedList));

    if (!list) {
        list = (LinkedList*) malloc(sizeof(LinkedList));
        if (!list) {
            return NULL;
        }
    }

    list->length = 0;
    list->head = NULL;

    return list;
}

void destroyList(LinkedList *list) {
    if (!list) return;

    Node *current = list->head;
    Node *next = NULL;

    while (current) {
        next = current;
        current = current->next;
        free(next);
    }

    free(list);
}

void destroyListAndValues(LinkedList *list) {
    if (!list) return;

    Node *current = list->head;
    Node *next = NULL;

    while (current) {
        next = current;
        current = current->next;
        free(current->data);
        free(next);
    }
    free(list);
}

int listAppendValue(LinkedList *list, void* data) {
    if (!list || !data) return 0;
   
    Node *current = list->head;
    Node *newNode = (Node*) malloc(sizeof(Node));

    if (!newNode) return 0;

    newNode->data = data;
    newNode->next = NULL;

    if (!current) {
        list->head = newNode;
        list->length++;
        return 1;
    }

    while (current->next) {
        current = current->next;
    }
    current->next  = newNode;

    list->length++;
    return list->length;
}

int listInsertValueAtN(LinkedList *list, void *data, size_t n) {
    if (!list || !data) return 0;
    if (n > (list->length)) return 0;
    
    Node *newNode = (Node*) malloc(sizeof(Node));

    if (!newNode) return 0;

    newNode->data = data;
    newNode->next = NULL;

    if (n == 0) {
        Node* head = list->head;
        list->head = newNode;
        newNode->next = head;
        list->length++;
        return n++;
    }

    Node *current = list->head;
    size_t count;
    for (count = 0; count < n - 1; count++) {
        if (!current) {
           free(newNode);
           return 0;
        }
        current = current->next;
    }

    if (!current) {
        free(newNode);
        return 0;
    }
    Node *after = current->next;
    current->next = newNode;
    newNode->next = after;
    list->length++;

    return n;
}

int listRemoveValue(LinkedList *list, void* data) {
    if (!list || !data) return 0;

    Node *previous = list->head;
    if (!previous) return 0;

    if (previous->data == data) {
        list->head = previous->next;

        previous->next = NULL;
        free(previous);
        list->length --;
        return 1;
    }

    while (previous->next) {
        if (previous->next->data == data) {
            break;
        }    
        previous = previous->next;
    }
    Node *toDelete = previous->next;

    previous->next = toDelete->next;

    toDelete->next = NULL;
    free(toDelete);
    list->length--;
    return 1;
} 

void printList(LinkedList* list);

/*
int main() {
    LinkedList *list = createLinkedList();

    int val1 = 7;
    int val2 = 0;
    int val3 = -1;

    listAppendValue(list, (void*) &val1);
    listAppendValue(list, (void*) &val2);

    //printList(list);

    listInsertValueAtN(list, (void*) &val3, 1);
    listAppendValue(list, (void*) &val1);

    printList(list);

    listRemoveValue(list, (void*) &val3);

    printList(list);

    destroyList(list);

    return 0;
}
*/


void printList(LinkedList* list) {
    Node *current = list->head;

    if (!list->head) {
        printf("Empty List\n");
        return;
    }

    printf("List with Length %u\n", list->length);

    while (current) {
        printf("%p with %d\n", current, *((int*) current->data));
        current = current->next;
    }

}
