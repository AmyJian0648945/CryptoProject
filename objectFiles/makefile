# How to use:
# --> To create all object files, write "make" into the compiler
# --> To remove all .o (object files) and .exe files, write "make remove"
# --> To execute the .exe file, write "./a.out" 
 

CC = gcc
CFLAGS = -Wall -pedantic -ansi

default: program

program:  main.o aes.o useAES.o helpfulFunctions.o sha2.o useSHA256.o hmac.o PRNG.o encryptDecrypt.o additionalFunctions.o modFunctions.o modularInverse.o montExponentiation.o formatting.o maskGenerationFunction.o signatureMessage.o verifySignature.o keyEstablishmentFunctions.o
	$(CC) $(CFLAGS) -o program main.o aes.o useAES.o helpfulFunctions.o sha2.o useSHA256.o hmac.o PRNG.o encryptDecrypt.o additionalFunctions.o modFunctions.o modularInverse.o montExponentiation.o formatting.o maskGenerationFunction.o signatureMessage.o verifySignature.o keyEstablishmentFunctions.o 

main.o: ../main.c 
	$(CC) $(CFLAGS) -c ../main.c

aes.o: ../library/aes.c ../library/aes.h
	$(CC) $(CFLAGS) -c ../library/aes.c 

useAES.o: ../library/useAES.c ../library/useAES.h
	$(CC) $(CFLAGS) -c ../library/useAES.c  

helpfulFunctions.o: ../library/helpfulFunctions.c ../library/helpfulFunctions.h
	$(CC) $(CFLAGS) -c ../library/helpfulFunctions.c  

sha2.o: ../library/sha2.c ../library/sha2.h
	$(CC) $(CFLAGS) -c ../library/sha2.c  

useSHA256.o: ../library/useSHA256.c ../library/useSHA256.h
	$(CC) $(CFLAGS) -c ../library/useSHA256.c  

hmac.o: ../library/hmac.c ../library/hmac.h
	$(CC) $(CFLAGS) -c ../library/hmac.c  

PRNG.o: ../library/PRNG.c ../library/PRNG.h
	$(CC) $(CFLAGS) -c ../library/PRNG.c  

encryptDecrypt.o: ../library/encryptDecrypt.c ../library/encryptDecrypt.h
	$(CC) $(CFLAGS) -c ../library/encryptDecrypt.c

additionalFunctions.o: ../Montgomery_Exponentiation/additionalFunctions.c ../Montgomery_Exponentiation/additionalFunctions.h
	$(CC) $(CFLAGS)	-c ../Montgomery_Exponentiation/additionalFunctions.c

modFunctions.o: ../Montgomery_Exponentiation/modFunctions.c ../Montgomery_Exponentiation/modFunctions.h
	$(CC) $(CFLAGS)	-c ../Montgomery_Exponentiation/modFunctions.c
	
modularInverse.o: ../Montgomery_Exponentiation/modularInverse.c ../Montgomery_Exponentiation/modularInverse.h
	$(CC) $(CFLAGS)	-c ../Montgomery_Exponentiation/modularInverse.c
	
montExponentiation.o: ../Montgomery_Exponentiation/montExponentiation.c ../Montgomery_Exponentiation/montExponentiation.h
	$(CC) $(CFLAGS)	-c ../Montgomery_Exponentiation/montExponentiation.c
	
formatting.o: ../Signature/formatting.c ../Signature/formatting.h
	$(CC) $(CFLAGS) -c ../Signature/formatting.c

maskGenerationFunction.o: ../Signature/maskGenerationFunction.c ../Signature/maskGenerationFunction.h
	$(CC) $(CFLAGS) -c ../Signature/maskGenerationFunction.c
	
signatureMessage.o: ../Signature/signatureMessage.c ../Signature/signatureMessage.h
	$(CC) $(CFLAGS) -c ../Signature/signatureMessage.c
	
verifySignature.o: ../Signature/verifySignature.c ../Signature/verifySignature.h
	$(CC) $(CFLAGS) -c ../Signature/verifySignature.c
	
keyEstablishmentFunctions.o: ../Signature/keyEstablishmentFunctions.c ../Signature/keyEstablishmentFunctions.h
	$(CC) $(CFLAGS)	-c ../Signature/keyEstablishmentFunctions.c

	
	
clean:
	$(RM) program *.o

