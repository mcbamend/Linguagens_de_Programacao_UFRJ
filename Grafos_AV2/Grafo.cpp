#include <iostream>
#include <limits>
#include <fstream>
#include <iomanip>
#include <string>

#include "Grafo.h"

using namespace std;

// Verifica se um vertice ja foi cadastrado
bool Grafo::existeVertice(string nome) {

    for (unsigned i = 0; i < vertices.size(); i++) {

        if (vertices[i].getNome() == nome) {

            return true;
        }
    }

    return false;
}

// Adiciona um novo vertice, evitando repeticao
void Grafo::adicionarVertice(string nome) {

    if (existeVertice(nome) == false) {

        Vertice novoVertice(nome);

        vertices.push_back(novoVertice);
    }
}

// Adiciona uma aresta ao grafo
void Grafo::adicionarAresta(string origem, string destino, double peso) {

    // Garante que os vertices da aresta existam no grafo
    adicionarVertice(origem);
    adicionarVertice(destino);

    // Cria e armazena a aresta
    Aresta novaAresta(origem, destino, peso);

    arestas.push_back(novaAresta);
}

// Mostra os vertices armazenados
void Grafo::mostrarVertices() {

    cout << endl;
    cout << "Vertices do grafo:" << endl;

    for (unsigned i = 0; i < vertices.size(); i++) {

        cout << vertices[i].getNome() << endl;
    }
}

// Mostra as arestas armazenadas
void Grafo::mostrarArestas() {

    cout << endl;
    cout << "Arestas do grafo:" << endl;

    for (unsigned i = 0; i < arestas.size(); i++) {

        cout << arestas[i].getOrigem() << " -- " << arestas[i].getDestino() << " | peso: " << arestas[i].getPeso() << endl;
    }
}

// Le o arquivo de entrada e adiciona as arestas ao grafo
void Grafo::carregarArquivo(string nomeArquivo) {

    ifstream arquivo(nomeArquivo.c_str());

    string origem;
    string destino;
    double peso;

    // Verifica se o arquivo foi aberto corretamente
    if (!arquivo) {

        cout << "Erro ao abrir o arquivo." << endl;

        return;
    }

    // Le cada linha no formato: origem destino peso
    while (arquivo >> origem >> destino >> peso) {

        adicionarAresta(origem, destino, peso);
    }

    arquivo.close();

    cout << "Arquivo carregado com sucesso!" << endl;
}

// Busca o indice de um vertice pelo nome
int Grafo::buscarIndiceVertice(string nome) {

    // Percorre todos os vertices cadastrados
    for (unsigned i = 0; i < vertices.size(); i++) {

        // Compara o nome do vertice atual com o nome procurado
        if (vertices[i].getNome() == nome) {

            return i;
        }
    }

    // Retorna -1 caso o vertice nao seja encontrado
    return -1;
}

// Mostra a matriz de adjacencia ponderada do grafo
void Grafo::mostrarMatrizAdjacencia() {

    unsigned quantidadeVertices = vertices.size();

    // Cria uma matriz quadrada inicializada com zero
    vector< vector<double> > matriz(quantidadeVertices, vector<double>(quantidadeVertices, 0));

    // Percorre todas as arestas para preencher a matriz
    for (unsigned i = 0; i < arestas.size(); i++) {

        int indiceOrigem = buscarIndiceVertice(arestas[i].getOrigem());

        int indiceDestino = buscarIndiceVertice(arestas[i].getDestino());

        double peso = arestas[i].getPeso();

        // Como o grafo e nao direcionado, preenche os dois sentidos
        if (indiceOrigem != -1 && indiceDestino != -1) {

            matriz[indiceOrigem][indiceDestino] = peso;

            matriz[indiceDestino][indiceOrigem] = peso;
        }
    }

    cout << endl;
    cout << "Matriz de adjacencia:" << endl;
    cout << endl;

    // Cabecalho com os nomes dos vertices
    cout << setw(12) << "";

    for (unsigned i = 0; i < quantidadeVertices; i++) {

        cout << setw(12) << vertices[i].getNome();
    }

    cout << endl;

    // Impressao das linhas da matriz
    for (unsigned i = 0; i < quantidadeVertices; i++) {

        cout << setw(12) << vertices[i].getNome();

        for (unsigned j = 0; j < quantidadeVertices; j++) {

            cout << setw(12) << matriz[i][j];
        }

        cout << endl;
    }
}

// Mostra o grau de todos os vertices do grafo
void Grafo::mostrarGraus() {

    cout << endl;
    cout << "Graus dos vertices:" << endl;
    cout << endl;

    // Percorre todos os vertices
    for (unsigned i = 0; i < vertices.size(); i++) {

        int grau = 0;

        // Percorre todas as arestas
        for (unsigned j = 0; j < arestas.size(); j++) {

            // Como o grafo e nao direcionado, conta origem ou destino
            if (arestas[j].getOrigem() == vertices[i].getNome() ||
                arestas[j].getDestino() == vertices[i].getNome()) {

                grau++;
            }
        }

        cout << vertices[i].getNome()
             << " | grau: "
             << grau
             << endl;
    }
}

