#ifndef ROUPA_H
#define ROUPA_H

#include "Peca.h"

// Representa uma peca de vestuario, como camisa, calca ou vestido.
class Roupa : public Peca {

public:
    // Recebe os dados comuns da peca e os atributos especificos da roupa.
    Roupa(int id, string nome, string material, double preco,
          int versatilidade, double temperaturaMinima,
          double temperaturaMaxima, int conforto,
          bool precisaManutencao, string tamanho,
          string categoriaRoupa);

    string getTamanho() const;
    string getCategoriaRoupa() const;

    void setTamanho(string tamanho);
    void setCategoriaRoupa(string categoriaRoupa);

    // Identifica o tipo real da peca.
    string getTipo() const override;

    // Acrescenta os atributos especificos na impressao.
    void imprimir(ostream& out) const override;

    // Converte os dados da roupa para uma linha de texto.
    string serializar() const override;

private:
    string tamanho;
    string categoriaRoupa;
};

#endif
