
#include "inicializador.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "instrucoes.h"
#include "metodos.h"

char *caminho = ".\\";

classStructure **classArray = NULL;
staticStruct *classStaticArray = NULL;
int32_t numClasses = 0;

//Carrega uma classe
int32_t carregarClass(char *className) {
	int32_t i, classIndex;
	char *path;
	methodInfo *staticMethod;

	if (className == NULL) {
		return -1;
	}

	for (i = 0; i < numClasses; i++) {
		if (strcmp(className, getClassName(classArray[i])) == 0)
			return i;
	}

	numClasses++;
	classIndex = numClasses;
	classArray = realloc(classArray, (classIndex*sizeof(classStructure *)));
	classStaticArray = realloc(classStaticArray, (classIndex*sizeof(staticStruct)));
	path = malloc(strlen(caminho) + strlen(className) + 7);

	if (strstr(className,".class") != NULL) {
		sprintf(path, "%s%s", caminho, className);
	} else {
		sprintf(path, "%s%s.class", caminho, className);
	}

	if ((classArray[classIndex-1] = read_class_file(path)) == NULL) {
		printf(" Erro: Nao foi possivel abrir o arquivo informado.\n");
		exit(1);
	}

	classStaticArray[classIndex-1].className = malloc(strlen(className)+1);
	memcpy(classStaticArray[classIndex-1].className, className, strlen(className));
	classStaticArray[classIndex-1].fieldCount = classArray[classIndex-1]->fieldCount;
	classStaticArray[classIndex-1].value = malloc(classArray[classIndex-1]->fieldCount * sizeof(u8));

	if ((staticMethod = getInitStaticMethod(classArray[classIndex-1])) != NULL) {
		prepararMetodo(classArray[classIndex-1], staticMethod);
		executarMetodo();
	}

	char * parent = getParentName(classArray[classIndex-1]);
	if(parent != NULL) {
		trocaCaracter(parent, "/", "\\");
	}
	carregarClass(parent);
	return classIndex-1;
}

//Retorna o nome da classe
char *getClassName(classStructure *class) {
	u2 thisClass = class->thisClass;
	u2 nameIndex = (class->constantPool[thisClass-1]).type.Class.nameIndex;
	return getName( class , nameIndex );
}

//Retorna o nome da superclasse
char *getParentName(classStructure *class) {
	u2 superClass, nameIndex, length;
	u1 *name;
	char *className;

	superClass = class->superClass;
	if (superClass == 0) {
		return NULL;
	}
	nameIndex = class->constantPool[superClass-1].type.Class.nameIndex;
	length = class->constantPool[nameIndex-1].type.Utf8.length;
	name = class->constantPool[nameIndex-1].type.Utf8.bytes;
	className = malloc(sizeof(u2) * length+1);
	strncpy(className, (char *)name, length);
	className[length] = '\0';
	return className;
}


//Retorna uma class a partir do nome
classStructure * getClassByName(char *className) {
	int i;
	if (!className) {
		return NULL;
	}
	for (i = 0; i < numClasses; i++) {
		if (strcmp(className, getClassName(classArray[i])) == 0)
			return classArray[i];
	}
	return NULL;
}

classStructure * getClassByIndex(int index) {
	if (index >= numClasses) {
		return NULL;
	}
	return classArray[index];
}

int getNumClasses() {
	return numClasses;
}

int32_t getFieldIndexByNameAndDesc(char *className, char *name, u2 nameLen, char *desc, u2 descLen) {
	int32_t i;
	classStructure *main_class;
	u1 *m_name, *m_desc;
	u2 m_name_len, m_desc_len;

	main_class = getClassByName(className);
	if (!main_class) {
		return -2;
	}
	for (i = 0; main_class && i < main_class->fieldCount; i++) {
		m_name = main_class->constantPool[(main_class->fields[i].nameIndex-1)].type.Utf8.bytes;
		m_name_len = main_class->constantPool[(main_class->fields[i].nameIndex-1)].type.Utf8.length;
		m_desc = main_class->constantPool[(main_class->fields[i].descriptorIndex-1)].type.Utf8.bytes;
		m_desc_len = main_class->constantPool[(main_class->fields[i].descriptorIndex-1)].type.Utf8.length;
		if (nameLen != m_name_len) {
			continue;
		}
		if (descLen != m_desc_len) {
			continue;
		}
		if ((strncmp((char *)name, (char *)m_name , m_name_len) == 0) && (strncmp((char *)desc, (char *)m_desc , m_desc_len) == 0)) {
			return i;
		}
	}
	return -1;
}

int32_t getClassIndex(classStructure *class_file) {
	int i;
	for (i = 0; i < numClasses; i++) {
		if (classArray[i] == class_file) {
			return i;
		}
	}
	return -1;
}

u8 getStaticFieldValue(int32_t classIndex, int32_t field_index) {
	return classStaticArray[classIndex].value[field_index];
}

void setStaticFieldValue(int32_t classIndex, int32_t field_index, u8 value) {
	classStaticArray[classIndex].value[field_index] = value;
}

//substituicao de substrings
void trocaCaracter(char * stringOriginal, char * subString, char * stringSubstituta) {
	char buffer[4096];
	char * ch;
	if(!(ch = strstr(stringOriginal, subString))) {
		return;
	}
	strncpy(buffer, stringOriginal, ch-stringOriginal);
	buffer[ch-stringOriginal] = 0;
	sprintf(buffer+(ch - stringOriginal), "%s%s", stringSubstituta, ch + strlen(subString));
	stringOriginal[0] = 0;
	strcpy(stringOriginal, buffer);
	return trocaCaracter(stringOriginal, subString, stringSubstituta);
}
