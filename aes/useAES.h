
#include "aes.h"





/* * * DEBUGGING STAAAAAATION! * * * * * * * * */ 
//#define step3 1
/* * * Uncomment if you want to activate! * * */




void AES(uint8_t*, uint8_t*, uint8_t*);
void AES_CBC(uint8_t*, uint8_t*, uint16_t, uint8_t*, uint8_t*);
void padding(uint8_t*, uint8_t*); 
    /* Pads data until a multipe of 16*/



void aes(uint8_t* output, uint8_t* plaintext, uint8_t* key){
    output[0] = 0x0f;
}

void AES_CBC(uint8_t* ciphertext, uint8_t* inputMsg, uint16_t msgLength, 
             uint8_t* IV, uint8_t* key)
{
    uint16_t CBCrounds = 0, i = 0;
    CBCrounds = msgLength / aes_BLOCK_SIZE;


    for(i = 0; i < CBCrounds; i++){
        aes(ciphertext + i*(aes_BLOCK_SIZE), inputMsg, key);
    }


}


void padding(uint8_t* inputToBePadded, uint8_t* inputLength){
    uint8_t pad = 0, i = 0;

    // See what needs to be padded
    pad = inputLength;
    pad = 16 - (pad % 16);

    #ifdef step3
    printf(">> To be padded: %d\n", pad % 16);
    #endif 

    inputLength++;
    printf("sum = %d + %d ",pad, inputLength);

    pad += inputLength;
    //inputLength += 1;
    printf("= %d \n",pad);
    /*
    if(pad != 0){
        for(i = inputLength; i < pad+inputLength; i++){
            inputToBePadded[i] = pad;
            printf("i=%d, inputLength=%d, pad=%d\n", i, pad, pad+inputLength);
        }
    }
    */
    // update message length    
    inputLength += pad;
}




/*
void temp(uint16_t* variable){
    *variable = 12;
}
*/

