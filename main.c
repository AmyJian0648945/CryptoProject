

#ifndef SHA256_DIGEST_LENGTH     
#define SHA256_DIGEST_LENGTH    32  
#endif /* SHA256_DIGEST_LENGTH */






#include<stdlib.h>
#include<stdio.h>
#include<string.h>

#include"sha2/useSHA256.h" // hashes messages
#include"HMAC/hmac.h"


int main(){
	uint8_t output[SHA256_DIGEST_LENGTH] = {0};

    uint32_t keySize = 128;
    

    hmac(output, output, output);





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