#include "frame.h"
#include <stdlib.h>

//	Frame atual e' o topo da pilha
static struct frame_stack *stack = NULL;

void newFrame(classStructure *class, void **constantPool, Code_attribute *code_attribute) {
	struct frame_stack *new;
	new = calloc(sizeof(struct frame_stack), 1);
	new->value = calloc(sizeof(struct frame), 1);
	new->next = stack;

	stack = new;
	stack->value->class = class;
	stack->value->constantPool = constantPool; 
	stack->value->maxStack = code_attribute->maxStack;
	stack->value->maxLocals = code_attribute->maxLocals;
	stack->value->codeLength = code_attribute->codeLength;		
	stack->value->code = code_attribute->code;
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
