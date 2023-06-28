#ifndef UTIL.H
#define UTIL.H

#include <pthread.h>

// Tipo e variáveis globais

typedef struct tipo_pessoa
{
    char* nome;
    int prioridade;
    int prioridade_temp;                                     
    int frustracoes;
    int uso_forno;                                    
    struct tipo_pessoa *proximo;

}tipo_pessoa;

typedef struct tipo_fila
{
    tipo_pessoa *primeiro;
    tipo_pessoa *ultimo;
    int qnt;
    
}tipo_fila;

//define variável fila
tipo_fila *fila;

//mutex
pthread_mutex_t mutex_forno = PTHREAD_MUTEX_INITIALIZER;

//variaveis de condição
pthread_cond_t cond[6];

#endif