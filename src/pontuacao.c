#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
    FILE *arquivo = fopen("SALVE-C/ranking/rank.txt", "a");
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

    FILE *arquivo = fopen("SALVE-C/ranking/rank.txt", "r");

    Ranking ranks[20];
    int r = 0;

    while (fscanf(arquivo, "%19s %d", ranks[r].nome, &ranks[r].pontuacao) == 2)
    {
        r++;
        if (r >= 20)
        {
            break;
        }
    }
    fclose(arquivo);
    qsort(ranks, r, sizeof(Ranking), compararRank);
    screenGotoxy((MAXX / 2) - 12, 5);
    printf("Melhores jogadores: ");

    int top = r < 10 ? r : 10;
    for (int i = 0; i < top; i++)
    {
        screenGotoxy((MAXX / 2) - 10, 7 + i);
        printf("%2d. %s - %d", i + 1, ranks[i].nome, ranks[i].pontuacao);
    }
    screenGotoxy((MAXX / 2) - 15, MAXY - 2);
    printf("Pessione qualquer tecla para voltar.");
    getchar();
}
