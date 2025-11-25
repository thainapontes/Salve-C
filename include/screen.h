/**
 * screen.h
 * Criado em 23 de Agosto de 2023
 * Autor: Tiago Barros
 * Baseado no "Curso De C para C++ - 2002"
 * Referência: https://en.wikipedia.org/wiki/ANSI_escape_code
 */

#ifndef __SCREEN_H__
#define __SCREEN_H__

#include <stdio.h>

// Sequências de controle do terminal
#define ESC "\033"
#define NORMALTEXT "[0m"
#define BOLDTEXT "[1m"
#define ITALICTEXT "[3m"
#define BLINKTEXT "[5m"
#define REVERSETEXT "[7m"
#define HOMECURSOR "[f"
#define SHOWCURSOR "[?25h"
#define HIDECURSOR "[?25l"
#define CLEARSCREEN "[2J"

// Desenho de CAIXAS (BOX Drawing) - Terminais tipo Unix
#define BOX_ENABLE "(0"
#define BOX_DISABLE "(B"
#define BOX_VLINE 0x78	  // Linha Vertical
#define BOX_HLINE 0x71	  // Linha Horizontal
#define BOX_UPLEFT 0x6C	  // Canto Superior Esquerdo
#define BOX_UPRIGHT 0x6B  // Canto Superior Direito
#define BOX_DWNLEFT 0x6D  // Canto Inferior Esquerdo
#define BOX_DWNRIGHT 0x6A // Canto Inferior Direito
#define BOX_CROSS 0x6E	  // Cruz (interseção)
#define BOX_TLEFT 0X74	  // T para a Esquerda
#define BOX_TRIGHT 0X75	  // T para a Direita
#define BOX_TUP 0X77	  // T para Cima
#define BOX_TDOWN 0X76	  // T para Baixo

#define BOX_DIAMOND 0x60 // Diamante
#define BOX_BLOCK 0x61	 // Bloco
#define BOX_DOT 0x7E	 // Ponto

// Constantes de tela (screen constants)
#define SCRSTARTX 3 // Posições inicial e final da tela para o jogo
#define SCRENDX 75	// Isso significa a área que pode ser desenhada
#define SCRSTARTY 1
#define SCRENDY 23

#define MINX 1	 // Posição horizontal mínima da tela
#define MINY 1	 // Posição vertical mínima da tela
#define MAXX 100 // Posição horizontal máxima da tela
#define MAXY 35	 // Posição vertical máxima da tela

/**
 * Tipo de Cores de Tela (Screen Colors type)
 */
typedef enum
{
	BLACK,
	RED,
	GREEN,
	BROWN,
	BLUE,
	MAGENTA,
	CYAN,
	LIGHTGRAY,
	DARKGRAY,
	LIGHTRED,
	LIGHTGREEN,
	YELLOW,
	LIGHTBLUE,
	LIGHTMAGENTA,
	LIGHTCYAN,
	WHITE
} screenColor;

/**
 * Move o cursor para a posição (0,0)
 */
static inline void screenHomeCursor()
{
	printf("%s%s", ESC, HOMECURSOR);
}

/**
 * Mostra o cursor
 */
static inline void screenShowCursor()
{
	printf("%s%s", ESC, SHOWCURSOR);
}

/**
 * Esconde o cursor
 */
static inline void screenHideCursor()
{
	printf("%s%s", ESC, HIDECURSOR);
}

/**
 * Limpa a tela
 */
static inline void screenClear()
{
	screenHomeCursor();
	printf("%s%s", ESC, CLEARSCREEN);
}

/**
 * Atualiza a tela imediatamente
 */
static inline void screenUpdate()
{
	fflush(stdout);
}

/**
 * Define o modo de tela para "normal"
 */
static inline void screenSetNormal()
{
	printf("%s%s", ESC, NORMALTEXT);
}

/**
 * Define o modo de tela para "negrito" (bold)
 */
static inline void screenSetBold()
{
	printf("%s%s", ESC, BOLDTEXT);
}

/**
 * Define o modo de tela para "piscando" (blink)
 */
static inline void screenSetBlink()
{
	printf("%s%s", ESC, BLINKTEXT);
}

/**
 * Define o modo de tela para "reverso" (cores invertidas)
 */
static inline void screenSetReverse()
{
	printf("%s%s", ESC, REVERSETEXT);
}

/**
 * Habilita os caracteres de CAIXA (BOX) no terminal
 */
static inline void screenBoxEnable()
{
	printf("%s%s", ESC, BOX_ENABLE);
}

/**
 * Desabilita os caracteres de CAIXA (BOX) no terminal
 */
static inline void screenBoxDisable()
{
	printf("%s%s", ESC, BOX_DISABLE);
}

/**
 * Desenha bordas na tela usando caracteres de caixa (BOX drawing)
 */
void screenDrawBorders();

/**
 * Limpa a tela, define o cursor para a posição inicial (home)
 * e opcionalmente desenha bordas nela.
 * * @param drawBorders se não for zero, desenha bordas na tela.
 */
void screenInit(int drawBorders);

/**
 * Limpa a tela e restaura para o estado inicial.
 */
void screenDestroy();

/**
 * Move o cursor para a posição (x,y)
 * @param x posição x
 * @param y posição y
 */

void screenGotoxy(int x, int y);

/**
 * Define as cores do texto
 * @param fg cor de primeiro plano (foreground), pode assumir valores de BLACK a WHITE
 * @param bg cor de fundo (background), pode assumir valores de BLACK a LIGHTGRAY
 */
void screenSetColor(screenColor fg, screenColor bg);

#endif /* __SCREEN_H__ */
