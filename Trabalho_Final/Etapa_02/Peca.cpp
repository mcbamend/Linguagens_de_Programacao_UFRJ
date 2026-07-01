#include "Peca.h"

// Inicializa os dados comuns a todos os tipos de peca.
Peca::Peca(int id, string nome, string material, double preco,
           int versatilidade, double temperaturaMinima,
           double temperaturaMaxima, int conforto,
           bool precisaManutencao) {

    this->id = id;
    this->nome = nome;
    this->material = material;
    this->preco = preco;
    this->versatilidade = versatilidade;
    this->temperaturaMinima = temperaturaMinima;
    this->temperaturaMaxima = temperaturaMaxima;
    this->conforto = conforto;
    this->precisaManutencao = precisaManutencao;

    // Uma peca nova ainda nao possui usos registrados.
    quantidadeUsos = 0;
    diasSemUso = 0;
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

int Peca::getConforto() const {
    return conforto;
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

void Peca::setConforto(int conforto) {
    this->conforto = conforto;
}

void Peca::setPrecisaManutencao(bool precisaManutencao) {
    this->precisaManutencao = precisaManutencao;
}

void Peca::setDiasSemUso(int diasSemUso) {
    this->diasSemUso = diasSemUso;
}

// Registra um novo uso da peca.
void Peca::registrarUso(int confortoInformado) {

    /*
        No primeiro uso, a avaliacao informada substitui a avaliacao inicial.
        Nos usos seguintes, e calculada uma media com as avaliacoes anteriores.
    */
    if (quantidadeUsos == 0) {
        conforto = confortoInformado;
    }
    else {
        conforto =
            ((conforto * quantidadeUsos) + confortoInformado)
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
    out << "Faixa de temperatura: "
        << temperaturaMinima << " a "
        << temperaturaMaxima << " graus" << endl;
    out << "Conforto medio: " << conforto << endl;
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
