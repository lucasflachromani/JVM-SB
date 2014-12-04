
#ifndef TYPES_H_
#define TYPES_H_

#include <stdint.h>
#include <inttypes.h>

typedef uint8_t  u1;
typedef uint16_t u2;
typedef uint32_t u4;
typedef uint64_t u8;

/*
 * FIELDS
 */
typedef struct {
	u2 	accessFlags;
	u2 	nameIndex;
	u2 	descriptorIndex;
	u2 	attributeCount;
	void 	** attributes;
} fieldInfo;


/*
 * METHODS
 */
typedef struct {
	u2 	accessFlags;
	u2 	nameIndex;
	u2 	descriptorIndex;
	u2 	attributeCount;
	void 	** attributes;
} methodInfo;

/*
 * CLASSFILE
 */
typedef struct {
	u4      	magicNumber;
	u2 			minorVersion;
	u2 			majorVersion;
	u2 			constantPoolCount;
	void 		** constantPool;
	u2 			accessFlags;
	u2 			thisClass;
	u2 			superClass;
	u2 			interfaceCount;
	u2 			* interfaces;
	u2 			fieldCount;
	fieldInfo 	* fields;
	u2 			methodCount;
	methodInfo * methods;
	u2 			attributeCount;
	void 		** attributes;
} classStructure;


/*
 * CLASS STATIC
 */
typedef struct {
	u1 * className;
	u2 fieldCount;
	u8 * value;
} staticStruct;

/*
 * CONSTANT POOL
 */
typedef struct {
	u1 tag;
	u1 * info;
} cpInfo;

struct CONSTANT_Class_info {
	u1 tag;
	u2 nameIndex;
};

struct CONSTANT_Fieldref_info {
	u1 tag;  				/* valor 9 */
	u2 classIndex;
	u2 nameTypeIndex;
};

struct CONSTANT_NameAndType_info {
	u1 tag;  				/* valor 12*/
	u2 nameIndex;
	u2 descriptorIndex;
};

struct CONSTANT_Utf8_info {
	u1 tag;  				/* valor 1*/
	u2 length;
	u1 * bytes;
};

struct CONSTANT_Methodref_info {
	u1 tag;  				/* valor 10*/
	u2 classIndex;
	u2 nameTypeIndex; /*if starts with <, should be <init>*/
};

struct CONSTANT_InterfaceMethodref_info {
	u1 tag;  				/* valor 11*/
	u2 classIndex;
	u2 nameTypeIndex;
};

struct CONSTANT_String_info {
	u1 tag;				/* valor 8*/
	u2 stringIndex;
};

struct CONSTANT_Integer_info {
	u1 tag;				/* valor 3*/
	u4 bytes;
};

struct CONSTANT_Float_info {
	u1 tag;				/* valor 4*/
	u4 bytes;
};

struct CONSTANT_Long_info {
	u1 tag;				/* valor 5*/
	u4 highBytes;		/* unsigned*/
	u4 lowBytes;			/* unsigned*/
};

struct CONSTANT_Double_info {
	u1 tag;				/* valor 6*/
	u4 highBytes;		/* unsigned*/
	u4 lowBytes;			/* unsigned*/
};

/*
 * ATTRIBUTES TABS
 */
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

/*
 * ATTRIBUTES
 */
typedef struct {
	u2 attributeNameIndex;
	u4 attributeLength;
	u2 tag;
	u1 * info;
} attributeInfo;

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


/********
***NEW***
********/



/********
***NEW***
********/

/*
 * FUNÇÕES
 */
u8 convert_2x32_to_64_bits(u4 low, u4 high);
u4 convert_2x8_to_32_bits(u4 low, u4 high);
void convert_64_bits_to_2x32(u8 value, u4 *low, u4 *high);
float convert_cast_32_bits_to_float(u4 bits);
double convert_cast_2x32_bits_to_double(u4 low, u4 high);

#endif
