#ifndef MNEMONICS_H_
#define MNEMONICS_H_

#include <stdlib.h>
#include <string.h>

typedef struct OPCODE_info {
	char descricao[20];
	unsigned short operandos_count;
	unsigned int *operandos_index;
} opcode_informacao;

void populate_opcode_info();

opcode_informacao *op_info;

#endif
