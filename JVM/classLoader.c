//
//  classLoader.c
//
//
//  Created by Paula Vasconcelos Gueiros on 11/25/14.
//
//

/* Software Basico - 2/2014
 * Professor: Marcelo Ladeira
 * Trabalho: Leitor / Exibidor do .class
 *
 * Descricao: Este trabalho consiste em um programa que le um
 * arquivo .class e carrega as informacoes do bytecode para uma
 * estrutura de classes.  Opcionalmente, gera um arquivo com
 * essas informacoes.
 *
 * Para compilar:       $ gcc -std=c99 classLoader.c -o classLoader
 * Para executar:       $ ./classLoader FileName.class OutFile.txt
 *                      $ ./classLoader FileName.class
 */

#include "classLoader.h"

/* @ brief Funcao Main: recebe um arquivo .class e chama as funcoes
 * de leitura e armazenamento das informacoes contidas no arquivo.
 * @ param argc numero de argumentos
 * @ param argv vetor contendo nome dos arquivos e inteiro que
 * decide se sera gerado arquivo de saida ou nao
 */
int main (int argc, char * argv[]) {
    FILE * file, * fileTrgt;
    char fileSrc[50], accessType[70];
    classStructure cs;
    
    carregar_opcode_informacao();

    strcpy (fileSrc, argv[1]);
    file = fopen (fileSrc, "rb");
    if (verifyMagic(file, &cs) && file) {
        storeVersions(file, &cs);               //armazena todos os dados em memoria
        storeConstantPool(file, &cs);
        storeAccessFlags(file, &cs);
        storeClasses(file, &cs);
        storeInterfaces(file, &cs);
        storeFields(file, &cs);
        storeMethods(file, &cs);
        storeAttributes(file, &cs);
    }
    else {
        printf("\nERRO: O arquivo não e do tipo .class");
    }
    
    fileTrgt = fopen (argv[2], "w");
    if (strcmp (argv[2], "")) {                 //armazena todos os dados em arquivo texto
        fprintf(fileTrgt, "Nome do arquivo: %s\n\n", fileSrc);
        saveGeneral(fileTrgt, &cs, accessType);
        saveConstantPool(fileTrgt, &cs);
        saveInterfaces(fileTrgt, &cs);
        saveFields(fileTrgt, &cs);
        saveMethods(fileTrgt, &cs);
        saveAttributes(fileTrgt, &cs);
        printf("Arquivo texto gerado.\n");
    }
    
    fclose (fileTrgt);
    fclose (file);
    
    printf("Programa Finalizado.\n");
    return 0;
}

/* @ brief Funcao que le um byte do arquivo e retorna o valor lido
 * @ param file : arquivo de entrada
 */
u1 u1Read (FILE * file) {
    u1 info;
    
    fread(&info, sizeof(u1), 1, file);
    
    return info;
}

/* @ brief Funcao que le dois bytes do arquivo e retorna o valor lido
 * @ param file : arquivo de entrada
 */
u2 u2Read (FILE * file) {
    u1 b1, b2;
    u2 info;
    
    fread (&b1, sizeof(u1), 1, file);
    fread (&b2, sizeof(u1), 1, file);
    info = b1 << 8;
    info = info | b2;
    
    return info;
}

/* @ brief Funcao que le quatro bytes do arquivo e retorna o valor lido
 * @ param file : arquivo de entrada
 */
u4 u4Read (FILE *file) {
    u1 b1, b2, b3, b4;
    u4 info = 0;
    
    fread (&b1, sizeof(u1), 1, file);
    fread (&b2, sizeof(u1), 1, file);
    fread (&b3, sizeof(u1), 1, file);
    fread (&b4, sizeof(u1), 1, file);
    info = b1 << 24;
    info = info | b2 << 16;
    info = info | b3 << 8;
    info = info | b4;
    
    return info;
}

/* @ brief Funcao que verifica o numero magic do arquivo
 * @ param file : arquivo de entrada
 * @ param cs : estrutura de dados da classe java
 */
int verifyMagic (FILE * file, classStructure * cs) {
    cs->magicNumber = u4Read(file);
    if (cs->magicNumber == 0xCAFEBABE) return 1;
    return 0;
}


/* @ brief Funcao que armazena os valores de version
 * @ param file : arquivo de entrada
 * @ param cs : estrutura de dados da classe java
 */
void storeVersions (FILE * file, classStructure * cs) {
    cs->minorVersion = u2Read(file);
    cs->majorVersion = u2Read(file);
}


/* @ brief Funcao que armazena os valores da pool de constantes
 * @ param file : arquivo de entrada
 * @ param cs : estrutura de dados da classe java
 */
void storeConstantPool (FILE * file, classStructure * cs) {
    int a, b;
    
    cs->constantPoolCount = u2Read(file);
    cs->constantPool = malloc ((cs->constantPoolCount - 1) * sizeof(cpInfo));
    
    for (a = 0; a < cs->constantPoolCount - 1; a++) {
        cpInfo info, info2;
        info.tag = u1Read(file);
        
        switch (info.tag) {     // tipo da constante
            case CUtf8:
                info.type.Utf8.length = u2Read(file);
                info.type.Utf8.bytes = malloc ((info.type.Utf8.length + 1) * sizeof(u1));
                for (b = 0; b < info.type.Utf8.length; b++) {
                    info.type.Utf8.bytes[b] = u1Read(file);
                }
                info.type.Utf8.bytes[b] = '\0';
                break;
            case CInteger:
                info.type.Integer.bytes = u4Read(file);
                break;
            case CFloat:
                info.type.Float.bytes = u4Read(file);
                break;
            case CLong:
                info.type.Long.highBytes = u4Read(file);
                info.type.Long.lowBytes = u4Read(file);
                break;
            case CDouble:
                info.type.Double.highBytes = u4Read(file);
                info.type.Double.lowBytes = u4Read(file);
                break;
            case CClass:
                info.type.Class.nameIndex = u2Read(file);
                break;
            case CString:
                info.type.String.stringIndex = u2Read(file);
                break;
            case CFieldRef:
                info.type.FieldRef.classIndex = u2Read(file);
                info.type.FieldRef.nameTypeIndex = u2Read(file);
                break;
            case CMethodRef:
                info.type.MethodRef.classIndex = u2Read(file);
                info.type.MethodRef.nameTypeIndex = u2Read(file);
                break;
            case CInterfaceMethodRef:
                info.type.InterfaceMethodRef.classIndex = u2Read(file);
                info.type.InterfaceMethodRef.nameTypeIndex = u2Read(file);
                break;
            case CNameType:
                info.type.NameType.nameIndex = u2Read(file);
                info.type.NameType.descriptorIndex = u2Read(file);
                break;
            default:
                break;
        }
        cs->constantPool[a] = info;
        if (info.tag == CLong || info.tag == CDouble) {
            a++;
            info2.tag = 0;
            strcpy (info2.type.Continued.bytes, "(large numeric continued)");
            cs->constantPool[a] = info2;
        }
    }
}


