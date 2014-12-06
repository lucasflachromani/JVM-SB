
#include "metodos.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "classloader.h"
#include "const.h"
#include "frame.h"
#include "inicializador.h"
#include "instrucoes.h"

extern struct frame *frameAtual;

methodInfo * getMainMethod() {
	int i;
	classStructure *main_class;
	u1 *name, *desc;
	u2 name_length, desc_length;

	main_class = getClassByIndex(0);

	/* procura por método main([LJava/lang/String;)V */
	for(i = 0; i < main_class->methodCount; i++) {

		name = main_class->constantPool[(main_class->methods[i].nameIndex-1)].type.Utf8.bytes;
		name_length = main_class->constantPool[(main_class->methods[i].nameIndex-1)].type.Utf8.length;

		desc = main_class->constantPool[(main_class->methods[i].descriptorIndex-1)].type.Utf8.bytes;
		desc_length = main_class->constantPool[(main_class->methods[i].descriptorIndex-1)].type.Utf8.length;

		if((strncmp("main",(char *)name, name_length) == 0)
				&&(strncmp("([Ljava/lang/String;)V",(char *)desc, desc_length) == 0))
			return &(main_class->methods[i]);
	}

	return NULL;
}


methodInfo * getInitStaticMethod(classStructure *main_class) {
	int i;
	u1 *name, *desc;
	u2 name_length, desc_length;

	/* procura por método main <clinit>()V */
	for(i = 0; i < main_class->methodCount; i++) {

		name = main_class->constantPool[(main_class->methods[i].nameIndex-1)].type.Utf8.bytes;
		name_length = main_class->constantPool[(main_class->methods[i].nameIndex-1)].type.Utf8.length;

		desc = main_class->constantPool[(main_class->methods[i].descriptorIndex-1)].type.Utf8.bytes;
		desc_length = main_class->constantPool[(main_class->methods[i].descriptorIndex-1)].type.Utf8.length;

		if((strncmp("<clinit>",(char *)name, name_length) == 0)
				&&(strncmp("()V",(char *)desc, desc_length) == 0))
			return &(main_class->methods[i]);
	}

	return NULL;
}


methodInfo * getMethodByNameAndDescIndex(classStructure *main_class, classStructure *name_type_class, u2 name_type_index) {
	int i;
	u1 *m_name, *m_desc;
	u2 m_name_len, m_desc_len;
	char *name, *desc;
	u2 name_len, desc_len;

	name = getName(name_type_class, name_type_class->constantPool[name_type_index-1].type.NameType.nameIndex);
	name_len = strlen(name);

	desc = getName(name_type_class, name_type_class->constantPool[name_type_index-1].type.NameType.descriptorIndex);
	desc_len = strlen(desc);

	for(i = 0; i < main_class->methodCount; i++) {

		m_name = main_class->constantPool[(main_class->methods[i].nameIndex-1)].type.Utf8.bytes;
		m_name_len = main_class->constantPool[(main_class->methods[i].nameIndex-1)].type.Utf8.length;

		m_desc = main_class->constantPool[(main_class->methods[i].descriptorIndex-1)].type.Utf8.bytes;
		m_desc_len = main_class->constantPool[(main_class->methods[i].descriptorIndex-1)].type.Utf8.length;

		if(name_len != m_name_len)
			continue;
		if(desc_len != m_desc_len)
			continue;

		if((strncmp((char *)name,(char *)m_name , m_name_len) == 0)
				&&(strncmp((char *)desc,(char *)m_desc , m_desc_len) == 0))
			return(main_class->methods + i);
	}

	return NULL;
}

void runMethod() {
	/* loop principal do método - executa o código */
	while(frameAtual != NULL &&(frameAtual->pc) < frameAtual->codeLength) {
		executarInstrucoes(frameAtual->code[frameAtual->pc]);
	}

	/* Finaliza o método chamado */
	finishMethod();

	/* Empilha o valor de retorno */
	if(returnType == RETURN_32bits) {
		push((u4)returnValue );
	} else if(returnType == RETURN_64bits) {
		pushU8( returnValue );
	}

	/* Reseta as variaveis de retorno */
	returnType = RETURN_none;
	returnValue = 0;
}


void prepararMetodo(classStructure *class, methodInfo *method) {
	int i;

	/* procura por atributo Code */
	for(i = 0; i < method->attributeCount; i++) {
		if(method->attributes[i].tag == ATTR_Code)
			break;
	}

	if(method->attributeCount != 0) {
		if(method->attributes[i].tag != ATTR_Code) {
			printf(" Erro: Nao encontrou atributo code no método.");
			exit(1);
		}
		newFrame(class, class->constantPool, &(method->attributes[i]));
	}
	else {
		(method->attributeCount)++;
		method->attributes = malloc(1 * sizeof(attributeInfo));
		method->attributes[0].type.Code.codeLength = 0;
		newFrame(class, class->constantPool, &(method->attributes[0]));
	}

}

void finishMethod() {
	freeFrame();
}

int32_t getNumParameters(classStructure *class, methodInfo *method) {
	int32_t prm=0;
	int32_t i;
	u2 length;
	u1 *bytes;

	bytes = class->constantPool[(method->descriptorIndex-1)].type.Utf8.bytes;
	length = class->constantPool[(method->descriptorIndex-1)].type.Utf8.length;

	for(i = 0; i < length && bytes[i] != ')'; i++) {

		if(bytes[i] == 'L') {

			while(bytes[i] != ';')
				i++;
			prm++;

		} else if((bytes[i] == 'B')||(bytes[i] == 'C')||(bytes[i] == 'F')||
				(bytes[i] == 'I')||(bytes[i] == 'S')||(bytes[i] == 'Z') ) {
			prm++;
		} else if((bytes[i] == 'D')||(bytes[i] == 'J')) {
			prm+=2;
		}

	}

	return prm;
}

methodInfo * getInitMethod(u1 *desc, u2 desc_len) {
	return NULL;
}
