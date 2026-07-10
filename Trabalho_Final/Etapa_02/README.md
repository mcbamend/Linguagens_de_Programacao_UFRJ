# ClosetLog

**Trabalho Final - Etapa 2**  
**Disciplina:** Linguagens de Programação - EEL670  
**Curso:** Engenharia Eletrônica e de Computação - UFRJ  
**Aluna:** Maria Clara Borges de Albuquerque de Mendonça  
**Período:** 2026.1  

---

## 1. Sobre o projeto

O **ClosetLog** é um sistema de gerenciamento de guarda-roupa feito em C++ com integração direta com Python.

A ideia do projeto é cadastrar peças de roupa, calçados e acessórios, registrar seus usos e gerar análises sobre o aproveitamento dessas peças. Em vez de ser apenas um cadastro simples, o sistema tenta responder perguntas como:

- quais peças eu uso mais?
- quais peças estão paradas?
- qual peça tem custo por uso muito alto?
- quais peças parecem subutilizadas?
- quais peças têm perfis de uso parecidos?
- quais peças precisam de manutenção?

O programa foi pensado como uma forma de organizar um guarda-roupa de maneira mais consciente, relacionando dados como preço, quantidade de usos, conforto, versatilidade, dias sem uso e necessidade de manutenção.

---

## 2. Objetivo

O objetivo principal do trabalho foi desenvolver um sistema em C++ que aplicasse conceitos estudados na disciplina de Linguagens de Programação, incluindo, programação orientada a objetos, herança, polimorfismo, templates, sobrecarga de operadores,tratamento de exceções, integração com função externa em outra linguagem, entre outros.
---

## 3. Linguagens e bibliotecas utilizadas

### C++

O C++ é responsável por:

- controlar o menu principal;
- cadastrar, editar, remover e buscar peças;
- organizar os objetos do sistema;
- salvar e carregar os dados em arquivo;
- aplicar os conceitos de orientação a objetos;
- chamar diretamente as funções externas em Python.

### Python

O Python é responsável pelas análises mais específicas:

- detecção de peças subutilizadas;
- agrupamento de peças por perfil de uso.

### Bibliotecas Python utilizadas

- NumPy;
- scikit-learn.

Os algoritmos usados foram:

- **Isolation Forest**, para identificar peças com comportamento incomum de subutilização;
- **K-Means**, para agrupar peças com perfis de uso parecidos.

---

## Funcionalidades

O sistema possui as seguintes opções no menu:

```txt
1 - Cadastrar peca
2 - Registrar uso de uma peca
3 - Listar pecas cadastradas
4 - Buscar, editar ou remover peca
5 - Calcular custo por uso
6 - Analisar pecas subutilizadas
7 - Agrupar pecas por perfil de uso
8 - Listar pecas para manutencao
0 - Sair
```

---

## Tipos de peça

O programa trabalha com três tipos de peça:

- **Roupa**
  - tamanho;
  - categoria da roupa.

- **Calçado**
  - numeração;
  - informação sobre ser impermeável.

- **Acessório**
  - tipo do acessório;
  - nível de fragilidade.

Todos os tipos também possuem dados comuns, como nome, material, preço, quantidade de usos, dias sem uso, conforto médio, versatilidade, manutenção e faixa de temperatura opcional.

---

## Análises em Python

O projeto utiliza Python para duas análises principais:

### Análise de subutilização

Usa o algoritmo **Isolation Forest** para identificar peças com comportamento incomum de subutilização.

A análise considera dados como:

- custo por uso;
- quantidade de usos;
- dias sem uso;
- versatilidade;
- conforto médio;
- necessidade de manutenção.

O resultado mostra uma pontuação de subutilização e indica possíveis motivos para a classificação.

### Agrupamento por perfil de uso

Usa o algoritmo **K-Means** para agrupar peças com perfis de uso parecidos.

O grupo 0 representa, em média, peças com menor aproveitamento. Os grupos seguintes representam perfis com maior aproveitamento médio.

---

## Integração C++ e Python

A comunicação entre C++ e Python foi feita usando a API do Python em C/C++.

O programa não usa `system()` e não utiliza arquivos intermediários para enviar ou receber os dados da análise.

O fluxo geral é:

```txt
Objetos em C++
      ↓
Lista de tuplas Python
      ↓
Funções em analises.py
      ↓
Resultado retornado para C++
      ↓
Exibição no menu
```

---

## Estrutura dos arquivos

```txt
main.cpp                  Arquivo principal
Menu.h / Menu.cpp          Interface de menu
ClosetLog.h / ClosetLog.cpp Classe principal do sistema
Peca.h / Peca.cpp          Classe base abstrata
Roupa.h / Roupa.cpp        Classe derivada para roupas
Calcado.h / Calcado.cpp    Classe derivada para calçados
Acessorio.h / Acessorio.cpp Classe derivada para acessórios
Repositorio.h             Classe template de armazenamento
Excecoes.h                Exceções personalizadas
IntegradorPython.h/.cpp    Integração entre C++ e Python
analises.py               Funções externas em Python
Makefile                  Arquivo de compilação
```

---

## Como compilar e executar

### Requisitos

É necessário ter:

- `g++`;
- `make`;
- Python 3;
- `python3-config`;
- NumPy;
- scikit-learn.

Por exemplo, no MSYS2 UCRT64, os pacotes podem ser instalados com:

```bash
pacman -S --needed make mingw-w64-ucrt-x86_64-gcc mingw-w64-ucrt-x86_64-python mingw-w64-ucrt-x86_64-python-numpy mingw-w64-ucrt-x86_64-python-scikit-learn
```

### Compilação

Na pasta do projeto, execute:

```bash
make clean
make
```

### Execução

Depois da compilação, execute:

```bash
./closetlog
```

---

## Arquivo de dados

As peças cadastradas são salvas automaticamente no arquivo:

```txt
pecas.csv
```

Esse arquivo é gerado pelo próprio programa e permite que os dados continuem disponíveis em execuções futuras.

Para iniciar uma base limpa de testes:

```bash
rm -f pecas.csv
```

---