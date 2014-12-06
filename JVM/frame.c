#include "frame.h"
#include <stdlib.h>

/*****************************
 * Frame mais recente, topo da pilha
 *****************************/
static struct framePilha *pilha = NULL;

void newFrame(classStructure *class, cpInfo *constantPool, attributeInfo *attribute) {
	struct framePilha *new;
	new = calloc(sizeof(struct framePilha), 1);
	new->valor = calloc(sizeof(struct frame), 1);
	new->next = pilha;

	pilha = new;
	pilha->valor->class = class;
	pilha->valor->constantPool = constantPool; 
	pilha->valor->maxStack = attribute->type.Code.maxStack;
	pilha->valor->maxLocals = attribute->type.Code.maxLocals;
	pilha->valor->codeLength = attribute->type.Code.codeLength;		
	pilha->valor->code = attribute->type.Code.code;
	pilha->valor->fields = calloc(sizeof(u4), pilha->valor->maxLocals);
	pilha->valor->pc = 0;
	frameAtual = pilha->valor;
	newStackFrame();
}

void freeFrame() {
	struct framePilha *proximo;

	if (pilha->next != NULL) {
		frameAtual = pilha->next->valor;
	} else {
		frameAtual = NULL;
	}

	proximo = pilha->next;
	free(pilha->valor->fields);
	free(pilha->valor);
	free(pilha);
	pilha = proximo;
	freeStackFrame();
}
