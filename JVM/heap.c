
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "heap.h"

#include "const.h"
#include "inicializador.h"
#include "tipos.h"

static u4 indexHeap;
static u4 maxHeap;

void newHeap() {
	heap = calloc(sizeof(struct Object*), INI_HEAP);
	indexHeap = 0;
	maxHeap = INI_HEAP;
}

struct Object* newObject(classStructure *this) {
	struct Object *object;
	u4 i, j, contador;
	u2 index;
	char descritor[200];
	cpInfo *descritorStruct;

	if (!this) {
		return NULL;
	}

	if (indexHeap == maxHeap) {
		heap = realloc(heap, maxHeap + INI_HEAP);
		if (heap == NULL) {
			printf(" Erro: Sem memoria\n");
			exit(1);
		}
		maxHeap += INI_HEAP;
	}

	object = calloc(sizeof(struct Object),1);
	object->this = this;
	object->super = newObject(getClassByName(getParentName(this)));

	contador = 0;
	for (i = 0; i < this->fieldCount; i++) {
		contador++;
		index = this->fields[i].descriptorIndex;
		descritorStruct = &(this->constantPool[index - 1]);
		memcpy(descritor, descritorStruct->type.Utf8.bytes, descritorStruct->type.Utf8.length);

		if (descritor[0] == 'D' || descritor[0] == 'J') {
			contador++;
		}
	}

	object->fields = calloc(sizeof(u4), contador);
	object->fields_index = calloc(sizeof(u4), contador);

	for (i = 0, j = 0; i < this->fieldCount; i++, j++) {
		object->fields_index[j] = this->fields[i].nameIndex;

		index = this->fields[i].descriptorIndex;
		descritorStruct = &(this->constantPool[index - 1]);
		memcpy(descritor, descritorStruct->type.Utf8.bytes, descritorStruct->type.Utf8.length);

		if (descritor[0] == 'D' || descritor[0] == 'J') {
			j++;
			object->fields_index[j] = -1;
		}
	}

	heap[indexHeap] = object;
	indexHeap++;
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
	return convert_2x32_to_64_bits(object->fields[i],object->fields[i+1]);
}

void setObjectField(struct Object* object, u4 nameIndex, u4 value) {
	int32_t i = 0;
	while (object->fields_index[i] != nameIndex) {
		i++;
	}
	object->fields[i] = value;
}

void setObjectFieldWide(struct Object* object, u4 nameIndex, u8 value) {
	int32_t i = 0;
	u4 low, high;

	while (object->fields_index[i] != nameIndex) {
		i++;
	}

	convert_64_bits_to_2x32(value, &low, &high);
	object->fields[i] = low;
	object->fields[i+1] = high;
}

void* newArray(u4 count, u1 type) {
	u4 size;
	void *array;

	switch (type) {
		case TYPE_reference:
			size = 4; /*reference*/
			break;
		case TYPE_boolean:
			size = 1;/*boolean*/
			break;
		case TYPE_char:
			size = 2;/*char*/
			break;
		case TYPE_float:
			size= 4;/*float*/
			break;
		case TYPE_double:
			size = 8;/*double*/
			break;
		case TYPE_byte:
			size = 1;/*byte*/
			break;
		case TYPE_short:
			size = 2;/*short*/
			break;
		case TYPE_int:
			size = 4;/*int*/
			break;
		case TYPE_long:
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

