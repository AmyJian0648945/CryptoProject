
#include "aes.h"





/* * * DEBUGGING STAAAAAATION! * * * * * * * * */ 
//#define step3 1
#define step4 1
/* * * Uncomment if you want to activate! * * */




void AES(uint8_t*, uint8_t*, uint8_t*);
void AES_CBC(uint8_t*, uint8_t*, uint8_t*, uint8_t*, uint8_t*);
void padding(uint8_t*, uint8_t*); 
    /* Pads data until a multipe of 16*/



void aes(uint8_t* output, uint8_t* plaintext, uint8_t* key){
    output[0] = 0x11;
}

void AES_CBC(uint8_t* ciphertext, uint8_t* inputMsg, uint8_t* msgLength, 
             uint8_t* IV, uint8_t* key)
{
    uint8_t CBCrounds = 0;
    uint16_t i = 0;
    CBCrounds = *msgLength;
    CBCrounds = CBCrounds / aes_BLOCK_SIZE;

    #ifdef step4
    printf("# of rounds = %d, msgLength = %d\n", CBCrounds, *msgLength);
    #endif

    aes(ciphertext, inputMsg, key);
    aes(ciphertext+10, inputMsg, key);
    aes(ciphertext+aes_BLOCK_SIZE, inputMsg, key);
/*
    for(i = 0; i < CBCrounds; i++){
        aes(ciphertext + i*(aes_BLOCK_SIZE), inputMsg, key);
    }
*/

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

