#include "growth.h"

int main(int argc, char *argv[]) {

    if (argc != 2) {
        fprintf(stderr, "Usage: ./a.exe <layout filename>");
        exit(EXIT_FAILURE);
    }

    City city = createCity();
    if (setLayout(city.layout, argv[1]) == ERRoR) {
        exit(EXIT_FAILURE);
    }
    printCity(city);

    for (int i = 0; i < 200; i++) {
        growResidential(&city);
    }

    // pthread_cond_init(&growI, NULL);
    // pthread_cond_init(&growC, NULL);

    // pthread_t industrialThread, commercialThread;

    // pthread_mutex_init(&mutex, NULL);

    // pthread_create(&industrialThread, NULL, growIndustrial, &city);
    // pthread_create(&commercialThread, NULL, growCommercial, &city);

    // pthread_join(industrialThread, NULL);
    // pthread_join(commercialThread, NULL);

    // pthread_mutex_destroy(&mutex);
    // pthread_cond_destroy(&growC);
    // pthread_cond_destroy(&growI);
    return 0;
}