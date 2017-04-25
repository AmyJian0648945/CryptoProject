#include<stdint.h>
#include<string.h>
#include<stdio.h>

#ifndef baseLength
#define baseLength 60
#endif

#ifndef modLength
#define modLength 64
#endif

#ifndef expLengthMAX
#define expLengthMAX 128
#endif

#define sizeModulusB 128
#define sizePrExpB 128
#define sizePuExpB 2
#define sizeModulusA 128
#define sizePrExpA 128
#define sizePuExpA 2
#define sizeMessageAB 256

#include "library/helpfulFunctions.h"
#include "library/sha2.h"
#include "library/useSHA256.h"
#include "library/aes.h"
#include "library/useAES.h"
#include "library/hmac.h"
#include "library/PRNG.h"
#include "library/encryptDecrypt.h"
#include "Montgomery_Exponentiation/additionalFunctions.h"
#include "Montgomery_Exponentiation/montExponentiation.h"
#include "Signature/formatting.h"
#include "Signature/signatureMessage.h"
#include "Signature/verifySignature.h"
#include "Signature/keyEstablishmentFunctions.h"


int main(void){

	uint16_t g[baseLength] = {0x285a, 0xd063, 0xcb4e, 0x158b, 0x19ac, 0xc462, 0x9dc7, 0x8b92, 0x5b55, 0x7200, 0xaf8a, 0x2b99, 0xf89b, 0xac17, 0xf31c, 0x93a9, 0x40ef, 0x5755, 0xb08b, 0x406e, 0xeb08, 0xec9a, 0x1d0a, 0x9ca9, 0xa2a0, 0x6e3e, 0xd680, 0x534c, 0x874, 0xf626, 0x7f4b, 0x8735, 0x3ec1, 0x909a, 0x8016, 0x915d, 0x4949, 0xf7ed, 0x8fef, 0xeb1, 0x55e, 0x245c, 0x49d3, 0x2f9e, 0xfbc3, 0x9d0, 0xb7b7, 0x3b3f, 0x859c, 0x82da, 0x8f40, 0x6254, 0x1b12, 0x4a54, 0xcde1, 0x2c18, 0x12c5, 0x35ba, 0x79df, 0x625c};
	
	uint16_t  p[modLength] = {0xC560, 0x6230, 0x4537, 0xA900, 0x9534, 0xD2ED, 0xE51C, 0xED5A, 0x1299, 0x4928, 0xEACF, 0x4FA5, 0x11D3, 0x082E, 0xD8EA, 0xFEB9, 0xAD67, 0x7B2E, 0x6948, 0xB8BF, 0x513A, 0xA1AD, 0x6CF8, 0x18AD, 0x4B22, 0xDEEC, 0xC060, 0xD442, 0x7015, 0xC93D, 0x8860, 0x236A, 0x0514, 0xBD7C, 0xAB1B, 0xE756, 0xB6A0, 0x16AF, 0xF376, 0x2C6F, 0xA56F, 0x15DD, 0x387B, 0x7CE4, 0x6C16, 0xA09E, 0xB321, 0x5194, 0x2469, 0x0DB8, 0x2E31, 0x22D7, 0x1065, 0x6FE3, 0xBC1B, 0x74CB, 0xBA4F, 0x84FE, 0xD68B, 0xEC13, 0x527C, 0x5095, 0xAEA0, 0x9029};

	uint16_t publicExponentB[sizePuExpB] = {0x1, 0x0001};
	uint16_t privateExponentB[sizePrExpB] = {0x6835, 0x5027, 0x7c09, 0x5488, 0x7725, 0x70a5, 0x5f60, 0xfbc2, 0x71ac, 0xbe08, 0xb407, 0x2da, 0x3e16, 0x500a, 0xc909, 0xbea0, 0x208e, 0x824f, 0x3eea, 0xabe5, 0x13e7, 0xd92b, 0x8ff1, 0x311e, 0x4adb, 0x5c54, 0x81ea, 0xe1f7, 0x968c, 0x3d79, 0xbb8b, 0x3873, 0x7136, 0xfd0, 0xaafc, 0xa8e0, 0xa5e, 0x6989, 0x36d4, 0xc6b0, 0x32a8, 0x5dbd, 0x7863, 0xb6bd, 0x7f9d, 0xc53, 0x8854, 0x95cb, 0x33e5, 0x5751, 0x1d35, 0x8216, 0x4cc2, 0x24bb, 0xd94d, 0x37ac, 0x2e65, 0x52e3, 0xe176, 0xc220, 0x894c, 0x5d6f, 0x6a63, 0x926, 0x5c9b, 0x54b7, 0x61de, 0xc65d, 0x69cf, 0x1e26, 0x2d31, 0xfefd, 0x22fb, 0x5d08, 0x28eb, 0x9929, 0x7e16, 0x749f, 0x3e30, 0xd40a, 0xc484, 0xceb2, 0x5c6b, 0xd4b3, 0x42d, 0x1b54, 0x6678, 0x4ac2, 0xe9b4, 0x662f, 0x1886, 0xb190, 0x1763, 0x2467, 0x912b, 0xe80e, 0xeb6, 0xa4d8, 0xfb95, 0x1896, 0x6445, 0x6653, 0xf73b, 0xb8b0, 0x64b4, 0xeb3b, 0x1487, 0x98f0, 0x4f1c, 0x91c5, 0x356d, 0x9d80, 0x68cf, 0xc06d, 0x587d, 0x69a1, 0x30f6, 0x4429, 0xac86, 0xa35, 0x24f9, 0x61ec, 0x3dfc, 0x499b, 0x5cf0, 0x6360, 0xbe47, 0x8051};
	uint16_t modulusB[sizeModulusB] = {0xaaea, 0xb81b, 0xdb90, 0x5253, 0x3bf0, 0xd3d9, 0x9c6d, 0xce47, 0xb699, 0x6d2a, 0xc58e, 0x5665, 0x7683, 0xe3c4, 0x2478, 0x71be, 0x849c, 0x4a8f, 0x56d2, 0xcca1, 0x16e7, 0x50bb, 0xda34, 0x842e, 0x2766, 0x2e9d, 0x4ff7, 0x114, 0x5008, 0x1fb6, 0x8f4f, 0xd0a2, 0x622, 0x6c6b, 0x57eb, 0xeee9, 0x4d72, 0x89f2, 0x7f39, 0x8782, 0x2e35, 0x7c64, 0x57ce, 0x2cfb, 0xa54c, 0xc26, 0x9fbb, 0xb7c8, 0x3206, 0xf729, 0x60c5, 0x6cd9, 0x5c2b, 0x8628, 0x2510, 0x371b, 0x5827, 0x44c7, 0xbe5, 0x1d60, 0x7174, 0xc2c9, 0xe9cc, 0x13b2, 0x61b5, 0xc6a8, 0x1bea, 0x2598, 0xcea3, 0xd4fe, 0x2d71, 0xa8c3, 0x1f64, 0x4806, 0x422a, 0x2d10, 0xdaa8, 0x1055, 0x3bc9, 0x838e, 0x5a06, 0xa83f, 0xe713, 0x25f7, 0x6862, 0x7a97, 0x5b31, 0x661e, 0xd1ca, 0xfa52, 0xb513, 0xf6d6, 0xf9f8, 0x3ac1, 0xaa27, 0x5c74, 0x7c3a, 0x7956, 0xfe2e, 0x1925, 0x38d0, 0xe863, 0x8d14, 0xf585, 0xb2e1, 0x9d79, 0xbd80, 0xecff, 0xaf13, 0x8d8d, 0x392e, 0x3389, 0x5f58, 0xe890, 0x92b0, 0x71f, 0xddee, 0xfd4b, 0x788a, 0xdeae, 0xe16d, 0x36e5, 0x8743, 0x1520, 0xee80, 0x49a6, 0xff05, 0x23fb};
	uint16_t modulusA[sizeModulusA] = {0xcee4, 0xf4e4, 0x5ec7, 0x2e72, 0x5fdb, 0xcd13, 0x369b, 0x6007, 0x1dbf, 0x2808, 0x6347, 0xf917, 0x474c, 0x3bbd, 0x79a, 0xf624, 0xa23f, 0x8781, 0x54cf, 0xa24a, 0x79a7, 0xd7ff, 0xd0e3, 0x8706, 0xe3d7, 0x31cc, 0x8825, 0xdc9f, 0x2b07, 0xce7f, 0x2b19, 0x3f5b, 0x52a7, 0xef00, 0x1ed6, 0x36a2, 0x568c, 0x94c6, 0xd312, 0xbfc3, 0xca95, 0x27f6, 0x7208, 0x15df, 0x7d01, 0x91a6, 0x1bd6, 0x7746, 0xa93b, 0x809b, 0x56f0, 0x2a38, 0x4e96, 0x4e7d, 0x71c3, 0xeb6f, 0xea7, 0xfadf, 0xfa75, 0x5b7a, 0x6525, 0x8311, 0xae7, 0x5f63, 0x9d33, 0xee8a, 0x8a46, 0x8a7c, 0xea56, 0x342d, 0x7804, 0xe6a6, 0x9aa9, 0x9b33, 0x108a, 0xbd88, 0x9728, 0x8a44, 0x1a01, 0xf933, 0xca73, 0x109c, 0x2f24, 0xb8e9, 0xac13, 0x1c2, 0x2732, 0x71fe, 0x65a0, 0x4568, 0xdae1, 0xb85c, 0x2efb, 0x91c3, 0x193a, 0x3e78, 0x49f4, 0x5811, 0xc453, 0x3ea5, 0x6ccd, 0xd92f, 0xf1d6, 0x9c68, 0xf3fa, 0xf980, 0xf05f, 0x8c9e, 0x7e28, 0xc42f, 0x20b2, 0x71fc, 0xff3e, 0xdd2a, 0xdf0f, 0xece0, 0x8ab2, 0xef22, 0x2958, 0x5848, 0xd919, 0xd290, 0x7c25, 0x8cda, 0xe497, 0x27d1, 0xfa5c, 0x3dcb};
	uint16_t publicExponentA[sizePuExpA] = {0x1, 0x0001};
	uint16_t privateExponentA[sizePrExpA] = { 0x1a1f, 0x98b8, 0x592b, 0x4737, 0x13d9, 0x7a0c, 0x6a01, 0xb65f, 0x4fa7, 0x3a53, 0xcccd, 0x62ab, 0x48ca, 0x5c64, 0xa2d8, 0x332a, 0x2efe, 0x5c8a, 0xbcfd, 0xb69d, 0x36bd, 0x35ad, 0xcc5f, 0x5e46, 0x4570, 0x7f8e, 0x36c6, 0xa913, 0xc3e8, 0x296f, 0xaf2e, 0x71ec, 0x8304, 0x474e, 0x3996, 0x8cb1, 0x74c2, 0x2d6a, 0xe96d, 0xdd9e, 0xc82e, 0x8b2c, 0x37fb, 0xc35f, 0x43b6, 0x7600, 0x8655, 0x4f1c, 0x31f4, 0x1c6a, 0xd1, 0x3453, 0x85c0, 0xbeca, 0x6219, 0xfdd9, 0x38fd, 0x86d4, 0xcf18, 0x1063, 0xe4ef, 0x969c, 0x947, 0x6ba8, 0xbb2b, 0x257e, 0x4e1c, 0x6eb3, 0x2e5f, 0x4e2e, 0x696a, 0xf704, 0xbc6a, 0x2dc7, 0x2bc9, 0x75e5, 0xafad, 0x105b, 0x65e3, 0xbf83, 0x5f6e, 0xef7e, 0xfd24, 0xda7f, 0x1a3d, 0x488, 0xd7b, 0xe0d7, 0x2022, 0x301d, 0xf62f, 0x9e4, 0x3e9e, 0xf454, 0xae1b, 0x83f0, 0xfa7, 0x2309, 0x4f3d, 0x4f8e, 0x50c9, 0x9d3e, 0x59c1, 0xb668, 0xc49d, 0x3841, 0xd20f, 0xf11a, 0xebb8, 0xdfcd, 0x2a08, 0xc175, 0x31e1, 0xb339, 0xc6af, 0x2298, 0x5613, 0x9767, 0x1bd, 0xed14, 0x9d80, 0x4b26, 0x3994, 0x9347, 0x5b1b, 0xf4bd, 0x69ec, 0x7241};

	uint16_t x[expLengthMAX] = {0};
	uint16_t y[expLengthMAX] = {0};
	uint16_t gx[modLength] = {0};
	uint16_t gy[modLength] = {0};

	uint8_t K1[encryptKeyLength] = {0};
	uint8_t K2[encryptKeyLength] = {0};
	
	uint8_t messageB[sizeMessageAB] = {0};
	uint16_t tempEMB[sizeModulusB] = {0};
	uint8_t EMB[sizeModulusB*2] = {0};
	uint8_t encodedMessageB[sizeModulusB*2] = {0};
	uint16_t identityBVerified = 0;
	
	uint8_t messageA[sizeMessageAB] = {0};
	uint8_t encodedMessageA[sizeMessageAB] = {0};
	uint16_t tempEMA[sizeModulusA] = {0};
	uint8_t EMA[sizeModulusA*2] = {0};
	uint16_t receivedMessageA[sizeModulusA] = {0};
	uint16_t receivedMessageB[sizeModulusB] = {0};
	uint16_t identityAVerified = 0;
	
	uint8_t keyInString[encryptKeyLength] = {0};
	uint8_t key[encryptKeyLength] = {0};
    uint8_t data[MAX_MESSAGE_LENGTH] = "hello there 0123456789 hello there 0123456789";
    uint8_t ciphertext[IVlength + MAX_TRANSMISSION_BLOCK_LENGTH + SHA256_DIGEST_LENGTH] = {0};
    uint8_t plaintext[MAX_MESSAGE_LENGTH] = {0};
    uint8_t tempLength = 0;
    uint16_t msgSize[1] = {0};

    /* Processing keys = make sure its in char */
    uint16_t keySize = (uint16_t) strlen((char*)key); 	/* IS A PATCH: Not guaranteed to work if first input is 0*/
	
	/**** KEY ESTABLISHMENT : the Diffie-Hellman scheme ****/
	/*** STS - Protocol ***/
	printf("\n\nStart of the STS protocol...\n");
	printf("Secret key creation by poth parties...\n");

	/* A computes g^x mod p and sends it to B */
	printf("A computes g^x mod p\n");
	createExponent(x,expLengthMAX);
	computePartOfKey(g,p,x,gx,baseLength,modLength,expLengthMAX);
	
	/* B computes g^y mod p and sends it to A */
	printf("B computes g^y mod p\n");
	createExponent(y,expLengthMAX);
	computePartOfKey(g,p,y,gy,baseLength,modLength,expLengthMAX);
	
	printf("B receives (g^x) mod p from A and A receives (g^y) mod p from B\n");
	
	
	/** B - KEY CREATION + ENTITY AUTHENTICATION **/
	/** B sends message to A to prove identity **/
	printf("Start of authentication of B\n");
	/* B calculates the key = (g^x)^y mod p and encodes,signs and encrypts the message (g^y mod p)||(g^x mod p) */
	calculateKey(gx,p,y,K1,modLength,modLength,expLengthMAX);
	printf("Key created by B = (g^x)^y mod p\n");
	printArray8(K1, "key", encryptKeyLength);
	
 	createMessage(gy, gx, messageB,modLength);
	signatureMessage(messageB, encodedMessageB);
	
	signMessage(encodedMessageB, tempEMB, modulusB, privateExponentB, sizeMessageAB, sizeModulusB, sizePrExpB);
	encryptMessage(tempEMB, EMB, sizeModulusB, K1);
	printArray8(messageB,"Original message B -> A",sizeMessageAB);
	printArray8(EMB, "Transmitted message", sizeModulusB*2);
	printf("B sends g^y mod p and Sb(g^y mod p || g^x mod p) to A\n");
	
	/* A calculates the key = (g^y)^x mod p */
	calculateKey(gy,p,x,K2,modLength,modLength,expLengthMAX);
	printf("Key created by A = (g^y)^x mod p\n");
	printArray8(K2, "key", encryptKeyLength);
	/* K1 = K2 = the secret key */
		
	/* A verifies the signature of B after receiving EMB */
	createMessage(gy, gx, messageB, modLength);
	decryptMessage(EMB, receivedMessageB, sizeModulusB*2, K2);
	unsignMessage(receivedMessageB, encodedMessageB, modulusB, publicExponentB, sizeModulusB, sizeModulusB, sizePuExpB);
	
	identityBVerified = verifySignature(messageB, encodedMessageB);
	if (identityBVerified == 1)
		printf("Authentication B succeeded\n\n");
	else
		printf("Authentication B failed\n\n");
	
	
	
	/** A - KEY CREATION + ENTITY AUTHENTICATION **/
	/** A sends message to B to prove identity **/
	printf("Start of authentication of A\n");
	createMessage(gx, gy, messageA, modLength);
	signatureMessage(messageA, encodedMessageA);

	signMessage(encodedMessageA, tempEMA, modulusA, privateExponentA, sizeMessageAB,sizeModulusA, sizePrExpA);
	encryptMessage(tempEMA, EMA, sizeModulusA, K2);
	printArray8(messageA,"Original message A -> B",sizeMessageAB);
	printArray8(EMA, "Transmitted message", sizeModulusA*2);
	printf("A sends Sa(g^x mod p || g^y mod p) to B\n");
	
	/** B receives message of A and checks A's identity **/
	createMessage(gx, gy, messageA, modLength);
	decryptMessage(EMA, receivedMessageA, sizeModulusA*2, K1);
	unsignMessage(receivedMessageA, encodedMessageA, modulusA, publicExponentA, sizeModulusA, sizeModulusA, sizePuExpA);
	
	identityAVerified = verifySignature(messageA, encodedMessageA);
	if (identityAVerified == 1)
		printf("Authentication A succeeded\n\n");
	else
		printf("Authentication A failed\n\n");
	
	
	
	/*** DATA TRANSMISSION ***/
	printf("\n Start of the Data Transmission...\n\n");
	copyArray8(K1, key, encryptKeyLength);
    msgSize[0] = (uint16_t) strlen((char*)data); 	/* Not guaranteed to work if first input is 0*/

    hexToString(keyInString, key, keySize);
	
	encrypt(ciphertext, msgSize, data, keyInString, keySize*2);
	decrypt(plaintext, msgSize, ciphertext, keyInString, keySize*2);
	tempLength = (uint8_t) msgSize[0]; 

	/* Printout operation summary */
	printf("\n---\nSummary I ...\n---\n");
	printf("Plaintext before encryption: "); printCharNoSpaces(data, tempLength);
	printf("\nCiphertext after encryption: "); printArrayNoSpaces(ciphertext, tempLength );
	printf("\nPlaintext after decryption: "); printCharNoSpaces(plaintext, tempLength);

	
	return 0;
}
