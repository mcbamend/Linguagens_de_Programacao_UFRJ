#ifndef REGISTROVALOR_H
#define REGISTROVALOR_H

#include <string>

using namespace std;

// Classe que representa um registro de valor de um ativo
class RegistroValor {

public:
	// Construtor da classe
	RegistroValor(string nomeIndicador, double valorNumerico);

	// Definindo metodos set e get do indicador
	void setNomeIndicador(string nomeIndicador);
    	string getNomeIndicador();

	// Definindo metodos set e get do valor numerico
    	void setValorNumerico(double valorNumerico);
    	double getValorNumerico();

private:

	// Nome do indicador
    	string nomeIndicador;

	// Valor associado ao indicador
    	double valorNumerico;
};

#endif
