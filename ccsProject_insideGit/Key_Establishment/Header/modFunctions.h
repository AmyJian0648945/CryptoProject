#ifndef MODFUNCTIONS_H
#define MODFUNCTIONS_H

#include "additionalFunctions.h"

#ifndef MAXLENGTH
#define MAXLENGTH 256
#endif
/* Maximum size for an array */

#ifndef MAXIMUMLENGTH
#define MAXIMUMLENGTH 2048
#endif
/* Macro for the binary array w for squareProduct and multiplication */

uint16_t positionMSB(uint16_t *array, uint16_t size);
void from2to16(uint16_t *binaryString, uint16_t *output, uint16_t size);
void mod(uint16_t *a, uint16_t *N, uint16_t *result, uint16_t sizeA, uint16_t sizeModulus);
void squareProduct(uint16_t *a, uint16_t *product, uint16_t sizeA);
void multiplication(uint16_t *x, uint16_t *y, uint16_t *product, uint16_t sizeX, uint16_t sizeY);
void modSquare(uint16_t *a, uint16_t *m, uint16_t *result, uint16_t sizeA, uint16_t sizeM);
void modFaster(uint16_t *x, uint16_t *m, uint16_t sizeX, uint16_t sizeM);


#endif

