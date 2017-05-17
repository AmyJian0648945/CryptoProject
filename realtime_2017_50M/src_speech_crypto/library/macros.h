#ifndef MACROS_H
#define MACROS_H



/* PKA */ 
/*nb of 32 bit size words */
#ifndef baseLength
#define baseLength 14
#endif
/*nb of 32 bit size words */
#ifndef modLength
#define modLength 15
#endif
/*nb of 32 bit size words */
#ifndef expLengthMAX
#define expLengthMAX 16
#endif
/*nb of bytes */
#define sizeMessageAB 120
/*nb of 32 bit size words */
#define sizeModulusAB 32
#define sizePrExpAB 32
#define sizePuExpAB 1

#define NORMAL		40
#define MEDIUM		41
#define LONG		80
#define VERYLONG	81

/*** Data Transmission ***/
#define DATA_BLOCK_SIZE         		64
#define MAX_MESSAGE_LENGTH              500 /* CURRENTLY A PATCH: ADJUST THIS VARIABLE after discussion with the processing group!! */
#define MAX_TRANSMISSION_BLOCK_LENGTH   512 /* CURRENTLY A PATCH: needs to be 16x */

#define encryptKeyLength    16 /* Length of the encryption key */
#define macKeyLength        16 /* Length of MAC key */ 
#define IVlength            16 /* Length of the IV used in AES CBC mode*/ 

/* USE SHA256 */
#ifndef SHA256_DIGEST_LENGTH     
#define SHA256_DIGEST_LENGTH    32  
#endif /* SHA256_DIGEST_LENGTH */
#define SHA2_USE_INTTYPES_H
#define TIME_DATA_BASE          10
#define TIME_DATA_LENGTH        16


#define AES_KEY_SIZE    128
#define AES_IVlength    16

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


#endif
