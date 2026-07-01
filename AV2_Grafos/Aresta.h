#ifndef ARESTA_H
#define ARESTA_H

#include <string>

using namespace std;

// Classe que representa uma aresta ponderada do grafo
class Aresta {

public:

    // Construtor
    Aresta(string origem, string destino, double peso);

    // Metodos set/get da origem
    void setOrigem(string origem);
    string getOrigem();

    // Metodos set/get do destino
    void setDestino(string destino);
    string getDestino();

    // Metodos set/get do peso
    void setPeso(double peso);
    double getPeso();

private:

    // Nome do vertice de origem
    string origem;

    // Nome do vertice de destino
    string destino;

    // Peso da aresta
    double peso;
};

#endif