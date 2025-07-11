#include <stdio.h>
#include <stdlib.h>
#include <time.h> // Para srand(time(NULL));
#include "cria_arquivo.h" // Inclui o header da sua lib 
#include "arquive_log.h" // Inclui o header da sua lib 


int main() {
    // Inicializa o gerador de números aleatórios APENAS UMA VEZ
    log_to_file("log_programa.log",  LOG_INFO,"Inicio do log\n");
    srand(time(NULL));

    inicializar_dicionario(1);

    // Testando a função de inserção
    inserir_palavra("nova_palavra"); // Deve adicionar
    inserir_palavra("abacaxi");    // Já existe
    inserir_palavra("teste");      // Deve adicionar

    // Testando a função de remoção
    remover_palavra("abacaxi");      // Deve remover
    remover_palavra("nao_existe"); // Não existe
    remover_palavra("teste");       // Deve remover

    // Removendo todas as palavras
    remover_palavra("cacau");
    remover_palavra("coco");
    remover_palavra("goiaba");
    remover_palavra("nova_palavra");
    
    cria_arquivo();
    
    mostrar_palavras();
    Palavra *teste = get_palavras(4,0);
    free(teste);
    teste= NULL;

    // Libere a memória quando não precisar mais do dicionário
    libera_array();
    log_to_file("log_programa.log",  LOG_INFO,"Fim do log\n");

    return 0;
}