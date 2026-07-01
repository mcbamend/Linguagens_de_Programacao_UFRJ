#include <iostream>

#include "Ativo.h"

using namespace std;


// Construtor da classe "Ativo"
Ativo::Ativo(string nome) {
	setNome(nome);
}

// Define o nome do ativo (set)
void Ativo::setNome(string nome) {
	this->nome = nome;
}

// Retorna o nome do ativo (get)
string Ativo::getNome() {
	return nome;
}

// Adiciona um novo registro ao vetor de registros via pushback
void Ativo::adicionarRegistro(RegistroValor registro) {
	registros.push_back(registro);
}

// Exibe todos os registros dos ativos
void Ativo::mostrarRegistros() {
	
	cout << "Ativo: " << nome << endl;
	
	// Percorre todos os registros armazenados
	for (unsigned i = 0; i < registros.size(); i++) {
	
        cout << registros[i].getNomeIndicador() << ": " << registros[i].getValorNumerico() << endl;
	}
}

// Calcula e exibe a evolucao da media movel
void Ativo::mostrarMediaMovel() {
	
	// Janela da media movel 
	const int janela = 3;

	// Printa o nome do ativo
	cout << endl;
	cout << "Ativo: " << nome << endl;
	
	// Printa medias moveis
	cout << "Medias moveis: ";

	// Caso de nao ter registros suficientes para o calculo
	if (registros.size() < janela) {
        cout << endl;
        cout << "Nao ha registros suficientes." << endl;
        return;
	}

	// Percorre o vetor
	for (unsigned i = janela - 1; i < registros.size(); i++) {

		double soma = 0;
		
		// Soma os valores da janela atual
		for (unsigned j = i - janela + 1; j <= i; j++) {
			soma = soma + registros[j].getValorNumerico();
		}

		// Calcula a media da janela		
		double media = soma / janela;
		
		cout << media << " ";
       	}

    cout << endl;
}


// Calcula a media da ultima janela
double Ativo::calcularMediaUltimaJanela() {
	
	const int janela = 3;
    	double soma = 0;
    
	// Verifica se existem registros suficientes
	if (registros.size() < janela) {
		return 0;
       	}
    
	// Percorre apenas os 3 ultimos elementos
	for (unsigned i = registros.size() - janela; i < registros.size(); i++) {
		soma = soma + registros[i].getValorNumerico();  
      	}

    return soma / janela;
}


// Calcula a media da janela anterior
double Ativo::calcularMediaJanelaAnterior() {

     	const int janela = 3;
    	double soma = 0;

    	// Verifica a quantidade de registros
	if (registros.size() < 4) {
		return 0;
	}
	
	// Percorre a janela anterior
	for (unsigned i = registros.size() - janela - 1; i < registros.size() - 1; i++) {
		soma = soma + registros[i].getValorNumerico();
    	}

    return soma / janela;
}

// Calcula a variacao percentual entre as medias

double Ativo::calcularVariacaoPercentual() {

    	double mediaAtual = calcularMediaUltimaJanela();
    	double mediaAnterior = calcularMediaJanelaAnterior();
	
	// Evitando divisao por zero
    	if (mediaAnterior == 0) {
	 	return 0;
       	}

    	return ((mediaAtual - mediaAnterior) / mediaAnterior) * 100;
}

// Previsao do proximo valor usando regressao linear simples
void Ativo::preverProximoValor() {

	// Quantidade de registros
    	int n = registros.size();

	
	// Variaveis que armazenam os somatorios necessarios para aplocar as formulas da regressao linear simples, sendo x o indice do registro e y o valor armazenado
    	double somaX = 0;
    	double somaY = 0;
    	double somaXY = 0;
    	double somaX2 = 0;
	
	for (int i = 0; i < n; i++) {
		
		double x = i + 1;
		double y = registros[i].getValorNumerico();

		somaX = somaX + x;
		somaY = somaY + y;
		somaXY = somaXY + (x * y);
		somaX2 = somaX2 + (x * x);
    	}
	
	// Calculo do coeficiente angular a
	double a = (n * somaXY - somaX * somaY) / (n * somaX2 - somaX * somaX);

	// Calculo do coeficiente linear b
	double b = (somaY - a * somaX) / n;

	// Definindo proximo indice
    	double proximoX = n + 1;

	// Previsao
	double previsao = a * proximoX + b;

    cout << endl;
    cout << "Ativo: " << nome << endl;
    cout << "Coeficiente angular (a): " << a << endl;
    cout << "Coeficiente linear (b): " << b << endl;
    cout << "Previsao do proximo valor: " << previsao << endl;
}
