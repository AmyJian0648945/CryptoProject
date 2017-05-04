# How to use:
# --> To create all object files, write "make" into the compiler
# --> To remove all .o (object files) and .exe files, write "make remove"
# --> To execute the .exe file, write "./a.out" 
 

CC = gcc
CFLAGS = -Wall -pedantic -O2 -std=c99

program:  main.o aes.o useAES.o helpfulFunctions.o sha2.o useSHA256.o hmac.o PRNG.o encryptDecrypt.o additionalFunctions32.o modFunctions32.o modularInverse32.o montExponentiation32.o maskGenerationFunction.o signatureMessage.o verifySignature.o  keyEstablishmentFunctions32.o
	$(CC) $(CFLAGS) -o program main.o aes.o useAES.o helpfulFunctions.o sha2.o useSHA256.o hmac.o PRNG.o encryptDecrypt.o additionalFunctions32.o modFunctions32.o modularInverse32.o montExponentiation32.o maskGenerationFunction.o signatureMessage.o verifySignature.o keyEstablishmentFunctions32.o

main.o: ../crypto_dspSimulation/main.c 
	$(CC) $(CFLAGS) -c ../crypto_dspSimulation/main.c

aes.o: ../crypto_dspSimulation/library/aes.c ../crypto_dspSimulation/library/aes.h
	$(CC) $(CFLAGS) -c ../crypto_dspSimulation/library/aes.c 

useAES.o: ../crypto_dspSimulation/library/useAES.c ../crypto_dspSimulation/library/useAES.h
	$(CC) $(CFLAGS) -c ../crypto_dspSimulation/library/useAES.c  

helpfulFunctions.o: ../crypto_dspSimulation/library/helpfulFunctions.c ../crypto_dspSimulation/library/helpfulFunctions.h
	$(CC) $(CFLAGS) -c ../crypto_dspSimulation/library/helpfulFunctions.c  

sha2.o: ../crypto_dspSimulation/library/sha2.c ../crypto_dspSimulation/library/sha2.h
	$(CC) $(CFLAGS) -c ../crypto_dspSimulation/library/sha2.c  

useSHA256.o: ../crypto_dspSimulation/library/useSHA256.c ../crypto_dspSimulation/library/useSHA256.h
	$(CC) $(CFLAGS) -c ../crypto_dspSimulation/library/useSHA256.c  

hmac.o: ../crypto_dspSimulation/library/hmac.c ../crypto_dspSimulation/library/hmac.h
	$(CC) $(CFLAGS) -c ../crypto_dspSimulation/library/hmac.c  

PRNG.o: ../crypto_dspSimulation/library/PRNG.c ../crypto_dspSimulation/library/PRNG.h
	$(CC) $(CFLAGS) -c ../crypto_dspSimulation/library/PRNG.c  

encryptDecrypt.o: ../crypto_dspSimulation/library/encryptDecrypt.c ../crypto_dspSimulation/library/encryptDecrypt.h
	$(CC) $(CFLAGS) -c ../crypto_dspSimulation/library/encryptDecrypt.c

#additionalFunctions.o: ../crypto_dspSimulation/Key_Establishment/Source/additionalFunctions.c ../crypto_dspSimulation/Key_Establishment/Header/additionalFunctions.h
#	$(CC) $(CFLAGS)	-c ../crypto_dspSimulation/Key_Establishment/Source/additionalFunctions.c

additionalFunctions32.o: ../crypto_dspSimulation/Key_Establishment/Source/additionalFunctions32.c ../crypto_dspSimulation/Key_Establishment/Header/additionalFunctions32.h
	$(CC) $(CFLAGS)	-c ../crypto_dspSimulation/Key_Establishment/Source/additionalFunctions32.c

#modFunctions.o: ../crypto_dspSimulation/Key_Establishment/Source/modFunctions.c ../crypto_dspSimulation/Key_Establishment/Header/modFunctions.h
#	$(CC) $(CFLAGS)	-c ../crypto_dspSimulation/Key_Establishment/Source/modFunctions.c
	
modFunctions32.o: ../crypto_dspSimulation/Key_Establishment/Source/modFunctions32.c ../crypto_dspSimulation/Key_Establishment/Header/modFunctions32.h
	$(CC) $(CFLAGS)	-c ../crypto_dspSimulation/Key_Establishment/Source/modFunctions32.c

#modularInverse.o: ../crypto_dspSimulation/Key_Establishment/Source/modularInverse.c ../crypto_dspSimulation/Key_Establishment/Header/modularInverse.h
#	$(CC) $(CFLAGS)	-c ../crypto_dspSimulation/Key_Establishment/Source/modularInverse.c
	
modularInverse32.o: ../crypto_dspSimulation/Key_Establishment/Source/modularInverse32.c ../crypto_dspSimulation/Key_Establishment/Header/modularInverse32.h
	$(CC) $(CFLAGS)	-c ../crypto_dspSimulation/Key_Establishment/Source/modularInverse32.c

#montExponentiation.o: ../crypto_dspSimulation/Key_Establishment/Source/montExponentiation.c ../crypto_dspSimulation/Key_Establishment/Header/montExponentiation.h
#	$(CC) $(CFLAGS)	-c ../crypto_dspSimulation/Key_Establishment/Source/montExponentiation.c

montExponentiation32.o: ../crypto_dspSimulation/Key_Establishment/Source/montExponentiation32.c ../crypto_dspSimulation/Key_Establishment/Header/montExponentiation32.h
	$(CC) $(CFLAGS)	-c ../crypto_dspSimulation/Key_Establishment/Source/montExponentiation32.c
	
#keyEstablishmentFunctions.o: ../crypto_dspSimulation/Key_Establishment/Source/keyEstablishmentFunctions.c ../crypto_dspSimulation/Key_Establishment/Header/keyEstablishmentFunctions.h
#	$(CC) $(CFLAGS)	-c ../crypto_dspSimulation/Key_Establishment/Source/keyEstablishmentFunctions.c

keyEstablishmentFunctions32.o: ../crypto_dspSimulation/Key_Establishment/Source/keyEstablishmentFunctions32.c ../crypto_dspSimulation/Key_Establishment/Header/keyEstablishmentFunctions32.h
	$(CC) $(CFLAGS)	-c ../crypto_dspSimulation/Key_Establishment/Source/keyEstablishmentFunctions32.c

signatureMessage.o: ../crypto_dspSimulation/Key_Establishment/Source/signatureMessage.c ../crypto_dspSimulation/Key_Establishment/Header/signatureMessage.h
	$(CC) $(CFLAGS) -c ../crypto_dspSimulation/Key_Establishment/Source/signatureMessage.c
	
verifySignature.o: ../crypto_dspSimulation/Key_Establishment/Source/verifySignature.c ../crypto_dspSimulation/Key_Establishment/Header/verifySignature.h
	$(CC) $(CFLAGS) -c ../crypto_dspSimulation/Key_Establishment/Source/verifySignature.c
	
maskGenerationFunction.o: ../crypto_dspSimulation/Key_Establishment/Source/maskGenerationFunction.c ../crypto_dspSimulation/Key_Establishment/Header/maskGenerationFunction.h
	$(CC) $(CFLAGS) -c ../crypto_dspSimulation/Key_Establishment/Source/maskGenerationFunction.c


clean:
	$(RM) program *.o


