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

int main() {
    // --- 1. Represente o Tabuleiro ---
    // Declara a matriz 10x10 que servirá como nosso tabuleiro.
    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];

    // Inicializa todas as posições do tabuleiro com 0 (água).
    inicializarTabuleiro(tabuleiro);

    // --- 2. Posicione os Navios ---
    // As coordenadas são definidas diretamente no código, como solicitado.
    // Lembre-se que em C, os índices de arrays começam em 0.
    // Linha 0 é a primeira linha, Coluna 0 é a primeira coluna.

    // --- NAVIO HORIZONTAL ---
    int navioH_linha = 2;   // Posição na linha 3 do tabuleiro
    int navioH_coluna = 3;  // Posição inicial na coluna 4 do tabuleiro

    // Validação: Verifica se o navio horizontal cabe nos limites do tabuleiro.
    if (navioH_coluna + TAMANHO_NAVIO <= TAMANHO_TABULEIRO) {
        // Se couber, posiciona o navio.
        // O loop percorre o tamanho do navio, adicionando 3 em cada posição.
        for (int i = 0; i < TAMANHO_NAVIO; i++) {
            // A linha é fixa, apenas a coluna muda.
            tabuleiro[navioH_linha][navioH_coluna + i] = 3;
        }
        printf("Navio horizontal posicionado com sucesso!\n");
    } else {
        printf("Erro: O navio horizontal está fora dos limites do tabuleiro!\n");
    }

    // --- NAVIO VERTICAL ---
    int navioV_linha = 5;   // Posição inicial na linha 6 do tabuleiro
    int navioV_coluna = 6;  // Posição na coluna 7 do tabuleiro

    // Validação: Verifica se o navio vertical cabe nos limites do tabuleiro.
    if (navioV_linha + TAMANHO_NAVIO <= TAMANHO_TABULEIRO) {
        // Validação de Sobreposição: Verifica se as posições já estão ocupadas.
        bool sobreposicao = false;
        for (int i = 0; i < TAMANHO_NAVIO; i++) {
            // A coluna é fixa, apenas a linha muda.
            if (tabuleiro[navioV_linha + i][navioV_coluna] != 0) {
                sobreposicao = true; // Encontrou uma parte de outro navio!
                break; // Não precisa continuar verificando.
            }
        }

        // Se não houve sobreposição, posiciona o navio.
        if (!sobreposicao) {
            for (int i = 0; i < TAMANHO_NAVIO; i++) {
                // A coluna é fixa, apenas a linha muda.
                tabuleiro[navioV_linha + i][navioV_coluna] = 3;
            }
            printf("Navio vertical posicionado com sucesso!\n\n");
        } else {
            printf("Erro: O navio vertical se sobrepõe a outro navio!\n\n");
        }

    } else {
        printf("Erro: O navio vertical está fora dos limites do tabuleiro!\n\n");
    }


    // --- 3. Exiba o Tabuleiro ---
    // Chama a função para imprimir o estado final do tabuleiro no console.
    exibirTabuleiro(tabuleiro);

    return 0; // Indica que o programa terminou com sucesso.
}

/**
 * @brief Inicializa o tabuleiro com 0 em todas as posições.
 * @param tabuleiro A matriz 2D que representa o tabuleiro.
 *
 * Esta função utiliza loops aninhados para percorrer cada célula
 * da matriz e atribuir o valor 0, que representa a água.
 */
void inicializarTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    // Loop para percorrer cada linha
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        // Loop para percorrer cada coluna da linha atual
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            tabuleiro[i][j] = 0;
        }
    }
}

/**
 * @brief Exibe o tabuleiro formatado no console.
 * @param tabuleiro A matriz 2D que representa o tabuleiro.
 *
 * Esta função imprime o conteúdo da matriz de forma organizada,
 * com 0s representando água e 3s representando os navios.
 */
void exibirTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    printf("--- TABULEIRO DE BATALHA NAVAL ---\n");
    // Loop para percorrer cada linha
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        // Loop para percorrer cada coluna
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            // Imprime o valor da célula seguido de um espaço para melhor visualização.
            printf("%d ", tabuleiro[i][j]);
        }
        // Ao final de cada linha, imprime uma quebra de linha para formar a grade.
        printf("\n");
    }
}
