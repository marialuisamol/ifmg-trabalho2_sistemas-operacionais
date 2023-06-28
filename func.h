#ifndef FUNC.H
#define FUNC.H
#include "util.h"
#include <pthread.h>

int vazia_fila(tipo_fila *fila);
void aumenta_prioridade(tipo_pessoa pessoa);
void cria_fila();
void enfileira(tipo_pessoa pessoa);
tipo_pessoa desenfileira();
void usa_forno(tipo_pessoa pessoa);

#endif