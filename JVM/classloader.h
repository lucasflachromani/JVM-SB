#ifndef CLOAD_H
#define CLOAD_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <errno.h>

#include "const.h"
#include "tipos.h"
#include "inicializador.h"

classStructure * cs;

classStructure * leArquivoClasse (char * fileSrc);
u1 u1Read ();
u2 u2Read ();
u4 u4Read ();
int verifyMagic ();
int verifyVersion ();
void storeVersions ();
void storeConstantPool ();
void storeAccessFlags ();
void storeClasses ();
void storeInterfaces ();
void storeFields ();
void storeMethods ();
void storeAttributes ();
void storeSingleAttribute (attributeInfo * att);
void storeConstValueAttr (attributeInfo * att);
void storeCodeAttr (attributeInfo * att);
void storeExceptionsAttr (attributeInfo * att);
void storeInnerClassesAttr (attributeInfo * att);
void storeSyntheticAttr (attributeInfo * att);
void storeDefaultAttr (attributeInfo * att);
void storeDeprecatedAttr (attributeInfo * att);
void storeLineNumberTableAttr (attributeInfo * att);
void storeLocalVariableTableAttr (attributeInfo * att);
void storeSourceFileAttr (attributeInfo * att);
void getAccessPerm (int intValue, char * target);
void saveConstantPool (FILE * fileTrgt);
void saveGeneral (FILE * fileTrgt, char * accessType);
void saveInterfaces (FILE * fileTrgt);
void saveFields (FILE * fileTrgt);
void saveMethods (FILE * fileTrgt);
void saveAttributes (FILE * fileTrgt);
void saveSingleAttribute (FILE * fileTrgt, attributeInfo * att, int a);
void carregarOpcodeInformacao();
void imprimir_mnemonics(u1 * bytecode, u2 size, FILE * fileTrgt);
opcode_informacao * op_info;
char * getName (classStructure *class_file, u2 nameIndex);

#endif
