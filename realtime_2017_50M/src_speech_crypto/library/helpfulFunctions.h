#ifndef HELPFULFUNCTIONS_H
#define	HELPFULFUNCTIONS_H

#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include "macros.h"
#include <time.h>



void concat(uint8_t*, uint8_t*, uint16_t, uint16_t);
void XOR(uint8_t*, uint8_t*, uint8_t*, uint16_t);

uint16_t timeData(); 
    /* Obtain current time to microseconds */
void hexToString(uint8_t*, uint8_t*, size_t); 
    /* hex --> String (in capital letters) */
void copyArray(uint8_t*, uint8_t*, uint16_t, uint16_t); 
    /* Copies array over from input to output, starting from "index" */
void copyArrayFrom0(uint8_t*, uint8_t*, uint16_t);




/* Printing Functions */
void printArray(uint8_t*, uint16_t);    
    /* prints the array */
void printArrayNoSpaces(uint8_t*, uint16_t);
void printArrayNoSpaces16(uint16_t*, uint16_t);
void printArrayNoSpaces32(uint32_t*, uint16_t);

void printCharNoSpaces(uint8_t*, uint16_t);
void printChar(uint8_t*, uint16_t);

/* For ease of debugging */
void seeTheDifference(uint8_t*, uint8_t*, uint16_t);
    /* subtracts the two inputs; if they are the same, */




#endif






