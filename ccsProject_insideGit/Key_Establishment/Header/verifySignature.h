#ifndef VERIFYSIGNATURE_H
#define VERIFYSIGNATURE_H

#ifndef EMLEN
#define EMLEN	256
#endif

#ifndef HASHLEN
#define HASHLEN	32
#endif

#ifndef SLEN
#define	SLEN	32
#endif

#ifndef MASKLEN
#define MASKLEN EMLEN-HASHLEN-1
#endif

#include "maskGenerationFunction.h"
#include "../../library/useSHA256.h"

uint16_t verifySignature(uint8_t *message, uint8_t *encodedMessage);

#endif /* VERIFYSIGNATURE_H */


