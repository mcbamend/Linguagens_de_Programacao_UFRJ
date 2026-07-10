#include "Menu.h"

#include <cctype>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;


// Remove espacos no inicio e no fim de um texto.
static string removerEspacosLaterais(const string& texto) {

    unsigned int inicio = 0;

    while (inicio < texto.size() &&
           isspace(static_cast<unsigned char>(texto[inicio]))) {

        inicio++;
    }

    unsigned int fim = texto.size();

    while (fim > inicio &&
           isspace(static_cast<unsigned char>(texto[fim - 1]))) {

        fim--;
    }

    return texto.substr(inicio, fim - inicio);
}


// Converte uma string para minusculas.
static string converterMinusculas(string texto) {

    for (unsigned int i = 0; i < texto.size(); i++) {

        texto[i] = static_cast<char>(
            tolower(static_cast<unsigned char>(texto[i]))
        );
    }

    return texto;
}


// Troca virgula por ponto para aceitar entrada como 7,5.
static void trocarVirgulaPorPonto(string& texto) {

    for (unsigned int i = 0; i < texto.size(); i++) {

        if (texto[i] == ',') {
            texto[i] = '.';
        }
    }
}


// Verifica se um texto representa um numero inteiro.
static bool textoEhInteiro(const string& texto, int& valor) {

    stringstream fluxo(texto);
    string resto;

    if (!(fluxo >> valor)) {
        return false;
    }

    if (fluxo >> resto) {
        return false;
    }

    return true;
}


// Mostra possiveis motivos para uma peca ter sido marcada
// como subutilizada.
static void imprimirMotivosSubutilizacao(const Peca* peca) {

    if (peca == nullptr) {
        return;
    }

    bool mostrouMotivo = false;

    cout << "Possiveis motivos:" << endl;

    if (peca->getQuantidadeUsos() <= 1) {
        cout << "- poucos usos registrados" << endl;
        mostrouMotivo = true;
    }

    if (peca->getDiasSemUso() >= 60) {
        cout << "- muitos dias sem uso" << endl;
        mostrouMotivo = true;
    }

    if (peca->getVersatilidade() <= 4) {
        cout << "- baixa versatilidade" << endl;
        mostrouMotivo = true;
    }

    if (peca->getConforto() <= 6.0) {
        cout << "- conforto medio baixo" << endl;
        mostrouMotivo = true;
    }

    if (peca->getPrecisaManutencao()) {
        cout << "- precisa de manutencao" << endl;
        mostrouMotivo = true;
    }

    if (peca->getQuantidadeUsos() > 0 &&
        peca->calcularCustoPorUso() >= 150.0) {

        cout << "- custo por uso elevado" << endl;
        mostrouMotivo = true;
    }

    if (!mostrouMotivo) {
        cout << "- combinacao incomum em relacao as outras pecas"
             << endl;
    }
}


// Inicializa o menu principal.
Menu::Menu() : closetLog("pecas.csv") {
}


// Exibe as opcoes principais.
void Menu::mostrarMenu() const {

    cout << "==================================" << endl;
    cout << "            CLOSETLOG             " << endl;
    cout << "==================================" << endl;
    cout << "1 - Cadastrar peca" << endl;
    cout << "2 - Registrar uso de uma peca" << endl;
    cout << "3 - Listar pecas cadastradas" << endl;
    cout << "4 - Buscar, editar ou remover peca" << endl;
    cout << "5 - Calcular custo por uso" << endl;
    cout << "6 - Analisar pecas subutilizadas" << endl;
    cout << "7 - Agrupar pecas por perfil de uso" << endl;
    cout << "8 - Listar pecas para manutencao" << endl;
    cout << "0 - Sair" << endl;
    cout << "==================================" << endl;
}


// Le a opcao escolhida.
int Menu::lerOpcao() {

    mostrarMenu();

    return lerInteiro("Escolha uma opcao: ");
}


// Executa a opcao escolhida.
void Menu::executarOpcao(int opcao) {

    switch (opcao) {

        case 1:
            cadastrarPeca();
            break;

        case 2:
            registrarUso();
            break;

        case 3:
            listarPecas();
            break;

        case 4:
            gerenciarPeca();
            break;

        case 5:
            mostrarCustoPorUso();
            break;

        case 6:
            analisarSubutilizacao();
            break;

        case 7:
            agruparPorPerfil();
            break;

        case 8:
            listarManutencao();
            break;

        case 0:
            cout << endl;
            cout << "Encerrando o ClosetLog..." << endl;
            break;

        default:
            cout << endl;
            cout << "Opcao invalida." << endl;
            break;
    }
}


