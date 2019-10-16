Quash: main.o Executive.o Quash.o
	g++ -g -std=c++11 main.o Executive.o Quash.o -o Quash

main.o: main.cpp Executive.h
	g++ -std=c++11 -g -c main.cpp

Executive.o: Executive.h Executive.cpp Quash.h
	g++ -std=c++11 -g -c Executive.cpp

Quash.o: Quash.h Quash.cpp 
	g++ -std=c++11 -g -c Quash.cpp

clean:
	rm *.o Quash
