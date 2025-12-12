#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include "screen.h"
#include "jogador.h"
#include "pontuacao.h"

typedef struct
{
    char nome[20];
    int pontuacao;
} Ranking;

void salvarPontuacao()
{
    Jogador *jogador = getJogador();
    int pontos = jogador->pontos;
    FILE *arquivo = fopen("ranking/rank.txt", "a");
    if (!arquivo)
    {
        /* tenta criar diretório caso não exista e reabrir o arquivo */
        mkdir("ranking", 0755);
        arquivo = fopen("ranking/rank.txt", "a");
        if (!arquivo)
        {
            perror("Erro ao abrir ranking/rank.txt para escrita");
            return;
        }
    }

    fprintf(arquivo, "%s %d\n", jogador->apelido, pontos);
    fclose(arquivo);
}

int compararRank(const void *a, const void *b)
{
    const Ranking *ra = (const Ranking *)a;
    const Ranking *rb = (const Ranking *)b;
    return rb->pontuacao - ra->pontuacao;
}

void mostrarRanking()
{
    screenClear();
    screenDrawBorders();
    screenUpdate();
    FILE *arquivo = fopen("ranking/rank.txt", "r");
    if (!arquivo)
    {
        screenGotoxy(MAXX / 2 - 18, MAXY / 2);
        printf("Nenhum ranking encontrado.");
        screenGotoxy(MAXX / 2 - 18, 34);
        printf("Pressione qualquer tecla para voltar.");
        getchar();
        return;
    }

    Ranking ranks[20];
    int r = 0;

    while (r < 20 && fscanf(arquivo, "%19s %d", ranks[r].nome, &ranks[r].pontuacao) == 2)
    {
        r++;
    }
    fclose(arquivo);
    qsort(ranks, r, sizeof(Ranking), compararRank);
    screenGotoxy(12, 4);
    printf("Melhores jogadores: ");

    int top = r < 10 ? r : 10;
    for (int i = 0; i < top; i++)
    {
        screenGotoxy((MAXX / 2) - 10, 7 + i);
        printf("%2d. %s - %d", i + 1, ranks[i].nome, ranks[i].pontuacao);
    }
    screenGotoxy(MAXX / 2 - 18, 34);
    printf("Pessione qualquer tecla para voltar.");
    getchar();
}
