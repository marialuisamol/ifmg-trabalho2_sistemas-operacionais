#include <stdlib.h>
#include <stdio.h>
#include "util.h"
#include <pthread.h>

void aumentaprioridade(tipo_pessoa p)
{
    if (p.frustracoes == 2)
    {
        p.prioridade_temp++;
    }
    
}

void cria_pessoa(pthread_t thread)
{
    
    
}