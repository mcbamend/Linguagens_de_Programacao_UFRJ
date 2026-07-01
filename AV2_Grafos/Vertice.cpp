#include "Vertice.h"

// Construtor da classe Vertice
Vertice::Vertice(string nome) {
    setNome(nome);
}

// Define o nome do vertice
void Vertice::setNome(string nome) {
    this->nome = nome;
}

// Retorna o nome do vertice
string Vertice::getNome() {
    return nome;
}