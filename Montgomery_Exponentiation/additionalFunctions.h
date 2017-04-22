#ifndef ADDITIONALFUNCTIONS_H
#define ADDITIONALFUNCTIONS_H

#include <stdint.h>
#include <stdio.h>
#include <string.h>
#define MAXLENGTH 128

void printArray16(uint16_t *array, char *word, uint16_t arrayLength);
void zerosArray(uint16_t *result, uint16_t arrayLength);
uint16_t isBiggerThan(uint16_t *number1, uint16_t *number2, uint16_t size);
uint16_t isBiggerThanOrEqual(uint16_t *number1, uint16_t *number2, uint16_t size);
uint16_t numberIsZero(uint16_t *number, uint16_t numberOfElements);
void copyArray16(uint16_t *original, uint16_t *copiedVersion, uint16_t arrayLength);
void flipArray(uint16_t *input, uint16_t size);
void divideByTwo(uint16_t *input, uint16_t size);
void multiplyByTwo(uint16_t *input, uint16_t size);
void addition(uint16_t *number1, uint16_t *number2, uint16_t *result, uint16_t size);
void subtraction(uint16_t *number1, uint16_t *number2, uint16_t *result, uint16_t size);
uint16_t subtractionWithSign(uint16_t *number1, uint16_t *number2, uint16_t *result, uint16_t size);

#endif


