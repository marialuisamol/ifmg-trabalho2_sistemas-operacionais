#ifndef UTIL.H
#define UTIL.H

typedef struct tipo_pessoa
{
    int prioridade;
    int prioridade_temp;
    char* nome;
    int frustracoes;                                       

}tipo_pessoa;

typedef struct tipo_fila
{
    tipo_pessoa *pessoa;
    int *proximo;
    int *anterior;

}tipo_fila;


#endif