#include "Filme.h"

// Sobrecarga do operador de saida para permitir: cout << filme
ostream& operator<<(ostream& out, const Filme& filme) {
    // Os campos sao exibidos em linhas separadas para facilitar a leitura.
    out << "Titulo: " << filme.titulo << endl;
    out << "Diretor: " << filme.diretor << endl;
    out << "Ano: " << filme.ano << endl;
    out << "Nota media: " << filme.nota << endl;

    // Retorna o fluxo para manter o comportamento padrao do operador <<.
    return out;
}

// Sobrecarga do operador de entrada para permitir: cin >> filme
istream& operator>>(istream& in, Filme& filme) {
    cout << "Titulo: ";

    // getline permite ler titulos compostos, com espacos.
    // O ws remove quebras de linha ou espacos que possam ter ficado no buffer.
    getline(in >> ws, filme.titulo);

    cout << "Diretor: ";

    // O nome do diretor tambem pode ter espacos, por isso usa getline.
    getline(in, filme.diretor);

    cout << "Ano de lancamento: ";
    in >> filme.ano;

    cout << "Nota media (0.0 a 10.0): ";
    in >> filme.nota;

    // Retorna o fluxo para permitir o mesmo padrao de uso do cin.
    return in;
}

// Dois filmes sao considerados iguais quando possuem o mesmo titulo.
bool operator==(const Filme& f1, const Filme& f2) {
    return f1.titulo == f2.titulo;
}

// Define a ordem usada para inserir os filmes no catalogo.
bool operator<(const Filme& f1, const Filme& f2) {
    // Primeiro criterio: ordem alfabetica pelo nome do diretor.
    if (f1.diretor < f2.diretor) {
        return true;
    }

    // Segundo criterio: se o diretor for o mesmo, ordena pelo titulo.
    if (f1.diretor == f2.diretor && f1.titulo < f2.titulo) {
        return true;
    }

    // Nos demais casos, f1 nao deve vir antes de f2.
    return false;
}