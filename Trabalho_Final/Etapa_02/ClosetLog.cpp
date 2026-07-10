#include "ClosetLog.h"

#include <algorithm>
#include <cctype>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

/*
    Separa uma linha usando ponto e virgula.

    Exemplo:
    Roupa;1;Camisa;Linho

    Resultado:
    campos[0] = Roupa
    campos[1] = 1
    campos[2] = Camisa
    campos[3] = Linho
*/
static vector<string> separarCampos(const string& linha) {

    vector<string> campos;
    string campo;
    stringstream fluxo(linha);

    while (getline(fluxo, campo, ';')) {
        campos.push_back(campo);
    }

    return campos;
}


// Verifica se uma string esta vazia ou possui ponto e virgula.
static bool textoInvalido(const string& texto) {

    if (texto.empty()) {
        return true;
    }

    return texto.find(';') != string::npos;
}


// Substitui todas as ocorrencias de um trecho por outro.
static void substituirTodas(string& texto,
                            const string& antigo,
                            const string& novo) {

    size_t posicao = 0;

    while ((posicao = texto.find(antigo, posicao)) != string::npos) {

        texto.replace(posicao, antigo.size(), novo);

        posicao += novo.size();
    }
}


// Normaliza um texto para facilitar a busca por nome.
// Exemplo: "Calça Paloma" vira "calca paloma".
static string normalizarTexto(string texto) {

    substituirTodas(texto, "á", "a");
    substituirTodas(texto, "à", "a");
    substituirTodas(texto, "â", "a");
    substituirTodas(texto, "ã", "a");
    substituirTodas(texto, "ä", "a");

    substituirTodas(texto, "Á", "a");
    substituirTodas(texto, "À", "a");
    substituirTodas(texto, "Â", "a");
    substituirTodas(texto, "Ã", "a");
    substituirTodas(texto, "Ä", "a");

    substituirTodas(texto, "é", "e");
    substituirTodas(texto, "è", "e");
    substituirTodas(texto, "ê", "e");
    substituirTodas(texto, "ë", "e");

    substituirTodas(texto, "É", "e");
    substituirTodas(texto, "È", "e");
    substituirTodas(texto, "Ê", "e");
    substituirTodas(texto, "Ë", "e");

    substituirTodas(texto, "í", "i");
    substituirTodas(texto, "ì", "i");
    substituirTodas(texto, "î", "i");
    substituirTodas(texto, "ï", "i");

    substituirTodas(texto, "Í", "i");
    substituirTodas(texto, "Ì", "i");
    substituirTodas(texto, "Î", "i");
    substituirTodas(texto, "Ï", "i");

    substituirTodas(texto, "ó", "o");
    substituirTodas(texto, "ò", "o");
    substituirTodas(texto, "ô", "o");
    substituirTodas(texto, "õ", "o");
    substituirTodas(texto, "ö", "o");

    substituirTodas(texto, "Ó", "o");
    substituirTodas(texto, "Ò", "o");
    substituirTodas(texto, "Ô", "o");
    substituirTodas(texto, "Õ", "o");
    substituirTodas(texto, "Ö", "o");

    substituirTodas(texto, "ú", "u");
    substituirTodas(texto, "ù", "u");
    substituirTodas(texto, "û", "u");
    substituirTodas(texto, "ü", "u");

    substituirTodas(texto, "Ú", "u");
    substituirTodas(texto, "Ù", "u");
    substituirTodas(texto, "Û", "u");
    substituirTodas(texto, "Ü", "u");

    substituirTodas(texto, "ç", "c");
    substituirTodas(texto, "Ç", "c");

    string resultado;
    bool ultimoFoiEspaco = true;

    for (unsigned int i = 0; i < texto.size(); i++) {

        unsigned char caractere =
            static_cast<unsigned char>(texto[i]);

        if (isalnum(caractere)) {

            resultado += static_cast<char>(
                tolower(caractere)
            );

            ultimoFoiEspaco = false;
        }
        else {

            if (!ultimoFoiEspaco) {
                resultado += ' ';
                ultimoFoiEspaco = true;
            }
        }
    }

    if (!resultado.empty() &&
        resultado[resultado.size() - 1] == ' ') {

        resultado.erase(resultado.size() - 1);
    }

    return resultado;
}


