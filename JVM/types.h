
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
typedef struct field_info_t {
	u2 	access_flags;
	u2 	name_index;
	u2 	descriptor_index;
	u2 	attributes_count;
	void 	**attributes;
} field_info;


/*
 * METHODS
 */
typedef struct method_info_t {
	u2 	access_flags;
	u2 	name_index;
	u2 	descriptor_index;
	u2 	attributes_count;
	void 	**attributes;
} method_info;

/*
 * CLASSFILE
 */
struct ClassFile {
	u4      		magic;
	u2 			minor_version;
	u2 			major_version;
	u2 			constant_pool_count;
	void 			**constant_pool;
	u2 			access_flags;
	u2 			this_class;
	u2 			super_class;
	u2 			interfaces_count;
	u2 			*interfaces;
	u2 			fields_count;
	field_info 	*fields;
	u2 			methods_count;
	method_info   *methods;
	u2 			attributes_count;
	void 			**attributes;
};


/*
 * CLASS STATIC
 */
typedef struct static_struct {
	u1 *class_name;
	u2 fields_count;
	u8 *value;
}static_struct;

/*
 * CONSTANT POOL
 */
typedef struct cp_info_t {
	u1 tag;
	u1 *info;
} cp_info;

struct CONSTANT_Class_info {
	u1 tag;
	u2 name_index;
};

struct CONSTANT_Fieldref_info {
	u1 tag;  				/* valor 9 */
	u2 class_index;
	u2 name_and_type_index;
};

struct CONSTANT_NameAndType_info {
	u1 tag;  				/* valor 12*/
	u2 name_index;
	u2 descriptor_index;
};

struct CONSTANT_Utf8_info {
	u1 tag;  				/* valor 1*/
	u2 length;
	u1 *bytes;
};

struct CONSTANT_Methodref_info {
	u1 tag;  				/* valor 10*/
	u2 class_index;
	u2 name_and_type_index; /*if starts with <, should be <init>*/
};

struct CONSTANT_InterfaceMethodref_info {
	u1 tag;  				/* valor 11*/
	u2 class_index;
	u2 name_and_type_index;
};

struct CONSTANT_String_info {
	u1 tag;				/* valor 8*/
	u2 string_index;
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
	u4 high_bytes;		/* unsigned*/
	u4 low_bytes;			/* unsigned*/
};

struct CONSTANT_Double_info {
	u1 tag;				/* valor 6*/
	u4 high_bytes;		/* unsigned*/
	u4 low_bytes;			/* unsigned*/
};

/*
 * ATTRIBUTES TABS
 */
typedef struct Exc_tab {
	u2 start_pc;
	u2 end_pc;
	u2 handler_pc;
	u2 catch_type;
} exception_tab;

typedef struct Class_t {
	u2 inner_class_info_index;
	u2 outer_class_info_index;
	u2 inner_name_index;
	u2 inner_class_access_flags;
} class_tab;

typedef struct LineNum {
	u2 start_pc;
	u2 line_number;
} line_number_tab;

/*
 * ATTRIBUTES
 */
typedef struct attribute_info_t {
	u2 attribute_name_index;
	u4 attribute_length;
	u2 tag;
	u1 *info;
} attribute_info;

typedef struct ConstantValue_attribute {
	u2 attribute_name_index;
	u4 attribute_length;
	u2 tag;
	u2 constantvalue_index;
} ConstantValue_attribute;

typedef struct Code_attribute {
	u2 			attribute_name_index;
	u4 			attribute_length;
	u2 			tag;
	u2 			max_stack;
	u2 			max_locals;
	u4 			code_length;
	u1 			*code;
	u2 			exception_table_length;
	exception_tab *exception_table;
	u2 			attributes_count;
	void 			**attributes;
} Code_attribute;

typedef struct Deprecated_attribute {
	u2 attribute_name_index;
	u4 attribute_length;
	u2 tag;
} Deprecated_attribute;

typedef struct Exceptions_attribute {
	u2 attribute_name_index;
	u4 attribute_length;
	u2 tag;
	u2 number_of_exceptions;
	u2 *exception_index_table;
} Exceptions_attribute;

typedef struct InnerClasses_attribute {
	u2 		attribute_name_index;
	u4 		attribute_length;
	u2 		tag;
	u2 		number_of_classes;
	class_tab *classes;
} InnerClasses_attribute;

typedef struct LineNumberTable_attribute {
	u2 				attribute_name_index;
	u4 				attribute_length;
	u2 				tag;
	u2 				line_number_table_length;
	line_number_tab 	*line_number_table;
} LineNumberTable_attribute;

typedef struct local_variable {
	u2 start_pc;
	u2 length;
	u2 name_index;
	u2 descriptor_index;
	u2 index;
} local_variable_tab;

typedef struct LocalVariableTable_attribute {
	u2 					attribute_name_index;
	u4 					attribute_length;
	u2 					tag;
	u2 					local_variable_table_length;
	local_variable_tab 	*local_variable_table;
} LocalVariableTable_attribute;

typedef struct SourceFile_attribute {
	u2 attribute_name_index;
	u4 attribute_length;
	u2 tag;
	u2 sourcefile_index;
} SourceFile_attribute;

typedef struct Synthetic_attribute {
	u2 attribute_name_index;
	u4 attribute_length;
} Synthetic_attribute;


/********
***NEW***
********/
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

//typedef uint8_t u1;
//typedef uint16_t u2;
//typedef uint32_t u4;

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
