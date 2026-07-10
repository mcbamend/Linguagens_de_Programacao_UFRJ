import numpy as np

from sklearn.cluster import KMeans
from sklearn.ensemble import IsolationForest
from sklearn.preprocessing import StandardScaler


# Cada peca deve ser recebida do C++ neste formato:
#
# (
#     id,
#     preco,
#     quantidade_usos,
#     dias_sem_uso,
#     versatilidade,
#     conforto_medio,
#     precisa_manutencao
# )
#
# A temperatura nao entra na analise porque nem sempre faz sentido
# para todos os tipos de peca, principalmente acessorios.


def _converter_dados(dados):
    """
    Valida os dados recebidos do C++ e os transforma
    em uma matriz numerica utilizada pelos algoritmos.
    """

    if not isinstance(dados, (list, tuple)):
        raise ValueError("Os dados devem ser enviados em uma lista.")

    if len(dados) == 0:
        raise ValueError("Nenhuma peca foi enviada para a analise.")

    ids = []
    registros = []

    for posicao, peca in enumerate(dados):

        if not isinstance(peca, (list, tuple)):
            raise ValueError(
                "Cada peca deve ser representada por uma lista ou tupla."
            )

        if len(peca) != 7:
            raise ValueError(
                "Cada peca deve possuir exatamente sete campos."
            )

        try:
            id_peca = int(peca[0])
            preco = float(peca[1])
            quantidade_usos = int(peca[2])
            dias_sem_uso = int(peca[3])
            versatilidade = int(peca[4])
            conforto_medio = float(peca[5])
            precisa_manutencao = bool(peca[6])

        except (TypeError, ValueError) as erro:
            raise ValueError(
                "Existem valores invalidos na peca da posicao "
                + str(posicao)
                + "."
            ) from erro

        if id_peca <= 0:
            raise ValueError("O ID da peca deve ser positivo.")

        if id_peca in ids:
            raise ValueError("Existem pecas com IDs repetidos.")

        if preco < 0:
            raise ValueError("O preco nao pode ser negativo.")

        if quantidade_usos < 0:
            raise ValueError(
                "A quantidade de usos nao pode ser negativa."
            )

        if dias_sem_uso < 0:
            raise ValueError(
                "Os dias sem uso nao podem ser negativos."
            )

        if versatilidade < 1 or versatilidade > 10:
            raise ValueError(
                "A versatilidade deve estar entre 1 e 10."
            )

        if conforto_medio < 1.0 or conforto_medio > 10.0:
            raise ValueError(
                "O conforto medio deve estar entre 1 e 10."
            )

        if quantidade_usos == 0:
            custo_por_uso = preco
        else:
            custo_por_uso = preco / quantidade_usos

        ids.append(id_peca)

        registros.append(
            [
                preco,
                quantidade_usos,
                dias_sem_uso,
                versatilidade,
                conforto_medio,
                int(precisa_manutencao),
                custo_por_uso,
            ]
        )

    matriz = np.asarray(registros, dtype=float)

    return ids, matriz


def _normalizar_pontuacoes(valores):
    """
    Converte os valores recebidos para uma escala entre 0 e 100.
    A pontuacao e relativa ao conjunto de pecas analisado.
    """

    menor_valor = float(np.min(valores))
    maior_valor = float(np.max(valores))

    amplitude = maior_valor - menor_valor

    if amplitude == 0:
        return np.full(len(valores), 50.0)

    return 100.0 * (valores - menor_valor) / amplitude


