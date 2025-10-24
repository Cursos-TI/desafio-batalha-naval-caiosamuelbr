#include <stdio.h>
#include <stdbool.h> // Para usar 'bool'
#include <stdlib.h>  // Para usar 'abs()' (valor absoluto)

// --- Constantes Globais (Legibilidade) ---
#define TAMANHO_TABULEIRO 10
#define TAMANHO_NAVIO 3
#define TAMANHO_HABILIDADE 5 // Tamanho fixo para as matrizes de habilidade (5x5)

// --- Símbolos do Tabuleiro (Legibilidade) ---
#define AGUA 0
#define NAVIO 3
#define EFEITO 5 // Novo valor para áreas de efeito

// --- Protótipos das Funções ---
void inicializarTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]);
void exibirTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]);
bool validarPosicao(int tab[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int lin, int col, int tam, char orientacao);

// Novas funções para habilidades
void limparMatrizHabilidade(int matriz[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE]);
void criarMatrizCone(int matriz[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE]);
void criarMatrizCruz(int matriz[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE]);
void criarMatrizOctaedro(int matriz[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE]);
void aplicarHabilidade(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO],
                       int hab[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE],
                       int origem_lin, int origem_col);

int main() {
    // --- 1. Definir o Tabuleiro ---
    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];
    inicializarTabuleiro(tabuleiro);

    // --- 2. Posicionar Navios (Base do nível anterior) ---
    printf("Posicionando navios...\n");
    // Navio 1: Horizontal
    if (validarPosicao(tabuleiro, 1, 1, TAMANHO_NAVIO, 'H')) {
        for (int i = 0; i < TAMANHO_NAVIO; i++) tabuleiro[1][1 + i] = NAVIO;
    }
    // Navio 2: Vertical
    if (validarPosicao(tabuleiro, 3, 8, TAMANHO_NAVIO, 'V')) {
        for (int i = 0; i < TAMANHO_NAVIO; i++) tabuleiro[3 + i][8] = NAVIO;
    }
    // Navio 3: Diagonal Principal
    if (validarPosicao(tabuleiro, 4, 1, TAMANHO_NAVIO, 'P')) {
        for (int i = 0; i < TAMANHO_NAVIO; i++) tabuleiro[4 + i][1 + i] = NAVIO;
    }
    // Navio 4: Diagonal Secundária
    if (validarPosicao(tabuleiro, 0, 8, TAMANHO_NAVIO, 'S')) {
        for (int i = 0; i < TAMANHO_NAVIO; i++) tabuleiro[0 + i][8 - i] = NAVIO;
    }
    printf("Navios posicionados.\n");

    // --- 3. Criar Matrizes de Habilidade ---
    printf("Criando matrizes de habilidade...\n");
    int matrizCone[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE];
    int matrizCruz[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE];
    int matrizOctaedro[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE];

    // Constrói as matrizes 5x5 usando loops e condicionais
    criarMatrizCone(matrizCone);
    criarMatrizCruz(matrizCruz);
    criarMatrizOctaedro(matrizOctaedro);

    // --- 4. Integrar Habilidades ao Tabuleiro ---
    printf("Aplicando habilidades ao tabuleiro...\n");

    // Define os pontos de origem (hardcoded)
    int cone_origem_lin = 2;
    int cone_origem_col = 5;

    int cruz_origem_lin = 7;
    int cruz_origem_col = 2;

    int octa_origem_lin = 4;
    int octa_origem_col = 4;

    // Aplica as habilidades, sobrepondo-as no tabuleiro principal
    aplicarHabilidade(tabuleiro, matrizCone, cone_origem_lin, cone_origem_col);
    aplicarHabilidade(tabuleiro, matrizCruz, cruz_origem_lin, cruz_origem_col);
    aplicarHabilidade(tabuleiro, matrizOctaedro, octa_origem_lin, octa_origem_col);


    // --- 5. Exibir o Tabuleiro com Habilidade ---
    exibirTabuleiro(tabuleiro);

    return 0;
}

// --- Funções de Habilidade ---

/**
 * @brief Zera uma matriz de habilidade 5x5 antes de criar a forma.
 */
void limparMatrizHabilidade(int matriz[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE]) {
    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            matriz[i][j] = 0;
        }
    }
}

/**
 * @brief Cria uma forma de "Cone" (triângulo) em uma matriz 5x5.
 * A forma se origina no centro (2,2) e se expande para baixo.
 * 0 0 0 0 0
 * 0 0 0 0 0
 * 0 0 1 0 0  (Linha 2: abs(j-2) <= 0)
 * 0 1 1 1 0  (Linha 3: abs(j-2) <= 1)
 * 1 1 1 1 1  (Linha 4: abs(j-2) <= 2)
 */
void criarMatrizCone(int matriz[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE]) {
    limparMatrizHabilidade(matriz);
    int centro = TAMANHO_HABILIDADE / 2; // centro = 2

    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            // A habilidade comeca na linha do centro (i >= centro)
            // A largura (abs(j - centro)) deve ser menor ou igual
            // a distancia vertical do centro (i - centro).
            if (i >= centro && abs(j - centro) <= (i - centro)) {
                matriz[i][j] = 1;
            }
        }
    }
}

