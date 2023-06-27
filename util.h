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

}tipo_pessoa;

typedef struct tipo_fila
{
    tipo_pessoa p;
    int ultimo;
    tipo_pessoa *prox;
}tipo_fila;

pthread_mutex_t mutex_forno = PTHREAD_MUTEX_INITIALIZER;


#endif