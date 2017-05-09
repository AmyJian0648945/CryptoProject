# How to use:
# --> To create all object files, write "make" into the compiler
# --> To remove all .o (object files) and .exe files, write "make remove"
# --> To execute the .exe file, write "./a.out" 
 

CC = gcc
CFLAGS = -Wall -pedantic -ansi

program1:  main.o aes.o useAES.o helpfulFunctions.o sha2.o useSHA256.o hmac.o PRNG.o encryptDecrypt.o additionalFunctions32.o modFunctions32.o modularInverse32.o montExponentiation32.o maskGenerationFunction.o signatureMessage.o verifySignature.o  keyEstablishmentFunctions32.o
	$(CC) $(CFLAGS) -o program main.o aes.o useAES.o helpfulFunctions.o sha2.o useSHA256.o hmac.o PRNG.o encryptDecrypt.o additionalFunctions32.o modFunctions32.o modularInverse32.o montExponentiation32.o maskGenerationFunction.o signatureMessage.o verifySignature.o keyEstablishmentFunctions32.o

main.o: ../ccsProject/main.c 
	$(CC) $(CFLAGS) -c ../ccsProject/main.c

aes.o: ../ccsProject/library/aes.c ../ccsProject/library/aes.h
	$(CC) $(CFLAGS) -c ../ccsProject/library/aes.c 

useAES.o: ../ccsProject/library/useAES.c ../ccsProject/library/useAES.h
	$(CC) $(CFLAGS) -c ../ccsProject/library/useAES.c  

helpfulFunctions.o: ../ccsProject/library/helpfulFunctions.c ../ccsProject/library/helpfulFunctions.h
	$(CC) $(CFLAGS) -c ../ccsProject/library/helpfulFunctions.c  

sha2.o: ../ccsProject/library/sha2.c ../ccsProject/library/sha2.h
	$(CC) $(CFLAGS) -c ../ccsProject/library/sha2.c  

useSHA256.o: ../ccsProject/library/useSHA256.c ../ccsProject/library/useSHA256.h
	$(CC) $(CFLAGS) -c ../ccsProject/library/useSHA256.c  

hmac.o: ../ccsProject/library/hmac.c ../ccsProject/library/hmac.h
	$(CC) $(CFLAGS) -c ../ccsProject/library/hmac.c  

PRNG.o: ../ccsProject/library/PRNG.c ../ccsProject/library/PRNG.h
	$(CC) $(CFLAGS) -c ../ccsProject/library/PRNG.c  

encryptDecrypt.o: ../ccsProject/library/encryptDecrypt.c ../ccsProject/library/encryptDecrypt.h
	$(CC) $(CFLAGS) -c ../ccsProject/library/encryptDecrypt.c

#additionalFunctions.o: ../ccsProject/Key_Establishment/Source/additionalFunctions.c ../ccsProject/Key_Establishment/Header/additionalFunctions.h
#	$(CC) $(CFLAGS)	-c ../ccsProject/Key_Establishment/Source/additionalFunctions.c

additionalFunctions32.o: ../ccsProject/Key_Establishment/Source/additionalFunctions32.c ../ccsProject/Key_Establishment/Header/additionalFunctions32.h
	$(CC) $(CFLAGS)	-c ../ccsProject/Key_Establishment/Source/additionalFunctions32.c

#modFunctions.o: ../ccsProject/Key_Establishment/Source/modFunctions.c ../ccsProject/Key_Establishment/Header/modFunctions.h
#	$(CC) $(CFLAGS)	-c ../ccsProject/Key_Establishment/Source/modFunctions.c
	
modFunctions32.o: ../ccsProject/Key_Establishment/Source/modFunctions32.c ../ccsProject/Key_Establishment/Header/modFunctions32.h
	$(CC) $(CFLAGS)	-c ../ccsProject/Key_Establishment/Source/modFunctions32.c

#modularInverse.o: ../ccsProject/Key_Establishment/Source/modularInverse.c ../ccsProject/Key_Establishment/Header/modularInverse.h
#	$(CC) $(CFLAGS)	-c ../ccsProject/Key_Establishment/Source/modularInverse.c
	
modularInverse32.o: ../ccsProject/Key_Establishment/Source/modularInverse32.c ../ccsProject/Key_Establishment/Header/modularInverse32.h
	$(CC) $(CFLAGS)	-c ../ccsProject/Key_Establishment/Source/modularInverse32.c

#montExponentiation.o: ../ccsProject/Key_Establishment/Source/montExponentiation.c ../ccsProject/Key_Establishment/Header/montExponentiation.h
#	$(CC) $(CFLAGS)	-c ../ccsProject/Key_Establishment/Source/montExponentiation.c

montExponentiation32.o: ../ccsProject/Key_Establishment/Source/montExponentiation32.c ../ccsProject/Key_Establishment/Header/montExponentiation32.h
	$(CC) $(CFLAGS)	-c ../ccsProject/Key_Establishment/Source/montExponentiation32.c
	
#keyEstablishmentFunctions.o: ../ccsProject/Key_Establishment/Source/keyEstablishmentFunctions.c ../ccsProject/Key_Establishment/Header/keyEstablishmentFunctions.h
#	$(CC) $(CFLAGS)	-c ../ccsProject/Key_Establishment/Source/keyEstablishmentFunctions.c

keyEstablishmentFunctions32.o: ../ccsProject/Key_Establishment/Source/keyEstablishmentFunctions32.c ../ccsProject/Key_Establishment/Header/keyEstablishmentFunctions32.h
	$(CC) $(CFLAGS)	-c ../ccsProject/Key_Establishment/Source/keyEstablishmentFunctions32.c

signatureMessage.o: ../ccsProject/Key_Establishment/Source/signatureMessage.c ../ccsProject/Key_Establishment/Header/signatureMessage.h
	$(CC) $(CFLAGS) -c ../ccsProject/Key_Establishment/Source/signatureMessage.c
	
verifySignature.o: ../ccsProject/Key_Establishment/Source/verifySignature.c ../ccsProject/Key_Establishment/Header/verifySignature.h
	$(CC) $(CFLAGS) -c ../ccsProject/Key_Establishment/Source/verifySignature.c
	
maskGenerationFunction.o: ../ccsProject/Key_Establishment/Source/maskGenerationFunction.c ../ccsProject/Key_Establishment/Header/maskGenerationFunction.h
	$(CC) $(CFLAGS) -c ../ccsProject/Key_Establishment/Source/maskGenerationFunction.c


clean:
	$(RM) program *.o


