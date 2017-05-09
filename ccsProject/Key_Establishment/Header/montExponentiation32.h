#ifndef	MONTEXPONENTIATION_H
#define MONTEXPONENTIATION_H

#include "additionalFunctions32.h"
#include "modularInverse32.h"
#include "modFunctions32.h"
#include "../../library/helpfulFunctions.h"

#ifndef MAXLENGTHLONG
#define MAXLENGTHLONG 64
#endif

#ifndef LENGTH
#define LENGTH 33
#endif

void mont(uint32_t *a, uint32_t *b, uint32_t *n, uint32_t *nInv, uint32_t *res, uint32_t SIZE, uint16_t sizeNInv, uint16_t samePointer);
void ADD(uint32_t *t, int i, uint32_t C, uint16_t size);
void SUB_COND(uint32_t *res, uint32_t *n, uint32_t SIZE);
void montMultiplication( uint32_t *x, uint32_t *y, uint32_t *m, uint32_t *result, uint16_t mInvLastBit, uint16_t sizeM, uint16_t sizeR, uint16_t middleR);
void montExp( uint32_t *x, uint32_t *m, uint32_t *e, uint32_t *result, uint16_t sizeX, uint16_t sizeM, uint16_t sizeE);

#endif


