test: testVectorsSetToledo32.o additionalFunctions32.o montExponentiation32.o modularInverse32.o modFunctions32.o
	gcc -o test testVectorsSetToledo32.o additionalFunctions32.o montExponentiation32.o modularInverse32.o modFunctions32.o
	
testVectorsSetToledo32.o: testVectorsSetToledo32.c
	gcc -c testVectorsSetToledo32.c
additionalFunctions32.o: additionalFunctions32.c ../Header/additionalFunctions32.h
	gcc -c additionalFunctions32.c
modFunctions32.o: modFunctions32.c	../Header/modFunctions32.h
	gcc -c modFunctions32.c
modularInverse32.o: modularInverse32.c	../Header/modularInverse32.h
	gcc -c modularInverse32.c
montExponentiation32.o: montExponentiation32.c	../Header/montExponentiation32.h
	gcc -c montExponentiation32.c