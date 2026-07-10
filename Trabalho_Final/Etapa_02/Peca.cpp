#include "Peca.h"

// Inicializa os dados comuns a todos os tipos de peca.
Peca::Peca(int id, string nome, string material, double preco,
           int versatilidade, double temperaturaMinima,
           double temperaturaMaxima, double confortoMedio,
           bool precisaManutencao,
           int quantidadeUsos,
           int diasSemUso,
           bool temperaturaInformada) {

    this->id = id;
    this->nome = nome;
    this->material = material;
    this->preco = preco;
    this->versatilidade = versatilidade;

    this->temperaturaMinima = temperaturaMinima;
    this->temperaturaMaxima = temperaturaMaxima;
    this->temperaturaInformada = temperaturaInformada;

    this->confortoMedio = confortoMedio;
    this->precisaManutencao = precisaManutencao;

    this->quantidadeUsos = quantidadeUsos;
    this->diasSemUso = diasSemUso;
}

// O destrutor e virtual porque os objetos serao acessados
// por meio de ponteiros para a classe base Peca.
Peca::~Peca() {
}

int Peca::getId() const {
    return id;
}

string Peca::getNome() const {
    return nome;
}

string Peca::getMaterial() const {
    return material;
}

double Peca::getPreco() const {
    return preco;
}

int Peca::getQuantidadeUsos() const {
    return quantidadeUsos;
}

int Peca::getDiasSemUso() const {
    return diasSemUso;
}

int Peca::getVersatilidade() const {
    return versatilidade;
}

double Peca::getTemperaturaMinima() const {
    return temperaturaMinima;
}

double Peca::getTemperaturaMaxima() const {
    return temperaturaMaxima;
}

bool Peca::getTemperaturaInformada() const {
    return temperaturaInformada;
}

double Peca::getConforto() const {
    return confortoMedio;
}

bool Peca::getPrecisaManutencao() const {
    return precisaManutencao;
}

void Peca::setNome(string nome) {
    this->nome = nome;
}

void Peca::setPreco(double preco) {
    this->preco = preco;
}

void Peca::setVersatilidade(int versatilidade) {
    this->versatilidade = versatilidade;
}

void Peca::setConforto(double confortoMedio) {
    this->confortoMedio = confortoMedio;
}

void Peca::setPrecisaManutencao(bool precisaManutencao) {
    this->precisaManutencao = precisaManutencao;
}

void Peca::setDiasSemUso(int diasSemUso) {
    this->diasSemUso = diasSemUso;
}

// Atualiza a faixa de temperatura da peca.
// Se temperaturaInformada for false, a faixa nao sera considerada.
void Peca::setFaixaTemperatura(double temperaturaMinima,
                               double temperaturaMaxima,
                               bool temperaturaInformada) {

    this->temperaturaMinima = temperaturaMinima;
    this->temperaturaMaxima = temperaturaMaxima;
    this->temperaturaInformada = temperaturaInformada;
}

// Restaura os dados que foram salvos no arquivo
// ou informados no cadastro inicial.
void Peca::restaurarHistorico(int quantidadeUsos,
                              int diasSemUso,
                              double confortoMedio) {

    this->quantidadeUsos = quantidadeUsos;
    this->diasSemUso = diasSemUso;
    this->confortoMedio = confortoMedio;
}

// Registra um novo uso da peca.
void Peca::registrarUso(double confortoInformado) {

    /*
        Se a peca ainda nao tinha usos registrados,
        a nota informada se torna o conforto medio.

        Se ja existiam usos, a nova nota entra na media.
    */
    if (quantidadeUsos == 0) {
        confortoMedio = confortoInformado;
    }
    else {
        confortoMedio =
            ((confortoMedio * quantidadeUsos) + confortoInformado)
            / (quantidadeUsos + 1);
    }

    quantidadeUsos++;

    // Depois de ser utilizada, a peca deixa de estar sem uso.
    diasSemUso = 0;
}

// Calcula quanto foi pago, em media, por cada uso da peca.
double Peca::calcularCustoPorUso() const {

    // Evita divisao por zero quando a peca ainda nao foi utilizada.
    if (quantidadeUsos == 0) {
        return 0.0;
    }

    return preco / quantidadeUsos;
}

// Duas pecas sao consideradas iguais quando possuem o mesmo identificador.
bool Peca::operator==(const Peca& outra) const {
    return id == outra.id;
}

// Permite comparar diretamente uma peca com um identificador.
bool Peca::operator==(int idProcurado) const {
    return id == idProcurado;
}

// Imprime os atributos comuns a todos os tipos de peca.
void Peca::imprimir(ostream& out) const {

    out << "Tipo: " << getTipo() << endl;
    out << "ID: " << id << endl;
    out << "Nome: " << nome << endl;
    out << "Material: " << material << endl;
    out << "Preco: R$ " << preco << endl;
    out << "Quantidade de usos: " << quantidadeUsos << endl;
    out << "Dias sem uso: " << diasSemUso << endl;
    out << "Versatilidade: " << versatilidade << endl;

    if (temperaturaInformada) {
        out << "Faixa de temperatura: "
            << temperaturaMinima << " a "
            << temperaturaMaxima << " graus" << endl;
    }
    else {
        out << "Faixa de temperatura: nao especificada" << endl;
    }

    out << "Conforto medio: " << confortoMedio << endl;

    out << "Precisa de manutencao: "
        << (precisaManutencao ? "Sim" : "Nao")
        << endl;

    if (quantidadeUsos > 0) {
        out << "Custo por uso: R$ "
            << calcularCustoPorUso()
            << endl;
    }
    else {
        out << "Custo por uso: ainda nao calculado" << endl;
    }
}

// Encaminha a impressao para o metodo virtual da peca.
ostream& operator<<(ostream& out, const Peca& peca) {

    peca.imprimir(out);

    return out;
}