#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include "func.h"

tipo_fila *fila;
pthread_mutex_t mutex_forno = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex_fila = PTHREAD_MUTEX_INITIALIZER;

int vazia_fila()
{
    return fila->primeiro == fila->ultimo;
}

void cria_fila()
{   
    fila = malloc(sizeof(tipo_fila));
    fila->primeiro = NULL;
    fila->ultimo = fila->primeiro;
    fila->qnt = 0;
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
        pthread_cond_wait(&pessoa->cond, &mutex_forno);

        tipo_pessoa *aux = fila->primeiro;

        while (aux != NULL)
        {
            if(aux->proximo == NULL)
            {
                aux->proximo = pessoa;
                fila->ultimo = pessoa;
                fila->qnt++;
                aux->proximo->proximo = NULL;
            }
            aux = aux->proximo;
            break;
        }   
    }     
}

tipo_pessoa desenfileira()
{
    tipo_pessoa *ret = consulta_maior();

    envelhece(ret);

    if (ret == fila->primeiro)
    {
        fila->primeiro = fila->primeiro->proximo;
    }
    
    else if (ret == fila->ultimo)
    {
        tipo_pessoa *aux = fila->primeiro;
        while (aux->proximo != ret)
        {
            aux = aux->proximo;
        }
        fila->ultimo = aux;
    }
    else
    {
        tipo_pessoa *aux = ret;
        while (aux != NULL)
        {
            aux = aux->proximo;
        }
        
    }
    fila->qnt--;
    return *ret;  
}

tipo_pessoa* consulta_maior()
{
    tipo_pessoa *aux = fila->primeiro, *maior = fila->primeiro;
    
    while (aux != NULL)
    {
        if (aux->prioridade_temp > maior->prioridade_temp)
        {
            maior = aux;
        }
        aux = aux->proximo;
    }
    return maior;
}


void envelhece(tipo_pessoa *ultimo)
{
    tipo_pessoa *aux = fila->primeiro;
    while (aux != ultimo)
    {
        aux->frustracoes++;
        if (aux->frustracoes == 2)
        {
            aux->prioridade_temp++;
        }
        aux = aux->proximo;
    }
    
}

void tarefa(void* args){
    srand(time(NULL));
    tipo_pessoa *pessoa = (tipo_pessoa*)args;
    int entrou = 0;
    while (pessoa->uso_forno != 0)
    {
        sleep(rand()%6 + 2);
        if (pessoa->uso_forno != 0 && entrou == 0)
        {
            pthread_mutex_lock(&mutex_fila);
            enfileira(pessoa);
            pthread_mutex_unlock(&mutex_fila);
            printf("%s entra na fila\n", pessoa->nome);
            entrou = 1;
        }
        
        pthread_mutex_lock(&mutex_forno);
            //seção crítica

            tipo_pessoa *maior_p = consulta_maior();//consulta
            pthread_cond_signal(&maior_p->cond);

            if (strcmp(maior_p->nome, pessoa->nome) == 0)
            {
                printf("%s está usando o forno\n", maior_p->nome);
                maior_p->frustracoes = 0;
                maior_p->prioridade_temp = maior_p->prioridade;
                maior_p->uso_forno--;
                sleep(1);
                printf("%s liberou o forno\n", maior_p->nome);
                //DESENFILEIRA E SIGNAL
                tipo_pessoa ret = desenfileira();
                entrou = 0;
                pthread_cond_signal(&ret.cond);
            }
        pthread_mutex_unlock(&mutex_forno);
    }
    
}

// void tarefa_faxineiro(void* args)
// {
//     tipo_pessoa *faxineiro = (tipo_pessoa*)args;
    
//     sleep(5);  
    
// }