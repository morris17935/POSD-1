all: hw3

hw3: MainNumber.o
ifeq (${OS}, Windows_NT)
	g++ -o hw3 MainNumber.o -lgtest 
else
	g++ -o hw3 MainNumber.o -lgtest -lpthread
endif
MainNumber.o: MainNumber.cpp  number.h atom.h variable.h struct.h term.h
		g++ -std=gnu++0x -c MainNumber.cpp

clean:
ifeq (${OS}, Windows_NT)
	del *.o *.exe
else
	rm -f *.o hw3
endif
