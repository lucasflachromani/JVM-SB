/*!
 \file classloader.c
 \brief Class Loader da JVM. Carrega os objetos do arquivo .class em memoria.
 Os campos sao mostrados em tela. O nome do arquivo pode ser passado por parametro
 da segiunte forma:
 ./classloader arquivo.class
 ou executando  o programa e informando o nome do arquivo:
 ./classloader
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <errno.h>

#include "carregador.h"
#include "classloader.h"
#include "mnemonics.h"

extern int errno;

FILE* classfile;

classStructure * read_class_file (char *nome_arq) {
	if (open_file(nome_arq) < 0) {
		return NULL;
	}

	/*!
	 * Inicio da leitura
	 */
	class = calloc(sizeof(classStructure), 1);

	if (class == NULL) {
		perror("Allocate class");
		return NULL;
	}

	class->magicNumber = u4Read();
	class->minorVersion = u2Read();
	class->majorVersion = u2Read();

	class->constantPoolCount = u2Read();

	/* Aloca memoria para o array de Constant Pool */
	class->constantPool = calloc(sizeof(void *), class->constantPoolCount);
	read_constant_pool();

	class->accessFlags = u2Read();
	class->thisClass = u2Read();
	class->superClass = u2Read();
	class->interfaceCount = u2Read();
	read_interfaces();
	class->fieldCount = u2Read();
	read_fields();
	class->methodCount = u2Read();
	read_methods();
	class->attributeCount = u2Read();
	read_attributes();

	close_file();

	if (errno != 0) {
		return NULL;
	}

	return class;
}

/*
 \brief Abre um arquivo binario para leitura
 \param file_name Nome do arquivo
 \return 0 Nao houve erro na funcao
 \return -1 Ocorreu erro
 */
int open_file(char *file_name) {
	classfile = fopen(file_name, "rb");
	if ((classfile) == NULL) {
		perror("openfile");
		return -1;
	}
	return 0;
}

void close_file() {
	fclose(classfile);
}

/* @ brief Funcao que le um byte do arquivo e retorna o valor lido
 * @ param file : arquivo de entrada
 */
u1 u1Read () {
	u1 info;
    
    if(fread (&info, sizeof(u1), 1, classfile)<0) {
		perror ("u1Read");
		return -1;
	}
    
    return info;
}

/* @ brief Funcao que le dois bytes do arquivo e retorna o valor lido
 * @ param file : arquivo de entrada
 */
u2 u2Read () {
	u1 b1, b2;
    u2 info;
    
	if ((fread (&b1, sizeof(u1), 1, classfile))<0 || (fread (&b2, sizeof(u1), 1, classfile))<0) {
		perror ("u2Read");
		return -1;
	}

    info = b1 << 8;
    info = info | b2;
    
    return info;
}

/* @ brief Funcao que le quatro bytes do arquivo e retorna o valor lido
 * @ param file : arquivo de entrada
 */
u4 u4Read () {
	u1 b1, b2, b3, b4;
    u4 info = 0;
    
    if ((fread (&b1, sizeof(u1), 1, classfile))<0 || (fread (&b2, sizeof(u1), 1, classfile))<0 || (fread (&b3, sizeof(u1), 1, classfile))<0 || (fread (&b4, sizeof(u1), 1, classfile))<0) {
		perror ("u4Read");
		return -1;
	}
	
    info = b1 << 24;
    info = info | b2 << 16;
    info = info | b3 << 8;
    info = info | b4;
    
    return info;
}

/*
 \brief Le a constant pool
 */
