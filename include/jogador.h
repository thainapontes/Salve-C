#ifndef JOGADOR_H
#define JOGADOR_H

#define TAM_MAX_APELIDO 20
typedef struct
{
    int vidas;
    int pontos;
    char apelido[TAM_MAX_APELIDO];
} Jogador;

void iniciarJogador(const char *apelido);

Jogador *getJogador();

void setVidas(int vidas);

void setPontos(int pontos);

void setApelido(const char *apelido);

#endif