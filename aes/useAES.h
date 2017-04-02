
#include "aes.h"
#include "aes.c"

#define AES_KEY_SIZE 128




void aesDecrypt(uint8_t*, uint8_t*, uint8_t*);
void aesEncrypt(uint8_t*, uint8_t*, uint8_t*);
void aesCBCdecrypt(uint8_t*, uint8_t*, uint8_t*, uint8_t*, uint8_t*);
void aesCBCencrypt(uint8_t*, uint8_t*, uint8_t*, uint8_t*, uint8_t*);
void padding(uint8_t*, uint8_t*); 
    /* Pads data until a multipe of 16*/

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

void aesCBCdecrypt(uint8_t* plaintext, uint8_t* ciphertext, uint8_t* msgLength, 
             uint8_t* IV, uint8_t* key){
    uint8_t temp[aes_BLOCK_SIZE] = {0};
    uint8_t CBCrounds = 0;
    uint16_t i = 0;

    /* Figuring out how many AES_CBC rounds is needed */
    CBCrounds = msgLength;
    CBCrounds = CBCrounds / aes_BLOCK_SIZE;

    copyArrayFrom0(temp, IV, IVlength);

    for(i = 0; i < CBCrounds; i++){
        /* Compute a single AES */
        aesDecrypt(plaintext + i*(aes_BLOCK_SIZE), ciphertext + i*(aes_BLOCK_SIZE), key);

        /* XOR previous ciphertext with current plaintext (unless its the first iteration)  */
        XOR(plaintext + i*(aes_BLOCK_SIZE), temp, plaintext + i*(aes_BLOCK_SIZE), aes_BLOCK_SIZE);

        /* Copy the ciphertext onto "temp", to calculate XOR for next iteration */
        copyArrayFrom0(temp, ciphertext + i*(aes_BLOCK_SIZE), aes_BLOCK_SIZE);   
    }

}

void aesCBCencrypt(uint8_t* ciphertext, uint8_t* inputMsg, uint8_t* msgLength, 
             uint8_t* IV, uint8_t* key)
{
    uint8_t temp[aes_BLOCK_SIZE] = {0};
    uint8_t tempXOR[aes_BLOCK_SIZE] = {0};
    uint8_t CBCrounds = 0;
    uint16_t i = 0;

    /* Figuring out how many AES_CBC rounds is needed */
    CBCrounds = *msgLength;
    CBCrounds = CBCrounds / aes_BLOCK_SIZE;

    /* Copy IV into temp, in order to initialise the first plaintext */
    copyArrayFrom0(temp, IV, IVlength);

    /* Go through all rounds AES, each with input 128bits of message */
    for(i = 0; i < CBCrounds; i++){
        /* XOR previous ciphertext with current plaintext (unless its the first iteration)  */
        XOR(tempXOR, temp, inputMsg + i*(aes_BLOCK_SIZE), aes_BLOCK_SIZE);

        /* Compute a single AES */
        aesEncrypt(ciphertext + i*(aes_BLOCK_SIZE), tempXOR, key);

        /* Copy the ciphertext onto "temp", to calculate XOR for next iteration */
        copyArrayFrom0(temp, ciphertext + i*(aes_BLOCK_SIZE), aes_BLOCK_SIZE);   
    }
}   


void padding(uint8_t* inputToBePadded, uint8_t* inputLength){
    uint8_t pad = 0, i = 0;

    /* figure out how much to pad */
    pad = *inputLength;
    pad = 16 - (pad % 16);

    /* pad as many times as needed */
    for(i = *inputLength; i < pad + *inputLength; i++) inputToBePadded[i] = pad;

    /* update message length */
    *inputLength += pad;
}

