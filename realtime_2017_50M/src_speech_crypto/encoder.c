#include <stdio.h>
#include "globals.h"
#include "encoder.h"
#include "auxiliaries.h"

////////////////////////////////////////////////////////////////////////////////////////////////////
///////  This routine initializes the parameter arrays with the values defined in the macros ////////
////////////////////////////////////////////////////////////////////////////////////////////////////


void InitParametersEnc ()
{

	MUS[0] = MU1;
	MUS[1] = MU2;
	MUS[2] = MU3;

	LOG_PHIS[0] = LOG_PHI1;
	LOG_PHIS[1] = LOG_PHI2;
	LOG_PHIS[2] = LOG_PHI3;

	NBITS[0] = NBITS1;
	NBITS[1] = NBITS2;
	NBITS[2] = NBITS3;
	return;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////        	This routine performs analysis filtering (stage 1) 	      ///////////////
////////////////        of the input and results in two outputs.                      ///////////////
////////////////////////////////////////////////////////////////////////////////////////////////////

void AnalysisStageOne (size16_t input[], size16_t overlap1[], size16_t overlap2[], size16_t * prev_sample, size16_t output1[], size16_t output2[])
{
	size16_t even_samples[BUFFERSIZE >> log_2];
	size16_t odd_samples[BUFFERSIZE >> log_2];

	size16_t c1[BUFFERSIZE >> log_2];
	size16_t c2[BUFFERSIZE >> log_2];
	
	size32_t i;


	even_samples[0] = input[0];                       								 		   // splitting the samples into even and odd ones
	odd_samples[0] = input[1];
	even_samples[1] = input[2];
	odd_samples[1] = input[3];
	even_samples[2] = input[4];
	odd_samples[2] = input[5];
	even_samples[3] = input[6];
	odd_samples[3] = input[7];
	even_samples[4] = input[8];
	odd_samples[4] = input[9];
	even_samples[5] = input[10];
	odd_samples[5] = input[11];
	even_samples[6] = input[12];
	odd_samples[6] = input[13];
	even_samples[7] = input[14];
	odd_samples[7] = input[15];
	even_samples[8] = input[16];
	odd_samples[8] = input[17];
	even_samples[9] = input[18];
	odd_samples[9] = input[19];
	
	for ((i=BUFFERSIZE >> log_4) - 1; i>0 ;i--) odd_samples[i] = odd_samples[i-1];
	odd_samples[0] = *prev_sample;
	*prev_sample = input[(BUFFERSIZE >> log_2) - 1];

	DoubleConvolution(even_samples, odd_samples, BUFFERSIZE >> log_4, overlap1, overlap2, h1_even, h1_odd, FILSIZE >> log_2, c1, c2);

	
	output1[0] = c1[0] + c2[0];
	output1[1] = c1[1] + c2[1];
	output1[2] = c1[2] + c2[2];
	output1[3] = c1[3] + c2[3];
	output1[4] = c1[4] + c2[4];
	output1[5] = c1[5] + c2[5];
	output1[6] = c1[6] + c2[6];
	output1[7] = c1[7] + c2[7];
	output1[8] = c1[8] + c2[8];
	output1[9] = c1[9] + c2[9];

	output2[0] = c1[0] - c2[0];
	output2[1] = c1[1] - c2[1];
	output2[2] = c1[2] - c2[2];
	output2[3] = c1[3] - c2[3];
	output2[4] = c1[4] - c2[4];
	output2[5] = c1[5] - c2[5];
	output2[6] = c1[6] - c2[6];
	output2[7] = c1[7] - c2[7];
	output2[8] = c1[8] - c2[8];
	output2[9] = c1[9] - c2[9];
	


	return;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////        	This routine performs analysis filtering (stage 2) 	          ///////////////
////////////////        of the input and results in two outputs.                      ///////////////
////////////////////////////////////////////////////////////////////////////////////////////////////

void AnalysisStageTwo (size16_t input[], size16_t overlap1[], size16_t overlap2[], size16_t * prev_sample, size16_t output1[], size16_t output2[])
{
	size16_t even_samples[BUFFERSIZE >> log_4];
	size16_t odd_samples[BUFFERSIZE >> log_4];

	size16_t c1[BUFFERSIZE >> log_4];
	size16_t c2[BUFFERSIZE >> log_4];

	size32_t i;

	even_samples[0] = input[0];                       								 		   // splitting the samples into even and odd ones
	odd_samples[0] = input[1];
	even_samples[1] = input[2];
	odd_samples[1] = input[3];
	even_samples[2] = input[4];
	odd_samples[2] = input[5];
	even_samples[3] = input[6];
	odd_samples[3] = input[7];
	even_samples[4] = input[8];
	odd_samples[4] = input[9];
	
	for (i=(BUFFERSIZE >> log_8)-1; i>0 ;i--) odd_samples[i] = odd_samples[i-1];
	odd_samples[0] = *prev_sample;
	*prev_sample = input[(BUFFERSIZE >> log_4)-1];
	DoubleConvolution(even_samples, odd_samples, BUFFERSIZE >> log_8, overlap1, overlap2, h2_even, h2_odd, FILSIZE >> log_2, c1, c2);

	
	output1[0] = c1[0] + c2[0];
	output1[1] = c1[1] + c2[1];
	output1[2] = c1[2] + c2[2];
	output1[3] = c1[3] + c2[3];
	output1[4] = c1[4] + c2[4];

	output2[0] = c1[0] - c2[0];
	output2[1] = c1[1] - c2[1];
	output2[2] = c1[2] - c2[2];
	output2[3] = c1[3] - c2[3];
	output2[4] = c1[4] - c2[4];

	return;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////         This routine performs predictive coding of the input       ////////////////             
////////////////////////////////////////////////////////////////////////////////////////////////////

void Encode (const size16_t * restrict s, size16_t * restrict d_primes, size16_t * delta, size16_t * s_star, size16_t * sum, size16_t * restrict z, size16_t band)
{
	size16_t d_prime;
	size32_t i, j;
	//size16_t sum;
	size16_t d;

	size16_t log_phi = LOG_PHIS[band-1];                      								 		   // band value starts from 1 and it is used for parameter array indexing.
	size16_t nbits = NBITS[band-1];
	size16_t mu = MUS[band-1];
	

	#pragma MUST_ITERATE(BUFFERSIZE >> log_8,BUFFERSIZE >> log_8,BUFFERSIZE >> log_8)
	#pragma UNROLL(BUFFERSIZE >> log_8)
	for (i=0; i<BUFFERSIZE >> log_8; i++)
	{
		d = s[i] - *s_star;
		z[i] = d / (*delta);
		if (z[i]>(1<<(nbits-1))-1) z[i] = (1<<(nbits-1))-1;
		if (z[i]< -(1<<(nbits-1))) z[i] = -(1<<(nbits-1));
		d_prime = z[i] * (*delta);
		*sum-=d_primes[0];
		#pragma MUST_ITERATE(WINDOWSIZE-1,WINDOWSIZE-1,WINDOWSIZE-1)
		#pragma UNROLL(WINDOWSIZE-1)
		for (j=0;j<WINDOWSIZE-1;j++)
		{
			d_primes[j]=d_primes[j+1];
		}

		d_primes[WINDOWSIZE-1] = _abs(d_prime);
		*sum+=d_primes[WINDOWSIZE-1];
		*delta = (((*sum<<log_phi))>>log_windowsize)>>log_256;
		*delta = (*delta<DELTAMIN) ? DELTAMIN : *delta;
		//*delta = (*delta>DELTAMAX) ? DELTAMAX : *delta;
		*s_star = (mu*(d_prime + *s_star))>>log_256;
	}
	
	return;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////        	This routine performs analysis filtering, encoding   	      ///////////////
///////////////         and packing of bits for transmission.                         ///////////////
////////////////////////////////////////////////////////////////////////////////////////////////////

void FirstPhase (size16_t buffer[], struct FirstPhaseChunk * chunk_L, struct FirstPhaseChunk * chunk_R, size16_t pCompressed[])
{
		

	SplitSamples (buffer, BUFFERSIZE, chunk_L->c, chunk_R->c);

	//////////////////////////////////////////////////////////////////////////////////////////////////

	AnalysisStageOne (chunk_L->c, chunk_L->overlap1, chunk_L->overlap2, &chunk_L->prev_sample, chunk_L->c12, chunk_L->c34);              // left channel filtering (stage 1).

	//////////////////////////////////////////////////////////////////////////////////////////////////

	AnalysisStageOne (chunk_R->c, chunk_R->overlap1, chunk_R->overlap2, &chunk_R->prev_sample, chunk_R->c12, chunk_R->c34);              // right channel filtering (stage 1).

	//////////////////////////////////////////////////////////////////////////////////////////////////

	AnalysisStageTwo (chunk_L->c12, chunk_L->overlap112, chunk_L->overlap212, &chunk_L->prev_sample12, chunk_L->c1, chunk_L->c2);	     // subband filtering - left channel (stage 2).
	AnalysisStageTwo (chunk_L->c34, chunk_L->overlap134, chunk_L->overlap234, &chunk_L->prev_sample34, chunk_L->c3, chunk_L->c4);

	//////////////////////////////////////////////////////////////////////////////////////////////////

	AnalysisStageTwo (chunk_R->c12, chunk_R->overlap112, chunk_R->overlap212, &chunk_R->prev_sample12, chunk_R->c1, chunk_R->c2);        // subband filtering - right channel (stage 2).
	AnalysisStageTwo (chunk_R->c34, chunk_R->overlap134, chunk_R->overlap234, &chunk_R->prev_sample34, chunk_R->c3, chunk_R->c4);
	
	//////////////////////////////////////////////////////////////////////////////////////////////////

	Encode (chunk_L->c1, chunk_L->d_primes1, &chunk_L->delta1, &chunk_L->s_star1, &chunk_L->sum1, chunk_L->z1, 1);
	Encode (chunk_L->c2, chunk_L->d_primes2, &chunk_L->delta2, &chunk_L->s_star2, &chunk_L->sum2, chunk_L->z2, 2);
	Encode (chunk_L->c3, chunk_L->d_primes3, &chunk_L->delta3, &chunk_L->s_star3, &chunk_L->sum3, chunk_L->z3, 3);

	//////////////////////////////////////////////////////////////////////////////////////////////////

	Encode (chunk_R->c1, chunk_R->d_primes1, &chunk_R->delta1, &chunk_R->s_star1, &chunk_R->sum1, chunk_R->z1, 1);
	Encode (chunk_R->c2, chunk_R->d_primes2, &chunk_R->delta2, &chunk_R->s_star2, &chunk_R->sum2, chunk_R->z2, 2);
	Encode (chunk_R->c3, chunk_R->d_primes3, &chunk_R->delta3, &chunk_R->s_star3, &chunk_R->sum3, chunk_R->z3, 3);

	//////////////////////////////////////////////////////////////////////////////////////////////////

	Pack(chunk_L->z1, chunk_L->z2, chunk_L->z3, chunk_L->z4, chunk_R->z1, chunk_R->z2, chunk_R->z3, chunk_R->z4, pCompressed);

	return;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////         This routine subtracts input elements of two arrays         ////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////

void InitFirstPhaseChunk (struct FirstPhaseChunk * chunk){

	size32_t i;

	size16_t h1_temp[FILSIZE] = h1;
	size16_t h2_temp[FILSIZE] = h2;
	
	chunk->delta1 = 1;
	chunk->delta2 = 1;
	chunk->delta3 = 1;

	chunk->sum1 = 0;
	chunk->sum2 = 0;
	chunk->sum3 = 0;

	for (i=0; i< FILSIZE/2; i++){
	
		h1_even[i] = h1_temp[2*i];
		h1_odd[i] = h1_temp[2*i+1];
		
		h2_even[i] = h2_temp[2*i];
		h2_odd[i] = h2_temp[2*i+1];	
	}

	return;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////		This routine performs packing of the bits for both right	///////////// 
/////////////		and the left channel for transmission. 5 samples in each        /////////////
/////////////		array, and for each sample bit extaction is performed.          /////////////
////////////////////////////////////////////////////////////////////////////////////////////////////

inline void Pack (size16_t z1_L[], size16_t z2_L[], size16_t z3_L[], size16_t z4_L[], size16_t z1_R[], size16_t z2_R[], size16_t z3_R[], size16_t z4_R[], size16_t pCompressed[])
{

///////////////////////		Left channel packing		///////////////////////
	
	pCompressed[0] = (z1_L[0] & MASK1)<<10 | (z2_L[0] & MASK2)<<5 | (z2_L[1] & MASK2);
	pCompressed[1] = (z1_L[1] & MASK1)<<10 | (z2_L[2] & MASK2)<<5 | (z2_L[3] & MASK2); 
	pCompressed[2] = (z1_L[2] & MASK1)<<10 | (z1_L[3] & MASK1)<<4 | (z3_L[0] & MASK3)<<3 | (z3_L[1] & MASK3)<<2 |(z3_L[2] & MASK3)<<1 |(z3_L[3] & MASK3);
	pCompressed[3] = (z1_L[4] & MASK1)<<10 | (z2_L[4] & MASK2)<<5 | (z3_L[4] & MASK3)<<4;

///////////////////////		Right channel packing		///////////////////////

	pCompressed[4] = (z1_R[0] & MASK1)<<10 | (z2_R[0] & MASK2)<<5 | (z2_R[1] & MASK2);
	pCompressed[5] = (z1_R[1] & MASK1)<<10 | (z2_R[2] & MASK2)<<5 | (z2_R[3] & MASK2); 
	pCompressed[6] = (z1_R[2] & MASK1)<<10 | (z1_R[3] & MASK1)<<4 | (z3_R[0] & MASK3)<<3 | (z3_L[1] & MASK3)<<2 |(z3_L[2] & MASK3)<<1 |(z3_L[3] & MASK3);
	pCompressed[7] = (z1_R[4] & MASK1)<<10 | (z2_R[4] & MASK2)<<5 | (z3_R[4] & MASK3)<<4;
	
	return;
}
