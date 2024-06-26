#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
    void *data;
    struct Node *next, *previous;
} Node;

typedef struct List{
    int length;
    Node *head, *tail;
} List;

List* createList() {
    List* list = malloc(sizeof(List));
    list->length = 0;
    list->head = NULL;
    list->tail = NULL;

    return list;
}

void appendToList(List *list, Node *node) {
    if (!list || !node) return;

    if (list->length == 0) {
        printf("Appended head!\n");
        node->previous = NULL;
        node->next = NULL;
        list->head = node;
        list->tail = node;
    } else {
        list->tail->next = node;
        node->previous = list->tail;
        
        node->next = NULL;
        list->tail = node;
    }

    list->length ++;
}

// node is always in list
void removeFromList(List *list, Node *node) {
    if (!list || !node) return;
    if (list->length == 0) return;

    if (list->head == node && list->tail == node) {
        list->head = NULL;
        list->tail = NULL;
    }
    else if (list->head == node) {
        if (node->next) {
            node->next->previous = NULL;
        }
        list->head = node->next;
        node->next = NULL;
    }
    else if (list->tail == node) {
        if (node->previous) {
            node->previous->next = NULL;
        }
        list->tail = node->previous;
        node->previous = NULL;
    }
    else {
        if (node->previous) {
            node->previous->next = node->next;
        }
        if (node->next) {
            node->next->previous = node->previous; 
        }

        node->next = NULL;
        node->previous = NULL;
    }
    
    list->length --;
    free(node);
}

void printNode(Node *node) {
    if (!node) return;

    printf("Print Node %p\t(Data %d)\n", node, node->data);
    printf("\tprev: %p\t\tnext: %p\n", node->previous, node->next);
}

void performFunctionOnList(List *list, void (*op)(Node*)) {
    if (!list || !op) return;
    if (list->length == 0) return;

    Node *current = list->head;

    while (current) {
        op(current);
        current = current->next;
    }
}

void removeDuplicates(List *list) {
    if (!list || list->length == 0) return;

    Node *current = list->head;
    int inner = 0;

    while (current) {
        printf("current data: %d\n", current->data);
        Node *next = current->next;
        while (next) {
            printf("next data: %d\n", next->data);
            if (current->data == next->data) {
                Node *afterNext = next->next;
                removeFromList(list, next);
                next = afterNext;
            }
            else {
                next = next->next;
            }
            inner++;
        }
        printf("performed %d inner loops for %d\n", inner, current->data);
        current = current->next;
    }
}

int main() {
    // create list
    List* list = createList();

    Node *first = malloc(sizeof(Node));
    first->data = (int*) 1;
    Node *second = malloc(sizeof(Node));
    second->data = (int*) 2;
    Node *third = malloc(sizeof(Node));
    third->data = (int*) 3;
    Node *fourth = malloc(sizeof(Node));
    fourth->data = (int*) 1;
    Node *fifth = malloc(sizeof(Node));
    fifth->data = (int*) 1;
    Node *sixth = malloc(sizeof(Node));
    sixth->data = (int*) 2;
    Node *extra = malloc(sizeof(Node));
    extra->data = (int*) 1;


    appendToList(list, first);
    appendToList(list, extra);
    appendToList(list, second);
    appendToList(list, third);
    appendToList(list, fourth);
    appendToList(list, fifth);
    appendToList(list, sixth);

    removeDuplicates(list);

    printf("After removing head and last:\nLength: %d\nhead: %p\t\ttail: %p\n", list->length, list->head, list->tail);
    performFunctionOnList(list, &printNode);

    return 0;
}