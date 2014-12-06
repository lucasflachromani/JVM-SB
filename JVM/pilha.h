#ifndef STACK_H
#define STACK_H

#include "tipos.h"

#define MAX 100

void newPilha();
void push(u4 value);
void pushU8(u8 value);
u4 pop();
void newFramePilha();
void freeFramePilha();

#endif
