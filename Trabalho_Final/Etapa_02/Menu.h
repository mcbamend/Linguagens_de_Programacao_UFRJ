#ifndef MENU_H
#define MENU_H

#include <string>
#include <vector>

#include "ClosetLog.h"

using namespace std;

class Menu {

public:
    Menu();

    int lerOpcao();

    void executarOpcao(int opcao);

    void pausarELimpar() const;

private:
    /*
        Estrutura auxiliar usada apenas pelo menu.

        Ela evita repetir a leitura dos mesmos dados
        em roupa, calcado e acessorio.
    */
    struct DadosComunsCadastro {

        string nome;
        string material;
        double preco;

        int versatilidade;

        bool temperaturaInformada;
        double temperaturaMinima;
        double temperaturaMaxima;

        int quantidadeUsos;
        int diasSemUso;
        double confortoMedio;

        bool precisaManutencao;
    };

    ClosetLog closetLog;

    void mostrarMenu() const;

    void cadastrarPeca();
    void registrarUso();
    void listarPecas() const;
    void gerenciarPeca();
    void mostrarCustoPorUso() const;
    void analisarSubutilizacao() const;
    void agruparPorPerfil() const;
    void listarManutencao() const;

    void buscarPeca() const;
    void editarPeca();
    void removerPeca();

    /*
        Lê os dados que todos os tipos de peça possuem:
        nome, material, preço, versatilidade, histórico,
        conforto médio, manutenção e temperatura opcional.
    */
    DadosComunsCadastro lerDadosComunsCadastro() const;

    /*
        Lê a faixa de temperatura apenas quando o usuário
        quiser informar esse dado.
    */
    void lerTemperaturaOpcional(bool& temperaturaInformada,
                                double& temperaturaMinima,
                                double& temperaturaMaxima) const;

    /*
        Permite escolher uma peça digitando ID ou parte do nome.

        O ID continua sendo usado internamente, mas o usuário
        não fica obrigado a decorar o número da peça.
    */
    Peca* selecionarPecaPorIdOuNome() const;

    /*
        Usa selecionarPecaPorIdOuNome e retorna apenas o ID.

        Isso facilita funções como remover, editar,
        registrar uso e calcular custo por uso.
    */
    int selecionarIdPecaPorIdOuNome() const;

    /*
        Mostra uma versão curta da peça em listas de busca.
    */
    void imprimirResumoPeca(const Peca* peca) const;

    int lerInteiro(const string& mensagem) const;
    double lerDouble(const string& mensagem) const;
    string lerTexto(const string& mensagem) const;
    bool lerBooleano(const string& mensagem) const;

    void esperarEnter() const;
    void limparTela() const;
};

#endif