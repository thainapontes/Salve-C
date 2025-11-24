/**
 * main.h
 * Created on Aug, 23th 2023
 * Author: Tiago Barros
 * Based on "From C to C++ course - 2002"
 */
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include "screen.h"
#include "keyboard.h"
#include "timer.h"
#include "telas.h"
#include "jogador.h"

#define MAX_BLOCO 10

int x = 34, y = 12; // Posição inicial do jogador;
int incX = 1;       // Movimentação do jogador

typedef struct
{
    char proposicao[20]; // Armazena a proposição gerada
    char resposta;       // Armazena a resposta da proposição
} Proposicao;

typedef struct
{
    int x;
    int y;
    int tipo;
    int ativo;
} Bloco; // Struct do bloco de resposta

Bloco bloco[MAX_BLOCO];

char operadores[][4] = {"∧", "∨", "→", "↔"}; // Operadores

char negacao(char prop)
{
    //(condição) ? valor_se_verdadeiro : valor_se_falso;
    return (prop == 'V') ? 'F' : 'V';
}

void gerarProposicao(Proposicao *prop)
{
    // Gera um numero aleatório e checa se é par ou impar
    // Sobra = 1 (V) Sobra = 0 (F)
    char p1 = (rand() % 2) ? 'V' : 'F'; // Parte 1 da proposição
    char p2 = (rand() % 2) ? 'V' : 'F'; // Parte 2 da proposição

    // Gera um numero aleatorio e divide por 2, a sobra decide se a proposição sera negada ou não
    int negaP1 = (rand() % 2);
    int negaP2 = (rand() % 2);

    // Se negaP1/P2 == 1 ele inverte o valor (Nega)
    // Se negaP1/P2 == 0 o valor é mantido (Não nega)
    char valA = negaP1 ? negar(p1) : p1;
    char valB = negaP2 ? negar(p2) : p2;

    // Define qual vai ser o operador lógico
    int opIndex = rand() % 4;
    char *operador = operadores[opIndex];

    // Monta a expressão
    char exprA[4], exprB[4];
    // Altera o texto caso seja negada ou não
    sprintf(exprA, "%s%c", negaP1 ? "¬" : "", p1);
    sprintf(exprB, "%s%c", negaP2 ? "¬" : "", p2);
    // Mostra a expressão finalizada
    sprintf(prop->proposicao, "(%s %s %s)", exprA, operador, exprB);

    // Avalia a expressão
    char resultado;

    if (strcmp(operador, "∧") == 0)
    {                                                         // Operador lógico "E" (as duas proposições tem que ser verdadeiras)
        resultado = (valA == 'V' && valB == 'V') ? 'V' : 'F'; // Só será V se os dois forem V, se não será F
    }
    else if (strcmp(operador, "∨") == 0)
    {                                                         // Operador lógico "OU" (As duas tem que ser falsas)
        resultado = (valA == 'F' && valB == 'F') ? 'F' : 'V'; // Só será F se os dois forem F, se não será V
    }
    else if (strcmp(operador, "→") == 0)
    {                                                         // Operador lógico "ENTÃO"
        resultado = (valA == 'V' && valB == 'F') ? 'F' : 'V'; // Só será F quando A = V e B = F, todo o resto é verdadeiro
    }
    else if (strcmp(operador, "↔") == 0)
    {                                           // Operador lógico "SE E SOMENTE SE"
        resultado = (valA == valB) ? 'V' : 'F'; // Os casos iguais são sempre V, o resto são falsos
    }

    prop->resposta = resultado;
}

void logica(Proposicao expressao)
{
    Jogador *statusJogador = getJogador();

    screenGotoxy(3, 3);

    printf("ESPRESSÃO: %s     RESPOSTA: %s", expressao.proposicao, expressao.resposta);

    screenGotoxy(2, 5);
    printf("_________________________________________________________________________________________________");
    screenGotoxy(MAXX * 0.5, 2);
    printf("|");
    screenGotoxy(MAXX * 0.5, 3);
    printf("|");
    screenGotoxy(MAXX * 0.5, 4);
    printf("|");

    screenGotoxy((MAXX * 0.5) + 8, 3);
    printf("VIDAS: %d          PONTOS: %d", statusJogador->vidas, statusJogador->pontos);
}

