#include "batalha.h"
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <string.h>

#ifdef _WIN32
  #include <windows.h>
  #include <conio.h>
#else
  #include <unistd.h>
  #include <sys/types.h>
  #include <sys/time.h>
  #include <sys/select.h>
#endif

void animaSpinner(const char *msg, int duracao_ms) 
{
    const char frames[] = "|/-\\";
    int frames_n = 4;
    int passos = duracao_ms / 80;
    for (int i = 0; i < passos; i++) 
    {
        printf("\r%s %c ", msg, frames[i % frames_n]);
        fflush(stdout);
        if (i % 6 == 0) beep_curto();
        Sleep(80);
    }
    printf("\r%-40s\r", "");
}

void emoticonCentralizado(int largura) 
{
    const char *art[] = 
    {
        "   ███████████████████████   ",
        "   █                     █   ",
        "   █      Bem vindo!     █   ",
        "   █     ¯//_(ツ)_//¯     █   ",
        "   █                     █   ",
        "   ███████████████████████   "
    };
    int linhas = sizeof(art)/sizeof(art[0]);
    int pad = 0;
    if (largura > 0) 
    {
        pad = (largura - (int)strlen(art[0]))/2;
        if (pad < 0) pad = 0;
    }
    for (int i = 0; i < linhas; i++) {
        for (int s = 0; s < pad; s++) putchar(' ');
        puts(art[i]);
    }
}

char **criarMatriz(int N) 
{
    char **m = malloc(N * sizeof(char*));
    if (!m) return NULL;
    for (int i = 0; i < N; i++) 
    {
        m[i] = malloc(N * sizeof(char));
        if (!m[i]) 
        {
            for (int k = 0; k < i; k++)
                free(m[k]);
            free(m);
            return NULL;
        }
    }
    return m;
}

void liberarMatriz(char **m, int N) 
{
    for (int i = 0; i < N; i++)
        free(m[i]);
    free(m);
}

void cabecalho(const char *titulo) 
{
    int w = 62;
    for (int i = 0; i < w; i++) putchar('=');
    printf("\n  %s\n", titulo);
    for (int i = 0; i < w; i++) putchar('=');
    putchar('\n');
}

void instrucoesSaida(int N) 
{
    printf("\nINSTRUÇÕES:\n");
    printf("- Para sair a qualquer momento: digite um número maior que %d na hora de digitar a linha ou a coluna.\n", N);
    printf("- Digite linha e coluna como números inteiros entre 1 e %d.\n", N);
    printf("- Você verá 'X' se acertou e 'O' se errou no tabuleiro.\n\n");
}

void inicializarTabuleiro(char **tab, int N, char simbolo) 
{
    for (int i = 0; i < N; i++) 
    {
        for (int j = 0; j < N; j++) 
        {
            tab[i][j] = simbolo;
        }
    }
}

void posicionarNavios(char **tab, int N, int navios) 
{
    int colocados = 0;
    while (colocados < navios) 
    {
        int r = rand() % N;
        int c = rand() % N;
        if (tab[r][c] == '~') 
        { 
            tab[r][c] = 'S';
            colocados++;
        }
    }
}

void mostrarTabuleiro(char **tab, int N) 
{
    printf("   ");
    for (int j = 0; j < N; j++) printf("%2d ", j+1);
    printf("\n");
    for (int i = 0; i < N; i++) 
    {
        printf("%2d ", i+1);
        for (int j = 0; j < N; j++) 
        {
            char ch = tab[i][j];
            if (ch == 'S') ch = '~';
            printf(" %c ", ch);
        }
        printf("\n");
    }
}

int verificarAtaque(char **tab, int N, int linha, int coluna) 
{
    if (linha < 0 || linha >= N || coluna < 0 || coluna >= N)
        return -1;
    
    char atual = tab[linha][coluna];
    if (atual == 'X' || atual == 'O')
        return 2; 
    
    if (atual == 'S') 
    {
        tab[linha][coluna] = 'X'; 
        return 1;
    } else {
        tab[linha][coluna] = 'O'; 
        return 0;
    }
}

void registrarResultado(const char *nome, int afundados, int venceu) 
{
    FILE *f = fopen("resultados.txt", "a");
    if (!f) return;
    fprintf(f, "Marinheiro %s | Navios afundados: %d | Resultado: %s\n",
            nome, afundados, venceu ? "VENCEU" : "PERDEU");
    fclose(f);
}

char *lerLinhaDinamica(void) 
{
    int cap = 64;
    int len = 0;
    char *s = malloc(cap);
    if (!s) return NULL;
    int c;
    while ((c = getchar()) != '\n' && c != EOF) 
    {
        s[len++] = (char)c;
        if (len + 1 >= cap) 
        {
            cap *= 2;
            char *t = realloc(s, cap);
            if (!t) { free(s); return NULL; }
            s = t;
        }
    }
    s[len] = '\0';
    return s;
}

void limparBuffer(void) 
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }
}

void beep_curto() 
{
    #ifdef _WIN32
        Beep(750, 120);
    #else
        putchar('\a');
        fflush(stdout);
    #endif
}