// Pausa a execucao e limpa a tela.
void Menu::pausarELimpar() const {

    esperarEnter();
    limparTela();
}


// Le os dados comuns a roupa, calcado e acessorio.
Menu::DadosComunsCadastro Menu::lerDadosComunsCadastro() const {

    DadosComunsCadastro dados;

    dados.nome = lerTexto("Nome da peca: ");
    dados.material = lerTexto("Material: ");
    dados.preco = lerDouble("Preco: R$ ");
    dados.versatilidade = lerInteiro("Versatilidade (1 a 10): ");

    lerTemperaturaOpcional(
        dados.temperaturaInformada,
        dados.temperaturaMinima,
        dados.temperaturaMaxima
    );

    cout << endl;
    cout << "Historico inicial da peca" << endl;
    cout << "Se a peca for nova, use 0 usos e 0 dias sem uso."
         << endl;

    dados.quantidadeUsos =
        lerInteiro("Quantidade de usos ja registrados: ");

    dados.diasSemUso =
        lerInteiro("Dias sem uso: ");

    dados.confortoMedio =
        lerDouble("Conforto medio atual (1 a 10): ");

    dados.precisaManutencao =
        lerBooleano("Precisa de manutencao? (1-sim / 0-nao): ");

    return dados;
}


// Le a faixa de temperatura somente quando fizer sentido.
void Menu::lerTemperaturaOpcional(bool& temperaturaInformada,
                                  double& temperaturaMinima,
                                  double& temperaturaMaxima) const {

    temperaturaInformada =
        lerBooleano("Deseja informar faixa de temperatura? "
                    "(1-sim / 0-nao): ");

    if (temperaturaInformada) {

        temperaturaMinima =
            lerDouble("Temperatura minima indicada: ");

        temperaturaMaxima =
            lerDouble("Temperatura maxima indicada: ");
    }
    else {

        temperaturaMinima = 0.0;
        temperaturaMaxima = 0.0;
    }
}


// Cadastra uma nova peca.
void Menu::cadastrarPeca() {

    cout << endl;
    cout << "===== CADASTRO DE PECA =====" << endl;
    cout << "1 - Roupa" << endl;
    cout << "2 - Calcado" << endl;
    cout << "3 - Acessorio" << endl;

    int tipo = lerInteiro("Tipo da peca: ");

    DadosComunsCadastro dados =
        lerDadosComunsCadastro();

    int idCriado = 0;

    if (tipo == 1) {

        string tamanho =
            lerTexto("Tamanho: ");

        string categoriaRoupa =
            lerTexto("Categoria da roupa: ");

        idCriado = closetLog.cadastrarRoupa(
            dados.nome,
            dados.material,
            dados.preco,
            dados.versatilidade,
            dados.temperaturaMinima,
            dados.temperaturaMaxima,
            dados.confortoMedio,
            dados.precisaManutencao,
            dados.quantidadeUsos,
            dados.diasSemUso,
            dados.temperaturaInformada,
            tamanho,
            categoriaRoupa
        );
    }
    else if (tipo == 2) {

        int numeracao =
            lerInteiro("Numeracao: ");

        bool impermeavel =
            lerBooleano("Impermeavel? (1-sim / 0-nao): ");

        idCriado = closetLog.cadastrarCalcado(
            dados.nome,
            dados.material,
            dados.preco,
            dados.versatilidade,
            dados.temperaturaMinima,
            dados.temperaturaMaxima,
            dados.confortoMedio,
            dados.precisaManutencao,
            dados.quantidadeUsos,
            dados.diasSemUso,
            dados.temperaturaInformada,
            numeracao,
            impermeavel
        );
    }
    else if (tipo == 3) {

        string tipoAcessorio =
            lerTexto("Tipo do acessorio: ");

        int nivelFragilidade =
            lerInteiro("Nivel de fragilidade (1 a 10): ");

        idCriado = closetLog.cadastrarAcessorio(
            dados.nome,
            dados.material,
            dados.preco,
            dados.versatilidade,
            dados.temperaturaMinima,
            dados.temperaturaMaxima,
            dados.confortoMedio,
            dados.precisaManutencao,
            dados.quantidadeUsos,
            dados.diasSemUso,
            dados.temperaturaInformada,
            tipoAcessorio,
            nivelFragilidade
        );
    }
    else {
        throw EntradaInvalida();
    }

    cout << endl;
    cout << "Peca cadastrada com sucesso." << endl;
    cout << "ID gerado: " << idCriado << endl;
}


