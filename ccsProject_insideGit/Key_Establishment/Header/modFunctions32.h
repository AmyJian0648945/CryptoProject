#ifndef MODFUNCTIONS_H
#define MODFUNCTIONS_H

#include "additionalFunctions32.h"

#ifndef MAXLENGTH
#define MAXLENGTH 256
#endif
/* Maximum size for an array */

#ifndef MAXIMUMLENGTH
#define MAXIMUMLENGTH 2048
#endif
/* Macro for the binary array w for squareProduct and multiplication */

uint16_t positionMSB(uint32_t *array, uint16_t size);
void from2to32(uint16_t *binaryString, uint32_t *output, uint16_t size);
void mod(uint32_t *a, uint32_t *N, uint32_t *result, uint16_t sizeA, uint16_t sizeModulus);
void squareProduct(uint32_t *a, uint32_t *product, uint16_t sizeA);
void multiplication(uint32_t *x, uint32_t *y, uint32_t *product, uint16_t sizeX, uint16_t sizeY);
void modSquare(uint32_t *a, uint32_t *m, uint32_t *result, uint16_t sizeA, uint16_t sizeM);
void modFaster(uint32_t *x, uint32_t *m, uint16_t sizeX, uint16_t sizeM);
void modMult(uint32_t *x, uint32_t *y, uint32_t *m, uint32_t *result, uint16_t sizeX, uint16_t sizeY, uint16_t sizeM);

#endif

