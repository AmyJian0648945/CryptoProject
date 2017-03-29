#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "aes/useAES.h"
#include "sha2/useSHA256.h"
#include "dataTransmission/encrypt.h"



int main()
{
    








    
    return 0;
}

/* Operation:
-   Hash the key K with SHA-256 so as to get 256 bits of "key material". 
	Split that into two halves: 128 bits for encryption (Ke), 128 bits for MAC (Km).

-   Generate a random IV of 128 bits. 

-   Pad the data (usual PKCS#5 padding) so that its length is a multiple of the AES block size (16 bytes).

-   Encrypt the data with AES in CBC mode, using the IV generated just above, and Ke as key. Let's call C the resulting ciphertext.
Compute HMAC/SHA-256 with key Km over the concatenation of IV and C, in that order. Call M the resulting value. It is crucial that the IV is part of the input to HMAC.

-   Concatenate IV, C and M, in that order. This is your "registration key".

-   When receiving a registration request, first verify the HMAC (by recomputing it), then (and only then) proceed to the decryption step.

*/
