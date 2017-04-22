# CFlags will be passed onto the compiler
CC = gcc
CFLAGS = -Wall -pedantic -ansi

output.out: aes.o useAES.o main.o
	$(CC) aes.o useAES.o main.o

main.o: ../main.c 
	$(CC) $(CFLAGS) -c ../main.c

aes.o: ../library/aes.c ../library/aes.h
	$(CC) $(CFLAGS) -c ../library/aes.c 

useAES.o: ../library/useAES.c ../library/useAES.h
	$(CC) $(CFLAGS) -c ../library/useAES.c  





#To execute all, type "make"
#To delete all object files, type "make clean"


#cryptoProjectMake: main.c mainSignature.c mainModularArithmetic.c testMontToledo.c
#	gcc -Wall -pedantic -ansi main.c -o hmacExample.exe
#	gcc -Wall -pedantic -ansi mainSignature.c -o signatureExample.exe
#	gcc -Wall -pedantic -ansi mainModularArithmetic.c -o modularArithmetic.exe
#	gcc -Wall -pedantic -ansi testMontToledo.c -o montToledo.exe

#module1: module1.c module1.h
#	gcc -Wall -pedantic -ansi module1.c -c -o module1.o

#module2: module2.c module2.h module1.h
#	gcc -Wall -pedantic -ansi module2.c -c -o module2.o

#main: main.c mainmacros.h
#	gcc -Wall -pedantic -ansi main.c -c -o main.o

#program: main.o module1.o module2.o
#	gcc -Wall -pedantic -ansi main.o module1.o module2.o -o program

#all: module1 module2 main program