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

	/* Creates a random size of the exponent that is not equal to zero */
	while (sizeExponent[0] == 0){
		RNG(sizeExponent,1);
	}
	/* Maximum value for sizeExponent is 255 => x8: 255*8 = 2040 bits
	Maximum number of bits for the exponent: 512 bits => 64 bytes */
 	sizeCast = (uint16_t) sizeExponent[0];
	if (sizeCast > expLengthMAX*4){
		sizeCast = sizeCast>>3;
		/* sizeCast divided by eight */
	}
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

void calculateKey(uint32_t *base, uint32_t *m, uint32_t *exponent, uint8_t *Key){
	
	uint32_t tempKey[modLength] = {0};
	uint8_t tempKey8[modLength*2] = {0};
	uint8_t hashKey[HASHLEN] = {0};

	montExp(base,m,exponent,tempKey, modLength, modLength, expLengthMAX);
	from32to8(tempKey,tempKey8,modLength);
	simpleHashWithLength(hashKey,tempKey8,4*modLength);
	copyArray8(hashKey, Key, KEYLEN);
}

void createMessage( uint32_t *gx, uint32_t *gy, uint8_t *message){
	
	uint8_t part[modLength*4] = {0};
	from32to8(gx, part, modLength);
	concat(message, part, 0, modLength*4);
	from32to8(gy, part, modLength);
	concat(message, part, modLength*4, modLength*4);
	
}


/* 	COMBINED FUNCTIONS INTO signAndEncryptMessage */
/* void signMessage(uint8_t *message, uint32_t *signedMessage, uint32_t *modulus, uint32_t *privateExponent){
		
	from8to32(message, signedMessage, sizeMessageAB/4);
	montExp(signedMessage, modulus, privateExponent, signedMessage,sizeMessageAB/4, sizeModulusAB, sizePrExpAB);
	
}

void encryptMessage(uint32_t *message, uint8_t *encryptedMessage, uint8_t *key){
	uint16_t msgLength[1] = {0};

	msgLength[0] = sizeMessageAB;
	from32to8(message, encryptedMessage, sizeMessageAB/4);
	simpleEncrypt(encryptedMessage, encryptedMessage, msgLength, key);
} */

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
/*	COMBINED FUNCTIONS INTO decryptAndUnsignMessage */
/* void decryptMessage(uint8_t *message, uint32_t *decryptedMessage, uint8_t *key){
	
	uint16_t msgLength[1] = {0};
	
	msgLength[0] = sizeMessageAB;
	simpleDecrypt(message, message, msgLength, key);
	from8to32(message, decryptedMessage, sizeMessage/4);

}
void unsignMessage(uint32_t *signedMessage, uint8_t *message, uint32_t *modulus, uint32_t *publicExponent){

	montExp(signedMessage, modulus, publicExponent, signedMessage, sizeMessageAB/4, sizeModulusAB, sizePuExpAB);
	from32to8(signedMessage, message, sizeModulusAB);

} */
void decryptAndUnsignMessage(uint8_t *message, uint8_t *unsignedMessage, uint8_t *key, uint32_t *modulus, uint32_t *publicExponent){

	uint16_t msgLength[1] = {0};
	uint32_t decryptedMessage[sizeModulusAB] = {0};
	/* sizeModulusAB 32 = sizeMessageAB/4 */

	/* Decrypt Message */
	msgLength[0] = sizeMessageAB;
	simpleDecrypt(message, message, msgLength, key);
	copyArray8(message, unsignedMessage, sizeMessageAB);
	from8to32(message, decryptedMessage, sizeMessageAB/4);

	/* Unsign Message */
	montExp(decryptedMessage, modulus, publicExponent, decryptedMessage, sizeModulusAB, sizeModulusAB, sizePuExpAB);
	from32to8(decryptedMessage, unsignedMessage, sizeModulusAB);
	
}



void from8to32(uint8_t *input, uint32_t *output, uint16_t size){
	int k;
	uint32_t newnumber = 0;
	uint32_t value1 = 0;
	uint32_t value2 = 0;
	uint32_t value3 = 0;
	uint32_t value4 = 0;

	for (k=0;k<size;k++){
		value1 = (uint32_t)input[k*4]<<24;
		value2 = (uint32_t)input[k*4+1]<<16;
		value3 = (uint32_t)input[k*4+2]<<8;
		value4 = (uint32_t)input[k*4+3];
		newnumber = value1 + value2 + value3 + value4;
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


