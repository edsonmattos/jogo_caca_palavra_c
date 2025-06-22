#ifndef CRIA_ARQUIVO_H
#define CRIA_ARQUIVO_H

// Inclusões necessárias para as funções e tipos declarados
#include <stdio.h>   // Para FILE, printf, perror, fprintf
#include <stdlib.h>  // Para malloc, free, srand, rand
#include <time.h>    // Para time
#include <string.h>  // Para strlen, strcpy, strncpy

// --- Constantes e Estruturas ---
// Declara que estas variáveis globais existem e serão definidas em cria_arquivo.c
extern const char *textos[];
extern const int num_textos;

// Definição da struct Palavra
typedef struct palavra_s {
    char palavra[20];
    int inicio[2];
    int fim[2];
} Palavra;

// --- Declarações de Funções ---
// Funções para sortear e gerenciar listas de palavras em memória
char **retorna_lista (int numero_lista_nova);
Palavra *retorna_lista_n_arquivo(char **lista_textos, int total_palavras);

// Funções para manipulação do arquivo binário (agora com nome de arquivo parametrizado)
int cria_arquivo(Palavra *lista_palavras, int total_palavras);
Palavra *retorna_dados_arquivo(int *total_palavras);
int valida_arquivo_criado();

// Função principal de gerenciamento que orquestra as operações
Palavra *get_palavras(int numero_de_escolhas, int valida_para_recriar);

#endif // CRIA_ARQUIVO_H