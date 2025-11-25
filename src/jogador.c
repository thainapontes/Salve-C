#include "jogador.h"
#include <string.h>

static Jogador jogador; // Struct do jogador definida em jogador.h

// Inicia os dados do jogador
void iniciarJogador(const char *apelido)
{
    jogador.vidas = 5;
    jogador.pontos = 0;
    strncpy(jogador.apelido, apelido, TAM_MAX_APELIDO - 1);
    jogador.apelido[TAM_MAX_APELIDO - 1] = '\0';
}

// Busca os dados do jogador através do ponteiro
Jogador *getJogador()
{
    return &jogador;
}

// Manipula a quantidade de vidas
void setVidas(int vidas)
{
    jogador.vidas = vidas;
}

// Manipula a quantidade de pontos
void setPontos(int pontos)
{
    jogador.pontos = pontos;
}

void setApelido(const char *apelido)
{
    strncpy(jogador.apelido, apelido, TAM_MAX_APELIDO - 1);
    jogador.apelido[TAM_MAX_APELIDO - 1] = '\0';
}
