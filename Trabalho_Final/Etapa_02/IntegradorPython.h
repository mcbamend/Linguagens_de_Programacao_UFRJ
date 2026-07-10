#ifndef INTEGRADORPYTHON_H
#define INTEGRADORPYTHON_H

#include <vector>

#include "Peca.h"

using namespace std;


// Representa o resultado retornado pela funcao Python
// que identifica pecas subutilizadas.
struct ResultadoSubutilizacao {

    int idPeca;
    double pontuacao;
    bool subutilizada;
};


// Representa o resultado retornado pela funcao Python
// que agrupa as pecas por perfil de uso.
struct ResultadoAgrupamento {

    int idPeca;
    int grupo;
};


// Responsavel pela comunicacao direta entre C++ e Python.
class IntegradorPython {

public:
    /*
        Inicializa o interpretador Python.

        O interpretador permanece ativo durante a existencia
        deste objeto.
    */
    IntegradorPython();

    // Encerra o interpretador ao final do programa.
    ~IntegradorPython();

    /*
        O integrador nao pode ser copiado.

        Duas copias poderiam tentar controlar e encerrar
        o mesmo interpretador Python.
    */
    IntegradorPython(
        const IntegradorPython& outro
    ) = delete;

    IntegradorPython& operator=(
        const IntegradorPython& outro
    ) = delete;

    /*
        Envia os dados das pecas para:

        analisar_subutilizacao(dados)

        no arquivo analises.py.

        Retorna o ID, a pontuacao e a classificacao
        de cada peca.
    */
    vector<ResultadoSubutilizacao>
    analisarSubutilizacao(
        const vector<Peca*>& pecas
    ) const;

    /*
        Envia os dados das pecas e a quantidade
        de grupos para:

        agrupar_por_perfil(dados, quantidade_grupos)

        no arquivo analises.py.
    */
    vector<ResultadoAgrupamento>
    agruparPorPerfil(
        const vector<Peca*>& pecas,
        int quantidadeGrupos
    ) const;

private:
    /*
        Registra se o interpretador foi inicializado
        corretamente por este objeto.
    */
    bool interpretadorAtivo;
};

#endif