// Calcula uma distancia simples entre duas strings.
// Quanto menor a distancia, mais parecidos sao os textos.
static int distanciaEdicao(const string& a,
                           const string& b) {

    vector<int> anterior(b.size() + 1);
    vector<int> atual(b.size() + 1);

    for (unsigned int j = 0; j <= b.size(); j++) {
        anterior[j] = static_cast<int>(j);
    }

    for (unsigned int i = 1; i <= a.size(); i++) {

        atual[0] = static_cast<int>(i);

        for (unsigned int j = 1; j <= b.size(); j++) {

            int custo = 0;

            if (a[i - 1] != b[j - 1]) {
                custo = 1;
            }

            int remover = anterior[j] + 1;
            int inserir = atual[j - 1] + 1;
            int substituir = anterior[j - 1] + custo;

            atual[j] = min(
                min(remover, inserir),
                substituir
            );
        }

        anterior = atual;
    }

    return anterior[b.size()];
}


// Atribui uma pontuacao para a semelhanca entre o nome
// da peca e o termo digitado pelo usuario.
static int pontuarNome(const string& nomeNormalizado,
                       const string& termoNormalizado) {

    if (termoNormalizado.empty()) {
        return -1;
    }

    if (nomeNormalizado == termoNormalizado) {
        return 1000;
    }

    if (nomeNormalizado.find(termoNormalizado) != string::npos) {
        return 900;
    }

    stringstream fluxo(termoNormalizado);
    string palavra;

    int totalPalavras = 0;
    int palavrasEncontradas = 0;

    while (fluxo >> palavra) {

        totalPalavras++;

        if (nomeNormalizado.find(palavra) != string::npos) {
            palavrasEncontradas++;
        }
    }

    if (palavrasEncontradas > 0) {

        return 600
               + 50 * palavrasEncontradas
               - 20 * (totalPalavras - palavrasEncontradas);
    }

    int maiorTamanho = static_cast<int>(
        max(nomeNormalizado.size(), termoNormalizado.size())
    );

    if (maiorTamanho == 0) {
        return -1;
    }

    int distancia = distanciaEdicao(
        nomeNormalizado,
        termoNormalizado
    );

    double similaridade =
        1.0 - static_cast<double>(distancia) / maiorTamanho;

    if (similaridade >= 0.45) {
        return static_cast<int>(similaridade * 500.0);
    }

    return -1;
}


// Inicializa o sistema e carrega os dados ja existentes.
ClosetLog::ClosetLog(string nomeArquivo) {

    this->nomeArquivo = nomeArquivo;
    proximoId = 1;

    carregarDados();
}


// Gera um identificador e prepara o proximo.
int ClosetLog::gerarId() {

    int idGerado = proximoId;

    proximoId++;

    return idGerado;
}


// Valida os atributos comuns a todos os tipos de peca.
void ClosetLog::validarDadosComuns(double preco,
                                    int versatilidade,
                                    double confortoMedio) const {

    if (preco < 0) {
        throw EntradaInvalida();
    }

    if (versatilidade < 1 || versatilidade > 10) {
        throw EntradaInvalida();
    }

    validarConforto(confortoMedio);
}


// Valida a faixa de temperatura quando ela for informada.
void ClosetLog::validarTemperatura(bool temperaturaInformada,
                                    double temperaturaMinima,
                                    double temperaturaMaxima) const {

    if (!temperaturaInformada) {
        return;
    }

    if (temperaturaMinima > temperaturaMaxima) {
        throw EntradaInvalida();
    }
}


// Valida os dados de historico inicial.
void ClosetLog::validarHistorico(int quantidadeUsos,
                                  int diasSemUso,
                                  double confortoMedio) const {

    if (quantidadeUsos < 0) {
        throw EntradaInvalida();
    }

    if (diasSemUso < 0) {
        throw EntradaInvalida();
    }

    validarConforto(confortoMedio);
}


