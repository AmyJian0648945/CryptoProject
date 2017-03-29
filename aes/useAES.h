
#include "aes.h"


/* * * DEBUGGING STAAAAAATION! * * * * * * * * */ 
#define step3 1
/* * * Uncomment if you want to activate! * * */





void AES_CBC();
void padding(uint8_t*, uint16_t*); 
    /* Pads data until a multipe of 16*/



void padding(uint8_t* inputToBePadded, uint16_t* inputLength){
    uint8_t pad = 0, i = 0;

    // See what needs to be padded
    pad = inputLength;
    
    if(pad < 16) pad = 16 - pad;
    else pad = pad % 16;
    


    #ifdef step3
        printf(">> To be padded: %d\n", pad % 16);
    #endif
    
    pad =0;

    if(pad != 0){
        for(i = inputLength; i < pad+inputLength; i++){
            inputToBePadded[i] = pad;
        }
    }
    
    // update message length    
    inputLength += pad;
}




/*
void temp(uint16_t* variable){
    *variable = 12;
}
*/

