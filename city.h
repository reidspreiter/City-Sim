#ifndef CITY_H
#define CITY_H

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

enum {MAX_SIZE = 100, ERROR = -1};

typedef struct node {
    char type;
    struct node *next;
} Node;

typedef struct list {
    Node *head;
    struct list *nextList;
} List;

Node* createNode(char type);
void appendNode(List *list, char type);

List* createList();
void appendList(List *city, List *list);
void printList(List list);
void printCity(List list);

int setLayout(List *city, char *filename);

#endif