/**
 * @brief Cria uma forma de "Cruz" (+) em uma matriz 5x5.
 * A forma afeta a linha central E a coluna central.
 */
void criarMatrizCruz(int matriz[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE]) {
    limparMatrizHabilidade(matriz);
    int centro = TAMANHO_HABILIDADE / 2; // centro = 2

    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            // Se a celula esta na linha central (i == centro)
            // OU na coluna central (j == centro)
            if (i == centro || j == centro) {
                matriz[i][j] = 1;
            }
        }
    }
}

/**
 * @brief Cria uma forma de "Octaedro" (Losango/Diamante) em uma matriz 5x5.
 * Utiliza a "Distância de Manhattan" do centro.
 * Dist = |i - centro| + |j - centro|
 * Afeta todas as celulas onde Dist <= centro (2).
 */
void criarMatrizOctaedro(int matriz[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE]) {
    limparMatrizHabilidade(matriz);
    int centro = TAMANHO_HABILIDADE / 2; // centro = 2

    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            // Calcula a distancia de Manhattan
            int dist = abs(i - centro) + abs(j - centro);

            // Se a distancia for menor ou igual ao 'raio' (centro), afeta.
            if (dist <= centro) {
                matriz[i][j] = 1;
            }
        }
    }
}

/**
 * @brief Sobrepõe uma matriz de habilidade (5x5) no tabuleiro principal (10x10).
 * @param tabuleiro O tabuleiro principal 10x10.
 * @param hab A matriz de habilidade 5x5 (preenchida com 0s e 1s).
 * @param origem_lin A linha do tabuleiro onde o CENTRO (2,2) da habilidade será aplicado.
 * @param origem_col A coluna do tabuleiro onde o CENTRO (2,2) da habilidade será aplicado.
 */
void aplicarHabilidade(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO],
                       int hab[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE],
                       int origem_lin, int origem_col) {

    int centro = TAMANHO_HABILIDADE / 2; // 2

    // Percorre a matriz de habilidade 5x5
    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {

            // 1. Verifica se esta parte da habilidade (i, j) deve ser aplicada (valor 1)
            if (hab[i][j] == 1) {
                // 2. Calcula a coordenada correspondente no tabuleiro principal
                // O (0,0) da habilidade corresponde a (origem_lin - 2, origem_col - 2) no tabuleiro
                // O (i,j) da habilidade corresponde a (origem_lin + (i - centro), origem_col + (j - centro))
                int tab_lin = origem_lin + (i - centro);
                int tab_col = origem_col + (j - centro);

                // 3. Validação de Limites (Requisito Funcional)
                // Garante que a coordenada calculada esteja DENTRO do tabuleiro 10x10
                if (tab_lin >= 0 && tab_lin < TAMANHO_TABULEIRO &&
                    tab_col >= 0 && tab_col < TAMANHO_TABULEIRO) {

                    // 4. Aplica o efeito visual (valor 5) no tabuleiro
                    // Sobrescreve agua (0) ou navio (3)
                    tabuleiro[tab_lin][tab_col] = EFEITO;
                }
            }
        }
    }
}


// --- Funções Auxiliares (do nível anterior, com melhorias) ---

/**
 * @brief Inicializa o tabuleiro com 0 (AGUA) em todas as posições.
 */
void inicializarTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            tabuleiro[i][j] = AGUA;
        }
    }
}

/**
 * @brief Valida se um navio pode ser posicionado (limites e sobreposição).
 */
bool validarPosicao(int tab[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int lin, int col, int tam, char orientacao) {
    for (int i = 0; i < tam; i++) {
        switch (orientacao) {
            case 'H': // Horizontal
                if (col + i >= TAMANHO_TABULEIRO || tab[lin][col + i] != AGUA) return false;
                break;
            case 'V': // Vertical
                if (lin + i >= TAMANHO_TABULEIRO || tab[lin + i][col] != AGUA) return false;
                break;
            case 'P': // Diagonal Principal (\)
                if (lin + i >= TAMANHO_TABULEIRO || col + i >= TAMANHO_TABULEIRO || tab[lin + i][col + i] != AGUA) return false;
                break;
            case 'S': // Diagonal Secundária (/)
                if (lin + i >= TAMANHO_TABULEIRO || col - i < 0 || tab[lin + i][col - i] != AGUA) return false;
                break;
        }
    }
    return true;
}

/**
 * @brief Exibe o tabuleiro formatado no console com caracteres.
 */
void exibirTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    printf("\n--- TABULEIRO DE BATALHA NAVAL ---\n");
    // Cabeçalho das colunas
    printf("    0 1 2 3 4 5 6 7 8 9\n");
    printf("  +---------------------\n");
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        // Cabeçalho da linha
        printf("%d | ", i);
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            // Imprime o caractere correspondente ao valor
            switch (tabuleiro[i][j]) {
                case AGUA:
                    printf("~ "); // '~' para Água
                    break;
                case NAVIO:
                    printf("N "); // 'N' para Navio
                    break;
                case EFEITO:
                    printf("* "); // '*' para Área de Efeito
                    break;
                default:
                    printf("? ");
            }
        }
        printf("|\n"); // Fim da linha
    }
    printf("  +---------------------\n");
    printf("Legenda: [~] Agua  [N] Navio  [*] Area de Efeito\n");
}
