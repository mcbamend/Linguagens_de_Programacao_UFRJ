#include "Moto.h"

// Inicializa os atributos comuns na classe Veiculo
// e a cilindrada propria da moto.
Moto::Moto(string placa, string marca, double quilometragem,
           double custoManutencao, int cilindrada)
    : Veiculo(placa, marca, quilometragem, custoManutencao) {

    this->cilindrada = cilindrada;
}

// Retorna a cilindrada da moto.
int Moto::getCilindrada() const {
    return cilindrada;
}

// Identifica o tipo real do objeto.
string Moto::getTipo() const {
    return "Moto";
}

// Calcula o custo de manutencao especifico da moto.
// Foi acrescentado um valor proporcional a cilindrada.
double Moto::calculaCustoManutencao() const {
    return getCustoManutencaoBase() + (cilindrada * 0.5);
}

// Imprime os dados comuns e depois a cilindrada.
void Moto::imprimir(ostream& out) const {
    Veiculo::imprimir(out);
    out << "Cilindrada: "
        << cilindrada
        << " cc"
        << endl;
}