// Valida uma nota de conforto.
void ClosetLog::validarConforto(double conforto) const {

    if (conforto < 1.0 || conforto > 10.0) {
        throw EntradaInvalida();
    }
}


// Busca uma peca e lanca excecao quando o ID nao existe.
Peca* ClosetLog::buscarOuLancar(int id) const {

    Peca* peca = repositorio[id];

    if (peca == nullptr) {
        throw PecaNaoEncontrada();
    }

    return peca;
}


// Cadastra uma nova roupa.
int ClosetLog::cadastrarRoupa(
    string nome,
    string material,
    double preco,
    int versatilidade,
    double temperaturaMinima,
    double temperaturaMaxima,
    double confortoMedio,
    bool precisaManutencao,
    int quantidadeUsos,
    int diasSemUso,
    bool temperaturaInformada,
    string tamanho,
    string categoriaRoupa
) {

    validarDadosComuns(
        preco,
        versatilidade,
        confortoMedio
    );

    validarHistorico(
        quantidadeUsos,
        diasSemUso,
        confortoMedio
    );

    validarTemperatura(
        temperaturaInformada,
        temperaturaMinima,
        temperaturaMaxima
    );

    if (textoInvalido(nome) ||
        textoInvalido(material) ||
        textoInvalido(tamanho) ||
        textoInvalido(categoriaRoupa)) {

        throw EntradaInvalida();
    }

    if (!temperaturaInformada) {
        temperaturaMinima = 0.0;
        temperaturaMaxima = 0.0;
    }

    int id = gerarId();

    Peca* novaPeca = new Roupa(
        id,
        nome,
        material,
        preco,
        versatilidade,
        temperaturaMinima,
        temperaturaMaxima,
        confortoMedio,
        precisaManutencao,
        quantidadeUsos,
        diasSemUso,
        temperaturaInformada,
        tamanho,
        categoriaRoupa
    );

    if (!repositorio.adicionar(novaPeca)) {
        delete novaPeca;
        throw EntradaInvalida();
    }

    salvarDados();

    return id;
}


// Cadastra um novo calcado.
int ClosetLog::cadastrarCalcado(
    string nome,
    string material,
    double preco,
    int versatilidade,
    double temperaturaMinima,
    double temperaturaMaxima,
    double confortoMedio,
    bool precisaManutencao,
    int quantidadeUsos,
    int diasSemUso,
    bool temperaturaInformada,
    int numeracao,
    bool impermeavel
) {

    validarDadosComuns(
        preco,
        versatilidade,
        confortoMedio
    );

    validarHistorico(
        quantidadeUsos,
        diasSemUso,
        confortoMedio
    );

    validarTemperatura(
        temperaturaInformada,
        temperaturaMinima,
        temperaturaMaxima
    );

    if (textoInvalido(nome) ||
        textoInvalido(material) ||
        numeracao <= 0) {

        throw EntradaInvalida();
    }

    if (!temperaturaInformada) {
        temperaturaMinima = 0.0;
        temperaturaMaxima = 0.0;
    }

    int id = gerarId();

    Peca* novaPeca = new Calcado(
        id,
        nome,
        material,
        preco,
        versatilidade,
        temperaturaMinima,
        temperaturaMaxima,
        confortoMedio,
        precisaManutencao,
        quantidadeUsos,
        diasSemUso,
        temperaturaInformada,
        numeracao,
        impermeavel
    );

    if (!repositorio.adicionar(novaPeca)) {
        delete novaPeca;
        throw EntradaInvalida();
    }

    salvarDados();

    return id;
}


