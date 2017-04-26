#ifndef MASKGENERATIONFUNCTION_H
#define MASKGENERATIONFUNCTION_H

#ifndef EMLEN
#define EMLEN 256
#endif

#ifndef HASHLEN
#define HASHLEN 32
#endif

#ifndef MASKLEN
#define MASKLEN EMLEN-HASHLEN-1
#endif

#include "../../library/useSHA256.h"

void maskGenerationFunction(uint8_t *input, uint8_t *dbmask);

#endif /* MASKGENERATIONFUNCTION_H */


