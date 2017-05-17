#ifndef GLOBALS_H
#define GLOBALS_H

typedef long long size64_t;
typedef long size40_t;
typedef int size32_t;
typedef short size16_t;

#define MIN_COUNT 5
#define MAX_COUNT 10
#define INNER_LOOP_COUNT 3
#define OUTER_LOOP_COUNT_MIN 10
#define OUTER_LOOP_COUNT_MAX 15

#define BUFFERS 100

#define BUFFERSIZE 40
#define FILSIZE 12
#define OVERLAPSIZE FILSIZE/2 -1
#define PACKSIZE 8

#define WINDOWSIZE 8

#define log_2 1
#define log_4 2
#define log_8 3
#define log_256 8
#define log_16384 14
#define log_32768 15
#define log_windowsize 3


#define h1 {-33, 289, 65, -2351, 2383, 16036, 16036, 2383, -2351, 65, 289, -33}
#define h2 {-33, 289, 65, -2351, 2383, 16036, 16036, 2383, -2351, 65, 289, -33};

#define f1 {-65, 579, 130, -4701, 4767, 32071, 32071, 4767, -4701, 130, 579, -65};
#define f2 {-65, 579, 130, -4701, 4767, 32071, 32071, 4767, -4701, 130, 579, -65};


#define MU1 218
#define MU2 36
#define MU3 32


#define NBITS1 6
#define NBITS2 5
#define NBITS3 1

#define MASK1 63
#define MASK2 31
#define MASK3 1

#define SIGNEX(x, nbits) ((x) | (((x) & (1 << (nbits-1))) ? ~((1 << (nbits-1))-1) : 0))

#define PHI1 32
#define PHI2 64
#define PHI3 256

#define LOG_PHI1 5
#define LOG_PHI2 6
#define LOG_PHI3 8

#define DELTAMAX 1000
#define DELTAMIN 1

#define INPUTWAVFILE  "input.wav"
#define OUTPUTWAVFILE "output.wav"

#endif



