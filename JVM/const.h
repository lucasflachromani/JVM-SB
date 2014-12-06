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
#define ATTR_CONSTANT_VALUE				0
#define ATTR_CODE						1
#define ATTR_DEPRECATED					2
#define ATTR_EXCEPTIONS					3
#define ATTR_INNER_CLASSES				4
#define ATTR_LINE_NUMBER_TABLE			5
#define ATTR_LOCAL_VARIABLE_TABLE		6
#define ATTR_SOURCE_FILE				7

/*****************************
 * TIPOS DE RETORNO
 *****************************/
#define RETURN_NONE 	0
#define RETURN_32bits 	1
#define RETURN_64bits 	2

/*****************************
 * TIPOS DE VARIAVEIS
 *****************************/
#define TYPE_REFERENCE 	0
#define	TYPE_BOOLEAN 	4
#define	TYPE_CHAR 		5
#define	TYPE_FLOAT 		6
#define	TYPE_DOUBLE 	7
#define	TYPE_BYTE 		8
#define	TYPE_SHORT 		9
#define	TYPE_INT 		10
#define	TYPE_LONG 		11

#define	TYPE_BOOLEAN_SIZE	1
#define	TYPE_BYTE_SIZE		1
#define	TYPE_CHAR_SIZE		2
#define	TYPE_SHORT_SIZE		2
#define TYPE_REFERENCE_SIZE	4
#define	TYPE_INT_SIZE 		4
#define	TYPE_FLOAT_SIZE		4
#define	TYPE_DOUBLE_SIZE	8
#define	TYPE_LONG_SIZE		8

#endif
