#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
    int x_coordinate;
    int y_coordinate;
    struct Node *next, *previous;
} Node;

typedef struct List{
    int length;
    Node *head, *tail;
} List;

void printNode(Node *node) {
    printf("Node: (%p)\nx: %d\t\t y: %d\n", node, node->x_coordinate, node->y_coordinate);
    printf("Next: %p\t\tPrevious: %p\n\n", node->next, node->previous);
}

void addToList(List *list, Node *node) {
    if (!list || !node) return;

    if (list->length == 0) {
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

void performFunctionOnList(List *list, void (*op)(Node*)) {
    if (!list || !op) return;
    if (list->length == 0) return;

    Node *current = list->head;

    while (current) {
        op(current);
        current = current->next;
    }
}

List* createList() {
    List *newList = malloc(sizeof(List));
    newList->head = NULL;
    newList->tail = NULL;
    newList->length = 0;
    
    Node *first = malloc(sizeof(Node));
    first->x_coordinate = 0;
    first->y_coordinate = 0;

    addToList(newList, first);

    return newList;
}

void makeListToSet(List *list) {
    if (!list || list->length == 0) return;
    
    Node *current = list->head;

    while (current) {
        Node *next = current->next;
        while (next) {
            if (current->y_coordinate == next->y_coordinate 
                && current->x_coordinate == next->x_coordinate) {
                Node *afterNext = next->next;
                removeFromList(list, next);
                next = afterNext;
            } else {
                next = next->next;
            }
        }
        current = current->next;
    }
}

int main() {
    // Open Filepointer
    FILE *fp = fopen("input.txt", "r");

    // if file not found, pointer is null
    if (!fp) {
        printf("No File found!");
        return 1;
    }

    char c;
    List *list = createList();

    // check file, char by char
    do {
        c = fgetc(fp);

        Node *newNode = malloc(sizeof(Node));
        newNode->x_coordinate = list->tail->x_coordinate;
        newNode->y_coordinate = list->tail->y_coordinate;

        if (c == '^') {
            newNode->x_coordinate++;
        }
        else if (c == 'v') {
            newNode->x_coordinate--;
        }
        else if (c == '>') {
            newNode->y_coordinate++;
        }  
        else if (c == '<') { 
            // c == '<'
            newNode->y_coordinate--;
        }
        else {
            continue;
        }
        
        addToList(list, newNode);
    }
    while (c != EOF) ;

    fclose(fp);

    makeListToSet(list);

    printf("Santa visits %d unique houses if alone", list->length);

    return 0;
}