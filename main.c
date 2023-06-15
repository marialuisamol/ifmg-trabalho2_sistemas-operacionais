#include <stdlib.h>
#include <stdio.h>
#include "util.h"
#include <assert.h>
#include <pthread.h>

int main(int argc, char const *argv[])
{
    pessoa pessoas[6];
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

    return 0;
}
