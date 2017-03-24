

////////// Define Macros Here //////////

#define MSG_LENGTH              13    /* length of the message to be sent into HMAC */
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
    uint8_t inputMessage[MSG_LENGTH] = {0x0a,0x0b,0x0c,1,2,3,4,5,6,7,8,9,0};
    

    //hmac(output, secretKey, inputMessage);
    printf("Output:"); printArray(secretKey, HMAC_SECRET_KEY_SIZE);
    simpleHash(output, secretKey);
    printf("Output:"); printArray(output, SHA256_DIGEST_LENGTH);



    printArrayNoSpaces(secretKey, HMAC_SECRET_KEY_SIZE);
    printArrayNoSpaces(output, HMAC_SECRET_KEY_SIZE);

	return 0;
}



//e1b85b27d6bcb05846c18e6a48f118e89f0c0587140de9fb3359f8370d0dba08
//7f65f220efa28cd91866e11d9a7ed72de387968947853b85cf9581704acb3538







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