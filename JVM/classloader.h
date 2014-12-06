#ifndef CLOAD_H
#define CLOAD_H

#include "const.h"
#include "tipos.h"

classStructure *class;

int open_file(char* file_name);
void close_file();
u1 u1Read ();
u2 u2Read ();
u4 u4Read ();
void read_constant_pool();
char * getName(classStructure *class_file, u2 nameIndex);
int read_s();
int read_interfaces();
int read_fields();
attributeInfo * read_attribute_info();
int read_methods();
int read_attributes();
classStructure * read_class_file(char *nome_arq);
void free_class_file(classStructure* classStructure);
void carregarOpcodeInformacao();
opcode_informacao *op_info;

#endif
