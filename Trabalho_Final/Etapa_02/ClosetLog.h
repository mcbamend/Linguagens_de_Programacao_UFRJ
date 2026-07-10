#ifndef CLOSETLOG_H
#define CLOSETLOG_H

#include <iostream>
#include <string>
#include <vector>

#include "Peca.h"
#include "Roupa.h"
#include "Calcado.h"
#include "Acessorio.h"
#include "Repositorio.h"
#include "Excecoes.h"
#include "IntegradorPython.h"

using namespace std;

// Classe principal de gerenciamento do guarda-roupa.
class ClosetLog {

public:
    // Recebe o nome do arquivo utilizado para persistencia.
    ClosetLog(string nomeArquivo = "pecas.csv");

    /*
        Cadastra uma roupa e retorna o ID criado
        automaticamente pelo sistema.

        A peca pode ser cadastrada ja com historico inicial:
        quantidade de usos, dias sem uso e conforto medio.
    */
    int cadastrarRoupa(
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
        string tamanho,
        string categoriaRoupa
    );

    /*
        Cadastra um calcado e retorna o ID criado.

        A temperatura pode ser informada ou deixada como
        nao especificada.
    */
    int cadastrarCalcado(
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
        bool impermeavel
    );

    /*
        Cadastra um acessorio e retorna o ID criado.

        Para acessorios, a faixa de temperatura pode ficar
        como nao especificada, pois nem sempre faz sentido
        relacionar esse tipo de peca ao clima.
    */
    int cadastrarAcessorio(
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
        int nivelFragilidade
    );

    // Busca uma peca pelo ID.
    Peca* buscarPeca(int id) const;

    /*
        Busca pecas pelo nome ou por parte do nome.

        Essa funcao nao substitui o ID internamente,
        mas torna o sistema mais facil de usar no menu.
    */
    vector<Peca*> buscarPecasPorNome(
        string termo,
        unsigned int limite = 5
    ) const;

    // Remove uma peca pelo ID.
    void removerPeca(int id);

    /*
        Atualiza os atributos que existem em qualquer tipo de peca.

        Os atributos especificos, como tamanho, numeracao
        ou tipo de acessorio, continuam sendo controlados
        pelas classes derivadas.
    */
    void atualizarPeca(
        int id,
        string novoNome,
        double novoPreco,
        int novaVersatilidade,
        double novoConfortoMedio,
        bool precisaManutencao,
        int diasSemUso,
        bool temperaturaInformada,
        double temperaturaMinima,
        double temperaturaMaxima
    );

    // Registra um novo uso e atualiza a avaliacao media de conforto.
    void registrarUso(int id, double confortoInformado);

    // Retorna o custo medio por uso de uma peca.
    double calcularCustoPorUso(int id) const;

    // Retorna todas as pecas que precisam de manutencao.
    vector<Peca*> listarPecasComManutencao() const;

    // Retorna uma copia do vector de ponteiros armazenado.
    vector<Peca*> obterPecas() const;

    // Retorna a quantidade de pecas cadastradas.
    unsigned int quantidadePecas() const;

    // Exibe todas as pecas.
    void imprimir(ostream& out) const;

    /*
        Executa a funcao externa em Python que identifica
        pecas com perfil de subutilizacao.
    */
    vector<ResultadoSubutilizacao>
    analisarPecasSubutilizadas() const;

    /*
        Executa a funcao externa em Python que agrupa
        as pecas de acordo com o perfil de uso.
    */
    vector<ResultadoAgrupamento>
    agruparPecasPorPerfil(int quantidadeGrupos) const;

    // Salva as pecas cadastradas no arquivo de persistencia.
    void salvarDados() const;

    // Carrega as pecas armazenadas no arquivo de persistencia.
    void carregarDados();

private:
    Repositorio<Peca> repositorio;

    string nomeArquivo;

    IntegradorPython integradorPython;

    // Identificador que sera atribuido ao proximo cadastro.
    int proximoId;

    // Gera um novo identificador unico.
    int gerarId();

    /*
        Busca uma peca e lanca a excecao personalizada
        quando o ID nao existe.
    */
    Peca* buscarOuLancar(int id) const;

    // Valida os atributos comuns a todos os tipos de peca.
    void validarDadosComuns(
        double preco,
        int versatilidade,
        double confortoMedio
    ) const;

    // Valida a faixa de temperatura quando ela for informada.
    void validarTemperatura(
        bool temperaturaInformada,
        double temperaturaMinima,
        double temperaturaMaxima
    ) const;

    // Valida os dados de historico inicial da peca.
    void validarHistorico(
        int quantidadeUsos,
        int diasSemUso,
        double confortoMedio
    ) const;

    // Valida uma avaliacao de conforto.
    void validarConforto(double conforto) const;
};


// Permite imprimir o ClosetLog com cout << closetLog.
ostream& operator<<(ostream& out, const ClosetLog& closetLog);

#endif