#ifndef REPOSITORIO_H
#define REPOSITORIO_H

#include <iostream>
#include <vector>

using namespace std;

// Classe template responsável por armazenar e gerenciar objetos.
// Neste programa, ela será utilizada como Repositorio<Peca>.
template <class T>
class Repositorio {

private:
    // Armazena ponteiros para objetos do tipo T.
    vector<T*> itens;

    // Procura a posição de um item pelo identificador.
    int localizarIndice(int id) const {

        for (unsigned int i = 0; i < itens.size(); i++) {

            // Usa o operator==(int) definido na classe Peca.
            if (*(itens[i]) == id) {
                return i;
            }
        }

        return -1;
    }

public:
    Repositorio() {
    }

    /*
        O repositório é responsável pelos objetos armazenados.
        Por isso, seu destrutor libera cada objeto criado com new.
    */
    ~Repositorio() {

        for (unsigned int i = 0; i < itens.size(); i++) {
            delete itens[i];
        }

        itens.clear();
    }

    /*
        Impede que o repositório seja copiado.

        Como ele armazena ponteiros e é responsável por apagá-los,
        uma cópia poderia fazer dois repositórios tentarem apagar
        os mesmos objetos.
    */
    Repositorio(const Repositorio<T>& outro) = delete;

    Repositorio<T>& operator=(
        const Repositorio<T>& outro
    ) = delete;

    // Adiciona um novo item, desde que o ID ainda não exista.
    bool adicionar(T* item) {

        if (item == nullptr) {
            return false;
        }

        if (buscar(item->getId()) != nullptr) {
            return false;
        }

        itens.push_back(item);

        return true;
    }

    // Remove um item pelo ID.
    bool remover(int id) {

        int indice = localizarIndice(id);

        if (indice == -1) {
            return false;
        }

        // Libera o objeto antes de remover o ponteiro do vector.
        delete itens[indice];

        itens.erase(itens.begin() + indice);

        return true;
    }

    // Busca um item pelo ID.
    T* buscar(int id) const {

        int indice = localizarIndice(id);

        if (indice == -1) {
            return nullptr;
        }

        return itens[indice];
    }

    /*
        Sobrecarga do operador + para adicionar um item.

        Exemplo:
        repositorio + novaPeca;
    */
    Repositorio<T>& operator+(T* item) {

        adicionar(item);

        return *this;
    }

    /*
        Sobrecarga do operador - para remover pelo ID.

        Exemplo:
        repositorio - 5;
    */
    Repositorio<T>& operator-(int id) {

        remover(id);

        return *this;
    }

    /*
        Sobrecarga do operador [] para buscar pelo ID.

        Neste programa, o valor entre colchetes representa o ID,
        e não a posição no vector.
    */
    T* operator[](int id) const {
        return buscar(id);
    }

    // Retorna uma cópia do vector de ponteiros.
    vector<T*> obterItens() const {
        return itens;
    }

    // Retorna a quantidade de itens armazenados.
    unsigned int tamanho() const {
        return itens.size();
    }

    // Informa se o repositório está vazio.
    bool vazio() const {
        return itens.empty();
    }

    // Imprime todos os itens armazenados.
    void imprimir(ostream& out) const {

        if (itens.empty()) {
            out << "Nenhuma peca cadastrada." << endl;
            return;
        }

        for (unsigned int i = 0; i < itens.size(); i++) {

            out << "------------------------------" << endl;

            /*
                O ponteiro é desreferenciado para chamar
                o operator<< definido para Peca.
            */
            out << *(itens[i]) << endl;
        }

        out << "------------------------------" << endl;
    }
};

// Permite imprimir o repositório utilizando cout << repositorio.
template <class T>
ostream& operator<<(ostream& out,
                    const Repositorio<T>& repositorio) {

    repositorio.imprimir(out);

    return out;
}

#endif