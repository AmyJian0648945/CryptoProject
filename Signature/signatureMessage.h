#ifndef SIGNATUREMESSAGE_H
#define SIGNATUREMESSAGE_H

#include "maskGenerationFunction.h"
#include "../library/PRNG.h"
#include "../library/useSHA256.h"

#define EMLEN	256
#define	HASHLEN	32
#define	SLEN	32
#define MASKLEN EMLEN-HASHLEN-1

uint16_t signatureMessage(uint8_t *message, uint8_t *encodedMessage);

#endif /* SIGNATUREMESSAGE_H */



