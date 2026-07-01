#include "RegistroValor.h"

// Construtor da classe RegistroValor
RegistroValor::RegistroValor(string nomeIndicador, double valorNumerico) {

	// Inicializando os atributos do objeto
    	setNomeIndicador(nomeIndicador);
    	setValorNumerico(valorNumerico);
}

// Define o nome do indicador
void RegistroValor::setNomeIndicador(string nomeIndicador) {
	this->nomeIndicador = nomeIndicador;
}

// Retorna o nome do indicador
string RegistroValor::getNomeIndicador() {
    	return nomeIndicador;
}

// Define o valor numerico do registro
void RegistroValor::setValorNumerico(double valorNumerico) {
    	this->valorNumerico = valorNumerico;
}

// Retorna o valor numerico do registro
double RegistroValor::getValorNumerico() {
    	return valorNumerico;
}