// Registra um novo uso de uma peca.
void Menu::registrarUso() {

    cout << endl;
    cout << "===== REGISTRAR USO =====" << endl;

    int id = selecionarIdPecaPorIdOuNome();

    double confortoInformado =
        lerDouble("Conforto neste uso (1 a 10): ");

    closetLog.registrarUso(
        id,
        confortoInformado
    );

    cout << endl;
    cout << "Uso registrado com sucesso." << endl;
}


// Lista todas as pecas.
void Menu::listarPecas() const {

    cout << endl;
    cout << "===== PECAS CADASTRADAS =====" << endl;
    cout << closetLog;
}


// Abre o submenu de gerenciamento.
void Menu::gerenciarPeca() {

    int opcao = -1;

    do {

        cout << endl;
        cout << "===== GERENCIAR PECA =====" << endl;
        cout << "1 - Buscar peca" << endl;
        cout << "2 - Editar peca" << endl;
        cout << "3 - Remover peca" << endl;
        cout << "0 - Voltar" << endl;

        opcao = lerInteiro("Escolha uma opcao: ");

        switch (opcao) {

            case 1:
                buscarPeca();
                break;

            case 2:
                editarPeca();
                break;

            case 3:
                removerPeca();
                break;

            case 0:
                break;

            default:
                cout << "Opcao invalida." << endl;
                break;
        }

    } while (opcao != 0);
}


// Busca uma peca por ID ou nome.
void Menu::buscarPeca() const {

    cout << endl;
    cout << "===== BUSCAR PECA =====" << endl;

    Peca* peca =
        selecionarPecaPorIdOuNome();

    cout << endl;
    cout << "Peca selecionada:" << endl;
    cout << "------------------------------" << endl;
    cout << *peca;
    cout << "------------------------------" << endl;
}


// Edita os dados comuns de uma peca.
void Menu::editarPeca() {

    cout << endl;
    cout << "===== EDITAR PECA =====" << endl;

    Peca* peca =
        selecionarPecaPorIdOuNome();

    cout << endl;
    cout << "Peca atual:" << endl;
    imprimirResumoPeca(peca);

    cout << endl;
    cout << "Informe os novos dados comuns da peca." << endl;

    string novoNome =
        lerTexto("Novo nome: ");

    double novoPreco =
        lerDouble("Novo preco: R$ ");

    int novaVersatilidade =
        lerInteiro("Nova versatilidade (1 a 10): ");

    bool temperaturaInformada;
    double temperaturaMinima;
    double temperaturaMaxima;

    lerTemperaturaOpcional(
        temperaturaInformada,
        temperaturaMinima,
        temperaturaMaxima
    );

    int diasSemUso =
        lerInteiro("Dias sem uso: ");

    double novoConfortoMedio =
        lerDouble("Conforto medio atual (1 a 10): ");

    bool precisaManutencao =
        lerBooleano("Precisa de manutencao? (1-sim / 0-nao): ");

    closetLog.atualizarPeca(
        peca->getId(),
        novoNome,
        novoPreco,
        novaVersatilidade,
        novoConfortoMedio,
        precisaManutencao,
        diasSemUso,
        temperaturaInformada,
        temperaturaMinima,
        temperaturaMaxima
    );

    cout << endl;
    cout << "Peca atualizada com sucesso." << endl;
}


// Remove uma peca.
void Menu::removerPeca() {

    cout << endl;
    cout << "===== REMOVER PECA =====" << endl;

    Peca* peca =
        selecionarPecaPorIdOuNome();

    cout << endl;
    cout << "Peca selecionada:" << endl;
    imprimirResumoPeca(peca);

    bool confirmar =
        lerBooleano("Confirmar remocao? (1-sim / 0-nao): ");

    if (!confirmar) {
        cout << "Remocao cancelada." << endl;
        return;
    }

    closetLog.removerPeca(
        peca->getId()
    );

    cout << endl;
    cout << "Peca removida com sucesso." << endl;
}


