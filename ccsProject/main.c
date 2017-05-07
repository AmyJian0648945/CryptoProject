/* #define PRINT_PKA_ControlCheck */
/* #define PRINT_DataTransmission */
/*#define EXE_PKA*/
#define EXE_PKA2
#define PRINT_Key
/* #define PRINT_PKA */
/* #define EXE_DataTransmission */

#include<stdint.h>
#include<string.h>
#include<stdio.h>

#ifdef EXE_PKA2
/*nb of 32 bit size words */
#ifndef baseLength
#define baseLength 15
#endif
/*nb of 32 bit size words */
#ifndef modLength
#define modLength 16
#endif
/*nb of 32 bit size words */
#ifndef expLengthMAX
#define expLengthMAX 16
#endif

/*nb of bytes */
#define sizeMessageAB 128
/*nb of 32 bit size words */
#define sizeModulusAB 32
#define sizePrExpAB 32
//#define sizePuExpAB 1
#endif /* EXE_PKA*/

#include "library/helpfulFunctions.h"
#include "library/sha2.h"
#include "library/useSHA256.h"
#include "library/aes.h"
#include "library/useAES.h"
#include "library/hmac.h"
#include "library/PRNG.h"
#include "library/encryptDecrypt.h"
#ifdef EXE_PKA2
#include "Key_Establishment/Header/additionalFunctions32.h"
#include "Key_Establishment/Header/montExponentiation32.h"
#include "Key_Establishment/Header/signatureMessage.h"
#include "Key_Establishment/Header/verifySignature.h"
#include "Key_Establishment/Header/keyEstablishmentFunctions32.h"
#endif /* EXE_PKA */

