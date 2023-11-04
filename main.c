#include "city.h"

int main(void) {

    City city = createCity();
    List temp;
    temp.head = NULL;
    appendNode(&temp, 6);
    appendNode(&temp, 7);
    appendNode(&temp, 8);
    appendList(&city, temp);
    appendNode(&temp, 6);
    appendNode(&temp, 7);
    appendNode(&temp, 8);
    appendList(&city, temp);
    appendNode(&temp, 6);
    appendNode(&temp, 7);
    appendNode(&temp, 8);
    appendList(&city, temp);
    printCity(city);
    return 0;
}