// Mostra o custo medio por uso.
void Menu::mostrarCustoPorUso() const {

    cout << endl;
    cout << "===== CUSTO POR USO =====" << endl;

    Peca* peca =
        selecionarPecaPorIdOuNome();

    double custo =
        closetLog.calcularCustoPorUso(
            peca->getId()
        );

    cout << endl;
    imprimirResumoPeca(peca);

    if (peca->getQuantidadeUsos() == 0) {
        cout << "A peca ainda nao possui usos registrados."
             << endl;
    }
    else {
        cout << fixed << setprecision(2);
        cout << "Custo por uso: R$ "
             << custo
             << endl;
    }
}


// Executa a analise de subutilizacao feita em Python.
void Menu::analisarSubutilizacao() const {

    cout << endl;
    cout << "===== ANALISE DE SUBUTILIZACAO =====" << endl;

    vector<ResultadoSubutilizacao> resultados =
        closetLog.analisarPecasSubutilizadas();

    int totalSubutilizadas = 0;

    for (unsigned int i = 0; i < resultados.size(); i++) {

        Peca* peca =
            closetLog.buscarPeca(resultados[i].idPeca);

        cout << "------------------------------" << endl;
        cout << "ID: " << peca->getId() << endl;
        cout << "Nome: " << peca->getNome() << endl;
        cout << "Tipo: " << peca->getTipo() << endl;

        cout << fixed << setprecision(2);
        cout << "Pontuacao de subutilizacao: "
             << resultados[i].pontuacao
             << endl;

        cout << "Classificacao: "
             << (resultados[i].subutilizada
                 ? "Subutilizada"
                 : "Perfil normal")
             << endl;

        if (resultados[i].subutilizada) {

            totalSubutilizadas++;

            imprimirMotivosSubutilizacao(peca);
        }
    }

    cout << "------------------------------" << endl;
    cout << "Total de pecas subutilizadas: "
         << totalSubutilizadas
         << endl;
}


// Executa o agrupamento feito em Python.
void Menu::agruparPorPerfil() const {

    cout << endl;
    cout << "===== AGRUPAMENTO POR PERFIL =====" << endl;

    int quantidadeGrupos =
        lerInteiro("Quantidade de grupos: ");

    vector<ResultadoAgrupamento> resultados =
        closetLog.agruparPecasPorPerfil(
            quantidadeGrupos
        );

    cout << endl;
    cout << "Grupo 0 representa, em media, o menor aproveitamento."
         << endl;

    for (int grupo = 0; grupo < quantidadeGrupos; grupo++) {

        cout << endl;
        cout << "Grupo " << grupo << ":" << endl;

        bool encontrou = false;

        for (unsigned int i = 0; i < resultados.size(); i++) {

            if (resultados[i].grupo == grupo) {

                Peca* peca =
                    closetLog.buscarPeca(resultados[i].idPeca);

                cout << "- ID "
                     << peca->getId()
                     << " | "
                     << peca->getNome()
                     << " | "
                     << peca->getTipo()
                     << " | usos: "
                     << peca->getQuantidadeUsos()
                     << " | dias sem uso: "
                     << peca->getDiasSemUso()
                     << endl;

                encontrou = true;
            }
        }

        if (!encontrou) {
            cout << "- Nenhuma peca neste grupo." << endl;
        }
    }
}


// Lista as pecas marcadas para manutencao.
void Menu::listarManutencao() const {

    cout << endl;
    cout << "===== PECAS PARA MANUTENCAO =====" << endl;

    vector<Peca*> pecas =
        closetLog.listarPecasComManutencao();

    if (pecas.empty()) {
        cout << "Nenhuma peca marcada para manutencao."
             << endl;
        return;
    }

    for (unsigned int i = 0; i < pecas.size(); i++) {

        cout << "------------------------------" << endl;
        imprimirResumoPeca(pecas[i]);
    }

    cout << "------------------------------" << endl;
}


