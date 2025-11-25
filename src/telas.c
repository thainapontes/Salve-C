#include "screen.h"
#include "keyboard.h"
#include "timer.h"
#include "jogador.h"
#include "main.h"
#include "telas.h"
#include "pontuacao.h"

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

char apelido[TAM_MAX_APELIDO];

void nomeJogador()
{
    screenClear();
    screenDrawBorders();

    screenGotoxy(5, 3);
    printf("Olá! Qual o seu nome? ");
    if (fgets(apelido, sizeof(apelido), stdin))
    {
        apelido[strcspn(apelido, "\n")] = '\0';
        iniciarJogador(apelido);
    }
}

void imprimirMenu()
{
    screenClear();
    screenDrawBorders();
    screenGotoxy(13, 3);
    printf("   _____         _ __      ________       _____ \n");
    screenGotoxy(13, 4);
    printf("  / ____|  /\\   | |\\ \\    / /  ____|     / ____|\n");
    screenGotoxy(13, 5);
    printf(" | (___   /  \\  | | \\ \\  / /| |__ ______| |     \n");
    screenGotoxy(13, 6);
    printf("  \\___ \\ / /\\ \\ | |  \\ \\/ / |  __|______| |     \n");
    screenGotoxy(13, 7);
    printf("  ____) / ____ \\| |___\\  /  | |____     | |____ \n");
    screenGotoxy(13, 8);
    printf(" |_____/_/    \\_\\______\\/   |______|     \\_____|\n\n");
    screenGotoxy(13, 9);
    printf("                  QUEM PUDER!\n");
    screenGotoxy(13, 13);
    printf("                1- Jogar\n");
    screenGotoxy(13, 15);
    printf("                2- Como jogar\n");
    screenGotoxy(13, 17);
    printf("                3- Ranking");
    screenGotoxy(13, 19);
    printf("                4- Creditos\n");
    screenGotoxy(13, 21);
    printf("                5- Sair\n\n");
}

void tutorial()
{
    screenClear();
    screenDrawBorders();
    screenUpdate();

    screenGotoxy(13, 8);
    printf("Use as telcas A e D para se mover");
    screenGotoxy(13, 9);
    printf("         [_]");

    screenGotoxy(13, 12);
    printf("Você receberá uma proposição aleatória");
    screenGotoxy(13, 13);
    printf("           Expressão: V → V          ");

    screenGotoxy(13, 15);
    printf("Colete a respota correta");

    screenGotoxy(13, 17);
    printf("    [V]          [F]");

    screenGotoxy(13, 22);
    printf("Pressione qualquer tecla para voltar");
    getchar();
}

void creditos()
{
    screenClear();
    screenDrawBorders();
    screenUpdate();

    screenGotoxy(13, 5);
    printf("Criado por");
    getchar();
}

void sair()
{
    screenClear();
    screenDrawBorders();

    screenGotoxy(65, 22);
    printf("Saindo...");

    screenUpdate();
    sleep(1);
    screenClear();
    exit(0);
}

void telaDerrota()
{
    screenClear();
    screenDrawBorders();
    screenUpdate();

    while (1)
    {
        screenGotoxy(MAXX / 2, MAXY / 2);
        printf("VOCÊ REPROVOU! TENTE NOVAMENTE PROXIMO PERIODO!");
        screenGotoxy(34, 20);
        printf("Sua pontuação foi: "); // Mostra a pontuação do jogador

        // Printa botão de jogar novamente
        screenGotoxy(MAXX / 2 - 13, 32);
        printf("ESPAÇO para jogar novamente");

        // Printa botão de ir para o menu
        screenGotoxy(MAXX / 2 - 11, 33);
        printf("ENTER para ir ao menu");

        // Vai pegar as teclas pressionadas
        if (keyhit())
        {
            int ch = readch();
            if (ch == 32)
            {                  // Espaço
                iniciarGame(); // Joga novamente
                break;
            }
            else if (ch == 10)
            {                  // Enter
                telaInicial(); // Sai para o menu
                break;
            }
        }
    }
}

int telaInicial() // Função para iniciar o menu
{
    nomeJogador(); // Inicia perguntando o nome do player

    screenInit(1);  // Inicia a Tela
    keyboardInit(); // Inicia o teclado

    while (1)
    {
        imprimirMenu(); // Imprime as opções do menu inicial
        int opcao;
        opcao = getchar();
        switch (opcao) // Switch das opções
        {
        case '1':
            iniciarGame(); // Inicia o jogo
            break;
        case '2':
            tutorial(); // Vai a tela de tutorial
            break;
        case '3':
            mostrarRanking(); // Mostra os melhores jogadores
            break;
        case '4':
            creditos(); // Mostra os creditos do jogo
            break;
        case '5':
            sair(); // Sai do jogo
            break;
        }
    }
    return 0;
}