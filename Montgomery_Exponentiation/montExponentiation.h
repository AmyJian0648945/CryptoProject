#ifndef	MONTEXPONENTIATION_H
#define MONTEXPONENTIATION_H

#include "additionalFunctions.h"
#include "modFunctions.h"
#include "modularInverse.h"
#define MAXLENGTH 128

void montMultiplication( uint16_t *x, uint16_t *y, uint16_t *m, uint16_t *result, uint16_t mInvLastBit, uint16_t sizeM, uint16_t sizeR);
void montExp( uint16_t *x, uint16_t *m, uint16_t *e, uint16_t *result, uint16_t sizeX, uint16_t sizeM, uint16_t sizeE);

#endif





