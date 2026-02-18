#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <locale.h>

#ifdef _WIN32
  #include <windows.h>
  #include <conio.h> 
  #define CLEAR_CMD "cls"
#else
  #include <unistd.h>
  #include <termios.h>
  #include <sys/select.h>
  #define Sleep(ms) usleep((ms)*1000)
  #define CLEAR_CMD "clear"
#endif
#include "batalha.h"

int main(int argc, char *argv[]) {
    #ifdef _WIN32
        SetConsoleOutputCP(CP_UTF8);
        SetConsoleCP(CP_UTF8);
        system("chcp 65001 > nul");
    #else
        setlocale(LC_ALL, "");
    #endif
        srand((unsigned) time(NULL));
        system(CLEAR_CMD);
        emoticonCentralizado(80);
        beep_curto();
        Sleep(500);
        printf("\nBem-vindo ao jogo Batalha Naval, Marinheiro!\n");
        Sleep(400);
        printf("Essa batalha foi diplomaticamente elaborada por Henrique Lima Gusmão.\n");
        Sleep(400);
        printf("\nComo podemos te chamar? \n> ");
        char *nome = lerLinhaDinamica();
        if (!nome) { printf("Pelo visto errou até seu nome! Provavelmente o jogo é de mais para você... Encerrando.\n"); return 1; }

        printf("\nPreparando o jogo...\n");
        animaSpinner("Carregando", 1000);
        beep_curto();

    int N = 0;
    while (1) {
        printf("\nMe fala um número para ser o tamanho do tabuleiro NxN\n> ");
        if (scanf("%d", &N) != 1) {
            printf("Igh... Tenta digitar um número inteiro.\n");
            limparBuffer();
            continue;
        }
        if (N < 2 || N > 30) {
            printf("Escolha um número entre 2 e 30.\n");
            continue;
        }
        limparBuffer();
        break;
    }

    int navios = 0;
    while (1) {
        printf("Quantos navios você vai querer posicionar para o ataque? (recomendamos: <= %d): ", N*N/6);
        if (scanf("%d", &navios) != 1) { printf("Igh... Deu erro, tenta denovo! \n"); limparBuffer(); continue; }
        if (navios <= 0 || navios > N*N) { printf("Igh... Deu erro, tenta denovo!\n"); limparBuffer(); continue; }
        limparBuffer();
        break;
    }

    int chances = 0;
    while (1) {
        printf("Quantas chances você quer ter (recomendamos: %d): ", navios*3);
        if (scanf("%d", &chances) != 1) { printf("Igh... Deu erro, tenta denovo!\n"); limparBuffer(); continue; }
        if (chances <= 0) { printf("Igh... Deu erro! O número de chances tem que ser > 0.\n"); limparBuffer(); continue; }
        limparBuffer();
        break;
    }

    system(CLEAR_CMD);
    cabecalho("Só para dar um recap, vamos batalhar seguindo isso aqui: ");
    printf("Marinheiro %s\n", nome);
    printf("O tabuleiro vai ser do tamanho: %dx%d | Navios: %d | Chances: %d\n", N, N, navios, chances);
    instrucoesSaida(N);
    printf("Assim que apertar Enter começaremos o jogo...");
    limparBuffer();

    char **tab = criarMatriz(N);
    if (!tab) { printf("Igh... Deu erro na memória\n"); free(nome); return 1; }
    inicializarTabuleiro(tab, N, '~');
    posicionarNavios(tab, N, navios);

    int afundados = 0;
    int jogadas = 0;
    while (chances > 0 && afundados < navios) 
    {
        system(CLEAR_CMD);
        cabecalho("BATALHA NAVAL - Em jogo");
        printf("Marinheiro %s   |   Navios afundados: %d / %d   |   Chances restantes: %d\n\n",
               nome, afundados, navios, chances);
        mostrarTabuleiro(tab, N);

        int linha = -1, coluna = -1;
        while (1) {
            printf("\nDigite a linha (1..%d) ou um número > %d para sair: ", N, N);
            if (scanf("%d", &linha) != 1) { printf("Igh... Deu erro, tenta denovo!\n"); limparBuffer(); continue; }
            limparBuffer();
            if (linha > N) { printf("Poxa... O campo de batalha não é para todos mesmo \n\nEncerrando partida...\n"); goto fim_partida; }
            if (linha < 1 || linha > N) { printf("Linha inválida. Tente novamente.\n"); continue; }
            break;
        }

        while (1) {
            printf("Digite a coluna (1..%d) ou número > %d para sair: ", N, N);
            if (scanf("%d", &coluna) != 1) { printf("Igh... Deu erro, tenta denovo!\n"); limparBuffer(); continue; }
            limparBuffer();
            if (coluna > N) { printf("Poxa... O campo de batalha não é para todos mesmo \n\nEncerrando partida...\n"); goto fim_partida; }
            if (coluna < 1 || coluna > N) { printf("Igh... Deu erro, tenta denovo!\n"); continue; }
            break;
        }

        linha--; coluna--;

        int res = verificarAtaque(tab, N, linha, coluna);
        if (res == -1) {
            printf("Igh... Deu erro, tenta denovo!\n");
            Sleep(800);
            continue;
        } else if (res == 2) {
            printf("Atirando em cova já aberta? Perdeu uma chance.\n");
            beep_curto();
            chances--;
        } else if (res == 1) {
            beep_curto();
            printf(">>> EITA! Navio atingido!\n");
            afundados++;
            chances--;
        } else if (res == 0) {
            beep_curto();
            printf(">>> Atirando em peixe? Tem formas melhores de se pescar. \n");
            chances--;
        }
        jogadas++;
        Sleep(1800);
    }

    fim_partida:
    system(CLEAR_CMD);
    cabecalho("Resultado Final");
    mostrarTabuleiro(tab, N);
    if (afundados == navios) {
        printf("\nParabéns, %s! Você AFUNDOU TODOS os navios!\n", nome);
        beep_curto();
    } else {
        printf("\nNossa batalha fica por aqui, Marinheiro %s. Afundamos %d de %d navios\n", nome, afundados, navios);
    }

    registrarResultado(nome, afundados, (afundados==navios));
    printf("\nAcabamos de gravar essa sua partida no arquivo 'resultados.txt'. Depois corre lá para conferir os últimos players.\n");

    printf("\nBora jogar denovo? (S para sim): ");
    int resposta = getchar();
    if (resposta == '\n') resposta = getchar();
    if (resposta == 'S' || resposta == 's') {
        printf("Reinicie o programa para jogar outra vez.\n");
    }

    liberarMatriz(tab, N);
    free(nome);
    return 0;
}
