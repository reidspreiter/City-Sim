/*
 * File: cityGrowth.c
 * Description: Define the cityGrowth function,
 * its corresponding thread functions, and growth requirements.
 */

#include "cityGrowth.h"

pthread_t residential, industrial, commercial;
pthread_mutex_t mutex;
pthread_cond_t grow;

/* 
 * To increase the size of a node, it must be surrounded by a 
 * specific number of nodes of a specific size
 * 
 * A node of size 3 must be surrounded by surroundingRequirement[3] 
 * nodes of size sizeRequirement[3] or more.
 * 
 * In other words, a node of size 3 must be surrounded by 
 * 6 nodes of size >= 3 to increase
 */
int surroundingRequirements[5] = {1, 2, 4, 6, 8}; 
int sizeRequirements[5] = {1, 1, 2, 3, 4};


/* Wrapper function to manage each growth thread */
void growCity(City *city) {

    pthread_cond_init(&grow, NULL);
    pthread_mutex_init(&mutex, NULL);

    pthread_create(&residential, NULL, growResidential, city);
    pthread_create(&industrial, NULL, growIndustrial, city);
    pthread_create(&commercial, NULL, growCommercial, city);

    pthread_join(residential, NULL);
    pthread_join(industrial, NULL);
    pthread_join(commercial, NULL);

    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&grow);
} 


/* Grows residential nodes under specific conditions */
void *growResidential(void *cityParam) {

    City *city = cityParam;
    while (1) {

        pthread_mutex_lock(&mutex);
        int currRpop = city->residentialPop;
        List *currList = city->layout;
        while (currList != NULL) {

            Node *curr = currList->head;
            while (curr != NULL) {

                /* 
                 * Halt residential growth if there are enough 
                 * workers to grow industrial and commercial
                 */
                while (city->workers > 1) {
                    pthread_cond_wait(&grow, &mutex);
                    if (city->growthLimit) {
                        pthread_mutex_unlock(&mutex);
                        return 0;
                    }
                }

                if (curr->type == 'R' && curr->size < 5 && checkSurroundings(curr)) {
                    curr->size++;
                    city->residentialPop++;
                    city->workers++;
                    printCity(*city);
                    pthread_cond_broadcast(&grow);
                }
                curr = curr->right;
            }
            currList = currList->nextList;
        }

        /* If no residential growth, stop the city growth process entirely */
        if (city->residentialPop == currRpop) {
            city->growthLimit = true;
            pthread_cond_broadcast(&grow);
            pthread_mutex_unlock(&mutex);
            return 0;
        }
        pthread_mutex_unlock(&mutex);
    }
}


/* Grows industrial nodes under specific conditions */
void *growIndustrial(void *cityParam) {

    City *city = cityParam;
    while (1) {

        pthread_mutex_lock(&mutex);
        int currIpop = city->industrialPop;
        List *currList = city->layout;
        while (currList != NULL) {

            Node *curr = currList->head;
            while (curr != NULL) {

                /* 
                 * Halt industrial growth if there aren't enough 
                 * workers to grow industrial, or if there are 
                 * enough to grow commercial
                 */
                while (city->workers < 2 || (city->workers > 0 && city->goods > 0)) {
                    pthread_cond_wait(&grow, &mutex);
                    if (city->growthLimit) {
                        pthread_mutex_unlock(&mutex);
                        return 0;
                    }
                }

                if (curr->type == 'I' && curr->size < 5 && checkSurroundings(curr)) {
                    curr->size++;
                    city->industrialPop++;
                    city->goods++;
                    city->workers -= 2;
                    printCity(*city);
                    pthread_cond_broadcast(&grow);
                }
                curr = curr->right;
            }
            currList = currList->nextList;
        }

        /* If no industrial growth, stop the city growth process entirely */
        if (city->industrialPop == currIpop) {
            city->growthLimit = true;
            pthread_cond_broadcast(&grow);
            pthread_mutex_unlock(&mutex);
            return 0;
        }
        pthread_mutex_unlock(&mutex);
    }
}


/* Grows commercial nodes under specific conditions */
void *growCommercial(void *cityParam) {

    City *city = cityParam;
    while (1) {

        pthread_mutex_lock(&mutex);
        int currCpop = city->commercialPop;
        List *currList = city->layout;
        while (currList != NULL) {

            Node *curr = currList->head;
            while (curr != NULL) {

                /* 
                 * Halt commercial growth if there aren't enough 
                 * workers or goods to grow commercial
                 */
                while (city->workers == 0 || city->goods == 0) {
                    pthread_cond_wait(&grow, &mutex);
                    if (city->growthLimit) {
                        pthread_mutex_unlock(&mutex);
                        return 0;
                    }
                }

                if (curr->type == 'C' && curr->size < 5 && checkSurroundings(curr)) {
                    curr->size++;
                    city->commercialPop++;
                    city->goods--;
                    city->workers--;
                    printCity(*city);
                    pthread_cond_broadcast(&grow);
                }
                curr = curr->right;
            }
            currList = currList->nextList;
        }

        if (city->commercialPop == currCpop) {
            city->growthLimit = true;
            pthread_cond_broadcast(&grow);
            pthread_mutex_unlock(&mutex);
            return 0;
        }
        pthread_mutex_unlock(&mutex);
    }
}


/* Checks if a surrounding node has the size to warrant an increase */
bool checkDensity(Node *node, char type, int size, int requiredSize) {

    if (node == NULL) {
        return false;
    }
    if (node->type == type && node->size >= requiredSize) {
        return true;
    } 

    /* Power lines count if size is 0 */
    if ((node->type == 'T' || node->type == '#') && size == 0) {
        return true;
    }
    return false;
}


/* Checks a node's surroundings to see if the node's size should increase*/
bool checkSurroundings(Node *node) {

    char type = node->type;
    int size = node->size;
    int requiredSize = sizeRequirements[node->size];
    int surroundingCellsOfSize = 0;

    if (node->right != NULL) {
        if (checkDensity(node->right, type, size, requiredSize))
            surroundingCellsOfSize++;
        if (checkDensity(node->right->up, type, size, requiredSize))
            surroundingCellsOfSize++;
        if (checkDensity(node->right->down, type, size, requiredSize)) 
            surroundingCellsOfSize++;
    }
    if (node->left != NULL) {
        if (checkDensity(node->left, type, size, requiredSize))
            surroundingCellsOfSize++;
        if (checkDensity(node->left->up, type, size, requiredSize))
            surroundingCellsOfSize++;
        if (checkDensity(node->left->down, type, size, requiredSize)) 
            surroundingCellsOfSize++;
    }
    if (checkDensity(node->up, type, size, requiredSize)) {
        surroundingCellsOfSize++;
    }
    if (checkDensity(node->down, type, size, requiredSize)) {
        surroundingCellsOfSize++;
    }

    if (surroundingCellsOfSize >= surroundingRequirements[node->size]) {
        return true;
    }
    return false;
}