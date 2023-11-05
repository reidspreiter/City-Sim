#include <windows.h>
#include "growth.h"

pthread_mutex_t mutex;
pthread_cond_t growI, growC;

int sizeRequirement[5] = {1, 1, 2, 3, 4};
int cellsRequired[5] = {1, 2, 4, 6, 8};  

bool checkDensity(Node *node, char type, int requiredSize) {
    if (node == NULL) {
        return false;
    }
    if (node->type == type && node->size >= requiredSize) {
        return true;
    } 
    if ((node->type == 'T' || node->type == '#') && node->size == 0) {
        return true;
    }
    return false;
}

bool checkSurroundings(Node *node) {
    char type = node->type;
    int requiredSize = sizeRequirement[node->size];
    int densityCells = 0;
    if (checkDensity(node->right, type, requiredSize))
        densityCells++;
    if (node->right != NULL && checkDensity(node->right->down, type, requiredSize))
        densityCells++;
    if (checkDensity(node->down, type, requiredSize))
        densityCells++;
    if (node->down != NULL && checkDensity(node->down->left, type, requiredSize))
        densityCells++;
    if (checkDensity(node->left, type, requiredSize))
        densityCells++;
    if (node->left != NULL && checkDensity(node->left->up, type, requiredSize))
        densityCells++;
    if (checkDensity(node->up, type, requiredSize))
        densityCells++;
    if (node->up != NULL && checkDensity(node->up->right, type, requiredSize))
        densityCells++;

    if (densityCells >= cellsRequired[node->size]) {
        return true;
    }
    return false;
}

void growResidential(City *city) {
    List *currList = city->layout;
    while (currList != NULL) {
        Node *curr = currList->head;
        while (curr != NULL) {
            if (curr->type == 'R' && curr->size < 5 && checkSurroundings(curr)) {
                curr->size++;
                city->population++;
                city->workers++;
                printCity(*city);
                Sleep(100);
            }
            curr = curr->right;
        }
        currList = currList->nextList;
    }
}

void *growIndustrial(void *cityParam) {
    City *city = cityParam;
    List *currList = city->layout;
    Node *curr = NULL;
    while (1) {
        pthread_mutex_lock(&mutex);

        while (city->workers < 2) {
            pthread_cond_wait(&growI, &mutex);
        }

        while (currList != NULL) {
            curr = currList->head;
            while (curr != NULL) {
                if (checkSurroundings(curr)) {
                    curr->size++;
                    city->goods++;
                    city->workers -= 2;
                    printCity(*city);
                }
                curr = curr->right;
            }
            currList = currList->nextList;
        }

        pthread_mutex_unlock(&mutex);
    }
}

void *growCommercial(void *cityParam) {
    City *city = cityParam;
    List *currList = city->layout;
    Node *curr = NULL;
    while (1) {
        pthread_mutex_lock(&mutex);

        while (city->workers < 1 && city->goods < 1) {
            pthread_cond_wait(&growC, &mutex);
        }

        while (currList != NULL) {
            curr = currList->head;
            while (curr != NULL) {
                if (checkSurroundings(curr)) {
                    curr->size++;
                    city->goods--;
                    city->workers--;
                    printCity(*city);
                }
                curr = curr->right;
            }
            currList = currList->nextList;
        }

        pthread_mutex_unlock(&mutex);
    }
}