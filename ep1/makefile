#makefile

all: unit_test

unit_test: unit_test.o 
	g++ -o unit_test unit_test.cpp -lm
	
unit_test.o: unit_test.cpp tabeladesimbolos.hpp
	g++ unit_test.o unit_test.cpp -c -Wall -O0 
	
clean:
	rm -rf *.o*~ unit_test
