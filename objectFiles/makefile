# How to use:
# --> To create all object files, write "make" into the compiler
# --> To remove all .o (object files) and .exe files, write "make remove"
# --> To execute the .exe file, write "./a.out" 
 

CC = gcc
CFLAGS = -Wall -pedantic -ansi

program:  main.o aes.o useAES.o helpfulFunctions.o sha2.o useSHA256.o hmac.o PRNG.o encryptDecrypt.o additionalFunctions32.o modFunctions32.o modularInverse32.o montExponentiation32.o maskGenerationFunction.o signatureMessage.o verifySignature.o  keyEstablishmentFunctions32.o
	$(CC) $(CFLAGS) -o program main.o aes.o useAES.o helpfulFunctions.o sha2.o useSHA256.o hmac.o PRNG.o encryptDecrypt.o additionalFunctions32.o modFunctions32.o modularInverse32.o montExponentiation32.o maskGenerationFunction.o signatureMessage.o verifySignature.o keyEstablishmentFunctions32.o

main.o: ../ccsProject_insideGit/main.c 
	$(CC) $(CFLAGS) -c ../ccsProject_insideGit/main.c

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

#additionalFunctions.o: ../ccsProject_insideGit/Key_Establishment/Source/additionalFunctions.c ../ccsProject_insideGit/Key_Establishment/Header/additionalFunctions.h
#	$(CC) $(CFLAGS)	-c ../ccsProject_insideGit/Key_Establishment/Source/additionalFunctions.c

additionalFunctions32.o: ../ccsProject_insideGit/Key_Establishment/Source/additionalFunctions32.c ../ccsProject_insideGit/Key_Establishment/Header/additionalFunctions32.h
	$(CC) $(CFLAGS)	-c ../ccsProject_insideGit/Key_Establishment/Source/additionalFunctions32.c

#modFunctions.o: ../ccsProject_insideGit/Key_Establishment/Source/modFunctions.c ../ccsProject_insideGit/Key_Establishment/Header/modFunctions.h
#	$(CC) $(CFLAGS)	-c ../ccsProject_insideGit/Key_Establishment/Source/modFunctions.c
	
modFunctions32.o: ../ccsProject_insideGit/Key_Establishment/Source/modFunctions32.c ../ccsProject_insideGit/Key_Establishment/Header/modFunctions32.h
	$(CC) $(CFLAGS)	-c ../ccsProject_insideGit/Key_Establishment/Source/modFunctions32.c

#modularInverse.o: ../ccsProject_insideGit/Key_Establishment/Source/modularInverse.c ../ccsProject_insideGit/Key_Establishment/Header/modularInverse.h
#	$(CC) $(CFLAGS)	-c ../ccsProject_insideGit/Key_Establishment/Source/modularInverse.c
	
modularInverse32.o: ../ccsProject_insideGit/Key_Establishment/Source/modularInverse32.c ../ccsProject_insideGit/Key_Establishment/Header/modularInverse32.h
	$(CC) $(CFLAGS)	-c ../ccsProject_insideGit/Key_Establishment/Source/modularInverse32.c

#montExponentiation.o: ../ccsProject_insideGit/Key_Establishment/Source/montExponentiation.c ../ccsProject_insideGit/Key_Establishment/Header/montExponentiation.h
#	$(CC) $(CFLAGS)	-c ../ccsProject_insideGit/Key_Establishment/Source/montExponentiation.c

montExponentiation32.o: ../ccsProject_insideGit/Key_Establishment/Source/montExponentiation32.c ../ccsProject_insideGit/Key_Establishment/Header/montExponentiation32.h
	$(CC) $(CFLAGS)	-c ../ccsProject_insideGit/Key_Establishment/Source/montExponentiation32.c
	
#keyEstablishmentFunctions.o: ../ccsProject_insideGit/Key_Establishment/Source/keyEstablishmentFunctions.c ../ccsProject_insideGit/Key_Establishment/Header/keyEstablishmentFunctions.h
#	$(CC) $(CFLAGS)	-c ../ccsProject_insideGit/Key_Establishment/Source/keyEstablishmentFunctions.c

keyEstablishmentFunctions32.o: ../ccsProject_insideGit/Key_Establishment/Source/keyEstablishmentFunctions32.c ../ccsProject_insideGit/Key_Establishment/Header/keyEstablishmentFunctions32.h
	$(CC) $(CFLAGS)	-c ../ccsProject_insideGit/Key_Establishment/Source/keyEstablishmentFunctions32.c

signatureMessage.o: ../ccsProject_insideGit/Key_Establishment/Source/signatureMessage.c ../ccsProject_insideGit/Key_Establishment/Header/signatureMessage.h
	$(CC) $(CFLAGS) -c ../ccsProject_insideGit/Key_Establishment/Source/signatureMessage.c
	
verifySignature.o: ../ccsProject_insideGit/Key_Establishment/Source/verifySignature.c ../ccsProject_insideGit/Key_Establishment/Header/verifySignature.h
	$(CC) $(CFLAGS) -c ../ccsProject_insideGit/Key_Establishment/Source/verifySignature.c
	
maskGenerationFunction.o: ../ccsProject_insideGit/Key_Establishment/Source/maskGenerationFunction.c ../ccsProject_insideGit/Key_Establishment/Header/maskGenerationFunction.h
	$(CC) $(CFLAGS) -c ../ccsProject_insideGit/Key_Establishment/Source/maskGenerationFunction.c


clean:
	$(RM) program *.o


