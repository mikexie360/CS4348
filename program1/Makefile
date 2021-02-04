
output: main.o program1.o
	g++ main.o program1.o -o main

main.o: main.cpp
	g++ -c main.cpp

program1.o: program1.cpp program1.h
	g++ -c program1.cpp

clean:
	rm *.o main