// Percorre o grafo a partir de um vertice
void Grafo::buscaProfundidade(int indiceAtual, vector<bool> &visitados) {

    // Marca o vertice atual como visitado
    visitados[indiceAtual] = true;

    string nomeAtual =
    vertices[indiceAtual].getNome();

    // Percorre todas as arestas para encontrar vizinhos
    for (unsigned i = 0; i < arestas.size(); i++) {

        string origem =
        arestas[i].getOrigem();

        string destino =
        arestas[i].getDestino();

        int indiceVizinho = -1;

        // Como o grafo e nao direcionado, verifica os dois lados da aresta
        if (origem == nomeAtual) {

            indiceVizinho =
            buscarIndiceVertice(destino);
        }

        else if (destino == nomeAtual) {

            indiceVizinho =
            buscarIndiceVertice(origem);
        }

        // Se encontrou um vizinho ainda nao visitado, continua a busca
        if (indiceVizinho != -1 &&
            visitados[indiceVizinho] == false) {

            buscaProfundidade(indiceVizinho, visitados);
        }
    }
}

// Verifica se todos os vertices podem ser alcancados
void Grafo::verificarConexo() {

    // Grafo vazio nao possui conexao a ser verificada
    if (vertices.size() == 0) {

        cout << endl;
        cout << "Grafo vazio." << endl;

        return;
    }

    // Vector que indica se cada vertice foi visitado
    vector<bool> visitados(vertices.size(), false);

    // Comeca a busca pelo primeiro vertice
    buscaProfundidade(0, visitados);

    // Verifica se algum vertice ficou sem ser visitado
    for (unsigned i = 0; i < visitados.size(); i++) {

        if (visitados[i] == false) {

            cout << endl;
            cout << "O grafo NAO e conexo." << endl;

            return;
        }
    }

    cout << endl;
    cout << "O grafo e conexo." << endl;
}

// Encontra o vertice nao visitado com menor distancia atual
int Grafo::menorDistancia(vector<double> distancias, vector<bool> visitados) {

    double menor = numeric_limits<double>::max();

    int indiceMenor = -1;

    for (unsigned i = 0; i < distancias.size(); i++) {

        if (visitados[i] == false && distancias[i] < menor) {

            menor = distancias[i];

            indiceMenor = i;
        }
    }

    return indiceMenor;
}

// Calcula o menor caminho entre dois vertices usando Dijkstra
void Grafo::menorCaminho(string origem, string destino) {

    int indiceOrigem = buscarIndiceVertice(origem);

    int indiceDestino = buscarIndiceVertice(destino);

    if (indiceOrigem == -1 || indiceDestino == -1) {

        cout << "\nOrigem ou destino nao encontrados." << endl;

        return;
    }

    int quantidadeVertices = vertices.size();

    vector<double> distancias(quantidadeVertices, numeric_limits<double>::max());

    vector<bool> visitados(quantidadeVertices, false);

    vector<int> anteriores(quantidadeVertices, );

    // A distancia da origem para ela mesma e zero
    distancias[indiceOrigem] = 0.0;

    for (int i = 0; i < quantidadeVertices; i++) {

        int atual = menorDistancia(distancias, visitados);

        if (atual == -1) {
            break;
        }

        visitados[atual] = true;

        string nomeAtual = vertices[atual].getNome();

        // Percorre as arestas para encontrar vizinhos do vertice atual
        for (unsigned j = 0; j < arestas.size(); j++) {

            string origemAresta = arestas[j].getOrigem();

            string destinoAresta = arestas[j].getDestino();

            double peso = arestas[j].getPeso();

            int indiceVizinho = -1;

            // Como o grafo e nao direcionado, verifica os dois sentidos
            if (origemAresta == nomeAtual) {

                indiceVizinho = buscarIndiceVertice(destinoAresta);
            }

            else if (destinoAresta == nomeAtual) {

                indiceVizinho = buscarIndiceVertice(origemAresta);
            }

            if (indiceVizinho != -1 && visitados[indiceVizinho] == false) {

                double novaDistancia = distancias[atual] + peso;

                if (novaDistancia < distancias[indiceVizinho]) {

                    distancias[indiceVizinho] = novaDistancia;

                    anteriores[indiceVizinho] = atual;
                }
            }
        }
    }

    cout << "\nMenor caminho de " << origem << " ate " << destino << ":" << endl;

    if (distancias[indiceDestino] == numeric_limits<double>::max()) {

        cout << "Nao existe caminho." << endl;

        return;
    }

    cout << "Distancia total: " << distancias[indiceDestino] << endl;

    // Reconstrucao do caminho
    vector<int> caminho;

    int atual = indiceDestino;

    while (atual != -1) {

        caminho.push_back(atual);
        atual = anteriores[atual];
    }

    cout << "Caminho: ";

    for (int i = caminho.size() - 1; i >= 0; i--) {

        cout << vertices[caminho[i]].getNome();

        if (i != 0) {
            cout << " -> ";
        }
    }

    cout << endl;
}

