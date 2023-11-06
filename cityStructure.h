/*
 * File: cityStructure.h
 * Description: Declares the City structure
 * and corresponding functions.
 */

#ifndef CITYSTRUCTURE_H
#define CITYSTRUCTURE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <errno.h>
#include <string.h>
#include <windows.h>


typedef struct node {
    char type;
    int size;
    struct node *right, *left, *up, *down;
} Node;


typedef struct list {
    Node *head;
    struct list *nextList;
} List;


typedef struct city {
    List *layout;
    int residentialPop, industrialPop, commercialPop, workers, goods;
    bool growthLimit;
} City;


Node* createNode(char type);
List* createList();
City createCity();

void appendNode(List *list, char type);
void appendList(List *city, List *list);
bool setLayout(List *city, char *filename);
void printCity(City city);

#endif