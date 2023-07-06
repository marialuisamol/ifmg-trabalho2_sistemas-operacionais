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
        tipo_pessoa *aux = fila->primeiro;

        while (aux != NULL)
        {
            if(aux->proximo == NULL)
            {
                aux->proximo = pessoa;
                pessoa->proximo = NULL;
                fila->ultimo = pessoa->proximo;
                fila->qnt++;
                pthread_cond_wait(&pessoa->cond, &mutex_forno);
                break;
            }
            aux = aux->proximo;
        }
    }     
}

void desenfileira(tipo_pessoa *pessoa)
{

    if (pessoa == fila->primeiro)
    {
        fila->primeiro = fila->primeiro->proximo;
    }    
    else
    {
        tipo_pessoa *aux = fila->primeiro;
        tipo_pessoa *anterior = fila->primeiro;
        while (aux != NULL)
        {
            aux = aux->proximo;
            if (pessoa == aux){
                anterior->proximo = pessoa->proximo;
            }
            anterior = anterior->proximo;
        }
    }
    fila->qnt--;
    
    return;  
}

tipo_pessoa consulta_maior()
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
    return *maior;
}


void envelhece(tipo_pessoa *pessoa_atual)
{
    tipo_pessoa *aux = fila->primeiro;
    if (fila->primeiro == pessoa_atual)
    {
        return;
    }
    else
    {
        while (aux != pessoa_atual)
        {
            aux->frustracoes++;
            if (aux->frustracoes == 2)
            {
                if (aux->prioridade_temp == 3)
                {
                    break;
                }
                else
                {
                    aux->prioridade_temp++;
                    aux->frustracoes = 0;
                }
            }
            aux = aux->proximo;
        }
    }
}

void imprime_fila(){
    tipo_pessoa *aux = fila->primeiro;
    printf("FILA: ");
    while (aux != NULL)
    {
        printf("%s\t", aux->nome);
        aux = aux->proximo;
    }
    printf("\n");
}

void tarefa(void* args){
    srand(time(NULL));
    tipo_pessoa *pessoa = (tipo_pessoa*)args;
    
    while (pessoa->uso_forno != 0)
    {
        sleep(rand()%6 + 2);
        pthread_mutex_lock(&mutex_fila);
            enfileira(pessoa);
            printf("%s entra na fila\n", pessoa->nome);  
            //imprime_fila(); 
            envelhece(pessoa);
        pthread_mutex_unlock(&mutex_fila);

        pthread_mutex_lock(&mutex_forno);
            
            desenfileira(pessoa);
            //imprime_fila();
            printf("%s está usando o forno\n", pessoa->nome);
            pessoa->frustracoes = 0;
            pessoa->prioridade_temp = pessoa->prioridade;
            pessoa->uso_forno--;
            sleep(1);
            printf("%s libera o forno\n", pessoa->nome); 
            //DESENFILEIRA E SIGNAL
            
            tipo_pessoa maior_p = consulta_maior();
            //printf("Signal: %s\n", maior_p.nome);
            pthread_cond_signal(&maior_p.cond);
        
        pthread_mutex_unlock(&mutex_forno);
    }
    
}
