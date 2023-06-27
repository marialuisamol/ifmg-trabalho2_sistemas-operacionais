#include <stdlib.h>
#include <stdio.h>
#include "util.h"
#include <assert.h>
#include <pthread.h>
#include <time.h>

#define NUM_TRHEADS 3
#define USA_FORNO 1

void task(void* args){

    tipo_pessoa *pessoa = (tipo_pessoa*)args, *prox = fila->primeiro;

    srand(time(NULL));
    sleep(rand()%3 + 3);
    
    //enfileira
    tipo_pessoa *aux;
    aux = malloc(sizeof(tipo_pessoa));
    fila->ultimo->proximo = aux;
    aux = pessoa;
    aux->proximo = NULL;
    fila->ultimo = aux; 
    fila->qnt++;

    printf("%s entra na fila", pessoa->nome);

    pthread_mutex_lock(&mutex_forno);
        //seção cŕtica
        //encontra o mais proximo do inicio da fila com maior prioridade
        for (size_t i = fila->qnt; i <= fila->primeiro; i--)
        {
            
            if (prox->prioridade < prox->prioridade_temp)
            {
                if (prox->prioridade_temp < fila->primeiro->proximo->prioridade || prox->prioridade_temp < fila->primeiro->proximo->prioridade_temp)
                    {
                        prox = fila->primeiro->proximo;
                    }
                }
                else
                {
                    if (prox->prioridade < fila->primeiro->proximo->prioridade || prox->prioridade_temp < fila->primeiro->proximo->prioridade_temp)
                    {
                        prox = fila->primeiro->proximo;
                    }
                }
            
            //aumentando a prioridade temporária de quem teve a fila furada
            fila->primeiro->frustracoes++;

            //verifica frustrações
            if(fila->primeiro->frustracoes == 2)
            {
                fila->primeiro->prioridade_temp++;
                fila->primeiro->frustracoes = 0;
            }

            //anda a fila
            fila->primeiro = fila->primeiro->proximo;
                
        }
        
        while (prox != pessoa)
        {
            pthread_cond_wait(/*&var_cond*/, &mutex_forno);//espera por sua vez
        }

        printf("%s usa forno\n", pessoa->nome);
        
        
    pthread_mutex_unlock(&mutex_forno);
}

int main(int argc, char const *argv[])
{
    tipo_pessoa pessoas[NUM_TRHEADS]; //vetor de pessoas presentes na dinamica da republica
    pthread_t threads[NUM_TRHEADS]; //identificador de trheads

    //inicializa fila
    fila->primeiro = malloc(sizeof(tipo_pessoa));
    fila->ultimo = fila->primeiro;
    fila->ultimo->proximo = NULL;
    
    // setando vetor nome x prioridade
    // calouro = 1; veterano = 2; senior = 3

    pessoas[0].nome = "carlos";
    pessoas[0].prioridade = 3;
    pessoas[0].prioridade_temp = pessoas[0].prioridade;
    pessoas[0].uso_forno = USA_FORNO;

    pessoas[1].nome = "saulo";
    pessoas[1].prioridade = 2;
    pessoas[1].prioridade_temp = pessoas[1].prioridade;
    pessoas[1].uso_forno = USA_FORNO;

    pessoas[2].nome = "vera";
    pessoas[2].prioridade = 1;
    pessoas[2].prioridade_temp = pessoas[2].prioridade;
    pessoas[2].uso_forno = USA_FORNO;

    // pessoas[3].nome = "sandro";
    // pessoas[3].prioridade = 3;
    // pessoas[3].prioridade_temp = pessoas[3].prioridade;
    // pessoas[3].uso_forno = USA_FORNO;

    // pessoas[4].nome = "vani";
    // pessoas[4].prioridade = 2;
    // pessoas[4].prioridade_temp = pessoas[4].prioridade;
    // pessoas[4].uso_forno = USA_FORNO;

    // pessoas[5].nome = "camila";
    // pessoas[5].prioridade = 1;
    // pessoas[5].prioridade_temp = pessoas[5].prioridade;
    // pessoas[5].uso_forno = USA_FORNO;

    
    for (int i = 0; i < NUM_TRHEADS; i++)
    {
        //cria threads
        pthread_create(&threads[i], NULL, (void*)task, (void*) &pessoas[i]);
    }

    //espera as threads terminarem para sguir a main
    for (int i = 0; i < NUM_TRHEADS; i++)
    {
        pthread_join(threads[i], NULL);
    }

    return 0;
}