void read_constant_pool() {
	int i, j;
	u1 cp_tag;

	for (i = 0; i < class->constantPoolCount - 1; i++) {
		cp_tag = u1Read();
		switch(cp_tag) {
		case CONSTANT_Class:
			class->constantPool[i] = (struct CONSTANT_Class_info*) calloc(sizeof (struct CONSTANT_Class_info), 1);
			((struct CONSTANT_Class_info*) class->constantPool[i])->tag = cp_tag;
			((struct CONSTANT_Class_info*) class->constantPool[i])->nameIndex = u2Read();
			break;
		case CONSTANT_Fieldref:
			class->constantPool[i] = (struct CONSTANT_Fieldref_info*) calloc(sizeof (struct CONSTANT_Fieldref_info), 1);
			((struct CONSTANT_Fieldref_info*) class->constantPool[i])->tag = cp_tag;
			((struct CONSTANT_Fieldref_info*) class->constantPool[i])->classIndex = u2Read();
			((struct CONSTANT_Fieldref_info*) class->constantPool[i])->nameTypeIndex = u2Read();
			break;
		case CONSTANT_Methodref:
			class->constantPool[i] = (struct CONSTANT_Methodref_info*) calloc(sizeof (struct CONSTANT_Methodref_info), 1);
			((struct CONSTANT_Methodref_info*) class->constantPool[i])->tag = cp_tag;
			((struct CONSTANT_Methodref_info*) class->constantPool[i])->classIndex = u2Read();
			((struct CONSTANT_Methodref_info*) class->constantPool[i])->nameTypeIndex = u2Read();
			break;
		case CONSTANT_InterfaceMethodref:
			class->constantPool[i] = (struct CONSTANT_InterfaceMethodref_info*) calloc(sizeof (struct CONSTANT_InterfaceMethodref_info), 1);
			((struct CONSTANT_InterfaceMethodref_info*) class->constantPool[i])->tag = cp_tag;
			((struct CONSTANT_InterfaceMethodref_info*) class->constantPool[i])->classIndex = u2Read();
			((struct CONSTANT_InterfaceMethodref_info*) class->constantPool[i])->nameTypeIndex = u2Read();
			break;
		case CONSTANT_String:
			class->constantPool[i] = (struct CONSTANT_String_info*) calloc(sizeof (struct CONSTANT_String_info), 1);
			((struct CONSTANT_String_info*) class->constantPool[i])->tag = cp_tag;
			((struct CONSTANT_String_info*) class->constantPool[i])->stringIndex = u2Read();
			break;
		case CONSTANT_Integer:
			class->constantPool[i] = (struct CONSTANT_Integer_info*) calloc(sizeof (struct CONSTANT_Integer_info), 1);
			((struct CONSTANT_Integer_info*) class->constantPool[i])->tag = cp_tag;
			((struct CONSTANT_Integer_info*) class->constantPool[i])->bytes = u4Read();
			break;
		case CONSTANT_Float:
			class->constantPool[i] = (struct CONSTANT_Float_info*) calloc(sizeof (struct CONSTANT_Float_info), 1);
			((struct CONSTANT_Float_info*) class->constantPool[i])->tag = cp_tag;
			((struct CONSTANT_Float_info*) class->constantPool[i])->bytes = u4Read();
			break;
		case CONSTANT_Long:
			class->constantPool[i] = (struct CONSTANT_Long_info*) calloc(sizeof (struct CONSTANT_Long_info), 1);
			((struct CONSTANT_Long_info*) class->constantPool[i])->tag = cp_tag;
			((struct CONSTANT_Long_info*) class->constantPool[i])->highBytes = u4Read();
			((struct CONSTANT_Long_info*) class->constantPool[i])->lowBytes = u4Read();
			i++;
			break;
		case CONSTANT_Double:
			class->constantPool[i] = (struct CONSTANT_Double_info*) calloc(sizeof (struct CONSTANT_Double_info), 1);
			((struct CONSTANT_Double_info*) class->constantPool[i])->tag = cp_tag;
			((struct CONSTANT_Double_info*) class->constantPool[i])->highBytes = u4Read();
			((struct CONSTANT_Double_info*) class->constantPool[i])->lowBytes = u4Read();
			i++;
			break;
		case CONSTANT_Utf8:
			class->constantPool[i] = (struct CONSTANT_Utf8_info*) calloc(1, sizeof (struct CONSTANT_Utf8_info));
			((struct CONSTANT_Utf8_info*) (class->constantPool[i]))->tag = cp_tag;
			((struct CONSTANT_Utf8_info*) (class->constantPool[i]))->length = u2Read();
			((struct CONSTANT_Utf8_info*) (class->constantPool[i]))->bytes = calloc( ((struct CONSTANT_Utf8_info*) class->constantPool[i])->length , sizeof (u1) );
			for (j = 0; j < ((struct CONSTANT_Utf8_info*) class->constantPool[i])->length; j++)
				((struct CONSTANT_Utf8_info*) class->constantPool[i])->bytes[j] = u1Read();
			break;
		case CONSTANT_NameAndType:
			class->constantPool[i] = (struct CONSTANT_NameAndType_info*) calloc(sizeof (struct CONSTANT_NameAndType_info), 1);
			((struct CONSTANT_NameAndType_info*) class->constantPool[i])->tag = cp_tag;
			((struct CONSTANT_NameAndType_info*) class->constantPool[i])->nameIndex = u2Read();
			((struct CONSTANT_NameAndType_info*) class->constantPool[i])->descriptorIndex = u2Read();
			break;
		default:
			break;
		}
	}
}

