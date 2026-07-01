CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++11

PROGRAMA = frota

OBJETOS = main.o Menu.o Frota.o Veiculo.o Carro.o Caminhao.o Moto.o

all: $(PROGRAMA)

$(PROGRAMA): $(OBJETOS)
	$(CXX) $(CXXFLAGS) -o $(PROGRAMA) $(OBJETOS)

main.o: main.cpp Menu.h VeiculoNaoEncontrado.h
	$(CXX) $(CXXFLAGS) -c main.cpp

Menu.o: Menu.cpp Menu.h Frota.h Carro.h Caminhao.h Moto.h
	$(CXX) $(CXXFLAGS) -c Menu.cpp

Frota.o: Frota.cpp Frota.h Arvore.h Veiculo.h VeiculoNaoEncontrado.h
	$(CXX) $(CXXFLAGS) -c Frota.cpp

Veiculo.o: Veiculo.cpp Veiculo.h
	$(CXX) $(CXXFLAGS) -c Veiculo.cpp

Carro.o: Carro.cpp Carro.h Veiculo.h
	$(CXX) $(CXXFLAGS) -c Carro.cpp

Caminhao.o: Caminhao.cpp Caminhao.h Veiculo.h
	$(CXX) $(CXXFLAGS) -c Caminhao.cpp

Moto.o: Moto.cpp Moto.h Veiculo.h
	$(CXX) $(CXXFLAGS) -c Moto.cpp

clean:
	rm -f *.o $(PROGRAMA)