

////////// Define Macros Here //////////

#define MSG_LENGTH              16    /* length of the message to be sent into HMAC */
#define MAX_MESSAGE_LENGTH      500
#define HMAC_SECRET_KEY_SIZE    32
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
    //uint8_t secretKey[HMAC_SECRET_KEY_SIZE] = {0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0A,0x0B,0x0C,0x0D,0x0E,0x0F,0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0A,0x0B,0x0C,0x0D,0x0E,0x0F};
    //uint8_t inputMessage[MSG_LENGTH] = {0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0A,0x0B,0x0C,0x0D,0x0E,0x0F};
    
    uint8_t secretKey[HMAC_SECRET_KEY_SIZE] = {0x0b,0x0b,0x0b,0x0b,0x0b,0x0b,0x0b,0x0b,0x0b,0x0b,0x0b,0x0b,0x0b,0x0b,0x0b,0x0b,0x0b,0x0b,0x0b,0x0b};
    uint8_t inputMessage[MSG_LENGTH] = {48,69,20,54,68,65,72,65};
    //uint8_t test[32] = "0123456789ABCDEF";

    uint8_t temp[MAX_MESSAGE_LENGTH] = {0}, temp1[MAX_MESSAGE_LENGTH] = {0};
    uint16_t i=0;



    printf("--------------------BEGIN:--------------------\n");
    //printf("Secret Key: "); printArrayNoSpaces(secretKey, HMAC_SECRET_KEY_SIZE);
    //printf("inputMessage: "); printArrayNoSpaces(inputMessage, MSG_LENGTH);
    hexToString(temp, secretKey, HMAC_SECRET_KEY_SIZE);
    printf("secret key: "); printCharNoSpaces(temp, HMAC_SECRET_KEY_SIZE*2);

    hexToString(temp1, inputMessage, MSG_LENGTH);
    printf("Input message: "); printCharNoSpaces(temp1, MSG_LENGTH*2);


    printf("................end BEGIN:....................\n");
    

   




    hmac(output, secretKey, inputMessage); // secret key and input message length are specified in the macros
    
    printf("--------------------FINAL:--------------------\n");
    printf("Output:"); printArrayNoSpaces(output, SHA256_DIGEST_LENGTH);
    printf("................end FINAL:....................\n\n");



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