/* @ brief Funcao que armazena o valor de access flags
 * @ param file : arquivo de entrada
 * @ param cs : estrutura de dados da classe java
 */
void storeAccessFlags (FILE * file, classStructure * cs) {
    cs->accessFlags = u2Read(file);
}

/* @ brief Funcao que armazena os valores de This class e Super class
 * @ param file : arquivo de entrada
 * @ param cs : estrutura de dados da classe java
 */
void storeClasses (FILE * file, classStructure * cs) {
    cs->thisClass = u2Read(file);
    cs->superClass = u2Read(file);
}

/* @ brief Funcao que armazena as interfaces
 * @ param file : arquivo de entrada
 * @ param cs : estrutura de dados da classe java
 */
void storeInterfaces (FILE * file, classStructure * cs) {
    int a;
    
    cs->interfaceCount = u2Read(file);
    cs->interfaces = malloc ((cs->interfaceCount) * sizeof(u2));
    
    for (a = 0; a < cs->interfaceCount; a++) {
        cs->interfaces[a] = u2Read(file);
    }
}

/* @ brief Funcao que armazena os fields
 * @ param file : arquivo de entrada
 * @ param cs : estrutura de dados da classe java
 */
void storeFields (FILE * file, classStructure * cs) {
    int a, b;
    
    cs->fieldCount = u2Read(file);
    cs->fields = malloc ((cs->fieldCount) * sizeof(fieldInfo));
    
    for (a = 0; a < cs->fieldCount; a++) {
        fieldInfo info;
        info.accessFlags = u2Read(file);
        info.nameIndex = u2Read(file);
        info.descriptorIndex = u2Read(file);
        info.attributeCount = u2Read(file);
        info.attributes = malloc ((info.attributeCount) * sizeof(attributeInfo));
        for (b = 0; b < info.attributeCount; b++) {
            storeSingleAttribute(file, cs, &(info.attributes[b]));
        }
        cs->fields[a] = info;
    }
}

/* @ brief Funcao que armazena os metodos
 * @ param file : arquivo de entrada
 * @ param cs : estrutura de dados da classe java
 */
void storeMethods (FILE * file, classStructure * cs) {
    int a, b;
    
    cs->methodCount = u2Read(file);
    cs->methods = malloc ((cs->methodCount) * sizeof(methodInfo));
    
    for (a = 0; a < cs->methodCount; a++) {
        methodInfo info;
        info.accessFlags = u2Read(file);
        info.nameIndex = u2Read(file);
        info.descriptorIndex = u2Read(file);
        info.attributeCount = u2Read(file);
        info.attributes = malloc ((info.attributeCount) * sizeof(attributeInfo));
        for (b = 0; b < info.attributeCount; b++) {
            storeSingleAttribute(file, cs, &(info.attributes[b]));
        }
        cs->methods[a] = info;
    }
}

/* @ brief Funcao que armazena os atributos
 * @ param file : arquivo de entrada
 * @ param cs : estrutura de dados da classe java
 */
void storeAttributes (FILE * file, classStructure * cs) {
    int a;
    
    cs->attributeCount = u2Read(file);
    cs->attributes = malloc (cs->attributeCount * sizeof(attributeInfo));
    for (a = 0; a < cs->attributeCount; a++) {
        storeSingleAttribute(file, cs, &(cs->attributes[a]));
    }
}

/* @ brief Funcao que armazena um único atributo
 * @ param file : arquivo de entrada
 * @ param cs : estrutura de dados da classe java
 * @ param att : ponteiro para local a armazenar o atributo
 */
void storeSingleAttribute (FILE * file, classStructure * cs, attributeInfo * att) {
    char * attType;
    
    att->attributeNameIndex = u2Read(file);
    att->attributeLength = u4Read(file);
    
    attType = malloc (cs->constantPool[att->attributeNameIndex - 1].type.Utf8.length * sizeof(char));
    strcpy (attType, (char *) cs->constantPool[att->attributeNameIndex - 1].type.Utf8.bytes);
    if (strcmp (attType, "ConstantValue") == 0) {
        storeConstValueAttr(file, att);
    }
    else if (strcmp (attType, "Code") == 0) {
        storeCodeAttr(file, cs, att);
    }
    else if (strcmp (attType, "Exceptions") == 0) {
        storeExceptionsAttr(file, att);
    }
    else if (strcmp (attType, "InnerClasses") == 0) {
        storeInnerClassesAttr(file, att);
    }
    else if (strcmp (attType, "Synthetic") == 0) {
        storeSyntheticAttr(file, att);
    }
    else {
        storeDefaultAttr(file, att);
    }
}

/* @ brief Funcao que armazena atributo do tipo ConstantValue
 * @ param file : arquivo de entrada
 * @ param att : ponteiro para local a armazenar o atributo
 */
void storeConstValueAttr (FILE * file, attributeInfo * att) {
    
    att->type.ConstantValue.constantValueIndex = u2Read(file);
}

/* @ brief Funcao que armazena atributo do tipo Code
 * @ param file : arquivo de entrada
 * @ param cs : estrutura de dados da classe java
 * @ param att : ponteiro para local a armazenar o atributo
 */
void storeCodeAttr (FILE * file, classStructure * cs, attributeInfo * att) {
    int a;
    
    att->type.Code.maxStack = u2Read(file);
    att->type.Code.maxLocals = u2Read(file);
    att->type.Code.codeLength = u4Read(file);
    att->type.Code.code = malloc (att->type.Code.codeLength * sizeof(u1));
    for (a = 0; a < att->type.Code.codeLength; a++) {
        att->type.Code.code[a] = u1Read(file);
    }
    att->type.Code.exceptionTableLength = u2Read(file);
    att->type.Code.exceptionTable = malloc (att->type.Code.exceptionTableLength * sizeof(exceptionTableType));
    for (a = 0; a < att->type.Code.exceptionTableLength; a++) {
        att->type.Code.exceptionTable[a].startPc = u2Read(file);
        att->type.Code.exceptionTable[a].endPc = u2Read(file);
        att->type.Code.exceptionTable[a].handlerPc = u2Read(file);
        att->type.Code.exceptionTable[a].catchType = u2Read(file);
    }
    att->type.Code.attributeCount = u2Read(file);
    att->type.Code.attributes = malloc (att->type.Code.attributeCount * sizeof(attributeInfo));
    for (a = 0; a < att->type.Code.attributeCount; a++) {
        storeSingleAttribute(file, cs, &(att->type.Code.attributes[a]));
    }
}

