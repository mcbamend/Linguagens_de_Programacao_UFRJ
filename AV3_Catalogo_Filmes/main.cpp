#include <iostream>
#include <vector>
#include "Filme.h"
#include "CatalogoFilmes.h"

using namespace std;

int main() {
    CatalogoFilmes catalogo(100, "filmes.txt");
    CatalogoFilmes outroCatalogo(100, "filmes2.txt");

    int opcao;

    do {
        cout << endl;
        cout << "===== MENU - CATALOGO DE FILMES =====" << endl;
        cout << "1 - Inserir filme no catalogo principal" << endl;
        cout << "2 - Remover filme do catalogo principal" << endl;
        cout << "3 - Imprimir catalogo principal ou filme" << endl;
        cout << "4 - Buscar filmes por diretor" << endl;
        cout << "5 - Atualizar nota de um filme" << endl;
        cout << "6 - Inserir filme no segundo catalogo" << endl;
        cout << "7 - Comparar os dois catalogos" << endl;
        cout << "0 - Sair" << endl;
        cout << "Escolha uma opcao: ";
        cin >> opcao;

        if (opcao == 1) {
            Filme filme;

            cin >> filme;
            catalogo = catalogo + filme;
        }

        else if (opcao == 2) {
            Filme filme;

            cout << "Titulo do filme a remover: ";
            getline(cin >> ws, filme.titulo);

            catalogo = catalogo - filme;
        }

        else if (opcao == 3) {
	    int tipoImpressao;

	    cout << endl;
	    cout << "1 - Imprimir catálogo principal completo" << endl;
	    cout << "2 - Imprimir filme pelo nome" << endl;
	    cout << "Escolha uma opção: ";
	    cin >> tipoImpressao;

	    if (tipoImpressao == 1){
		    cout << catalogo;
	    }

	    else if (tipoImpressao == 2){
		    string titulo;
		    Filme filmeEncontrado;

		    cout << "Titulo do filme: ";
		    getline(cin >> ws, titulo);

		    bool encontrou = catalogo.buscarFilmePorTitulo(titulo, filmeEncontrado);

		    if (encontrou){
			    cout << endl;
			    cout << filmeEncontrado;
		    }

		    else {
			    cout << "Filme nao encontrado." << endl;
		    }

	    }

        }

        else if (opcao == 4) {
            string diretor;

            cout << "Nome do diretor: ";
            getline(cin >> ws, diretor);

            vector<Filme> encontrados = catalogo[diretor];

            if (encontrados.size() == 0) {
                cout << "Nenhum filme encontrado para esse diretor." << endl;
            } else {
                cout << endl;
                cout << "Filmes encontrados:" << endl;

                for (int i = 0; i < (int)encontrados.size(); i++) {
                    cout << endl;
                    cout << encontrados[i];
                }
            }
        }

        else if (opcao == 5) {
            string titulo;
            double novaNota;

            cout << "Titulo do filme: ";
            getline(cin >> ws, titulo);

            cout << "Nova nota: ";
            cin >> novaNota;

            bool sucesso = catalogo(titulo, novaNota);

            if (sucesso) {
                cout << "Nota atualizada com sucesso." << endl;
            } else {
                cout << "Filme nao encontrado." << endl;
            }
        }

        else if (opcao == 6) {
            Filme filme;

            cin >> filme;
            outroCatalogo = outroCatalogo + filme;
        }

        else if (opcao == 7) {
            cout << "Catalogo principal: "
                 << catalogo.getQuantidadeFilmes()
                 << " filme(s)." << endl;

            cout << "Segundo catalogo: "
                 << outroCatalogo.getQuantidadeFilmes()
                 << " filme(s)." << endl;

            if (catalogo > outroCatalogo) {
                cout << "O catalogo principal possui mais filmes." << endl;
            } else if (outroCatalogo > catalogo) {
                cout << "O segundo catalogo possui mais filmes." << endl;
            } else {
                cout << "Os dois catalogos possuem a mesma quantidade de filmes." << endl;
            }
        }

        else if (opcao == 0) {
            catalogo.salvarArquivo();
            outroCatalogo.salvarArquivo();

            cout << "Catalogos salvos. Programa encerrado." << endl;
        }

        else {
            cout << "Opcao invalida." << endl;
        }

    } while (opcao != 0);

    return 0;
}
