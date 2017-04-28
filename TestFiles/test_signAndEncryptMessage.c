#include<stdint.h>
#include<string.h>
#include<stdio.h>

#ifndef baseLength
#define baseLength 30
#endif

#ifndef modLength
#define modLength 32
#endif

#ifndef expLengthMAX
#define expLengthMAX 32
#endif

#define sizeMessageAB 128
#define sizeModulusAB 64
#define sizePrExpAB 64
#define sizePuExpAB 2

/*#define PRINT*/

#include "library/helpfulFunctions.h"
#include "library/sha2.h"
#include "library/useSHA256.h"
#include "library/aes.h"
#include "library/useAES.h"
#include "library/hmac.h"
#include "library/PRNG.h"
#include "library/encryptDecrypt.h"
#include "Key_Establishment/Header/additionalFunctions.h"
#include "Key_Establishment/Header/montExponentiation.h"
#include "Key_Establishment/Header/signatureMessage.h"
#include "Key_Establishment/Header/verifySignature.h"
#include "Key_Establishment/Header/keyEstablishmentFunctions.h"