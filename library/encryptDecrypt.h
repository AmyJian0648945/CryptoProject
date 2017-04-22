/* * * * * * * * * * * * * * * * * * * * * * * *
This file encrypts the message, and outputs the ciphertext and corresponding 
information (HMAC and IV) to allow for decryption. 

--> Protocol Specifications:
	Encryption method: AES-128, CBC Mode
	Message authentication: HMAC-SHA256
	Encryption and MAC assembly: Encrypt-then-MAC
	Padding: PKCS#7
--> Note: 
	{IV || C || HMAC(IV || C) } = regist key 


*** For more info about Encrypt-then-Mac, see https://goo.gl/8wAanl
*** For more info about PKCS#7, see https://tools.ietf.org/html/rfc5652#section-6.3
* * * * * * * * * * * * * * * * * * * * * * * * */
#ifndef ENCRYPT_H
#define ENCRYPT_H

#define encryptKeyLength    16
#define macKeyLength        16
#define IVlength            16

#include <stdint.h>
#include "useSHA256.h"
#include "useAES.h"
#include "PRNG.h"
#include "hmac.h"
#include "helpfulFunctions.h"




/* Function Introduction */
void encrypt(uint8_t*, uint8_t*, uint8_t*, uint8_t*, uint16_t);
void decrypt(uint8_t*, uint8_t*, uint8_t*, uint8_t*, uint16_t);

#endif	
