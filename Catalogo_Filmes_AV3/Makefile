CXX = g++
CXXFLAGS = -Wall -std=c++11

PROG = catalogo

OBJS = main.o Filme.o CatalogoFilmes.o

all: $(PROG)

$(PROG): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(PROG) $(OBJS)

main.o: main.cpp Filme.h CatalogoFilmes.h
	$(CXX) $(CXXFLAGS) -c main.cpp

Filme.o: Filme.cpp Filme.h
	$(CXX) $(CXXFLAGS) -c Filme.cpp

CatalogoFilmes.o: CatalogoFilmes.cpp CatalogoFilmes.h Filme.h
	$(CXX) $(CXXFLAGS) -c CatalogoFilmes.cpp

clean:
	rm -f *.o $(PROG)