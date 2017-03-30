
#include "aes.h"





/* * * DEBUGGING STAAAAAATION! * * * * * * * * */ 
//#define step3 1
#define step4 1
//#define step4_insideLoop 1
/* * * Uncomment if you want to activate! * * */




void AES(uint8_t*, uint8_t*, uint8_t*);
void AES_CBC(uint8_t*, uint8_t*, uint8_t*, uint8_t*, uint8_t*);
void padding(uint8_t*, uint8_t*); 
    /* Pads data until a multipe of 16*/



void aes(uint8_t* output, uint8_t* plaintext, uint8_t* key){
    uint16_t i = 0;
    for (i=0; i<16; i++){
        output[i] = i;   
    }


    
}

void AES_CBC(uint8_t* ciphertext, uint8_t* inputMsg, uint8_t* msgLength, 
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
    
    #ifdef step4 /* Debugging statement*/
    printf("# of rounds = %d, msgLength = %d\n", CBCrounds, *msgLength);
    printf("IV: (should be the same as 'temp' below) "); printArray(IV, IVlength);
    printf("temp: (should be the same as 'IV' above) "); printArray(temp, IVlength);
    #endif

    // Go through all rounds AES, each with input 128bits of message
    for(i = 0; i < CBCrounds; i++){
        // XOR previous ciphertext with current plaintext (unless its the first iteration)
        XOR(temp, temp, inputMsg + i*(aes_BLOCK_SIZE), aes_BLOCK_SIZE);

        #ifdef step4_insideLoop
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

