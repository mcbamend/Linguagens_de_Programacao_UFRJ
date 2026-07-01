#include <iostream>
#include <string>

#include "RegistroValor.h"
#include "Ativo.h"
#include "SistemaFinanceiro.h"

using namespace std;

int main() {

    SistemaFinanceiro sistema;

    int opcao;

    do {

        cout << endl;
	cout << endl;
	cout << endl;

        cout << "~~~~~~ SISTEMA FINANCEIRO ~~~~~~" << endl;

        cout << "1 - Inserir novo ativo" << endl;
        cout << "2 - Inserir novo registro" << endl;
        cout << "3 - Mostrar relatorio" << endl;
        cout << "4 - Mostrar medias moveis" << endl;
        cout << "5 - Ordenar ativos e detectar variacao anormal" << endl;
        cout << "6 - Prever proximo valor" << endl;
        cout << "0 - Sair" << endl;
        cout << endl;

        cout << "Escolha uma opcao: ";
        cin >> opcao;

        if (opcao == 1) {

	    cout << endl;
	    cout << endl;

	    cout << "~~~~~ Inserir novo ativo ~~~~~" << endl;
	    cout << endl;

            string nomeAtivo;

            cout << "Digite o nome do ativo: ";
            cin >> nomeAtivo;

            Ativo novoAtivo(nomeAtivo);

            sistema.adicionarAtivo(novoAtivo);

	    cout << endl;
	    cout << endl;

            sistema.mostrarRelatorio();
        }

        else if (opcao == 2) {
	    
	    cout << endl;
	    cout << endl;
	    cout << "~~~~~ Adicionar novo registro em ativo ~~~~~" << endl;
	    cout << endl;

            string nomeAtivo;
            string indicador;

            double valor;

            cout << "Digite o nome do ativo: ";
            cin >> nomeAtivo;

            cout << "Digite o indicador: ";
            cin >> indicador;

            cout << "Digite o valor: ";
            cin >> valor;

            RegistroValor novoRegistro(indicador, valor);

            sistema.adicionarRegistroEmAtivo(
                nomeAtivo,
                novoRegistro
            );

            sistema.mostrarRelatorio();
        }

        else if (opcao == 3) {

	    cout << endl;
	    cout << endl;

	    sistema.mostrarRelatorio();
        }

        else if (opcao == 4) {

            cout << endl;
	    cout << endl;

	    sistema.mostrarMediasMoveis();
        }

        else if (opcao == 5) {
            
	    cout << endl;
            cout << endl;
	    
	    sistema.ordenarAtivosPorMediaMovel();
	    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
        }

        else if (opcao == 6) {
	
	    cout << endl;
	    cout << endl;

            sistema.preverValores();
	    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
        }

        else if (opcao == 0) {

            cout << "Programa encerrado." << endl;
        }

        else {

            cout << "Opcao invalida." << endl;
        }

    } while (opcao != 0);

    return 0;
}
