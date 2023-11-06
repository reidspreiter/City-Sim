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

    pthread_cond_init(&growR, NULL);
    pthread_cond_init(&growI, NULL);
    pthread_cond_init(&growC, NULL);

    pthread_t residentialThread, industrialThread, commercialThread;

    pthread_mutex_init(&mutex, NULL);

    pthread_create(&residentialThread, NULL, growResidential, &city);
    pthread_create(&industrialThread, NULL, growIndustrial, &city);
    pthread_create(&commercialThread, NULL, growCommercial, &city);

    pthread_join(residentialThread, NULL);
    printf("Exited R\n");
    pthread_exit(&industrialThread);
    pthread_exit(&commercialThread);
    printf("Exited other threads R\n");

    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&growC);
    pthread_cond_destroy(&growI);
    pthread_cond_destroy(&growR);
    return 0;
}