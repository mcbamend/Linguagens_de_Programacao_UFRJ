#include <iostream>
#include <string>

#include "Grafo.h"

using namespace std;

int main() {
    Grafo grafo;

    string nomeArquivo;
    int opcao;

    cout << "Digite o nome do arquivo de entrada: ";
    cin >> nomeArquivo;

    grafo.carregarArquivo(nomeArquivo);

    do {

        cout << endl;
        cout << "===== SISTEMA DE GRAFOS =====" << endl;
        cout << "1 - Imprimir matriz de adjacencia" << endl;
        cout << "2 - Imprimir graus dos vertices" << endl;
        cout << "3 - Verificar se o grafo e conexo" << endl;
        cout << "4 - Calcular menor caminho entre dois vertices" << endl;
        cout << "5 - Mostrar centralidade de intermediacao" << endl;
        cout << "6 - Mostrar vertices e arestas" << endl;
        cout << "0 - Sair" << endl;
        cout << "Escolha uma opcao: ";
        cin >> opcao;

        if (opcao == 1) {

            grafo.mostrarMatrizAdjacencia();
        }

        else if (opcao == 2) {

            grafo.mostrarGraus();
        }

        else if (opcao == 3) {

            grafo.verificarConexo();
        }

        else if (opcao == 4) {

            string origem;
            string destino;

            cout << "Digite o vertice de origem: ";
            cin >> origem;

            cout << "Digite o vertice de destino: ";
            cin >> destino;

            grafo.menorCaminho(origem, destino);
        }

        else if (opcao == 5) {

            grafo.mostrarCentralidadeIntermediacao();
        }

        else if (opcao == 6) {

            grafo.mostrarVertices();
            grafo.mostrarArestas();
        }

        else if (opcao == 0) {

            cout << "Encerrando o programa..." << endl;
        }

        else {

            cout << "Opcao invalida." << endl;
        }

    } while (opcao != 0);

    return 0;
}