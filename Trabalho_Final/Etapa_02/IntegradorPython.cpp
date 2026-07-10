#include <Python.h>

#include "IntegradorPython.h"
#include "Excecoes.h"

#include <iostream>
#include <vector>

using namespace std;


namespace {

/*
    Exibe no terminal o erro produzido pelo Python,
    quando existir, e lanca a excecao usada pelo C++.
*/
void lancarErroIntegracao() {

    if (PyErr_Occurred()) {
        PyErr_Print();
    }

    throw ErroIntegracaoPython();
}


/*
    Coloca um objeto Python dentro de uma tupla.

    PyTuple_SetItem passa a ser responsavel pelo objeto
    recebido, por isso nao usamos Py_DECREF no valor
    depois da insercao.
*/
bool definirItemTupla(
    PyObject* tupla,
    Py_ssize_t posicao,
    PyObject* valor
) {

    if (valor == nullptr) {
        return false;
    }

    return PyTuple_SetItem(
        tupla,
        posicao,
        valor
    ) == 0;
}


/*
    Converte uma Peca do C++ para uma tupla Python.

    Formato enviado:

    (
        id,
        preco,
        quantidade_usos,
        dias_sem_uso,
        versatilidade,
        conforto,
        precisa_manutencao
    )
*/
PyObject* criarTuplaPeca(const Peca* peca) {

    if (peca == nullptr) {
        return nullptr;
    }

    PyObject* tupla = PyTuple_New(7);

    if (tupla == nullptr) {
        return nullptr;
    }

    if (!definirItemTupla(
            tupla,
            0,
            PyLong_FromLong(peca->getId())
        ) ||
        !definirItemTupla(
            tupla,
            1,
            PyFloat_FromDouble(peca->getPreco())
        ) ||
        !definirItemTupla(
            tupla,
            2,
            PyLong_FromLong(peca->getQuantidadeUsos())
        ) ||
        !definirItemTupla(
            tupla,
            3,
            PyLong_FromLong(peca->getDiasSemUso())
        ) ||
        !definirItemTupla(
            tupla,
            4,
            PyLong_FromLong(peca->getVersatilidade())
        ) ||
        !definirItemTupla(
            tupla,
            5,
            PyLong_FromLong(peca->getConforto())
        ) ||
        !definirItemTupla(
            tupla,
            6,
            PyBool_FromLong(
                peca->getPrecisaManutencao() ? 1 : 0
            )
        )) {

        Py_DECREF(tupla);

        return nullptr;
    }

    return tupla;
}


/*
    Converte o vector de Peca* para uma lista Python
    contendo uma tupla para cada peca.
*/
PyObject* criarListaPecas(
    const vector<Peca*>& pecas
) {

    PyObject* lista = PyList_New(
        static_cast<Py_ssize_t>(pecas.size())
    );

    if (lista == nullptr) {
        return nullptr;
    }

    for (unsigned int i = 0; i < pecas.size(); i++) {

        PyObject* tupla = criarTuplaPeca(pecas[i]);

        if (tupla == nullptr) {
            Py_DECREF(lista);
            return nullptr;
        }

        /*
            PyList_SetItem passa a controlar a referencia
            da tupla depois da insercao.
        */
        if (PyList_SetItem(
                lista,
                static_cast<Py_ssize_t>(i),
                tupla
            ) != 0) {

            Py_DECREF(lista);

            return nullptr;
        }
    }

    return lista;
}


/*
    Importa o arquivo analises.py como modulo Python.
*/
PyObject* importarModuloAnalises() {

    return PyImport_ImportModule("analises");
}


/*
    Procura uma funcao dentro do modulo e verifica
    se o objeto encontrado pode ser chamado.
*/
PyObject* obterFuncao(
    PyObject* modulo,
    const char* nomeFuncao
) {

    PyObject* funcao = PyObject_GetAttrString(
        modulo,
        nomeFuncao
    );

    if (funcao == nullptr) {
        return nullptr;
    }

    if (!PyCallable_Check(funcao)) {

        Py_DECREF(funcao);

        PyErr_SetString(
            PyExc_TypeError,
            "O objeto encontrado no modulo nao e uma funcao."
        );

        return nullptr;
    }

    return funcao;
}


/*
    Converte o retorno de analisar_subutilizacao:

    [
        (id, pontuacao, subutilizada),
        ...
    ]

    para vector<ResultadoSubutilizacao>.
*/
vector<ResultadoSubutilizacao>
converterResultadoSubutilizacao(
    PyObject* retorno
) {

    vector<ResultadoSubutilizacao> resultados;

    PyObject* sequencia = PySequence_Fast(
        retorno,
        "O retorno da analise deve ser uma sequencia."
    );

    if (sequencia == nullptr) {
        lancarErroIntegracao();
    }

    Py_ssize_t quantidade =
        PySequence_Fast_GET_SIZE(sequencia);

    for (Py_ssize_t i = 0; i < quantidade; i++) {

        PyObject* item =
            PySequence_Fast_GET_ITEM(sequencia, i);

        PyObject* campos = PySequence_Fast(
            item,
            "Cada resultado deve ser uma tupla."
        );

        if (campos == nullptr) {
            Py_DECREF(sequencia);
            lancarErroIntegracao();
        }

        if (PySequence_Fast_GET_SIZE(campos) != 3) {

            Py_DECREF(campos);
            Py_DECREF(sequencia);

            PyErr_SetString(
                PyExc_ValueError,
                "O resultado de subutilizacao deve ter tres campos."
            );

            lancarErroIntegracao();
        }

        PyObject* campoId =
            PySequence_Fast_GET_ITEM(campos, 0);

        PyObject* campoPontuacao =
            PySequence_Fast_GET_ITEM(campos, 1);

        PyObject* campoSubutilizada =
            PySequence_Fast_GET_ITEM(campos, 2);

        long idPeca = PyLong_AsLong(campoId);

        double pontuacao =
            PyFloat_AsDouble(campoPontuacao);

        int subutilizada =
            PyObject_IsTrue(campoSubutilizada);

        if (PyErr_Occurred() || subutilizada < 0) {

            Py_DECREF(campos);
            Py_DECREF(sequencia);

            lancarErroIntegracao();
        }

        ResultadoSubutilizacao resultado;

        resultado.idPeca = static_cast<int>(idPeca);
        resultado.pontuacao = pontuacao;
        resultado.subutilizada = subutilizada != 0;

        resultados.push_back(resultado);

        Py_DECREF(campos);
    }

    Py_DECREF(sequencia);

    return resultados;
}


/*
    Converte o retorno de agrupar_por_perfil:

    [
        (id, grupo),
        ...
    ]

    para vector<ResultadoAgrupamento>.
*/
vector<ResultadoAgrupamento>
converterResultadoAgrupamento(
    PyObject* retorno
) {

    vector<ResultadoAgrupamento> resultados;

    PyObject* sequencia = PySequence_Fast(
        retorno,
        "O retorno do agrupamento deve ser uma sequencia."
    );

    if (sequencia == nullptr) {
        lancarErroIntegracao();
    }

    Py_ssize_t quantidade =
        PySequence_Fast_GET_SIZE(sequencia);

    for (Py_ssize_t i = 0; i < quantidade; i++) {

        PyObject* item =
            PySequence_Fast_GET_ITEM(sequencia, i);

        PyObject* campos = PySequence_Fast(
            item,
            "Cada resultado deve ser uma tupla."
        );

        if (campos == nullptr) {
            Py_DECREF(sequencia);
            lancarErroIntegracao();
        }

        if (PySequence_Fast_GET_SIZE(campos) != 2) {

            Py_DECREF(campos);
            Py_DECREF(sequencia);

            PyErr_SetString(
                PyExc_ValueError,
                "O resultado do agrupamento deve ter dois campos."
            );

            lancarErroIntegracao();
        }

        PyObject* campoId =
            PySequence_Fast_GET_ITEM(campos, 0);

        PyObject* campoGrupo =
            PySequence_Fast_GET_ITEM(campos, 1);

        long idPeca = PyLong_AsLong(campoId);
        long grupo = PyLong_AsLong(campoGrupo);

        if (PyErr_Occurred()) {

            Py_DECREF(campos);
            Py_DECREF(sequencia);

            lancarErroIntegracao();
        }

        ResultadoAgrupamento resultado;

        resultado.idPeca = static_cast<int>(idPeca);
        resultado.grupo = static_cast<int>(grupo);

        resultados.push_back(resultado);

        Py_DECREF(campos);
    }

    Py_DECREF(sequencia);

    return resultados;
}

} // fim do namespace


