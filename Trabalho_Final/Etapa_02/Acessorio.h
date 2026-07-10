#ifndef ACESSORIO_H
#define ACESSORIO_H

#include "Peca.h"

// Representa um acessorio, como bolsa, colar, cinto ou chapeu.
class Acessorio : public Peca {

public:
    /*
        Recebe os dados comuns da peca, incluindo o historico
        inicial de uso, e os atributos especificos do acessorio.
    */
    Acessorio(int id,
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
              string tipoAcessorio,
              int nivelFragilidade);

    string getTipoAcessorio() const;
    int getNivelFragilidade() const;

    void setTipoAcessorio(string tipoAcessorio);
    void setNivelFragilidade(int nivelFragilidade);

    // Identifica o tipo real da peca.
    string getTipo() const override;

    // Acrescenta os atributos especificos na impressao.
    void imprimir(ostream& out) const override;

    // Converte os dados do acessorio para uma linha de texto.
    string serializar() const override;

private:
    string tipoAcessorio;
    int nivelFragilidade;
};

#endif