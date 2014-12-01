//
//  classLoader.h
//
//
//  Created by Paula Vasconcelos Gueiros on 11/25/14.
//
//

#ifndef _classLoader_h
#define _classLoader_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

// Definição dos tipos de constantes
#define CContinued          0
#define CUtf8               1
#define CInteger            3
#define CFloat              4
#define CLong               5
#define CDouble             6
#define CClass              7
#define CString             8
#define CFieldRef           9
#define CMethodRef          10
#define CInterfaceMethodRef 11
#define CNameType           12

#define isBitActivated(variable, index) ((variable) & (1<<(index - 1)))

typedef uint8_t u1;
typedef uint16_t u2;
typedef uint32_t u4;

union fltConv {
    float f;
    uint32_t i;
} u;

union dblConv {
    double d;
    long l;
} du;

typedef struct {
    u2 innerClassInfoIndex;
    u2 outerClassInfoIndex;
    u2 innerNameIndex;
    u2 innerClassAccessFlags;
} classType;

typedef struct {
    u2 startPc;
    u2 endPc;
    u2 handlerPc;
    u2 catchType;
} exceptionTableType;

typedef struct attrInfo {
    u2 attributeNameIndex;
    u4 attributeLength;
    union {
        struct {
            u2 constantValueIndex;
        } ConstantValue;
        struct {
            u2 maxStack;
            u2 maxLocals;
            u4 codeLength;
            u1 * code /*[codeLength]*/;
            u2 exceptionTableLength;
            exceptionTableType * exceptionTable /*[exceptionTableLength]*/;
            u2 attributeCount;
            struct attrInfo * attributes /*[attributeCount]*/;
        } Code;
        struct {
            u2 numberOfExceptions;
            u2 * exceptionIndexTable /*[numberOfExceptions]*/;
        } Exceptions;
        struct {
            u2 numberOfClasses;
            classType * classes /*[numberOfClasses]*/;
        } InnerClasses;
        struct {
            
        } Synthetic;
        struct {
            u1 * info;
        } Default;
    } type;
} attributeInfo;

typedef struct {
    u2 accessFlags;
    u2 nameIndex;
    u2 descriptorIndex;
    u2 attributeCount;
    attributeInfo * attributes /*[attributeCount]*/;
} fieldInfo, methodInfo;

typedef struct {
    u1 tag;
    union {
        struct {
            char bytes[26]; /*"(large numeric continued)"*/
        } Continued;
        struct {
            u2 length;
            u1 * bytes;
        } Utf8;
        struct {
            u4 bytes;
        } Integer, Float;
        struct {
            u4 lowBytes;
            u4 highBytes;
        } Long, Double;
        struct {
            u2 nameIndex;
        } Class;
        struct {
            u2 stringIndex;
        } String;
        struct {
            u2 classIndex;
            u2 nameTypeIndex;
        } FieldRef, MethodRef, InterfaceMethodRef;
        struct {
            u2 nameIndex;
            u2 descriptorIndex;
        } NameType;
    } type;
} cpInfo;

typedef struct {
    u4 magicNumber;
    
    u2 minorVersion;
    u2 majorVersion;
    
    u2 constantPoolCount;
    cpInfo * constantPool /*[constantPoolCount - 1]*/;
    
    u2 accessFlags;
    
    u2 thisClass;
    u2 superClass;
    
    u2 interfaceCount;
    u2 * interfaces /*[interfaceCount]*/;
    
    u2 fieldCount;
    fieldInfo * fields /*[fieldCount]*/;
    
    u2 methodCount;
    methodInfo * methods /*[methodCount]*/;
    
    u2 attributeCount;
    attributeInfo * attributes /*[attributeCount]*/;
} classStructure;

typedef struct opcode_info {
	char descricao[50];
	unsigned short operandos_count;
	unsigned int * operandos_index;
} opcode_informacao;

u1 u1Read (FILE * file);
u2 u2Read (FILE * file);
u4 u4Read (FILE * file);
int verifyMagic (FILE * file, classStructure * cs);
void storeVersions (FILE * file, classStructure * cs);
void storeConstantPool (FILE * file, classStructure * cs);
void storeAccessFlags (FILE * file, classStructure * cs);
void storeClasses (FILE * file, classStructure * cs);
void storeInterfaces (FILE * file, classStructure * cs);
void storeFields (FILE * file, classStructure * cs);
void storeMethods (FILE * file, classStructure * cs);
void storeAttributes (FILE * file, classStructure * cs);
void storeSingleAttribute (FILE * file, classStructure * cs, attributeInfo * att);
void storeConstValueAttr (FILE * file, attributeInfo * att);
void storeCodeAttr (FILE * file, classStructure * cs, attributeInfo * att);
void storeExceptionsAttr (FILE * file, attributeInfo * att);
void storeInnerClassesAttr (FILE * file, attributeInfo * att);
void storeSyntheticAttr (FILE * file, attributeInfo * att);
void storeDefaultAttr (FILE * file, attributeInfo * att);
void getAccessPerm (int intValue, char * target);
void saveConstantPool (FILE * fileTrgt, classStructure * cs);
void saveGeneral (FILE * fileTrgt, classStructure * cs, char * accessType);
void saveInterfaces (FILE * fileTrgt, classStructure * cs);
void saveFields (FILE * fileTrgt, classStructure * cs);
void saveMethods (FILE * fileTrgt, classStructure * cs);
void saveAttributes (FILE * fileTrgt, classStructure * cs);
void saveSingleAttribute (FILE * fileTrgt, classStructure * cs, attributeInfo * att, int a);
void carregar_opcode_informacao();
void imprimir_mnemonics(u1 * bytecode, u2 size, FILE * file);
opcode_informacao * op_info;

#endif

