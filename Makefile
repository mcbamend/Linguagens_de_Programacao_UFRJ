programa: main.o RegistroValor.o Ativo.o SistemaFinanceiro.o
	g++ main.o RegistroValor.o Ativo.o SistemaFinanceiro.o -o programa

main.o: main.cpp RegistroValor.h Ativo.h SistemaFinanceiro.h
	g++ -Wall -c main.cpp

RegistroValor.o: RegistroValor.cpp RegistroValor.h
	g++ -Wall -c RegistroValor.cpp

Ativo.o: Ativo.cpp Ativo.h RegistroValor.h
	g++ -Wall -c Ativo.cpp

SistemaFinanceiro.o: SistemaFinanceiro.cpp SistemaFinanceiro.h Ativo.h RegistroValor.h
	g++ -Wall -c SistemaFinanceiro.cpp

clean:
	rm -f *.o programa