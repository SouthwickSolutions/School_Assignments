CXXFLAGS := -std=c++11 -Wall -Werror
CC = g++

CritterTest: main.o critter.o lion.o zebra.o main.o simulation.o
	$(CC) $(CXXFLAGS) -o CritterTest main.o critter.o lion.o zebra.o simulation.o
main.o: main.cpp
	$(CC) $(CXXFLAGS) -c main.cpp simulation.h 
critter.o: critter.cpp
	$(CC) $(CXXFLAGS) -c critter.cpp critter.h
lion.o: lion.cpp
	$(CC) $(CXXFLAGS) -c lion.cpp lion.h
zebra.o: zebra.cpp
	$(CC) $(CXXFLAGS) -c zebra.cpp zebra.h
simulation.o: simulation.cpp
		$(CC) $(CXXFLAGS) -c simulation.h simulation.cpp

clean:
	rm -f core *.o *.gch

run: ./CritterTest

memtest:
	g++ $(CXXFLAGS) -o CritterTest -g main.cpp
	valgrind --leak-check=full ./CritterTest

	clean:
		-rm -f *.o *~ main
