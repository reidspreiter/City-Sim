#ifndef CITY_H
#define CITY_H

#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int type;
    struct node *next;
} Node;

typedef struct list {
    Node *head;
    struct list *nextList;
} List;

Node* createNode(int type);
void appendNode(List *list, int type);

List* createList();
void appendList(List *city, List *list);
void printList(List list);
void print2DList(List list);

#endif