def analisar_subutilizacao(dados):
    """
    Identifica pecas com perfil incomum de subutilizacao.

    Retorno:
    [
        (id_peca, pontuacao, subutilizada),
        ...
    ]

    A pontuacao varia de 0 a 100.
    Quanto maior, maior o perfil de subutilizacao
    em comparacao com as outras pecas.
    """

    ids, matriz = _converter_dados(dados)

    if len(ids) < 5:
        raise ValueError(
            "Sao necessarias pelo menos cinco pecas para a analise."
        )

    quantidade_usos = matriz[:, 1]
    dias_sem_uso = matriz[:, 2]
    versatilidade = matriz[:, 3]
    conforto_medio = matriz[:, 4]
    precisa_manutencao = matriz[:, 5]
    custo_por_uso = matriz[:, 6]

    # Todas as colunas sao organizadas para que valores maiores
    # indiquem uma possibilidade maior de subutilizacao.
    #
    # Exemplo:
    # custo por uso alto              -> mais subutilizacao
    # muitos dias sem uso             -> mais subutilizacao
    # poucos usos                     -> mais subutilizacao
    # baixa versatilidade             -> mais subutilizacao
    # conforto medio baixo            -> mais subutilizacao
    # precisa de manutencao           -> mais subutilizacao
    caracteristicas = np.column_stack(
        [
            custo_por_uso,
            dias_sem_uso,
            1.0 / (quantidade_usos + 1.0),
            10.0 - versatilidade,
            10.0 - conforto_medio,
            precisa_manutencao,
        ]
    )

    normalizador = StandardScaler()

    caracteristicas_normalizadas = normalizador.fit_transform(
        caracteristicas
    )

    modelo = IsolationForest(
        n_estimators=200,
        contamination=0.25,
        random_state=42,
    )

    classificacoes = modelo.fit_predict(
        caracteristicas_normalizadas
    )

    # O indice direcional nao decide sozinho se uma peca
    # e subutilizada. Ele serve para criar uma pontuacao
    # mais facil de entender pelo usuario.
    indice_direcional = np.mean(
        caracteristicas_normalizadas,
        axis=1,
    )

    pontuacoes = _normalizar_pontuacoes(indice_direcional)

    resultados = []

    for i in range(len(ids)):

        # O Isolation Forest devolve:
        # -1 para um perfil considerado anomalo;
        #  1 para um perfil considerado normal.
        #
        # Nesta versao, se o modelo marcou como anomalia,
        # a peca e classificada como subutilizada.
        subutilizada = classificacoes[i] == -1

        resultados.append(
            (
                int(ids[i]),
                round(float(pontuacoes[i]), 2),
                bool(subutilizada),
            )
        )

    # Ordena da maior para a menor pontuacao.
    # Isso deixa a saida do menu mais intuitiva.
    resultados.sort(
        key=lambda item: item[1],
        reverse=True,
    )

    return resultados


def agrupar_por_perfil(dados, quantidade_grupos):
    """
    Agrupa as pecas de acordo com seus perfis de uso.

    Retorno:
    [
        (id_peca, grupo),
        ...
    ]

    O grupo 0 representa o perfil de menor aproveitamento.
    Os grupos de numeros maiores apresentam, em media,
    melhor aproveitamento.
    """

    ids, matriz = _converter_dados(dados)

    try:
        quantidade_grupos = int(quantidade_grupos)

    except (TypeError, ValueError) as erro:
        raise ValueError(
            "A quantidade de grupos deve ser um numero inteiro."
        ) from erro

    if quantidade_grupos < 2:
        raise ValueError(
            "A quantidade de grupos deve ser pelo menos dois."
        )

    if quantidade_grupos > len(ids):
        raise ValueError(
            "A quantidade de grupos nao pode superar "
            "a quantidade de pecas."
        )

    normalizador = StandardScaler()

    matriz_normalizada = normalizador.fit_transform(matriz)

    modelo = KMeans(
        n_clusters=quantidade_grupos,
        n_init=10,
        random_state=42,
    )

    grupos_originais = modelo.fit_predict(matriz_normalizada)

    quantidade_usos = matriz[:, 1]
    dias_sem_uso = matriz[:, 2]
    versatilidade = matriz[:, 3]
    conforto_medio = matriz[:, 4]
    precisa_manutencao = matriz[:, 5]
    custo_por_uso = matriz[:, 6]

    # Esse indice serve apenas para ordenar os nomes dos grupos.
    # Ele nao interfere na formacao dos agrupamentos pelo K-Means.
    #
    # Quanto maior, melhor tende a ser o aproveitamento da peca.
    indice_aproveitamento = (
        quantidade_usos
        - dias_sem_uso / 30.0
        + versatilidade
        + conforto_medio
        - 2.0 * precisa_manutencao
        - custo_por_uso / 100.0
    )

    medias_dos_grupos = {}

    for grupo in range(quantidade_grupos):

        mascara = grupos_originais == grupo

        medias_dos_grupos[grupo] = float(
            np.mean(indice_aproveitamento[mascara])
        )

    grupos_ordenados = sorted(
        medias_dos_grupos,
        key=medias_dos_grupos.get,
    )

    conversao_grupos = {}

    for novo_grupo, grupo_original in enumerate(grupos_ordenados):
        conversao_grupos[grupo_original] = novo_grupo

    resultados = []

    for i in range(len(ids)):

        grupo_final = conversao_grupos[
            int(grupos_originais[i])
        ]

        resultados.append(
            (
                int(ids[i]),
                int(grupo_final),
            )
        )

    return resultados