#ifndef GRAFO_H
#define GRAFO_H

#include <vector>
#include <string>

#include "Vertice.h"
#include "Aresta.h"

using namespace std;

// Classe que representa o grafo completo
class Grafo {

public:

    // Adiciona um vertice ao grafo, se ele ainda nao existir
    void adicionarVertice(string nome);

    // Adiciona uma aresta ponderada entre dois vertices
    void adicionarAresta(string origem, string destino, double peso);

    // Verifica se um vertice ja existe no grafo
    bool existeVertice(string nome);

    // Mostra todos os vertices cadastrados
    void mostrarVertices();

    // Mostra todas as arestas cadastradas
    void mostrarArestas();

    // Carrega Arquivo de entrada
    void carregarArquivo(string nomeArquivo);

    // Mostra a matriz de adjacencia ponderada
    void mostrarMatrizAdjacencia();

    // Mostra o grau de cada vertice
    void mostrarGraus();

    // Verifica se o grafo e conexo
    void verificarConexo();

    // Encontra o menor caminho entre dois vertices usando Dijkstra
    void menorCaminho(string origem, string destino);

    // Mostra vertices em ordem decrescente de centralidade
    void mostrarCentralidadeIntermediacao();

private:

    // Vector com todos os vertices do grafo
    vector<Vertice> vertices;

    // Vector com todas as arestas do grafo
    vector<Aresta> arestas;

    // Busca o indice de um vertice dentro do vetor
    int buscarIndiceVertice(string nome);

    // Funcao auxiliar para a busca em profundidade para percorrer o grafo
    void buscaProfundidade(int indiceAtual, vector<bool> &visitados);

    // Retorna o indice do vertice com a menor distancia ainda nao visitado
    int menorDistancia(vector<double> distancias, vector<bool> visitados);

    // Calcula distancias e predecessores usando Dijkstra
    void calcularDijkstra(int indiceOrigem, vector<double> &distancias, vector< vector<int> > &predecessores);

    // Monta todos os caminhos minimos usando os predecessores
    void montarCaminhos(int atual, int origem, const vector< vector<int> > &predecessores, vector<int> caminhoAtual, vector< vector<int> > &caminhos);
};

#endif