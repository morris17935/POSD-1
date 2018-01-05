all: hw8

hw8: mainProlog.o
ifeq (${OS}, Windows_NT)
	g++ -o hw8 mainProlog.o -lgtest 
else
	g++ -o hw8 mainProlog.o -lgtest -lpthread
endif
mainProlog.o: mainProlog.cpp  number.h atom.h variable.h struct.h list.h term.h scanner.h parser.h global.h node.h
		g++ -std=gnu++0x -c mainProlog.cpp
clean:
ifeq (${OS}, Windows_NT)
	del *.o *.exe
else
	rm -f *.o hw8
endif
