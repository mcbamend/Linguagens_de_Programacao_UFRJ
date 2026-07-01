#ifndef VEICULO_H
#define VEICULO_H

#include <iostream>
#include <string>

using namespace std;

// Classe base para os diferentes tipos de veiculo da frota.
class Veiculo {

public:
    Veiculo(string placa, string marca, double quilometragem,
            double custoManutencao);

    virtual ~Veiculo();

    string getPlaca() const;
    string getMarca() const;
    double getQuilometragem() const;
    double getCustoManutencaoBase() const;

    void setQuilometragem(double novaQuilometragem);

    // Comparacao usada na ordenacao da arvore.
    bool operator>(const Veiculo& outro) const;

    // Comparacao entre dois veiculos pela placa.
    bool operator==(const Veiculo& outro) const;

    // Comparacao entre um veiculo e uma placa procurada.
    bool operator==(const string& outraPlaca) const;

    virtual string getTipo() const = 0;
    virtual double calculaCustoManutencao() const = 0;

    virtual void imprimir(ostream& out) const;

private:
    string placa;
    string marca;
    double quilometragem;
    double custoManutencao;
};

ostream& operator<<(ostream& out, const Veiculo& veiculo);

#endif