// Cadastra um novo acessorio.
int ClosetLog::cadastrarAcessorio(
    string nome,
    string material,
    double preco,
    int versatilidade,
    double temperaturaMinima,
    double temperaturaMaxima,
    double confortoMedio,
    bool precisaManutencao,
    int quantidadeUsos,
    int diasSemUso,
    bool temperaturaInformada,
    string tipoAcessorio,
    int nivelFragilidade
) {

    validarDadosComuns(
        preco,
        versatilidade,
        confortoMedio
    );

    validarHistorico(
        quantidadeUsos,
        diasSemUso,
        confortoMedio
    );

    validarTemperatura(
        temperaturaInformada,
        temperaturaMinima,
        temperaturaMaxima
    );

    if (textoInvalido(nome) ||
        textoInvalido(material) ||
        textoInvalido(tipoAcessorio)) {

        throw EntradaInvalida();
    }

    if (nivelFragilidade < 1 || nivelFragilidade > 10) {
        throw EntradaInvalida();
    }

    if (!temperaturaInformada) {
        temperaturaMinima = 0.0;
        temperaturaMaxima = 0.0;
    }

    int id = gerarId();

    Peca* novaPeca = new Acessorio(
        id,
        nome,
        material,
        preco,
        versatilidade,
        temperaturaMinima,
        temperaturaMaxima,
        confortoMedio,
        precisaManutencao,
        quantidadeUsos,
        diasSemUso,
        temperaturaInformada,
        tipoAcessorio,
        nivelFragilidade
    );

    if (!repositorio.adicionar(novaPeca)) {
        delete novaPeca;
        throw EntradaInvalida();
    }

    salvarDados();

    return id;
}


// Busca uma peca pelo identificador.
Peca* ClosetLog::buscarPeca(int id) const {

    return buscarOuLancar(id);
}


// Busca pecas por nome ou por parte do nome.
vector<Peca*> ClosetLog::buscarPecasPorNome(
    string termo,
    unsigned int limite
) const {

    struct ResultadoBusca {

        Peca* peca;
        int pontuacao;
    };

    vector<ResultadoBusca> encontrados;

    string termoNormalizado =
        normalizarTexto(termo);

    vector<Peca*> pecas =
        repositorio.obterItens();

    for (unsigned int i = 0; i < pecas.size(); i++) {

        string nomeNormalizado =
            normalizarTexto(pecas[i]->getNome());

        int pontuacao =
            pontuarNome(nomeNormalizado, termoNormalizado);

        if (pontuacao >= 200) {

            ResultadoBusca resultado;

            resultado.peca = pecas[i];
            resultado.pontuacao = pontuacao;

            encontrados.push_back(resultado);
        }
    }

    sort(
        encontrados.begin(),
        encontrados.end(),
        [](const ResultadoBusca& a,
           const ResultadoBusca& b) {

            if (a.pontuacao != b.pontuacao) {
                return a.pontuacao > b.pontuacao;
            }

            return a.peca->getId() < b.peca->getId();
        }
    );

    vector<Peca*> resultadoFinal;

    for (unsigned int i = 0;
         i < encontrados.size() && i < limite;
         i++) {

        resultadoFinal.push_back(encontrados[i].peca);
    }

    return resultadoFinal;
}


// Remove uma peca pelo identificador.
void ClosetLog::removerPeca(int id) {

    buscarOuLancar(id);

    // Usa o operador - sobrecarregado no repositorio.
    repositorio - id;

    salvarDados();
}


// Atualiza os atributos comuns de uma peca.
void ClosetLog::atualizarPeca(
    int id,
    string novoNome,
    double novoPreco,
    int novaVersatilidade,
    double novoConfortoMedio,
    bool precisaManutencao,
    int diasSemUso,
    bool temperaturaInformada,
    double temperaturaMinima,
    double temperaturaMaxima
) {

    Peca* peca = buscarOuLancar(id);

    validarDadosComuns(
        novoPreco,
        novaVersatilidade,
        novoConfortoMedio
    );

    if (diasSemUso < 0) {
        throw EntradaInvalida();
    }

    validarTemperatura(
        temperaturaInformada,
        temperaturaMinima,
        temperaturaMaxima
    );

    if (textoInvalido(novoNome)) {
        throw EntradaInvalida();
    }

    if (!temperaturaInformada) {
        temperaturaMinima = 0.0;
        temperaturaMaxima = 0.0;
    }

    peca->setNome(novoNome);
    peca->setPreco(novoPreco);
    peca->setVersatilidade(novaVersatilidade);
    peca->setConforto(novoConfortoMedio);
    peca->setPrecisaManutencao(precisaManutencao);
    peca->setDiasSemUso(diasSemUso);

    peca->setFaixaTemperatura(
        temperaturaMinima,
        temperaturaMaxima,
        temperaturaInformada
    );

    salvarDados();
}


