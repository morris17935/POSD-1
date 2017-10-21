all: hw4

hw4: MainNumber.o
ifeq (${OS}, Windows_NT)
	g++ -o hw4 MainNumber.o -lgtest 
else
	g++ -o hw4 MainNumber.o -lgtest -lpthread
endif
MainNumber.o: MainNumber.cpp  number.h atom.h variable.h struct.h list.h term.h 
		g++ -std=gnu++0x -c MainNumber.cpp

clean:
ifeq (${OS}, Windows_NT)
	del *.o *.exe
else
	rm -f *.o hw4
endif
