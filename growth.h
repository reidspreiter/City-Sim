#ifndef GROWTH_H
#define GROWTH_H

#include <pthread.h>
#include "city.h"

extern pthread_mutex_t mutex;
extern pthread_cond_t growR, growI, growC;

void *growResidential(void *cityParam);
void *growIndustrial(void *cityParam);
void *growCommercial(void *cityParam);

#endif