/*
 \brief Le as interfaces para memoria
 \return 0 Nao houve erro na funcao
 \return -1 Ocorreu erro
 */
int read_interfaces() {
	int i;

	if ((class->interfaces = (u2*)calloc(sizeof (u2), class->interfaceCount)) == NULL) {
		perror("Interface");
		return -1;
	}

	for (i = 0; i < class->interfaceCount; i++) {
		class->interfaces[i] = u2Read();
	}
	return 0;
}


/*
 \brief Le os fields para memoria
 \return 0 Nao houve erro na funcao
 \return -1 Ocorreu erro
 */
int read_fields() {
	int i, j;

	if ((class->fields = calloc(sizeof (fieldInfo), class->fieldCount)) == NULL) {
		perror("Fields");
		return -1;
	}

	for (i = 0; i < class->fieldCount; i++) {
		class->fields[i].accessFlags = u2Read();
		class->fields[i].nameIndex = u2Read();
		class->fields[i].descriptorIndex = u2Read();
		class->fields[i].attributeCount = u2Read();

		if ((class->fields[i].attributes = calloc(sizeof (void *), class->fields[i].attributeCount)) == NULL) {
			perror("Attributes");
			return -1;
		}

		for (j = 0; j < class->fields[i].attributeCount; j++){
			class->fields[i].attributes[j] = read_attribute_info();
		}

	}

	return 0;
}


/*
 \brief Escreve em dest o nome enderecado pelo index
 \param dest String de destino
 \param nameIndex indice no constant pool
 */
char * getName(classStructure *class_file, u2 nameIndex) {
	int i;

	char *dest = malloc(((struct CONSTANT_Utf8_info*) class_file->constantPool[nameIndex - 1])->length + 1);
	for (i = 0; i < ((struct CONSTANT_Utf8_info*) class_file->constantPool[nameIndex - 1])->length; i++) {
		dest[i] = (char) ((struct CONSTANT_Utf8_info*) class_file->constantPool[nameIndex - 1])->bytes[i];
	}
	dest[i] = '\0';

	return dest;
}


/*
 \brief Le um atribute_info e retorna o ponteiro para tal
 \return Ponteiro para um atributo
 */
