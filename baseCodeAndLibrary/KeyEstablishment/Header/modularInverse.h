#ifndef MODULARINVERSE_H
#define MODULARINVERSE_H

#include "additionalFunctions.h"

#ifndef MAXLENGTH
#define MAXLENGTH 2048
#endif

uint16_t signedSubtraction(uint16_t *x, uint16_t *y, uint16_t arrayLength, uint16_t sign1, uint16_t sign2);
void modularInverse(uint16_t *x, uint16_t *y, uint16_t *inverse, uint16_t sizeX, uint16_t sizeModulus);

#endif



