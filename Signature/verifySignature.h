#ifndef VERIFYSIGNATURE_H
#define VERIFYSIGNATURE_H

#define EMLEN	256
#define HASHLEN	32
#define	SLEN	32
#define MASKLEN EMLEN-HASHLEN-1

#include <stdint.h>

#ifndef MASKGENERATIONFUNCTION_H
#define MASKGENERATIONFUNCTION_H
#include "maskGenerationFunction.h"
#endif

uint16_t verifySignature(uint8_t *message, uint8_t *encodedMessage);

#endif /* VERIFYSIGNATURE_H */
