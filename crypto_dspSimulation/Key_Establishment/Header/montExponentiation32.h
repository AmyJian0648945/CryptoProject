#ifndef	MONTEXPONENTIATION_H
#define MONTEXPONENTIATION_H

#include "additionalFunctions32.h"
#include "modularInverse32.h"
#include "modFunctions32.h"

#ifndef MAXLENGTH
#define MAXLENGTH 256
#endif

void montMultiplication( uint32_t *x, uint32_t *y, uint32_t *m, uint32_t *result, uint16_t mInvLastBit, uint16_t sizeM, uint16_t sizeR);
void montExp( uint32_t *x, uint32_t *m, uint32_t *e, uint32_t *result, uint16_t sizeX, uint16_t sizeM, uint16_t sizeE);

#endif