void verificaColisao(Proposicao *proposicao)
{
    Jogador *jogador = getJogador();
    for (int i = 0; i < MAX_BLOCO; i++)
    {
        if (bloco[i].ativo)
        {
            if (bloco[i].x == x && bloco[i].y == y)
            {
                int respostaProp = (proposicao->resposta == 'V') ? 0 : 1;
                if (bloco[i].tipo == respostaProp)
                {
                    setPontos(jogador->pontos += 100);
                    gerarProposicao(proposicao);
                }
                else
                {
                    setVidas(jogador->vidas -= 1);
                    setPontos(jogador->pontos -= 50);
                    gerarProposicao(proposicao);
                }
                bloco[i].ativo = 0;
                screenGotoxy(bloco[i].x, bloco[i].y);
                printf("   ");

                screenUpdate();
                break;
            }
        }
    }
}

void movimentacao(int ch)
{
    screenGotoxy(x, y); // apaga a posição anterior do jogador
    printf("   ");      // tamanho do jogador

    if (ch == 100 && x < MAXX - strlen("[_]") - 1) // Tecla A
    {
        x += incX; // move para a esquerda
    }
    else if (ch == 97 && x > MINX + 1) // Tecla D
    {
        x -= incX; // move para a direita
    }

    // Cria o jogador na nova posição
    screenGotoxy(x, y);
    printf("[_]");

    screenUpdate();
}

void criarBloco()
{
    for (int i = 0; i < MAX_BLOCO; i++)
    {
        if (!bloco[i].ativo)
        {
            bloco[i].ativo = 1;
            bloco[i].x = rand() % (MAXX - 10) + 5;
            bloco[i].y = 6;
            bloco[i].tipo = rand() % 2;
            break;
        }
    }
}

int deslocamentoBloco = 0;
void atualizaBloco()
{
    deslocamentoBloco++;
    if (deslocamentoBloco % 2 != 0)
    {
        return; // o bloco so se move a cada duas atualizações
    }
    for (int i = 0; i < MAX_BLOCO; i++)
    {
        if (bloco[i].ativo)
        {
            screenGotoxy(bloco[i].x, bloco[i].y);
            printf("   ");
            bloco[i].y++;

            if (bloco[i].y >= MAXY - 1)
            {
                bloco[i].ativo = 0;
            }
            else
            {
                screenGotoxy(bloco[i].x, bloco[i].y);
                if (bloco[i].tipo == 0)
                {
                    printf("V");
                }
                else
                {
                    printf("F");
                }
            }
        }
    }
}

void iniciarGame()
{
    Proposicao proposicao;
    gerarProposicao(&proposicao);

    Jogador *jogador = getJogador();
    setVidas(5);
    setPontos(0);

    static int caracter = 0;
    static long timer = 0;

    for (int i = 0; i < MAX_BLOCO; i++)
    {
        bloco[i].ativo = 0;
    }

    x = 48;
    y = 33;

    srand(time(NULL));
    screenInit(1);
    keyboardInit();
    timerInit(50);

    logica(proposicao);
    movimentacao(100);
    screenUpdate();

    while (jogador->vidas > 0)
    {
        logica(proposicao);

        if (keyhit())
        {
            int ch = readch();
            movimentacao(ch);
        }

        if (rand() % 10 == 0)
        {
            criarBloco();
        }

        atualizaBloco();              // atualiza a posição dos blocos
        verificaColisao(&proposicao); // Verifica se o jogador selecionou uma resposta;

        screenUpdate();
        timer++;
    }
    salvarPontuacao(); // Salva a pontuação em um arquivo externo
    telaDerrota();     // Mostra a tela de game over
}

int main()
{
    screenSetColor(WHITE, BLACK);
    telaInicial();
    return 0;
}
