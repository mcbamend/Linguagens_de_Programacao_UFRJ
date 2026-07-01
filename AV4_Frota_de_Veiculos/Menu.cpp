#include <iostream>
#include <string>

#include "Menu.h"
#include "Carro.h"
#include "Caminhao.h"
#include "Moto.h"

using namespace std;

Menu::Menu() {
    limparTela();
}


// Mostra as opcoes principais.
void Menu::mostrarMenu() {

    cout << endl;
    cout << "===== SISTEMA DE GERENCIAMENTO DE FROTA =====" << endl;
    cout << "1 - Inserir veiculo" << endl;
    cout << "2 - Buscar veiculo pela placa" << endl;
    cout << "3 - Imprimir frota" << endl;
    cout << "4 - Atualizar quilometragem" << endl;
    cout << "5 - Calcular custo medio de manutencao" << endl;
    cout << "0 - Sair" << endl;
    cout << "Escolha uma opcao: ";
}


// Le a opcao e devolve o valor para o main.
int Menu::lerOpcao() {

    int opcao;

    mostrarMenu();
    cin >> opcao;

    return opcao;
}


// Direciona cada opcao para seu metodo correspondente.
void Menu::executarOpcao(int opcao) {

    switch (opcao) {

        case 1:
            inserirVeiculo();
            break;

        case 2:
            buscarVeiculo();
            break;

        case 3:
            imprimirFrota();
            break;

        case 4:
            atualizarQuilometragem();
            break;

        case 5:
            calcularCustoMedio();
            break;

        case 0:
            cout << "Encerrando o programa..." << endl;
            break;

        default:
            cout << "Opcao invalida." << endl;
    }
}


// Le os dados e cria o tipo escolhido.
void Menu::inserirVeiculo() {

    int tipo;

    cout << endl;
    cout << "1 - Carro" << endl;
    cout << "2 - Caminhao" << endl;
    cout << "3 - Moto" << endl;
    cout << "Escolha o tipo do veiculo: ";
    cin >> tipo;

    if (tipo < 1 || tipo > 3) {
        cout << "Tipo de veiculo invalido." << endl;
        return;
    }

    string placa;
    string marca;
    double quilometragem;
    double custoManutencao;

    cout << "Placa: ";
    cin >> placa;

    cout << "Marca: ";
    getline(cin >> ws, marca);

    cout << "Quilometragem: ";
    cin >> quilometragem;

    cout << "Custo base de manutencao: ";
    cin >> custoManutencao;

    Veiculo* veiculo = NULL;

    switch (tipo) {

        case 1: {
            int numPortas;

            cout << "Numero de portas: ";
            cin >> numPortas;

            veiculo = new Carro(
                placa,
                marca,
                quilometragem,
                custoManutencao,
                numPortas
            );

            break;
        }

        case 2: {
            double capacidadeCarga;

            cout << "Capacidade de carga em toneladas: ";
            cin >> capacidadeCarga;

            veiculo = new Caminhao(
                placa,
                marca,
                quilometragem,
                custoManutencao,
                capacidadeCarga
            );

            break;
        }

        case 3: {
            int cilindrada;

            cout << "Cilindrada: ";
            cin >> cilindrada;

            veiculo = new Moto(
                placa,
                marca,
                quilometragem,
                custoManutencao,
                cilindrada
            );

            break;
        }
    }

    bool inseriu = frota.insere(veiculo);

    if (inseriu) {
        cout << "Veiculo inserido com sucesso." << endl;
    }
    else {
        cout << "Ja existe um veiculo com essa placa." << endl;
    }
}


// A excecao nao e tratada aqui.
// Caso a placa nao exista, ela chegara ao main.
void Menu::buscarVeiculo() {

    string placa;

    cout << "Digite a placa procurada: ";
    cin >> placa;

    Veiculo* veiculo = frota(placa);

    cout << endl;
    cout << *veiculo;
}


void Menu::imprimirFrota() {
    frota.imprimir();
}


// A excecao tambem segue ate o main.
void Menu::atualizarQuilometragem() {

    string placa;
    double novaQuilometragem;

    cout << "Digite a placa do veiculo: ";
    cin >> placa;

    cout << "Digite a nova quilometragem: ";
    cin >> novaQuilometragem;

    Veiculo* veiculo =
        frota(placa, novaQuilometragem);

    cout << "Quilometragem atualizada com sucesso." << endl;
    cout << endl;
    cout << *veiculo;
}


void Menu::calcularCustoMedio() {
    frota.calculaCustoManutencao();
}


// Pausa o programa e limpa a tela.
void Menu::pausarELimpar() {
    esperarEnter();
    limparTela();
}


void Menu::limparTela() {
    cout << "\033[2J\033[1;1H";
}


void Menu::esperarEnter() {

    cout << endl;
    cout << "Pressione Enter para continuar...";

    cin.ignore(1000, '\n');
    cin.get();
}