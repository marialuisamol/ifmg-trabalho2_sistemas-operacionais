#include "fila.h"

tipo_fila *fila;

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

        pthread_cond_wait(&pessoa->cond, &mutex_forno);

        while (aux != NULL)
        {
            if(aux->proximo == NULL)
            {
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
    tipo_pessoa *ret;
    ret = fila->primeiro;
    fila->primeiro = fila->primeiro->proximo;
    fila->qnt--;
    return *ret;
}