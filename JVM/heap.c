#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "heap.h"
#include "const.h"
#include "inicializador.h"
#include "tipos.h"

static u4 heap_index;
static u4 heap_max;

void newHeap() {
	heap = calloc(sizeof(struct Object*), HEAP_INIT);
	heap_index = 0;
	heap_max = HEAP_INIT;
}

struct Object* newObject(classStructure *this) {
	struct Object *object;
	u4 i, j, counter;
	u2 index;
	char descriptor[200];
	cpInfo *desc_struct;


	if (!this) {
		return NULL;
	}

	if (heap_index == heap_max) {
		heap = realloc(heap, heap_max + HEAP_INIT);
		if (heap == NULL) {
			printf(" Erro: Sem memoria\n");
			exit(1);
		}
		heap_max += HEAP_INIT;
	}

	object = calloc(sizeof(struct Object),1);
	object->this = this;
	object->super = newObject(getClassByName(getParentName(this)));

	counter = 0;
	for (i = 0; i < this->fieldCount; i++) {
		counter++;
		index = this->fields[i].descriptorIndex;
		desc_struct = &(this->constantPool[index - 1]);
		memcpy(descriptor, desc_struct->type.Utf8.bytes, desc_struct->type.Utf8.length);

		if (descriptor[0] == 'D' || descriptor[0] == 'J') {
			counter++;
		}
	}

	object->fields = calloc(sizeof(u4), counter);
	object->fields_index = calloc(sizeof(u4), counter);

	for (i = 0, j = 0; i < this->fieldCount; i++, j++) {
		object->fields_index[j] = this->fields[i].nameIndex;

		index = this->fields[i].descriptorIndex;
		desc_struct = &(this->constantPool[index - 1]);
		memcpy(descriptor, desc_struct->type.Utf8.bytes, desc_struct->type.Utf8.length);

		if (descriptor[0] == 'D' || descriptor[0] == 'J') {
			j++;
			object->fields_index[j] = -1;
		}
	}

	heap[heap_index] = object;
	heap_index++;
	return object;
}

u4 getObjectField(struct Object* object, u4 nameIndex) {
	int32_t i = 0;
	while (object->fields_index[i] != nameIndex) {
		i++;
	}
	return object->fields[i];
}

u8 getObjectFieldWide(struct Object* object, u4 nameIndex) {
	int32_t i = 0;
	while (object->fields_index[i] != nameIndex) {
		i++;
	}
	return converter2x32To64bits(object->fields[i],object->fields[i+1]);
}

void setObjectField(struct Object* object, u4 nameIndex, u4 valor) {
	int32_t i = 0;
	while (object->fields_index[i] != nameIndex) {
		i++;
	}
	object->fields[i] = valor;
}

void setObjectFieldWide(struct Object* object, u4 nameIndex, u8 valor) {
	int32_t i = 0;
	u4 low, high;

	while (object->fields_index[i] != nameIndex) {
		i++;
	}

	converter64bitsTo2x32(valor, &low, &high);
	object->fields[i] = low;
	object->fields[i+1] = high;
}

void* newArray(u4 count, u1 type) {
	u4 size;
	void *array;

	switch (type) {
		case TYPE_REFERENCE:
			size = 4; /*reference*/
			break;
		case TYPE_BOOLEAN:
			size = 1;/*boolean*/
			break;
		case TYPE_CHAR:
			size = 2;/*char*/
			break;
		case TYPE_FLOAT:
			size= 4;/*float*/
			break;
		case TYPE_DOUBLE:
			size = 8;/*double*/
			break;
		case TYPE_BYTE:
			size = 1;/*byte*/
			break;
		case TYPE_SHORT:
			size = 2;/*short*/
			break;
		case TYPE_INT:
			size = 4;/*int*/
			break;
		case TYPE_LONG:
			size = 8;/*long*/
			break;
	}

	array = calloc(count, size);
	numArrays++;
	arrayLength = realloc (arrayLength, sizeof(struct array)*numArrays);
	arrayLength[numArrays-1].size = size;
	arrayLength[numArrays-1].ref = (u4)array;

	return array;
}

