
#ifndef METODOS_H_
#define METODOS_H_

#include "classloader.h"

/* Variaveis usadas para saber qual o retorno da funcao */
u1 returnType;
u8 returnValue;

methodInfo * getMainMethod();
methodInfo * getInitStaticMethod();
methodInfo * getMethodByNameAndDescIndex(classStructure *main_class, classStructure *name_type_class, u2 name_type_index);
int getNumParameters(classStructure *class, methodInfo *method);
methodInfo * getInitMethod(u1 *desc, u2 desc_len);
void executarMetodo();
void prepararMetodo(classStructure *class, methodInfo *method);
void terminarMetodo();

#endif
