#include "CatalogoFilmes.h"
#include <fstream>
#include <sstream>
#include <cstdlib>

// Construtor da classe.
// Recebe a capacidade maxima do catalogo e o nome do arquivo usado na persistencia.
CatalogoFilmes::CatalogoFilmes(int capacidade, string arquivo) {
    capacidadeMaxima = capacidade;
    nomeArquivo = arquivo;

    // Sempre que um catalogo e criado, os filmes ja salvos sao carregados.
    carregarArquivo();
}

// Carrega os filmes armazenados no arquivo de texto.
void CatalogoFilmes::carregarArquivo() {
    ifstream arquivo(nomeArquivo.c_str());

    // Se o arquivo nao existir ou nao puder ser aberto, o catalogo comeca vazio.
    if (!arquivo.is_open()) {
        return;
    }

    string linha;

    while (getline(arquivo, linha)) {
        // Ignora linhas vazias.
        if (linha == "") {
            continue;
        }

        Filme filme;
        string anoTexto;
        string notaTexto;

        /*
            O arquivo usa o formato:
            titulo;diretor;ano;nota

            O stringstream permite separar a linha em partes usando ';'.
        */
        stringstream ss(linha);

        getline(ss, filme.titulo, ';');
        getline(ss, filme.diretor, ';');
        getline(ss, anoTexto, ';');
        getline(ss, notaTexto, ';');

        filme.ano = atoi(anoTexto.c_str());
        filme.nota = atof(notaTexto.c_str());

        // So carrega se ainda houver espaco no catalogo.
        if ((int)filmes.size() < capacidadeMaxima) {
            filmes.push_back(filme);
        }
    }

	 // Ordena os filmes que vieram do arquivo
	for (int i = 0; i < (int)filmes.size(); i++){
		for (int j = i + 1; j < (int) filmes.size(); j++){
			if (filmes[j] < filmes[i]){
				Filme auxiliar = filmes [i];
				filmes[i] = filmes[j];
				filmes[j] = auxiliar;
		       	}
		}
	}	
	arquivo.close();
}

// Salva todos os filmes do catalogo no arquivo de texto.
void CatalogoFilmes::salvarArquivo() {
    ofstream arquivo(nomeArquivo.c_str());

    if (!arquivo.is_open()) {
        cout << "Erro ao abrir o arquivo para salvar." << endl;
        return;
    }

    /*
        O arquivo e reescrito por completo para refletir o estado atual
        do catalogo no momento do encerramento do programa.
    */
    for (int i = 0; i < (int)filmes.size(); i++) {
        arquivo << filmes[i].titulo << ";"
                << filmes[i].diretor << ";"
                << filmes[i].ano << ";"
                << filmes[i].nota << endl;
    }

    arquivo.close();
}

// Retorna a quantidade atual de filmes cadastrados.
int CatalogoFilmes::getQuantidadeFilmes() const {
    return filmes.size();
}

// Insercao de filme com o operador +.
CatalogoFilmes CatalogoFilmes::operator+(const Filme& filme) {
    // Verifica se ainda existe espaco no catalogo.
    if ((int)filmes.size() >= capacidadeMaxima) {
        cout << "Catalogo cheio. Filme nao inserido." << endl;
        return *this;
    }

    // Nao permite inserir filmes com titulo repetido.
    for (int i = 0; i < (int)filmes.size(); i++) {
        if (filmes[i] == filme) {
            cout << "Ja existe um filme com esse titulo no catalogo." << endl;
            return *this;
        }
    }

    /*
        Insere o filme na posicao correta, mantendo a ordenacao.
        O operador < de Filme define a ordem: diretor e depois titulo.
    */
    int posicao = 0;

    while (posicao < (int)filmes.size() && filmes[posicao] < filme) {
        posicao++;
    }

    filmes.insert(filmes.begin() + posicao, filme);

    cout << "Filme inserido com sucesso." << endl;

    return *this;
}

// Remocao de filme com o operador -.
CatalogoFilmes CatalogoFilmes::operator-(const Filme& filme) {
    /*
        A remocao e feita pelo titulo.
        Por isso, basta comparar usando o operador == de Filme.
    */
    for (int i = 0; i < (int)filmes.size(); i++) {
        if (filmes[i] == filme) {
            filmes.erase(filmes.begin() + i);
            cout << "Filme removido com sucesso." << endl;
            return *this;
        }
    }

    cout << "Filme nao encontrado." << endl;
    return *this;
}

// Busca de filmes por diretor com o operador [].
vector<Filme> CatalogoFilmes::operator[](string diretor) {
    vector<Filme> encontrados;

    for (int i = 0; i < (int)filmes.size(); i++) {
        if (filmes[i].diretor == diretor) {
            encontrados.push_back(filmes[i]);
        }
    }

    return encontrados;
}

// Atualizacao da nota de um filme com o operador ().
bool CatalogoFilmes::operator()(string titulo, double novaNota) {
    for (int i = 0; i < (int)filmes.size(); i++) {
        if (filmes[i].titulo == titulo) {
            filmes[i].nota = novaNota;
            return true;
        }
    }

    return false;
}

// Comparacao entre catalogos pelo numero de filmes.
bool CatalogoFilmes::operator>(const CatalogoFilmes& outroCatalogo) const {
    return filmes.size() > outroCatalogo.filmes.size();
}

bool CatalogoFilmes::buscarFilmePorTitulo(string titulo, Filme &filmeEncontrado){
    for (int i = 0; i < (int)filmes.size(); i++){
	 if (filmes[i].titulo == titulo){
	     filmeEncontrado = filmes[i];
             return true;
       	}
    }

    return false;
}

// Impressao do catalogo completo com cout << catalogo.
ostream& operator<<(ostream& out, const CatalogoFilmes& catalogo) {
    if (catalogo.filmes.size() == 0) {
        out << "Catalogo vazio." << endl;
        return out;
    }

    out << "===== Catalogo de Filmes =====" << endl;

    for (int i = 0; i < (int)catalogo.filmes.size(); i++) {
        out << endl;
        out << "Filme " << i + 1 << endl;
        out << catalogo.filmes[i];
    }

    return out;
}