/*
    Inicializa o interpretador Python.

    Tambem adiciona o diretorio atual ao sys.path,
    permitindo que o programa encontre analises.py.
*/
IntegradorPython::IntegradorPython() {

    interpretadorAtivo = false;

    /*
        Caso ainda nao exista um interpretador Python,
        este objeto fica responsavel por inicializa-lo.
    */
    if (!Py_IsInitialized()) {

        Py_Initialize();

        interpretadorAtivo = true;
    }

    if (!Py_IsInitialized()) {
        interpretadorAtivo = false;
        throw ErroIntegracaoPython();
    }

    #ifdef _WIN32

    /*
        No Windows, bibliotecas como NumPy dependem de DLLs
        armazenadas na pasta bin da instalacao do Python.

        O objeto retornado e mantido em uma variavel global
        do Python para que o diretorio continue registrado.
    */
    const char* configurarDiretorioDll =
        "import os, sys\n"
        "_closetlog_dll_dir = "
        "os.add_dll_directory(os.path.join(sys.prefix, 'bin'))\n";

    if (PyRun_SimpleString(configurarDiretorioDll) != 0) {

        if (PyErr_Occurred()) {
            PyErr_Print();
        }

        if (interpretadorAtivo) {
            Py_FinalizeEx();
            interpretadorAtivo = false;
        }

        throw ErroIntegracaoPython();
    }

#endif

    /*
        PySys_GetObject devolve uma referencia emprestada
        para a lista sys.path.
    */
    PyObject* caminhoPython = PySys_GetObject("path");

    if (caminhoPython == nullptr) {

        if (PyErr_Occurred()) {
            PyErr_Print();
        }

        if (interpretadorAtivo) {
            Py_FinalizeEx();
            interpretadorAtivo = false;
        }

        throw ErroIntegracaoPython();
    }

    PyObject* diretorioAtual =
        PyUnicode_FromString(".");

    if (diretorioAtual == nullptr) {

        if (PyErr_Occurred()) {
            PyErr_Print();
        }

        if (interpretadorAtivo) {
            Py_FinalizeEx();
            interpretadorAtivo = false;
        }

        throw ErroIntegracaoPython();
    }

    if (PyList_Insert(
            caminhoPython,
            0,
            diretorioAtual
        ) != 0) {

        Py_DECREF(diretorioAtual);

        if (PyErr_Occurred()) {
            PyErr_Print();
        }

        if (interpretadorAtivo) {
            Py_FinalizeEx();
            interpretadorAtivo = false;
        }

        throw ErroIntegracaoPython();
    }

    Py_DECREF(diretorioAtual);
}


