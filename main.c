#include "city.h"

int main(void) {

    printf("Hello World\n");
    List *city = createList();

    for (int i = 0; i < 30; i++) {
        List *nums = createList();
        appendNode(nums, i);
        appendNode(nums, i+1);
        appendNode(nums, i+2);
        appendList(city, nums);
    }
    print2DList(*city);
    return 0;
}