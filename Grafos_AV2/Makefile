programa: main.o Vertice.o Aresta.o Grafo.o
	g++ main.o Vertice.o Aresta.o Grafo.o -o programa

main.o: main.cpp Grafo.h Vertice.h Aresta.h
	g++ -Wall -c main.cpp

Vertice.o: Vertice.cpp Vertice.h
	g++ -Wall -c Vertice.cpp

Aresta.o: Aresta.cpp Aresta.h
	g++ -Wall -c Aresta.cpp

Grafo.o: Grafo.cpp Grafo.h Vertice.h Aresta.h
	g++ -Wall -c Grafo.cpp

clean:
	rm -f *.o programa