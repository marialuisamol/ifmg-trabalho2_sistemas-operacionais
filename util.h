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

#endif