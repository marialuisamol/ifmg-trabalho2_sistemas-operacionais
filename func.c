#include <stdlib.h>
#include <stdio.h>
#include "util.h"
#include <pthread.h>

void aumentaprioridade(pessoa p)
{
    if (p.frustracoes == 2)
    {
        p.prioridade_temp++;
    }
    
}