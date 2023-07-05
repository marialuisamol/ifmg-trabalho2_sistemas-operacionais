#ifndef FUNC_H
#define FUNC_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>

typedef struct tipo_pessoa
{
    char* nome;
    int prioridade;
    int prioridade_temp;                                     
    int frustracoes;
    int uso_forno;                                    
    struct tipo_pessoa *proximo;
    pthread_cond_t cond; // Variáveis de condição

} tipo_pessoa;

typedef struct 
{
    tipo_pessoa *primeiro;
    tipo_pessoa *ultimo;
    int qnt;
    
} tipo_fila;

int vazia_fila();
void cria_fila();
void enfileira(tipo_pessoa *pessoa);
tipo_pessoa desenfileira();
tipo_pessoa* consulta_maior();
void envelhece(tipo_pessoa *ultimo);

void aumenta_prioridade(tipo_pessoa *pessoa);
void tarefa(void* args);
void tarefa_faxineiro(void* args);

#endif