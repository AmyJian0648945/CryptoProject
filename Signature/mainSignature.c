#include<stdint.h>
#include<stdio.h>
#include<string.h>
#include "useSHA256.h"
#include "pseudoRandNumGenerator.h"
#include "maskGenerationFunction.h"
#include "signatureMessage.h"
#include "verifySignature.h"
#include "formatting.h"

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
		printf("Verification succeeded!\n");
	else
		printf("Verification failed!\n");
	return 0;
}

