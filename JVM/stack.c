#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

static u4 stack[MAX_STACK];
static u4 stack_top;
static u4 frame_base;

void newStack()
{
	stack_top = -1;
	frame_base = 0;
}

void push(u4 value)
{
	if (stack_top == MAX_STACK)
	{
		printf(" Erro: Pilha sem memoria.\n");
		exit(1);
	}
	stack[++stack_top] = value;
}

void pushU8(u8 value)
{
	u4 low, high;

	convert_64_bits_to_2x32( value , &low , &high );
	push( high );
	push( low );
}


u4 pop()
{
	if (stack_top < frame_base)
	{
		printf(" Erro: Acesso a posicao invalida da Stack.\n\n");
		return 0;
	}
	return stack[stack_top--];
}

void newStackFrame()
{
	push(frame_base);
	frame_base = stack_top;
}

void freeStackFrame()
{
	u4 previous_frame;

	stack_top = frame_base;
	previous_frame = pop();
	if (previous_frame > frame_base)
	{
		printf(" Erro: Frame nao existente\n");
		return;
	}
	frame_base = previous_frame;
}
