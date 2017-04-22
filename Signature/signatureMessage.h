#ifndef SIGNATUREMESSAGE_H
#define SIGNATUREMESSAGE_H

#ifndef MASKGENERATIONFUNCTION_H
#define MASKGENERATIONFUNCTION_H
#include "maskGenerationFunction.h"
#endif

#ifndef PRNG_H
#include "../library/PRNG.h"
#endif

#define EMLEN	256
#define	HASHLEN	32
#define	SLEN	32
#define MASKLEN EMLEN-HASHLEN-1

#include <stdint.h>

uint16_t signatureMessage(uint8_t *message, uint8_t *encodedMessage);

#endif /* SIGNATUREMESSAGE_H */



