/* This program reads in a layout.csv file and grows a city */

#include "cityGrowth.h"

int main(int argc, char *argv[]) {

    if (argc != 2) {
        fprintf(stderr, "Usage: ./a.exe <layout filename>");
        exit(EXIT_FAILURE);
    }

    City city = createCity();
    if (!setLayout(city.layout, argv[1])) {
        exit(EXIT_FAILURE);
    }

    printCity(city);
    growCity(&city);
    printf("What a wonderful city!\n");
    return 0;
}