#include <exception>
#include <iostream>

#include "Menu.h"
#include "Excecoes.h"

using namespace std;

int main() {

    try {

        Menu menu;
        int opcao = -1;

        do {

            opcao = menu.lerOpcao();

            try {

                menu.executarOpcao(opcao);
            }
            catch (const PecaNaoEncontrada& erro) {

                cout << endl;
                cout << erro.what() << endl;
            }
            catch (const EntradaInvalida& erro) {

                cout << endl;
                cout << erro.what() << endl;
            }
            catch (const DadosInsuficientes& erro) {

                cout << endl;
                cout << erro.what() << endl;

                cout << "Cadastre ou registre o uso de mais pecas "
                     << "antes de executar esta opcao."
                     << endl;
            }
            catch (const ErroIntegracaoPython& erro) {

                cout << endl;
                cout << erro.what() << endl;

                cout << "Verifique o arquivo analises.py e "
                     << "as bibliotecas Python instaladas."
                     << endl;
            }
            catch (const ErroArquivo& erro) {

                cout << endl;
                cout << erro.what() << endl;
            }
            catch (const exception& erro) {

                cout << endl;
                cout << "Erro inesperado: "
                     << erro.what()
                     << endl;
            }
            catch (...) {

                cout << endl;
                cout << "Ocorreu um erro desconhecido."
                     << endl;
            }

            if (opcao != 0) {
                menu.pausarELimpar();
            }

        } while (opcao != 0);
    }
    catch (const ErroIntegracaoPython& erro) {

        cerr << erro.what() << endl;

        cerr << "Nao foi possivel inicializar o modulo Python."
             << endl;

        return 1;
    }
    catch (const ErroArquivo& erro) {

        cerr << erro.what() << endl;

        return 1;
    }
    catch (const exception& erro) {

        cerr << "Erro durante a inicializacao: "
             << erro.what()
             << endl;

        return 1;
    }
    catch (...) {

        cerr << "Erro desconhecido durante a inicializacao."
             << endl;

        return 1;
    }

    return 0;
}