/* @ brief Funcao que armazena atributo do tipo Exceptions
 * @ param file : arquivo de entrada
 * @ param att : ponteiro para local a armazenar o atributo
 */
void storeExceptionsAttr (FILE * file, attributeInfo * att) {
    int a;
    
    att->type.Exceptions.numberOfExceptions = u2Read(file);
    att->type.Exceptions.exceptionIndexTable = malloc (att->type.Exceptions.numberOfExceptions * sizeof(u2));
    for (a = 0; a < att->type.Exceptions.numberOfExceptions; a++) {
        att->type.Exceptions.exceptionIndexTable[a] = u2Read(file);
    }
}

/* @ brief Funcao que armazena atributo do tipo InnerClasses
 * @ param file : arquivo de entrada
 * @ param att : ponteiro para local a armazenar o atributo
 */
void storeInnerClassesAttr (FILE * file, attributeInfo * att) {
    int a;
    
    att->type.InnerClasses.numberOfClasses = u2Read(file);
    att->type.InnerClasses.classes = malloc (att->type.InnerClasses.numberOfClasses * sizeof(classType));
    for (a = 0; a < att->type.InnerClasses.numberOfClasses; a++) {
        att->type.InnerClasses.classes[a].innerClassInfoIndex = u2Read(file);
        att->type.InnerClasses.classes[a].outerClassInfoIndex = u2Read(file);
        att->type.InnerClasses.classes[a].innerNameIndex = u2Read(file);
        att->type.InnerClasses.classes[a].innerClassAccessFlags = u2Read(file);
    }
}

/* @ brief Funcao que armazena atributo do tipo Synthetic
 * @ param file : arquivo de entrada
 * @ param att : ponteiro para local a armazenar o atributo
 */
void storeSyntheticAttr (FILE * file, attributeInfo * att) {
}

/* @ brief Funcao que armazena atributo padrao
 * @ param file : arquivo de entrada
 * @ param att : ponteiro para local a armazenar o atributo
 */
void storeDefaultAttr (FILE * file, attributeInfo * att) {
    int a;
    
    att->type.Default.info = malloc (att->attributeLength * sizeof(u1));
    for (a = 0; a < att->attributeLength; a++) {
        att->type.Default.info[a] = u1Read(file);
    }
}

/* @ brief Funcao que salva em arquivo as informacoes gerais do .class
 * @ param fileTrgt : arquivo de saida
 * @ param cs : estrutura de dados da classe java
 * @ param accessType : endereco de armazenamento da string correspondente
 * ao tipo de permissao identificada por accessFlags
 */
void saveGeneral (FILE * fileTrgt, classStructure * cs, char * accessType) {
    fprintf(fileTrgt, "------------------------------------------------------\n\n");
    fprintf(fileTrgt, "General Information:\n\n");
    fprintf(fileTrgt, "Minor Version: %14d\n", cs->minorVersion);
    fprintf(fileTrgt, "Major Version: %14d\n", cs->majorVersion);
    fprintf(fileTrgt, "Constant Pool Count: %8d\n", cs->constantPoolCount);
    getAccessPerm(cs->accessFlags, accessType);
    fprintf(fileTrgt, "Access Flags:            0x%x [%s]\n", cs->accessFlags, accessType);
    fprintf(fileTrgt, "This Class:        cpInfo #%d: <%s>\n", cs->thisClass, cs->constantPool[cs->constantPool[cs->thisClass - 1].type.Class.nameIndex - 1].type.Utf8.bytes);
    fprintf(fileTrgt, "Super Class:       cpInfo #%d: <%s>\n", cs->superClass, cs->constantPool[cs->constantPool[cs->superClass - 1].type.Class.nameIndex - 1].type.Utf8.bytes);
    fprintf(fileTrgt, "Interface Count: %12d\n", cs->interfaceCount);
    fprintf(fileTrgt, "Field Count: %16d\n", cs->fieldCount);
    fprintf(fileTrgt, "Method Count: %15d\n", cs->methodCount);
    fprintf(fileTrgt, "Attribute Count: %12d\n\n", cs->attributeCount);
}

/* @ brief Funcao que recebe um inteiro e retorna o tipo de permissao correspondente a ele
 * @ param intValue : valor inteiro de accessFlags
 * @ param target : endereco de armazenamento da string correspondente
 * ao tipo de permissao identificada por accessFlags
 */
void getAccessPerm (int intValue, char * target) {
    
    strcpy (target, "");
    
    if isBitActivated(intValue, 1) strcat (target, "public ");
    else if isBitActivated(intValue, 2) strcat (target, "private ");
    else if isBitActivated(intValue, 3) strcat (target, "protected ");
    
    if isBitActivated(intValue, 4) strcat (target, "static ");
    if isBitActivated(intValue, 5) strcat (target, "final ");
    if isBitActivated(intValue, 6) strcat (target, "synchronized ");
    if isBitActivated(intValue, 7) strcat (target, "volatile ");
    if isBitActivated(intValue, 8) strcat (target, "transient ");
    if isBitActivated(intValue, 9) strcat (target, "native ");
    if isBitActivated(intValue, 10) strcat (target, "interface ");
    if isBitActivated(intValue, 11) strcat (target, "abstract ");
}

/* @ brief Funcao que salva em arquivo os valores da pool de constantes
 * @ param fileTrgt : arquivo de saida
 * @ param cs : estrutura de dados da classe java
 */
