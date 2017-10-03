all: hw2

hw2: MainNumber.o
ifeq (${OS}, Windows_NT)
	g++ -o hw2 MainNumber.o -lgtest 
else
	g++ -o hw2 MainNumber.o -lgtest -lpthread
endif
MainNumber.o: MainNumber.cpp utTerm.h number.h atom.h variable.h
		g++ -std=gnu++0x -c MainNumber.cpp

clean:
ifeq (${OS}, Windows_NT)
	del *.o *.exe
else
	rm -f *.o hw2
endif
