#ifndef CATALOGOFILMES_H
#define CATALOGOFILMES_H

#include <iostream>
#include <vector>
#include <string>
#include "Filme.h"

using namespace std;

class CatalogoFilmes {
private:
    // Vetor que armazena os filmes cadastrados no catalogo.
    vector<Filme> filmes;

    // Quantidade maxima de filmes permitida no catalogo.
    int capacidadeMaxima;

    // Nome do arquivo usado para salvar e carregar os filmes.
    string nomeArquivo;

public:
    // Construtor: define a capacidade maxima e carrega os dados do arquivo.
    CatalogoFilmes(int capacidade, string arquivo);

    // Carrega os filmes salvos no arquivo de texto.
    void carregarArquivo();

    // Salva todos os filmes atuais no arquivo de texto.
    void salvarArquivo();

    // Retorna a quantidade atual de filmes no catalogo.
    int getQuantidadeFilmes() const;

    // Insercao de filme no catalogo usando: catalogo = catalogo + filme
    CatalogoFilmes operator+(const Filme& filme);

    // Remocao de filme pelo titulo usando: catalogo = catalogo - filme
    CatalogoFilmes operator-(const Filme& filme);

    // Busca filmes por diretor usando: catalogo["Nome do Diretor"]
    vector<Filme> operator[](string diretor);

    // Atualiza a nota de um filme usando: catalogo("Titulo", novaNota)
    bool operator()(string titulo, double novaNota);

    // Compara dois catalogos pela quantidade de filmes.
    bool operator>(const CatalogoFilmes& outroCatalogo) const;

    // Impressao do catalogo completo usando: cout << catalogo
    friend ostream& operator<<(ostream& out, const CatalogoFilmes& catalogo);

    // Busca um filme pelo título
    bool buscarFilmePorTitulo(string titulo, Filme &filmeEncontrado);

};

#endif
