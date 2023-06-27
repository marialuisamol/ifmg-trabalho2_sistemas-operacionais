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

void cria_fila(tipo_fila *fila){
    
    fila->primeiro = malloc(sizeof(tipo_pessoa));
    fila->ultimo = fila->primeiro;
    fila->ultimo->proximo = NULL;
}

void desenfileira()
{
    tipo_pessoa *ret = fila->primeiro;
    
    while (fila->primeiro->proximo != NULL)
    {
        if (fila->primeiro->proximo->prioridade > ret->prioridade)
        {
            ret = fila->primeiro->proximo;
        }

        for (size_t i = ret; i <= fila->ultimo; i++)
        {
               
        }
        
        fila->qnt--;
    }
    
}

void enfileira(tipo_pessoa pessoa)
{
    tipo_pessoa *aux;
    aux = malloc(sizeof(tipo_pessoa));
    fila->ultimo->proximo = aux;
    *aux = pessoa;
    aux->proximo = NULL;
    fila->ultimo = aux;       
}

void usa_forno(tipo_pessoa pessoa){

    srand(time(NULL));
    sleep(rand()%3 + 3);
    printf("%s entra na fila", pessoa.nome);
    enfileira(pessoa);

    pthread_mutex_lock(&mutex_forno);
        //seção crítica
        //verificar se ha alguem com maior prioridade
            //se sim
                //dar signal
                //aumentar a prioridade temporaria de quem esta na frente desse
            //se não 
                //usar
                //dar signal no proximo 
        printf("%s usa o forno\n", pessoa.nome);
        pessoa.uso_forno--;
        desenfileira(pessoa);
        sleep(1);
    pthread_mutex_unlock(&mutex_forno);
}
