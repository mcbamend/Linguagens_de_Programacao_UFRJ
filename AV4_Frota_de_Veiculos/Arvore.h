#ifndef ARVORE_H
#define ARVORE_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

// No generico usado na arvore binaria.
template <class T>
class No {

public:
    T elemento;
    No<T>* esquerda;
    No<T>* direita;

    No(T elemento) {
        this->elemento = elemento;
        esquerda = NULL;
        direita = NULL;
    }
};


// Arvore binaria implementada como classe template.
template <class T>
class Arvore {

private:
    No<T>* raiz;

    // Insere o elemento a partir do no atual.
    bool inserirRecursivo(No<T>*& noAtual, T novoElemento) {

        // Encontrou uma posicao vazia para o novo elemento.
        if (noAtual == NULL) {
            noAtual = new No<T>(novoElemento);
            return true;
        }

        // A comparacao por igualdade impede placas repetidas.
        if (*novoElemento == *(noAtual->elemento)) {
            return false;
        }

        // Pela regra do enunciado, elementos maiores vao para a esquerda.
        if (*novoElemento > *(noAtual->elemento)) {
            return inserirRecursivo(noAtual->esquerda, novoElemento);
        }

        // Elementos menores vao para a direita.
        return inserirRecursivo(noAtual->direita, novoElemento);
    }


    // Busca recursivamente um veiculo pela placa.
    T buscarRecursivo(No<T>* noAtual, const string& placa) const {

        if (noAtual == NULL) {
            return NULL;
        }

        /*
            A comparacao utiliza o operator== de Veiculo,
            sobrecarregado para receber uma string com a placa.
        */
        if (*(noAtual->elemento) == placa) {
            return noAtual->elemento;
        }

        string placaAtual = noAtual->elemento->getPlaca();

        // Placas maiores foram armazenadas na subarvore esquerda.
        if (placa > placaAtual) {
            return buscarRecursivo(noAtual->esquerda, placa);
        }

        // Placas menores foram armazenadas na subarvore direita.
        return buscarRecursivo(noAtual->direita, placa);
    }


    /*
        Como os menores elementos ficam na direita,
        este percurso imprime em ordem alfabetica crescente.
    */
    void imprimirRecursivo(No<T>* noAtual, ostream& out) const {

        if (noAtual == NULL) {
            return;
        }

        imprimirRecursivo(noAtual->direita, out);

        out << *(noAtual->elemento) << endl;

        imprimirRecursivo(noAtual->esquerda, out);
    }


    // Copia os ponteiros da arvore para um vector.
    void coletarRecursivo(No<T>* noAtual,
                          vector<T>& elementos) const {

        if (noAtual == NULL) {
            return;
        }

        coletarRecursivo(noAtual->direita, elementos);

        elementos.push_back(noAtual->elemento);

        coletarRecursivo(noAtual->esquerda, elementos);
    }


    // Libera primeiro as subarvores e depois o no atual.
    void destruirRecursivo(No<T>* noAtual) {

        if (noAtual == NULL) {
            return;
        }

        destruirRecursivo(noAtual->esquerda);
        destruirRecursivo(noAtual->direita);

        delete noAtual->elemento;
        delete noAtual;
    }


public:
    Arvore() {
        raiz = NULL;
    }

    ~Arvore() {
        destruirRecursivo(raiz);
    }

    bool inserir(T elemento) {
        return inserirRecursivo(raiz, elemento);
    }

    /*
        O operador + representa a insercao de um elemento.
        A propria arvore e alterada e retornada.
    */
    Arvore<T>& operator+(T elemento) {
        inserir(elemento);
        return *this;
    }

    T buscar(const string& placa) const {
        return buscarRecursivo(raiz, placa);
    }

    vector<T> obterElementos() const {
        vector<T> elementos;

        coletarRecursivo(raiz, elementos);

        return elementos;
    }

    bool vazia() const {
        return raiz == NULL;
    }

    void imprimir(ostream& out) const {

        if (raiz == NULL) {
            out << "Frota vazia." << endl;
            return;
        }

        imprimirRecursivo(raiz, out);
    }
};


// Permite imprimir a arvore com cout << arvore.
template <class T>
ostream& operator<<(ostream& out, const Arvore<T>& arvore) {

    arvore.imprimir(out);

    return out;
}

#endif