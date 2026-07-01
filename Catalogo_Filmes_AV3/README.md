# Exercício Avaliado 3 - Catálogo de Filmes

Nome: Maria Clara Borges de Albuquerque de Mendonça

## Descrição

Este programa implementa um pequeno sistema de gerenciamento de filmes em C++.

Cada filme é representado por uma struct chamada Filme, contendo título, diretor, ano de lançamento e nota média. O catálogo é representado pela classe CatalogoFilmes, que armazena os filmes em um vector e possui uma capacidade máxima definida no construtor.

O objetivo principal do exercício é usar sobrecarga de operadores para realizar as operações do catálogo.

## Arquivos do projeto

- Filme.h e Filme.cpp: definem a struct Filme e os operadores relacionados a um filme individual.
- CatalogoFilmes.h e CatalogoFilmes.cpp: definem a classe CatalogoFilmes e os operadores usados no catálogo.
- main.cpp: contém o menu de interação com o usuário.
- filmes.txt: arquivo usado para salvar os filmes do catálogo principal.
- filmes2.txt: arquivo usado para o segundo catálogo, utilizado na comparação entre catálogos.
- Makefile: arquivo usado para compilar o projeto.

## Como compilar

No terminal, dentro da pasta do projeto, digite:

make

Isso gera o executável chamado catalogo.

## Como executar

Depois de compilar, execute:

./catalogo

## Como limpar a compilação

Para apagar o executável e os arquivos .o, use:

make clean

## Menu do programa

O programa possui as seguintes opções:

1. Inserir filme no catálogo principal
2. Remover filme do catálogo principal
3. Imprimir catálogo principal
4. Buscar filmes por diretor
5. Atualizar nota de um filme
6. Inserir filme no segundo catálogo
7. Comparar os dois catálogos
0. Sair

Ao escolher a opção 0, os catálogos são salvos nos arquivos de texto.

## Operadores sobrecarregados usados

No arquivo Filme.cpp:

- << imprime um filme individual.
- >> lê os dados de um filme.
- == compara dois filmes pelo título.
- < compara dois filmes para ordenação por diretor e depois por título.

No arquivo CatalogoFilmes.cpp:

- << imprime o catálogo completo.
- + insere um filme no catálogo.
- - remove um filme do catálogo pelo título.
- [] busca filmes pelo nome do diretor.
- () atualiza a nota média de um filme pelo título.
- > compara dois catálogos pela quantidade de filmes.

## Formato dos arquivos de texto

Os filmes são salvos nos arquivos filmes.txt e filmes2.txt no seguinte formato:

titulo;diretor;ano;nota

Exemplo:

Interestelar;Christopher Nolan;2014;9.5

## Observações

O catálogo principal é salvo em filmes.txt.

O segundo catálogo é salvo em filmes2.txt e foi usado para permitir o teste do operador >, que compara dois catálogos pela quantidade de filmes.

Os filmes são inseridos em ordem pelo nome do diretor e, quando o diretor é o mesmo, pelo título do filme.