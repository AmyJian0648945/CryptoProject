#include<stdint.h>
#include<string.h>
#include<stdio.h>

#ifndef baseLength
/*#define baseLength 30*/
#define baseLength 15
#endif

#ifndef modLength
/*#define modLength 32*/ 
#define modLength 16
#endif

#ifndef expLengthMAX
/*#define expLengthMAX 32*/
#define expLengthMAX 16
#endif

/*nb of bytes */
#define sizeMessageAB 128
/*nb of 32 bit size words */
#define sizeModulusAB 32
#define sizePrExpAB 32
#define sizePuExpAB 2
//#define sizeMessageAB 128
//#define sizeModulusAB 64
//#define sizePrExpAB 64
//#define sizePuExpAB 2

#define PRINT

#include "library/helpfulFunctions.h"
#include "library/sha2.h"
#include "library/useSHA256.h"
#include "library/aes.h"
#include "library/useAES.h"
#include "library/hmac.h"
#include "library/PRNG.h"
#include "library/encryptDecrypt.h"
#include "Key_Establishment/Header/additionalFunctions32.h"
#include "Key_Establishment/Header/montExponentiation32.h"
#include "Key_Establishment/Header/signatureMessage.h"
#include "Key_Establishment/Header/verifySignature.h"
#include "Key_Establishment/Header/keyEstablishmentFunctions32.h"

