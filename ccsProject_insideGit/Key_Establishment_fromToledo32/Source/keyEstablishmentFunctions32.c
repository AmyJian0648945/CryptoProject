#include "../Header/keyEstablishmentFunctions32.h"

void repositionZeros(uint32_t *array, uint16_t size){
	
	uint32_t stack[MAXSIZE] = {0};
	uint16_t actualSize = 0;
	uint16_t stop = 0;
	int i;
	
	actualSize = size;
	i = size-1;
	while (stop == 0){
		if (array[i] != 0){
			actualSize = i+1;
			stop = 1;
		} else {
			i = i-1;
			stop = 0;
		}
	}
	
	copyArray32(array,stack,size);
	zerosArray(array,size);
	for(i=0;i<actualSize;i++){
		array[i+(size-actualSize)] = stack[i];
	}

}


void createExponent( uint32_t *x, uint16_t sizeX){

	uint8_t x8[expLengthMAX*4] = {0};
	uint8_t sizeExponent[1] = {0};
	uint16_t sizeCast = 0;

	/* Creates a random size of the exponent */
	while (sizeExponent[0] == 0){
		RNG(sizeExponent,1);
	}

	sizeCast = (uint16_t) sizeExponent[0]/8 + 1;

	/*while (numberIsZero8(x8, expLengthMAX*2)){
		RNG(x8,sizeCast);
	}*/

	RNG(x8,sizeCast);
	from8to32(x8,x,expLengthMAX);
	repositionZeros(x,expLengthMAX);
	
}

void computePartOfKey(uint32_t *g, uint32_t *m, uint32_t *exponent, uint32_t *partOfKey){

	montExp(g,m,exponent,partOfKey, baseLength, modLength, expLengthMAX);
}

void calculateKey(uint32_t *g, uint32_t *m, uint32_t *exponent, uint8_t *Key){
	
	uint32_t tempKey[modLength] = {0};
	uint8_t tempKey8[modLength*2] = {0};
	uint8_t hashKey[HASHLEN] = {0};
	int i;

	montExp(g,m,exponent,tempKey, modLength, modLength, expLengthMAX);
	from32to8(tempKey,tempKey8,modLength);

	simpleHashWithLength(hashKey,tempKey8,4*modLength);
	for(i=0;i<(HASHLEN/2);i++){
		Key[i] = hashKey[i];
	}
}

void createMessage( uint32_t *gx, uint32_t *gy, uint8_t *message){
	
	uint8_t part[modLength*4] = {0};
	from32to8(gx, part, modLength);
	concat(message, part, 0, modLength*4);
	from32to8(gy, part, modLength);
	concat(message, part, modLength*4, modLength*4);
	
}


/* 	COMBINED FUNCTIONS INTO signAndEncryptMessage
void signMessage(uint8_t *message, uint32_t *signedMessage, uint32_t *modulus, uint32_t *privateExponent, uint16_t sizeMessage, uint16_t sizeMod, uint16_t sizePrivateExp){
		
	from8to32(message, signedMessage, sizeMessage/2);
	montExp(signedMessage, modulus, privateExponent, signedMessage,sizeMessage/2, sizeMod, sizePrivateExp);
	
}

void encryptMessage(uint32_t *message, uint8_t *encryptedMessage, uint16_t sizeMessage, uint8_t *key){
	uint16_t msgLength[1] = {0};

	msgLength[0] = sizeMessage*2;
	from32to8(message, encryptedMessage, sizeMessage);
	simpleEncrypt(encryptedMessage, encryptedMessage, msgLength, key);
}
*/
void signAndEncryptMessage(uint8_t *message, uint8_t *encryptedMessage, uint32_t *modulus, uint32_t *privateExponent, uint8_t *key){

	uint16_t msgLength[1] = {0};
	uint32_t signedMessage[sizeModulusAB] = {0};

	/* Sign Message */
	from8to32(message, signedMessage, sizeMessageAB/4);
	montExp(signedMessage, modulus, privateExponent, signedMessage, sizeMessageAB/4, sizeModulusAB, sizePrExpAB);

	/* Encrypt Message*/
	msgLength[0] = sizeMessageAB;
	from32to8(signedMessage, encryptedMessage, sizeMessageAB/4);
	simpleEncrypt(encryptedMessage, encryptedMessage, msgLength, key);

}
/*	COMBINED FUNCTIONS INTO decryptAndUnsignMessage
void decryptMessage(uint8_t *message, uint32_t *decryptedMessage, uint16_t sizeMessage, uint8_t *key){
	
	uint16_t msgLength[1] = {0};
	
	msgLength[0] = sizeMessage;
	simpleDecrypt(message, message, msgLength, key);
	from8to32(message, decryptedMessage, sizeMessage/2);

}
void unsignMessage(uint32_t *signedMessage, uint8_t *message, uint32_t *modulus, uint32_t *publicExponent, uint16_t sizeSignedMessage, uint16_t sizeMod, uint16_t sizePublicExp){

	montExp(signedMessage, modulus, publicExponent, signedMessage, sizeSignedMessage, sizeMod, sizePublicExp);
	from16to8(signedMessage, message, sizeMod);

}*/
void decryptAndUnsignMessage(uint8_t *message, uint8_t *unsignedMessage, uint8_t *key, uint32_t *modulus, uint32_t *publicExponent){

	uint16_t msgLength[1] = {0};
	uint32_t decryptedMessage[sizeMessageAB] = {0};

	/* Decrypt Message */
	msgLength[0] = sizeMessageAB;
	simpleDecrypt(message, message, msgLength, key);
	from8to32(message, decryptedMessage, sizeMessageAB/4);

	/* Unsign Message */
	montExp(decryptedMessage, modulus, publicExponent, decryptedMessage, sizeMessageAB/4, sizeModulusAB, sizePuExpAB);
	from32to8(decryptedMessage, unsignedMessage, sizeMessageAB/4);

}



void from8to32(uint8_t *input, uint32_t *output, uint16_t size){
	int k;
	uint32_t newnumber = 0;

	for (k=0;k<size;k++){
		newnumber += (uint32_t)input[k*4]<<24;
		newnumber += (uint32_t)input[k*4+1]<<16;
		newnumber += (uint32_t)input[k*4+2]<<8;
		newnumber += (uint32_t)input[k*4+3];
		output[k] = newnumber;
	}
}

void from32to8(uint32_t *input, uint8_t *output, uint16_t size){
	int k;

	for (k=0;k<size;k++){
		output[k*4] = (uint8_t)(input[k]>>24);
		output[k*4+1] = (uint8_t)(input[k]>>16);
		output[k*4+2] = (uint8_t)(input[k]>>8);
		output[k*4+3] = (uint8_t)input[k];
	}
}


