#include <stdio.h>

#define TAM 10
#define NAVIO 3

int tabuleiro[TAM][TAM] = {0};

// Função para verificar se é possível posicionar o navio
int podePosicionar(int linha, int coluna, int tamanho, char direcao) {
    for (int i = 0; i < tamanho; i++) {
        int l = linha, c = coluna;
        if (direcao == 'H') c += i;
        else if (direcao == 'V') l += i;
        else if (direcao == 'D') { l += i; c += i; }
        else if (direcao == 'E') { l += i; c -= i; }

        if (l < 0 || l >= TAM || c < 0 || c >= TAM || tabuleiro[l][c] != 0)
            return 0;  // falso
    }
    return 1;  // verdadeiro
}

// Função para posicionar o navio
void posicionarNavio(int linha, int coluna, int tamanho, char direcao) {
    for (int i = 0; i < tamanho; i++) {
        int l = linha, c = coluna;
        if (direcao == 'H') c += i;
        else if (direcao == 'V') l += i;
        else if (direcao == 'D') { l += i; c += i; }
        else if (direcao == 'E') { l += i; c -= i; }

        tabuleiro[l][c] = NAVIO;
    }
}

int main() {
    printf("--- TABULEIRO BATALHA NAVAL ---\n\n");
    printf("    A B C D E F G H I J\n");

// Posicionando os navios
// Navio 1 - Horizontal
    if (podePosicionar(1, 1, 3, 'H'))
        posicionarNavio(1, 1, 3, 'H');

// Navio 2 - Vertical
    if (podePosicionar(4, 6, 3, 'V'))
        posicionarNavio(4, 6, 3, 'V');

    // Navio 3 - Diagonal Principal
    if (podePosicionar(0, 0, 3, 'D'))
        posicionarNavio(0, 0, 3, 'D');

// Navio 4 - Diagonal Secundária
    if (podePosicionar(0, 9, 3, 'E'))
        posicionarNavio(0, 9, 3, 'E');

// Exibir o tabuleiro
    for (int i = 0; i < TAM; i++) {
        printf("%2d ", i + 1);
        for (int j = 0; j < TAM; j++) {
            printf(" %d", tabuleiro[i][j]);
        }
        printf("\n");
    }

    return 0;
}