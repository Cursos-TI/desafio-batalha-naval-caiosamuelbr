#include <stdio.h>
#include <stdbool.h> // Biblioteca para usar o tipo de dado 'bool' (true/false)

// --- Requisitos não funcionais: Legibilidade e Manutenção ---
// Definindo constantes para o tamanho do tabuleiro e dos navios.
// Isso torna o código mais fácil de ler e modificar no futuro.
#define TAMANHO_TABULEIRO 10
#define TAMANHO_NAVIO 3

// --- Protótipos das Funções (Boas práticas de organização) ---
void inicializarTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]);
void exibirTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]);
bool validarPosicao(int tab[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int lin, int col, int tam, char orientacao);

int main() {
    // --- 1. Criar um Tabuleiro 10x10 ---
    // Declara a matriz que servirá como nosso tabuleiro.
    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];

    // Inicializa todas as posições do tabuleiro com 0 (água).
    inicializarTabuleiro(tabuleiro);

    // --- 2. Posicionar Quatro Navios ---
    // As coordenadas e orientações são definidas diretamente no código.
    // Lembre-se que em C, os índices de arrays começam em 0.

    // --- NAVIO 1: HORIZONTAL ---
    int navio1_linha = 1;
    int navio1_coluna = 1;
    if (validarPosicao(tabuleiro, navio1_linha, navio1_coluna, TAMANHO_NAVIO, 'H')) {
        for (int i = 0; i < TAMANHO_NAVIO; i++) {
            tabuleiro[navio1_linha][navio1_coluna + i] = 3;
        }
        printf("Navio 1 (Horizontal) posicionado com sucesso!\n");
    } else {
        printf("Erro: Nao foi possivel posicionar o Navio 1 (Horizontal).\n");
    }

    // --- NAVIO 2: VERTICAL ---
    int navio2_linha = 3;
    int navio2_coluna = 8;
    if (validarPosicao(tabuleiro, navio2_linha, navio2_coluna, TAMANHO_NAVIO, 'V')) {
        for (int i = 0; i < TAMANHO_NAVIO; i++) {
            tabuleiro[navio2_linha + i][navio2_coluna] = 3;
        }
        printf("Navio 2 (Vertical) posicionado com sucesso!\n");
    } else {
        printf("Erro: Nao foi possivel posicionar o Navio 2 (Vertical).\n");
    }

    // --- NAVIO 3: DIAGONAL (Principal: Topo-Esquerda para Baixo-Direita) ---
    int navio3_linha = 4;
    int navio3_coluna = 1;
    if (validarPosicao(tabuleiro, navio3_linha, navio3_coluna, TAMANHO_NAVIO, 'P')) { // 'P' de Principal
        for (int i = 0; i < TAMANHO_NAVIO; i++) {
            // Incrementa tanto a linha quanto a coluna para criar a diagonal.
            tabuleiro[navio3_linha + i][navio3_coluna + i] = 3;
        }
        printf("Navio 3 (Diagonal Principal) posicionado com sucesso!\n");
    } else {
        printf("Erro: Nao foi possivel posicionar o Navio 3 (Diagonal Principal).\n");
    }

    // --- NAVIO 4: DIAGONAL (Secundária: Topo-Direita para Baixo-Esquerda) ---
    int navio4_linha = 0;
    int navio4_coluna = 8;
     if (validarPosicao(tabuleiro, navio4_linha, navio4_coluna, TAMANHO_NAVIO, 'S')) { // 'S' de Secundária
        for (int i = 0; i < TAMANHO_NAVIO; i++) {
            // Incrementa a linha, mas decrementa a coluna.
            tabuleiro[navio4_linha + i][navio4_coluna - i] = 3;
        }
        printf("Navio 4 (Diagonal Secundaria) posicionado com sucesso!\n\n");
    } else {
        printf("Erro: Nao foi possivel posicionar o Navio 4 (Diagonal Secundaria).\n\n");
    }


    // --- 3. Exibir o Tabuleiro ---
    // Chama a função para imprimir o estado final do tabuleiro no console.
    exibirTabuleiro(tabuleiro);

    return 0; // Indica que o programa terminou com sucesso.
}

/**
 * @brief Inicializa o tabuleiro com 0 em todas as posições (água).
 * @param tabuleiro A matriz 2D que representa o tabuleiro.
 */
void inicializarTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            tabuleiro[i][j] = 0;
        }
    }
}

/**
 * @brief Valida se um navio pode ser posicionado em um local específico.
 * @param tab O tabuleiro do jogo.
 * @param lin A linha inicial para posicionar o navio.
 * @param col A coluna inicial para posicionar o navio.
 * @param tam O tamanho do navio.
 * @param orientacao A orientação do navio ('H', 'V', 'P' para Principal, 'S' para Secundária).
 * @return Retorna 'true' se a posição for válida, 'false' caso contrário.
 *
 * Esta função verifica duas coisas:
 * 1. Limites do Tabuleiro: Se o navio cabe inteiramente no tabuleiro.
 * 2. Sobreposição: Se alguma das posições desejadas já está ocupada por outro navio.
 */
bool validarPosicao(int tab[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int lin, int col, int tam, char orientacao) {
    for (int i = 0; i < tam; i++) {
        switch (orientacao) {
            case 'H': // Horizontal
                if (col + i >= TAMANHO_TABULEIRO || tab[lin][col + i] != 0) return false;
                break;
            case 'V': // Vertical
                if (lin + i >= TAMANHO_TABULEIRO || tab[lin + i][col] != 0) return false;
                break;
            case 'P': // Diagonal Principal (\)
                if (lin + i >= TAMANHO_TABULEIRO || col + i >= TAMANHO_TABULEIRO || tab[lin + i][col + i] != 0) return false;
                break;
            case 'S': // Diagonal Secundária (/)
                if (lin + i >= TAMANHO_TABULEIRO || col - i < 0 || tab[lin + i][col - i] != 0) return false;
                break;
        }
    }
    // Se o loop terminar sem retornar false, a posição é válida.
    return true;
}


/**
 * @brief Exibe o tabuleiro formatado no console.
 * @param tabuleiro A matriz 2D que representa o tabuleiro.
 */
void exibirTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    printf("--- TABULEIRO DE BATALHA NAVAL ---\n");
    // Adiciona cabeçalho das colunas para melhor visualização
    printf("  0 1 2 3 4 5 6 7 8 9\n");
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        // Adiciona cabeçalho da linha
        printf("%d ", i);
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            // Imprime o valor da célula seguido de um espaço.
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n"); // Quebra de linha ao final de cada linha.
    }
}
