#include "cria_arquivo.h"

const char *textos[] = {
    // Frutas (4-7 caracteres)
    "abacaxi", "abricot", "acai", "ameixa", "amora", "araca", "banana", "cacau", "caju", "caqui",
    "caramb", "cereja", "coco", "damasco", "figo", "goiaba", "guava", "jabuti", "jaca", "kiwi",
    "laranja", "limao", "lichia", "maca", "manga", "melao", "mexer", "morango", "pera", "pessego",
    "pitanga", "roma", "sapoti", "umbu", "uva", "uvaia", "acerola", "grosel", "marmelo", "tamar",

    // Vegetais (4-7 caracteres)
    "abobra", "agriao", "alho", "alface", "aspargo", "batata", "brocol", "cebola", "cenoura", "chuchu",
    "cogume", "couve", "ervilha", "feijao", "inhame", "jilo", "milho", "nabo", "pepino", "quiabo",
    "rabanet", "rucula", "salsao", "tomate", "beterr", "couvef", "lentilh", "piment", "broto", "mostar",

    // Objetos (4-7 caracteres)
    "anel", "apito", "aviao", "balao", "balde", "banco", "barco", "bolsa", "botao", "cabo",
    "caixa", "cama", "caneca", "caneta", "carro", "carta", "cesto", "chave", "colher", "cone",
    "copo", "dado", "espada", "espelh", "esponja", "faca", "fio", "fita", "fones", "forno",
    "garfo", "garrafa", "gaveta", "grade", "jarra", "janela", "lampa", "lapis", "lata", "lente",
    "linha", "livro", "lixeira", "luz", "martel", "mesa", "micro", "moeda", "muro", "navio"
};
const int num_textos = 100; 


char **retorna_lista (int numero_lista_nova){
    if (numero_lista_nova <=0 || numero_lista_nova > num_textos){
        printf("O numero de sorteio deve ser entre 1 e %d", num_textos);
        return  NULL;
    }
    
    int *lista_indice = (int *)malloc(numero_lista_nova * sizeof(int));
    if (lista_indice == NULL){
        printf("erro ao alocar memoria");
        return  NULL;
    }
    
    char **textos_aleatorios = (char**)malloc(numero_lista_nova * sizeof(char *));
    if (textos_aleatorios == NULL){
        printf("erro ao alocar memoria");
        free(lista_indice);
        return  NULL;
    }
    
    int contador = 0;

    while (contador <numero_lista_nova){
        int numero_aletorio = rand() % num_textos;
        int escolhido = 0;
        for (int i = 0; i < contador; i++){
            if (lista_indice[i] == numero_aletorio){
                escolhido = 1;
                break;
            }
        }
        if (!escolhido){
            lista_indice[contador] = numero_aletorio;
            textos_aleatorios[contador] = (char*)malloc(strlen(textos[numero_aletorio])+1);
            if (textos_aleatorios[contador] == NULL){
                printf("erro ao alocar memoria");
                for (int i = 0; i < contador; i++){
                    free(textos_aleatorios[i]);
                }
                free(textos_aleatorios);
                free(lista_indice);
                return  NULL;
            }
            strcpy(textos_aleatorios[contador],textos[numero_aletorio]);
            contador++;
        }
    }
    free(lista_indice);
    return textos_aleatorios;
}

Palavra *retorna_lista_n_arquivo(char **lista_textos, int total_palavras){
    if(lista_textos == NULL || total_palavras <=0){
        printf("Erro: lista de textos invalida ou numero de palavras <=0 ");
        return NULL;
    }
    Palavra *lista_palavras = (Palavra*) malloc(total_palavras * sizeof(Palavra));
    if (lista_palavras == NULL){
        printf("erro ao alocar memoria");
        return NULL;
    }
    for (int i = 0; i < total_palavras; i++){
        if (lista_textos[i] == NULL){
            printf("erro ao selcionar palavra");
            for (int j = 0; j < i; j++){
                free(lista_textos[j]);
            }
            free(lista_textos);
            return NULL;
        }
        strncpy(lista_palavras[i].palavra,lista_textos[i], sizeof(lista_palavras[i].palavra)-1);
        lista_palavras[i].palavra[sizeof(lista_palavras[i].palavra) -1] = '\0';
        lista_palavras[i].inicio[0] = 0;
        lista_palavras[i].fim[0] = 0;
        lista_palavras[i].inicio[1] = 0;
        lista_palavras[i].fim[1] = 0;
        
    }
    return lista_palavras;
} 

