#include <iostream>

#include "Menu.h"
#include "VeiculoNaoEncontrado.h"

using namespace std;

int main() {

    Menu menu;
    int opcao;

    do {

        opcao = menu.lerOpcao();

        try {
            menu.executarOpcao(opcao);
        }

        catch (const VeiculoNaoEncontrado& erro) {
            cout << erro.what() << endl;
        }

        if (opcao != 0) {
            menu.pausarELimpar();
        }

    } while (opcao != 0);

    return 0;
}