// Seleciona uma peca digitando ID ou parte do nome.
Peca* Menu::selecionarPecaPorIdOuNome() const {

    while (true) {

        string entrada =
            lerTexto("Digite o ID ou parte do nome da peca: ");

        int id = 0;

        if (textoEhInteiro(entrada, id)) {

            Peca* peca =
                closetLog.buscarPeca(id);

            cout << endl;
            cout << "Peca encontrada:" << endl;
            imprimirResumoPeca(peca);

            bool confirmar =
                lerBooleano("E essa peca? (1-sim / 0-nao): ");

            if (confirmar) {
                return peca;
            }

            continue;
        }

        vector<Peca*> encontradas =
            closetLog.buscarPecasPorNome(
                entrada,
                5
            );

        if (encontradas.empty()) {

            cout << endl;
            cout << "Nenhuma peca encontrada com esse termo."
                 << endl;

            bool tentarNovamente =
                lerBooleano("Deseja tentar novamente? "
                            "(1-sim / 0-nao): ");

            if (!tentarNovamente) {
                throw PecaNaoEncontrada();
            }

            continue;
        }

        cout << endl;
        cout << "Pecas encontradas:" << endl;

        for (unsigned int i = 0; i < encontradas.size(); i++) {

            cout << i + 1 << " - ";
            imprimirResumoPeca(encontradas[i]);
        }

        cout << "0 - Cancelar" << endl;

        int escolha =
            lerInteiro("Escolha a peca: ");

        if (escolha == 0) {
            throw PecaNaoEncontrada();
        }

        if (escolha < 1 ||
            escolha > static_cast<int>(encontradas.size())) {

            cout << "Escolha invalida." << endl;
            continue;
        }

        Peca* selecionada =
            encontradas[escolha - 1];

        bool confirmar =
            lerBooleano("Confirmar esta peca? "
                        "(1-sim / 0-nao): ");

        if (confirmar) {
            return selecionada;
        }
    }
}


// Seleciona uma peca e retorna apenas o ID.
int Menu::selecionarIdPecaPorIdOuNome() const {

    Peca* peca =
        selecionarPecaPorIdOuNome();

    return peca->getId();
}


// Imprime uma versao curta de uma peca.
void Menu::imprimirResumoPeca(const Peca* peca) const {

    if (peca == nullptr) {
        cout << "Peca inexistente." << endl;
        return;
    }

    cout << "ID "
         << peca->getId()
         << " | "
         << peca->getNome()
         << " | "
         << peca->getTipo()
         << " | usos: "
         << peca->getQuantidadeUsos()
         << " | dias sem uso: "
         << peca->getDiasSemUso()
         << endl;
}


// Le um numero inteiro.
int Menu::lerInteiro(const string& mensagem) const {

    while (true) {

        string entrada;

        cout << mensagem;
        getline(cin, entrada);

        entrada = removerEspacosLaterais(entrada);

        int valor = 0;

        if (textoEhInteiro(entrada, valor)) {
            return valor;
        }

        cout << "Entrada invalida. Digite um numero inteiro."
             << endl;
    }
}


// Le um numero real.
double Menu::lerDouble(const string& mensagem) const {

    while (true) {

        string entrada;

        cout << mensagem;
        getline(cin, entrada);

        entrada = removerEspacosLaterais(entrada);

        trocarVirgulaPorPonto(entrada);

        stringstream fluxo(entrada);
        string resto;
        double valor = 0.0;

        if ((fluxo >> valor) && !(fluxo >> resto)) {
            return valor;
        }

        cout << "Entrada invalida. Digite um numero."
             << endl;
    }
}


// Le um texto nao vazio.
string Menu::lerTexto(const string& mensagem) const {

    while (true) {

        string texto;

        cout << mensagem;
        getline(cin, texto);

        texto = removerEspacosLaterais(texto);

        if (!texto.empty()) {
            return texto;
        }

        cout << "Entrada invalida. O texto nao pode ser vazio."
             << endl;
    }
}


// Le uma resposta booleana.
bool Menu::lerBooleano(const string& mensagem) const {

    while (true) {

        string entrada;

        cout << mensagem;
        getline(cin, entrada);

        entrada = removerEspacosLaterais(
            converterMinusculas(entrada)
        );

        if (entrada == "1" ||
            entrada == "s" ||
            entrada == "sim" ||
            entrada == "y" ||
            entrada == "yes") {

            return true;
        }

        if (entrada == "0" ||
            entrada == "n" ||
            entrada == "nao" ||
            entrada == "não" ||
            entrada == "no") {

            return false;
        }

        cout << "Entrada invalida. Digite 1 para sim ou 0 para nao."
             << endl;
    }
}


// Espera o usuario pressionar Enter.
void Menu::esperarEnter() const {

    cout << endl;
    cout << "Pressione Enter para continuar...";

    string linha;
    getline(cin, linha);
}


// Limpa a tela
void Menu::limparTela() const {

    cout << "\033[2J\033[1;1H";
}