#ifndef CITY_H
#define CITY_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <errno.h>
#include <string.h>
#include <windows.h>

enum {MAX_SIZE = 100, ERRoR = -1};

typedef struct node {
    char type;
    int size;
    struct node *right;
    struct node *left;
    struct node *up;
    struct node *down;
} Node;

typedef struct list {
    Node *head;
    struct list *nextList;
} List;

typedef struct city {
    List *layout;
    int population, workers, goods, pollution;
    bool grownR, grownI, grownC;
} City;

Node* createNode(char type);
void appendNode(List *list, char type);

List* createList();
void appendList(List *city, List *list);
void printList(List list);

City createCity();
int setLayout(List *city, char *filename);
void printCity(City city);

#endif