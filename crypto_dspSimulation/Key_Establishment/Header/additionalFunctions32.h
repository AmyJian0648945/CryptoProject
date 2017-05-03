#ifndef ADDITIONALFUNCTIONS_H
#define ADDITIONALFUNCTIONS_H

#include <stdint.h>
#include <stdio.h>
#include <string.h>

#ifndef MAXLENGTH
#define MAXLENGTH 256
#endif

void printArray32(uint32_t *array, char *word, uint16_t arrayLength);
void printArray8(uint8_t *array, char *word, uint16_t arrayLength);
void zerosArray(uint32_t *result, uint16_t arrayLength);
void zerosArray16(uint16_t *result, uint16_t arrayLength);
uint16_t isBiggerThan(uint32_t *number1, uint32_t *number2, uint16_t size);
uint16_t isBiggerThanOrEqual(uint32_t *number1, uint32_t *number2, uint16_t size);
uint16_t numberIsZero(uint32_t *number, uint16_t numberOfElements);
void copyArray32(uint32_t *original, uint32_t *copiedVersion, uint16_t arrayLength);
void copyArray8(uint8_t *original, uint8_t *copiedVersion, uint16_t arrayLength);
void divideByTwo(uint32_t *input, uint16_t size);
void multiplyByTwo(uint32_t *input, uint16_t size);
void addition(uint32_t *number1, uint32_t *number2, uint32_t *result, uint16_t size);
void subtraction(uint32_t *number1, uint32_t *number2, uint32_t *result, uint16_t size);
uint16_t subtractionWithSign(uint32_t *number1, uint32_t *number2, uint32_t *result, uint16_t size);

#endif