// Registra um novo uso de uma peca.
void ClosetLog::registrarUso(int id,
                              double confortoInformado) {

    validarConforto(confortoInformado);

    Peca* peca = buscarOuLancar(id);

    peca->registrarUso(confortoInformado);

    salvarDados();
}


// Calcula o custo medio por uso.
double ClosetLog::calcularCustoPorUso(int id) const {

    Peca* peca = buscarOuLancar(id);

    return peca->calcularCustoPorUso();
}


// Retorna as pecas marcadas para manutencao.
vector<Peca*> ClosetLog::listarPecasComManutencao() const {

    vector<Peca*> pecas = repositorio.obterItens();
    vector<Peca*> pecasComManutencao;

    for (unsigned int i = 0; i < pecas.size(); i++) {

        if (pecas[i]->getPrecisaManutencao()) {
            pecasComManutencao.push_back(pecas[i]);
        }
    }

    return pecasComManutencao;
}


// Retorna os ponteiros armazenados no repositorio.
vector<Peca*> ClosetLog::obterPecas() const {

    return repositorio.obterItens();
}


// Retorna a quantidade de pecas cadastradas.
unsigned int ClosetLog::quantidadePecas() const {

    return repositorio.tamanho();
}


// Imprime todas as pecas cadastradas.
void ClosetLog::imprimir(ostream& out) const {

    out << repositorio;
}


// Salva as pecas no arquivo configurado.
void ClosetLog::salvarDados() const {

    ofstream arquivo(nomeArquivo.c_str());

    if (!arquivo.is_open()) {
        throw ErroArquivo();
    }

    vector<Peca*> pecas = repositorio.obterItens();

    for (unsigned int i = 0; i < pecas.size(); i++) {
        arquivo << pecas[i]->serializar() << endl;
    }

    arquivo.close();
}


