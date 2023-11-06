/*
 * File: cityStructure.c
 * Description: Defines functions for creating, printing, 
 * and setting the layout List of the City structure.
 */

#include "cityStructure.h"

const int MAX_SIZE = 100;


/* Initialize node of specified type */
Node* createNode(char type) {
    Node *n = malloc(sizeof(Node));
    n->type = type;
    n->size = 0;
    n->right = n->left = n->up = n->down = NULL;
    return n;
}


/* Initialize list */
List* createList() {
    List *l = malloc(sizeof(List));
    l->head = NULL;
    l->nextList = NULL;
    return l;
}


/* Initialize city */
City createCity() {
    City c;
    c.layout = createList();
    c.residentialPop = c.industrialPop = c.commercialPop = 0;
    c.workers = c.goods = 0;
    c.growthLimit = false;
    return c;
}


/* Append node of specified type to specified list */
void appendNode(List *list, char type) {

    if (list->head == NULL) {
        list->head = createNode(type);
        return;
    }

    Node *curr = list->head;
    while (curr->right != NULL) {
        curr = curr->right;
    }
    curr->right = createNode(type);
    curr->right->left = curr;
}


/* Append specified list to specified city layout */
void appendList(List *cityLayout, List *list) {
    
    if (cityLayout->head == NULL) {
        cityLayout->head = list->head;
        return;
    }

    List *curr = cityLayout;
    while (curr->nextList != NULL) {
        curr = curr->nextList;
    }
    curr->nextList = list;

    Node *topNode = curr->head;
    Node *bottomNode = curr->nextList->head;
    while (topNode != NULL && bottomNode != NULL) {
        topNode->down = bottomNode;
        bottomNode->up = topNode;
        topNode = topNode->right;
        bottomNode = bottomNode->right;
    }
}


/* Read specified filename into specified city layout*/
bool setLayout(List *cityLayout, char *filename) {
    
    FILE *layout;
    layout = fopen(filename, "r");
    if (layout == NULL) {
        fprintf(stderr, "Error opening file: %s\n", strerror(errno));
        return false;
    }

    char buffer[MAX_SIZE];
    while(fgets(buffer, MAX_SIZE, layout)) {
        List *row = createList();
        for (int i = 0; i < strlen(buffer); i += 2) {
            appendNode(row, buffer[i]);
        }
        appendList(cityLayout, row);
    }

    fclose(layout);
    return true;
}

/* Print specified city */
void printCity(City city) {

    FILE *output;
    output = fopen("output.txt", "w");
    if (output == NULL) {
        fprintf(stderr, "Error opening output.txt in write mode: %s\n", strerror(errno));
        return;
    }

    List *currList = city.layout;
    while (currList != NULL) {
        
        Node *curr = currList->head;
        while (curr != NULL) {

            /* Only print R, I, and C nodes if size > 0 */
            if (curr->size > 0) {
                fprintf(output, "%c%i  ", curr->type, curr->size);
            } else if (curr->type != 'R' && curr->type != 'I' && curr->type != 'C') {
                fprintf(output, "%c%c  ", curr->type, curr->type);
            } else {
                fprintf(output, "    ");
            }
            curr = curr->right;
        }
        fprintf(output, "\n");
        currList = currList->nextList;
    }

    fprintf(output, "Residential: %i\n", city.residentialPop);
    fprintf(output, "Industrial: %i\n", city.industrialPop);
    fprintf(output, "Commercial: %i\n", city.commercialPop);

    fclose(output);
    output = fopen("output.txt", "r");
    if (output == NULL) {
        fprintf(stderr, "Error opening output.txt in read mode: %s\n", strerror(errno));
        return;
    }

    fseek(output, 0, SEEK_END);
    int fileLength = ftell(output);
    fseek(output, 0, SEEK_SET);

    char *buffer = malloc(sizeof(char) * (fileLength + 1));
    char c;
    for (int i = 0; (c = fgetc(output)) != EOF; i++) {
        buffer[i] = c;
    }

    fclose(output);
    system("cls");
    puts(buffer);
    Sleep(10);
}