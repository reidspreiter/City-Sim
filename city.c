#include "city.h"

Node* createNode(char type) {
    Node *n = malloc(sizeof(Node));
    n->type = type;
    n->size = 0;
    n->right = NULL;
    n->left = NULL;
    n->up = NULL;
    n->down = NULL;
    return n;
}

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

List* createList() {
    List *l = malloc(sizeof(List));
    l->head = NULL;
    l->nextList = NULL;
    return l;
}

void printList(List list) {
    Node *curr = list.head;
    while (curr != NULL) {
        printf("%c", curr->type);
        if (curr->type == 'R' || curr->type == 'I' || curr->type == 'C') {
            printf("%i  ", curr->size);
        } else {
            printf("%c  ", curr->type);
        }
        curr = curr->right;
    }
    printf("\n");
}

City createCity() {
    City c;
    c.layout = createList();
    c.population = 0;
    c.workers = 0;
    c.goods = 0;
    c.pollution = 0;
    return c;
}

void printCity(City city) {
    system("cls");
    List *currList = city.layout;
    while (currList != NULL) {
        printList(*currList);
        currList = currList->nextList;
    }
    printf("Pop: %i\n", city.population);
    printf("Workers: %i\n", city.workers);
    printf("Goods: %i\n\n", city.goods);
}

void appendList(List *city, List *list) {
    
    if (city->head == NULL) {
        city->head = list->head;
        return;
    }
    List *curr = city;
    while (curr->nextList != NULL) {
        curr = curr->nextList;
    }
    curr->nextList = list;

    // set up and down pointers
    Node *top = curr->head;
    Node *bottom = curr->nextList->head;
    while (top != NULL && bottom != NULL) {
        top->down = bottom;
        bottom->up = top;
        top = top->right;
        bottom = bottom->right;
    }
}

int setLayout(List *city, char *filename) {
    
    FILE * layout;
    layout = fopen(filename, "r");
    
    if (layout == NULL) {
        fprintf(stderr, "Error opening file: %s\n", strerror(errno));
        return ERRoR;
    }

    char buffer[MAX_SIZE];

    while(fgets(buffer, MAX_SIZE, layout)) {
        List *row = createList();
        for (int i = 0; i < strlen(buffer); i += 2) {
            appendNode(row, buffer[i]);
        }
        appendList(city, row);
    }

    fclose(layout);
    return 0;
}