/*
    Encerra o interpretador somente quando este objeto
    foi responsavel por inicializa-lo.
*/
IntegradorPython::~IntegradorPython() {

    if (interpretadorAtivo && Py_IsInitialized()) {

        Py_FinalizeEx();

        interpretadorAtivo = false;
    }
}


/*
    Chama no Python:

    analisar_subutilizacao(dados)
*/
vector<ResultadoSubutilizacao>
IntegradorPython::analisarSubutilizacao(
    const vector<Peca*>& pecas
) const {

    if (!Py_IsInitialized()) {
        throw ErroIntegracaoPython();
    }

    PyObject* dadosPython =
        criarListaPecas(pecas);

    if (dadosPython == nullptr) {
        lancarErroIntegracao();
    }

    PyObject* modulo = importarModuloAnalises();

    if (modulo == nullptr) {

        Py_DECREF(dadosPython);

        lancarErroIntegracao();
    }

    PyObject* funcao = obterFuncao(
        modulo,
        "analisar_subutilizacao"
    );

    if (funcao == nullptr) {

        Py_DECREF(modulo);
        Py_DECREF(dadosPython);

        lancarErroIntegracao();
    }

    /*
        Equivale em Python a:

        analises.analisar_subutilizacao(dadosPython)
    */
    PyObject* retorno = PyObject_CallFunctionObjArgs(
        funcao,
        dadosPython,
        nullptr
    );

    Py_DECREF(funcao);
    Py_DECREF(modulo);
    Py_DECREF(dadosPython);

    if (retorno == nullptr) {
        lancarErroIntegracao();
    }

    vector<ResultadoSubutilizacao> resultados;

    try {

        resultados =
            converterResultadoSubutilizacao(retorno);
    }
    catch (...) {

        Py_DECREF(retorno);

        throw;
    }

    Py_DECREF(retorno);

    return resultados;
}


/*
    Chama no Python:

    agrupar_por_perfil(dados, quantidadeGrupos)
*/
vector<ResultadoAgrupamento>
IntegradorPython::agruparPorPerfil(
    const vector<Peca*>& pecas,
    int quantidadeGrupos
) const {

    if (!Py_IsInitialized()) {
        throw ErroIntegracaoPython();
    }

    PyObject* dadosPython =
        criarListaPecas(pecas);

    if (dadosPython == nullptr) {
        lancarErroIntegracao();
    }

    PyObject* quantidadePython =
        PyLong_FromLong(quantidadeGrupos);

    if (quantidadePython == nullptr) {

        Py_DECREF(dadosPython);

        lancarErroIntegracao();
    }

    PyObject* modulo = importarModuloAnalises();

    if (modulo == nullptr) {

        Py_DECREF(quantidadePython);
        Py_DECREF(dadosPython);

        lancarErroIntegracao();
    }

    PyObject* funcao = obterFuncao(
        modulo,
        "agrupar_por_perfil"
    );

    if (funcao == nullptr) {

        Py_DECREF(modulo);
        Py_DECREF(quantidadePython);
        Py_DECREF(dadosPython);

        lancarErroIntegracao();
    }

    /*
        Equivale em Python a:

        analises.agrupar_por_perfil(
            dadosPython,
            quantidadePython
        )
    */
    PyObject* retorno = PyObject_CallFunctionObjArgs(
        funcao,
        dadosPython,
        quantidadePython,
        nullptr
    );

    Py_DECREF(funcao);
    Py_DECREF(modulo);
    Py_DECREF(quantidadePython);
    Py_DECREF(dadosPython);

    if (retorno == nullptr) {
        lancarErroIntegracao();
    }

    vector<ResultadoAgrupamento> resultados;

    try {

        resultados =
            converterResultadoAgrupamento(retorno);
    }
    catch (...) {

        Py_DECREF(retorno);

        throw;
    }

    Py_DECREF(retorno);

    return resultados;
}