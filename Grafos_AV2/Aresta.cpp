#include "Aresta.h"

// Construtor da classe Aresta
Aresta::Aresta(string origem, string destino, double peso) {

    setOrigem(origem);
    setDestino(destino);
    setPeso(peso);
}

// Define o vertice de origem
void Aresta::setOrigem(string origem) {

    this->origem = origem;
}

// Retorna o vertice de origem
string Aresta::getOrigem() {

    return origem;
}

// Define o vertice de destino
void Aresta::setDestino(string destino) {

    this->destino = destino;
}

// Retorna o vertice de destino
string Aresta::getDestino() {

    return destino;
}

// Define o peso da aresta
void Aresta::setPeso(double peso) {

    this->peso = peso;
}

// Retorna o peso da aresta
double Aresta::getPeso() {

    return peso;
}