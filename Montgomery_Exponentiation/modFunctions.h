#ifndef MODFUNCTIONS_H
#define MODFUNCTIONS_H

#include "additionalFunctions.h"
#define MAXLENGTH 128
#define MAXIMUMLENGTH 300

uint16_t positionMSB(uint16_t *array, uint16_t size);
void from2to16(uint16_t *binaryString, uint16_t *output, uint16_t size);
void mod(uint16_t *a, uint16_t *N, uint16_t *result, uint16_t sizeA, uint16_t sizeModulus);
void squareProduct(uint16_t *a, uint16_t *product, uint16_t sizeA);
void multiplication(uint16_t *x, uint16_t *y, uint16_t *product, uint16_t sizeX, uint16_t sizeY);
void division(uint16_t *x, uint16_t *y, uint16_t *resultDiv, uint16_t *resultRem, uint16_t sizeX, uint16_t sizeY);
void modSquare(uint16_t *a, uint16_t *m, uint16_t *result, uint16_t sizeA, uint16_t sizeM);
void modFaster(uint16_t *x, uint16_t *m, uint16_t sizeX, uint16_t sizeM);
void modExp(uint16_t *x, uint16_t *m, uint16_t *e, uint16_t *result, uint16_t sizeX, uint16_t sizeM, uint16_t sizeE);



#endif

