
#ifndef CARREGADOR_H_
#define CARREGADOR_H_

#include "classloader.h"

int32_t carregarClass(char *);
char *getClassName(classStructure *class);
char *getParentName(classStructure *class);
int getNumClasses();
classStructure * getClassByName(char *className);
classStructure * getClassByIndex(int index);
int32_t getFieldIndexByNameAndDesc(char *className, char *name, u2 name_len, char *desc, u2 desc_len);
u8 getStaticFieldValue(int32_t classIndex, int32_t field_index);
void setStaticFieldValue(int32_t classIndex, int32_t field_index, u8 value);
void trocaCaracter(char * o_string, char * s_string, char * r_string);

#endif