int main(void){

#ifdef EXE_PKA2

	uint32_t g[baseLength] = {0x285ad063, 0xcb4e158b, 0x19acc462, 0x9dc78b92, 0x5b557200, 0xaf8a2b99, 0xf89bac17, 0xf31c93a9, 0x40ef5755, 0xb08b406e, 0xeb08ec9a, 0x1d0a9ca9, 0xa2a06e3e, 0xd680534c, 0x874f626};
	uint32_t p[modLength] = {0xCF5A4C9E,0xBE8AFBD3,0xB4C6475A,0x2B03361C,0x0108AA51,0x44E64827,0xAA17A5AD,0xCD093BCE,0xF88B9A0E,0xAC06E7C3,0xE18A5548,0xD2EDE19D,0x3AD4EB54,0x1AE473FF,0x3018B4BA,0xC353BFCB};

//	uint32_t publicExponentB[sizePuExpAB] = {0x10001};
	uint32_t privateExponentB[sizePrExpAB] = { 0x4a18c038, 0x32aefc22, 0x6139f6c7, 0x15f753a7, 0xfd0e7916, 0x939b9ff, 0xa252060, 0x631341c7, 0x80943f17, 0xf24cf3f4, 0x63f3dc59, 0x80c3cebb, 0x94d0dd6f, 0xce1e2dcd, 0x633f5d82, 0x0b4745a5, 0x5b6da35c, 0x72bb3775, 0x08c2cc4d, 0x36d3574c, 0xd9f614d8, 0x57fc3ae5, 0x403e7746, 0x2c2c55bd, 0xb5ffec2d, 0xd04794d6, 0x42cb721d, 0xc2db1258, 0xcbebb445, 0x956fc862, 0xb1ae6760, 0x476f3b8d};
	uint32_t modulusB[sizeModulusAB] = {0xe8d3bb3a, 0x533b8d2e, 0x40c9648c, 0xb80ad232, 0x7482d192, 0xd05640a5, 0x039f756b, 0x807191ef, 0x8210aa05, 0xc931f23e, 0xb8237380, 0xdabd61ed, 0x5cc8fa7f, 0x46c8c72d, 0x96221b4a, 0x4df4d78c, 0x302bd427, 0xd2a2873b, 0x7417bfb6, 0xb20a3d1d, 0x9d787d06, 0xfd98d0bc, 0x18416587, 0xbf65863c, 0x2c704f9e, 0x348e3d17, 0xc0b4c2d1, 0x74b80fb2, 0x024a43ea, 0xa2ceff1d, 0x2695cb72, 0x71a563e5};
	uint32_t modulusA[sizeModulusAB] = {0xcc70b25c, 0xd644e756, 0x8336c7fe, 0xe148d14c, 0x2839d46b, 0x9bf690b4, 0x6b2073d2, 0xa181a113, 0x6ebbc420, 0x34d52f5c, 0xe0c55f6c, 0xf6aed990, 0xf1a68b1a, 0xa1b5db9f, 0x1f2a0235, 0xa11c0ba0, 0x229664b8, 0x9f0272df, 0x82998679, 0x9f7c64a2, 0x90de6e7d, 0xb47d6fff, 0xe99586da, 0xe9609f47, 0xd749a8dc, 0x642692b6, 0x47f00938, 0x8d221c03, 0xfb482658, 0x2c22945d, 0x5070919f, 0x3065b46f};
//	uint32_t publicExponentA[sizePuExpAB] = {0x10001};
	uint32_t privateExponentA[sizePrExpAB] = { 0x7af42061, 0x7340777d, 0x7166e5fb, 0x65947cc3, 0xf7c167fe, 0xdc0afb56, 0x76c34ac5, 0x57faf55c, 0x1191fdcf, 0x7cd6e628, 0x4eca85ac, 0xabe3d6d7, 0xb46dfc65, 0x24f291c6, 0x6e60be79, 0x708ec472, 0x13e2f4a6, 0xb5109716, 0x4b5ad5c3, 0xfeefd2eb, 0xdde552bd, 0x2edf499c, 0x41ac15f2, 0xc879c0c1, 0xcaad1c4e, 0xae82c05d, 0xd3e86909, 0x0be6df0e, 0x81beeb96, 0x64783820, 0xf62ab20c, 0x58187671};
	uint32_t publicExponent[1] = {0x10001};
	uint32_t x[expLengthMAX] = {0};
	uint32_t y[expLengthMAX] = {0};
	uint32_t gx[modLength] = {0};
	uint32_t gy[modLength] = {0};
/*

	uint8_t messageA[sizeMessageAB] = {0};
	uint8_t messageB[sizeMessageAB] = {0};
	uint8_t encodedMessageB[sizeMessageAB] = {0};
	uint8_t encodedMessageA[sizeMessageAB] = {0};
	uint8_t transmittedMessageA[sizeMessageAB] = {0};
	uint8_t transmittedMessageB[sizeMessageAB] = {0};
*/
	uint8_t message[sizeMessageAB] = {0};
	uint8_t encodedMessage[sizeMessageAB] = {0};
//	uint8_t transmittedMessage[sizeMessageAB] = {0};
/*

	uint16_t identityAVerified = 0;
	uint16_t identityBVerified = 0;
*/
	uint16_t identityVerified = 0;
/*
	uint8_t K1[encryptKeyLength] = {0};
	uint8_t K2[encryptKeyLength] = {0};
*/
	uint8_t key[encryptKeyLength] = {0};

#endif

#ifdef EXE_DataTransmission
	uint8_t keyInString[encryptKeyLength] = {0};
	uint8_t key[encryptKeyLength] = {0xAA, 0x11, 0x22, 0x33, 0x44, 0xAA, 0XBB};
    uint8_t data[MAX_MESSAGE_LENGTH] = "AAhello there 0123456789 BBhello there 0123456789 CChello there 0123456789 DDhello there 0123456789 EEhello there 0123456789 FFhello there 0123456789 GGhello there 0123456789 HHhello there 0123456789 IIhello there 0123456789";
    uint8_t ciphertext[IVlength + MAX_TRANSMISSION_BLOCK_LENGTH + SHA256_DIGEST_LENGTH] = {0};
    uint8_t plaintext[MAX_MESSAGE_LENGTH] = {0};
    uint16_t msgSize[1] = {0};

    /* Processing keys = make sure its in char */
	/*uint8_t key[encryptKeyLength] = {};*/

    uint16_t keySize = (uint16_t) strlen((char*)key); 	/* Not guaranteed to work if first input is 0 */
#endif

/**** KEY ESTABLISHMENT : the Diffie-Hellman scheme ****/
/*** STS - Protocol ***/

#ifdef PRINT_PKA_ControlCheck
    printf("\n\nStart of the STS protocol...\n");
/*	printf("A computes g^x mod p\n");
	printf("B computes g^y mod p\n");
*/
#endif

#ifdef EXE_PKA2
	createExponent(x,expLengthMAX);
	computePartOfKey(g,p,x,gx);

	createExponent(y,expLengthMAX);
	computePartOfKey(g,p,y,gy);

	calculateKey(gx,p,y,key);
#endif

#ifdef PRINT_Key
	printf("B receives (g^x) mod p from A and A receives (g^y) mod p from B\n");
	printf("Key created by B = (g^x)^y mod p:");
	printArrayNoSpaces(key, encryptKeyLength);
	/* K1 = K2 = the secret key */
#endif

#ifdef EXE_PKA2
	calculateKey(gy,p,x,key);
#endif

#ifdef PRINT_Key
	printf("Key created by A = (g^y)^x mod p:");
	printArrayNoSpaces(key, encryptKeyLength);
#endif

/** B - KEY CREATION + ENTITY AUTHENTICATION **/
/** B sends message to A to prove identity **/

#ifdef PRINT_PKA_ControlCheck
	printf("Start of authentication of B\n");
#endif

#ifdef EXE_PKA2
 	createMessage(gy, gx, message);
	signatureMessage(message, encodedMessage);
	signAndEncryptMessage(encodedMessage, encodedMessage, modulusB, privateExponentB, key);
#endif

#ifdef PRINT_PKA_ControlCheck
 	printf("Original message B->A  (g^y mod p || g^x mod p):");
/*	printArrayNoSpaces(messageB,sizeMessageAB);
	printf("Encoded message B sends to A:");
	printArrayNoSpaces(encodedMessageB, sizeMessageAB);
	printf("Transmitted message B->A:");
	printArrayNoSpaces(transmittedMessageB,sizeMessageAB);
	printf("B sends Ek(Sb(g^y mod p || g^x mod p)) to A\n");
*/
#endif

#ifdef EXE_PKA2
	createMessage(gy, gx, message);
	decryptAndUnsignMessage(encodedMessage, encodedMessage, key, modulusB, publicExponent);
#endif

#ifdef PRINT_PKA
/*
	printf("Encoded message A receives from B (after decryption):");
	printArrayNoSpaces(encodedMessageB, sizeMessageAB);
*/
#endif
#ifdef EXE_PKA2
	identityVerified = verifySignature(message, encodedMessage);
	if (identityVerified == 1)
		printf("\n--> Authentication B succeeded\n\n");
	else
		printf("\n--> Authentication B failed\n\n");
#endif

/** A - ENTITY AUTHENTICATION **/
/** A sends message to B to prove identity **/

#ifdef PRINT_PKA_ControlCheck
	printf("Start of authentication of A\n");
#endif

#ifdef EXE_PKA2
	createMessage(gx, gy, message);
	signatureMessage(message, encodedMessage);
	signAndEncryptMessage(encodedMessage, encodedMessage, modulusA, privateExponentA, key);
#endif

#ifdef PRINT_PKA
/* 	printf("Encoded message A sends to B:");
	printArrayNoSpaces(encodedMessageA, sizeMessageAB);
 	printf("Original message A->B (g^x mod p||g^y mod p):");
	printArrayNoSpaces(messageA,sizeMessageAB);
	printf("Transmitted message A->B:");
	printArrayNoSpaces(transmittedMessageA,sizeMessageAB);
	printf("A sends Ek(Sa(g^x mod p || g^y mod p)) to B\n"); */
#endif

#ifdef EXE_PKA2
	createMessage(gx, gy, message);
	decryptAndUnsignMessage(encodedMessage, encodedMessage, key, modulusA, publicExponent);
#endif

#ifdef PRINT_PKA
/*	printf("Encoded message B receives from A (after decryption):");
	printArrayNoSpaces(encodedMessageA, sizeMessageAB); */
#endif

#ifdef EXE_PKA2
	identityVerified = verifySignature(message, encodedMessage);
	if (identityVerified == 1)
		printf("\n--> Authentication A succeeded\n\n");
	else
		printf("\n--> Authentication A failed\n\n");
#endif


/*** DATA TRANSMISSION ***/

#ifdef PRINT_DataTransmission
	printf("Start of the Data Transmission...\n");
#endif


#ifdef EXE_DataTransmission
	/*copyArray8(K1, key, encryptKeyLength);*/
	msgSize[0] = (uint16_t) strlen((char*)data); 	/* Not guaranteed to work if first input is 0*/
    hexToString(keyInString, key, keySize);
	encryptHMAC(ciphertext, msgSize, data, keyInString, keySize*2);
	decryptHMAC(plaintext, msgSize, ciphertext, keyInString, keySize*2);
#endif
	/* Printout operation summary */
#ifdef PRINT_DataTransmission
	printf("Plaintext before encryption: "); printCharNoSpaces(data, *msgSize);
	printf("\nCiphertext after encryption: "); printArrayNoSpaces(ciphertext, *msgSize );
	printf("\nPlaintext after decryption: "); printCharNoSpaces(plaintext, *msgSize);
#endif
	
	/*printf("\ntest: "); printCharNoSpaces(plaintext, *msgSize);*/

	return 0;
}


