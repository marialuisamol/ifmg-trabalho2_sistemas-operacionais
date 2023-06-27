#ifndef UTIL.H
#define UTIL.H

#include <pthread.h>

typedef struct tipo_pessoa
{
    int prioridade;
    int prioridade_temp;
    char* nome;
    int frustracoes;
    int uso_forno;
    int id;                                       

}tipo_pessoa;

typedef struct tipo_fila
{
    tipo_pessoa p;
    int ultimo;
}tipo_fila;

pthread_mutex_t mutex_forno = PTHREAD_MUTEX_INITIALIZER;


#endif