#include "Roupa.h"

#include <sstream>

using namespace std;

// Inicializa os dados comuns na classe Peca
// e os atributos especificos da roupa.
Roupa::Roupa(int id,
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
             string tamanho,
             string categoriaRoupa)
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

    this->tamanho = tamanho;
    this->categoriaRoupa = categoriaRoupa;
}

// Retorna o tamanho da roupa.
string Roupa::getTamanho() const {
    return tamanho;
}

// Retorna a categoria da roupa.
string Roupa::getCategoriaRoupa() const {
    return categoriaRoupa;
}

// Atualiza o tamanho da roupa.
void Roupa::setTamanho(string tamanho) {
    this->tamanho = tamanho;
}

// Atualiza a categoria da roupa.
void Roupa::setCategoriaRoupa(string categoriaRoupa) {
    this->categoriaRoupa = categoriaRoupa;
}

// Identifica o tipo real do objeto durante o uso polimorfico.
string Roupa::getTipo() const {
    return "Roupa";
}

// Reaproveita a impressao dos dados comuns
// e acrescenta os atributos proprios da roupa.
void Roupa::imprimir(ostream& out) const {

    Peca::imprimir(out);

    out << "Tamanho: "
        << tamanho
        << endl;

    out << "Categoria da roupa: "
        << categoriaRoupa
        << endl;
}

// Converte os dados da roupa em uma linha de texto.
// Os campos sao separados por ponto e virgula.
string Roupa::serializar() const {

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
          << tamanho << ";"
          << categoriaRoupa;

    return linha.str();
}