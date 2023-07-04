#include "func.h"

#define NUM_TRHEADS 3
#define USO_FORNO 2

int main(int argc, char const *argv[])
{
    tipo_pessoa alunos[NUM_TRHEADS]; //vetor de alunos presentes na dinamica da republica
    pthread_t threads[NUM_TRHEADS]; //identificador de trheads
    
    // setando vetor nome x prioridade
    // calouro = 1; veterano = 2; senior = 3

    alunos[0].nome = "Carlos";
    alunos[0].prioridade = 1;
    alunos[0].prioridade_temp = alunos[0].prioridade;
    alunos[0].uso_forno = USO_FORNO;
    pthread_cond_init(&alunos[0].cond, NULL); 


    alunos[1].nome = "Saulo";
    alunos[1].prioridade = 3;
    alunos[1].prioridade_temp = alunos[1].prioridade;
    alunos[1].uso_forno = USO_FORNO;
    pthread_cond_init(&alunos[1].cond, NULL); 


    alunos[2].nome = "Vera";
    alunos[2].prioridade = 2;
    alunos[2].prioridade_temp = alunos[2].prioridade;
    alunos[2].uso_forno = USO_FORNO;
    pthread_cond_init(&alunos[2].cond, NULL); 


    // alunos[3].nome = "Sandro";
    // alunos[3].prioridade = 3;
    // alunos[3].prioridade_temp = alunos[3].prioridade;
    // alunos[3].uso_forno = USO_FORNO;
    // pthread_cond_init(&alunos[3].cond, NULL); 

    // alunos[4].nome = "Vani";
    // alunos[4].prioridade = 2;
    // alunos[4].prioridade_temp = alunos[4].prioridade;
    // alunos[4].uso_forno = USO_FORNO;
    // pthread_cond_init(&alunos[4].cond, NULL); 

    // alunos[5].nome = "Camila";
    // alunos[5].prioridade = 1;
    // alunos[5].prioridade_temp = alunos[5].prioridade;
    // alunos[5].uso_forno = USO_FORNO;
    // pthread_cond_init(&alunos[5].cond, NULL); 

    cria_fila(); //inicializa a fila
    
    for (int i = 0; i < NUM_TRHEADS; i++)
    {
        //cria threads dos alunos
        pthread_create(&threads[i], NULL, (void*)tarefa, (void*) &alunos[i]);
    }

    //cria a thread do monitor
    //pthread_create(&threads[NUM_TRHEADS], NULL, (void*)tarefa_faxineiro, NULL);

    //espera as threads terminarem para sguir a main
    for (int i = 0; i < NUM_TRHEADS; i++)
    {
        pthread_join(threads[i], NULL);
    }

    return 0;
}
