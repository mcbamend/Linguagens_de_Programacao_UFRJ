#ifndef PECA_H
#define PECA_H

#include <iostream>
#include <string>

using namespace std;

// Classe base para os diferentes tipos de peca do guarda-roupa.
class Peca {

public:
    Peca(int id, string nome, string material, double preco,
         int versatilidade, double temperaturaMinima,
         double temperaturaMaxima, double confortoMedio,
         bool precisaManutencao,
         int quantidadeUsos = 0,
         int diasSemUso = 0,
         bool temperaturaInformada = true);

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
    bool getTemperaturaInformada() const;
    double getConforto() const;
    bool getPrecisaManutencao() const;

    void setNome(string nome);
    void setPreco(double preco);
    void setVersatilidade(int versatilidade);
    void setConforto(double confortoMedio);
    void setPrecisaManutencao(bool precisaManutencao);
    void setDiasSemUso(int diasSemUso);

    /*
        Atualiza a faixa de temperatura.

        Quando temperaturaInformada for false, os valores de
        temperatura minima e maxima nao devem ser considerados
        pelo menu nem pela impressao.
    */
    void setFaixaTemperatura(double temperaturaMinima,
                             double temperaturaMaxima,
                             bool temperaturaInformada);

    /*
        Restaura os dados de uso ao carregar a peca do arquivo
        ou ao cadastrar uma peca que ja tinha historico anterior.
    */
    void restaurarHistorico(int quantidadeUsos,
                            int diasSemUso,
                            double confortoMedio);

    // Registra um novo uso e atualiza a media de conforto.
    void registrarUso(double confortoInformado);

    // Calculado no proprio C++, pois e uma operacao simples.
    double calcularCustoPorUso() const;

    // O identificador sera usado nas buscas e comparacoes internas.
    bool operator==(const Peca& outra) const;
    bool operator==(int idProcurado) const;

    // Cada classe derivada informa seu tipo especifico.
    virtual string getTipo() const = 0;

    // Cada tipo acrescenta seus proprios dados na impressao.
    virtual void imprimir(ostream& out) const;

    // Cada classe derivada define como seus dados serao salvos.
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
    bool temperaturaInformada;

    double confortoMedio;

    bool precisaManutencao;
};

// Permite imprimir qualquer peca usando cout << peca.
ostream& operator<<(ostream& out, const Peca& peca);

#endif