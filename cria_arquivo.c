#include "cria_arquivo.h"

char **textos = NULL;
int num_textos= 0;

int palavra_existe(const char *palavra){
    for (int i = 0; i < num_textos; i++){
        if(strcmp(textos[i],palavra) ==0){
            return 1;
        }
    }
    return 0;
}

void inserir_palavra (const char *nova_palavra){
    if (nova_palavra == NULL){
        printf("Palavra nao passada na funcao");
        return;
    }
    if (strlen(nova_palavra) <4 &&  strlen(nova_palavra) >4 ){
        printf("Palavra fora do range de 4 a 20 caracteres");
        return;
    }
    char **temporario = (char**)realloc(textos,(num_textos+1) * sizeof(char*));
    if(temporario == NULL){
        printf("erro ao realocar memoria para o array de palavras\n");
        return;
    }
    textos = temporario;
    textos[num_textos] = (char*) malloc(strlen(nova_palavra)+1);
    if (textos[num_textos] == NULL){
        printf("erro ao alocar memoria para a nova palavra\n");
        return;
    }
    strcpy(textos[num_textos],nova_palavra);
    num_textos++;
    printf("Palavra '%s' adicionada com sucesso.\n",nova_palavra);
}

void remover_palavra(const char *palavra_a_remover){
    int indice_remover = -1;
    for (int i = 0; i < num_textos; i++){
        if (strcmp(textos[i],palavra_a_remover) == 0){
            indice_remover = i;
            break;
        }
    }
    if (indice_remover == -1){
        printf("A palavra '%s' nao foi encontrada no array de palavras\n",palavra_a_remover);
        return;
    }
    free(textos[indice_remover]);
    for (int i = indice_remover; i < num_textos -1; i++){
        textos[i] = textos[i+1];
    }
    num_textos--;
    if (num_textos<=0){
        num_textos = 0;
        free(textos);
        textos = NULL;
        printf("Removido a palavra '%s' e o array de palavras esta vazio\n",palavra_a_remover);
    }else{
        char **temporario = (char**) realloc(textos, num_textos * sizeof(char*));
        if (temporario == NULL){
            printf("erro ao alocar memoria apos a remocao, porem sem aplicar no array original\n");
            return;
        }
        textos = temporario;
        printf("Removido a palavra '%s' do array de palavras\n",palavra_a_remover);
    }
}

void libera_array(){
    for (int i = 0; i < num_textos; i++){
        free(textos[i]);
    }
    free(textos);
    textos= NULL;
    num_textos = 0;
    printf("Array de palavras liberado na memoria\n");
}

void mostrar_palavras(){
    printf("\n--- Palavras Atuais no Array (%d) ---\n", num_textos);
    if (num_textos == 0) {
        printf("Array vazio.\n");
        return;
    }
    for (int i = 0; i < num_textos; i++) {
        printf("%d: %s\n", i + 1, textos[i]);
    }
    printf("---------------------------------------\n");
}

void inicializar_dicionario() {
    const char *palavras_iniciais[] = {
        "abacaxi","acai","ameixa","amora","araca","banana","cacau","caju","caqui","cereja",
        "coco","damasco","figo","goiaba","jaca","kiwi","laranja","limao","lichia","umbu",
        "maca","manga","melao","mamao","morango","pera","pessego","pitanga","roma","sapoti",
        "abobora","agriao","alho","alface","aipo","aspargo","batata","cebola","cenoura","chuchu",
        "couve","ervilha","feijao","inhame","jilo","milho","nabo","erva","pepino","quiabo",
        "maniva","repolho","rucula","salsao","tomate","acelga","broto","pure","grao","vagem","rama","talo","trevo","alga",
        "anel","apito","aviao","balao","balde","banco","barco","bolsa","botao","cabo",
        "caixa","cama","caneca","caneta","carro","carta","cesto","chave","colher","cone",
        "copo","dado","espada","espelho","faca","fios","fita","fones","forno","garfo",
        "globo","guarda","haste","janela","jarra",
        "abelha","bode","cabra","cisne","cobra","coelho","coruja","foca","formiga","galinha",
        "ganso","gato","jabuti","leao","macaco","morcego","ovelha","panda","papagaio","peru",
        "pomba","pinguim","porco","pulga","rato","texugo","tigre","touro","urso","vaca","zebra","alpaca","burro","camelo",
        "azul","bege","branco","cobre","dourado","marrom","preto","roxo","verde","amarelo",
        "cinza","prata","creme","rosa","violeta","indigo","ciano","magenta","carmim","lilas",
        "bronze","salmao","ocre","palha","rubi","siena","trigo","vinho","azulejo",
        "andar","beber","cantar","correr","dormir","falar","olhar","pular","comer",
        "abrir","ajudar","amar","apoiar","banhar","cair","chamar","criar","dancar","ensinar",
        "entrar","estudar","fazer","fechar","ganhar","gostar","gritar","jogar","limpar","morar"
    };

    int total_palavras_iniciais = sizeof(palavras_iniciais) / sizeof(palavras_iniciais[0]);
    printf("Inicializando array com %d palavras...\n", total_palavras_iniciais);

    for (int i = 0; i < total_palavras_iniciais; i++) {
        inserir_palavra(palavras_iniciais[i]);
    }
    printf("Array inicializado.\n");
}

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
    
    arquivo = fopen("palavras.bin","wb"); 
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
    arquivo = fopen("palavras.bin","rb"); 
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
    arquivo = fopen("palavras.bin","rb");
    if (arquivo == NULL){
        printf("erro ao abrir para leitura o aquivo");
        return 0;
    }
    fclose(arquivo);
    return 1;
}

Palavra *get_palavras(int numero_de_escolhas, int valida_para_recriar) {
    if (numero_de_escolhas <= 0 && numero_de_escolhas > num_textos){
        printf("numero fora do range de 0 e %d",num_textos);
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



// int main() {
//     inicializar_dicionario();

//     // Testando a função de inserção
//     inserir_palavra("nova_palavra"); // Deve adicionar
//     inserir_palavra("abacaxi");    // Já existe
//     inserir_palavra("teste");      // Deve adicionar

//     // Testando a função de remoção
//     remover_palavra("abacaxi");      // Deve remover
//     remover_palavra("nao_existe"); // Não existe
//     remover_palavra("teste");       // Deve remover

//     // Removendo todas as palavras
//     remover_palavra("cacau");
//     remover_palavra("coco");
//     remover_palavra("goiaba");
//     remover_palavra("nova_palavra");

//     mostrar_palavras();
//     Palavra *teste = get_palavras(4,1);
//     free(teste);
//     teste= NULL;

//     // Libere a memória quando não precisar mais do dicionário
//     libera_array();

//     return 0;
// }