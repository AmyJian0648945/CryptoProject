
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <sys/time.h>

/* Needed for useSHA256.h */
#define SHA2_USE_INTTYPES_H
#define TIME_DATA_BASE          10
#define TIME_DATA_LENGTH        16

#ifndef SHA256_DIGEST_LENGTH     
#define SHA256_DIGEST_LENGTH    32  
#endif /* SHA256_DIGEST_LENGTH */

/* Needed for hmac.h */
#define DATA_BLOCK_SIZE         64
#define MAX_MESSAGE_LENGTH              500 /* CURRENTLY A PATCH: ADJUST THIS VARIABLE after discussion with the processing group!! */
#define MAX_TRANSMISSION_BLOCK_LENGTH   512 /* CURRENTLY A PATCH: needs to be 16x */

/* Needed for useAES.h */


/* Needed for pseudoRandNumGenerator.h */ 
#define RNG_Block_Length    30      /* must be <256/8 = 32!!! */
#define RandNumLength       60      /* for testing purposes */

#define MaxRandNumLength    2048    /* for up / down boundaries of x,y,g */
#define MinRandNumLength    2

#define PRNG_FSR1_LENGTH    64
#define PRNG_FSR2_LENGTH    65
#define PRNG_FSR3_LENGTH    72

#define PRNG_CMP_LOCATION   9       /* must be < any of PRNG_FSR_LENGTH */
#define PRNG_XOR_LOCATION1  7       /* For use in "updateFSR" must be < any of PRNG_FSR_LENGTH */
#define PRNG_XOR_LOCATION2  11          
#define PRNG_XOR_LOCATION3  15
#define PRNG_XOR_LOCATION4  23


/* Needed for encrypt.h */
#define encryptKeyLength    16
#define macKeyLength        16
#define IVlength            16



#include "helpfulFunctions.h"
#include "helpfulFunctions.c"

#include "sha2.h"
#include "sha2.c"

#include "useSHA256.h"
#include "useSHA256.c"

#include "aes.h"


#include "useAES.h"
#include "useAES.c" 

#include "hmac.h"
#include "hmac.c"

#include "PRNG.h"
#include "PRNG.c"

#include "encryptDecrypt.h"
#include "encryptDecrypt.c"





