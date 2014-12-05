
#ifndef TYPES_H_
#define TYPES_H_

#include <stdint.h>
#include <inttypes.h>

typedef uint8_t  u1;
typedef uint16_t u2;
typedef uint32_t u4;
typedef uint64_t u8;

/************************
 * TYPES FOR CONVERSION
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
 * TABLES FOR ATTRIBUTES
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
} lineNumberTableType;

/*************************
 * STATIC STRUCT
 *************************/
typedef struct {
	u1 * className;
	u2 fieldCount;
	u8 * value;
} staticStruct;

//NEW ---------------------------------------------------
/*************************
 * 	ATTRIBUTE INFO
 *************************/
typedef struct {
	u2 attributeNameIndex;
	u4 attributeLength;
	u2 tag;
	u1 * info;
} attributeInfo;

/*************************
 * FIELD AND METHOD INFO
 *************************/
typedef struct {
	u2 	accessFlags;
	u2 	nameIndex;
	u2 	descriptorIndex;
	u2 	attributeCount;
	void 	** attributes;
} fieldInfo, methodInfo;

//NEW ---------------------------------------------------
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

//PARTIALLY NEW -----------------------------------------
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
    void ** attributes /*[attributeCount]*/; //modificar depois
} classStructure;











/*
 * ATTRIBUTES
 */

typedef struct ConstantValue_attribute {
	u2 attributeNameIndex;
	u4 attributeLength;
	u2 tag;
	u2 constantValueIndex;
} ConstantValue_attribute;

typedef struct Code_attribute {
	u2 			attributeNameIndex;
	u4 			attributeLength;
	u2 			tag;
	u2 			maxStack;
	u2 			maxLocals;
	u4 			codeLength;
	u1 			* code;
	u2 			exceptionTableLength;
	exceptionTableType * exceptionTable;
	u2 			attributeCount;
	void 		** attributes;
} Code_attribute;

typedef struct Deprecated_attribute {
	u2 attributeNameIndex;
	u4 attributeLength;
	u2 tag;
} Deprecated_attribute;

typedef struct Exceptions_attribute {
	u2 attributeNameIndex;
	u4 attributeLength;
	u2 tag;
	u2 numberOfExceptions;
	u2 * exceptionIndexTable;
} Exceptions_attribute;

typedef struct InnerClasses_attribute {
	u2 		attributeNameIndex;
	u4 		attributeLength;
	u2 		tag;
	u2 		numberOfClasses;
	classType * classes;
} InnerClasses_attribute;

typedef struct LineNumberTable_attribute {
	u2 				attributeNameIndex;
	u4 				attributeLength;
	u2 				tag;
	u2 				lineNumberTableLength;
	lineNumberTableType 	* lineNumberTable;
} LineNumberTable_attribute;

typedef struct {
	u2 startPc;
	u2 length;
	u2 nameIndex;
	u2 descriptorIndex;
	u2 index;
} localVariableTableType;

typedef struct LocalVariableTable_attribute {
	u2 					attributeNameIndex;
	u4 					attributeLength;
	u2 					tag;
	u2 					localVariableTableLength;
	localVariableTableType 	* localVariableTable;
} LocalVariableTable_attribute;

typedef struct SourceFile_attribute {
	u2 attributeNameIndex;
	u4 attributeLength;
	u2 tag;
	u2 sourceFileIndex;
} SourceFile_attribute;

typedef struct Synthetic_attribute {
	u2 attributeNameIndex;
	u4 attributeLength;
} Synthetic_attribute;













/*************************
 * FUNCTIONS
 *************************/
u8 convert_2x32_to_64_bits(u4 low, u4 high);
u4 convert_2x8_to_32_bits(u4 low, u4 high);
void convert_64_bits_to_2x32(u8 value, u4 *low, u4 *high);
float convert_cast_32_bits_to_float(u4 bits);
double convert_cast_2x32_bits_to_double(u4 low, u4 high);

#endif
