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

void desenfileira(tipo_fila *fila)
{
    tipo_pessoa pessoa = fila[0].p;

    while (fila->ultimo != NULL)
    {
        int i = 0;
        fila[i].p = fila[i+1].p;
        i++;
    }
    fila->ultimo--;
}

void enfileira(tipo_fila *fila, tipo_pessoa pessoa)
{
    int i = fila->ultimo, menor_prioridade = fila->ultimo;
    while (fila->ultimo <= 0)
    {        
        if (fila[i].p.prioridade_temp < pessoa.prioridade ||
        fila[i].p.prioridade < pessoa.prioridade)
        {
            menor_prioridade = i;
        }
        
        i--;
    }

    for (int j = fila->ultimo; i < j; j--)
    {
        fila[j].p = fila[j-1].p;
    }

    fila[i].p = pessoa;
    fila->ultimo++;

    printf("%s entrou na fila\n", pessoa.nome);
       
}

void usa_forno(void){

    pthread_mutex_lock(&mutex_forno);
        //seção crítica
        printf("%s usa o forno\n", pessoa.nome);
        pessoa.uso_forno--;
        sleep(1);
    pthread_mutex_unlock(&mutex_forno);
}
