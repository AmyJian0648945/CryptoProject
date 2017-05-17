#include <stdio.h>
#include "globals.h"
#include "decoder.h"
#include "auxiliaries.h"

////////////////////////////////////////////////////////////////////////////////////////////////////
///////  This routine initializes the parameter arrays with the values defined in the macros ////////
////////////////////////////////////////////////////////////////////////////////////////////////////

void InitParametersDec ()
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
///////////////        	This routine performs synthesis filtering (stage1) 	      ///////////////
////////////////        of the input and results in two outputs.                      ///////////////
////////////////////////////////////////////////////////////////////////////////////////////////////

void SynthesisStageOne (size16_t input1[], size16_t input2[], size16_t overlap1[], size16_t overlap2[], size16_t * prev_sample, size16_t output[])
{

	size16_t sum[BUFFERSIZE >> log_2];
	size16_t sub[BUFFERSIZE >> log_2];
	size16_t c1[BUFFERSIZE >> log_2];
	size16_t c2[BUFFERSIZE >> log_2];
	size32_t i;
	size16_t aux;

	sum[0] = input1[0] + input2[0];
	sum[1] = input1[1] + input2[1];
	sum[2] = input1[2] + input2[2];
	sum[3] = input1[3] + input2[3];
	sum[4] = input1[4] + input2[4];
	sum[5] = input1[5] + input2[5];
	sum[6] = input1[6] + input2[6];
	sum[7] = input1[7] + input2[7];
	sum[8] = input1[8] + input2[8];
	sum[9] = input1[9] + input2[9];

	sub[0] = input1[0] - input2[0];
	sub[1] = input1[1] - input2[1];
	sub[2] = input1[2] - input2[2];
	sub[3] = input1[3] - input2[3];
	sub[4] = input1[4] - input2[4];
	sub[5] = input1[5] - input2[5];
	sub[6] = input1[6] - input2[6];
	sub[7] = input1[7] - input2[7];
	sub[8] = input1[8] - input2[8];
	sub[9] = input1[9] - input2[9];

	DoubleConvolution(sum, sub, BUFFERSIZE >> log_4, overlap1, overlap2, f1_odd, f1_even, FILSIZE >> log_2, c1, c2);
	aux = c1[(BUFFERSIZE >> log_4)-1];
	for (i=(BUFFERSIZE >> log_4)-1; i>0 ;i--) c1[i] = c1[i-1];
	c1[0] = *prev_sample;
	*prev_sample = aux;

	output[0] = c1[0];                       								 		   // combining even and odd samples
	output[1] = c2[0];
	output[2] = c1[1];
	output[3] = c2[1];
	output[4] = c1[2];
	output[5] = c2[2];
	output[6] = c1[3];
	output[7] = c2[3];
	output[8] = c1[4];
	output[9] = c2[4];
	output[10] = c1[5];
	output[11] = c2[5];
	output[12] = c1[6];
	output[13] = c2[6];
	output[14] = c1[7];
	output[15] = c2[7];
	output[16] = c1[8];
	output[17] = c2[8];
	output[18] = c1[9];
	output[19] = c2[9];

	return;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////        	This routine performs synthesis filtering (stage2) 	      ///////////////
////////////////        of the input and results in two outputs.                      ///////////////
////////////////////////////////////////////////////////////////////////////////////////////////////

void SynthesisStageTwo (size16_t input1[], size16_t input2[], size16_t overlap1[], size16_t overlap2[], size16_t * prev_sample, size16_t output[])
{

	size16_t sum[BUFFERSIZE >> log_4];
	size16_t sub[BUFFERSIZE >> log_4];
	size16_t c1[BUFFERSIZE >> log_4];
	size16_t c2[BUFFERSIZE >> log_4];
	size32_t i;
	size16_t aux;

	sum[0] = input1[0] + input2[0];
	sum[1] = input1[1] + input2[1];
	sum[2] = input1[2] + input2[2];
	sum[3] = input1[3] + input2[3];
	sum[4] = input1[4] + input2[4];

	sub[0] = input1[0] - input2[0];
	sub[1] = input1[1] - input2[1];
	sub[2] = input1[2] - input2[2];
	sub[3] = input1[3] - input2[3];
	sub[4] = input1[4] - input2[4];

	DoubleConvolution(sum, sub, BUFFERSIZE >> log_8, overlap1, overlap2, f2_odd, f2_even, FILSIZE >> log_2, c1, c2);
	aux = c1[(BUFFERSIZE >> log_8) -1];
	for (i=(BUFFERSIZE >> log_8) -1; i>0 ;i--) c1[i] = c1[i-1];
	c1[0] = *prev_sample;
	*prev_sample = aux;

	output[0] = c1[0];                       								 		   // combining even and odd samples
	output[1] = c2[0];
	output[2] = c1[1];
	output[3] = c2[1];
	output[4] = c1[2];
	output[5] = c2[2];
	output[6] = c1[3];
	output[7] = c2[3];
	output[8] = c1[4];
	output[9] = c2[4];

	return;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////        	This routine performs decoding of the input stream 	      ///////////////
////////////////////////////////////////////////////////////////////////////////////////////////////

void Decode (const size16_t * restrict z, size16_t * restrict d_primes, size16_t * delta, size16_t * s_star, size16_t * sum, size16_t * restrict s, size16_t band)
{

	size32_t i, j;
	//size16_t sum;
	size16_t d_prime;

	size16_t log_phi = LOG_PHIS[band-1];                     								 		   // band is used for parameter array indexing and starts from 1
	size16_t mu = MUS[band-1];

	#pragma MUST_ITERATE(BUFFERSIZE >> log_8,BUFFERSIZE >> log_8,BUFFERSIZE >> log_8)
	#pragma UNROLL(BUFFERSIZE >> log_8)
	for (i=0; i< BUFFERSIZE >> log_8; i++)
	{
		d_prime = z[i] * (*delta);
		s[i] = d_prime + *s_star;
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
		*s_star = (mu*s[i])>>log_256;
	}
	return;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
////////////     This routine performs all the tasks of stage2 namely decoding,  	   //////////
///////////      synthesis filtering and combining right/left channels.                    /////////
////////////////////////////////////////////////////////////////////////////////////////////////////

void SecondPhase (size16_t pCompressed[], struct SecondPhaseChunk * chunk_L, struct SecondPhaseChunk * chunk_R, size16_t buffer[])
{
	Unpack (pCompressed, chunk_L->z1, chunk_L->z2, chunk_L->z3, chunk_L->z4, chunk_R->z1, chunk_R->z2, chunk_R->z3, chunk_R->z4);

	//////////////////////////////////////////////////////////////////////////////////////////////////

	Decode (chunk_L->z1, chunk_L->d_primes1, &chunk_L->delta1, &chunk_L->s_star1, &chunk_L->sum1, chunk_L->s1, 1);
	Decode (chunk_L->z2, chunk_L->d_primes2, &chunk_L->delta2, &chunk_L->s_star2, &chunk_L->sum2, chunk_L->s2, 2);
	Decode (chunk_L->z3, chunk_L->d_primes3, &chunk_L->delta3, &chunk_L->s_star3, &chunk_L->sum3, chunk_L->s3, 3);

	//////////////////////////////////////////////////////////////////////////////////////////////////

	Decode (chunk_R->z1, chunk_R->d_primes1, &chunk_R->delta1, &chunk_R->s_star1, &chunk_R->sum1, chunk_R->s1, 1);
	Decode (chunk_R->z2, chunk_R->d_primes2, &chunk_R->delta2, &chunk_R->s_star2, &chunk_R->sum2, chunk_R->s2, 2);
	Decode (chunk_R->z3, chunk_R->d_primes3, &chunk_R->delta3, &chunk_R->s_star3, &chunk_R->sum3, chunk_R->s3, 3);

	//////////////////////////////////////////////////////////////////////////////////////////////////

	SynthesisStageTwo (chunk_L->s1, chunk_L->s2, chunk_L->overlap112, chunk_L->overlap212, &chunk_L->prev_sample12, chunk_L->s12);
	SynthesisStageTwo (chunk_L->s3, chunk_L->s4, chunk_L->overlap134, chunk_L->overlap234, &chunk_L->prev_sample34, chunk_L->s34);

	//////////////////////////////////////////////////////////////////////////////////////////////////

	SynthesisStageTwo (chunk_R->s1, chunk_R->s2, chunk_R->overlap112, chunk_R->overlap212, &chunk_R->prev_sample12, chunk_R->s12);
	SynthesisStageTwo (chunk_R->s3, chunk_R->s4, chunk_R->overlap134, chunk_R->overlap234, &chunk_R->prev_sample34, chunk_R->s34);

	//////////////////////////////////////////////////////////////////////////////////////////////////

	SynthesisStageOne (chunk_L->s12, chunk_L->s34, chunk_L->overlap1, chunk_L->overlap2, &chunk_L->prev_sample, chunk_L->s);

	//////////////////////////////////////////////////////////////////////////////////////////////////

	SynthesisStageOne (chunk_R->s12, chunk_R->s34, chunk_R->overlap1, chunk_R->overlap2, &chunk_R->prev_sample, chunk_R->s);

	//////////////////////////////////////////////////////////////////////////////////////////////////

	CombineSamples (chunk_L->s, chunk_R->s, BUFFERSIZE/2, buffer);	

	return;
}

void InitSecondPhaseChunk (struct SecondPhaseChunk * chunk){

	size32_t i;

	size16_t f1_temp[FILSIZE] = f1;
	size16_t f2_temp[FILSIZE] = f2;

	chunk->delta1 = 1;
	chunk->delta2 = 1;
	chunk->delta3 = 1;

	chunk->sum1 = 0;
	chunk->sum2 = 0;
	chunk->sum3 = 0;

	for (i=0; i< FILSIZE/2; i++){
	
		f1_even[i] = f1_temp[2*i];
		f1_odd[i] = f1_temp[2*i+1];
		
		f2_even[i] = f2_temp[2*i];
		f2_odd[i] = f2_temp[2*i+1];	
	}	

	return;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////        	This routine performs unpacking of the  bits and also 	      ///////////////
////////////////        the sign extension.                                           ///////////////
////////////////////////////////////////////////////////////////////////////////////////////////////

inline void Unpack (size16_t pCompressed[], size16_t z1_L[], size16_t z2_L[], size16_t z3_L[], size16_t z4_L[], size16_t z1_R[], size16_t z2_R[], size16_t z3_R[], size16_t z4_R[])
{

///////////////////////		Left channel unpacking		///////////////////////

	z1_L[0] = (pCompressed[0]>>10) & MASK1;
	z1_L[0] = SIGNEX(z1_L[0],6);
	z1_L[1] = (pCompressed[1]>>10) & MASK1;
	z1_L[1] = SIGNEX(z1_L[1],6);
	z1_L[2] = (pCompressed[2]>>10) & MASK1;
	z1_L[2] = SIGNEX(z1_L[2],6);
	z1_L[3] = (pCompressed[2]>>4) & MASK1;
	z1_L[3] = SIGNEX(z1_L[3],6);
	z1_L[4] = (pCompressed[3]>>10) & MASK1;
	z1_L[4] = SIGNEX(z1_L[4],6);

	z2_L[0] = (pCompressed[0]>>5) & MASK2;
	z2_L[0] = SIGNEX(z2_L[0],5);
	z2_L[1] = pCompressed[0] & MASK2; 
	z2_L[1] = SIGNEX(z2_L[1],5);
	z2_L[2] = (pCompressed[1]>>5) & MASK2;
	z2_L[2] = SIGNEX(z2_L[2],5);
	z2_L[3] = pCompressed[1] & MASK2; 
	z2_L[3] = SIGNEX(z2_L[3],5);
	z2_L[4] = (pCompressed[3]>>5) & MASK2;
	z2_L[4] = SIGNEX(z2_L[4],5);

	z3_L[0] = (pCompressed[2]>>3) & MASK3;
	z3_L[0] = SIGNEX(z3_L[0],1);
	z3_L[1] = (pCompressed[2]>>2) & MASK3;
	z3_L[1] = SIGNEX(z3_L[1],1);
	z3_L[2] = (pCompressed[2]>>1) & MASK3;
	z3_L[2] = SIGNEX(z3_L[2],1);
	z3_L[3] = pCompressed[2] & MASK3;
	z3_L[3] = SIGNEX(z3_L[3],1);
	z3_L[4] = (pCompressed[3]>>4) & MASK3;
	z3_L[4] = SIGNEX(z3_L[4],1);

	z4_L[0] = 0;
	z4_L[1] = 0;
	z4_L[2] = 0;
	z4_L[3] = 0;
	z4_L[4] = 0;

///////////////////////		Right channel unpacking		///////////////////////

	z1_R[0] = (pCompressed[4]>>10) & MASK1;
	z1_R[0] = SIGNEX(z1_R[0],6);
	z1_R[1] = (pCompressed[5]>>10) & MASK1;
	z1_R[1] = SIGNEX(z1_R[1],6);
	z1_R[2] = (pCompressed[6]>>10) & MASK1;
	z1_R[2] = SIGNEX(z1_R[2],6);
	z1_R[3] = (pCompressed[6]>>4) & MASK1;
	z1_R[3] = SIGNEX(z1_R[3],6);
	z1_R[4] = (pCompressed[7]>>10) & MASK1;
	z1_R[4] = SIGNEX(z1_R[4],6);

	z2_R[0] = (pCompressed[4]>>5) & MASK2;
	z2_R[0] = SIGNEX(z2_R[0],5);
	z2_R[1] = pCompressed[4] & MASK2; 
	z2_R[1] = SIGNEX(z2_R[1],5);
	z2_R[2] = (pCompressed[5]>>5) & MASK2;
	z2_R[2] = SIGNEX(z2_R[2],5);
	z2_R[3] = pCompressed[5] & MASK2; 
	z2_R[3] = SIGNEX(z2_R[3],5);
	z2_R[4] = (pCompressed[7]>>5) & MASK2;
	z2_R[4] = SIGNEX(z2_R[4],5);

	z3_R[0] = (pCompressed[6]>>3) & MASK3;
	z3_R[0] = SIGNEX(z3_R[0],1);
	z3_R[1] = (pCompressed[6]>>2) & MASK3;
	z3_R[1] = SIGNEX(z3_R[1],1);
	z3_R[2] = (pCompressed[6]>>1) & MASK3;
	z3_R[2] = SIGNEX(z3_R[2],1);
	z3_R[3] = pCompressed[6] & MASK3;
	z3_R[3] = SIGNEX(z3_R[3],1);
	z3_R[4] = (pCompressed[7]>>4) & MASK3;
	z3_R[4] = SIGNEX(z3_R[4],1);

	z4_R[0] = 0;
	z4_R[1] = 0;
	z4_R[2] = 0;
	z4_R[3] = 0;
	z4_R[4] = 0;
	
	return;
}