void saveConstantPool (FILE * fileTrgt, classStructure * cs) {
    int a;
    long long whole;
    
    fprintf(fileTrgt, "------------------------------------------------------\n\n");
    fprintf(fileTrgt, "Constant Pool:\n\n");
    
    for (a = 0; a < cs->constantPoolCount - 1; a++) {
        fprintf(fileTrgt, "%d)\n", a + 1);
        switch (cs->constantPool[a].tag) {          // tipo da constante
            case CContinued:
                fprintf(fileTrgt, "%s\n\n",
                        cs->constantPool[a].type.Continued.bytes);
                break;
            case CUtf8:
                fprintf(fileTrgt, "Type: Utf8\n"
                                  "Length: %d\n"
                                  "String: %s\n\n",
                        cs->constantPool[a].type.Utf8.length,
                        cs->constantPool[a].type.Utf8.bytes);
                break;
            case CInteger:
                fprintf(fileTrgt, "Type: Integer\n"
                                  "Bytes: 0x%x\n"
                                  "Value: %d\n\n",
                        cs->constantPool[a].type.Integer.bytes,
                        cs->constantPool[a].type.Integer.bytes);
                break;
            case CFloat:
                u.i = cs->constantPool[a].type.Float.bytes;
                fprintf(fileTrgt, "Type: Float\n"
                                  "Bytes: 0x%x\n"
                                  "Value: %f\n\n",
                        cs->constantPool[a].type.Float.bytes,
                        u.f);
                break;
            case CLong:
                whole = (long long)cs->constantPool[a].type.Long.highBytes << 32;
                whole = whole | cs->constantPool[a].type.Long.lowBytes;
                fprintf(fileTrgt, "Type: Long\n"
                                  "High Bytes: 0x%x\n"
                                  "Low Bytes: 0x%x\n"
                                  "Value: %lu\n\n",
                        cs->constantPool[a].type.Long.highBytes,
                        cs->constantPool[a].type.Long.lowBytes,
                        whole);
                break;
            case CDouble:
                whole = (long long)cs->constantPool[a].type.Double.highBytes << 32;
                du.l = whole | cs->constantPool[a].type.Double.lowBytes;
                fprintf(fileTrgt, "Type: Double\n"
                                  "High Bytes: 0x%x\n"
                                  "Low Bytes: 0x%x\n"
                                  "Value: %f\n\n",
                        cs->constantPool[a].type.Double.highBytes,
                        cs->constantPool[a].type.Double.lowBytes,
                        du.d);
                break;
            case CClass:
                fprintf(fileTrgt, "Type: Class\n"
                                  "Name: cpInfo #%d: <%s>\n\n",
                        cs->constantPool[a].type.Class.nameIndex,
                        cs->constantPool[cs->constantPool[a].type.Class.nameIndex - 1].type.Utf8.bytes);
                break;
            case CString:
                fprintf(fileTrgt, "Type: String\n"
                                  "String: cpInfo #%d: <%s>\n\n",
                        cs->constantPool[a].type.Class.nameIndex,
                        cs->constantPool[cs->constantPool[a].type.Class.nameIndex - 1].type.Utf8.bytes);
                break;
            case CFieldRef:
                fprintf(fileTrgt, "Type: Field Reference\n"
                                  "Class: cpInfo #%d: <%s>\n"
                                  "Name and Type: cpInfo #%d: <%s%s>\n\n",
                        cs->constantPool[a].type.FieldRef.classIndex,
                        cs->constantPool[cs->constantPool[cs->constantPool[a].type.FieldRef.classIndex - 1].type.Class.nameIndex - 1].type.Utf8.bytes,
                        cs->constantPool[a].type.FieldRef.nameTypeIndex,
                        cs->constantPool[cs->constantPool[cs->constantPool[a].type.FieldRef.nameTypeIndex - 1].type.NameType.nameIndex - 1].type.Utf8.bytes,
                        cs->constantPool[cs->constantPool[cs->constantPool[a].type.FieldRef.nameTypeIndex - 1].type.NameType.descriptorIndex - 1].type.Utf8.bytes);
                break;
            case CMethodRef:
                fprintf(fileTrgt, "Type: Method Reference\n"
                                  "Class: cpInfo #%d: <%s>\n"
                                  "Name and Type: cpInfo #%d: <%s%s>\n\n",
                        cs->constantPool[a].type.MethodRef.classIndex,
                        cs->constantPool[cs->constantPool[cs->constantPool[a].type.MethodRef.classIndex - 1].type.Class.nameIndex - 1].type.Utf8.bytes,
                        cs->constantPool[a].type.MethodRef.nameTypeIndex,
                        cs->constantPool[cs->constantPool[cs->constantPool[a].type.MethodRef.nameTypeIndex - 1].type.NameType.nameIndex - 1].type.Utf8.bytes,
                        cs->constantPool[cs->constantPool[cs->constantPool[a].type.MethodRef.nameTypeIndex - 1].type.NameType.descriptorIndex - 1].type.Utf8.bytes);
                break;
            case CInterfaceMethodRef:
                fprintf(fileTrgt, "Type: Interface Method Reference\n"
                                  "Class: cpInfo #%d: <%s>\n"
                                  "Name and Type: cpInfo #%d: <%s%s>\n\n",
                        cs->constantPool[a].type.InterfaceMethodRef.classIndex,
                        cs->constantPool[cs->constantPool[cs->constantPool[a].type.InterfaceMethodRef.classIndex - 1].type.Class.nameIndex - 1].type.Utf8.bytes,
                        cs->constantPool[a].type.InterfaceMethodRef.nameTypeIndex,
                        cs->constantPool[cs->constantPool[cs->constantPool[a].type.InterfaceMethodRef.nameTypeIndex - 1].type.NameType.nameIndex - 1].type.Utf8.bytes,
                        cs->constantPool[cs->constantPool[cs->constantPool[a].type.InterfaceMethodRef.nameTypeIndex - 1].type.NameType.descriptorIndex - 1].type.Utf8.bytes);
                break;
            case CNameType:
                fprintf(fileTrgt, "Type: Name and Type\n"
                                  "Name: cpInfo #%d: <%s>\n"
                                  "Descriptor: cpInfo #%d: <%s>\n\n",
                        cs->constantPool[a].type.NameType.nameIndex,
                        cs->constantPool[cs->constantPool[a].type.NameType.nameIndex - 1].type.Utf8.bytes,
                        cs->constantPool[a].type.NameType.descriptorIndex,
                        cs->constantPool[cs->constantPool[a].type.NameType.descriptorIndex - 1].type.Utf8.bytes
                        );
                break;
            default:
                break;
        }
    }
}

/* @ brief Funcao que salva em arquivo as interfaces
 * @ param fileTrgt : arquivo de saida
 * @ param cs : estrutura de dados da classe java
 */
