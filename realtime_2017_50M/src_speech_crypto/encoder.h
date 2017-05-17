#ifndef ENCODER_H
#define ENCODER_H

#include "globals.h"

static short h1_even[FILSIZE/2];
static short h1_odd[FILSIZE/2];

static short h2_even[FILSIZE/2];
static short h2_odd[FILSIZE/2];

static short NBITS[4];
//static short WINDOWSIZES[4];
static short MUS[4];
static short LOG_PHIS[4];

typedef struct FirstPhaseChunk{

///////////////////////		Analysis chunk variables	///////////////////////

	short overlap1[OVERLAPSIZE];
	short overlap2[OVERLAPSIZE];
	short prev_sample;

	short overlap112[OVERLAPSIZE];
	short overlap212[OVERLAPSIZE];
	short prev_sample12;

	short overlap134[OVERLAPSIZE];
	short overlap234[OVERLAPSIZE];
	short prev_sample34;

///////////////////////		Encoding chunk variables	///////////////////////

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

	short c[BUFFERSIZE/2];

	short c12[BUFFERSIZE/4];
	short c34[BUFFERSIZE/4];

	short c1[BUFFERSIZE/8];
	short c2[BUFFERSIZE/8];
	short c3[BUFFERSIZE/8];
	short c4[BUFFERSIZE/8];

	short z1[BUFFERSIZE/8];
	short z2[BUFFERSIZE/8];
	short z3[BUFFERSIZE/8];
	short z4[BUFFERSIZE/8];

}FirstPhaseChunk;

void InitParametersEnc ();

void AnalysisStageOne (size16_t input[], size16_t overlap1[], size16_t overlap2[], size16_t * prev_sample, size16_t output1[], size16_t output2[]);

void AnalysisStageTwo (size16_t input[], size16_t overlap1[], size16_t overlap2[], size16_t * prev_sample, size16_t output1[], size16_t output2[]);

void Encode (const size16_t * restrict s, size16_t * restrict d_primes, size16_t * delta, size16_t * s_star, size16_t * avg, size16_t * restrict z, size16_t band);

void FirstPhase (size16_t buffer[], struct FirstPhaseChunk * chunk_L, struct FirstPhaseChunk * chunk_R, size16_t pCompressed[]);

void InitFirstPhaseChunk (struct FirstPhaseChunk * chunk);

inline void Pack (size16_t z1_L[], size16_t z2_L[], size16_t z3_L[], size16_t z4_L[], size16_t z1_R[], size16_t z2_R[], size16_t z3_R[], size16_t z4_R[], size16_t pCompressed[]);

#endif
