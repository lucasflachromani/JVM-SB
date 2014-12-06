
#include "pilha.h"

#include <stdio.h>
#include <stdlib.h>

static u4 pilha[MAX];
static u4 topoPilha;
static u4 baseFrame;

void newPilha() {
	topoPilha = -1;
	baseFrame = 0;
}

void push(u4 valor) {
	if (topoPilha == MAX) {
		printf(" Erro: Pilha sem memoria.\n");
		exit(1);
	}
	pilha[++topoPilha] = valor;
}

void pushU8(u8 valor) {
	u4 low, high;
	converter64bitsTo2x32(valor , &low , &high);
	push(high);
	push(low);
}

u4 pop() {
	if (topoPilha < baseFrame) {
		printf(" Erro: Acesso a posicao invalida da pilha.\n\n");
		return 0;
	}
	return pilha[topoPilha--];
}

void newFramePilha() {
	push(baseFrame);
	baseFrame = topoPilha;
}

void freeFramePilha() {
	u4 frameAnterior;
	topoPilha = baseFrame;
	frameAnterior = pop();
	if (frameAnterior > baseFrame) {
		printf(" Erro: Frame nao existente\n");
		return;
	}
	baseFrame = frameAnterior;
}
