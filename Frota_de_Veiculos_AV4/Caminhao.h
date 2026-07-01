#ifndef CAMINHAO_H
#define CAMINHAO_H

#include "Veiculo.h"

// Classe derivada que representa um caminhao da frota.
class Caminhao : public Veiculo {

public:
    // Construtor com os dados comuns e a capacidade de carga.
    Caminhao(string placa, string marca, double quilometragem,
             double custoManutencao, double capacidadeCarga);

    // Retorna a capacidade de carga do caminhao.
    double getCapacidadeCarga() const;

    // Identifica o tipo real do objeto.
    string getTipo() const;

    // Calcula o custo de manutencao especifico do caminhao.
    double calculaCustoManutencao() const;

    // Acrescenta a capacidade de carga na impressao.
    void imprimir(ostream& out) const;

private:
    double capacidadeCarga;
};

#endif