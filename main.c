

#include<stdlib.h>
#include<stdio.h>
#include<string.h>

//#include"ciphers/sha2/sha2.h"
//#include"ciphers/sha2/sha2.c"

#include"CPRNG/useSHA256.h"
#include"CPRNG/pseudoRandNumGenerator.h"
#include"HMAC/hmac.h"




int main(){
	uint8_t output[SHA256_DIGEST_LENGTH] = {0};
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