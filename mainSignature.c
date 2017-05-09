#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "library/helpfulFunctions.h"
#include "library/useSHA256.h"
#include "library/PRNG.h"
#include "Key_Establishment/Header/maskGenerationFunction.h"
#include "Key_Establishment/Header/signatureMessage.h"
#include "Key_Establishment/Header/verifySignature.h"
#include "Key_Establishment/Header/keyEstablishmentFunctions32.h"

int main(void){
	
	uint8_t message[128] =  {0};
	uint8_t encodedMessage[128] = {0};
	uint32_t encodedMessageReformed[32] = {0};
	uint16_t verificationCorrect = 0;
	
	/* PARTY A */
	
	RNG(message, 128);
	
	signatureMessage(message,encodedMessage);
	/* Because the modular exponentiation is done with 16 bit numbers. */
	from8to32(encodedMessage,encodedMessageReformed,128/4);
	/* ... modular exponentiation x^e mod n (x=message||encodedMessage;  e = private key; n = modulus)*/
	
	/* PARTY B */
	
	/* decryption: modular exponentiation x^d mod n (x = receivedMessage; d = public key of the other party; n = modulus */
	from32to8(encodedMessageReformed,encodedMessage,128/4);

	verificationCorrect = verifySignature(message,encodedMessage);
	if (verificationCorrect == 1)
		printf("\n Verification succeeded!\n");
	else
		printf("\n Verification failed!\n");
	return 0;
}

