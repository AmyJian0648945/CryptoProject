# How to use:
# --> To create all object files, write "make" into the compiler
# --> To remove all .o (object files) and .exe files, write "make remove"
# --> To execute the .exe file, write "./a.out" 
 

CC = gcc
#CFLAGS = -Wall -pedantic -ansi
CFLAGS = 

program:  testVectorsSetToledo.o additionalFunctions32.o modFunctions32.o modularInverse32.o montExponentiation32.o
	$(CC) $(CFLAGS) -o program testVectorsSetToledo.o additionalFunctions32.o modFunctions32.o modularInverse32.o montExponentiation32.o

testVectorsSetToledo.o: testVectorsSetToledo.c
	$(CC) $(CFLAGS) -c testVectorsSetToledo.c

additionalFunctions32.o: additionalFunctions32.c ../Header/additionalFunctions32.h
	$(CC) $(CFLAGS)	-c additionalFunctions32.c
	
modFunctions32.o: modFunctions32.c ../Header/modFunctions32.h
	$(CC) $(CFLAGS)	-c modFunctions32.c
	
modularInverse32.o: modularInverse32.c
	$(CC) $(CFLAGS)	-c modularInverse32.c

montExponentiation32.o: montExponentiation32.c
	$(CC) $(CFLAGS)	-c montExponentiation32.c

keyEstablishmentFunctions32.o:keyEstablishmentFunctions32.c ../Header/keyEstablishmentFunctions32.h
	$(CC) $(CFLAGS)	-c keyEstablishmentFunctions32.c

signatureMessage.o: signatureMessage.c ../Header/signatureMessage.h
	$(CC) $(CFLAGS) -c signatureMessage.c
	
verifySignature.o: verifySignature.c ../Header/verifySignature.h
	$(CC) $(CFLAGS) -c verifySignature.c
	
maskGenerationFunction.o: maskGenerationFunction.c ../Header/maskGenerationFunction.h
	$(CC) $(CFLAGS) -c maskGenerationFunction.c


clean:
	$(RM) program *.o