void * read_attribute_info() {
	int i;
	char *nome;

	void *attribute;

	u2 nameIndex;
	u4 length;

	nameIndex = u2Read();
	length = u4Read();

	nome = getName(class, nameIndex);

	if (strcmp("ConstantValue", nome) == 0) {
		attribute = (ConstantValue_attribute *) calloc(sizeof (ConstantValue_attribute), 1);
		((ConstantValue_attribute *) attribute)->attributeNameIndex = nameIndex;
		((ConstantValue_attribute *) attribute)->attributeLength = length;
		((ConstantValue_attribute *) attribute)->tag = ATTR_ConstantValue;
		((ConstantValue_attribute *) attribute)->constantValueIndex = u2Read();
	}

	else if (strcmp("Code", nome) == 0) {
		attribute = (Code_attribute *) calloc(sizeof (Code_attribute), 1);
		((Code_attribute *) attribute)->attributeNameIndex = nameIndex;
		((Code_attribute *) attribute)->attributeLength = length;
		((Code_attribute *) attribute)->tag = ATTR_Code;
		((Code_attribute *) attribute)->maxStack = u2Read();
		((Code_attribute *) attribute)->maxLocals = u2Read();

		((Code_attribute *) attribute)->codeLength = u4Read();
		((Code_attribute *) attribute)->code = (u1 *) calloc(sizeof (u1), ((Code_attribute *) attribute)->codeLength);
		for (i = 0; i < ((Code_attribute *) attribute)->codeLength; i++) {
			((Code_attribute *) attribute)->code[i] = u1Read();
		}

		((Code_attribute *) attribute)->exceptionTableLength = u2Read();
		((Code_attribute *) attribute)->exceptionTable = (exceptionTableType *) calloc(sizeof (exceptionTableType),
				((Code_attribute *) attribute)->exceptionTableLength);
		for (i = 0; i < ((Code_attribute *) attribute)->exceptionTableLength; i++) {
			((Code_attribute *) attribute)->exceptionTable[i].startPc = u2Read();
			((Code_attribute *) attribute)->exceptionTable[i].endPc = u2Read();
			((Code_attribute *) attribute)->exceptionTable[i].handlerPc = u2Read();
			((Code_attribute *) attribute)->exceptionTable[i].catchType = u2Read();
		}

		((Code_attribute *) attribute)->attributeCount = u2Read();
		((Code_attribute *) attribute)->attributes = (void *) calloc(sizeof (void *),
				((Code_attribute *) attribute)->attributeCount);
		for (i = 0; i < ((Code_attribute *) attribute)->attributeCount; i++) {
			((Code_attribute *) attribute)->attributes[i] = read_attribute_info();
		}
	}

	else if (strcmp("Deprecated", nome) == 0) {
		attribute = (Deprecated_attribute *) calloc(sizeof (Deprecated_attribute), 1);
		((Deprecated_attribute *) attribute)->attributeNameIndex = nameIndex;
		((Deprecated_attribute *) attribute)->attributeLength = length;
		((Deprecated_attribute *) attribute)->tag = ATTR_Deprecated;
	}

	else if (strcmp("Exceptions", nome) == 0) {
		attribute = (Exceptions_attribute *) calloc(sizeof (Exceptions_attribute), 1);
		((Exceptions_attribute *) attribute)->attributeNameIndex = nameIndex;
		((Exceptions_attribute *) attribute)->attributeLength = length;
		((Exceptions_attribute *) attribute)->tag = ATTR_Exceptions;

		((Exceptions_attribute *) attribute)->numberOfExceptions = u2Read();
		((Exceptions_attribute *) attribute)->exceptionIndexTable = (u2 *) calloc(sizeof (u2),
				((Exceptions_attribute *) attribute)->numberOfExceptions);
		for (i = 0; i < ((Exceptions_attribute *) attribute)->numberOfExceptions; i++) {
			((Exceptions_attribute *) attribute)->exceptionIndexTable[i] = u2Read();
		}
	}

	else if (strcmp("InnerClasses", nome) == 0) {
		attribute = (InnerClasses_attribute *) calloc(sizeof (InnerClasses_attribute), 1);
		((InnerClasses_attribute *) attribute)->attributeNameIndex = nameIndex;
		((InnerClasses_attribute *) attribute)->attributeLength = length;
		((InnerClasses_attribute *) attribute)->tag = ATTR_InnerClasses;

		((InnerClasses_attribute *) attribute)->numberOfClasses = u2Read();
		((InnerClasses_attribute *) attribute)->classes = (classType *) calloc(sizeof (classType),
				((InnerClasses_attribute *) attribute)->numberOfClasses);
		for (i = 0; i < ((InnerClasses_attribute *) attribute)->numberOfClasses; i++) {
			((InnerClasses_attribute *) attribute)->classes[i].innerClassInfoIndex = u2Read();
			((InnerClasses_attribute *) attribute)->classes[i].outerClassInfoIndex = u2Read();
			((InnerClasses_attribute *) attribute)->classes[i].innerNameIndex = u2Read();
			((InnerClasses_attribute *) attribute)->classes[i].innerClassAccessFlags = u2Read();
		}
	}

	else if (strcmp("LineNumberTable", nome) == 0) {
		attribute = (LineNumberTable_attribute *) calloc(sizeof (LineNumberTable_attribute), 1);
		((LineNumberTable_attribute *) attribute)->attributeNameIndex = nameIndex;
		((LineNumberTable_attribute *) attribute)->attributeLength = length;
		((LineNumberTable_attribute *) attribute)->tag = ATTR_LineNumberTable;

		((LineNumberTable_attribute *) attribute)->lineNumberTableLength = u2Read();
		((LineNumberTable_attribute *) attribute)->lineNumberTable = (lineNumberTableType *) calloc(sizeof (lineNumberTableType),
				((LineNumberTable_attribute *) attribute)->lineNumberTableLength);
		for (i = 0; i < ((LineNumberTable_attribute *) attribute)->lineNumberTableLength; i++) {
			((LineNumberTable_attribute *) attribute)->lineNumberTable[i].startPc = u2Read();
			((LineNumberTable_attribute *) attribute)->lineNumberTable[i].lineNumber = u2Read();
		}
	}

	else if (strcmp("LocalVariableTable", nome) == 0) {
		attribute = (LocalVariableTable_attribute *) calloc(sizeof (LocalVariableTable_attribute), 1);
		((LocalVariableTable_attribute *) attribute)->attributeNameIndex = nameIndex;
		((LocalVariableTable_attribute *) attribute)->attributeLength = length;
		((LocalVariableTable_attribute *) attribute)->tag = ATTR_LocalVariableTable;

		((LocalVariableTable_attribute *) attribute)->localVariableTableLength = u2Read();
		((LocalVariableTable_attribute *) attribute)->localVariableTable = (localVariableTableType *) calloc(sizeof (localVariableTableType),
				((LocalVariableTable_attribute *) attribute)->localVariableTableLength);
		for (i = 0; i < ((LocalVariableTable_attribute *) attribute)->localVariableTableLength; i++) {
			((LocalVariableTable_attribute *) attribute)->localVariableTable[i].startPc = u2Read();
			((LocalVariableTable_attribute *) attribute)->localVariableTable[i].length = u2Read();
			((LocalVariableTable_attribute *) attribute)->localVariableTable[i].nameIndex = u2Read();
			((LocalVariableTable_attribute *) attribute)->localVariableTable[i].descriptorIndex = u2Read();
			((LocalVariableTable_attribute *) attribute)->localVariableTable[i].index = u2Read();
		}
	}

	else if (strcmp("SourceFile", nome) == 0) {
		attribute = (SourceFile_attribute *) calloc(sizeof (SourceFile_attribute), 1);
		((SourceFile_attribute *) attribute)->attributeNameIndex = nameIndex;
		((SourceFile_attribute *) attribute)->attributeLength = length;
		((SourceFile_attribute *) attribute)->tag = ATTR_SourceFile;
		((SourceFile_attribute *) attribute)->sourceFileIndex = u2Read();
	}

	else if (strcmp("Synthetic", nome) == 0) {
		attribute = (Synthetic_attribute *) calloc(sizeof (Synthetic_attribute), 1);
		((Synthetic_attribute *) attribute)->attributeNameIndex = nameIndex;
		((Synthetic_attribute *) attribute)->attributeLength = length;
	}

	else {
		printf(" Erro: Attributo nao reconhecido.");
	}

	return attribute;
}

