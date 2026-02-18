# Batalha Naval
Seja muito bem-vindo ao Batalha Naval, um jogo desenvolvido com muito carinho, paciência e plays de rock do Spotify em linguagem C.

Esse é um jogo de Batalha Naval que você joga com nosso algoritmo extremamente capaz em te destruir!

Funciona assim:
. Você vai digitar seu nome, escolher o tamanho do tabuleiro (que é o nosso mar), o número de tentativas e, pronto!
. O mar é uma matriz NxN. Se não lembra o que é uma matriz, é como se fosse um tabuleiro de xadrez.
. Cada posição da matriz pode esconder um navio inimigo.
. Em cada rodada, digite a linha e a coluna onde quer atacar.
. O jogo te dirá se foi acerto ou erro.

O jogo termina quando:
. Você afundar todos os navios (parabéns!).
. Quando suas tentativas acabarem (vida que segue).
. Ou, se quiser sair antes, basta digitar um número maior que o tamanho do tabuleiro.

Quer saber se é o bichão mesmo?
. Dá uma olhadinha no arquivo resultados.txt, lá vai ficar registrado seu nome, quantos navios você afundou, e se saiu como herói ou como mais um que foi de arrasto. 
> Ah, e se conseguir vencer na primeira tentativa, corre para pegar sua loto, porque você não pode desperdiçar seu dia de sorte jogando um jogo em C 

Como fazer o jogo funcionar no Windows:
1. Baixe a pasta que está esse arquivo e coloque em algum lugar que você lembre (tipo na Área de Trabalho).
2. Copie o endereço da pasta (lá em cima, na barra do Explorer).
3. Abra o Prompt de Comando (CMD) do Windows.
4. Dentro do CMD, digite: cd "COLE AQUI O CAMINHO DA SUA PASTA" e pressione Enter.
5. Agora, compile o código com: gcc main.c batalha.c -o batalha.exe
6. Finalmente, digite: batalha.exe.

Como fazer o jogo funcionar no Linux:
1. Baixe a pasta que está esse arquivo e coloque em algum lugar que você lembre (tipo na Área de Trabalho).
2. Copie o endereço da pasta (lá em cima, na barra do Explorer).
3. Abra o Terminal (Ctrl + Alt + T).
4. Dentro do CMD, digite: cd ~COLE AQUI O CAMINHO DA SUA PASTA e pressione Enter.
5. Agora, compile o código com: gcc main.c batalha.c -o batalha.exe
6. Finalmente, digite: ./batalha

Como fazer o jogo funcionar no macOS:
1. Baixe a pasta que está esse arquivo e coloque em algum lugar que você lembre (tipo no Desktop).
2. Copie o endereço da pasta (lá em cima, na barra do Explorer).
3. Abra o Terminal (Cmd + Espaço → digite “Terminal” → Enter).
4. Dentro do CMD, digite: cd ~COLE AQUI O CAMINHO DA SUA PASTA e pressione Enter.
5. Agora, compile o código com: gcc main.c batalha.c -o batalha.exe
6. Finalmente, digite: ./batalha




SAC
- AH, Henrique! O meu não deu certo... O que aconteceu?
Uai, deveria ter dado certo! Um problema possível é que sua máquina não tem o GCC, caso não o tenha, basta seguir os seguintes passos ;)

Windows
1. Acesse: https://www.mingw-w64.org/downloads/
2. Baixe o instalador MinGW-w64 GCC
3. Durante a instalação, escolha a última disponível, arquitetura x86_64
4. Instale e copie o caminho da pasta bin
5. Adicione esse caminho à variável PATH
6. Feche e reabra o CMD
7. Verifique se funcionou digitando no CMD: gcc --version

Linux
1. O GCC já costuma vir instalado. Caso não, digite no seu terminal de comando: sudo apt update (TECLA ENTER) sudo apt install build-essential
2. Para verificar, digite: gcc --version

macOS 
1. Abra o Terminal.
2. Instale as ferramentas de desenvolvimento: xcode-select --install
3. Para verificar, digite: gcc --version

Ainda NÃO DEU CERTO? Então é só me enviar um e-mail que te dou uma moral hehe 
henriquelimagusmao@ufmg.br




© Créditos creditosos
Desenvolvido por: Henrique Lima Gusmão
Programação e Desenvolvimento de Software I - UFMG 2025/2 TF
