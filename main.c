

////////// Define Macros Here //////////

#define MSG_LENGTH              40    /* length of the message to be sent into HMAC */
#define MAX_MESSAGE_LENGTH      1000
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
    uint8_t secretKey[HMAC_SECRET_KEY_SIZE] = {1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2};
    uint8_t inputMessage[MSG_LENGTH] = {0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0A,0x0B,0x0C,0x0D,0x0E,0x0F};
    
    //uint8_t test[32] = "0123456789ABCDEF";

    
    printf("Input"); printArray(secretKey, HMAC_SECRET_KEY_SIZE);
    hmac(output, secretKey, inputMessage); // secret key and input message length are specified in the macros
    printf("Output:"); printArray(output, SHA256_DIGEST_LENGTH);




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