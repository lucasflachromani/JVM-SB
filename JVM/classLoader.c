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

struct ClassFile * read_class_file (char *nome_arq) {
	if (open_file(nome_arq) < 0) {
		return NULL;
	}

	/*!
	 * Inicio da leitura
	 */
	class = calloc(sizeof(struct ClassFile), 1);

	if (class == NULL) {
		perror("Allocate class");
		return NULL;
	}

	class->magic = u4Read();
	class->minor_version = u2Read();
	class->major_version = u2Read();

	class->constant_pool_count = u2Read();

	/* Aloca memoria para o array de Constant Pool */
	class->constant_pool = calloc(sizeof(void *), class->constant_pool_count);
	read_constant_pool();

	class->access_flags = u2Read();
	class->this_class = u2Read();
	class->super_class = u2Read();
	class->interfaces_count = u2Read();
	read_interfaces();
	class->fields_count = u2Read();
	read_fields();
	class->methods_count = u2Read();
	read_methods();
	class->attributes_count = u2Read();
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

	for (i = 0; i < class->constant_pool_count - 1; i++) {
		cp_tag = u1Read();
		switch(cp_tag) {
		case CONSTANT_Class:
			class->constant_pool[i] = (struct CONSTANT_Class_info*) calloc(sizeof (struct CONSTANT_Class_info), 1);
			((struct CONSTANT_Class_info*) class->constant_pool[i])->tag = cp_tag;
			((struct CONSTANT_Class_info*) class->constant_pool[i])->name_index = u2Read();
			break;
		case CONSTANT_Fieldref:
			class->constant_pool[i] = (struct CONSTANT_Fieldref_info*) calloc(sizeof (struct CONSTANT_Fieldref_info), 1);
			((struct CONSTANT_Fieldref_info*) class->constant_pool[i])->tag = cp_tag;
			((struct CONSTANT_Fieldref_info*) class->constant_pool[i])->class_index = u2Read();
			((struct CONSTANT_Fieldref_info*) class->constant_pool[i])->name_and_type_index = u2Read();
			break;
		case CONSTANT_Methodref:
			class->constant_pool[i] = (struct CONSTANT_Methodref_info*) calloc(sizeof (struct CONSTANT_Methodref_info), 1);
			((struct CONSTANT_Methodref_info*) class->constant_pool[i])->tag = cp_tag;
			((struct CONSTANT_Methodref_info*) class->constant_pool[i])->class_index = u2Read();
			((struct CONSTANT_Methodref_info*) class->constant_pool[i])->name_and_type_index = u2Read();
			break;
		case CONSTANT_InterfaceMethodref:
			class->constant_pool[i] = (struct CONSTANT_InterfaceMethodref_info*) calloc(sizeof (struct CONSTANT_InterfaceMethodref_info), 1);
			((struct CONSTANT_InterfaceMethodref_info*) class->constant_pool[i])->tag = cp_tag;
			((struct CONSTANT_InterfaceMethodref_info*) class->constant_pool[i])->class_index = u2Read();
			((struct CONSTANT_InterfaceMethodref_info*) class->constant_pool[i])->name_and_type_index = u2Read();
			break;
		case CONSTANT_String:
			class->constant_pool[i] = (struct CONSTANT_String_info*) calloc(sizeof (struct CONSTANT_String_info), 1);
			((struct CONSTANT_String_info*) class->constant_pool[i])->tag = cp_tag;
			((struct CONSTANT_String_info*) class->constant_pool[i])->string_index = u2Read();
			break;
		case CONSTANT_Integer:
			class->constant_pool[i] = (struct CONSTANT_Integer_info*) calloc(sizeof (struct CONSTANT_Integer_info), 1);
			((struct CONSTANT_Integer_info*) class->constant_pool[i])->tag = cp_tag;
			((struct CONSTANT_Integer_info*) class->constant_pool[i])->bytes = u4Read();
			break;
		case CONSTANT_Float:
			class->constant_pool[i] = (struct CONSTANT_Float_info*) calloc(sizeof (struct CONSTANT_Float_info), 1);
			((struct CONSTANT_Float_info*) class->constant_pool[i])->tag = cp_tag;
			((struct CONSTANT_Float_info*) class->constant_pool[i])->bytes = u4Read();
			break;
		case CONSTANT_Long:
			class->constant_pool[i] = (struct CONSTANT_Long_info*) calloc(sizeof (struct CONSTANT_Long_info), 1);
			((struct CONSTANT_Long_info*) class->constant_pool[i])->tag = cp_tag;
			((struct CONSTANT_Long_info*) class->constant_pool[i])->high_bytes = u4Read();
			((struct CONSTANT_Long_info*) class->constant_pool[i])->low_bytes = u4Read();
			i++;
			break;
		case CONSTANT_Double:
			class->constant_pool[i] = (struct CONSTANT_Double_info*) calloc(sizeof (struct CONSTANT_Double_info), 1);
			((struct CONSTANT_Double_info*) class->constant_pool[i])->tag = cp_tag;
			((struct CONSTANT_Double_info*) class->constant_pool[i])->high_bytes = u4Read();
			((struct CONSTANT_Double_info*) class->constant_pool[i])->low_bytes = u4Read();
			i++;
			break;
		case CONSTANT_Utf8:
			class->constant_pool[i] = (struct CONSTANT_Utf8_info*) calloc(1, sizeof (struct CONSTANT_Utf8_info));
			((struct CONSTANT_Utf8_info*) (class->constant_pool[i]))->tag = cp_tag;
			((struct CONSTANT_Utf8_info*) (class->constant_pool[i]))->length = u2Read();
			((struct CONSTANT_Utf8_info*) (class->constant_pool[i]))->bytes = calloc( ((struct CONSTANT_Utf8_info*) class->constant_pool[i])->length , sizeof (u1) );
			for (j = 0; j < ((struct CONSTANT_Utf8_info*) class->constant_pool[i])->length; j++)
				((struct CONSTANT_Utf8_info*) class->constant_pool[i])->bytes[j] = u1Read();
			break;
		case CONSTANT_NameAndType:
			class->constant_pool[i] = (struct CONSTANT_NameAndType_info*) calloc(sizeof (struct CONSTANT_NameAndType_info), 1);
			((struct CONSTANT_NameAndType_info*) class->constant_pool[i])->tag = cp_tag;
			((struct CONSTANT_NameAndType_info*) class->constant_pool[i])->name_index = u2Read();
			((struct CONSTANT_NameAndType_info*) class->constant_pool[i])->descriptor_index = u2Read();
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

	if ((class->interfaces = (u2*)calloc(sizeof (u2), class->interfaces_count)) == NULL) {
		perror("Interface");
		return -1;
	}

	for (i = 0; i < class->interfaces_count; i++) {
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

	if ((class->fields = calloc(sizeof (field_info), class->fields_count)) == NULL) {
		perror("Fields");
		return -1;
	}

	for (i = 0; i < class->fields_count; i++) {
		class->fields[i].access_flags = u2Read();
		class->fields[i].name_index = u2Read();
		class->fields[i].descriptor_index = u2Read();
		class->fields[i].attributes_count = u2Read();

		if ((class->fields[i].attributes = calloc(sizeof (void *), class->fields[i].attributes_count)) == NULL) {
			perror("Attributes");
			return -1;
		}

		for (j = 0; j < class->fields[i].attributes_count; j++){
			class->fields[i].attributes[j] = read_attribute_info();
		}

	}

	return 0;
}


/*
 \brief Escreve em dest o nome enderecado pelo index
 \param dest String de destino
 \param name_index indice no constant pool
 */
char * getName(struct ClassFile *class_file, u2 name_index) {
	int i;

	char *dest = malloc(((struct CONSTANT_Utf8_info*) class_file->constant_pool[name_index - 1])->length + 1);
	for (i = 0; i < ((struct CONSTANT_Utf8_info*) class_file->constant_pool[name_index - 1])->length; i++) {
		dest[i] = (char) ((struct CONSTANT_Utf8_info*) class_file->constant_pool[name_index - 1])->bytes[i];
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

	u2 name_index;
	u4 length;

	name_index = u2Read();
	length = u4Read();

	nome = getName(class, name_index);

	if (strcmp("ConstantValue", nome) == 0) {
		attribute = (ConstantValue_attribute *) calloc(sizeof (ConstantValue_attribute), 1);
		((ConstantValue_attribute *) attribute)->attribute_name_index = name_index;
		((ConstantValue_attribute *) attribute)->attribute_length = length;
		((ConstantValue_attribute *) attribute)->tag = ATTR_ConstantValue;
		((ConstantValue_attribute *) attribute)->constantvalue_index = u2Read();
	}

	else if (strcmp("Code", nome) == 0) {
		attribute = (Code_attribute *) calloc(sizeof (Code_attribute), 1);
		((Code_attribute *) attribute)->attribute_name_index = name_index;
		((Code_attribute *) attribute)->attribute_length = length;
		((Code_attribute *) attribute)->tag = ATTR_Code;
		((Code_attribute *) attribute)->max_stack = u2Read();
		((Code_attribute *) attribute)->max_locals = u2Read();

		((Code_attribute *) attribute)->code_length = u4Read();
		((Code_attribute *) attribute)->code = (u1 *) calloc(sizeof (u1), ((Code_attribute *) attribute)->code_length);
		for (i = 0; i < ((Code_attribute *) attribute)->code_length; i++) {
			((Code_attribute *) attribute)->code[i] = u1Read();
		}

		((Code_attribute *) attribute)->exception_table_length = u2Read();
		((Code_attribute *) attribute)->exception_table = (exception_tab *) calloc(sizeof (exception_tab),
				((Code_attribute *) attribute)->exception_table_length);
		for (i = 0; i < ((Code_attribute *) attribute)->exception_table_length; i++) {
			((Code_attribute *) attribute)->exception_table[i].start_pc = u2Read();
			((Code_attribute *) attribute)->exception_table[i].end_pc = u2Read();
			((Code_attribute *) attribute)->exception_table[i].handler_pc = u2Read();
			((Code_attribute *) attribute)->exception_table[i].catch_type = u2Read();
		}

		((Code_attribute *) attribute)->attributes_count = u2Read();
		((Code_attribute *) attribute)->attributes = (void *) calloc(sizeof (void *),
				((Code_attribute *) attribute)->attributes_count);
		for (i = 0; i < ((Code_attribute *) attribute)->attributes_count; i++) {
			((Code_attribute *) attribute)->attributes[i] = read_attribute_info();
		}
	}

	else if (strcmp("Deprecated", nome) == 0) {
		attribute = (Deprecated_attribute *) calloc(sizeof (Deprecated_attribute), 1);
		((Deprecated_attribute *) attribute)->attribute_name_index = name_index;
		((Deprecated_attribute *) attribute)->attribute_length = length;
		((Deprecated_attribute *) attribute)->tag = ATTR_Deprecated;
	}

	else if (strcmp("Exceptions", nome) == 0) {
		attribute = (Exceptions_attribute *) calloc(sizeof (Exceptions_attribute), 1);
		((Exceptions_attribute *) attribute)->attribute_name_index = name_index;
		((Exceptions_attribute *) attribute)->attribute_length = length;
		((Exceptions_attribute *) attribute)->tag = ATTR_Exceptions;

		((Exceptions_attribute *) attribute)->number_of_exceptions = u2Read();
		((Exceptions_attribute *) attribute)->exception_index_table = (u2 *) calloc(sizeof (u2),
				((Exceptions_attribute *) attribute)->number_of_exceptions);
		for (i = 0; i < ((Exceptions_attribute *) attribute)->number_of_exceptions; i++) {
			((Exceptions_attribute *) attribute)->exception_index_table[i] = u2Read();
		}
	}

	else if (strcmp("InnerClasses", nome) == 0) {
		attribute = (InnerClasses_attribute *) calloc(sizeof (InnerClasses_attribute), 1);
		((InnerClasses_attribute *) attribute)->attribute_name_index = name_index;
		((InnerClasses_attribute *) attribute)->attribute_length = length;
		((InnerClasses_attribute *) attribute)->tag = ATTR_InnerClasses;

		((InnerClasses_attribute *) attribute)->number_of_classes = u2Read();
		((InnerClasses_attribute *) attribute)->classes = (class_tab *) calloc(sizeof (class_tab),
				((InnerClasses_attribute *) attribute)->number_of_classes);
		for (i = 0; i < ((InnerClasses_attribute *) attribute)->number_of_classes; i++) {
			((InnerClasses_attribute *) attribute)->classes[i].inner_class_info_index = u2Read();
			((InnerClasses_attribute *) attribute)->classes[i].outer_class_info_index = u2Read();
			((InnerClasses_attribute *) attribute)->classes[i].inner_name_index = u2Read();
			((InnerClasses_attribute *) attribute)->classes[i].inner_class_access_flags = u2Read();
		}
	}

	else if (strcmp("LineNumberTable", nome) == 0) {
		attribute = (LineNumberTable_attribute *) calloc(sizeof (LineNumberTable_attribute), 1);
		((LineNumberTable_attribute *) attribute)->attribute_name_index = name_index;
		((LineNumberTable_attribute *) attribute)->attribute_length = length;
		((LineNumberTable_attribute *) attribute)->tag = ATTR_LineNumberTable;

		((LineNumberTable_attribute *) attribute)->line_number_table_length = u2Read();
		((LineNumberTable_attribute *) attribute)->line_number_table = (line_number_tab *) calloc(sizeof (line_number_tab),
				((LineNumberTable_attribute *) attribute)->line_number_table_length);
		for (i = 0; i < ((LineNumberTable_attribute *) attribute)->line_number_table_length; i++) {
			((LineNumberTable_attribute *) attribute)->line_number_table[i].start_pc = u2Read();
			((LineNumberTable_attribute *) attribute)->line_number_table[i].line_number = u2Read();
		}
	}

	else if (strcmp("LocalVariableTable", nome) == 0) {
		attribute = (LocalVariableTable_attribute *) calloc(sizeof (LocalVariableTable_attribute), 1);
		((LocalVariableTable_attribute *) attribute)->attribute_name_index = name_index;
		((LocalVariableTable_attribute *) attribute)->attribute_length = length;
		((LocalVariableTable_attribute *) attribute)->tag = ATTR_LocalVariableTable;

		((LocalVariableTable_attribute *) attribute)->local_variable_table_length = u2Read();
		((LocalVariableTable_attribute *) attribute)->local_variable_table = (local_variable_tab *) calloc(sizeof (local_variable_tab),
				((LocalVariableTable_attribute *) attribute)->local_variable_table_length);
		for (i = 0; i < ((LocalVariableTable_attribute *) attribute)->local_variable_table_length; i++) {
			((LocalVariableTable_attribute *) attribute)->local_variable_table[i].start_pc = u2Read();
			((LocalVariableTable_attribute *) attribute)->local_variable_table[i].length = u2Read();
			((LocalVariableTable_attribute *) attribute)->local_variable_table[i].name_index = u2Read();
			((LocalVariableTable_attribute *) attribute)->local_variable_table[i].descriptor_index = u2Read();
			((LocalVariableTable_attribute *) attribute)->local_variable_table[i].index = u2Read();
		}
	}

	else if (strcmp("SourceFile", nome) == 0) {
		attribute = (SourceFile_attribute *) calloc(sizeof (SourceFile_attribute), 1);
		((SourceFile_attribute *) attribute)->attribute_name_index = name_index;
		((SourceFile_attribute *) attribute)->attribute_length = length;
		((SourceFile_attribute *) attribute)->tag = ATTR_SourceFile;
		((SourceFile_attribute *) attribute)->sourcefile_index = u2Read();
	}

	else if (strcmp("Synthetic", nome) == 0) {
		attribute = (Synthetic_attribute *) calloc(sizeof (Synthetic_attribute), 1);
		((Synthetic_attribute *) attribute)->attribute_name_index = name_index;
		((Synthetic_attribute *) attribute)->attribute_length = length;
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

	if ((class->methods = (method_info*) calloc(sizeof (method_info), class->methods_count)) == NULL) {
		perror("Methods");
		return -1;
	}

	for (i = 0; i < class->methods_count; i++) {
		class->methods[i].access_flags = u2Read();
		class->methods[i].name_index = u2Read();
		class->methods[i].descriptor_index = u2Read();
		class->methods[i].attributes_count = u2Read();

		if ((class->methods[i].attributes = calloc(sizeof (void *), class->methods[i].attributes_count)) == NULL) {
			perror("Methods");
			return -1;
		}

		for (j = 0; j < class->methods[i].attributes_count; j++) {
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

	if ((class->attributes = calloc(sizeof (void *), class->attributes_count)) == NULL) {
		perror("Attributes");
		return -1;
	}

	for (i = 0; i < class->attributes_count; i++) {
		class->attributes[i] = read_attribute_info();
	}

	return 0;
}

/*
 \brief Libera uma estrutura de classe e suas estruturas internas.
 \param class_file Ponteiro para a estrutura que sera' liberada
 */
void free_class_file(struct ClassFile* class_file)
{

}
