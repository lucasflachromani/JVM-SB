
#include "imprimir.h"

void populate_opcode_info() {
	int i;

	op_informacao = malloc(sizeof(op_informacao)*256);

	//TODO: colocar da tabela
	strcpy(op_informacao[0x00].descricao, "nop");
	strcpy(op_informacao[0x01].descricao, "aconst_null");
	strcpy(op_informacao[0x02].descricao, "iconst_m1");
	strcpy(op_informacao[0x03].descricao, "iconst_0");
	strcpy(op_informacao[0x04].descricao, "iconst_1");
	strcpy(op_informacao[0x05].descricao, "iconst_2");
	strcpy(op_informacao[0x06].descricao, "iconst_3");
	strcpy(op_informacao[0x07].descricao, "iconst_4");
	strcpy(op_informacao[0x08].descricao, "iconst_5");
	strcpy(op_informacao[0x09].descricao, "lconst_0");
	strcpy(op_informacao[0x0a].descricao, "lconst_1");
	strcpy(op_informacao[0x0b].descricao, "fconst_0");
	strcpy(op_informacao[0x0c].descricao, "fconst_1");
	strcpy(op_informacao[0x0d].descricao, "fconst_2");
	strcpy(op_informacao[0x0e].descricao, "dconst_0");
	strcpy(op_informacao[0x0f].descricao, "dconst_1");
	strcpy(op_informacao[0x10].descricao, "bipush");
	strcpy(op_informacao[0x11].descricao, "sipush");
	strcpy(op_informacao[0x12].descricao, "ldc");
	strcpy(op_informacao[0x13].descricao, "ldc_w");
	strcpy(op_informacao[0x14].descricao, "ldc2_w");
	strcpy(op_informacao[0x15].descricao, "iload");
	strcpy(op_informacao[0x16].descricao, "lload");
	strcpy(op_informacao[0x17].descricao, "fload");
	strcpy(op_informacao[0x18].descricao, "dload");
	strcpy(op_informacao[0x19].descricao, "aload");
	strcpy(op_informacao[0x1a].descricao, "iload_0");
	strcpy(op_informacao[0x1b].descricao, "iload_1");
	strcpy(op_informacao[0x1c].descricao, "iload_2");
	strcpy(op_informacao[0x1d].descricao, "iload_3");
	strcpy(op_informacao[0x1e].descricao, "lload_0");
	strcpy(op_informacao[0x1f].descricao, "lload_1");
	strcpy(op_informacao[0x20].descricao, "lload_2");
	strcpy(op_informacao[0x21].descricao, "lload_3");
	strcpy(op_informacao[0x22].descricao, "fload_0");
	strcpy(op_informacao[0x23].descricao, "fload_1");
	strcpy(op_informacao[0x24].descricao, "fload_2");
	strcpy(op_informacao[0x25].descricao, "fload_3");
	strcpy(op_informacao[0x26].descricao, "dload_0");
	strcpy(op_informacao[0x27].descricao, "dload_1");
	strcpy(op_informacao[0x28].descricao, "dload_2");
	strcpy(op_informacao[0x29].descricao, "dload_3");
	strcpy(op_informacao[0x2a].descricao, "aload_0");
	strcpy(op_informacao[0x2b].descricao, "aload_1");
	strcpy(op_informacao[0x2c].descricao, "aload_2");
	strcpy(op_informacao[0x2d].descricao, "aload_3");
	strcpy(op_informacao[0x2e].descricao, "iaload");
	strcpy(op_informacao[0x2f].descricao, "laload");
	strcpy(op_informacao[0x31].descricao, "daload");
	strcpy(op_informacao[0x32].descricao, "aaload");
	strcpy(op_informacao[0x33].descricao, "baload");
	strcpy(op_informacao[0x34].descricao, "caload");
	strcpy(op_informacao[0x35].descricao, "saload");
	strcpy(op_informacao[0x36].descricao, "istore");
	strcpy(op_informacao[0x37].descricao, "lstore");
	strcpy(op_informacao[0x38].descricao, "fstore");
	strcpy(op_informacao[0x39].descricao, "dstore");
	strcpy(op_informacao[0x3a].descricao, "astore");
	strcpy(op_informacao[0x3b].descricao, "istore_0");
	strcpy(op_informacao[0x3c].descricao, "istore_1");
	strcpy(op_informacao[0x3d].descricao, "istore_2");
	strcpy(op_informacao[0x3e].descricao, "istore_3");
	strcpy(op_informacao[0x3f].descricao, "lstore_0");
	strcpy(op_informacao[0x40].descricao, "lstore_1");
	strcpy(op_informacao[0x41].descricao, "lstore_2");
	strcpy(op_informacao[0x42].descricao, "lstore_3");
	strcpy(op_informacao[0x43].descricao, "fstore_0");
	strcpy(op_informacao[0x44].descricao, "fstore_1");
	strcpy(op_informacao[0x45].descricao, "fstore_2");
	strcpy(op_informacao[0x46].descricao, "fstore_3");
	strcpy(op_informacao[0x47].descricao, "dstore_0");
	strcpy(op_informacao[0x48].descricao, "dstore_1");
	strcpy(op_informacao[0x49].descricao, "dstore_2");
	strcpy(op_informacao[0x4a].descricao, "dstore_3");
	strcpy(op_informacao[0x4b].descricao, "astore_0");
	strcpy(op_informacao[0x4c].descricao, "astore_1");
	strcpy(op_informacao[0x4d].descricao, "astore_2");
	strcpy(op_informacao[0x4e].descricao, "astore_3");
	strcpy(op_informacao[0x4f].descricao, "iastore");
	strcpy(op_informacao[0x50].descricao, "lastore");
	strcpy(op_informacao[0x51].descricao, "fastore");
	strcpy(op_informacao[0x52].descricao, "dastore");
	strcpy(op_informacao[0x53].descricao, "aastore");
	strcpy(op_informacao[0x54].descricao, "bastore");
	strcpy(op_informacao[0x55].descricao, "castore");
	strcpy(op_informacao[0x56].descricao, "sastore");
	strcpy(op_informacao[0x60].descricao, "iadd");
	strcpy(op_informacao[0x61].descricao, "ladd");
	strcpy(op_informacao[0x62].descricao, "fadd");
	strcpy(op_informacao[0x63].descricao, "dadd");
	strcpy(op_informacao[0x64].descricao, "isub");
	strcpy(op_informacao[0x65].descricao, "lsub");
	strcpy(op_informacao[0x66].descricao, "fsub");
	strcpy(op_informacao[0x67].descricao, "dsub");
	strcpy(op_informacao[0x68].descricao, "imul");
	strcpy(op_informacao[0x69].descricao, "lmul");
	strcpy(op_informacao[0x6a].descricao, "fmul");
	strcpy(op_informacao[0x6b].descricao, "dmul");
	strcpy(op_informacao[0x6c].descricao, "idiv");
	strcpy(op_informacao[0x6d].descricao, "ldiv");
	strcpy(op_informacao[0x6e].descricao, "fdiv");
	strcpy(op_informacao[0x6f].descricao, "ddiv");
	strcpy(op_informacao[0x70].descricao, "irem");
	strcpy(op_informacao[0x71].descricao, "lrem");
	strcpy(op_informacao[0x72].descricao, "frem");
	strcpy(op_informacao[0x73].descricao, "drem");
	strcpy(op_informacao[0x74].descricao, "ineg");
	strcpy(op_informacao[0x75].descricao, "lneg");
	strcpy(op_informacao[0x76].descricao, "fneg");
	strcpy(op_informacao[0x77].descricao, "dneg");
	strcpy(op_informacao[0x78].descricao, "ishl");
	strcpy(op_informacao[0x79].descricao, "lshl");
	strcpy(op_informacao[0x7a].descricao, "ishr");
	strcpy(op_informacao[0x7b].descricao, "lshr");
	strcpy(op_informacao[0x7c].descricao, "iushr");
	strcpy(op_informacao[0x7d].descricao, "lushr");
	strcpy(op_informacao[0x7e].descricao, "iand");
	strcpy(op_informacao[0x7f].descricao, "land");
	strcpy(op_informacao[0x80].descricao, "ior");
	strcpy(op_informacao[0x81].descricao, "lor");
	strcpy(op_informacao[0x82].descricao, "ixor");
	strcpy(op_informacao[0x83].descricao, "lxor");
	strcpy(op_informacao[0x84].descricao, "iinc");
	strcpy(op_informacao[0x85].descricao, "i2l");
	strcpy(op_informacao[0x86].descricao, "i2f");
	strcpy(op_informacao[0x87].descricao, "i2d");
	strcpy(op_informacao[0x88].descricao, "l2i");
	strcpy(op_informacao[0x89].descricao, "l2f");
	strcpy(op_informacao[0x8a].descricao, "l2d");
	strcpy(op_informacao[0x8b].descricao, "f2i");
	strcpy(op_informacao[0x8c].descricao, "f2l");
	strcpy(op_informacao[0x8d].descricao, "f2d");
	strcpy(op_informacao[0x8e].descricao, "d2i");
	strcpy(op_informacao[0x8f].descricao, "d2l");
	strcpy(op_informacao[0x90].descricao, "d2f");
	strcpy(op_informacao[0x91].descricao, "i2b");
	strcpy(op_informacao[0x92].descricao, "i2c");
	strcpy(op_informacao[0x93].descricao, "i2s");
	strcpy(op_informacao[0x94].descricao, "lcmp");
	strcpy(op_informacao[0x95].descricao, "fcmpl");
	strcpy(op_informacao[0x96].descricao, "fcmpg");
	strcpy(op_informacao[0x97].descricao, "dcmpl");
	strcpy(op_informacao[0x98].descricao, "dcmpg");
	strcpy(op_informacao[0x99].descricao, "ifeq");
	strcpy(op_informacao[0x9a].descricao, "ifne");
	strcpy(op_informacao[0x9b].descricao, "iflt");
	strcpy(op_informacao[0x9c].descricao, "ifge");
	strcpy(op_informacao[0x9d].descricao, "ifgt");
	strcpy(op_informacao[0x9e].descricao, "ifle");
	strcpy(op_informacao[0x9f].descricao, "if_icmpeq");
	strcpy(op_informacao[0xa0].descricao, "if_icmpne");
	strcpy(op_informacao[0xa1].descricao, "if_icmplt");
	strcpy(op_informacao[0xa2].descricao, "if_icmpge");
	strcpy(op_informacao[0xa3].descricao, "if_icmpgt");
	strcpy(op_informacao[0xa4].descricao, "if_icmple");
	strcpy(op_informacao[0xa5].descricao, "if_acmpeq");
	strcpy(op_informacao[0xa6].descricao, "if_acmpne");
	strcpy(op_informacao[0xa7].descricao, "goto");
	strcpy(op_informacao[0xa8].descricao, "jsr");
	strcpy(op_informacao[0xa9].descricao, "ret");
	strcpy(op_informacao[0xaa].descricao, "tableswitch");
	strcpy(op_informacao[0xab].descricao, "lookupswitch");
	strcpy(op_informacao[0xac].descricao, "ireturn");
	strcpy(op_informacao[0xad].descricao, "lreturn");
	strcpy(op_informacao[0xae].descricao, "freturn");
	strcpy(op_informacao[0xaf].descricao, "dreturn");
	strcpy(op_informacao[0xb0].descricao, "areturn");
	strcpy(op_informacao[0xb1].descricao, "return");
	strcpy(op_informacao[0xb2].descricao, "getstatic");
	strcpy(op_informacao[0xb3].descricao, "putstatic");
	strcpy(op_informacao[0xb4].descricao, "getfield");
	strcpy(op_informacao[0xb5].descricao, "putfield");
	strcpy(op_informacao[0xb6].descricao, "invokevirtual");
	strcpy(op_informacao[0xb7].descricao, "invokespecial");
	strcpy(op_informacao[0xb8].descricao, "invokestatic");
	strcpy(op_informacao[0xb9].descricao, "invokeinterface");
	strcpy(op_informacao[0xbb].descricao, "new");
	strcpy(op_informacao[0xbc].descricao, "newarray");
	strcpy(op_informacao[0xbd].descricao, "anewarray");
	strcpy(op_informacao[0xbe].descricao, "arraylength");
	strcpy(op_informacao[0xc4].descricao, "wide");
	strcpy(op_informacao[0xc5].descricao, "multianewarray");
	strcpy(op_informacao[0xc6].descricao, "ifnull");
	strcpy(op_informacao[0xc7].descricao, "ifnonnull");
	strcpy(op_informacao[0xc8].descricao, "goto_w");
	strcpy(op_informacao[0xc9].descricao, "jsr_w");
	
	for(i = 0x00; i<= 0xc9; i++){

		op_informacao[i].operandos_count = 0;

	}
	
	
	

	op_informacao[0x19].operandos_count = 1;
	op_informacao[0xbd].operandos_count = 2;
	op_informacao[0x3a].operandos_count = 1;
	op_informacao[0x10].operandos_count = 1;
	op_informacao[0x18].operandos_count = 1;
	op_informacao[0x39].operandos_count = 1;
	op_informacao[0x17].operandos_count = 1;
	op_informacao[0x38].operandos_count = 1;
	op_informacao[0xb4].operandos_count = 2;
	op_informacao[0xb2].operandos_count = 2;
	op_informacao[0xa7].operandos_count = 2;
	op_informacao[0xc8].operandos_count = 4;
	op_informacao[0xa5].operandos_count = 2;
	op_informacao[0xa6].operandos_count = 2;
	op_informacao[0x9f].operandos_count = 2;
	op_informacao[0xa0].operandos_count = 2;
	op_informacao[0xa1].operandos_count = 2;
	op_informacao[0xa2].operandos_count = 2;
	op_informacao[0xa3].operandos_count = 2;
	op_informacao[0xa4].operandos_count = 2;
	op_informacao[0x99].operandos_count = 2;
	op_informacao[0x9a].operandos_count = 2;
	op_informacao[0x9b].operandos_count = 2;
	op_informacao[0x9c].operandos_count = 2;
	op_informacao[0x9d].operandos_count = 2;
	op_informacao[0x9e].operandos_count = 2;
	op_informacao[0xc7].operandos_count = 2;
	op_informacao[0xc6].operandos_count = 2;
	op_informacao[0x84].operandos_count = 2;
	op_informacao[0x15].operandos_count = 1;
	op_informacao[0xb9].operandos_count = 4;
	op_informacao[0xb7].operandos_count = 2;
	op_informacao[0xb8].operandos_count = 2;
	op_informacao[0xb6].operandos_count = 2;
	op_informacao[0x36].operandos_count = 1;
	op_informacao[0xa8].operandos_count = 2;
	op_informacao[0xc9].operandos_count = 4;
	op_informacao[0x12].operandos_count = 1;
	op_informacao[0x13].operandos_count = 2;
	op_informacao[0x14].operandos_count = 2;
	op_informacao[0x16].operandos_count = 1;
	op_informacao[0xab].operandos_count = 10; /*TODO Ver se realmente sÃ£o 10 operandos */
	op_informacao[0x37].operandos_count = 1;
	op_informacao[0xc5].operandos_count = 3;
	op_informacao[0xbb].operandos_count = 2;
	op_informacao[0xbc].operandos_count = 1;
	op_informacao[0xb5].operandos_count = 2;
	op_informacao[0xb3].operandos_count = 2;
	op_informacao[0xa9].operandos_count = 1;
	op_informacao[0x11].operandos_count = 2;
	op_informacao[0xaa].operandos_count = 14; /*TODO Ver se realmente sÃ£o 14 operandos */
	op_informacao[0xc4].operandos_count = 7;  /*TODO Ver se realmente sÃ£o 7 operandos */
	
	//TODO: Colocar as outras instruções desse for, pra n ter for
	for (i = 0xcb; i < 0xfe; i++) {
	  op_informacao[i].operandos_count = 0;
	}

}



