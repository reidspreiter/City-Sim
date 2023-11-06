#include "growth.h"

pthread_mutex_t mutex;
pthread_cond_t growR, growI, growC;

int sizeRequirement[5] = {1, 1, 2, 3, 4};
int cellsRequired[5] = {1, 2, 4, 6, 8};  

bool checkDensity(Node *node, char type, int size, int requiredSize) {
    if (node == NULL) {
        return false;
    }
    if (node->type == type && node->size >= requiredSize) {
        return true;
    } 
    if ((node->type == 'T' || node->type == '#') && size == 0) {
        return true;
    }
    return false;
}

bool checkSurroundings(Node *node) {
    char type = node->type;
    int size = node->size;
    int requiredSize = sizeRequirement[node->size];
    int densityCells = 0;
    if (checkDensity(node->right, type, size, requiredSize))
        densityCells++;
    if (node->right != NULL && checkDensity(node->right->down, type, size, requiredSize))
        densityCells++;
    if (checkDensity(node->down, type, size, requiredSize))
        densityCells++;
    if (node->down != NULL && checkDensity(node->down->left, type, size, requiredSize))
        densityCells++;
    if (checkDensity(node->left, type, size, requiredSize))
        densityCells++;
    if (node->left != NULL && checkDensity(node->left->up, type, size, requiredSize))
        densityCells++;
    if (checkDensity(node->up, type, size, requiredSize))
        densityCells++;
    if (node->up != NULL && checkDensity(node->up->right, type, size, requiredSize))
        densityCells++;

    if (densityCells >= cellsRequired[node->size]) {
        return true;
    }
    return false;
}

void *growResidential(void *cityParam) {
    City *city = cityParam;
    while (city->grownR) {
        city->grownR = false;
        List *currList = city->layout;
        while (currList != NULL) {
            Node *curr = currList->head;
            while (curr != NULL) {
                printf("R: Locking\n");
                pthread_mutex_lock(&mutex);
                while (city->workers > 1) {
                    printf("R: Sleeping\n");
                    pthread_cond_wait(&growR, &mutex);
                    printf("R: Awake\n");
                }
                if (curr->type == 'R' && curr->size < 5 && checkSurroundings(curr)) {
                    printf("R: Increasing\n");
                    city->grownR = true;
                    curr->size++;
                    city->population++;
                    city->workers++;
                    pthread_cond_signal(&growC);
                    pthread_cond_signal(&growI);
                    printCity(*city);
                }
                pthread_mutex_unlock(&mutex);
                curr = curr->right;
            }
            currList = currList->nextList;
        }
    }
    printf("Exiting\n");
}

void *growIndustrial(void *cityParam) {
    City *city = cityParam;
    while (1) {
        List *currList = city->layout;
        while (currList != NULL) {
            Node *curr = currList->head;
            while (curr != NULL) {
                printf("I: Locking\n");
                pthread_mutex_lock(&mutex);
                while (city->workers < 2 || (city->workers > 0 && city->goods > 0)) {
                    printf("I: Sleeping\n");
                    pthread_cond_wait(&growI, &mutex);
                    printf("I: Awake\n");
                }
                if (curr->type == 'I' && curr->size < 5 && checkSurroundings(curr)) {
                    printf("I: Increasing\n");
                    curr->size++;
                    city->goods++;
                    city->workers -= 2;
                    pthread_cond_signal(&growC);
                    pthread_cond_signal(&growR);
                    printCity(*city);
                }
                pthread_mutex_unlock(&mutex);
                curr = curr->right;
            }
            currList = currList->nextList;
        }
    }
}

void *growCommercial(void *cityParam) {
    City *city = cityParam;
    while (1) {
        List *currList = city->layout;
        while (currList != NULL) {
            Node *curr = currList->head;
            while (curr != NULL) {
                printf("C: Locking\n");
                pthread_mutex_lock(&mutex);
                while (city->workers == 0 || city->goods == 0) {
                    printf("C: Sleeping\n");
                    pthread_cond_wait(&growC, &mutex);
                    printf("C: Awake\n");
                }
                if (curr->type == 'C' && curr->size < 5 && checkSurroundings(curr)) {
                    printf("C: Increasing\n");
                    curr->size++;
                    city->goods--;
                    city->workers--;
                    pthread_cond_signal(&growI);
                    pthread_cond_signal(&growR);
                    printCity(*city);
                }
                pthread_mutex_unlock(&mutex);
                curr = curr->right;
            }
            currList = currList->nextList;
        }
    }
}