// Carrega as pecas salvas anteriormente.
void ClosetLog::carregarDados() {

    ifstream arquivo(nomeArquivo.c_str());

    /*
        O arquivo pode ainda nao existir na primeira execucao.
        Nesse caso, o programa simplesmente inicia vazio.
    */
    if (!arquivo.is_open()) {
        return;
    }

    string linha;
    int maiorId = 0;

    while (getline(arquivo, linha)) {

        if (linha.empty()) {
            continue;
        }

        vector<string> campos = separarCampos(linha);

        /*
            Formato antigo:
            tipo;id;nome;material;preco;usos;dias;versatilidade;
            tempMin;tempMax;conforto;manutencao;campo1;campo2

            Formato novo:
            tipo;id;nome;material;preco;usos;dias;versatilidade;
            temperaturaInformada;tempMin;tempMax;conforto;
            manutencao;campo1;campo2
        */
        if (campos.size() < 14) {
            continue;
        }

        string tipo = campos[0];

        int id = atoi(campos[1].c_str());
        string nome = campos[2];
        string material = campos[3];
        double preco = atof(campos[4].c_str());
        int quantidadeUsos = atoi(campos[5].c_str());
        int diasSemUso = atoi(campos[6].c_str());
        int versatilidade = atoi(campos[7].c_str());

        bool temperaturaInformada = true;
        double temperaturaMinima = 0.0;
        double temperaturaMaxima = 0.0;
        double confortoMedio = 1.0;
        bool precisaManutencao = false;

        unsigned int indiceCampoEspecifico = 12;

        if (campos.size() >= 15) {

            temperaturaInformada =
                atoi(campos[8].c_str()) != 0;

            temperaturaMinima =
                atof(campos[9].c_str());

            temperaturaMaxima =
                atof(campos[10].c_str());

            confortoMedio =
                atof(campos[11].c_str());

            precisaManutencao =
                atoi(campos[12].c_str()) != 0;

            indiceCampoEspecifico = 13;
        }
        else {

            temperaturaInformada = true;

            temperaturaMinima =
                atof(campos[8].c_str());

            temperaturaMaxima =
                atof(campos[9].c_str());

            confortoMedio =
                atof(campos[10].c_str());

            precisaManutencao =
                atoi(campos[11].c_str()) != 0;

            indiceCampoEspecifico = 12;
        }

        if (campos.size() <= indiceCampoEspecifico + 1) {
            continue;
        }

        Peca* peca = nullptr;

        if (tipo == "Roupa") {

            string tamanho =
                campos[indiceCampoEspecifico];

            string categoriaRoupa =
                campos[indiceCampoEspecifico + 1];

            peca = new Roupa(
                id,
                nome,
                material,
                preco,
                versatilidade,
                temperaturaMinima,
                temperaturaMaxima,
                confortoMedio,
                precisaManutencao,
                quantidadeUsos,
                diasSemUso,
                temperaturaInformada,
                tamanho,
                categoriaRoupa
            );
        }
        else if (tipo == "Calcado") {

            int numeracao =
                atoi(campos[indiceCampoEspecifico].c_str());

            bool impermeavel =
                atoi(campos[indiceCampoEspecifico + 1].c_str()) != 0;

            peca = new Calcado(
                id,
                nome,
                material,
                preco,
                versatilidade,
                temperaturaMinima,
                temperaturaMaxima,
                confortoMedio,
                precisaManutencao,
                quantidadeUsos,
                diasSemUso,
                temperaturaInformada,
                numeracao,
                impermeavel
            );
        }
        else if (tipo == "Acessorio") {

            string tipoAcessorio =
                campos[indiceCampoEspecifico];

            int nivelFragilidade =
                atoi(campos[indiceCampoEspecifico + 1].c_str());

            peca = new Acessorio(
                id,
                nome,
                material,
                preco,
                versatilidade,
                temperaturaMinima,
                temperaturaMaxima,
                confortoMedio,
                precisaManutencao,
                quantidadeUsos,
                diasSemUso,
                temperaturaInformada,
                tipoAcessorio,
                nivelFragilidade
            );
        }

        // Ignora linhas cujo tipo nao foi reconhecido.
        if (peca == nullptr) {
            continue;
        }

        if (!repositorio.adicionar(peca)) {
            delete peca;
            continue;
        }

        if (id > maiorId) {
            maiorId = id;
        }
    }

    arquivo.close();

    proximoId = maiorId + 1;

    if (proximoId < 1) {
        proximoId = 1;
    }
}


// Executa a analise de subutilizacao feita em Python.
vector<ResultadoSubutilizacao>
ClosetLog::analisarPecasSubutilizadas() const {

    if (repositorio.tamanho() < 5) {
        throw DadosInsuficientes();
    }

    vector<Peca*> pecas =
        repositorio.obterItens();

    return integradorPython.analisarSubutilizacao(
        pecas
    );
}


// Executa o agrupamento por perfil feito em Python.
vector<ResultadoAgrupamento>
ClosetLog::agruparPecasPorPerfil(
    int quantidadeGrupos
) const {

    if (quantidadeGrupos < 2) {
        throw EntradaInvalida();
    }

    if (repositorio.tamanho() <
        static_cast<unsigned int>(quantidadeGrupos)) {

        throw DadosInsuficientes();
    }

    vector<Peca*> pecas =
        repositorio.obterItens();

    return integradorPython.agruparPorPerfil(
        pecas,
        quantidadeGrupos
    );
}


// Permite utilizar cout << closetLog.
ostream& operator<<(ostream& out,
                    const ClosetLog& closetLog) {

    closetLog.imprimir(out);

    return out;
}