#include "Veiculo.h"

// Inicializa os dados comuns a todos os tipos de veiculo.
Veiculo::Veiculo(string placa, string marca, double quilometragem,
                 double custoManutencao) {

    this->placa = placa;
    this->marca = marca;
    this->quilometragem = quilometragem;
    this->custoManutencao = custoManutencao;
}

Veiculo::~Veiculo() {
}

string Veiculo::getPlaca() const {
    return placa;
}

string Veiculo::getMarca() const {
    return marca;
}

double Veiculo::getQuilometragem() const {
    return quilometragem;
}

double Veiculo::getCustoManutencaoBase() const {
    return custoManutencao;
}

void Veiculo::setQuilometragem(double novaQuilometragem) {
    quilometragem = novaQuilometragem;
}

// A placa define a posicao do veiculo na arvore.
bool Veiculo::operator>(const Veiculo& outro) const {
    return placa > outro.placa;
}

// Dois veiculos sao iguais quando possuem a mesma placa.
bool Veiculo::operator==(const Veiculo& outro) const {
    return placa == outro.placa;
}

// Permite comparar o veiculo atual diretamente com uma placa.
bool Veiculo::operator==(const string& outraPlaca) const {
    return placa == outraPlaca;
}

// Impressao dos atributos comuns.
void Veiculo::imprimir(ostream& out) const {
    out << "Tipo: " << getTipo() << endl;
    out << "Placa: " << placa << endl;
    out << "Marca: " << marca << endl;
    out << "Quilometragem: " << quilometragem << " km" << endl;
    out << "Custo de manutencao: R$ "
        << calculaCustoManutencao()
        << endl;
}

// Encaminha a impressao para o metodo virtual.
ostream& operator<<(ostream& out, const Veiculo& veiculo) {
    veiculo.imprimir(out);
    return out;
}