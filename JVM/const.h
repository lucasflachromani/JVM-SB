
#ifndef CONST_H_
#define CONST_H_

/*
 * Access flags
 */
#define ACC_PUBLIC    0x0001
#define ACC_PRIVATE   0x0002
#define ACC_PROTECTED 0x0004
#define ACC_STATIC    0x0008
#define ACC_FINAL     0x0010
#define ACC_SUPER     0x0020
#define ACC_VOLATILE  0x0040
#define ACC_TRANSIENT 0x0080
#define ACC_NATIVE    0x0100
#define ACC_INTERFACE 0x0200
#define ACC_ABSTRACT  0x0400
#define ACC_STRICT    0x0800

/*
 * Constant's flags
 */
#define CONSTANT_Class              7
#define CONSTANT_Fieldref           9
#define CONSTANT_Methodref          10
#define CONSTANT_InterfaceMethodref 11
#define CONSTANT_String             8
#define CONSTANT_Integer            3
#define CONSTANT_Float              4
#define CONSTANT_Long               5
#define CONSTANT_Double             6
#define CONSTANT_NameAndType        12
#define CONSTANT_Utf8               1

/*
 * Attributes flags
 */
#define ATTR_ConstantValue			0
#define ATTR_Code					1
#define ATTR_Deprecated				2
#define ATTR_Exceptions				3
#define ATTR_InnerClasses			4
#define ATTR_LineNumberTable		5
#define ATTR_LocalVariableTable		6
#define ATTR_SourceFile				7

/*
 * Variable types
 */
#define TYPE_reference 	0
#define	TYPE_boolean 	4
#define	TYPE_char 		5
#define	TYPE_float 		6
#define	TYPE_double 	7
#define	TYPE_byte 		8
#define	TYPE_short 		9
#define	TYPE_int 		10
#define	TYPE_long 		11

#define TYPE_reference_size	4
#define	TYPE_boolean_size	1
#define	TYPE_char_size		2
#define	TYPE_float_size		4
#define	TYPE_double_size	8
#define	TYPE_byte_size		1
#define	TYPE_short_size		2
#define	TYPE_int_size 		4
#define	TYPE_long_size		8

/*
 * NULL
 */
#define CONSTANT_Null 0

/*
 * RETURN
 */
#define RETURN_none 	0
#define RETURN_32bits 	1
#define RETURN_64bits 	2

/*
*
* New
*
*/
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

#endif
