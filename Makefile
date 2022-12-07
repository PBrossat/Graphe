prog : main.o Graphe.o 
	g++ main.o Graphe.o -o main

main.o : main.cpp Graphe.h 
	g++ -g -Wall -c main.cpp -o main.o

Graphe.o : Graphe.cpp Graphe.h 
	g++ -g -Wall -c Graphe.cpp -o Graphe.o
