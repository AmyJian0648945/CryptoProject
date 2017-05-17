#include <stdio.h>
#include <string.h>
#include "globals.h"
#include "auxiliaries.h"


////////////////////////////////////////////////////////////////////////////////////////////////////
////////////  This routine copies the samples of the input array to the output array   /////////////
////////////////////////////////////////////////////////////////////////////////////////////////////

void CopyArray(const size16_t input[], size16_t output[], const size16_t length)
{
	size16_t i;
	for (i = 0; i < length; i++) output[i] = input[i];
	return;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////  This routine takes the input and spilts into even and odd samples  ////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////

void SplitSamples (const size16_t * restrict input, const size16_t input_length, size16_t * restrict even_samples, size16_t * restrict odd_samples)
{
	size32_t i;

	#pragma MUST_ITERATE(MIN_COUNT,MAX_COUNT,MIN_COUNT)
	#pragma UNROLL(MIN_COUNT)
	for (i=0;i<input_length/2; i++)
	{
		even_samples[i] = input[2*i];
		odd_samples[i] = input[2*i+1];
	}	
	return;	
}

////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////    This routine comines even and odd samples into a single output   ////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////

void CombineSamples (const size16_t even_samples[], const size16_t odd_samples[], const size16_t input_length, size16_t output[])
{
	size32_t i;

	#pragma MUST_ITERATE(MIN_COUNT,MAX_COUNT,MIN_COUNT)
	#pragma UNROLL(MIN_COUNT)
	for (i=0; i<input_length; i++)
	{
		output[2*i] = even_samples[i];
		output[2*i+1] = odd_samples[i];
	}
	return;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////                This routine is used to print an array               ////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////

void PrintSignal(const char* name, const size16_t signal[], const size16_t length)
{
	size32_t i;

	for (i = 0; i < length; i++)
	{
		printf("%s[%hi] = %x, ", name, i, signal[i]);
	}
	printf("\n");
	return;
}
 

////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////          This routine adds input elements of two arrays             ////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////

void Add(const size16_t input1[], const size16_t input2[], size16_t output[], const size16_t length)
{
	size32_t i;

	#pragma MUST_ITERATE(MIN_COUNT,MAX_COUNT,MIN_COUNT)
	#pragma UNROLL(MIN_COUNT)
	for (i=0; i<length; i++) output[i] = (short)((long)input1[i] + (long)input2[i]);
	return;	
}

////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////         This routine subtracts input elements of two arrays         ////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////

void Subtract(const size16_t input1[], const size16_t input2[], size16_t output[], const size16_t length)
{
	size32_t i;

	#pragma MUST_ITERATE(MIN_COUNT,MAX_COUNT,MIN_COUNT)
	#pragma UNROLL(MIN_COUNT)
	for (i=0; i<length; i++) output[i] = (short)((long)input1[i] - (long)input2[i]);
	return;	
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//////  This routine convolves two inputs with two filters in an overlap and save fashion.   ///////
////////////////////////////////////////////////////////////////////////////////////////////////////

void DoubleConvolution(const size16_t * restrict input1, const size16_t * restrict input2, const size16_t input_length, size16_t * restrict overlap1, size16_t * restrict overlap2, const size16_t * restrict filter1, const size16_t * restrict filter2, const size16_t filter_length, size16_t * restrict output1, size16_t * restrict output2)
{

	size32_t n;
	size32_t samples11, samples21, samples31, filters11, filters21, filters31;
	size32_t sum11, sum21, sum31;

	size32_t samples12, samples22, samples32, filters12, filters22, filters32;
	size32_t sum12, sum22, sum32;

	size16_t input_ext1[BUFFERSIZE >> log_2];
	size16_t input_ext2[BUFFERSIZE >> log_2];

	memset(input_ext1, 0, sizeof(input_ext1));
	memset(input_ext2, 0, sizeof(input_ext2));

	#pragma MUST_ITERATE(MIN_COUNT,MAX_COUNT,MIN_COUNT)
	#pragma UNROLL(MIN_COUNT)
	for (n=0; n < input_length; n++)												// zero padding
	{
		input_ext1[n+filter_length-1] = input1[n];
		input_ext2[n+filter_length-1] = input2[n];
	}

	#pragma MUST_ITERATE(OUTER_LOOP_COUNT_MIN,OUTER_LOOP_COUNT_MAX,MIN_COUNT)
	#pragma UNROLL(MIN_COUNT)
	for (n = 0; n < input_length + filter_length - 1; n++)
	{

		samples11 = _pack2(input_ext1[n+filter_length-1], input_ext1[n+filter_length-2]);
		samples21 = _pack2(input_ext1[n+filter_length-3], input_ext1[n+filter_length-4]);
		samples31 = _pack2(input_ext1[n+filter_length-5], input_ext1[n+filter_length-6]);

		filters11 = _pack2(filter1[0], filter1[1]);
		filters21 = _pack2(filter1[2], filter1[3]);
		filters31 = _pack2(filter1[4], filter1[5]);

		sum11 = _dotp2(samples11, filters11);
		sum21 = _dotp2(samples21, filters21);
		sum31 = _dotp2(samples31, filters31);

		samples12 = _pack2(input_ext2[n+filter_length-1], input_ext2[n+filter_length-2]);
		samples22 = _pack2(input_ext2[n+filter_length-3], input_ext2[n+filter_length-4]);
		samples32 = _pack2(input_ext2[n+filter_length-5], input_ext2[n+filter_length-6]);

		filters12 = _pack2(filter2[0], filter2[1]);
		filters22 = _pack2(filter2[2], filter2[3]);
		filters32 = _pack2(filter2[4], filter2[5]);

		sum12 = _dotp2(samples12, filters12);
		sum22 = _dotp2(samples22, filters22);
		sum32 = _dotp2(samples32, filters32);
		
		output1[n] = (size16_t) ((sum11+sum21+sum31) >> log_32768);
		output2[n] = (size16_t) ((sum12+sum22+sum32) >> log_32768);
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////

	output1[0] = output1[0] + overlap1[0];
	output1[1] = output1[1] + overlap1[1];
	output1[2] = output1[2] + overlap1[2];
	output1[3] = output1[3] + overlap1[3];
	output1[4] = output1[4] + overlap1[4];

	output2[0] = output2[0] + overlap2[0];
	output2[1] = output2[1] + overlap2[1];
	output2[2] = output2[2] + overlap2[2];
	output2[3] = output2[3] + overlap2[3];
	output2[4] = output2[4] + overlap2[4];

	////////////////////////////////////////////////////////////////////////////////////////////////////

	overlap1[0] = output1[input_length];
	overlap1[1] = output1[input_length+1];
	overlap1[2] = output1[input_length+2];
	overlap1[3] = output1[input_length+3];
	overlap1[4] = output1[input_length+4];

	overlap2[0] = output2[input_length];
	overlap2[1] = output2[input_length+1];
	overlap2[2] = output2[input_length+2];
	overlap2[3] = output2[input_length+3];
	overlap2[4] = output2[input_length+4];

	////////////////////////////////////////////////////////////////////////////////////////////////////

	return;
}