void saveInterfaces (FILE * fileTrgt, classStructure * cs) {
    int a;
    
    fprintf(fileTrgt, "------------------------------------------------------\n\n");
    fprintf(fileTrgt, "Interfaces: %d\n\n", cs->interfaceCount);
    
    for (a = 0; a < cs->interfaceCount; a++) {
        fprintf(fileTrgt, "Interface %d) cpInfo #%d: <%s>\n\n",
                a + 1,
                cs->interfaces[a],
                cs->constantPool[cs->constantPool[cs->interfaces[a] - 1].type.Class.nameIndex - 1].type.Utf8.bytes);
    }
}

/* @ brief Funcao que salva em arquivo os fields
 * @ param fileTrgt : arquivo de saida
 * @ param cs : estrutura de dados da classe java
 */
void saveFields (FILE * fileTrgt, classStructure * cs) {
    int a, b;
    char accessType[70];
    
    fprintf(fileTrgt, "------------------------------------------------------\n\n");
    fprintf(fileTrgt, "Fields: %d\n\n", cs->fieldCount);
    
    for (a = 0; a < cs->fieldCount; a++) {
        fprintf(fileTrgt, "Field %d)\n", a + 1);
        getAccessPerm (cs->fields[a].accessFlags, accessType);
        fprintf(fileTrgt, "Access Flags: 0x%x [%s]\n"
                          "Name: cpInfo #%d: <%s>\n"
                          "Descriptor: cpInfo #%d: <%s>\n\n"
                          "Attribute Count: %d\n\n",
                cs->fields[a].accessFlags,
                accessType,
                cs->fields[a].nameIndex,
                cs->constantPool[cs->fields[a].nameIndex - 1].type.Utf8.bytes,
                cs->fields[a].descriptorIndex,
                cs->constantPool[cs->fields[a].descriptorIndex - 1].type.Utf8.bytes,
                cs->fields[a].attributeCount);
        for (b = 0; b < cs->fields[a].attributeCount; b++) {
            saveSingleAttribute (fileTrgt, cs, &(cs->fields[a].attributes[b]), b + 1);
        }
    }
}

/* @ brief Funcao que salva em arquivo os metodos
 * @ param fileTrgt : arquivo de saida
 * @ param cs : estrutura de dados da classe java
 */
void saveMethods (FILE * fileTrgt, classStructure * cs) {
    int a, b;
    char accessType[70];
    
    fprintf(fileTrgt, "------------------------------------------------------\n\n");
    fprintf(fileTrgt, "Methods: %d\n\n", cs->methodCount);
    
    for (a = 0; a < cs->methodCount; a++) {
        fprintf(fileTrgt, "Method %d)\n", a + 1);
        getAccessPerm (cs->methods[a].accessFlags, accessType);
        fprintf(fileTrgt, "Access Flags: 0x%x [%s]\n"
                          "Name: cpInfo #%d: <%s>\n"
                          "Descriptor: cpInfo #%d: <%s>\n\n"
                          "Attribute Count: %d\n\n",
                cs->methods[a].accessFlags,
                accessType,
                cs->methods[a].nameIndex,
                cs->constantPool[cs->methods[a].nameIndex - 1].type.Utf8.bytes,
                cs->methods[a].descriptorIndex,
                cs->constantPool[cs->methods[a].descriptorIndex - 1].type.Utf8.bytes,
                cs->methods[a].attributeCount);
        for (b = 0; b < cs->methods[a].attributeCount; b++) {
            saveSingleAttribute (fileTrgt, cs, &(cs->methods[a].attributes[b]), b + 1);
        }
    }
}

/* @ brief Funcao que salva em arquivo os atributos
 * @ param fileTrgt : arquivo de saida
 * @ param cs : estrutura de dados da classe java
 */
void saveAttributes (FILE * fileTrgt, classStructure * cs) {
    int a;
    
    fprintf(fileTrgt, "------------------------------------------------------\n\n");
    fprintf(fileTrgt, "Attributes: %d\n\n", cs->attributeCount);
    
    for (a = 0; a < cs->attributeCount; a++) {
        saveSingleAttribute (fileTrgt, cs, &(cs->attributes[a]), a + 1);
    }
    
}

/* @ brief Funcao que salva em arquivo um único atibuto
 * @ param fileTrgt : arquivo de saida
 * @ param cs : estrutura de dados da classe java
 * @ param att : ponteiro para endereco do atributo a armazenar
 * @ param a : posicao do atributo
 */
