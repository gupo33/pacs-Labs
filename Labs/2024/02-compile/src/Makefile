all: main

main: test.o liblinearalgebra.so
	g++ test.o -L${mkSuitesparseLib} -lumfpack -L${PWD} -llinearalgebra -o main

test.o: test.cpp
	g++ test.cpp -c -I../include -I${mkEigenInc} -I${mkSuitesparseInc}

liblinearalgebra.so: utilities.o
	g++ -shared utilities.o -o liblinearalgebra.so

utilities.o: Utilities.cpp
	g++ -c -I../include -I/${mkEigenInc} -fPIC Utilities.cpp

#potentially add clean and distclean