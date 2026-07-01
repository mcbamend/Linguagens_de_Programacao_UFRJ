#ifndef MENU_H
#define MENU_H

#include "Frota.h"

class Menu {

public:
    Menu();

    // Mostra o menu, le e retorna a opcao escolhida.
    int lerOpcao();

    // Executa a acao correspondente a opcao.
    void executarOpcao(int opcao);

    // Aguarda o usuario e prepara a proxima tela.
    void pausarELimpar();

private:
    Frota frota;

    void mostrarMenu();

    void inserirVeiculo();
    void buscarVeiculo();
    void imprimirFrota();
    void atualizarQuilometragem();
    void calcularCustoMedio();

    void limparTela();
    void esperarEnter();
};

#endif