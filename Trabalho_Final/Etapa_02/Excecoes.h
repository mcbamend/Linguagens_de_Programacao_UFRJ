#ifndef EXCECOES_H
#define EXCECOES_H

#include <exception>

// Excecao lancada quando o ID procurado nao pertence
// a nenhuma peca cadastrada.
class PecaNaoEncontrada : public std::exception {

public:
    const char* what() const noexcept override {
        return "Erro: peca nao encontrada no sistema.";
    }
};


// Excecao lancada quando o usuario fornece um valor invalido.
class EntradaInvalida : public std::exception {

public:
    const char* what() const noexcept override {
        return "Erro: entrada invalida.";
    }
};


// Excecao lancada quando nao existem pecas suficientes
// para realizar uma analise estatistica ou de aprendizado de maquina.
class DadosInsuficientes : public std::exception {

public:
    const char* what() const noexcept override {
        return "Erro: dados insuficientes para realizar a analise.";
    }
};


// Excecao lancada quando ocorre uma falha na comunicacao
// entre o programa em C++ e o modulo externo em Python.
class ErroIntegracaoPython : public std::exception {

public:
    const char* what() const noexcept override {
        return "Erro: falha na integracao com o modulo Python.";
    }
};

// Excecao lancada quando ocorre uma falha ao acessar o arquivo.
class ErroArquivo : public std::exception {

public:
    const char* what() const noexcept override {
        return "Erro: nao foi possivel acessar o arquivo de dados.";
    }
};

#endif