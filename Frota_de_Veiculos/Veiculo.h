#ifndef VEICULO_H
#define VEICULO_H

#include <iostream>
#include <string>

using namespace std;

// Classe base para os diferentes tipos de veiculo da frota.
class Veiculo {

public:
    // Construtor com os atributos comuns a todos os veiculos.
    Veiculo(string placa, string marca, double quilometragem,
            double custoManutencao);

    // Destrutor virtual para permitir a destruicao correta
    // de objetos derivados por meio de ponteiros para Veiculo.
    virtual ~Veiculo();

    // Metodos de acesso aos atributos comuns.
    string getPlaca() const;
    string getMarca() const;
    double getQuilometragem() const;
    double getCustoManutencaoBase() const;

    // Permite atualizar a quilometragem do veiculo.
    void setQuilometragem(double novaQuilometragem);

    // Compara dois veiculos pela placa.
    bool operator>(const Veiculo& outro) const;
    bool operator==(const Veiculo& outro) const;

    // Cada classe derivada informa seu proprio tipo.
    virtual string getTipo() const = 0;

    // Cada tipo de veiculo calcula seu custo de forma diferente.
    virtual double calculaCustoManutencao() const = 0;

    // Cada classe derivada acrescenta seus dados especificos na impressao.
    virtual void imprimir(ostream& out) const;

private:
    string placa;
    string marca;
    double quilometragem;
    double custoManutencao;
};

// Permite imprimir um veiculo usando cout << veiculo.
ostream& operator<<(ostream& out, const Veiculo& veiculo);

#endif
