#ifndef MOTO_H
#define MOTO_H

#include "Veiculo.h"

// Classe derivada que representa uma moto da frota.
class Moto : public Veiculo {

public:
    // Construtor com os dados comuns e a cilindrada da moto.
    Moto(string placa, string marca, double quilometragem,
         double custoManutencao, int cilindrada);

    // Retorna a cilindrada da moto.
    int getCilindrada() const;

    // Identifica o tipo real do objeto.
    string getTipo() const;

    // Calcula o custo de manutencao especifico da moto.
    double calculaCustoManutencao() const;

    // Acrescenta a cilindrada na impressao.
    void imprimir(ostream& out) const;

private:
    int cilindrada;
};

#endif