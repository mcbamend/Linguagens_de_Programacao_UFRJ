#ifndef ATIVO_H
#define ATIVO_H

#include <string>
#include <vector>

// Composicao entre Ativo e RegistroValor
#include "RegistroValor.h"

using namespace std;

class Ativo {

public:
	// Construtor da classe "Ativo"
	Ativo(string nome);

	// Metodos de set e get
	void setNome(string nome);
	string getNome();

	// Adicionando um registro ao ativo
	void adicionarRegistro(RegistroValor registro);

	// Exibir todos os registros
	void mostrarRegistros();

	// Exibir a evolucao da media movel
	void mostrarMediaMovel();

	// Calcular medias moveis e variacao percentual
	double calcularMediaUltimaJanela();
	double calcularMediaJanelaAnterior();
	double calcularVariacaoPercentual();

	// Previsao usando regressao linear simples
	void preverProximoValor();

private:

	// Nome do ativo
	string nome;

	// Vetor que armazena os registros do ativo (permite facil insercao e acesso aos elementos)
	vector<RegistroValor> registros;
};

#endif
