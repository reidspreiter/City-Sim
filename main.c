#include "city.h"

int main(int argc, char *argv[]) {

    if (argc != 2) {
        fprintf(stderr, "Usage: ./a.exe <layout filename>");
        exit(EXIT_FAILURE);
    }

    List *city = createList();
    if (setLayout(city, argv[1]) == ERROR) {
        exit(EXIT_FAILURE);
    }
    
    printCity(*city);
    return 0;
}