#ifndef MODULARINVERSE_H
#define MODULARINVERSE_H

#include <stdint.h>
#include "additionalFunctions.h"
#define MAXLENGTH 128

uint16_t signedSubtraction(uint16_t *x, uint16_t *y, uint16_t arrayLength, uint16_t sign1, uint16_t sign2);
void modularInverse(uint16_t *x, uint16_t *y, uint16_t *inverse, uint16_t sizeX, uint16_t modLength);

#endif



