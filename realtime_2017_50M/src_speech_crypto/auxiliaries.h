#ifndef AUXILIARIES_H
#define AUXILIARIES_H

#include <c6x.h>
#include "globals.h"

void CopyArray(const short input[], short output[], const short length);
void SplitSamples (const size16_t * restrict input, const size16_t input_length, size16_t * restrict even_samples, size16_t * restrict odd_samples);
void CombineSamples (const size16_t even_samples[], const size16_t odd_samples[], const size16_t input_length, size16_t output[]);
void PrintSignal(const char* name, const size16_t signal[], const size16_t length);
void Add(const size16_t input1[], const size16_t input2[], size16_t output[], const size16_t length);
void Subtract(const size16_t input1[], const size16_t input2[], size16_t output[], const size16_t length);
void Convolution(const size16_t * restrict input, const size16_t input_length, size16_t * restrict overlap, const size16_t * restrict filter, const size16_t filter_length, size16_t * restrict output);
void DoubleConvolution(const size16_t * restrict input1, const size16_t * restrict input2, const size16_t input_length, size16_t * restrict overlap1, size16_t * restrict overlap2, const size16_t * restrict filter1, const size16_t * restrict filter2, const size16_t filter_length, size16_t * restrict output1, size16_t * restrict output2);

#endif
