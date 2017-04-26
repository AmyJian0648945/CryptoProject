#ifndef SIGNATUREMESSAGE_H
#define SIGNATUREMESSAGE_H

#include "maskGenerationFunction.h"
#include "../../library/PRNG.h"
#include "../../library/useSHA256.h"

#ifndef EMLEN
#define EMLEN	256
#endif

#ifndef HASHLEN
#define	HASHLEN	32
#endif

#ifndef SLEN
#define	SLEN	32
#endif

#ifndef MASKLEN
#define MASKLEN EMLEN-HASHLEN-1
#endif

void signatureMessage(uint8_t *message, uint8_t *encodedMessage);

#endif /* SIGNATUREMESSAGE_H */


