#include "city.h"

Node* createNode(char type) {
    Node *n = malloc(sizeof(Node));
    n->type = type;
    n->next = NULL;
    return n;
}

void appendNode(List *list, char type) {

    if (list->head == NULL) {
        list->head = createNode(type);
        return;
    }

    Node *curr = list->head;
    while (curr->next != NULL) {
        curr = curr->next;
    }
    curr->next = createNode(type);
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
        printf("%c ", curr->type);
        curr = curr->next;
    }
    printf("\n");
}

void printCity(List city) {
    List *currList = &city;
    while (currList != NULL) {
        printList(*currList);
        currList = currList->nextList;
    }
    printf("\n");
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
}

int setLayout(List *city, char *filename) {
    
    FILE * layout;
    layout = fopen(filename, "r");
    
    if (layout == NULL) {
        fprintf(stderr, "Error opening file: %s\n", strerror(errno));
        return ERROR;
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