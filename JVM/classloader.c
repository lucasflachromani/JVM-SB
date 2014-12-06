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

#include "classloader.h"

#include "const.h"
#include "inicializador.h"
#include "tipos.h"

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
	class->constantPool = calloc(sizeof(cpInfo), class->constantPoolCount);
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
		case CClass:

			( class->constantPool[i]).tag = cp_tag;
			( class->constantPool[i]).type.Class.nameIndex = u2Read();
			break;
		case CFieldRef:
			( class->constantPool[i]).tag = cp_tag;
			( class->constantPool[i]).type.FieldRef.classIndex = u2Read();
			( class->constantPool[i]).type.FieldRef.nameTypeIndex = u2Read();
			break;
		case CMethodRef:
			( class->constantPool[i]).tag = cp_tag;
			( class->constantPool[i]).type.MethodRef.classIndex = u2Read();
			( class->constantPool[i]).type.MethodRef.nameTypeIndex = u2Read();

			break;
		case CInterfaceMethodRef:
			(class->constantPool[i]).tag = cp_tag;
			( class->constantPool[i]).type.InterfaceMethodRef.classIndex = u2Read();
			( class->constantPool[i]).type.InterfaceMethodRef.nameTypeIndex = u2Read();
			break;
		case CString:
			( class->constantPool[i]).tag = cp_tag;
			(class->constantPool[i]).type.String.stringIndex = u2Read();
			break;
		case CInteger:
			( class->constantPool[i]).tag = cp_tag;
			( class->constantPool[i]).type.Integer.bytes = u4Read();
			break;
		case CFloat:
			( class->constantPool[i]).tag = cp_tag;
			( class->constantPool[i]).type.Float.bytes = u4Read();
			break;
		case CLong:
			( class->constantPool[i]).tag = cp_tag;
			( class->constantPool[i]).type.Long.highBytes = u4Read();
			( class->constantPool[i]).type.Long.lowBytes = u4Read();
			i++;
			break;
		case CDouble:
			( class->constantPool[i]).tag = cp_tag;
			( class->constantPool[i]).type.Double.highBytes = u4Read();
			( class->constantPool[i]).type.Double.lowBytes = u4Read();
			i++;
			break;
		case CUtf8:
			(class->constantPool[i]).tag = cp_tag;
			(class->constantPool[i]).type.Utf8.length = u2Read();
			(class->constantPool[i]).type.Utf8.bytes = calloc( class->constantPool[i].type.Utf8.length , sizeof (u1) );
			for (j = 0; j < ( class->constantPool[i]).type.Utf8.length; j++)
				(class->constantPool[i]).type.Utf8.bytes[j] = u1Read();
			break;
		case CNameType:
			( class->constantPool[i]).tag = cp_tag;
			(class->constantPool[i]).type.NameType.nameIndex = u2Read();
			(class->constantPool[i]).type.NameType.descriptorIndex = u2Read();
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

	char *dest = malloc((class_file->constantPool[nameIndex - 1]).type.Utf8.length + 1);
	for (i = 0; i < ( class_file->constantPool[nameIndex - 1]).type.Utf8.length; i++) {
		dest[i] = (char) (class_file->constantPool[nameIndex - 1]).type.Utf8.bytes[i];
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
		((LocalVariableTable_attribute *) attribute)->localVariableTable = (LocalVariableTableType *) calloc(sizeof (LocalVariableTableType),
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

void carregarOpcodeInformacao() {
	int i;

	op_info = malloc(sizeof(opcode_informacao)*256);

	//TODO: colocar da tabela
	strcpy(op_info[0x00].descricao, "nop");
	strcpy(op_info[0x01].descricao, "aconst_null");
	strcpy(op_info[0x02].descricao, "iconst_m1");
	strcpy(op_info[0x03].descricao, "iconst_0");
	strcpy(op_info[0x04].descricao, "iconst_1");
	strcpy(op_info[0x05].descricao, "iconst_2");
	strcpy(op_info[0x06].descricao, "iconst_3");
	strcpy(op_info[0x07].descricao, "iconst_4");
	strcpy(op_info[0x08].descricao, "iconst_5");
	strcpy(op_info[0x09].descricao, "lconst_0");
	strcpy(op_info[0x0a].descricao, "lconst_1");
	strcpy(op_info[0x0b].descricao, "fconst_0");
	strcpy(op_info[0x0c].descricao, "fconst_1");
	strcpy(op_info[0x0d].descricao, "fconst_2");
	strcpy(op_info[0x0e].descricao, "dconst_0");
	strcpy(op_info[0x0f].descricao, "dconst_1");
	strcpy(op_info[0x10].descricao, "bipush");
	strcpy(op_info[0x11].descricao, "sipush");
	strcpy(op_info[0x12].descricao, "ldc");
	strcpy(op_info[0x13].descricao, "ldc_w");
	strcpy(op_info[0x14].descricao, "ldc2_w");
	strcpy(op_info[0x15].descricao, "iload");
	strcpy(op_info[0x16].descricao, "lload");
	strcpy(op_info[0x17].descricao, "fload");
	strcpy(op_info[0x18].descricao, "dload");
	strcpy(op_info[0x19].descricao, "aload");
	strcpy(op_info[0x1a].descricao, "iload_0");
	strcpy(op_info[0x1b].descricao, "iload_1");
	strcpy(op_info[0x1c].descricao, "iload_2");
	strcpy(op_info[0x1d].descricao, "iload_3");
	strcpy(op_info[0x1e].descricao, "lload_0");
	strcpy(op_info[0x1f].descricao, "lload_1");
	strcpy(op_info[0x20].descricao, "lload_2");
	strcpy(op_info[0x21].descricao, "lload_3");
	strcpy(op_info[0x22].descricao, "fload_0");
	strcpy(op_info[0x23].descricao, "fload_1");
	strcpy(op_info[0x24].descricao, "fload_2");
	strcpy(op_info[0x25].descricao, "fload_3");
	strcpy(op_info[0x26].descricao, "dload_0");
	strcpy(op_info[0x27].descricao, "dload_1");
	strcpy(op_info[0x28].descricao, "dload_2");
	strcpy(op_info[0x29].descricao, "dload_3");
	strcpy(op_info[0x2a].descricao, "aload_0");
	strcpy(op_info[0x2b].descricao, "aload_1");
	strcpy(op_info[0x2c].descricao, "aload_2");
	strcpy(op_info[0x2d].descricao, "aload_3");
	strcpy(op_info[0x2e].descricao, "iaload");
	strcpy(op_info[0x2f].descricao, "laload");
	strcpy(op_info[0x31].descricao, "daload");
	strcpy(op_info[0x32].descricao, "aaload");
	strcpy(op_info[0x33].descricao, "baload");
	strcpy(op_info[0x34].descricao, "caload");
	strcpy(op_info[0x35].descricao, "saload");
	strcpy(op_info[0x36].descricao, "istore");
	strcpy(op_info[0x37].descricao, "lstore");
	strcpy(op_info[0x38].descricao, "fstore");
	strcpy(op_info[0x39].descricao, "dstore");
	strcpy(op_info[0x3a].descricao, "astore");
	strcpy(op_info[0x3b].descricao, "istore_0");
	strcpy(op_info[0x3c].descricao, "istore_1");
	strcpy(op_info[0x3d].descricao, "istore_2");
	strcpy(op_info[0x3e].descricao, "istore_3");
	strcpy(op_info[0x3f].descricao, "lstore_0");
	strcpy(op_info[0x40].descricao, "lstore_1");
	strcpy(op_info[0x41].descricao, "lstore_2");
	strcpy(op_info[0x42].descricao, "lstore_3");
	strcpy(op_info[0x43].descricao, "fstore_0");
	strcpy(op_info[0x44].descricao, "fstore_1");
	strcpy(op_info[0x45].descricao, "fstore_2");
	strcpy(op_info[0x46].descricao, "fstore_3");
	strcpy(op_info[0x47].descricao, "dstore_0");
	strcpy(op_info[0x48].descricao, "dstore_1");
	strcpy(op_info[0x49].descricao, "dstore_2");
	strcpy(op_info[0x4a].descricao, "dstore_3");
	strcpy(op_info[0x4b].descricao, "astore_0");
	strcpy(op_info[0x4c].descricao, "astore_1");
	strcpy(op_info[0x4d].descricao, "astore_2");
	strcpy(op_info[0x4e].descricao, "astore_3");
	strcpy(op_info[0x4f].descricao, "iastore");
	strcpy(op_info[0x50].descricao, "lastore");
	strcpy(op_info[0x51].descricao, "fastore");
	strcpy(op_info[0x52].descricao, "dastore");
	strcpy(op_info[0x53].descricao, "aastore");
	strcpy(op_info[0x54].descricao, "bastore");
	strcpy(op_info[0x55].descricao, "castore");
	strcpy(op_info[0x56].descricao, "sastore");
	strcpy(op_info[0x57].descricao, "pop");
	strcpy(op_info[0x58].descricao, "pop2");
	strcpy(op_info[0x59].descricao, "dup");
	strcpy(op_info[0x5a].descricao, "dup_x1");
	strcpy(op_info[0x5b].descricao, "dup_x2");
	strcpy(op_info[0x5c].descricao, "dup2");
	strcpy(op_info[0x5d].descricao, "dup2_x1");
	strcpy(op_info[0x5e].descricao, "dup2_x2");
	strcpy(op_info[0x60].descricao, "iadd");
	strcpy(op_info[0x61].descricao, "ladd");
	strcpy(op_info[0x62].descricao, "fadd");
	strcpy(op_info[0x63].descricao, "dadd");
	strcpy(op_info[0x64].descricao, "isub");
	strcpy(op_info[0x65].descricao, "lsub");
	strcpy(op_info[0x66].descricao, "fsub");
	strcpy(op_info[0x67].descricao, "dsub");
	strcpy(op_info[0x68].descricao, "imul");
	strcpy(op_info[0x69].descricao, "lmul");
	strcpy(op_info[0x6a].descricao, "fmul");
	strcpy(op_info[0x6b].descricao, "dmul");
	strcpy(op_info[0x6c].descricao, "idiv");
	strcpy(op_info[0x6d].descricao, "ldiv");
	strcpy(op_info[0x6e].descricao, "fdiv");
	strcpy(op_info[0x6f].descricao, "ddiv");
	strcpy(op_info[0x70].descricao, "irem");
	strcpy(op_info[0x71].descricao, "lrem");
	strcpy(op_info[0x72].descricao, "frem");
	strcpy(op_info[0x73].descricao, "drem");
	strcpy(op_info[0x74].descricao, "ineg");
	strcpy(op_info[0x75].descricao, "lneg");
	strcpy(op_info[0x76].descricao, "fneg");
	strcpy(op_info[0x77].descricao, "dneg");
	strcpy(op_info[0x78].descricao, "ishl");
	strcpy(op_info[0x79].descricao, "lshl");
	strcpy(op_info[0x7a].descricao, "ishr");
	strcpy(op_info[0x7b].descricao, "lshr");
	strcpy(op_info[0x7c].descricao, "iushr");
	strcpy(op_info[0x7d].descricao, "lushr");
	strcpy(op_info[0x7e].descricao, "iand");
	strcpy(op_info[0x7f].descricao, "land");
	strcpy(op_info[0x80].descricao, "ior");
	strcpy(op_info[0x81].descricao, "lor");
	strcpy(op_info[0x82].descricao, "ixor");
	strcpy(op_info[0x83].descricao, "lxor");
	strcpy(op_info[0x84].descricao, "iinc");
	strcpy(op_info[0x85].descricao, "i2l");
	strcpy(op_info[0x86].descricao, "i2f");
	strcpy(op_info[0x87].descricao, "i2d");
	strcpy(op_info[0x88].descricao, "l2i");
	strcpy(op_info[0x89].descricao, "l2f");
	strcpy(op_info[0x8a].descricao, "l2d");
	strcpy(op_info[0x8b].descricao, "f2i");
	strcpy(op_info[0x8c].descricao, "f2l");
	strcpy(op_info[0x8d].descricao, "f2d");
	strcpy(op_info[0x8e].descricao, "d2i");
	strcpy(op_info[0x8f].descricao, "d2l");
	strcpy(op_info[0x90].descricao, "d2f");
	strcpy(op_info[0x91].descricao, "i2b");
	strcpy(op_info[0x92].descricao, "i2c");
	strcpy(op_info[0x93].descricao, "i2s");
	strcpy(op_info[0x94].descricao, "lcmp");
	strcpy(op_info[0x95].descricao, "fcmpl");
	strcpy(op_info[0x96].descricao, "fcmpg");
	strcpy(op_info[0x97].descricao, "dcmpl");
	strcpy(op_info[0x98].descricao, "dcmpg");
	strcpy(op_info[0x99].descricao, "ifeq");
	strcpy(op_info[0x9a].descricao, "ifne");
	strcpy(op_info[0x9b].descricao, "iflt");
	strcpy(op_info[0x9c].descricao, "ifge");
	strcpy(op_info[0x9d].descricao, "ifgt");
	strcpy(op_info[0x9e].descricao, "ifle");
	strcpy(op_info[0x9f].descricao, "if_icmpeq");
	strcpy(op_info[0xa0].descricao, "if_icmpne");
	strcpy(op_info[0xa1].descricao, "if_icmplt");
	strcpy(op_info[0xa2].descricao, "if_icmpge");
	strcpy(op_info[0xa3].descricao, "if_icmpgt");
	strcpy(op_info[0xa4].descricao, "if_icmple");
	strcpy(op_info[0xa5].descricao, "if_acmpeq");
	strcpy(op_info[0xa6].descricao, "if_acmpne");
	strcpy(op_info[0xa7].descricao, "goto");
	strcpy(op_info[0xa8].descricao, "jsr");
	strcpy(op_info[0xa9].descricao, "ret");
	strcpy(op_info[0xaa].descricao, "tableswitch");
	strcpy(op_info[0xab].descricao, "lookupswitch");
	strcpy(op_info[0xac].descricao, "ireturn");
	strcpy(op_info[0xad].descricao, "lreturn");
	strcpy(op_info[0xae].descricao, "freturn");
	strcpy(op_info[0xaf].descricao, "dreturn");
	strcpy(op_info[0xb0].descricao, "areturn");
	strcpy(op_info[0xb1].descricao, "return");
	strcpy(op_info[0xb2].descricao, "getstatic");
	strcpy(op_info[0xb3].descricao, "putstatic");
	strcpy(op_info[0xb4].descricao, "getfield");
	strcpy(op_info[0xb5].descricao, "putfield");
	strcpy(op_info[0xb6].descricao, "invokevirtual");
	strcpy(op_info[0xb7].descricao, "invokespecial");
	strcpy(op_info[0xb8].descricao, "invokestatic");
	strcpy(op_info[0xb9].descricao, "invokeinterface");
	strcpy(op_info[0xbb].descricao, "new");
	strcpy(op_info[0xbc].descricao, "newarray");
	strcpy(op_info[0xbd].descricao, "anewarray");
	strcpy(op_info[0xbe].descricao, "arraylength");
	strcpy(op_info[0xc4].descricao, "wide");
	strcpy(op_info[0xc5].descricao, "multianewarray");
	strcpy(op_info[0xc6].descricao, "ifnull");
	strcpy(op_info[0xc7].descricao, "ifnonnull");
	strcpy(op_info[0xc8].descricao, "goto_w");
	strcpy(op_info[0xc9].descricao, "jsr_w");

	for(i = 0x00; i<= 0xc9; i++){
		op_info[i].operandos_count = 0;
	}

	op_info[0x10].operandos_count = 1;
	op_info[0x11].operandos_count = 2;
	op_info[0x12].operandos_count = 1;
	op_info[0x13].operandos_count = 2;
	op_info[0x14].operandos_count = 2;
	op_info[0x15].operandos_count = 1;
	op_info[0x16].operandos_count = 1;
	op_info[0x17].operandos_count = 1;
	op_info[0x18].operandos_count = 1;
	op_info[0x19].operandos_count = 1;
	op_info[0x36].operandos_count = 1;
	op_info[0x37].operandos_count = 1;
	op_info[0x38].operandos_count = 1;
	op_info[0x39].operandos_count = 1;
	op_info[0x3a].operandos_count = 1;
	op_info[0x84].operandos_count = 2;
	op_info[0x99].operandos_count = 2;
	op_info[0x9a].operandos_count = 2;
	op_info[0x9b].operandos_count = 2;
	op_info[0x9c].operandos_count = 2;
	op_info[0x9d].operandos_count = 2;
	op_info[0x9e].operandos_count = 2;
	op_info[0x9f].operandos_count = 2;
	op_info[0xa7].operandos_count = 2;
	op_info[0xa0].operandos_count = 2;
	op_info[0xa1].operandos_count = 2;
	op_info[0xa2].operandos_count = 2;
	op_info[0xa3].operandos_count = 2;
	op_info[0xa4].operandos_count = 2;
	op_info[0xa5].operandos_count = 2;
	op_info[0xa6].operandos_count = 2;
	op_info[0xa8].operandos_count = 2;
	op_info[0xa9].operandos_count = 1;
	op_info[0xaa].operandos_count = 14;
	op_info[0xab].operandos_count = 10;
	op_info[0xb2].operandos_count = 2;
	op_info[0xb4].operandos_count = 2;
	op_info[0xbd].operandos_count = 2;
	op_info[0xb9].operandos_count = 4;
	op_info[0xb7].operandos_count = 2;
	op_info[0xb8].operandos_count = 2;
	op_info[0xb6].operandos_count = 2;
	op_info[0xbc].operandos_count = 1;
	op_info[0xb5].operandos_count = 2;
	op_info[0xb3].operandos_count = 2;
	op_info[0xbb].operandos_count = 2;
	op_info[0xc8].operandos_count = 4;
	op_info[0xc7].operandos_count = 2;
	op_info[0xc6].operandos_count = 2;
	op_info[0xc9].operandos_count = 4;
	op_info[0xc5].operandos_count = 3;
	op_info[0xc4].operandos_count = 7;

}
