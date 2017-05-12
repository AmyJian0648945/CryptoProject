/*
    This is a helpful wrapper function to for use of AES (in particular, in 
    CBC Mode). 
*/

#ifndef USEAES_H
#define USEAES_H

#include <stdint.h>
#include "helpfulFunctions.h"
#include "aes.h"



void aesDecrypt(uint8_t*, uint8_t*, uint8_t*);
    /* Performs a single AES decryption */
void aesEncrypt(uint8_t*, uint8_t*, uint8_t*);
    /* Performs a single AES Encryption */
void aesCBCdecrypt(uint8_t*, uint8_t*, uint16_t, uint8_t*, uint8_t*);
    /* Performs complete AES Decryption, CBC Mode */
void aesCBCencrypt(uint8_t*, uint8_t*, uint16_t*, uint8_t*, uint8_t*);
    /* Performs complete AES Encryption, CBC Mode */
void simpleDecrypt(uint8_t*, uint8_t*, uint16_t*, uint8_t*);
    /* Performs complete AES Decryption, CBC Mode */
void simpleEncrypt(uint8_t*, uint8_t*, uint16_t*, uint8_t*);
    /* Performs complete AES Encryption, CBC Mode */



void padding(uint8_t*, uint16_t*); 
    /* Pads data until a multipe of 16 */

#endif /* __USEAES_H__ */



