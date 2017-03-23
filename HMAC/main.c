

#ifndef SHA256_DIGEST_LENGTH     
#define SHA256_DIGEST_LENGTH    32  
#endif /* SHA256_DIGEST_LENGTH */


#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include"useSHA256.h" // hashes messages
#include"hmac.h"

int main(){
	uint8_t output[32] = {0};
    hmac(output, output);




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