#ifndef VERTICE_H
#define VERTICE_H

#include <string>

using namespace std;

// Classe que representa um vertice do grafo
class Vertice {

public:

    // Construtor
    Vertice(string nome);

    // Metodo set/get do nome
    void setNome(string nome);
    string getNome();

private:

    // Nome do vertice
    string nome;
};

#endif