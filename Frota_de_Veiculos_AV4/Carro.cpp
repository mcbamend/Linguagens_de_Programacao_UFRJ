#include "Carro.h"

// Inicializa os atributos comuns na classe Veiculo
// e o atributo especifico da classe Carro.
Carro::Carro(string placa, string marca, double quilometragem,
             double custoManutencao, int numPortas)
    : Veiculo(placa, marca, quilometragem, custoManutencao) {

    this->numPortas = numPortas;
}

// Retorna a quantidade de portas do carro.
int Carro::getNumPortas() const {
    return numPortas;
}

// Identifica o tipo real do objeto.
string Carro::getTipo() const {
    return "Carro";
}

// Calcula o custo de manutencao especifico do carro.
// Foi acrescentado um valor de 50 para cada porta.
double Carro::calculaCustoManutencao() const {
    return getCustoManutencaoBase() + (numPortas * 50.0);
}

// Imprime primeiro os dados comuns de Veiculo
// e depois o atributo especifico de Carro.
void Carro::imprimir(ostream& out) const {
    Veiculo::imprimir(out);
    out << "Numero de portas: " << numPortas << endl;
}