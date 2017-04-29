//#include "../Header/keyEstablishmentFunctions.h"
//
//void repositionZeros(uint16_t *array, uint16_t size){
//
//	uint16_t stack[MAXSIZE] = {0};
//	uint16_t actualSize = 0;
//	uint16_t stop = 0;
//	int i;
//
//	actualSize = size;
//	i = size-1;
//	while (stop == 0){
//		if (array[i] != 0){
//			actualSize = i+1;
//			stop = 1;
//		} else {
//			i = i-1;
//			stop = 0;
//		}
//	}
//
//	copyArray16(array,stack,size);
//	zerosArray(array,size);
//	for(i=0;i<actualSize;i++){
//		array[i+(size-actualSize)] = stack[i];
//	}
//
//}
//
//
//void createExponent( uint16_t *x, uint16_t sizeX){
//
//	uint8_t x8[expLengthMAX*2] = {0};
//	uint8_t sizeExponent[1] = {0};
//	uint16_t sizeCast = 0;
//
//	/* Creates a random size of the exponent */
//	while (sizeExponent[0] == 0){
//		RNG(sizeExponent,1);
//	}
//
//	sizeCast = (uint16_t) sizeExponent[0]/8 + 1;
//
//	/*while (numberIsZero8(x8, expLengthMAX*2)){
//		RNG(x8,sizeCast);
//	}*/
//
//	RNG(x8,sizeCast);
//	from8to16(x8,x,expLengthMAX);
//	repositionZeros(x,expLengthMAX);
//
//}
//
//void computePartOfKey(uint16_t *g, uint16_t *m, uint16_t *exponent, uint16_t *partOfKey, uint16_t sizeG, uint16_t sizeM, uint16_t sizeExp){
//
//	montExp(g,m,exponent,partOfKey,sizeG,sizeM,sizeExp);
//}
//
//void calculateKey(uint16_t *g, uint16_t *m, uint16_t *exponent, uint8_t *Key, uint16_t sizeG, uint16_t sizeM, uint16_t sizeExp){
//
//	uint16_t tempKey[modLength] = {0};
//	uint8_t tempKey8[modLength*2] = {0};
//	uint8_t hashKey[HASHLEN] = {0};
//	int i;
//
//	montExp(g,m,exponent,tempKey,sizeG,sizeM,sizeExp);
//	from16to8(tempKey,tempKey8,sizeM);
//
//	simpleHashWithLength(hashKey,tempKey8,2*sizeM);
//	for(i=0;i<(HASHLEN/2);i++){
//		Key[i] = hashKey[i];
//	}
//}
//
//void createMessage( uint16_t *gx, uint16_t *gy, uint8_t *message, uint16_t sizegxgy){
//
//	uint8_t part[modLength*2] = {0};
//	from16to8(gx, part, sizegxgy);
//	concat(message, part, 0, sizegxgy*2);
//	from16to8(gy, part, sizegxgy);
//	concat(message, part, sizegxgy*2, sizegxgy*2);
//
//}
//
//
///* 	COMBINED FUNCTIONS INTO signAndEncryptMessage
//void signMessage(uint8_t *message, uint16_t *signedMessage, uint16_t *modulus, uint16_t *privateExponent, uint16_t sizeMessage, uint16_t sizeMod, uint16_t sizePrivateExp){
//
//	from8to16(message, signedMessage, sizeMessage/2);
//	montExp(signedMessage, modulus, privateExponent, signedMessage,sizeMessage/2, sizeMod, sizePrivateExp);
//
//}
//
//void encryptMessage(uint16_t *message, uint8_t *encryptedMessage, uint16_t sizeMessage, uint8_t *key){
//	uint16_t msgLength[1] = {0};
//
//	msgLength[0] = sizeMessage*2;
//	from16to8(message, encryptedMessage, sizeMessage);
//	simpleEncrypt(encryptedMessage, encryptedMessage, msgLength, key);
//}
//*/
//void signAndEncryptMessage(uint8_t *message, uint8_t *encryptedMessage, uint16_t *modulus, uint16_t *privateExponent, uint8_t *key){
//
//	uint16_t msgLength[1] = {0};
//	uint16_t signedMessage[sizeModulusAB] = {0};
//
//	/* Sign Message */
//	from8to16(message, signedMessage, sizeMessageAB/2);
//	montExp(signedMessage, modulus, privateExponent, signedMessage, sizeMessageAB/2, sizeModulusAB, sizePrExpAB);
//
//	/* Encrypt Message*/
//	msgLength[0] = sizeMessageAB*2;
//	from16to8(signedMessage, encryptedMessage, sizeMessageAB);
//	simpleEncrypt(encryptedMessage, encryptedMessage, msgLength, key);
//
//}
//
//void decryptMessage(uint8_t *message, uint16_t *decryptedMessage, uint16_t sizeMessage, uint8_t *key){
//
//	uint16_t msgLength[1] = {0};
//
//	msgLength[0] = sizeMessage;
//	simpleDecrypt(message, message, msgLength, key);
//	from8to16(message, decryptedMessage, sizeMessage/2);
//
//}
//void unsignMessage(uint16_t *signedMessage, uint8_t *message, uint16_t *modulus, uint16_t *publicExponent, uint16_t sizeSignedMessage, uint16_t sizeMod, uint16_t sizePublicExp){
//
//	montExp(signedMessage, modulus, publicExponent, signedMessage, sizeSignedMessage, sizeMod, sizePublicExp);
//	from16to8(signedMessage, message, sizeMod);
//
//}
//
//
//
//void decryptAndUnsignMessage(uint8_t *message, uint8_t *unsignedMessage, uint8_t *key, uint16_t *modulus, uint16_t *publicExponent){
//
//	uint16_t msgLength[1] = {0};
//	uint16_t decryptedMessage[sizeModulusAB] = {0};
//
//	/* Decrypt Message */
//	msgLength[0] = sizeMessageAB;
//	simpleDecrypt(message, message, msgLength, key);
//	from8to16(message, decryptedMessage, sizeMessageAB/2);
//
//	/* Unsign Message */
//	montExp(decryptedMessage, modulus, publicExponent, decryptedMessage, sizeMessageAB/2, sizeModulusAB, sizePuExpAB);
//	from16to8(decryptedMessage, unsignedMessage, sizeModulusAB);
//
//}
//
//
//
//void from8to16(uint8_t *input, uint16_t *output, uint16_t size){
//	int k;
//	uint16_t first8bits = 0;
//	uint16_t last8bits = 0;
//	uint16_t newnumber = 0;
//
//	for (k = 0; k < size; k++){
//		first8bits = ((uint16_t)input[2*k])<<8;
//		last8bits = (uint16_t)input[2*k+1];
//		newnumber = first8bits + last8bits;
//		output[k] = newnumber;
//	}
//}
//
//void from16to8(uint16_t *input, uint8_t *output, uint16_t size){
//	int k;
//	uint8_t first8bits = 0;
//	uint8_t last8bits = 0;
//
//	for (k=0;k<size;k++){
//		first8bits = (uint8_t)(input[k]>>8);
//		last8bits = (uint8_t)input[k];
//		output[2*k] = first8bits;
//		output[2*k+1] = last8bits;
//	}
//}
//
//
