#ifndef MODULARINVERSE_H
#define MODULARINVERSE_H

#include "../../library/macros.h"
#include "additionalFunctions32.h"

uint16_t signedSubtraction(uint32_t *x, uint32_t *y, uint16_t arrayLength, uint16_t sign1, uint16_t sign2);
void modularInverse(uint32_t *x, uint32_t *y, uint32_t *inverse, uint16_t sizeX, uint16_t sizeModulus);

#endif

