
#include "aes.h"
#include "aes.c"

#define AES_KEY_SIZE 128



/* * * DEBUGGING STAAAAAATION! * * * * * * * * */ 
//#define step3 1
#define step4_aesBeforeLoop 1
//#define checkAES 1
//#define step4_insideAESLoop 1
/* * * Uncomment if you want to activate! * * */




void AES(uint8_t*, uint8_t*, uint8_t*);
void aesCBCencrypt(uint8_t*, uint8_t*, uint8_t*, uint8_t*, uint8_t*);
void padding(uint8_t*, uint8_t*); 
    /* Pads data until a multipe of 16*/



void aes(uint8_t* output, uint8_t* plaintext, uint8_t* key){
    aes_key aeskey;

    aes_set_encrypt_key(&aeskey, key, 128);
    aes_encrypt(&aeskey, plaintext, output);






    #ifdef checkAES
    printf("Key: "); printArrayNoSpaces(key, encryptKeyLength);
    printf("Plaintext: "); printArrayNoSpaces(tempMsg, aes_BLOCK_SIZE);
    printf("Output: "); printArrayNoSpaces(output, aes_BLOCK_SIZE);

    /*
    if (memcmp(output, "\x3a\xd7\x7b\xb4\x0d\x7a\x36\x60\xa8\x9e\xca\xf3\x24\x66\xef\x97", 16) != 0) {
        fprintf(stderr, "Encryption failed. \n");
        abort();
    }
    else fprintf(stderr, "Encryption succeeded! \n");
    */
    #endif

    
 
/*
    aes_set_decrypt_key(&aeskey, "\x2b\x7e\x15\x16\x28\xae\xd2\xa6\xab\xf7\x15\x88\x09\xcf\x4f\x3c", 128);
    aes_decrypt(&aeskey, "\x3a\xd7\x7b\xb4\x0d\x7a\x36\x60\xa8\x9e\xca\xf3\x24\x66\xef\x97", output);

    if (memcmp(output, "\x6b\xc1\xbe\xe2\x2e\x40\x9f\x96\xe9\x3d\x7e\x11\x73\x93\x17\x2a", 16) != 0) {
        fprintf(stderr, "Decryption failed\n");
        abort();
    }
*/

    
}

void aesCBCencrypt(uint8_t* ciphertext, uint8_t* inputMsg, uint8_t* msgLength, 
             uint8_t* IV, uint8_t* key)
{
    uint8_t temp[aes_BLOCK_SIZE] = {0};
    uint8_t checkingArray[aes_BLOCK_SIZE] = {0};
    uint8_t CBCrounds = 0;
    uint16_t i = 0;



    // Figuring out how many AES_CBC rounds is needed
    CBCrounds = *msgLength;
    CBCrounds = CBCrounds / aes_BLOCK_SIZE;

    // Copy IV into temp, in order to initialise the first plaintext
    copyArrayFrom0(temp, IV, IVlength);
    

    printf("Msg = "); printArray(inputMsg, *msgLength);


    #ifdef step4_aesBeforeLoop /* Debugging statement*/
    printf("CBCrounds of rounds = %d, msgLength = %d\n", CBCrounds, *msgLength);
    printf("IV: (should be the same as 'temp' below) "); printArray(IV, IVlength);
    printf("temp: (should be the same as 'IV' above) "); printArray(temp, IVlength);
    #endif

    



    // Go through all rounds AES, each with input 128bits of message
    for(i = 0; i < CBCrounds; i++){
        // XOR previous ciphertext with current plaintext (unless its the first iteration)
        XOR(temp, temp, inputMsg + i*(aes_BLOCK_SIZE), aes_BLOCK_SIZE);




        #ifdef step4_insideAESLoop
        printf("Index = %d\n", i*(aes_BLOCK_SIZE));
        XOR(checkingArray, temp, inputMsg + i*(aes_BLOCK_SIZE), aes_BLOCK_SIZE);
        printf("Check XOR: "); seeTheDifference(temp, checkingArray, aes_BLOCK_SIZE);
        #endif




        // Compute a single AES 
        aes(ciphertext + i*(aes_BLOCK_SIZE), inputMsg + i*(aes_BLOCK_SIZE), key);
        
        // Copy the ciphertext onto "temp", to calculate XOR for next iteration
        copyArrayFrom0(temp, ciphertext + i*(aes_BLOCK_SIZE), aes_BLOCK_SIZE);
    }
    
}   


void padding(uint8_t* inputToBePadded, uint8_t* inputLength){
    uint8_t pad = 0, i = 0;
    // See what needs to be padded
    pad = *inputLength;
    pad = 16 - (pad % 16);

    #ifdef step3
    printf(">> To be padded: %d\n", pad);
    #endif 
    
    if(pad != 0){
        for(i = *inputLength; i < pad + *inputLength; i++){
            inputToBePadded[i] = pad;
        }
    }
    
    // update message length    
    *inputLength += pad;
    
    //*inputLength = pad;
}




/*
void temp(uint16_t* variable){
    *variable = 12;
}
*/

