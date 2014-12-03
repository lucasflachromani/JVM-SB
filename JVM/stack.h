#ifndef STACK_H
#define STACK_H

#include "types.h"

#define MAX_STACK 100

void newStack();
void push(u4 value);
void pushU8(u8 value);
u4 pop();
void newStackFrame();
void freeStackFrame();

#endif
