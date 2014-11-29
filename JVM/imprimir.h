
#ifndef IMPRIMIR_H_
#define IMPRIMIR_H_

#include <stdlib.h>
#include <string.h>

typedef struct OPCODE_info {
	char descricao[50];
	unsigned short operandos_count;
	unsigned int *operandos_index;
} opcode_informacao;

void carregar_opcode_informacao();

opcode_informacao *op_informacao;

#endif
