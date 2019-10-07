Squash: main.o Executive.o Squash.o 
	g++ -g -std=c++11 main.o Executive.o Squash.o -o Squash

main.o: main.cpp Executive.h
	g++ -std=c++11 -g -c main.cpp

Executive.o: Executive.h Executive.cpp Squash.h 
	g++ -std=c++11 -g -c Executive.cpp

Linkedlist.o: Squash.h Squash.cpp 
	g++ -std=c++11 -g -c Squash.cpp

clean:
	rm *.o Squash