void saveSingleAttribute (FILE * fileTrgt, classStructure * cs, attributeInfo * att, int a) {
    int b;
    char attType[30] = "", accessType[70];
    long long whole;
    
    fprintf(fileTrgt, "Attribute %d)\n", a);
    strcpy (attType, (char *) cs->constantPool[att->attributeNameIndex - 1].type.Utf8.bytes);
    fprintf(fileTrgt, "[Generic Info]\n"
                      "Attribute Name: cpInfo #%d: <%s>\n"
                      "Attribute Length: %d\n",
            att->attributeNameIndex,
            attType,
            att->attributeLength);
    if (strcmp (attType, "ConstantValue") == 0) {               // tipo do atributo
        fprintf(fileTrgt, "[Specific Info]\n");
        fprintf(fileTrgt, "Constant Value: cpInfo #%d",
                att->type.ConstantValue.constantValueIndex);
        switch (cs->constantPool[att->type.ConstantValue.constantValueIndex - 1].tag) {
            case CInteger:
                fprintf(fileTrgt, ": <%d>\n", cs->constantPool[att->type.ConstantValue.constantValueIndex - 1].type.Integer.bytes);
                break;
            case CFloat:
                u.i = cs->constantPool[att->type.ConstantValue.constantValueIndex - 1].type.Float.bytes;
                fprintf(fileTrgt, ": <%f>\n", u.f);
                break;
            case CLong:
                whole = (long long)cs->constantPool[att->type.ConstantValue.constantValueIndex - 1].type.Long.highBytes << 32;
                whole = whole | cs->constantPool[att->type.ConstantValue.constantValueIndex - 1].type.Long.lowBytes;
                fprintf(fileTrgt, ": <%lu>\n", whole);
                break;
            case CDouble:
                whole = (long long)cs->constantPool[att->type.ConstantValue.constantValueIndex - 1].type.Double.highBytes << 32;
                du.l = whole | cs->constantPool[att->type.ConstantValue.constantValueIndex - 1].type.Double.lowBytes;
                fprintf(fileTrgt, ": <%f>\n", du.d);
                break;
            default:
                fprintf(fileTrgt, "\n");
                break;
        }
    }
    else if (strcmp (attType, "Code") == 0) {
        fprintf(fileTrgt, "[Specific Info]\n");
        fprintf(fileTrgt, "Maximum stack depth: %d\n"
                          "Maximum local variables: %d\n"
                          "Code Length: %d\n",
                att->type.Code.maxStack,
                att->type.Code.maxLocals,
                att->type.Code.codeLength);
        if (att->type.Code.exceptionTableLength > 0) fprintf(fileTrgt, "\nException Table Length: %d\n\n", att->type.Code.exceptionTableLength);
        for (b = 0; b < att->type.Code.exceptionTableLength; b++) {
            fprintf(fileTrgt, "Code %d)\n"
                              "Start Pc: %d\n"
                              "End Pc: %d\n"
                              "Handler Pc: %d\n"
                              "Catch Type: %d\n",
                    b + 1,
                    att->type.Code.exceptionTable[b].startPc,
                    att->type.Code.exceptionTable[b].endPc,
                    att->type.Code.exceptionTable[b].handlerPc,
                    att->type.Code.exceptionTable[b].catchType);
        }
        if (att->type.Code.attributeCount > 0) {
        	fprintf (fileTrgt, "\nSub-attributes: %d\n\n", att->type.Code.attributeCount);
    		imprimir_mnemonics(att->type.Code.code , att->type.Code.codeLength, fileTrgt);	// Escreve os mnemonicos do bytecode
        }
        for (b = 0; b < att->type.Code.attributeCount; b++) {
            saveSingleAttribute (fileTrgt, cs, &(att->type.Code.attributes[b]), b + 1);
        }
        if (att->type.Code.attributeCount > 0) fprintf (fileTrgt, "\n");
    }
    else if (strcmp (attType, "Exceptions") == 0) {
        fprintf(fileTrgt, "[Specific Info]\n");
        fprintf(fileTrgt, "Number of Exceptions: %d\n\n", att->type.Exceptions.numberOfExceptions);
        for (b = 0; b < att->type.Exceptions.numberOfExceptions; b++) {
            fprintf(fileTrgt, "Exception %d)\n"
                              "Class: cpInfo #%d\n"
                              "Class Name: cpInfo #%d: <%s>\n\n",
                    b + 1,
                    att->type.Exceptions.exceptionIndexTable[b],
                    cs->constantPool[att->type.Exceptions.exceptionIndexTable[b] - 1].type.Class.nameIndex,
                    cs->constantPool[cs->constantPool[att->type.Exceptions.exceptionIndexTable[b] - 1].type.Class.nameIndex - 1].type.Utf8.bytes);
        }
    }
    else if (strcmp (attType, "InnerClasses") == 0) {
        fprintf(fileTrgt, "[Specific Info]\n");
        fprintf(fileTrgt, "Number of Classes: %d\n\n", att->type.InnerClasses.numberOfClasses);
        
        for (b = 0; b < att->type.InnerClasses.numberOfClasses; b++) {
            getAccessPerm (att->type.InnerClasses.classes[b].innerClassAccessFlags, accessType);
            fprintf(fileTrgt, "Inner Class %d)\n"
                              "Inner Class: cpInfo #%d: <%s>\n"
                              "Outer Class: cpInfo #%d: <%s>\n"
                              "Inner Name: cpInfo #%d: <%s>\n"
                              "Inner Class Access Flags: 0x%x [%s]\n",
                    b + 1,
                    att->type.InnerClasses.classes[b].innerClassInfoIndex,
                    cs->constantPool[cs->constantPool[att->type.InnerClasses.classes[b].innerClassInfoIndex - 1].type.Class.nameIndex - 1].type.Utf8.bytes,
                    att->type.InnerClasses.classes[b].outerClassInfoIndex,
                    cs->constantPool[cs->constantPool[att->type.InnerClasses.classes[b].outerClassInfoIndex - 1].type.Class.nameIndex - 1].type.Utf8.bytes,
                    att->type.InnerClasses.classes[b].innerNameIndex,
                    cs->constantPool[att->type.InnerClasses.classes[b].innerNameIndex - 1].type.Utf8.bytes,
                    att->type.InnerClasses.classes[b].innerClassAccessFlags,
                    accessType);
        }
    }
    else if (strcmp (attType, "Synthetic") == 0) {
    }
    else {
    }
    fprintf(fileTrgt, "\n");
}

void imprimir_mnemonics(u1 *bytecode, u2 size, FILE *file) {
	int i, j, linha;

	struct opcode_info opcode_tmp;

	fprintf(file, "Bytecode:\n");
	for (i = 0, linha = 1; i < size; i++, linha++) {
		opcode_tmp = op_info[bytecode[i]];
		fprintf(file, "%d    %s", linha, opcode_tmp.descricao);
		opcode_tmp.operandos_index = calloc(sizeof(u4), opcode_tmp.operandos_count);
		for (j = 0; j < opcode_tmp.operandos_count; j++) {
			opcode_tmp.operandos_index[j] = bytecode[++i];
			fprintf(file, " #%hu", opcode_tmp.operandos_index[j]);
		}
		fprintf(file, "\n");
	}
	fprintf(file, "\n");

}

