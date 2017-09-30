all: hw2

hw2: mainNumber.o
ifeq (${OS}, Windows_NT)
	g++ -o hw2 mainNumber.o -lgtest 
else
	g++ -o hw2 mainNumber.o -lgtest -lpthread
endif
mainNumber.o: mainNumber.cpp utNumber.h number.h atom.h variable.h
		g++ -std=gnu++0x -c mainNumber.cpp

clean:
ifeq (${OS}, Windows_NT)
	del *.o *.exe
else
	rm -f *.o hw2
endif
