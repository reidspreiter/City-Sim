/*
 * File: cityGrowth.h
 * Description: Declares growth related functions
 */

#ifndef CITYGROWTH_H
#define CITYGROWTH_H

#include <pthread.h>
#include "cityStructure.h"

void growCity(City *city);
void *growResidential(void *cityParam);
void *growIndustrial(void *cityParam);
void *growCommercial(void *cityParam);
bool checkSurroundings(Node *node);
bool checkDensity(Node *node, char type, int size, int requiredSize);

#endif