#ifndef GROWTH_H
#define GROWTH_H

#include <stdbool.h>
#include <pthread.h>
#include "city.h"

extern pthread_mutex_t mutex;
extern pthread_cond_t growI, growC;

void growResidential(City *city);
void *growIndustrial(void *cityParam);
void *growCommercial(void *cityParam);

#endif