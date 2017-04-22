#ifndef MASKGENERATIONFUNCTION_H
#define MASKGENERATIONFUNCTION_H

#define EMLEN 256
#define HASHLEN 32
#define MASKLEN EMLEN-HASHLEN-1

#ifndef USESHA256_H
#include "../library/useSHA256.h"
#define USESHA256_H
#endif

uint16_t verifySignature(uint8_t*, uint8_t*);

#endif /* MASKGENERATIONFUNCTION_H */


