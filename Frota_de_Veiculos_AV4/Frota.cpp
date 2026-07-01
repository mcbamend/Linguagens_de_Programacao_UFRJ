#include "Frota.h"

// Insere um veiculo na arvore utilizando o operador +.
bool Frota::insere(Veiculo* veiculo) {

    // A placa nao pode aparecer duas vezes na frota.
    if (busca(veiculo->getPlaca()) != NULL) {
        delete veiculo;
        return false;
    }

    /*
        O operador + da arvore realiza a insercao
        e retorna a propria arvore atualizada.
    */
    arvore = arvore + veiculo;

    return true;
}


// Retorna o ponteiro encontrado ou NULL.
Veiculo* Frota::busca(string placa) const {
    return arvore.buscar(placa);
}


// Sobrecarga usada em frota("placa").
Veiculo* Frota::operator()(string placa) {

    Veiculo* veiculo = busca(placa);

    if (veiculo == NULL) {
        throw VeiculoNaoEncontrado();
    }

    return veiculo;
}


// Sobrecarga usada em frota("placa", novaQuilometragem).
Veiculo* Frota::operator()(string placa, double novaQuilometragem) {

    /*
        Reutiliza o primeiro operator().
        Caso a placa nao exista, a excecao ja sera lancada.
    */
    Veiculo* veiculo = (*this)(placa);

    veiculo->setQuilometragem(novaQuilometragem);

    return veiculo;
}


// Imprime a arvore usando o operador <<.
void Frota::imprimir() const {
    cout << arvore;
}


// Calcula o custo medio para cada tipo de veiculo.
void Frota::calculaCustoManutencao() const {

    vector<Veiculo*> veiculos = arvore.obterElementos();

    double somaCarros = 0.0;
    double somaCaminhoes = 0.0;
    double somaMotos = 0.0;

    int quantidadeCarros = 0;
    int quantidadeCaminhoes = 0;
    int quantidadeMotos = 0;

    for (unsigned i = 0; i < veiculos.size(); i++) {

        string tipo = veiculos[i]->getTipo();

        /*
            O metodo e virtual, portanto cada objeto utiliza
            a implementacao correspondente ao seu tipo real.
        */
        double custo =
            veiculos[i]->calculaCustoManutencao();

        if (tipo == "Carro") {
            somaCarros += custo;
            quantidadeCarros++;
        }

        else if (tipo == "Caminhao") {
            somaCaminhoes += custo;
            quantidadeCaminhoes++;
        }

        else if (tipo == "Moto") {
            somaMotos += custo;
            quantidadeMotos++;
        }
    }

    cout << endl;
    cout << "===== CUSTO MEDIO DE MANUTENCAO =====" << endl;

    if (quantidadeCarros > 0) {
        cout << "Carros: R$ "
             << somaCarros / quantidadeCarros
             << endl;
    }
    else {
        cout << "Carros: nenhum veiculo cadastrado." << endl;
    }

    if (quantidadeCaminhoes > 0) {
        cout << "Caminhoes: R$ "
             << somaCaminhoes / quantidadeCaminhoes
             << endl;
    }
    else {
        cout << "Caminhoes: nenhum veiculo cadastrado." << endl;
    }

    if (quantidadeMotos > 0) {
        cout << "Motos: R$ "
             << somaMotos / quantidadeMotos
             << endl;
    }
    else {
        cout << "Motos: nenhum veiculo cadastrado." << endl;
    }
}