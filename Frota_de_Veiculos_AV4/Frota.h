#ifndef FROTA_H
#define FROTA_H

#include <iostream>
#include <string>
#include <vector>

#include "Veiculo.h"
#include "Arvore.h"
#include "VeiculoNaoEncontrado.h"

using namespace std;

// Gerencia os veiculos armazenados na arvore.
class Frota {

public:
    // Insere um veiculo usando o operador + da arvore.
    bool insere(Veiculo* veiculo);

    // Retorna o veiculo encontrado ou NULL.
    Veiculo* busca(string placa) const;

    // Busca pela placa e lanca excecao se nao encontrar.
    Veiculo* operator()(string placa);

    // Busca e atualiza a quilometragem.
    Veiculo* operator()(string placa, double novaQuilometragem);

    void imprimir() const;

    void calculaCustoManutencao() const;

private:
    Arvore<Veiculo*> arvore;
};

#endif