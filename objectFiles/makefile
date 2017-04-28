# How to use:
# --> To create all object files, write "make" into the compiler
# --> To remove all .o (object files) and .exe files, write "make remove"
# --> To execute the .exe file, write "./a.out" 
 

CC = gcc
CFLAGS = -Wall -pedantic -ansi

program:  main.o aes.o useAES.o helpfulFunctions.o sha2.o useSHA256.o hmac.o PRNG.o encryptDecrypt.o additionalFunctions.o modFunctions.o modularInverse.o montExponentiation.o formatting.o maskGenerationFunction.o signatureMessage.o verifySignature.o keyEstablishmentFunctions.o
	$(CC) $(CFLAGS) -o program main.o aes.o useAES.o helpfulFunctions.o sha2.o useSHA256.o hmac.o PRNG.o encryptDecrypt.o additionalFunctions.o modFunctions.o modularInverse.o montExponentiation.o formatting.o maskGenerationFunction.o signatureMessage.o verifySignature.o keyEstablishmentFunctions.o 

main.o: ../ccsProject_inside/main.c 
	$(CC) $(CFLAGS) -c ../ccsProject_inside/main.c

aes.o: ../ccsProject_insideGit/library/aes.c ../ccsProject_insideGit/library/aes.h
	$(CC) $(CFLAGS) -c ../ccsProject_insideGit/library/aes.c 

useAES.o: ../ccsProject_insideGit/library/useAES.c ../ccsProject_insideGit/library/useAES.h
	$(CC) $(CFLAGS) -c ../ccsProject_insideGit/library/useAES.c  

helpfulFunctions.o: ../ccsProject_insideGit/library/helpfulFunctions.c ../ccsProject_insideGit/library/helpfulFunctions.h
	$(CC) $(CFLAGS) -c ../ccsProject_insideGit/library/helpfulFunctions.c  

sha2.o: ../ccsProject_insideGit/library/sha2.c ../ccsProject_insideGit/library/sha2.h
	$(CC) $(CFLAGS) -c ../ccsProject_insideGit/library/sha2.c  

useSHA256.o: ../ccsProject_insideGit/library/useSHA256.c ../ccsProject_insideGit/library/useSHA256.h
	$(CC) $(CFLAGS) -c ../ccsProject_insideGit/library/useSHA256.c  

hmac.o: ../ccsProject_insideGit/library/hmac.c ../ccsProject_insideGit/library/hmac.h
	$(CC) $(CFLAGS) -c ../ccsProject_insideGit/library/hmac.c  

PRNG.o: ../ccsProject_insideGit/library/PRNG.c ../ccsProject_insideGit/library/PRNG.h
	$(CC) $(CFLAGS) -c ../ccsProject_insideGit/library/PRNG.c  

encryptDecrypt.o: ../ccsProject_insideGit/library/encryptDecrypt.c ../ccsProject_insideGit/library/encryptDecrypt.h
	$(CC) $(CFLAGS) -c ../ccsProject_insideGit/library/encryptDecrypt.c

additionalFunctions.o: ../ccsProject_insideGit/Key_Establishment/Source/additionalFunctions.c ../ccsProject_insideGit/Key_Establishment/Header/additionalFunctions.h
	$(CC) $(CFLAGS)	-c ../ccsProject_insideGit/Key_Establishment/Source/additionalFunctions.c

modFunctions.o: ../ccsProject_insideGit/Key_Establishment/Source/modFunctions.c ../ccsProject_insideGit/Key_Establishment/Header/modFunctions.h
	$(CC) $(CFLAGS)	-c ../ccsProject_insideGit/Key_Establishment/Source/modFunctions.c
	
modularInverse.o: ../ccsProject_insideGit/Key_Establishment/Source/modularInverse.c ../ccsProject_insideGit/Key_Establishment/Header/modularInverse.h
	$(CC) $(CFLAGS)	-c ../Montgomery_Exponentiation/Source/modularInverse.c
	
montExponentiation.o: ../ccsProject_insideGit/Key_Establishment/Source/montExponentiation.c ../ccsProject_insideGit/Key_Establishment/Header/montExponentiation.h
	$(CC) $(CFLAGS)	-c ../ccsProject_insideGit/Key_Establishment/Source/montExponentiation.c
	
formatting.o: ../ccsProject_insideGit/Key_Establishment/Source/formatting.c ../ccsProject_insideGit/Key_Establishment/Header/formatting.h
	$(CC) $(CFLAGS) -c ../ccsProject_insideGit/Key_Establishment/Source/formatting.c

maskGenerationFunction.o: ../ccsProject_insideGit/Key_Establishment/Source/maskGenerationFunction.c ../ccsProject_insideGit/Key_Establishment/Header/maskGenerationFunction.h
	$(CC) $(CFLAGS) -c ../ccsProject_insideGit/Key_Establishment/Source/maskGenerationFunction.c
	
signatureMessage.o: ../ccsProject_insideGit/Key_Establishment/Source/signatureMessage.c ../ccsProject_insideGit/Key_Establishment/Header/signatureMessage.h
	$(CC) $(CFLAGS) -c ../ccsProject_insideGit/Key_Establishment/Source/signatureMessage.c
	
verifySignature.o: ../ccsProject_insideGit/Key_Establishment/Source/verifySignature.c ../ccsProject_insideGit/Key_Establishment/Header/verifySignature.h
	$(CC) $(CFLAGS) -c ../Signature/Source/verifySignature.c
	
keyEstablishmentFunctions.o: ../ccsProject_insideGit/Key_Establishment/Source/keyEstablishmentFunctions.c ../ccsProject_insideGit/Key_Establishment/Header/keyEstablishmentFunctions.h
	$(CC) $(CFLAGS)	-c ../ccsProject_insideGit/Key_Establishment/Source/keyEstablishmentFunctions.c



