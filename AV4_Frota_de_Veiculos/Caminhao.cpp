#include "Caminhao.h"

// Inicializa os atributos comuns na classe Veiculo
// e a capacidade de carga propria do caminhao.
Caminhao::Caminhao(string placa, string marca, double quilometragem,
                   double custoManutencao, double capacidadeCarga)
    : Veiculo(placa, marca, quilometragem, custoManutencao) {

    this->capacidadeCarga = capacidadeCarga;
}

// Retorna a capacidade maxima de carga do caminhao.
double Caminhao::getCapacidadeCarga() const {
    return capacidadeCarga;
}

// Identifica o tipo real do objeto.
string Caminhao::getTipo() const {
    return "Caminhao";
}

// Calcula o custo de manutencao especifico do caminhao.
// Foi acrescentado um valor proporcional a capacidade de carga.
double Caminhao::calculaCustoManutencao() const {
    return getCustoManutencaoBase() + (capacidadeCarga * 20.0);
}

// Imprime os dados comuns e depois a capacidade de carga.
void Caminhao::imprimir(ostream& out) const {
    Veiculo::imprimir(out);
    out << "Capacidade de carga: "
        << capacidadeCarga
        << " toneladas"
        << endl;
}