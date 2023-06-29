#ifndef FILA_H
#define FILA_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>

typedef struct tipo_pessoa
{
    char* nome;
    int prioridade;
    int prioridade_temp;                                     
    int frustracoes;
    int uso_forno;                                    
    struct tipo_pessoa *proximo;
    pthread_cond_t cond; // Variáveis de condição

} tipo_pessoa;


typedef struct 
{
    tipo_pessoa *primeiro;
    tipo_pessoa *ultimo;
    int qnt;
    
} tipo_fila;

void cria_fila();
int vazia_fila();
void enfileira(tipo_pessoa *pessoa);
tipo_pessoa desenfileira();

//mutex
pthread_mutex_t mutex_forno = PTHREAD_MUTEX_INITIALIZER;

#endif