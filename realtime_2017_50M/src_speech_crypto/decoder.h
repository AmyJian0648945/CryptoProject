#ifndef DECODER_H
#define DECODER_H

#include "globals.h"

static short f1_even[FILSIZE/2];
static short f1_odd[FILSIZE/2];

static short f2_even[FILSIZE/2];
static short f2_odd[FILSIZE/2];

static short NBITS[4];
static short WINDOWSIZES[4];
static short MUS[4];
static short LOG_PHIS[4];

typedef struct SecondPhaseChunk{

///////////////////////		Synthesis chunk variables	///////////////////////

	short overlap1[OVERLAPSIZE];
	short overlap2[OVERLAPSIZE];
	short prev_sample;

	short overlap112[OVERLAPSIZE];
	short overlap212[OVERLAPSIZE];
	short prev_sample12;

	short overlap134[OVERLAPSIZE];
	short overlap234[OVERLAPSIZE];
	short prev_sample34;

///////////////////////		Decoding chunk variables	///////////////////////

	short s_star1;
	short delta1;
	short d_primes1[WINDOWSIZE];

	short s_star2;
	short delta2;
	short d_primes2[WINDOWSIZE];

	short s_star3;
	short delta3;
	short d_primes3[WINDOWSIZE];

	short sum1;
	short sum2;
	short sum3;

//////////////////////////		Output arrays	          ///////////////////////

	short s[BUFFERSIZE/2];

	short s12[BUFFERSIZE/4];
	short s34[BUFFERSIZE/4];

	short s1[BUFFERSIZE/8];
	short s2[BUFFERSIZE/8];
	short s3[BUFFERSIZE/8];
	short s4[BUFFERSIZE/8];

	short z1[BUFFERSIZE/8];
	short z2[BUFFERSIZE/8];
	short z3[BUFFERSIZE/8];
	short z4[BUFFERSIZE/8];

}SecondPhaseChunk;

void InitParametersDec ();

void SynthesisStageOne (size16_t input1[], size16_t input2[], size16_t overlap1[], size16_t overlap2[], size16_t * prev_sample, size16_t output[]);

void SynthesisStageTwo (size16_t input1[], size16_t input2[], size16_t overlap1[], size16_t overlap2[], size16_t * prev_sample, size16_t output[]);

void Decode (const size16_t * restrict z, size16_t * restrict d_primes, size16_t * delta, size16_t * s_star, size16_t * avg, size16_t * restrict s, size16_t band);

void SecondPhase (size16_t pCompressed[], struct SecondPhaseChunk * chunk_L, struct SecondPhaseChunk * chunk_R, size16_t buffer[]);

void InitSecondPhaseChunk (struct SecondPhaseChunk * chunk);

inline void Unpack (size16_t pCompressed[], size16_t z1_L[], size16_t z2_L[], size16_t z3_L[], size16_t z4_L[], size16_t z1_R[], size16_t z2_R[], size16_t z3_R[], size16_t z4_R[]);

#endif
