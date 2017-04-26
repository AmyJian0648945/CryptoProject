#include <stdlib.h>
#include <stdio.h>
#include "sha.h"

void hexDump(uint8_t* text,uint8_t *data, int nofDataBytes){
  int i;
  for (i=0;i<nofDataBytes;i++)
    printf("%02X",data[i]);
  printf("\t<%s>",text);
}

int main (void) {

  uint8_t emptyString[]="";
  uint8_t singleA[]="a";
  uint8_t abc[]="abc";
  uint8_t alphabet[]="abcdefghijklmnopqrstuvwxyz";

  uint8_t reference1[]="DA39A3EE5E6B4B0D3255BFEF95601890AFD80709";
  uint8_t reference2[]="86F7E437FAA5A7FCE15D1DDCB9EAEAEA377667B8";
  uint8_t reference3[]="A9993E364706816ABA3E25717850C26C9CD0D89D";
  uint8_t reference4[]="32D10C7B8CF96570CA04CE37F2A19D84240D3A89";

  uint8_t hashResult[20];

  printf("testing SHA1-test vectors\n");

  sha1(hashResult,emptyString,0);
  hexDump(emptyString, hashResult, 20);
  printf("\n");
  printf("%s\treference\n",reference1);
  
  sha1(hashResult,singleA,1);
  hexDump(singleA, hashResult, 20);
  printf("\n");
  printf("%s\treference\n",reference2);

  sha1(hashResult,abc,3);
  hexDump(abc, hashResult, 20);
  printf("\n");
  printf("%s\treference\n",reference3);

  sha1(hashResult,alphabet,26);
  hexDump(alphabet, hashResult, 20);
  printf("\n");
  printf("%s\treference\n",reference4);

  return 0;
}
