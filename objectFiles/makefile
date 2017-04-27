# How to use:
# --> To create all object files, write "make" into the compiler
# --> To remove all .o (object files) and .exe files, write "make remove"
# --> To execute the .exe file, write "./a.out" 
 

CC = gcc
CFLAGS = -Wall -pedantic -ansi

program:  main2.o aes.o useAES.o helpfulFunctions.o sha2.o useSHA256.o hmac.o PRNG.o encryptDecrypt.o additionalFunctions.o modFunctions.o modularInverse.o montExponentiation.o formatting.o maskGenerationFunction.o signatureMessage.o verifySignature.o keyEstablishmentFunctions.o
	$(CC) $(CFLAGS) -o program main2.o aes.o useAES.o helpfulFunctions.o sha2.o useSHA256.o hmac.o PRNG.o encryptDecrypt.o additionalFunctions.o modFunctions.o modularInverse.o montExponentiation.o formatting.o maskGenerationFunction.o signatureMessage.o verifySignature.o keyEstablishmentFunctions.o 

main2.o: ../main2.c 
	$(CC) $(CFLAGS) -c ../main2.c

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

additionalFunctions.o: ../Key_Establishment/Source/additionalFunctions.c ../Key_Establishment/Header/additionalFunctions.h
	$(CC) $(CFLAGS)	-c ../Key_Establishment/Source/additionalFunctions.c

modFunctions.o: ../Key_Establishment/Source/modFunctions.c ../Key_Establishment/Header/modFunctions.h
	$(CC) $(CFLAGS)	-c ../Key_Establishment/Source/modFunctions.c
	
modularInverse.o: ../Key_Establishment/Source/modularInverse.c ../Key_Establishment/Header/modularInverse.h
	$(CC) $(CFLAGS)	-c ../Key_Establishment/Source/modularInverse.c
	
montExponentiation.o: ../Key_Establishment/Source/montExponentiation.c ../Key_Establishment/Header/montExponentiation.h
	$(CC) $(CFLAGS)	-c ../Key_Establishment/Source/montExponentiation.c
	
formatting.o: ../Key_Establishment/Source/formatting.c ../Key_Establishment/Header/formatting.h
	$(CC) $(CFLAGS) -c ../Key_Establishment/Source/formatting.c

maskGenerationFunction.o: ../Key_Establishment/Source/maskGenerationFunction.c ../Key_Establishment/Header/maskGenerationFunction.h
	$(CC) $(CFLAGS) -c ../Key_Establishment/Source/maskGenerationFunction.c
	
signatureMessage.o: ../Key_Establishment/Source/signatureMessage.c ../Key_Establishment/Header/signatureMessage.h
	$(CC) $(CFLAGS) -c ../Key_Establishment/Source/signatureMessage.c
	
verifySignature.o: ../Key_Establishment/Source/verifySignature.c ../Key_Establishment/Header/verifySignature.h
	$(CC) $(CFLAGS) -c ../Key_Establishment/Source/verifySignature.c
	
keyEstablishmentFunctions.o: ../Key_Establishment/Source/keyEstablishmentFunctions.c ../Key_Establishment/Header/keyEstablishmentFunctions.h
	$(CC) $(CFLAGS)	-c ../Key_Establishment/Source/keyEstablishmentFunctions.c



