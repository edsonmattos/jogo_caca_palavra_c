#include <stdio.h>
#include <stdlib.h>
#include <time.h> // Para srand(time(NULL));

#include "cria_arquivo.h" // Inclui o header da sua lib dentro da pasta 'data'

int main() {
    // Inicializa o gerador de números aleatórios APENAS UMA VEZ
    srand(time(NULL));

    int valida_para_recriar = 0;
    printf("Deseja recriar o arquivo? (1 para sim, 0 para nao): ");
    if (scanf("%d", &valida_para_recriar) != 1) {
        fprintf(stderr, "Entrada inválida. Usando '0' (não recriar).\n");
        valida_para_recriar = 0;
        // Limpa o buffer do stdin caso o usuário digite algo não numérico
        while (getchar() != '\n');
    }

    // Chama a função principal da sua biblioteca
    const int NUM_TEXTOS_A_USAR = 3; // Você define o número de escolhas aqui
    Palavra *minhas_palavras = get_palavras(NUM_TEXTOS_A_USAR, valida_para_recriar);

    if (minhas_palavras == NULL) {
        fprintf(stderr, "Erro: Nao foi possivel obter a lista de palavras. Encerrando.\n");
        return 1;
    }

    // A função 'get_palavras' já imprime as palavras.
    // Se você precisar fazer algo mais com 'minhas_palavras' aqui, pode fazer.

    // MUITO IMPORTANTE: Liberar a memória retornada por get_palavras
    // (A responsabilidade de liberar a lista de Palavras retornada é de quem chamou a função)
    free(minhas_palavras);
    minhas_palavras = NULL;

    printf("\nMemória liberada para 'minhas_palavras'. Programa finalizado.\n");
    return 0;
}