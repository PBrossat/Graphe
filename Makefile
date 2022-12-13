CXXFLAGS=-g -std=c++11 -Wall -pedantic

prog : main.o Graphe.o 
	g++ main.o Graphe.o -o main

main.o : main.cpp Graphe.h 
	g++ -g -Wall -c main.cpp -o main.o

Graphe.o : Graphe.cpp Graphe.h 
	g++ -g -Wall -c Graphe.cpp -o Graphe.o

clean:
	\rm *.o Graphe
	\rm *.o main 
