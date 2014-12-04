
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "carregador.h"
#include "methods.h"
#include "mnemonics.h"
#include "instructions.h"

char *caminho = ".\\";

classStructure **classArray = NULL;
staticStruct *classStaticArray = NULL;
int32_t numClasses = 0;

void replace(char * o_string, char * s_string, char * r_string);

/*!
 * Carrega uma classe pelo seu nome \a className.
 * Será carregada para o vetor classArray no novo índice (numClasses -1).
 * \return Class Index
 */
int32_t carregarClass(char *className) {
	int32_t i, classIndex;
	char *path;
	methodInfo *staticMethod;

	if (className == NULL) {
		return -1;
	}

	/* procura em classArray se a classe já foi carregada */
	for (i = 0; i < numClasses; i++) {
		if (strcmp(className, getClassName(classArray[i])) == 0)
			return i;
	}

	/* aumenta o vetor classArray */
	numClasses++;
	classIndex = numClasses;
	classArray = realloc(classArray, (classIndex*sizeof(classStructure *)));
	classStaticArray = realloc(classStaticArray, (classIndex*sizeof(staticStruct)));

	/* cria o path completo para o arquivo da classe base_path + className + .class */
	path = malloc(strlen(caminho) + strlen(className) + 7);

	if (strstr(className,".class") != NULL) {
		sprintf(path, "%s%s", caminho, className);
	} else {
		sprintf(path, "%s%s.class", caminho, className);
	}

	/* lê a nova classe */
	if ((classArray[classIndex-1] = read_class_file(path)) == NULL) {
		printf(" Erro: Não foi possível abrir arquivo informado.\n");
		exit(1);
	}

	classStaticArray[classIndex-1].className = malloc(strlen(className)+1);
	memcpy(classStaticArray[classIndex-1].className, className, strlen(className));
	classStaticArray[classIndex-1].fieldCount = classArray[classIndex-1]->fieldCount;
	classStaticArray[classIndex-1].value = malloc(classArray[classIndex-1]->fieldCount * sizeof(u8));

	/* Executa o método de Init Static caso tenha */
	if ((staticMethod = getInitStaticMethod(classArray[classIndex-1])) != NULL) {
		prepararMetodo(classArray[classIndex-1], staticMethod);
		runMethod();
	}

	//Modificado do original
	// O caminho das classes JAVA vinha errado, a barra do caminho era trocada
	//================================================================================

	char * parent = getParentName(classArray[classIndex-1]);
	if(parent != NULL) {
		replace(parent, "/", "\\");
	}

	/* carrega a superclasse da classe carregada */
	carregarClass(parent);
	//	loadClass(getParentName(classArray[classIndex-1]));

	//================================================================================

	return classIndex-1;
}


/*!
 * Retorna string com nome da classe a partir de ponteiro para ClassFile
 */
char *getClassName(classStructure *class) {
	u2 thisClass = class->thisClass;
	u2 nameIndex = ((struct CONSTANT_Class_info*)class->constantPool[thisClass-1])->nameIndex;
	return getName( class , nameIndex );
}

/*!
 * Retorna string com nome da super classe a partir de ponteiro para ClassFile
 */
char *getParentName(classStructure *class) {
	u2 superClass, nameIndex, length;
	u1 *name;
	char *className;

	superClass = class->superClass;

	if (superClass == 0) {
		return NULL;
	}

	nameIndex = ((struct CONSTANT_Class_info*)(class->constantPool[superClass-1]))->nameIndex;

	length = ((struct CONSTANT_Utf8_info*) (class->constantPool[nameIndex-1]))->length;
	name = ((struct CONSTANT_Utf8_info*) (class->constantPool[nameIndex-1]))->bytes;

	className = malloc(sizeof(u2) * length+1);

	strncpy(className, (char *)name, length);
	className[length] = '\0';

	return className;
}


/*!
 * Retorna ponteiro pra ClassFile a partir de string \a className.
 */
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

/*
 * Não consegui colocar essas definicoes no .h, nao sei o motivo.
 * Entao tive q fazer esses dois getters.
 */
classStructure * getClassByIndex(int index) {
	if (index >= numClasses) {
		return NULL;
	}
	return classArray[index];
}

int getNumClasses() {
	return numClasses;
}

int32_t getFieldIndexByNameAndDesc(char *className, char *name, u2 name_len, char *desc, u2 desc_len) {
	int32_t i;
	classStructure *main_class;
	u1 *m_name, *m_desc;
	u2 m_name_len, m_desc_len;

	main_class = getClassByName(className);

	if (!main_class) {
		return -2;
	}

	/* Procura pelo Field de acordo com o nome e o desc */
	for (i = 0; main_class && i < main_class->fieldCount; i++) {
		m_name = ((struct CONSTANT_Utf8_info *)(main_class->constantPool[(main_class->fields[i].nameIndex-1)]))->bytes;
		m_name_len = ((struct CONSTANT_Utf8_info *)(main_class->constantPool[(main_class->fields[i].nameIndex-1)]))->length;

		m_desc = ((struct CONSTANT_Utf8_info *)(main_class->constantPool[(main_class->fields[i].descriptorIndex-1)]))->bytes;
		m_desc_len = ((struct CONSTANT_Utf8_info *)(main_class->constantPool[(main_class->fields[i].descriptorIndex-1)]))->length;

		if (name_len != m_name_len)
			continue;
		if (desc_len != m_desc_len)
			continue;

		if ((strncmp((char *)name, (char *)m_name , m_name_len) == 0)
				&& (strncmp((char *)desc, (char *)m_desc , m_desc_len) == 0)) {
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

/**
 * The replace function
 *
 * Searches all of the occurrences using recursion
 * and replaces with the given string
 * @param char * o_string The original string
 * @param char * s_string The string to search for
 * @param char * r_string The replace string
 * @return void The o_string passed is modified
 */
void replace(char * o_string, char * s_string, char * r_string) {
	//a buffer variable to do all replace things
	char buffer[4096];
	//to store the pointer returned from strstr
	char * ch;

	//first exit condition
	if(!(ch = strstr(o_string, s_string)))
		return;

	//copy all the content to buffer before the first occurrence of the search string
	strncpy(buffer, o_string, ch-o_string);

	//prepare the buffer for appending by adding a null to the end of it
	buffer[ch-o_string] = 0;

	//append using sprintf function
	sprintf(buffer+(ch - o_string), "%s%s", r_string, ch + strlen(s_string));

	//empty o_string for copying
	o_string[0] = 0;
	strcpy(o_string, buffer);
	//pass recursively to replace other occurrences
	return replace(o_string, s_string, r_string);
}
