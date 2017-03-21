/******* Header Files *******/

/******* Variables *******/
// Function outputs first, then input!


int main(){
	printf("Hello World!");
	return 0;
}



/*************** Todo list ****************
1. Define word length (16 bit or 32 bit)
2. Generate private/public key pair for Alice and Bob
3. 
*******************************************/






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