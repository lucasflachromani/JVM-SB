
#ifndef TIPOS_H_
#define TIPOS_H_

#include <stdint.h>
#include <inttypes.h>

typedef uint8_t  u1;
typedef uint16_t u2;
typedef uint32_t u4;
typedef uint64_t u8;

typedef struct OPCODE_info {
	char descricao[30];
	unsigned short operandos_count;
	unsigned int *operandos_index;
} opcode_informacao;

/************************
 * TIPOS PARA CONVERSAO
 ************************/
union fltConv {
    float f;
    uint32_t i;
} u;

union dblConv {
    double d;
    long l;
} du;

/*************************
 * TABELAS PARA ATTRIBUTES
 *************************/
typedef struct {
	u2 startPc;
	u2 endPc;
	u2 handlerPc;
	u2 catchType;
} exceptionTableType;

typedef struct {
	u2 innerClassInfoIndex;
	u2 outerClassInfoIndex;
	u2 innerNameIndex;
	u2 innerClassAccessFlags;
} classType;

typedef struct {
	u2 startPc;
	u2 lineNumber;
} LineNumberTableType;

typedef struct {
    u2 startPc;
    u2 length;
    u2 nameIndex;
    u2 descriptorIndex;
    u2 index;
} LocalVariableTableType;

/*************************
 * STATIC STRUCT
 *************************/
typedef struct {
	u1 * className;
	u2 fieldCount;
	u8 * value;
} staticStruct;

/*************************
 * 	ATTRIBUTE INFO
 *************************/
typedef struct attrInfo {
    u2 attributeNameIndex;
    u4 attributeLength;
    u2 tag;
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
            u2 sourceFileIndex;
        } SourceFile;
        struct {
            
        } Synthetic, Deprecated;
        struct {
            u2 	lineNumberTableLength;
            LineNumberTableType * lineNumberTable;
        } LineNumberTable;
        struct {
            u2 	localVariableTableLength;
            LocalVariableTableType 	* localVariableTable;
        } LocalVariableTable;
        struct {
            u1 * info;
        } Default;
    } type;
} attributeInfo;

/*************************
 * FIELD AND METHOD INFO
 *************************/
typedef struct {
	u2 	accessFlags;
	u2 	nameIndex;
	u2 	descriptorIndex;
	u2 	attributeCount;
	attributeInfo * attributes;
} fieldInfo, methodInfo;

/*************************
 * CONSTANT POOL INFO
 *************************/
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

/*************************
 * CLASS STRUCTURE
 *************************/
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
    attributeInfo * attributes /*[attributeCount]*/; //modificar depois
} classStructure;

/*************************
 * FUNCOES
 *************************/
u8 converter2x32To64bits(u4 low, u4 high);
u4 converter2x8To32bits(u4 low, u4 high);
void converter64bitsTo2x32(u8 value, u4 *low, u4 *high);
float converterCast32bitsToFloat(u4 bits);
double convertCast2x32bitsToDouble(u4 low, u4 high);

#endif
