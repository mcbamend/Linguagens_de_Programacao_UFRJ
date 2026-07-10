#include "Acessorio.h"

#include <sstream>

using namespace std;

// Inicializa os dados comuns na classe Peca
// e os atributos especificos do acessorio.
Acessorio::Acessorio(int id,
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
                     string tipoAcessorio,
                     int nivelFragilidade)
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

    this->tipoAcessorio = tipoAcessorio;
    this->nivelFragilidade = nivelFragilidade;
}

// Retorna o tipo especifico do acessorio.
string Acessorio::getTipoAcessorio() const {
    return tipoAcessorio;
}

// Retorna o nivel de fragilidade do acessorio.
int Acessorio::getNivelFragilidade() const {
    return nivelFragilidade;
}

// Atualiza o tipo especifico do acessorio.
void Acessorio::setTipoAcessorio(string tipoAcessorio) {
    this->tipoAcessorio = tipoAcessorio;
}

// Atualiza o nivel de fragilidade do acessorio.
void Acessorio::setNivelFragilidade(int nivelFragilidade) {
    this->nivelFragilidade = nivelFragilidade;
}

// Identifica o tipo real do objeto durante o uso polimorfico.
string Acessorio::getTipo() const {
    return "Acessorio";
}

// Reaproveita a impressao dos dados comuns
// e acrescenta os atributos proprios do acessorio.
void Acessorio::imprimir(ostream& out) const {

    Peca::imprimir(out);

    out << "Tipo do acessorio: "
        << tipoAcessorio
        << endl;

    out << "Nivel de fragilidade: "
        << nivelFragilidade
        << endl;
}

// Converte os dados do acessorio em uma linha de texto.
// Os campos sao separados por ponto e virgula.
string Acessorio::serializar() const {

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
          << tipoAcessorio << ";"
          << nivelFragilidade;

    return linha.str();
}