#ifndef VEICULONAOENCONTRADO_H
#define VEICULONAOENCONTRADO_H

#include <exception>

using namespace std;

// Excecao usada quando uma placa nao e encontrada na frota.
class VeiculoNaoEncontrado : public exception {

public:
    // Retorna a mensagem associada ao erro.
    const char* what() const throw() {
        return "Erro: veiculo nao encontrado no sistema.";
    }
};

#endif