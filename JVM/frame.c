#include "frame.h"
#include <stdlib.h>

//	Frame atual e' o topo da pilha
static struct frame_stack *stack = NULL;

void newFrame(classStructure *class, cpInfo *constantPool, attributeInfo *attribute) {
	struct frame_stack *new;
	new = calloc(sizeof(struct frame_stack), 1);
	new->value = calloc(sizeof(struct frame), 1);
	new->next = stack;

	stack = new;
	stack->value->class = class;
	stack->value->constantPool = constantPool; 
	stack->value->maxStack = attribute->type.Code.maxStack;
	stack->value->maxLocals = attribute->type.Code.maxLocals;
	stack->value->codeLength = attribute->type.Code.codeLength;		
	stack->value->code = attribute->type.Code.code;
	stack->value->fields = calloc(sizeof(u4), stack->value->maxLocals);
	stack->value->pc = 0;
	frameAtual = stack->value;
	newStackFrame();
}

void freeFrame() {
	struct frame_stack *next;

	if (stack->next != NULL) {
		frameAtual = stack->next->value;
	} else {
		frameAtual = NULL;
	}

	next = stack->next;
	free(stack->value->fields);
	free(stack->value);
	free(stack);
	stack = next;
	freeStackFrame();
}
