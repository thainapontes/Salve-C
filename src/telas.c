#include "screen.h"
#include "keyboard.h"
#include "timer.h"
#include "main.h"

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

void imprimirMenu()
{
    screenClear();
    screenDrawBorders();

    screenGotoxy(13, 8);
    printf("   _____         _ __      ________       _____ \n");
    screenGotoxy(13, 9);
    printf("  / ____|  /\\   | |\\ \\    / /  ____|     / ____|\n");
    screenGotoxy(13, 10);
    printf(" | (___   /  \\  | | \\ \\  / /| |__ ______| |     \n");
    screenGotoxy(13, 11);
    printf("  \\___ \\ / /\\ \\ | |  \\ \\/ / |  __|______| |     \n");
    screenGotoxy(13, 12);
    printf("  ____) / ____ \\| |___\\  /  | |____     | |____ \n");
    screenGotoxy(13, 13);
    printf(" |_____/_/    \\_\\______\\/   |______|     \\_____|\n\n");
    screenGotoxy(13, 14);
    printf("                  QUEM PUDER!\n");
    screenGotoxy(13, 16);
    printf("                1- Jogar\n");
    screenGotoxy(13, 18);
    printf("                2- Como jogar\n");
    screenGotoxy(13, 20);
    printf("                3- Creditos\n");
    screenGotoxy(13, 22);
    printf("                4- Sair\n\n");
}

void tutorial()
{
    screenClear();
    screenDrawBorders();

    // Movimentar
    screenGotoxy(7, 8);
    printf("  Use A  D para se mover");

    // Proposições
    screenGotoxy(55, 8);
    printf("Você receberá uma proposição aleatória");
    screenGotoxy(55, 11);
    printf("           Expressão: ¬F → F          ");

    // Interface do jogo

    // Voltar ao menu
    screenGotoxy((MAXX / 2) - 15, MAXY - 2);
    printf("Pressione ENTER para voltar");
    if (keyhit())
    {
        int tecla = readch();
        if (tecla == '\n')
        {
            menuOpcoes();
        }
    }
}

void creditos()
{
    screenClear();
    screenDrawBorders();

    screenGotoxy(45, 5);
    printf("Criado por");
}

void sair()
{
    screenClear();
    screenDrawBorders();

    screenGotoxy((MAXX / 2) - 5, (MAXY / 2));
    printf("Saindo...");

    screenUpdate();
    sleep(1);
    screenClear();
    exit(0);
}

void telaDerrota()
{
    creenClear();
    screenDrawBorders();

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
            {                  // Tecla espaço
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
    screenInit(1);  // Inicia a Tela
    keyboardInit(); // Inicia o teclado

    while (1)
    {
        imprimirMenu();     // Imprime as opções do menu inicial
        int op = getchar(); // lê um char para  switch
        switch (op)         // Switch das opções
        {
        case '1':
            iniciarGame(); // Inicia o jogo
            break;
        case '2':
            tutorial(); // Vai a tela de tutorial
            break;
        case '3':
            creditos(); // Mostra os creditos do jogo
            break;
        case '4':
            sair(); // Sai do jogo
            break;
        }
    }
    return 0;
}