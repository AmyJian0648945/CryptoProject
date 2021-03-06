#include "process_audio.h"

/* Include your header files here */
#include<string.h>
#include<stdio.h>
#include<stdlib.h>

#include "globals.h"
#include "encode.h"
#include "decode.h"




/* Declare your variables globally here */

short buffer[BUFFERSIZE];
short encoded[BUFFERSIZE];
short reconstructedBuffer[BUFFERSIZE];

/*
struct chunkEncoder encoderChunkLeft;
struct chunkEncoder encoderChunkRight;
struct chunkDecoder decoderChunkLeft;
struct chunkDecoder decoderChunkRight;
*/


void init_audio(){

    /* Include all your initialization code. This function is called once only */

	printf("\n Init done");
}


// Multi-iteration version

void process_audio(int* input_buf, int* output_buf, int nbytes)
{
   int i=0, iter=0;
   short *pshort;
   int nr_elements = BUFFERSIZE;
   short input_rot[BUFLEN*2], output_rot[BUFLEN*2];	/* Factor of 2 is because of sizeof(int)/sizeof(short) = 2*/
   int niters = (BUFLEN*2)/BUFFERSIZE;
   int stepsize = BUFFERSIZE/2;

   /* Dummy copy code below. Insert your encode, encrypt, decrypt, decode functions below and comment out the copy loop */
    for (i = 0; i < nbytes/4; i++) { // no._int is 1/4 of nbytes
        output_buf[i] = input_buf[i];
    }


    printf(" Hello! \n ");

    //printf("nr_elements = %d\n", nr_elements);
    //printf("nbytes      = %d\n", nbytes);
    //printf("BUFLEN      = %d\n", BUFLEN);



    /*
    for (iter=0; iter<niters; iter++){
    	// Extract upper and lower 16 bits from input_buf[i]
    	pshort = (short*)(&input_buf[iter*stepsize]);
    	for (i = 0; i < nr_elements; i++) {
    	    input_rot[(iter*BUFFERSIZE)+i] = pshort[i];
    	}
    	encode(&input_rot[iter*BUFFERSIZE], &encoderChunkLeft, &encoderChunkRight, encoded);
    }

    // call encrypt and decrypt function

    for (iter=0; iter<niters; iter++){
    	decode(encoded, &decoderChunkLeft, &decoderChunkRight, &output_rot[iter*BUFFERSIZE]);
    	pshort = (short*)(&output_buf[iter*stepsize]);
    	for (i = 0; i < nr_elements; i++) {
    		pshort[i] = output_rot[(iter*BUFFERSIZE)+i];
    	}
    }
    */

}