int cria_arquivo(Palavra *lista_palavras, int total_palavras){
    FILE *arquivo = NULL;
    if (lista_palavras == NULL || total_palavras <=0){
        printf("Erro: lista de textos invalida ou numero de palavras <=0 ");
        return -1;
    }
    
    arquivo = fopen("teste.bin","wb"); 
    if (arquivo == NULL){
        printf("erro ao criar aquivo");
        return -1;
    }

    if (fwrite(&total_palavras,sizeof(int),1,arquivo) != 1){
        printf("erro ao escrever total de palavras no arquivo");
        fclose(arquivo);
        return -1;
    }

    if (fwrite(lista_palavras,sizeof(Palavra),total_palavras,arquivo) != (size_t)total_palavras){
        printf("erro ao escrever palavras no arquivo");
        fclose(arquivo);
        return -1;
    }
    fclose(arquivo);
    printf("Dados criados com sucesso no arquivo.\n");
    return 0;
    
}
Palavra *retorna_dados_arquivo(int * total_palavras){
    FILE *arquivo = NULL;
    Palavra *lista_palavras = NULL;
    int contador = 0;
    if (total_palavras == NULL){
        printf("erro ponteiro nao alocado ");
        return NULL;
    }
    *total_palavras = 0;
    arquivo = fopen("teste.bin","rb"); 
    if (arquivo == NULL){
        printf("erro ao abrir para leitura o aquivo");
        return NULL;
    }
    if (fread(&contador,sizeof(int),1,arquivo) != 1){
        printf("erro ao ler numero de palavras");
        fclose(arquivo);
        return NULL;
    }
    if (contador <= 0){
        printf("Arquivo sem palavras");
        fclose(arquivo);
        return NULL;
    }
    lista_palavras = (Palavra *) malloc(contador * sizeof(Palavra));
    if (lista_palavras == NULL){
        printf("erro ao alocar memoria");
        fclose(arquivo);
        return NULL;
    }
    if(fread(lista_palavras,sizeof(Palavra),contador,arquivo) != (size_t)contador){
        printf("erro ao ler palavras do  arquivo");
        free(lista_palavras);
        fclose(arquivo);
        return NULL;
    }
    fclose(arquivo);
    *total_palavras = contador;
    printf("Dados lidos com sucesso do arquivo");
    return lista_palavras;
}

int valida_arquivo_criado(){
    FILE *arquivo = NULL;
    arquivo = fopen("teste.bin","rb");
    if (arquivo == NULL){
        printf("erro ao abrir para leitura o aquivo");
        return 0;
    }
    fclose(arquivo);
    return 1;
}

Palavra *get_palavras(int numero_de_escolhas, int valida_para_recriar) {
    if (numero_de_escolhas <= 0 && numero_de_escolhas > num_textos){
        printf("");
        return NULL;
    }

    if ( valida_arquivo_criado() == 0  || valida_para_recriar==1){
        char **meus_textos_aleatorios = retorna_lista(numero_de_escolhas);
        // --- 1. Geração e Conversão para Palavras ---
        if (meus_textos_aleatorios == NULL) {
            printf("Falha ao obter textos aleatórios. Encerrando programa.\n");
            return NULL;
        }
    
        Palavra *lista_de_palavras_struct = retorna_lista_n_arquivo(meus_textos_aleatorios, numero_de_escolhas);
        if (lista_de_palavras_struct == NULL) {
            printf("Falha ao converter para lista de Palavras. Liberando textos aleatórios e encerrando.\n");
            // Libera a memória de meus_textos_aleatorios antes de sair
            for (int i = 0; i < numero_de_escolhas; i++) {
                free(meus_textos_aleatorios[i]);
            }
            free(meus_textos_aleatorios);
            return NULL;
        }
    
        // --- 2. Escrita no Arquivo ---
        printf("\n--- Escrevendo dados no arquivo ---\n");
        if (cria_arquivo(lista_de_palavras_struct, numero_de_escolhas) != 0) {
            printf("Erro ao criar e escrever no arquivo. Encerrando programa.\n");
            return NULL;
        }
        for (int i = 0; i < numero_de_escolhas; i++) {
            free(meus_textos_aleatorios[i]);
        }
        free(meus_textos_aleatorios);
        free(lista_de_palavras_struct);
        meus_textos_aleatorios = NULL;
        lista_de_palavras_struct = NULL;
    }

    // --- 3. Leitura do Arquivo ---
    printf("\n--- Lendo dados do arquivo ---\n");
    int num_palavras_lidas = 0; // Variável para armazenar quantas palavras foram lidas do arquivo
    Palavra *lista_de_palavras_arquivo = retorna_dados_arquivo( &num_palavras_lidas);

    if (lista_de_palavras_arquivo == NULL) {
        printf("Falha ao ler dados do arquivo. Encerrando programa.\n");
        return NULL;
    }

    // --- 4. Imprime as palavras e suas informações lidas do arquivo ---
    printf("\n--- Lista de Palavras Lidas do Arquivo () ---\n");
    for (int i = 0; i < num_palavras_lidas; i++) {
        printf("Palavra %d: %s\n", i + 1, lista_de_palavras_arquivo[i].palavra);
        printf("  Inicio: [%d, %d]\n", lista_de_palavras_arquivo[i].inicio[0], lista_de_palavras_arquivo[i].inicio[1]);
        printf("  Fim:    [%d, %d]\n", lista_de_palavras_arquivo[i].fim[0], lista_de_palavras_arquivo[i].fim[1]);
        printf("---\n");
    }

    return lista_de_palavras_arquivo; // Indica que o programa terminou com sucesso
}
