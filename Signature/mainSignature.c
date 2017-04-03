
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../helpfulFunctions.h"
#include "../sha2/useSHA256.h"
#include "../CPRNG/pseudoRandNumGenerator.h"
#include "maskGenerationFunction.h"
#include "signatureMessage.h"
#include "verifySignature.h"
#include "formatting.h"
/* File for testing purposes. */

 
 #include <time.h>
 #include <sys/types.h>
 

int main(void){
	
	uint8_t message[256] =  {0};
	uint8_t encodedMessage[256] = {0};
	uint16_t encodedMessageReformed[128] = {0};
	uint16_t verificationCorrect = 0;
	
	
	RNG(message, 256);
	
	signatureMessage(message,encodedMessage);

	from8to16(encodedMessage,encodedMessageReformed);

	from16to8(encodedMessageReformed,encodedMessage);

	verificationCorrect = verifySignature(message,encodedMessage);
	if (verificationCorrect == 1)
		printf("\n Verification succeeded!\n");
	else
		printf("\n Verification failed!\n");
	return 0;
}

