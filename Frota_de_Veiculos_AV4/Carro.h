#ifndef CARRO_H
#define CARRO_H

#include "Veiculo.h"

// Classe derivada que representa um carro da frota.
class Carro : public Veiculo {

public:
    // Construtor com os dados comuns e o numero de portas.
    Carro(string placa, string marca, double quilometragem,
          double custoManutencao, int numPortas);

    // Retorna o numero de portas do carro.
    int getNumPortas() const;

    // Identifica o tipo real do objeto.
    string getTipo() const;

    // Calcula o custo de manutencao especifico do carro.
    double calculaCustoManutencao() const;

    // Acrescenta o numero de portas na impressao do veiculo.
    void imprimir(ostream& out) const;

private:
    int numPortas;
};

#endif