int main(void){
/*

	uint16_t g[baseLength] = {0x285a, 0xd063, 0xcb4e, 0x158b, 0x19ac, 0xc462, 0x9dc7, 0x8b92, 0x5b55, 0x7200, 0xaf8a, 0x2b99, 0xf89b, 0xac17, 0xf31c, 0x93a9, 0x40ef, 0x5755, 0xb08b, 0x406e, 0xeb08, 0xec9a, 0x1d0a, 0x9ca9, 0xa2a0, 0x6e3e, 0xd680, 0x534c, 0x874, 0xf626};

	uint16_t p[modLength] = {0xCF5A,0x4C9E,0xBE8A,0xFBD3,0xB4C6,0x475A,0x2B03,0x361C,0x0108,0xAA51,0x44E6,0x4827,0xAA17,0xA5AD,0xCD09,0x3BCE,0xF88B,0x9A0E,0xAC06,0xE7C3,0xE18A,0x5548,0xD2ED,0xE19D,0x3AD4,0xEB54,0x1AE4,0x73FF,0x3018,0xB4BA,0xC353,0xBFCB};

*/
	uint32_t g[baseLength] = {0x285ad063, 0xcb4e158b, 0x19acc462, 0x9dc78b92, 0x5b557200, 0xaf8a2b99, 0xf89bac17, 0xf31c93a9, 0x40ef5755, 0xb08b406e, 0xeb08ec9a, 0x1d0a9ca9, 0xa2a06e3e, 0xd680534c, 0x874f626};
	
	uint32_t p[modLength] = {0xCF5A4C9E,0xBE8AFBD3,0xB4C6475A,0x2B03361C,0x0108AA51,0x44E64827,0xAA17A5AD,0xCD093BCE,0xF88B9A0E,0xAC06E7C3,0xE18A5548,0xD2EDE19D,0x3AD4EB54,0x1AE473FF,0x3018B4BA,0xC353BFCB};
/*

	 uint16_t publicExponentB[sizePuExpAB] = {0x1, 0x0001};
	uint16_t privateExponentB[64] = { 0x4a18, 0xc038, 0x32ae, 0xfc22, 0x6139, 0xf6c7, 0x15f7, 0x53a7, 0xfd0e, 0x7916, 0x939, 0xb9ff, 0xa25, 0x2060, 0x6313, 0x41c7, 0x8094, 0x3f17, 0xf24c, 0xf3f4, 0x63f3, 0xdc59, 0x80c3, 0xcebb, 0x94d0, 0xdd6f, 0xce1e, 0x2dcd, 0x633f, 0x5d82, 0xb47, 0x45a5, 0x5b6d, 0xa35c, 0x72bb, 0x3775, 0x8c2, 0xcc4d, 0x36d3, 0x574c, 0xd9f6, 0x14d8, 0x57fc, 0x3ae5, 0x403e, 0x7746, 0x2c2c, 0x55bd, 0xb5ff, 0xec2d, 0xd047, 0x94d6, 0x42cb, 0x721d, 0xc2db, 0x1258, 0xcbeb, 0xb445, 0x956f, 0xc862, 0xb1ae, 0x6760, 0x476f, 0x3b8d};
	uint16_t modulusB[64] = { 0xe8d3, 0xbb3a, 0x533b, 0x8d2e, 0x40c9, 0x648c, 0xb80a, 0xd232, 0x7482, 0xd192, 0xd056, 0x40a5, 0x39f, 0x756b, 0x8071, 0x91ef, 0x8210, 0xaa05, 0xc931, 0xf23e, 0xb823, 0x7380, 0xdabd, 0x61ed, 0x5cc8, 0xfa7f, 0x46c8, 0xc72d, 0x9622, 0x1b4a, 0x4df4, 0xd78c, 0x302b, 0xd427, 0xd2a2, 0x873b, 0x7417, 0xbfb6, 0xb20a, 0x3d1d, 0x9d78, 0x7d06, 0xfd98, 0xd0bc, 0x1841, 0x6587, 0xbf65, 0x863c, 0x2c70, 0x4f9e, 0x348e, 0x3d17, 0xc0b4, 0xc2d1, 0x74b8, 0xfb2, 0x24a, 0x43ea, 0xa2ce, 0xff1d, 0x2695, 0xcb72, 0x71a5, 0x63e5};
	uint16_t modulusA[64] = {0xcc70, 0xb25c, 0xd644, 0xe756, 0x8336, 0xc7fe, 0xe148, 0xd14c, 0x2839, 0xd46b, 0x9bf6, 0x90b4, 0x6b20, 0x73d2, 0xa181, 0xa113, 0x6ebb, 0xc420, 0x34d5, 0x2f5c, 0xe0c5, 0x5f6c, 0xf6ae, 0xd990, 0xf1a6, 0x8b1a, 0xa1b5, 0xdb9f, 0x1f2a, 0x235, 0xa11c, 0xba0, 0x2296, 0x64b8, 0x9f02, 0x72df, 0x8299, 0x8679, 0x9f7c, 0x64a2, 0x90de, 0x6e7d, 0xb47d, 0x6fff, 0xe995, 0x86da, 0xe960, 0x9f47, 0xd749, 0xa8dc, 0x6426, 0x92b6, 0x47f0, 0x938, 0x8d22, 0x1c03, 0xfb48, 0x2658, 0x2c22, 0x945d, 0x5070, 0x919f, 0x3065, 0xb46f};
	uint16_t publicExponentA[sizePuExpAB] = {0x1, 0x0001};
	uint16_t privateExponentA[64] = { 0x7af4, 0x2061, 0x7340, 0x777d, 0x7166, 0xe5fb, 0x6594, 0x7cc3, 0xf7c1, 0x67fe, 0xdc0a, 0xfb56, 0x76c3, 0x4ac5, 0x57fa, 0xf55c, 0x1191, 0xfdcf, 0x7cd6, 0xe628, 0x4eca, 0x85ac, 0xabe3, 0xd6d7, 0xb46d, 0xfc65, 0x24f2, 0x91c6, 0x6e60, 0xbe79, 0x708e, 0xc472, 0x13e2, 0xf4a6, 0xb510, 0x9716, 0x4b5a, 0xd5c3, 0xfeef, 0xd2eb, 0xdde5, 0x52bd, 0x2edf, 0x499c, 0x41ac, 0x15f2, 0xc879, 0xc0c1, 0xcaad, 0x1c4e, 0xae82, 0xc05d, 0xd3e8, 0x6909, 0xbe6, 0xdf0e, 0x81be, 0xeb96, 0x6478, 0x3820, 0xf62a, 0xb20c, 0x5818, 0x7671};
*/

	uint32_t publicExponentB[sizePuExpAB] = {0x10001};
	uint32_t privateExponentB[sizePrExpAB] = { 0x4a18c038, 0x32aefc22, 0x6139f6c7, 0x15f753a7, 0xfd0e7916, 0x939b9ff, 0xa252060, 0x631341c7, 0x80943f17, 0xf24cf3f4, 0x63f3dc59, 0x80c3cebb, 0x94d0dd6f, 0xce1e2dcd, 0x633f5d82, 0xb4745a5, 0x5b6da35c, 0x72bb3775, 0x8c2cc4d, 0x36d3574c, 0xd9f614d8, 0x57fc3ae5, 0x403e7746, 0x2c2c55bd, 0xb5ffec2d, 0xd04794d6, 0x42cb721d, 0xc2db1258, 0xcbebb445, 0x956fc862, 0xb1ae6760, 0x476f3b8d};
	uint32_t modulusB[sizeModulusAB] = { 0xe8d3bb3a, 0x533b8d2e, 0x40c9648c, 0xb80ad232, 0x7482d192, 0xd05640a5, 0x39f756b, 0x807191ef, 0x8210aa05, 0xc931f23e, 0xb8237380, 0xdabd61ed, 0x5cc8fa7f, 0x46c8c72d, 0x96221b4a, 0x4df4d78c, 0x302bd427, 0xd2a2873b, 0x7417bfb6, 0xb20a3d1d, 0x9d787d06, 0xfd98d0bc, 0x18416587, 0xbf65863c, 0x2c704f9e, 0x348e3d17, 0xc0b4c2d1, 0x74b8fb2, 0x24a43ea, 0xa2ceff1d, 0x2695cb72, 0x71a563e5};
	uint32_t modulusA[sizeModulusAB] = {0xcc70b25c, 0xd644e756, 0x8336c7fe, 0xe148d14c, 0x2839d46b, 0x9bf690b4, 0x6b2073d2, 0xa181a113, 0x6ebbc420, 0x34d52f5c, 0xe0c55f6c, 0xf6aed990, 0xf1a68b1a, 0xa1b5db9f, 0x1f2a235, 0xa11cba0, 0x229664b8, 0x9f0272df, 0x82998679, 0x9f7c64a2, 0x90de6e7d, 0xb47d6fff, 0xe99586da, 0xe9609f47, 0xd749a8dc, 0x642692b6, 0x47f0938, 0x8d221c03, 0xfb482658, 0x2c22945d, 0x5070919f, 0x3065b46f};
	uint32_t publicExponentA[sizePuExpAB] = {0x10001};
	uint32_t privateExponentA[sizeModulusAB] = { 0x7af42061, 0x7340777d, 0x7166e5fb, 0x65947cc3, 0xf7c167fe, 0xdc0afb56, 0x76c34ac5, 0x57faf55c, 0x1191fdcf, 0x7cd6e628, 0x4eca85ac, 0xabe3d6d7, 0xb46dfc65, 0x24f291c6, 0x6e60be79, 0x708ec472, 0x13e2f4a6, 0xb5109716, 0x4b5ad5c3, 0xfeefd2eb, 0xdde552bd, 0x2edf499c, 0x41ac15f2, 0xc879c0c1, 0xcaad1c4e, 0xae82c05d, 0xd3e86909, 0xbe6df0e, 0x81beeb96, 0x64783820, 0xf62ab20c, 0x58187671};

	uint32_t x[expLengthMAX] = {0};
	uint32_t y[expLengthMAX] = {0};
	uint32_t gx[modLength] = {0};
	uint32_t gy[modLength] = {0};

	uint8_t K1[encryptKeyLength] = {0};
	uint8_t K2[encryptKeyLength] = {0};
	

	uint8_t messageA[sizeMessageAB] = {0};
	uint8_t messageB[sizeMessageAB] = {0};
	uint8_t encodedMessageB[sizeMessageAB] = {0};
	uint8_t encodedMessageA[sizeMessageAB] = {0};
	uint8_t transmittedMessageA[sizeModulusAB] = {0};
	uint8_t transmittedMessageB[sizeModulusAB] = {0};
	uint16_t identityAVerified = 0;
	uint16_t identityBVerified = 0;
	
	uint8_t keyInString[encryptKeyLength] = {0};
	uint8_t key[encryptKeyLength] = {0};
    uint8_t data[MAX_MESSAGE_LENGTH] = "hello there 0123456789 hello there 0123456789";
    uint8_t ciphertext[IVlength + MAX_TRANSMISSION_BLOCK_LENGTH + SHA256_DIGEST_LENGTH] = {0};
    uint8_t plaintext[MAX_MESSAGE_LENGTH] = {0};
    uint16_t msgSize[1] = {0};

    /* Processing keys = make sure its in char */
    uint16_t keySize = (uint16_t) strlen((char*)key); 	/* Not guaranteed to work if first input is 0 */
	
	/**** KEY ESTABLISHMENT : the Diffie-Hellman scheme ****/
	/*** STS - Protocol ***/
#ifdef PRINT
    printf("\n\nStart of the STS protocol...\n");
	printf("Secret key creation by poth parties...\n");
#endif
	/* A computes g^x mod p and sends it to B */
#ifdef PRINT
	printf("A computes g^x mod p\n");
#endif
	createExponent(x,expLengthMAX);
	computePartOfKey(g,p,x,gx);
	
	/* B computes g^y mod p and sends it to A */
#ifdef PRINT
	printf("B computes g^y mod p\n");
#endif
	createExponent(y,expLengthMAX);
	computePartOfKey(g,p,y,gy);

#ifdef PRINT
	printf("B receives (g^x) mod p from A and A receives (g^y) mod p from B\n");
#endif

	
	/** B - KEY CREATION + ENTITY AUTHENTICATION **/
	/** B sends message to A to prove identity **/
#ifdef PRINT
	printf("Start of authentication of B\n");
#endif
	/* B calculates the key = (g^x)^y mod p and encodes,signs and encrypts the message (g^y mod p)||(g^x mod p) */
	calculateKey(gx,p,y,K1);
#ifdef PRINT
	printf("Key created by B = (g^x)^y mod p\n");
#endif
	printArrayNoSpaces(K1, encryptKeyLength);

 	createMessage(gy, gx, messageB);
	signatureMessage(messageB, encodedMessageB);
	
	/*
	signMessage(encodedMessageB, tempEMB, modulusB, privateExponentB, sizeMessageAB, sizeModulusAB, sizePrExpAB);
	encryptMessage(tempEMB, EMB, sizeModulusAB, K1);
	 */
	signAndEncryptMessage(encodedMessageB, transmittedMessageB, modulusB, privateExponentB, K1);

#ifdef PRINT
	printArray8(messageB,"Original message B -> A",sizeMessageAB);
	printArray8(transmittedMessageB, "Transmitted message", sizeModulusAB*2);
	printf("B sends g^y mod p and Ek(Sb(g^y mod p || g^x mod p)) to A\n");
#endif

	/* A calculates the key = (g^y)^x mod p */
	calculateKey(gy,p,x,K2);
#ifdef PRINT
	printf("Key created by A = (g^y)^x mod p\n");
#endif
	printArrayNoSpaces(K2,encryptKeyLength);
	/* K1 = K2 = the secret key */
		
	/* A verifies the signature of B after receiving EMB */
	createMessage(gy, gx, messageB);


/*
	decryptMessage(EMB, transmittedMessageB, sizeModulusAB*2, K2);
	unsignMessage(transmittedMessageB, encodedMessageB, modulusB, publicExponentB, sizeModulusAB, sizeModulusAB, sizePuExpAB);
	*/

	decryptAndUnsignMessage(transmittedMessageB, encodedMessageB, K2, modulusB, publicExponentB);

	identityBVerified = verifySignature(messageB, encodedMessageB);
#ifdef PRINT
	if (identityBVerified == 1)
		printf("Authentication B succeeded\n\n");
	else
		printf("Authentication B failed\n\n");
#endif

	
	
	/** A - KEY CREATION + ENTITY AUTHENTICATION **/
	/** A sends message to B to prove identity **/
#ifdef PRINT
	printf("Start of authentication of A\n");
#endif
	createMessage(gx, gy, messageA);
	signatureMessage(messageA, encodedMessageA);

	/*
	signMessage(encodedMessageA, tempEMA, modulusA, privateExponentA, sizeMessageAB,sizeModulusAB, sizePrExpAB);
	encryptMessage(tempEMA, EMA, sizeModulusAB, K2); */
	signAndEncryptMessage(encodedMessageA, transmittedMessageA, modulusA, privateExponentA, K1);

#ifdef PRINT
	printArray8(messageA,"Original message A -> B",sizeMessageAB);
	/*printArray8(transmittedMessage, "Transmitted message", sizeMessageAB);*/
	printf("A sends Ek(Sa(g^x mod p || g^y mod p)) to B\n");
#endif

	/** B receives message of A and checks A's identity **/
	createMessage(gx, gy, messageA);
	/*
	decryptMessage(EMA, transmittedMessageA, sizeModulusAB*2, K1);
	unsignMessage(transmittedMessageA, encodedMessageA, modulusA, publicExponentA, sizeModulusAB, sizeModulusAB, sizePuExpAB);
	*/
	decryptAndUnsignMessage(transmittedMessageA, encodedMessageA, K1, modulusA, publicExponentA);

	identityAVerified = verifySignature(messageA, encodedMessageA);
#ifdef PRINT
	if (identityAVerified == 1)
		printf("Authentication A succeeded\n\n");
	else
		printf("Authentication A failed\n\n");
#endif


	
	/*** DATA TRANSMISSION ***/
#ifdef PRINT
	printf("\n Start of the Data Transmission...\n\n");
#endif
	copyArray8(K1, key, encryptKeyLength);
    msgSize[0] = (uint16_t) strlen((char*)data); 	/* Not guaranteed to work if first input is 0*/

    hexToString(keyInString, key, keySize);
	
	encryptHMAC(ciphertext, msgSize, data, keyInString, keySize*2);
	decryptHMAC(plaintext, msgSize, ciphertext, keyInString, keySize*2);


	/* Printout operation summary */
#ifdef PRINT
	printf("\n---\nSummary I ...\n---\n");
	printf("Plaintext before encryption: "); printCharNoSpaces(data, msgSize[0]);
	printf("\nCiphertext after encryption: "); printArrayNoSpaces(ciphertext, msgSize[0] );
	printf("\nPlaintext after decryption: "); printCharNoSpaces(plaintext, msgSize[0]);
#endif






	
	return 0;
}