/*
 \brief Le metodos para memoria
 \return 0 Nao houve erro na funcao
 \return -1 Ocorreu erro
 */
int read_methods() {

	int i, j;

	if ((class->methods = (methodInfo*) calloc(sizeof (methodInfo), class->methodCount)) == NULL) {
		perror("Methods");
		return -1;
	}

	for (i = 0; i < class->methodCount; i++) {
		class->methods[i].accessFlags = u2Read();
		class->methods[i].nameIndex = u2Read();
		class->methods[i].descriptorIndex = u2Read();
		class->methods[i].attributeCount = u2Read();

		if ((class->methods[i].attributes = calloc(sizeof (void *), class->methods[i].attributeCount)) == NULL) {
			perror("Methods");
			return -1;
		}

		for (j = 0; j < class->methods[i].attributeCount; j++) {
			class->methods[i].attributes[j] = read_attribute_info();
		}
	}

	return 0;
}

/*
 \brief Le atributos da class file
 \return 0 Nao houve erro na funcao
 \return -1 Ocorreu erro
 */

int read_attributes() {
	int i;

	if ((class->attributes = calloc(sizeof (void *), class->attributeCount)) == NULL) {
		perror("Attributes");
		return -1;
	}

	for (i = 0; i < class->attributeCount; i++) {
		class->attributes[i] = read_attribute_info();
	}

	return 0;
}

/*
 \brief Libera uma estrutura de classe e suas estruturas internas.
 \param class_file Ponteiro para a estrutura que sera' liberada
 */
void free_class_file(classStructure* class_file)
{

}
