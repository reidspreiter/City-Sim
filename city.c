#include "city.h"

Node* createNode(char type) {
    Node *n = malloc(sizeof(Node));
    n->type = type;
    n->population = 0;
    n->pollution = 0;
    n->next = NULL;
    n->prev = NULL;
    n->up = NULL;
    n->down = NULL;
    return n;
}

List* createList() {
    List *l = malloc(sizeof(List));
    l->head = NULL;
    l->next = NULL;
    return l;
}

City createCity() {
    City c;
    c.head = NULL;
    c.population = 0;
    c.workers = 0;
    c.goods = 0;
    c.pollution = 0;
    return c;
}

void appendNode(List *list, char type) {

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

void appendList(City *city, List *list) {

    if (city->head == NULL) {
        city->head = list;
    }

    List *curr = city->head;
    while (curr->next != NULL) {
        curr = curr->next;
    }
    curr->next = list;
}

void printCity(City city) {
    List *y = city.head;
    while (y != NULL) {
        Node *x = y->head;
        while (x != NULL) {
            printf("%c ", x->type);
        }
        printf("\n");
        y = y->next;
    }
    printf("\n");
}