void carregar_opcode_informacao() {
	int i;

	op_info = malloc(sizeof(opcode_informacao)*256);

	//TODO: colocar da tabela
	strcpy(op_info[0x00].descricao, "nop");
	strcpy(op_info[0x01].descricao, "aconst_null");
	strcpy(op_info[0x02].descricao, "iconst_m1");
	strcpy(op_info[0x03].descricao, "iconst_0");
	strcpy(op_info[0x04].descricao, "iconst_1");
	strcpy(op_info[0x05].descricao, "iconst_2");
	strcpy(op_info[0x06].descricao, "iconst_3");
	strcpy(op_info[0x07].descricao, "iconst_4");
	strcpy(op_info[0x08].descricao, "iconst_5");
	strcpy(op_info[0x09].descricao, "lconst_0");
	strcpy(op_info[0x0a].descricao, "lconst_1");
	strcpy(op_info[0x0b].descricao, "fconst_0");
	strcpy(op_info[0x0c].descricao, "fconst_1");
	strcpy(op_info[0x0d].descricao, "fconst_2");
	strcpy(op_info[0x0e].descricao, "dconst_0");
	strcpy(op_info[0x0f].descricao, "dconst_1");
	strcpy(op_info[0x10].descricao, "bipush");
	strcpy(op_info[0x11].descricao, "sipush");
	strcpy(op_info[0x12].descricao, "ldc");
	strcpy(op_info[0x13].descricao, "ldc_w");
	strcpy(op_info[0x14].descricao, "ldc2_w");
	strcpy(op_info[0x15].descricao, "iload");
	strcpy(op_info[0x16].descricao, "lload");
	strcpy(op_info[0x17].descricao, "fload");
	strcpy(op_info[0x18].descricao, "dload");
	strcpy(op_info[0x19].descricao, "aload");
	strcpy(op_info[0x1a].descricao, "iload_0");
	strcpy(op_info[0x1b].descricao, "iload_1");
	strcpy(op_info[0x1c].descricao, "iload_2");
	strcpy(op_info[0x1d].descricao, "iload_3");
	strcpy(op_info[0x1e].descricao, "lload_0");
	strcpy(op_info[0x1f].descricao, "lload_1");
	strcpy(op_info[0x20].descricao, "lload_2");
	strcpy(op_info[0x21].descricao, "lload_3");
	strcpy(op_info[0x22].descricao, "fload_0");
	strcpy(op_info[0x23].descricao, "fload_1");
	strcpy(op_info[0x24].descricao, "fload_2");
	strcpy(op_info[0x25].descricao, "fload_3");
	strcpy(op_info[0x26].descricao, "dload_0");
	strcpy(op_info[0x27].descricao, "dload_1");
	strcpy(op_info[0x28].descricao, "dload_2");
	strcpy(op_info[0x29].descricao, "dload_3");
	strcpy(op_info[0x2a].descricao, "aload_0");
	strcpy(op_info[0x2b].descricao, "aload_1");
	strcpy(op_info[0x2c].descricao, "aload_2");
	strcpy(op_info[0x2d].descricao, "aload_3");
	strcpy(op_info[0x2e].descricao, "iaload");
	strcpy(op_info[0x2f].descricao, "laload");
	strcpy(op_info[0x31].descricao, "daload");
	strcpy(op_info[0x32].descricao, "aaload");
	strcpy(op_info[0x33].descricao, "baload");
	strcpy(op_info[0x34].descricao, "caload");
	strcpy(op_info[0x35].descricao, "saload");
	strcpy(op_info[0x36].descricao, "istore");
	strcpy(op_info[0x37].descricao, "lstore");
	strcpy(op_info[0x38].descricao, "fstore");
	strcpy(op_info[0x39].descricao, "dstore");
	strcpy(op_info[0x3a].descricao, "astore");
	strcpy(op_info[0x3b].descricao, "istore_0");
	strcpy(op_info[0x3c].descricao, "istore_1");
	strcpy(op_info[0x3d].descricao, "istore_2");
	strcpy(op_info[0x3e].descricao, "istore_3");
	strcpy(op_info[0x3f].descricao, "lstore_0");
	strcpy(op_info[0x40].descricao, "lstore_1");
	strcpy(op_info[0x41].descricao, "lstore_2");
	strcpy(op_info[0x42].descricao, "lstore_3");
	strcpy(op_info[0x43].descricao, "fstore_0");
	strcpy(op_info[0x44].descricao, "fstore_1");
	strcpy(op_info[0x45].descricao, "fstore_2");
	strcpy(op_info[0x46].descricao, "fstore_3");
	strcpy(op_info[0x47].descricao, "dstore_0");
	strcpy(op_info[0x48].descricao, "dstore_1");
	strcpy(op_info[0x49].descricao, "dstore_2");
	strcpy(op_info[0x4a].descricao, "dstore_3");
	strcpy(op_info[0x4b].descricao, "astore_0");
	strcpy(op_info[0x4c].descricao, "astore_1");
	strcpy(op_info[0x4d].descricao, "astore_2");
	strcpy(op_info[0x4e].descricao, "astore_3");
	strcpy(op_info[0x4f].descricao, "iastore");
	strcpy(op_info[0x50].descricao, "lastore");
	strcpy(op_info[0x51].descricao, "fastore");
	strcpy(op_info[0x52].descricao, "dastore");
	strcpy(op_info[0x53].descricao, "aastore");
	strcpy(op_info[0x54].descricao, "bastore");
	strcpy(op_info[0x55].descricao, "castore");
	strcpy(op_info[0x56].descricao, "sastore");
	strcpy(op_info[0x60].descricao, "iadd");
	strcpy(op_info[0x61].descricao, "ladd");
	strcpy(op_info[0x62].descricao, "fadd");
	strcpy(op_info[0x63].descricao, "dadd");
	strcpy(op_info[0x64].descricao, "isub");
	strcpy(op_info[0x65].descricao, "lsub");
	strcpy(op_info[0x66].descricao, "fsub");
	strcpy(op_info[0x67].descricao, "dsub");
	strcpy(op_info[0x68].descricao, "imul");
	strcpy(op_info[0x69].descricao, "lmul");
	strcpy(op_info[0x6a].descricao, "fmul");
	strcpy(op_info[0x6b].descricao, "dmul");
	strcpy(op_info[0x6c].descricao, "idiv");
	strcpy(op_info[0x6d].descricao, "ldiv");
	strcpy(op_info[0x6e].descricao, "fdiv");
	strcpy(op_info[0x6f].descricao, "ddiv");
	strcpy(op_info[0x70].descricao, "irem");
	strcpy(op_info[0x71].descricao, "lrem");
	strcpy(op_info[0x72].descricao, "frem");
	strcpy(op_info[0x73].descricao, "drem");
	strcpy(op_info[0x74].descricao, "ineg");
	strcpy(op_info[0x75].descricao, "lneg");
	strcpy(op_info[0x76].descricao, "fneg");
	strcpy(op_info[0x77].descricao, "dneg");
	strcpy(op_info[0x78].descricao, "ishl");
	strcpy(op_info[0x79].descricao, "lshl");
	strcpy(op_info[0x7a].descricao, "ishr");
	strcpy(op_info[0x7b].descricao, "lshr");
	strcpy(op_info[0x7c].descricao, "iushr");
	strcpy(op_info[0x7d].descricao, "lushr");
	strcpy(op_info[0x7e].descricao, "iand");
	strcpy(op_info[0x7f].descricao, "land");
	strcpy(op_info[0x80].descricao, "ior");
	strcpy(op_info[0x81].descricao, "lor");
	strcpy(op_info[0x82].descricao, "ixor");
	strcpy(op_info[0x83].descricao, "lxor");
	strcpy(op_info[0x84].descricao, "iinc");
	strcpy(op_info[0x85].descricao, "i2l");
	strcpy(op_info[0x86].descricao, "i2f");
	strcpy(op_info[0x87].descricao, "i2d");
	strcpy(op_info[0x88].descricao, "l2i");
	strcpy(op_info[0x89].descricao, "l2f");
	strcpy(op_info[0x8a].descricao, "l2d");
	strcpy(op_info[0x8b].descricao, "f2i");
	strcpy(op_info[0x8c].descricao, "f2l");
	strcpy(op_info[0x8d].descricao, "f2d");
	strcpy(op_info[0x8e].descricao, "d2i");
	strcpy(op_info[0x8f].descricao, "d2l");
	strcpy(op_info[0x90].descricao, "d2f");
	strcpy(op_info[0x91].descricao, "i2b");
	strcpy(op_info[0x92].descricao, "i2c");
	strcpy(op_info[0x93].descricao, "i2s");
	strcpy(op_info[0x94].descricao, "lcmp");
	strcpy(op_info[0x95].descricao, "fcmpl");
	strcpy(op_info[0x96].descricao, "fcmpg");
	strcpy(op_info[0x97].descricao, "dcmpl");
	strcpy(op_info[0x98].descricao, "dcmpg");
	strcpy(op_info[0x99].descricao, "ifeq");
	strcpy(op_info[0x9a].descricao, "ifne");
	strcpy(op_info[0x9b].descricao, "iflt");
	strcpy(op_info[0x9c].descricao, "ifge");
	strcpy(op_info[0x9d].descricao, "ifgt");
	strcpy(op_info[0x9e].descricao, "ifle");
	strcpy(op_info[0x9f].descricao, "if_icmpeq");
	strcpy(op_info[0xa0].descricao, "if_icmpne");
	strcpy(op_info[0xa1].descricao, "if_icmplt");
	strcpy(op_info[0xa2].descricao, "if_icmpge");
	strcpy(op_info[0xa3].descricao, "if_icmpgt");
	strcpy(op_info[0xa4].descricao, "if_icmple");
	strcpy(op_info[0xa5].descricao, "if_acmpeq");
	strcpy(op_info[0xa6].descricao, "if_acmpne");
	strcpy(op_info[0xa7].descricao, "goto");
	strcpy(op_info[0xa8].descricao, "jsr");
	strcpy(op_info[0xa9].descricao, "ret");
	strcpy(op_info[0xaa].descricao, "tableswitch");
	strcpy(op_info[0xab].descricao, "lookupswitch");
	strcpy(op_info[0xac].descricao, "ireturn");
	strcpy(op_info[0xad].descricao, "lreturn");
	strcpy(op_info[0xae].descricao, "freturn");
	strcpy(op_info[0xaf].descricao, "dreturn");
	strcpy(op_info[0xb0].descricao, "areturn");
	strcpy(op_info[0xb1].descricao, "return");
	strcpy(op_info[0xb2].descricao, "getstatic");
	strcpy(op_info[0xb3].descricao, "putstatic");
	strcpy(op_info[0xb4].descricao, "getfield");
	strcpy(op_info[0xb5].descricao, "putfield");
	strcpy(op_info[0xb6].descricao, "invokevirtual");
	strcpy(op_info[0xb7].descricao, "invokespecial");
	strcpy(op_info[0xb8].descricao, "invokestatic");
	strcpy(op_info[0xb9].descricao, "invokeinterface");
	strcpy(op_info[0xbb].descricao, "new");
	strcpy(op_info[0xbc].descricao, "newarray");
	strcpy(op_info[0xbd].descricao, "anewarray");
	strcpy(op_info[0xbe].descricao, "arraylength");
	strcpy(op_info[0xc4].descricao, "wide");
	strcpy(op_info[0xc5].descricao, "multianewarray");
	strcpy(op_info[0xc6].descricao, "ifnull");
	strcpy(op_info[0xc7].descricao, "ifnonnull");
	strcpy(op_info[0xc8].descricao, "goto_w");
	strcpy(op_info[0xc9].descricao, "jsr_w");

	for(i = 0x00; i<= 0xc9; i++){
		op_info[i].operandos_count = 0;
	}

	op_info[0x10].operandos_count = 1;
	op_info[0x11].operandos_count = 2;
	op_info[0x12].operandos_count = 1;
	op_info[0x13].operandos_count = 2;
	op_info[0x14].operandos_count = 2;
	op_info[0x15].operandos_count = 1;
	op_info[0x16].operandos_count = 1;
	op_info[0x17].operandos_count = 1;
	op_info[0x18].operandos_count = 1;
	op_info[0x19].operandos_count = 1;
	op_info[0x36].operandos_count = 1;
	op_info[0x37].operandos_count = 1;
	op_info[0x38].operandos_count = 1;
	op_info[0x39].operandos_count = 1;
	op_info[0x3a].operandos_count = 1;
	op_info[0x84].operandos_count = 2;
	op_info[0x99].operandos_count = 2;
	op_info[0x9a].operandos_count = 2;
	op_info[0x9b].operandos_count = 2;
	op_info[0x9c].operandos_count = 2;
	op_info[0x9d].operandos_count = 2;
	op_info[0x9e].operandos_count = 2;
	op_info[0x9f].operandos_count = 2;
	op_info[0xa7].operandos_count = 2;
	op_info[0xa0].operandos_count = 2;
	op_info[0xa1].operandos_count = 2;
	op_info[0xa2].operandos_count = 2;
	op_info[0xa3].operandos_count = 2;
	op_info[0xa4].operandos_count = 2;
	op_info[0xa5].operandos_count = 2;
	op_info[0xa6].operandos_count = 2;
	op_info[0xa8].operandos_count = 2;
	op_info[0xa9].operandos_count = 1;
	op_info[0xaa].operandos_count = 14;
	op_info[0xab].operandos_count = 10;
	op_info[0xb2].operandos_count = 2;
	op_info[0xb4].operandos_count = 2;
	op_info[0xbd].operandos_count = 2;
	op_info[0xb9].operandos_count = 4;
	op_info[0xb7].operandos_count = 2;
	op_info[0xb8].operandos_count = 2;
	op_info[0xb6].operandos_count = 2;
	op_info[0xbc].operandos_count = 1;
	op_info[0xb5].operandos_count = 2;
	op_info[0xb3].operandos_count = 2;
	op_info[0xbb].operandos_count = 2;
	op_info[0xc8].operandos_count = 4;
	op_info[0xc7].operandos_count = 2;
	op_info[0xc6].operandos_count = 2;
	op_info[0xc9].operandos_count = 4;
	op_info[0xc5].operandos_count = 3;
	op_info[0xc4].operandos_count = 7;

}






















