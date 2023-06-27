#ifndef FUNC.H
#define FUNC.H
#include "util.h"
#include <pthread.h>

void aumentaprioridade(tipo_pessoa pessoa);
void enfileira(tipo_pessoa pessoa);
tipo_pessoa desenfileira(tipo_fila *fila);
void comportamento();

#endif