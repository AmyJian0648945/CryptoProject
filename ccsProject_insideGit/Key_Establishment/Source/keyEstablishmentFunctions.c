#include "../Header/keyEstablishmentFunctions.h"

void repositionZeros(uint16_t *array, uint16_t size){
	
	uint16_t stack[MAXSIZE] = {0};
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
	
	copyArray16(array,stack,size);
	zerosArray(array,size);
	for(i=0;i<actualSize;i++){
		array[i+(size-actualSize)] = stack[i];
	}

}


void createExponent( uint16_t *x, uint16_t sizeX){
		
	uint8_t sizeExponent[1] = {0};
	uint8_t x8[expLengthMAX*2] = {0};
	uint16_t sizeCast = 0;
	
	RNG(sizeExponent,1);
	while (sizeExponent[0] == 0){
		RNG(sizeExponent,1);
	}
	sizeCast = (uint16_t) sizeExponent[0];
	RNG(x8,sizeCast);
	from8to16(x8,x,expLengthMAX);
	while (numberIsZero(x, expLengthMAX)){
		RNG(x8,sizeCast);
		from8to16(x8,x,expLengthMAX);
	}
	repositionZeros(x,expLengthMAX);
	
}

void computePartOfKey(uint16_t *g, uint16_t *m, uint16_t *exponent, uint16_t *partOfKey, uint16_t sizeG, uint16_t sizeM, uint16_t sizeExp){

	montExp(g,m,exponent,partOfKey,sizeG,sizeM,sizeExp);
}

void calculateKey(uint16_t *g, uint16_t *m, uint16_t *exponent, uint8_t *Key, uint16_t sizeG, uint16_t sizeM, uint16_t sizeExp){
	
	uint16_t tempKey[modLength] = {0};
	uint8_t tempKey8[modLength] = {0};
	uint8_t hashKey[HASHLEN] = {0};
	int i;
	
	montExp(g,m,exponent,tempKey,sizeG,sizeM,sizeExp);
	from16to8(tempKey,tempKey8,sizeM);

	simpleHashWithLength(hashKey,tempKey8,2*sizeM);
	for(i=0;i<(HASHLEN/2);i++){
		Key[i] = hashKey[i];
	}
	
}

void createMessage( uint16_t *gx, uint16_t *gy, uint8_t *message, uint16_t sizegxgy){
	
	uint8_t part[MAXSIZE] = {0};
	from16to8(gx, part, sizegxgy);
	concat(message, part, 0, sizegxgy*2);
	from16to8(gy, part, sizegxgy);
	concat(message, part, sizegxgy*2, sizegxgy*2);
	
}

void signMessage(uint8_t *message, uint16_t *signedMessage, uint16_t *modulus, uint16_t *privateExponent, uint16_t sizeMessage, uint16_t sizeMod, uint16_t sizePrivateExp){
		
	from8to16(message, signedMessage, sizeMessage/2);
	montExp(signedMessage, modulus, privateExponent, signedMessage,sizeMessage/2, sizeMod, sizePrivateExp);
	
}

void encryptMessage(uint16_t *message, uint8_t *encryptedMessage, uint16_t sizeMessage, uint8_t *key){

	uint16_t msgLength[1] = {0};

	msgLength[0] = sizeMessage*2;
	from16to8(message, encryptedMessage, sizeMessage);
	simpleEncrypt(encryptedMessage, encryptedMessage, msgLength, key);
}

void unsignMessage(uint16_t *signedMessage, uint8_t *message, uint16_t *modulus, uint16_t *publicExponent, uint16_t sizeSignedMessage, uint16_t sizeMod, uint16_t sizePublicExp){
		
	montExp(signedMessage, modulus, publicExponent, signedMessage, sizeSignedMessage, sizeMod, sizePublicExp);
	from16to8(signedMessage, message, sizeMod);
	
}

void decryptMessage(uint8_t *message, uint16_t *decryptedMessage, uint16_t sizeMessage, uint8_t *key){
	
	uint16_t msgLength[1] = {0};
	
	msgLength[0] = sizeMessage;
	simpleDecrypt(message, message, msgLength, key);
	from8to16(message, decryptedMessage, sizeMessage/2);

}


