#include <stdio.h>

#define TAM 10
#define NAVIO 3
#define HABILIDADE 5
#define TAM_HAB 5

int tabuleiro[TAM][TAM] = {0};

// Verifica se pode posicionar o navio
int podePosicionar(int linha, int coluna, int tamanho, char direcao) {
    for (int i = 0; i < tamanho; i++) {
        int l = linha, c = coluna;
        if (direcao == 'H') c += i;
        else if (direcao == 'V') l += i;
        else if (direcao == 'D') { l += i; c += i; }
        else if (direcao == 'E') { l += i; c -= i; }

        if (l < 0 || l >= TAM || c < 0 || c >= TAM || tabuleiro[l][c] != 0)
            return 0;
    }
    return 1;
}

// Posiciona navio no tabuleiro
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

// Cria matriz de habilidade em forma de cone
void criarCone(int matriz[TAM_HAB][TAM_HAB]) {
    for (int i = 0; i < TAM_HAB; i++) {
        for (int j = 0; j < TAM_HAB; j++) {
            matriz[i][j] = 0;
            int centro = TAM_HAB / 2;
            if (j >= centro - i && j <= centro + i)
                matriz[i][j] = 1;
        }
    }
}

// Cria matriz de habilidade em forma de cruz
void criarCruz(int matriz[TAM_HAB][TAM_HAB]) {
    for (int i = 0; i < TAM_HAB; i++) {
        for (int j = 0; j < TAM_HAB; j++) {
            matriz[i][j] = (i == TAM_HAB / 2 || j == TAM_HAB / 2) ? 1 : 0;
        }
    }
}

// Cria matriz de habilidade em forma de octaedro (losango)
void criarOctaedro(int matriz[TAM_HAB][TAM_HAB]) {
    for (int i = 0; i < TAM_HAB; i++) {
        for (int j = 0; j < TAM_HAB; j++) {
            int centro = TAM_HAB / 2;
            matriz[i][j] = (abs(i - centro) + abs(j - centro) <= centro) ? 1 : 0;
        }
    }
}

// Aplica habilidade no tabuleiro
void aplicarHabilidade(int origem_linha, int origem_coluna, int matriz[TAM_HAB][TAM_HAB]) {
    int offset = TAM_HAB / 2;

    for (int i = 0; i < TAM_HAB; i++) {
        for (int j = 0; j < TAM_HAB; j++) {
            int linha = origem_linha - offset + i;
            int coluna = origem_coluna - offset + j;

            if (linha >= 0 && linha < TAM && coluna >= 0 && coluna < TAM) {
                if (matriz[i][j] == 1 && tabuleiro[linha][coluna] != NAVIO) {
                    tabuleiro[linha][coluna] = HABILIDADE;
                }
            }
        }
    }
}

// Exibe o tabuleiro com números
void exibirTabuleiro() {
    printf("    A B C D E F G H I J\n");
    for (int i = 0; i < TAM; i++) {
        printf("%2d ", i + 1);
        for (int j = 0; j < TAM; j++) {
            printf(" %d", tabuleiro[i][j]);
        }
        printf("\n");
    }
}

int main() {
// Posicionar navios
    if (podePosicionar(1, 1, 3, 'H'))
        posicionarNavio(1, 1, 3, 'H');

    if (podePosicionar(4, 6, 3, 'V'))
        posicionarNavio(4, 6, 3, 'V');

    if (podePosicionar(0, 0, 3, 'D'))
        posicionarNavio(0, 0, 3, 'D');

    if (podePosicionar(0, 9, 3, 'E'))
        posicionarNavio(0, 9, 3, 'E');

// Criar e aplicar habilidades
    int cone[TAM_HAB][TAM_HAB], cruz[TAM_HAB][TAM_HAB], octaedro[TAM_HAB][TAM_HAB];

    criarCone(cone);
    criarCruz(cruz);
    criarOctaedro(octaedro);

    aplicarHabilidade(6, 6, cone);      // Centro do cone
    aplicarHabilidade(2, 7, cruz);      // Centro da cruz
    aplicarHabilidade(8, 4, octaedro);  // Centro do octaedro

// Exibir o tabuleiro final
    printf("\n--- TABULEIRO FINAL ---\n\n");
    exibirTabuleiro();

    return 0;
}