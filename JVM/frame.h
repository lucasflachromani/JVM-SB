#ifndef FRAME_H
#define FRAME_H

#include "stack.h"
#include "types.h"
#include "carregador.h"

struct frame {
	u4				*fields;
	cpInfo			*constantPool;
	classStructure 	*class;
	u2 				maxStack;
	u2 				maxLocals;
	u4 				codeLength;
	u1 				*code;
	u4 				pc;
};

/**
 Pilha de frame.
 */
struct frame_stack {
	struct frame *value;
	struct frame_stack *next;
};

struct frame *frameAtual;

void newFrame(classStructure *class, cpInfo *constantPool, Code_attribute *code_attribute);
void freeFrame();

#endif
