#ifndef SISTEMAFINANCEIRO_H
#define SISTEMAFINANCEIRO_H

#include <vector>
#include <string>

// Composicao com Ativo
#include "Ativo.h"

using namespace std;

// Classe responsavel por armazenar e manipular todos os ativos
class SistemaFinanceiro {

public:
	// Adiciona um novo ativo ao sistema
    	void adicionarAtivo(Ativo ativo);

	// Procura um ativo pelo nome e adiciona um registro nele
    	void adicionarRegistroEmAtivo(string nomeAtivo, RegistroValor registro);

	// Mostra todos os ativos cadastrados e seus registros
    	void mostrarRelatorio();

	// Mostra as medias moveis dos ativos cadastrados
	void mostrarMediasMoveis();

	// Ordena os ativos pela ultima media movel e verifica variacoes anormais
    	void ordenarAtivosPorMediaMovel();

	// Realiza a previsao do proximo valor para os ativos
    	void preverValores();

private:
	// Vetor que armazena todos os ativos do sistema
    	vector<Ativo> ativos;
};

#endif
