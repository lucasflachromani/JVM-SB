#ifndef HEAP_H
#define HEAP_H

#include "tipos.h"

#define HEAP_INIT 32

struct Object {
	classStructure *this;
	struct Object *super;
	u4 *fields;
	u4 *fields_index;
};

struct array{
	u4 ref;
	u4 size;
};

/*****************************
 * REFERENCIA PARA UM OBJETO
 *****************************/
struct Object **heap;

/*****************************
 * Vetor com o tamanho dos arrays
 *****************************/
struct array *arrayLength;

/*****************************
 * Num de arrays alocados
 *****************************/
u4 numArrays;

void newHeap();
struct Object* newObject(classStructure *this);
u4 getObjectField(struct Object* object, u4 nameIndex);
u8 getObjectFieldWide(struct Object* object, u4 nameIndex);
void setObjectField(struct Object* object, u4 nameIndex, u4 value);
void setObjectFieldWide(struct Object* object, u4 nameIndex, u8 value);
void* newArray(u4 count, u1 type);

#endif
