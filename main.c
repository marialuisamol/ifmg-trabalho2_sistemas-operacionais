#include <stdlib.h>
#include <stdio.h>
#include "util.h"
#include "func.h"
#include <assert.h>
#include <string.h>
#include <pthread.h>

#define NUM_TRHEADS 7

int main(int argc, char const *argv[])
{
    tipo_pessoa pessoas[NUM_TRHEADS]; //vetor de pessoas presentes na dinamica da republica
    // setando vetor nome x prioridade
    pessoas[0].nome = "carlos";
    pessoas[0].prioridade = 3;

    pessoas[1].nome = "saulo";
    pessoas[1].prioridade = 2;

    pessoas[2].nome = "vera";
    pessoas[2].prioridade = 1;

    pessoas[3].nome = "sandro";
    pessoas[3].prioridade = 3;

    pessoas[4].nome = "vani";
    pessoas[4].prioridade = 2;

    pessoas[5].nome = "camila";
    pessoas[5].prioridade = 1;

    pessoas[6].nome = "frederico";
    pessoas[6].prioridade = 0;

    for (int i = 0; i < NUM_TRHEADS-1; i++)
    {
        printf("Entre com a quantidade de vezes que %s vai utilizar o forno: ", pessoas[i].nome);
        scanf("%d", &pessoas[i].uso_forno);
    }
    

    pthread_t threads[NUM_TRHEADS]; //identificador de trheads
    for (int i = 0; i < NUM_TRHEADS-1; i++)
    {
        //cria threads
        pthread_create(&threads[i], NULL, (void*)comportamento, (void*) &pessoas[i]);
    }

    //espera as threads terminarem para sguir a main
    for (int i = 0; i < NUM_TRHEADS; i++)
    {
        pthread_join(threads[i], NULL);
    }

    return 0;
}
