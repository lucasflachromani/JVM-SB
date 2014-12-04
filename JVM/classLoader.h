#ifndef CLOAD_H
#define CLOAD_H

#include "constantes.h"
#include "types.h"

struct ClassFile *class;

int open_file(char* file_name);
void close_file();
u1 u1Read ();
u2 u2Read ();
u4 u4Read ();
void read_constant_pool();
char * getName(struct ClassFile *class_file, u2 name_index);
int read_s();
int read_interfaces();
int read_fields();
void *read_attribute_info();
int read_methods();
int read_attributes();
struct ClassFile * read_class_file(char *nome_arq);
void free_class_file(struct ClassFile* class_file);

#endif
