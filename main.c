#include <stdlib.h>
#include "util.h"
#include "func.h"
#include <pthread.h>

#define NUM_TRHEADS 3
#define USO_FORNO 1

int main(int argc, char const *argv[])
{
    tipo_pessoa pessoas[NUM_TRHEADS]; //vetor de pessoas presentes na dinamica da republica
    pthread_t threads[NUM_TRHEADS]; //identificador de trheads
    
    // setando vetor nome x prioridade
    // calouro = 1; veterano = 2; senior = 3

    pessoas[0].nome = "carlos";
    pessoas[0].prioridade = 3;
    pessoas[0].prioridade_temp = pessoas[0].prioridade;
    pessoas[0].uso_forno = USO_FORNO;
    pthread_cond_init(&pessoas[0].cond, NULL); 


    pessoas[1].nome = "saulo";
    pessoas[1].prioridade = 2;
    pessoas[1].prioridade_temp = pessoas[1].prioridade;
    pessoas[1].uso_forno = USO_FORNO;
    pthread_cond_init(&pessoas[1].cond, NULL); 


    pessoas[2].nome = "vera";
    pessoas[2].prioridade = 1;
    pessoas[2].prioridade_temp = pessoas[2].prioridade;
    pessoas[2].uso_forno = USO_FORNO;
    pthread_cond_init(&pessoas[2].cond, NULL); 


    // pessoas[3].nome = "sandro";
    // pessoas[3].prioridade = 3;
    // pessoas[3].prioridade_temp = pessoas[3].prioridade;
    // pessoas[3].uso_forno = USO_FORNO;

    // pessoas[4].nome = "vani";
    // pessoas[4].prioridade = 2;
    // pessoas[4].prioridade_temp = pessoas[4].prioridade;
    // pessoas[4].uso_forno = USO_FORNO;

    // pessoas[5].nome = "camila";
    // pessoas[5].prioridade = 1;
    // pessoas[5].prioridade_temp = pessoas[5].prioridade;
    // pessoas[5].uso_forno = USO_FORNO;

    cria_fila(); //inicializa a fila
    
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

