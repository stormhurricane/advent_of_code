#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Node{
    int x_coordinate;
    int y_coordinate;
    struct Node *next, *previous;
} Node;

typedef struct List{
    int length;
    Node *head, *tail;
} List;

// helper
void printNode(Node *node) {
    printf("Node: (%p)\nx: %d\t\t y: %d\n", node, node->x_coordinate, node->y_coordinate);
    printf("Next: %p\t\tPrevious: %p\n\n", node->next, node->previous);
}


void appendToList(List *list, Node *node) {
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

    appendToList(newList, first);

    return newList;
}

// remove duplicates from list
void removeDuplicates(List *list) {
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

// naively add two lists together
List* addListToList(List *listOne, List *listTwo) {
    if (!listOne || listOne->length == 0) {
        if (listTwo && listTwo->length > 0) 
        return listTwo;
    }

    if (!listTwo || listTwo->length == 0) {
        if (listOne && listOne->length > 0) 
        return listOne;
    }

    if (!listOne && !listTwo) return NULL;
 
    List *newList = malloc(sizeof(List));
    
    newList->head = listOne->head;
    newList->tail = listTwo->tail;
    
    newList->length = listOne->length + listTwo->length;

    listOne->tail->next = listTwo->head;
    listTwo->head->previous = listOne->tail;

    return newList;
}

int main() {
    // Open Filepointer
    FILE *fp = fopen("input.txt", "r");

    // if file not found, pointer is null
    if (!fp) {
        printf("No File found!");
        return 1;
    }

    clock_t start = clock();

    char c;
    int i = 0;
    List *santaOnlyList = createList();
    List *santaList = createList();
    List *roboSantaList = createList();

    // check file, char by char
    do {
        c = fgetc(fp);

        // two nodes, one for single santa and two santa lists
        Node *newNode = malloc(sizeof(Node));
        Node *copyNode = malloc(sizeof(Node));
        
        // get the coordinates of the most recent
        if (i % 2 == 0) {
            newNode->x_coordinate = santaList->tail->x_coordinate;
            newNode->y_coordinate = santaList->tail->y_coordinate;
        }
        else {
            newNode->x_coordinate = roboSantaList->tail->x_coordinate;
            newNode->y_coordinate = roboSantaList->tail->y_coordinate;
        }

        copyNode->x_coordinate = santaOnlyList->tail->x_coordinate;
        copyNode->y_coordinate = santaOnlyList->tail->y_coordinate;

        // increment necessary value;
        if (c == '^') {
            newNode->x_coordinate++;
            copyNode->x_coordinate++;
        }
        else if (c == 'v') {
            newNode->x_coordinate--;
            copyNode->x_coordinate--;
        }
        else if (c == '>') {
            newNode->y_coordinate++;
            copyNode->y_coordinate++;
        }  
        else if (c == '<') { 
            // c == '<'
            newNode->y_coordinate--;
            copyNode->y_coordinate--;
        }
        else {
            continue;
            free(newNode);
            free(copyNode);
        }

        // add to respective lists
        appendToList(santaOnlyList, copyNode);

        if (i % 2 == 0){
            appendToList(santaList, newNode);
        }
        else {
            appendToList(roboSantaList, newNode);
        }

        i++;
    }
    while (c != EOF) ;

    fclose(fp);

    removeDuplicates(santaOnlyList);

    List *completeList = addListToList(santaList, roboSantaList);
    removeDuplicates(completeList);

    clock_t end = clock();

    printf("Santa visits %d unique houses alone\n", santaOnlyList->length);
    printf("Santa and Robot Santa visit %d unique houses", completeList->length);
    float seconds = (float)(end - start) / CLOCKS_PER_SEC;
    printf("\nNeeded Time: %f seconds", seconds);

    return 0;
}