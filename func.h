#ifndef FUNC_H
#define FUNC_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>

int vazia_fila();
void cria_fila();
void enfileira(tipo_pessoa *pessoa);
tipo_pessoa desenfileira();

void aumenta_prioridade(tipo_pessoa *pessoa);
void tarefa(void* args);

#endif