#ifndef FILME_H
#define FILME_H

#include <iostream>
#include <string>

using namespace std;

// Estrutura usada para armazenar os dados de um filme do catalogo.
struct Filme {
    string titulo;
    string diretor;
    int ano;
    double nota;
};

// Impressao de um filme individual com cout << filme.
ostream& operator<<(ostream& out, const Filme& filme);

// Leitura dos dados de um filme com cin >> filme.
istream& operator>>(istream& in, Filme& filme);

// Dois filmes sao considerados iguais quando possuem o mesmo titulo.
bool operator==(const Filme& f1, const Filme& f2);

// Criterio de ordenacao: diretor e, em caso de empate, titulo.
bool operator<(const Filme& f1, const Filme& f2);

#endif