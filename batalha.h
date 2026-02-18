#ifndef BATALHA_H
#define BATALHA_H
#include <stdio.h>
#include <stdlib.h>

void inicializarTabuleiro(char **tab, int N, char simbolo);
void posicionarNavios(char **tab, int N, int navios);
void mostrarTabuleiro(char **tab, int N);
void registrarResultado(const char *nome, int afundados, int venceu);
int verificarAtaque(char **tab, int N, int linha, int coluna);
void limparBuffer(void);
char *lerLinhaDinamica(void);
void beep_curto(void);
void animaSpinner(const char *msg, int duracao_ms);
void emoticonCentralizado(int largura);
void cabecalho(const char *titulo);
void instrucoesSaida(int N);
char **criarMatriz(int N);
void liberarMatriz(char **m, int N);

#endif 
