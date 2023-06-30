#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

tipo_fila *fila;

//mutex
pthread_mutex_t mutex_forno = PTHREAD_MUTEX_INITIALIZER;

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

void aumenta_prioridade(tipo_pessoa *pessoa)
{
    if (pessoa->frustracoes == 2)
    {
        pessoa->prioridade_temp++;
    }
}

void tarefa(void* args){

    tipo_pessoa *pessoa = (tipo_pessoa*)args;
    printf("Thread %s\n", pessoa->nome);

    srand(time(NULL));
    sleep(rand()%6 + 3);

    printf("%s entra na fila", pessoa->nome);
    enfileira(pessoa);

    pthread_mutex_lock(&mutex_forno);
        //seção crítica

        tipo_pessoa maior_p = desenfileira();
        pthread_cond_signal(&maior_p.cond);

        if (strcmp(maior_p.nome, pessoa->nome) == 0)
        {
            printf("%s usa o forno\n", maior_p->nome);

            sleep(1);
            printf("%s liberou o forno\n", maior_p->nome);
        }

    pthread_mutex_unlock(&mutex_forno);
}
