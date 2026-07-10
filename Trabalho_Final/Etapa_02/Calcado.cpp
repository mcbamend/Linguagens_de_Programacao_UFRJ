#include "Calcado.h"

#include <sstream>

using namespace std;

// Inicializa os dados comuns na classe Peca
// e os atributos especificos do calcado.
Calcado::Calcado(int id,
                 string nome,
                 string material,
                 double preco,
                 int versatilidade,
                 double temperaturaMinima,
                 double temperaturaMaxima,
                 double confortoMedio,
                 bool precisaManutencao,
                 int quantidadeUsos,
                 int diasSemUso,
                 bool temperaturaInformada,
                 int numeracao,
                 bool impermeavel)
    : Peca(id,
           nome,
           material,
           preco,
           versatilidade,
           temperaturaMinima,
           temperaturaMaxima,
           confortoMedio,
           precisaManutencao,
           quantidadeUsos,
           diasSemUso,
           temperaturaInformada) {

    this->numeracao = numeracao;
    this->impermeavel = impermeavel;
}

// Retorna a numeracao do calcado.
int Calcado::getNumeracao() const {
    return numeracao;
}

// Informa se o calcado e impermeavel.
bool Calcado::getImpermeavel() const {
    return impermeavel;
}

// Atualiza a numeracao do calcado.
void Calcado::setNumeracao(int numeracao) {
    this->numeracao = numeracao;
}

// Atualiza a informacao de impermeabilidade.
void Calcado::setImpermeavel(bool impermeavel) {
    this->impermeavel = impermeavel;
}

// Identifica o tipo real do objeto durante o uso polimorfico.
string Calcado::getTipo() const {
    return "Calcado";
}

// Reaproveita a impressao dos dados comuns
// e acrescenta os atributos proprios do calcado.
void Calcado::imprimir(ostream& out) const {

    Peca::imprimir(out);

    out << "Numeracao: "
        << numeracao
        << endl;

    out << "Impermeavel: "
        << (impermeavel ? "Sim" : "Nao")
        << endl;
}

// Converte os dados do calcado em uma linha de texto.
// Os campos sao separados por ponto e virgula.
string Calcado::serializar() const {

    ostringstream linha;

    linha << getTipo() << ";"
          << getId() << ";"
          << getNome() << ";"
          << getMaterial() << ";"
          << getPreco() << ";"
          << getQuantidadeUsos() << ";"
          << getDiasSemUso() << ";"
          << getVersatilidade() << ";"
          << getTemperaturaInformada() << ";"
          << getTemperaturaMinima() << ";"
          << getTemperaturaMaxima() << ";"
          << getConforto() << ";"
          << getPrecisaManutencao() << ";"
          << numeracao << ";"
          << impermeavel;

    return linha.str();
}