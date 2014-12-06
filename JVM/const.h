#ifndef CONST_H_
#define CONST_H_

#define isBitActivated(variable, index) ((variable) & (1<<(index - 1)))

#define CONSTANT_Null 0

/*****************************
 * CONTANTES DO POOL
 *****************************/
 
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

/*****************************
 * FLAGS DE ACESSO
 *****************************/
#define AFPuplic    0x0001
#define AFPrivate   0x0002
#define AFProtected 0x0004
#define AFStatic    0x0008
#define AFFinal     0x0010
#define AFSuper     0x0020
#define AFVolatile  0x0040
#define AFTransient 0x0080
#define AFNative    0x0100
#define AFInterface 0x0200
#define AFAbstract  0x0400
#define AFStrict    0x0800

/*****************************
 * CONTANTES DE ATRIBUTO
 *****************************/
#define ATTR_ConstantValue			0
#define ATTR_Code					1
#define ATTR_Deprecated				2
#define ATTR_Exceptions				3
#define ATTR_InnerClasses			4
#define ATTR_LineNumberTable		5
#define ATTR_LocalVariableTable		6
#define ATTR_SourceFile				7

/*****************************
 * TIPOS DE RETORNO
 *****************************/
#define RETURN_none 	0
#define RETURN_32bits 	1
#define RETURN_64bits 	2

/*****************************
 * TIPOS DE VARIAVEIS
 *****************************/
#define TYPE_reference 	0
#define	TYPE_boolean 	4
#define	TYPE_char 		5
#define	TYPE_float 		6
#define	TYPE_double 	7
#define	TYPE_byte 		8
#define	TYPE_short 		9
#define	TYPE_int 		10
#define	TYPE_long 		11

#define	TYPE_boolean_size	1
#define	TYPE_byte_size		1
#define	TYPE_char_size		2
#define	TYPE_short_size		2
#define TYPE_reference_size	4
#define	TYPE_int_size 		4
#define	TYPE_float_size		4
#define	TYPE_double_size	8
#define	TYPE_long_size		8

#endif
