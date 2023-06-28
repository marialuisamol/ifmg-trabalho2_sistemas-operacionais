#ifndef FUNC.H
#define FUNC.H

#include "util.h"
#include <pthread.h>

int vazia_fila();
void cria_fila();
void enfileira(tipo_pessoa *pessoa);
tipo_pessoa desenfileira();

void aumenta_prioridade(tipo_pessoa *pessoa);
void task(void* args);

#endif