#include <iostream>

#include "SistemaFinanceiro.h"

using namespace std;

// Adiciona um novo ativo no sistema
void SistemaFinanceiro::adicionarAtivo(Ativo ativo) {

	// Insere um ativo no final do vetor
    	ativos.push_back(ativo);
	
    	cout << endl;
    	cout << "Ativo inserido com sucesso!" << endl;
}

// Exibe todos os ativos cadastrados no sistema
void SistemaFinanceiro::mostrarRelatorio() {

    	cout << endl;
    	cout << "~~~~~ RELATORIO DO SISTEMA ~~~~~" << endl;
    	cout << endl;

	// Verifica se existem ativos cadastrados
	if (ativos.size() == 0) {
		cout << "Nenhum ativo cadastrado." << endl;
    	}
    
	// Percorre todos os ativos do vetor
	for (unsigned i = 0; i < ativos.size(); i++) {
		
		// Cada ativo exibe seus proprios registros
		ativos[i].mostrarRegistros();

		cout << endl;
    	}

    	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
}

// Procura um ativo pelo nome e adiciona um registro nele
void SistemaFinanceiro::adicionarRegistroEmAtivo( string nomeAtivo, RegistroValor registro) {
    	cout << endl;
    	cout << "~~~~~ Adicionar Registro em Ativo ~~~~~" << endl;
    
	// Percorre todos os ativos cadastrados
	for (unsigned i = 0; i < ativos.size(); i++) {
	
		// Verifica se o nome do ativo coincide
		if (ativos[i].getNome() == nomeAtivo) {

			// Adiciona o registro ao tivo encontrado    
			ativos[i].adicionarRegistro(registro);
		    
			cout << endl;
	    		cout << "Registro inserido com sucesso!" << endl;
	     		return;
		}
    	}

    	cout << endl;
    	cout << "Ativo nao encontrado." << endl;
}

// Exibe as medias moveis de todos os ativos
void SistemaFinanceiro::mostrarMediasMoveis() {
    
	cout << endl;
    	cout << "~~~~~ MEDIAS MOVEIS ~~~~~" << endl;
	
	// Precisa de pelo menos 3 ativos
    	if (ativos.size() < 3) {
		cout << endl;
		cout << "Cadastre pelo menos 3 ativos." << endl;
    	}

	// Cada ativo calcula e exibe sua media movel
    	for (unsigned i = 0; i < ativos.size(); i++) {
		ativos[i].mostrarMediaMovel();
    	}

    cout << endl;
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
}

// Ordena os ativos pela media da ultima janela
void SistemaFinanceiro::ordenarAtivosPorMediaMovel() {

	// Ordenacao
    	for (unsigned i = 0; i < ativos.size(); i++) {

		for (unsigned j = i + 1; j < ativos.size(); j++) {

			// Compara medias moveis
	    		if (ativos[j].calcularMediaUltimaJanela() > ativos[i].calcularMediaUltimaJanela()) {
				// Troca os ativos para as devidas posicoes
				Ativo auxiliar = ativos[i];
				ativos[i] = ativos[j];
				ativos[j] = auxiliar;
	    		}
		}
    	}
    
	cout << endl;
    	cout << "~~~~~ ATIVOS ORDENADOS POR MEDIA MOVEL ~~~~~" << endl;
    	cout << endl;


	// Percorre os ativos ja ordenados
    	for (unsigned i = 0; i < ativos.size(); i++) {

		// Armazena a media movel mais recente do ativo
		double mediaAtual = ativos[i].calcularMediaUltimaJanela();

		// Calcula a  variacao percentual entre as medias moveis
		double variacao = ativos[i].calcularVariacaoPercentual();
		
		cout << "Ativo: " << ativos[i].getNome() << endl;
		cout << "Media da ultima janela: " << mediaAtual << endl;
		cout << "Variacao percentual: " << variacao << "%" << endl;
		
		// Verifica se a variacao ultrapassa de +-10%
		if (variacao > 10 || variacao < -10) {
	    		cout << "Variacao anormal: SIM" << endl;
		} 
		
		else {
	    		cout << "Variacao anormal: NAO" << endl;
		}

		cout << endl;
    	}
}

// Exibe a previsao do proximo valor de cada ativo
void SistemaFinanceiro::preverValores() {
	
    	cout << endl;
    	cout << "~~~~~ PREVISAO DE VALORES ~~~~~" << endl;
    	cout << endl;
	
	// Cada ativo realiza sua propria regrassao linear
    	for (unsigned i = 0; i < ativos.size(); i++) {
	
		ativos[i].preverProximoValor();
		
		cout << endl;
    	}
}
