#ifndef CALCADO_H
#define CALCADO_H

#include "Peca.h"

// Representa um calcado, como tenis, bota, sandalia ou sapato.
class Calcado : public Peca {

public:
    /*
        Recebe os dados comuns da peca, incluindo o historico
        inicial de uso, e os atributos especificos do calcado.
    */
    Calcado(int id,
            string nome,
            string material,
            double preco,
            int versatilidade,
            double temperaturaMinima,
            double temperaturaMaxima,
            double confortoMedio,
            bool precisaManutencao,
            int quantidadeUsos,
            int diasSemUso,
            bool temperaturaInformada,
            int numeracao,
            bool impermeavel);

    int getNumeracao() const;
    bool getImpermeavel() const;

    void setNumeracao(int numeracao);
    void setImpermeavel(bool impermeavel);

    // Identifica o tipo real da peca.
    string getTipo() const override;

    // Acrescenta os atributos especificos na impressao.
    void imprimir(ostream& out) const override;

    // Converte os dados do calcado para uma linha de texto.
    string serializar() const override;

private:
    int numeracao;
    bool impermeavel;
};

#endif