
#ifndef __TEST_H__
#define __TEST_H__

#ifdef __cplusplus
extern "C" {
#endif

#include<stdlib.h>
#include<stdio.h>
#include <sys/types.h>

#ifdef SHA2_USE_INTTYPES_H

printf("SHA2_USE_INTTYPES_H\n");

#include <inttypes.h>

#endif /* SHA2_USE_INTTYPES_H */






#if 0
typedef unsigned char u_int8_t;		/* 1-byte  (8-bits)  */
typedef unsigned int u_int32_t;		/* 4-bytes (32-bits) */
typedef unsigned long long u_int64_t;	/* 8-bytes (64-bits) */
#endif







#ifdef SHA2_USE_INTTYPES_H
printf("we're still using the SHA2_USE_INTTYPES_H\n");

#else /* SHA2_USE_INTTYPES_H */
printf(":O we're not using the SHA2_USE_INTTYPES_H\n");

#endif /* SHA2_USE_INTTYPES_H */

typedef SHA512_CTX SHA384_CTX;






/*** SHA-256/384/512 Function Prototypes ******************************/

//#ifndef NOPROTO

//#ifdef SHA2_USE_INTTYPES_H

//#else /* SHA2_USE_INTTYPES_H */

//#endif /* SHA2_USE_INTTYPES_H */

//#else /* NOPROTO */

//#endif /* NOPROTO */






#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif /* __TEST_H__ */

