#include "city.h"

Node* createNode(int type) {
    Node *n = malloc(sizeof(Node));
    n->type = type;
    n->next = NULL;
    return n;
}

void appendNode(List *list, int type) {

    if (list->head == NULL) {
        list->head = createNode(type);
        return;
    }

    Node *curr = list->head;
    while (curr->next != NULL) {
        curr = curr->next;
    }
    curr->next = createNode(type);
}

List* createList() {
    List *l = malloc(sizeof(List));
    l->head = NULL;
    l->nextList = NULL;
    return l;
}

void printList(List list) {
    Node *curr = list.head;
    while (curr != NULL) {
        printf("%i ", curr->type);
        curr = curr->next;
    }
    printf("\n");
}

void print2DList(List city) {
    List *currList = &city;
    while (currList != NULL) {
        printList(*currList);
        currList = currList->nextList;
    }
    printf("\n");
}

void appendList(List *city, List *list) {
    
    if (city->head == NULL) {
        city->head = list->head;
        return;
    }
    List *curr = city;
    while (curr->nextList != NULL) {
        curr = curr->nextList;
    }
    curr->nextList = list;
}
