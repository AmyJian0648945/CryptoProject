
#include "useAES.h"






void aesDecrypt(uint8_t* plaintext, uint8_t* ciphertext, uint8_t* key){
    aes_key aeskey;
 
    aes_set_decrypt_key(&aeskey, key, 128);
    aes_decrypt(&aeskey, ciphertext, plaintext);
}

void aesEncrypt(uint8_t* ciphertext, uint8_t* plaintext, uint8_t* key){
    aes_key aeskey;

    aes_set_encrypt_key(&aeskey, key, 128);
    aes_encrypt(&aeskey, plaintext, ciphertext);    
}


void simpleDecrypt(uint8_t* plaintext, uint8_t* ciphertext, uint16_t* msgLength, 
             uint8_t* key){
    uint8_t CBCrounds = 0;
    uint16_t i = 0;

    /* Figuring out how many AES_CBC rounds are needed */
    
    CBCrounds = msgLength[0] / aes_BLOCK_SIZE;

    for(i = 0; i < CBCrounds; i++){
        /* Compute a single AES */
        aesDecrypt(plaintext + i*(aes_BLOCK_SIZE), ciphertext + i*(aes_BLOCK_SIZE), key); 
    }
}

void simpleEncrypt(uint8_t* ciphertext, uint8_t* inputMsg, uint16_t* msgLength, 
            uint8_t* key){
    
    uint16_t CBCrounds = 0;
    uint16_t i = 0;

    /* Figuring out how many AES_CBC rounds is needed */
    CBCrounds = msgLength[0] / aes_BLOCK_SIZE;

    /* Go through all rounds AES, each with input 128bits of message */
    for(i = 0; i < CBCrounds; i++){
        /* Compute a single AES */
        aesEncrypt(ciphertext + i*(aes_BLOCK_SIZE), inputMsg + i*(aes_BLOCK_SIZE), key);
    }
}

void aesCBCdecrypt(uint8_t* plaintext, uint8_t* ciphertext, uint16_t msgLength, 
             uint8_t* IV, uint8_t* key){
    uint8_t temp[aes_BLOCK_SIZE] = {0};
    uint16_t CBCrounds = 0;
    uint16_t i = 0;

    /* Figuring out how many AES_CBC rounds is needed */
    
    CBCrounds = msgLength / aes_BLOCK_SIZE;

    copyArrayFrom0(temp, IV, AES_IVlength);

    for(i = 0; i < CBCrounds; i++){
        /* Compute a single AES */
        aesDecrypt(plaintext + i*(aes_BLOCK_SIZE), ciphertext + i*(aes_BLOCK_SIZE), key);

        /* XOR previous ciphertext with current plaintext (unless its the first iteration)  */
        XOR(plaintext + i*(aes_BLOCK_SIZE), temp, plaintext + i*(aes_BLOCK_SIZE), aes_BLOCK_SIZE);

        /* Copy the ciphertext onto "temp", to calculate XOR for next iteration */
        copyArrayFrom0(temp, ciphertext + i*(aes_BLOCK_SIZE), aes_BLOCK_SIZE);   
    }

}




void aesCBCencrypt(uint8_t* ciphertext, uint8_t* inputMsg, uint16_t* msgLength, 
             uint8_t* IV, uint8_t* key)
{
    uint8_t temp[aes_BLOCK_SIZE] = {0};
    uint8_t tempXOR[aes_BLOCK_SIZE] = {0};
    uint16_t CBCrounds = 0;
    uint16_t i = 0;

    /* Figuring out how many AES_CBC rounds is needed */
    
    CBCrounds = msgLength[0] / aes_BLOCK_SIZE;

    /* Copy IV into temp, in order to initialise the first plaintext */
    copyArrayFrom0(temp, IV, AES_IVlength);

    /* Go through all rounds AES, each with input 128bits of message */
    for(i = 0; i < CBCrounds; i++){
        /* XOR previous ciphertext with current plaintext (unless its the first iteration)  */
        XOR(tempXOR, temp, inputMsg+ i*(aes_BLOCK_SIZE), aes_BLOCK_SIZE);

        /* Compute a single AES */
        aesEncrypt(ciphertext + i*(aes_BLOCK_SIZE), tempXOR, key);

        /* Copy the ciphertext onto "temp", to calculate XOR for next iteration */
        copyArrayFrom0(temp, ciphertext + i*(aes_BLOCK_SIZE), aes_BLOCK_SIZE);   
    }
}   


void padding(uint8_t* inputToBePadded, uint16_t* inputLength){
    uint16_t pad = 0, i = 0;

    /* figure out how much to pad */
    pad = inputLength[0] % 16;

    if(pad != 0){
    	pad = 16 - pad;
    	/* pad as many times as needed */
    	for(i = inputLength[0]; i < pad + inputLength[0]; i++) inputToBePadded[i] = pad;

    	/* update message length */
    	inputLength[0] += pad;
    }
}
