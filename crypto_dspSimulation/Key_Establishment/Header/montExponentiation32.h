#ifndef	MONTEXPONENTIATION_H
#define MONTEXPONENTIATION_H

#include "additionalFunctions32.h"
#include "modularInverse32.h"
#include "modFunctions32.h"

#ifndef MAXLENGTH
#define MAXLENGTH 256
#endif

#include <time.h>
#include <stdint.h>

void ADD( uint32_t *t, int i, uint32_t C);
void SUB_COND( uint32_t *res, uint32_t *n, uint16_t size);
void mont( uint32_t *x, uint32_t *y, uint32_t *m, uint32_t *mInv, uint32_t *result, uint32_t sizeM);
void montMultiplication( uint32_t *x, uint32_t *y, uint32_t *m, uint32_t *result, uint16_t mInvLastBit, uint16_t sizeM, uint16_t sizeR);
void montExp( uint32_t *x, uint32_t *m, uint32_t *e, uint32_t *result, uint16_t sizeX, uint16_t sizeM, uint16_t sizeE);

#endif

