#ifndef CITY_H
#define CITY_H

#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    char type;
    int population, pollution;
    struct node *next, *prev, *up, *down;
} Node;

typedef struct list {
    Node *head;
    struct list *next;
} List;

typedef struct city {
    List *head;
    int population, workers, goods, pollution;
} City;

Node* createNode(char type);

void appendNode(List *list, char type);

List* createList();

void appendList(City *city, List list);

City createCity();

#endif