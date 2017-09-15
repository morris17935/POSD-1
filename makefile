all: exp

exp: main.o 
ifeq (${OS}, Windows_NT)
	g++ -o exp main.o -lgtest
else
	g++ -o exp main.o -lgtest -lpthread
endif
	
main.o: main.cpp utsort.h
	g++ -std=gnu++0x -c main.cpp

clean:	
ifeq (${OS}, Windows_NT)
	del *.o *.exe
else
	rm -f *.o exp
endif