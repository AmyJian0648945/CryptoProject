
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "helpfulFunctions.h"
#include "sha2/useSHA256.h"
#include "CPRNG/pseudoRandNumGenerator.h"
#include "Signature/maskGenerationFunction.h"
#include "Signature/signatureMessage.h"
#include "Signature/verifySignature.h"
#include "Signature/formatting.h"
/* File for testing purposes. */

int main(void){
	
	uint8_t message[256] =  {0};
	uint8_t encodedMessage[256] = {0};
	uint16_t encodedMessageReformed[128] = {0};
	uint16_t verificationCorrect = 0;
	
	/* PARTY A */
	
	RNG(message, 256);
	
	signatureMessage(message,encodedMessage);
	/* Because the modular exponentiation is done with 16 bit numbers. */
	from8to16(encodedMessage,encodedMessageReformed);
	/* ... modular exponentiation x^e mod n (x=message||encodedMessage;  e = private key; n = modulus)*/
	
	/* PARTY B */
	
	/* decryption: modular exponentiation x^d mod n (x = receivedMessage; d = public key of the other party; n = modulus */
	from16to8(encodedMessageReformed,encodedMessage);

	verificationCorrect = verifySignature(message,encodedMessage);
	if (verificationCorrect == 1)
		printf("\n Verification succeeded!\n");
	else
		printf("\n Verification failed!\n");
	return 0;
}

