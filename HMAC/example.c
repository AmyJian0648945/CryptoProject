

////////// Define Macros Here //////////


#define MAX_MESSAGE_LENGTH      500
#define DATA_BLOCK_SIZE         64


#ifndef SHA256_DIGEST_LENGTH     
#define SHA256_DIGEST_LENGTH    32  
#endif 


#include<stdlib.h>
#include<stdio.h>
#include<string.h>

#include"sha2/useSHA256.h" // hashes messages
#include"HMAC/hmac.h"


int main(){
	uint8_t output[SHA256_DIGEST_LENGTH] = {0};

    /* * * Using strings to calculate HMAC * * */
    uint8_t secretKey[MAX_MESSAGE_LENGTH] = "Jefe";
    uint8_t inputMessage[MAX_MESSAGE_LENGTH] = "what do ya want for nothing?";
    uint16_t secretKeySize = strlen(secretKey);
    uint16_t inputMessageSize = strlen(inputMessage);

    hmac(output, secretKey, inputMessage, secretKeySize, inputMessageSize); // secret key and input message length are specified in the macros
    
    printf("Secret Key:"); printCharNoSpaces(secretKey, secretKeySize);
    printf("Input Message:"); printCharNoSpaces(inputMessage, inputMessageSize);
    printf("Output:"); printArrayNoSpaces(output, SHA256_DIGEST_LENGTH);
    printf("\n\n");





    

    /* * * Using hex numbers to calculate HMAC * * */

    uint8_t secretKeyHEX[MAX_MESSAGE_LENGTH] = {0x10, 0x01, 0x02, 0x03, 0x0A, 0x0B, 0xFF};
    uint8_t inputMessageHEX[MAX_MESSAGE_LENGTH] = {0xAA, 0xBB, 0xCC, 0xDD};
    uint8_t temp1[MAX_MESSAGE_LENGTH] = {0}, temp2[MAX_MESSAGE_LENGTH] = {0};
    secretKeySize = strlen(secretKeyHEX);  /* THIS MIGHT CAUSE ERROR IF FIRST ELEMENT ==0*/
    inputMessageSize = strlen(inputMessageHEX);  /* THIS MIGHT CAUSE ERROR IF FIRST ELEMENT ==0*/

    // Convert hex to char (string)
    hexToString(temp1, secretKeyHEX, secretKeySize);
    hexToString(temp2, inputMessageHEX, inputMessageSize);

    hmac(output, temp1, temp2, secretKeySize*2, inputMessageSize*2); // secret key and input message length are specified in the macros
    
    printf("Secret Key:"); printCharNoSpaces(temp1, secretKeySize*2);
    printf("Input Message:"); printCharNoSpaces(temp2, inputMessageSize*2);
    printf("Output:"); printArrayNoSpaces(output, SHA256_DIGEST_LENGTH);




	return 0;
}





/*************** Protocol ****************
	AES - 	Encryption method
    		Key size 128 bits, 
    		block size 128 bits 
            
    SHA-256 - hash function 
    		outputs block size 256 bits, 
            no input on message bits
            
    HMAC-SHA256 - MAC: message authentication & integrity, 
    		outputs blocks of 256 bits
            
    RSASSA-PSS - digital signature purposes
*******************************************/