#include <stdlib.h>
#include <stdio.h>
#include "util.h"
#include <pthread.h>

int vazia_fila(){
    return fila->primeiro == fila->ultimo;
}

void cria_fila(tipo_fila *fila)
{    
    fila->primeiro = malloc(sizeof(tipo_pessoa));
    fila->ultimo = fila->primeiro;
    fila->ultimo->proximo = NULL;
}

void enfileira(tipo_pessoa *pessoa)
{
    if (vazia_fila(fila))
    {
        fila->primeiro = pessoa;
        pessoa->proximo = NULL;
        fila->ultimo = pessoa->proximo;
        fila->qnt++;
    }
    else
    {
        tipo_pessoa *aux = fila->primeiro;

        pthread_cond_wait(&pessoa->cond, &mutex_forno);

        while (aux != NULL)
        {
            if(aux->proximo == NULL){
                aux->proximo = pessoa;
                fila->qnt++;
                fila->ultimo = pessoa;
            }
            aux = aux->proximo;
            break;
        }   
    }     
}

tipo_pessoa desenfileira()
{
    tipo_pessoa *ret = fila->primeiro, *aux;
    
    //encontra o proximo da fila seguindo a prioridade e ordem de chegada
    while (ret != NULL)
    {
        if (ret->prioridade_temp > ret->prioridade)
        {
            if (ret->prioridade_temp < fila->primeiro->proximo->prioridade ||
            ret->prioridade_temp < fila->primeiro->proximo->prioridade_temp)
            {
                ret = fila->primeiro->proximo;
                ret->frustracoes = 0;
                ret->prioridade_temp = ret->prioridade;
                aux = ret;
                break;
            }
            
        }
        else
        {
            if (ret->prioridade < fila->primeiro->proximo->prioridade ||
            ret->prioridade < fila->primeiro->proximo->prioridade_temp)
            {
                ret = fila->primeiro->proximo;
                ret->frustracoes = 0;
                ret->prioridade_temp = ret->prioridade;
                aux = ret;
                break;
            }
            
        }
        else
        {
            if (ret->prioridade < fila->primeiro->proximo->prioridade ||
            ret->prioridade < fila->primeiro->proximo->prioridade_temp)
            {
                ret = fila->primeiro->proximo;
                ret->frustracoes = 0;
                ret->prioridade_temp = ret->prioridade;
                aux = ret;
                break;
            }
            
        }

        //aumenta frustração de quem a fila foi furada
        fila->primeiro->frustracoes++;

        aumenta_prioridade(fila->primeiro);

        //anda com a fila
        ret = ret->proximo;

    }//while
    
    if (aux == fila->primeiro)
    {
        fila->primeiro = fila->primeiro->proximo;
    }
    
    //arredando pra frente celulas que estão depois da celula desenfileirada
    else
    {
        while (aux != NULL)
        {
            aux = aux->proximo;
        }
    }
    
    fila->qnt--;
    return *ret;
}

void aumenta_prioridade(tipo_pessoa *pessoa)
{
    if (pessoa->frustracoes == 2)
    {
        pessoa->prioridade_temp++;
    }
}

void task(void* args)
{
    tipo_pessoa *pessoa = (tipo_pessoa*)args, *prox = fila->primeiro;

    srand(time(NULL));
    sleep(rand()%3 + 3);

    printf("%s entra na fila", pessoa->nome);
    enfileira(pessoa);

    pthread_mutex_lock(&mutex_forno);
        //seção crítica

        tipo_pessoa maior_p = desenfileira();
        pthread_cond_signal(&maior_p.cond);

        if (strcmp(maior_p.nome, pessoa->nome) == 0)
        {
            printf("%s usa o forno\n", pessoa->nome);

            sleep(1);
        }

    pthread_mutex_unlock(&mutex_forno);
}

/*
* lock mutex
* entra na seção critica
* verifica se essa thread é a maix proxima do inicio da fila e de maior prioridade
* se sim 
* * usa a seção critica
* * da signal pra proxima
*
* se não
* * da wait em quem é
*/
