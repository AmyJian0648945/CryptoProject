#ifndef FORMATTING_H
#define FORMATTING_H

#include <stdint.h>

/* Reformatting the array 
	From 8 bit words to 16 bit words.
	uint8_t *input = array of 8 bit words (input).
	uint16_t *output = array of 16 bit words (output).
	size = 2 * number of elements in input
		 = number of elements in output
*/
void from8to16(uint8_t *input, uint16_t *output, uint16_t size);
/* Reformatting the array.
	From 16 bit words to 8 bit words.
	Inputs:
		uint16_t *input = array of 16 words (input).
		uint8_t *output = array of 8 words (output).
		size = number of elements in input
			 = 2 * number of elements in output
*/
void from16to8(uint16_t *input, uint8_t *output, uint16_t size);

#endif


