#ifndef PECA_H
#define PECA_H

#include <iostream>
#include <string>

using namespace std;

// Classe base para os diferentes tipos de peça do guarda-roupa.
class Peca {

public:
    Peca(int id, string nome, string material, double preco,
         int versatilidade, double temperaturaMinima,
         double temperaturaMaxima, int conforto,
         bool precisaManutencao);

    virtual ~Peca();

    int getId() const;
    string getNome() const;
    string getMaterial() const;
    double getPreco() const;
    int getQuantidadeUsos() const;
    int getDiasSemUso() const;
    int getVersatilidade() const;
    double getTemperaturaMinima() const;
    double getTemperaturaMaxima() const;
    int getConforto() const;
    bool getPrecisaManutencao() const;

    void setNome(string nome);
    void setPreco(double preco);
    void setVersatilidade(int versatilidade);
    void setConforto(int conforto);
    void setPrecisaManutencao(bool precisaManutencao);
    void setDiasSemUso(int diasSemUso);

    // Registra um novo uso e reinicia o tempo sem uso.
    void registrarUso(int confortoInformado);

    // Calculado no próprio C++, pois é uma operação simples.
    double calcularCustoPorUso() const;

    // O identificador será usado nas buscas e comparações.
    bool operator==(const Peca& outra) const;
    bool operator==(int idProcurado) const;

    // Cada classe derivada informa seu tipo específico.
    virtual string getTipo() const = 0;

    // Cada tipo acrescenta seus próprios dados na impressão.
    virtual void imprimir(ostream& out) const;

    // Cada classe derivada define como seus dados serão salvos.
    virtual string serializar() const = 0;

private:
    int id;
    string nome;
    string material;
    double preco;
    int quantidadeUsos;
    int diasSemUso;
    int versatilidade;
    double temperaturaMinima;
    double temperaturaMaxima;
    int conforto;
    bool precisaManutencao;
};

// Permite imprimir qualquer peça usando cout << peca.
ostream& operator<<(ostream& out, const Peca& peca);

#endif