// Calcula distancias e predecessores a partir de uma origem
void Grafo::calcularDijkstra(int indiceOrigem, vector<double> &distancias, vector< vector<int> > &predecessores) {

    int quantidadeVertices = vertices.size();

    vector<bool> visitados(quantidadeVertices, false);

    for (int i = 0; i < quantidadeVertices; i++) {

        distancias[i] = numeric_limits<double>::max();

        predecessores[i].clear();
    }

    // A distancia da origem para ela mesma e zero
    distancias[indiceOrigem] = 0;

    for (int i = 0; i < quantidadeVertices; i++) {

        int atual = menorDistancia(distancias, visitados);

        if (atual == -1) {
            break;
        }

        visitados[atual] = true;

        string nomeAtual = vertices[atual].getNome();

        // Percorre todas as arestas procurando vizinhos
        for (unsigned j = 0; j < arestas.size(); j++) {

            string origemAresta = arestas[j].getOrigem();

            string destinoAresta = arestas[j].getDestino();

            double peso = arestas[j].getPeso();

            int indiceVizinho = -1;

            // Como o grafo e nao direcionado, verifica os dois sentidos
            if (origemAresta == nomeAtual) {
                indiceVizinho = buscarIndiceVertice(destinoAresta);
            }

            else if (destinoAresta == nomeAtual) {
                indiceVizinho = buscarIndiceVertice(origemAresta);
            }

            if (indiceVizinho != -1 && visitados[indiceVizinho] == false) {

                double novaDistancia = distancias[atual] + peso;

                // Encontrou caminho menor
                if (novaDistancia < distancias[indiceVizinho]) {

                    distancias[indiceVizinho] = novaDistancia;

                    predecessores[indiceVizinho].clear();

                    predecessores[indiceVizinho].push_back(atual);
                }

                // Encontrou outro caminho com mesmo custo
                else if (novaDistancia == distancias[indiceVizinho]) {

                    predecessores[indiceVizinho].push_back(atual);
                }
            }
        }
    }
}

// Monta todos os caminhos minimos entre origem e atual
void Grafo::montarCaminhos(int atual, int origem, const vector< vector<int> > &predecessores, vector<int> caminhoAtual, vector< vector<int> > &caminhos) {

    // Insere o vertice atual no caminho
    caminhoAtual.push_back(atual);

    // Se chegou na origem, o caminho esta completo
    if (atual == origem) {

        caminhos.push_back(caminhoAtual);

        return;
    }

    // Continua voltando pelos predecessores
    for (unsigned i = 0; i < predecessores[atual].size(); i++) {

        montarCaminhos(predecessores[atual][i], origem, predecessores, caminhoAtual, caminhos);
    }
}

// Calcula e mostra a centralidade de intermediacao
void Grafo::mostrarCentralidadeIntermediacao() {

    int quantidadeVertices = vertices.size();

    vector<double> centralidade(quantidadeVertices, 0);

    // Para cada par de vertices s e t
    for (int s = 0; s < quantidadeVertices; s++) {

        vector<double> distancias(quantidadeVertices, numeric_limits<double>::max());

        vector< vector<int> > predecessores(quantidadeVertices);

        calcularDijkstra(s, distancias, predecessores);

        for (int t = 0; t < quantidadeVertices; t++) {

            if (s != t && distancias[t] != numeric_limits<double>::max()) {

                vector< vector<int> > caminhos;

                vector<int> caminhoAtual;

                montarCaminhos(t, s, predecessores, caminhoAtual, caminhos);

                double totalCaminhos = caminhos.size();

                // Analisa todos os vertices v
                for (int v = 0; v < quantidadeVertices; v++) {

                    if (v != s && v != t) {

                        double caminhosComV = 0;

                        // Verifica em quantos caminhos v aparece
                        for (unsigned c = 0; c < caminhos.size(); c++) {

                            bool passouPeloVertice = false;

                            for (unsigned p = 0; p < caminhos[c].size(); p++) {

                                if (caminhos[c][p] == v) {
                                    passouPeloVertice = true;
                                }
                            }

                            if (passouPeloVertice == true) {
                                caminhosComV++;
                            }
                        }

                        if (totalCaminhos > 0) {
                            centralidade[v] = centralidade[v] + (caminhosComV / totalCaminhos);
                        }
                    }
                }
            }
        }
    }

    // Ordena os vertices por centralidade decrescente
    for (int i = 0; i < quantidadeVertices; i++) {

        for (int j = i + 1; j < quantidadeVertices; j++) {

            if (centralidade[j] > centralidade[i]) {

                double centralidadeAuxiliar = centralidade[i];

                centralidade[i] = centralidade[j];

                centralidade[j] = centralidadeAuxiliar;

                Vertice verticeAuxiliar = vertices[i];

                vertices[i] = vertices[j];

                vertices[j] = verticeAuxiliar;
            }
        }
    }

    cout << endl;
    cout << "Centralidade de intermediacao:" << endl;
    cout << endl;

    for (int i = 0; i < quantidadeVertices; i++) {

        cout << vertices[i].getNome() << " | centralidade: " << centralidade[i] << endl;
    }
}