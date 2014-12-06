#ifndef FRAME_H
#define FRAME_H

#include "inicializador.h"
#include "pilha.h"
#include "tipos.h"

struct frame {
	u4				* fields;
	cpInfo			* constantPool;
	classStructure 	* class;
	u2 				maxStack;
	u2 				maxLocals;
	u4 				codeLength;
	u1 				* code;
	u4 				pc;
};

/*****************************
 * PILHA DO FRAME
 *****************************/
struct framePilha {
	struct frame *valor;
	struct framePilha *next;
};

struct frame *frameAtual;

void newFrame(classStructure *class, cpInfo *constantPool, attributeInfo *attribute);
void freeFrame();

#endif
