# Linguagens de Programação - UFRJ

Repositório criado para armazenar os exercícios avaliados e trabalhos desenvolvidos na disciplina Linguagens de Programação da UFRJ.

Os programas foram desenvolvidos principalmente em C++, utilizando conceitos apresentados durante as aulas, como orientação a objetos, estruturas de dados, sobrecarga de operadores, herança, polimorfismo, templates e tratamento de exceções.

## Organização do repositório

### AV1 - Sistema Financeiro

Implementação de um sistema simples para cadastro e análise de ativos financeiros.

Principais conceitos utilizados:

* Classes e objetos
* Encapsulamento
* Vector
* Busca e ordenação
* Média móvel
* Regressão linear simples
* Makefile

### AV2 - Grafos

Programa para leitura e análise de um grafo não direcionado e ponderado a partir de um arquivo de entrada.

Principais operações:

* Matriz de adjacência
* Cálculo do grau dos vértices
* Verificação de conectividade com busca em profundidade
* Caminho de menor custo com o algoritmo de Dijkstra
* Centralidade de intermediação

### AV3 - Catálogo de Filmes

Sistema para gerenciamento de um catálogo pessoal de filmes.

Principais conceitos utilizados:

* Struct
* Classes
* Vector
* Sobrecarga de operadores
* Inserção ordenada
* Busca e remoção de filmes
* Persistência em arquivo de texto

### AV4 - Frota de Veículos

Sistema para gerenciamento da frota de veículos de uma empresa.

Principais conceitos utilizados:

* Herança
* Polimorfismo
* Métodos virtuais
* Classe template
* Árvore binária
* Ponteiros
* Sobrecarga de operadores
* Tratamento de exceções

### Trabalho Final

Diretório destinado às etapas do trabalho final da disciplina.

O trabalho final desenvolvido foi o **ClosetLog**, um sistema de gerenciamento de guarda-roupa feito em **C++** com integração direta com **Python**.

O sistema permite cadastrar roupas, calçados e acessórios, registrar usos, calcular custo por uso, buscar peças por nome, listar peças que precisam de manutenção e realizar análises sobre o aproveitamento das peças cadastradas.

A primeira etapa contém o planejamento do projeto, incluindo a proposta inicial, a divisão entre o programa gerenciador em C++ e as funções externas em Python, além da descrição das funcionalidades previstas.

A segunda etapa contém a implementação do sistema, utilizando conceitos como:

* Classes e objetos
* Herança
* Polimorfismo
* Métodos virtuais
* Classe template
* Sobrecarga de operadores
* Tratamento de exceções
* Persistência em arquivo
* Busca por nome aproximado
* Integração entre C++ e Python sem uso de `system()`
* Uso de funções externas em Python com NumPy e scikit-learn

As análises em Python incluem:

* Identificação de peças subutilizadas com **Isolation Forest**
* Agrupamento de peças por perfil de uso com **K-Means**
## Compilação

Cada exercício possui seu próprio Makefile e README com as instruções específicas de compilação e execução.

De forma geral, para compilar um programa, é necessário entrar na pasta correspondente e executar:

```
make
```

Depois, executar o programa utilizando o nome do executável indicado no README da atividade.

Para remover o executável e os arquivos gerados durante a compilação:

```
make clean
```

## Autora

Maria Clara Borges de Albuquerque de Mendonça

Engenharia Eletrônica e de Computação - UFRJ
