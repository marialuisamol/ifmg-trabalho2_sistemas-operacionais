#ifndef UTIL.H
#define UTIL.H

#include <pthread.h>

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

tipo_fila *fila;

pthread_mutex_t mutex_forno = PTHREAD_MUTEX_INITIALIZER;//mutex

//variaveis de condição
pthread_cond_t cond_s01 = PTHREAD_COND_INITIALIZER;
pthread_cond_t cond_s02 = PTHREAD_COND_INITIALIZER;
pthread_cond_t cond_v01 = PTHREAD_COND_INITIALIZER;
pthread_cond_t cond_v02 = PTHREAD_COND_INITIALIZER;
pthread_cond_t cond_c01 = PTHREAD_COND_INITIALIZER;
pthread_cond_t cond_c02 = PTHREAD_COND_INITIALIZER;

#endif