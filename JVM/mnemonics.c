#include "mnemonics.h"

void populate_opcode_info() {
	int i;

	op_info = malloc(sizeof(opcode_info)*256);

	strcpy(op_info[0x32].desc, "aaload");
	strcpy(op_info[0x53].desc, "aastore");
	strcpy(op_info[0x01].desc, "aconst_null");
	strcpy(op_info[0x19].desc, "aload");
	strcpy(op_info[0x2a].desc, "aload_0");
	strcpy(op_info[0x2b].desc, "aload_1");
	strcpy(op_info[0x2c].desc, "aload_2");
	strcpy(op_info[0x2d].desc, "aload_3");
	strcpy(op_info[0xbd].desc, "anewarray");
	strcpy(op_info[0xb0].desc, "areturn");
	strcpy(op_info[0xbe].desc, "arraylength");
	strcpy(op_info[0x3a].desc, "astore");
	strcpy(op_info[0x4b].desc, "astore_0");
	strcpy(op_info[0x4c].desc, "astore_1");
	strcpy(op_info[0x4d].desc, "astore_2");
	strcpy(op_info[0x4e].desc, "astore_3");
	strcpy(op_info[0xbf].desc, "athrow");
	strcpy(op_info[0x33].desc, "baload");
	strcpy(op_info[0x54].desc, "bastore");
	strcpy(op_info[0x10].desc, "bipush");
	strcpy(op_info[0x34].desc, "caload");
	strcpy(op_info[0x55].desc, "castore");
	strcpy(op_info[0xc0].desc, "checkcast");
	strcpy(op_info[0x90].desc, "d2f");
	strcpy(op_info[0x8e].desc, "d2i");
	strcpy(op_info[0x8f].desc, "d2l");
	strcpy(op_info[0x63].desc, "dadd");
	strcpy(op_info[0x31].desc, "daload");
	strcpy(op_info[0x52].desc, "dastore");
	strcpy(op_info[0x98].desc, "dcmpg");
	strcpy(op_info[0x97].desc, "dcmpl");
	strcpy(op_info[0x0e].desc, "dconst_0");
	strcpy(op_info[0x0f].desc, "dconst_1");
	strcpy(op_info[0x6f].desc, "ddiv");
	strcpy(op_info[0x18].desc, "dload");
	strcpy(op_info[0x26].desc, "dload_0");
	strcpy(op_info[0x27].desc, "dload_1");
	strcpy(op_info[0x28].desc, "dload_2");
	strcpy(op_info[0x29].desc, "dload_3");
	strcpy(op_info[0x6b].desc, "dmul");
	strcpy(op_info[0x77].desc, "dneg");
	strcpy(op_info[0x73].desc, "drem");
	strcpy(op_info[0xaf].desc, "dreturn");
	strcpy(op_info[0x39].desc, "dstore");
	strcpy(op_info[0x47].desc, "dstore_0");
	strcpy(op_info[0x48].desc, "dstore_1");
	strcpy(op_info[0x49].desc, "dstore_2");
	strcpy(op_info[0x4a].desc, "dstore_3");
	strcpy(op_info[0x67].desc, "dsub");
	strcpy(op_info[0x59].desc, "dup");
	strcpy(op_info[0x5a].desc, "dup_x1");
	strcpy(op_info[0x5b].desc, "dup_x2");
	strcpy(op_info[0x5c].desc, "dup2");
	strcpy(op_info[0x5d].desc, "dup2_x1");
	strcpy(op_info[0x5e].desc, "dup2_x2");
	strcpy(op_info[0x8d].desc, "f2d");
	strcpy(op_info[0x8b].desc, "f2i");
	strcpy(op_info[0x8c].desc, "f2l");
	strcpy(op_info[0x62].desc, "fadd");
	strcpy(op_info[0x30].desc, "faload");
	strcpy(op_info[0x51].desc, "fastore");
	strcpy(op_info[0x96].desc, "fcmpg");
	strcpy(op_info[0x95].desc, "fcmpl");
	strcpy(op_info[0x0b].desc, "fconst_0");
	strcpy(op_info[0x0c].desc, "fconst_1");
	strcpy(op_info[0x0d].desc, "fconst_2");
	strcpy(op_info[0x6e].desc, "fdiv");
	strcpy(op_info[0x17].desc, "fload");
	strcpy(op_info[0x22].desc, "fload_0");
	strcpy(op_info[0x23].desc, "fload_1");
	strcpy(op_info[0x24].desc, "fload_2");
	strcpy(op_info[0x25].desc, "fload_3");
	strcpy(op_info[0x6a].desc, "fmul");
	strcpy(op_info[0x76].desc, "fneg");
	strcpy(op_info[0x72].desc, "frem");
	strcpy(op_info[0xae].desc, "freturn");
	strcpy(op_info[0x38].desc, "fstore");
	strcpy(op_info[0x43].desc, "fstore_0");
	strcpy(op_info[0x44].desc, "fstore_1");
	strcpy(op_info[0x45].desc, "fstore_2");
	strcpy(op_info[0x46].desc, "fstore_3");
	strcpy(op_info[0x66].desc, "fsub");
	strcpy(op_info[0xb4].desc, "getfield");
	strcpy(op_info[0xb2].desc, "getstatic");
	strcpy(op_info[0xa7].desc, "goto");
	strcpy(op_info[0xc8].desc, "goto_w");
	strcpy(op_info[0x91].desc, "i2b");
	strcpy(op_info[0x92].desc, "i2c");
	strcpy(op_info[0x87].desc, "i2d");
	strcpy(op_info[0x86].desc, "i2f");
	strcpy(op_info[0x85].desc, "i2l");
	strcpy(op_info[0x93].desc, "i2s");
	strcpy(op_info[0x60].desc, "iadd");
	strcpy(op_info[0x2e].desc, "iaload");
	strcpy(op_info[0x7e].desc, "iand");
	strcpy(op_info[0x4f].desc, "iastore");
	strcpy(op_info[0x02].desc, "iconst_m1");
	strcpy(op_info[0x03].desc, "iconst_0");
	strcpy(op_info[0x04].desc, "iconst_1");
	strcpy(op_info[0x05].desc, "iconst_2");
	strcpy(op_info[0x06].desc, "iconst_3");
	strcpy(op_info[0x07].desc, "iconst_4");
	strcpy(op_info[0x08].desc, "iconst_5");
	strcpy(op_info[0x6c].desc, "idiv");
	strcpy(op_info[0xa5].desc, "if_acmpeq");
	strcpy(op_info[0xa6].desc, "if_acmpne");
	strcpy(op_info[0x9f].desc, "if_icmpeq");
	strcpy(op_info[0xa0].desc, "if_icmpne");
	strcpy(op_info[0xa1].desc, "if_icmplt");
	strcpy(op_info[0xa2].desc, "if_icmpge");
	strcpy(op_info[0xa3].desc, "if_icmpgt");
	strcpy(op_info[0xa4].desc, "if_icmple");
	strcpy(op_info[0x99].desc, "ifeq");
	strcpy(op_info[0x9a].desc, "ifne");
	strcpy(op_info[0x9b].desc, "iflt");
	strcpy(op_info[0x9c].desc, "ifge");
	strcpy(op_info[0x9d].desc, "ifgt");
	strcpy(op_info[0x9e].desc, "ifle");
	strcpy(op_info[0xc7].desc, "ifnonnull");
	strcpy(op_info[0xc6].desc, "ifnull");
	strcpy(op_info[0x84].desc, "iinc");
	strcpy(op_info[0x15].desc, "iload");
	strcpy(op_info[0x1a].desc, "iload_0");
	strcpy(op_info[0x1b].desc, "iload_1");
	strcpy(op_info[0x1c].desc, "iload_2");
	strcpy(op_info[0x1d].desc, "iload_3");
	strcpy(op_info[0x68].desc, "imul");
	strcpy(op_info[0x74].desc, "ineg");
	strcpy(op_info[0xc1].desc, "instanceof");
	strcpy(op_info[0xb9].desc, "invokeinterface");
	strcpy(op_info[0xb7].desc, "invokespecial");
	strcpy(op_info[0xb8].desc, "invokestatic");
	strcpy(op_info[0xb6].desc, "invokevirtual");
	strcpy(op_info[0x80].desc, "ior");
	strcpy(op_info[0x70].desc, "irem");
	strcpy(op_info[0xac].desc, "ireturn");
	strcpy(op_info[0x78].desc, "ishl");
	strcpy(op_info[0x7a].desc, "ishr");
	strcpy(op_info[0x36].desc, "istore");
	strcpy(op_info[0x3b].desc, "istore_0");
	strcpy(op_info[0x3c].desc, "istore_1");
	strcpy(op_info[0x3d].desc, "istore_2");
	strcpy(op_info[0x3e].desc, "istore_3");
	strcpy(op_info[0x64].desc, "isub");
	strcpy(op_info[0x7c].desc, "iushr");
	strcpy(op_info[0x82].desc, "ixor");
	strcpy(op_info[0xa8].desc, "jsr");
	strcpy(op_info[0xc9].desc, "jsr_w");
	strcpy(op_info[0x8a].desc, "l2d");
	strcpy(op_info[0x89].desc, "l2f");
	strcpy(op_info[0x88].desc, "l2i");
	strcpy(op_info[0x61].desc, "ladd");
	strcpy(op_info[0x2f].desc, "laload");
	strcpy(op_info[0x7f].desc, "land");
	strcpy(op_info[0x50].desc, "lastore");
	strcpy(op_info[0x94].desc, "lcmp");
	strcpy(op_info[0x09].desc, "lconst_0");
	strcpy(op_info[0x0a].desc, "lconst_1");
	strcpy(op_info[0x12].desc, "ldc");
	strcpy(op_info[0x13].desc, "ldc_w");
	strcpy(op_info[0x14].desc, "ldc2_w");
	strcpy(op_info[0x6d].desc, "ldiv");
	strcpy(op_info[0x16].desc, "lload");
	strcpy(op_info[0x1e].desc, "lload_0");
	strcpy(op_info[0x1f].desc, "lload_1");
	strcpy(op_info[0x20].desc, "lload_2");
	strcpy(op_info[0x21].desc, "lload_3");
	strcpy(op_info[0x69].desc, "lmul");
	strcpy(op_info[0x75].desc, "lneg");
	strcpy(op_info[0xab].desc, "lookupswitch");
	strcpy(op_info[0x81].desc, "lor");
	strcpy(op_info[0x71].desc, "lrem");
	strcpy(op_info[0xad].desc, "lreturn");
	strcpy(op_info[0x79].desc, "lshl");
	strcpy(op_info[0x7b].desc, "lshr");
	strcpy(op_info[0x37].desc, "lstore");
	strcpy(op_info[0x3f].desc, "lstore_0");
	strcpy(op_info[0x40].desc, "lstore_1");
	strcpy(op_info[0x41].desc, "lstore_2");
	strcpy(op_info[0x42].desc, "lstore_3");
	strcpy(op_info[0x65].desc, "lsub");
	strcpy(op_info[0x7d].desc, "lushr");
	strcpy(op_info[0x83].desc, "lxor");
	strcpy(op_info[0xc2].desc, "monitorenter");
	strcpy(op_info[0xc3].desc, "monitorexit");
	strcpy(op_info[0xc5].desc, "multianewarray");
	strcpy(op_info[0xbb].desc, "new");
	strcpy(op_info[0xbc].desc, "newarray");
	strcpy(op_info[0x00].desc, "nop");
	strcpy(op_info[0x57].desc, "pop");
	strcpy(op_info[0x58].desc, "pop2");
	strcpy(op_info[0xb5].desc, "putfield");
	strcpy(op_info[0xb3].desc, "putstatic");
	strcpy(op_info[0xa9].desc, "ret");
	strcpy(op_info[0xb1].desc, "return");
	strcpy(op_info[0x35].desc, "saload");
	strcpy(op_info[0x56].desc, "sastore");
	strcpy(op_info[0x11].desc, "sipush");
	strcpy(op_info[0x5f].desc, "swap");
	strcpy(op_info[0xaa].desc, "tableswitch");
	strcpy(op_info[0xc4].desc, "wide");
	strcpy(op_info[0xca].desc, "breakpoint");
	strcpy(op_info[0xfe].desc, "impdep1");
	strcpy(op_info[0xff].desc, "impdep2");
	strcpy(op_info[0xba].desc, "xxxunusedxxx");

	for (i = 0xcb; i < 0xfe; i++) {
		strcpy(op_info[i].desc, "(no name)");
	}


	op_info[0x32].operands_count = 0;
	op_info[0x53].operands_count = 0;
	op_info[0x01].operands_count = 0;
	op_info[0x19].operands_count = 1;
	op_info[0x2a].operands_count = 0;
	op_info[0x2b].operands_count = 0;
	op_info[0x2c].operands_count = 0;
	op_info[0x2d].operands_count = 0;
	op_info[0xbd].operands_count = 2;
	op_info[0xb0].operands_count = 0;
	op_info[0xbe].operands_count = 0;
	op_info[0x3a].operands_count = 1;
	op_info[0x4b].operands_count = 0;
	op_info[0x4c].operands_count = 0;
	op_info[0x4d].operands_count = 0;
	op_info[0x4e].operands_count = 0;
	op_info[0xbf].operands_count = 0;
	op_info[0x33].operands_count = 0;
	op_info[0x54].operands_count = 0;
	op_info[0x10].operands_count = 1;
	op_info[0x34].operands_count = 0;
	op_info[0x55].operands_count = 0;
	op_info[0xc0].operands_count = 2;
	op_info[0x90].operands_count = 0;
	op_info[0x8e].operands_count = 0;
	op_info[0x8f].operands_count = 0;
	op_info[0x63].operands_count = 0;
	op_info[0x31].operands_count = 0;
	op_info[0x52].operands_count = 0;
	op_info[0x98].operands_count = 0;
	op_info[0x97].operands_count = 0;
	op_info[0x0e].operands_count = 0;
	op_info[0x0f].operands_count = 0;
	op_info[0x6f].operands_count = 0;
	op_info[0x18].operands_count = 1;
	op_info[0x26].operands_count = 0;
	op_info[0x27].operands_count = 0;
	op_info[0x28].operands_count = 0;
	op_info[0x29].operands_count = 0;
	op_info[0x6b].operands_count = 0;
	op_info[0x77].operands_count = 0;
	op_info[0x73].operands_count = 0;
	op_info[0xaf].operands_count = 0;
	op_info[0x39].operands_count = 1;
	op_info[0x47].operands_count = 0;
	op_info[0x48].operands_count = 0;
	op_info[0x49].operands_count = 0;
	op_info[0x4a].operands_count = 0;
	op_info[0x67].operands_count = 0;
	op_info[0x59].operands_count = 0;
	op_info[0x5a].operands_count = 0;
	op_info[0x5b].operands_count = 0;
	op_info[0x5c].operands_count = 0;
	op_info[0x5d].operands_count = 0;
	op_info[0x5e].operands_count = 0;
	op_info[0x8d].operands_count = 0;
	op_info[0x8b].operands_count = 0;
	op_info[0x8c].operands_count = 0;
	op_info[0x62].operands_count = 0;
	op_info[0x30].operands_count = 0;
	op_info[0x51].operands_count = 0;
	op_info[0x96].operands_count = 0;
	op_info[0x95].operands_count = 0;
	op_info[0x0b].operands_count = 0;
	op_info[0x0c].operands_count = 0;
	op_info[0x0d].operands_count = 0;
	op_info[0x6e].operands_count = 0;
	op_info[0x17].operands_count = 1;
	op_info[0x22].operands_count = 0;
	op_info[0x23].operands_count = 0;
	op_info[0x24].operands_count = 0;
	op_info[0x25].operands_count = 0;
	op_info[0x6a].operands_count = 0;
	op_info[0x76].operands_count = 0;
	op_info[0x72].operands_count = 0;
	op_info[0xae].operands_count = 0;
	op_info[0x38].operands_count = 1;
	op_info[0x43].operands_count = 0;
	op_info[0x44].operands_count = 0;
	op_info[0x45].operands_count = 0;
	op_info[0x46].operands_count = 0;
	op_info[0x66].operands_count = 0;
	op_info[0xb4].operands_count = 2;
	op_info[0xb2].operands_count = 2;
	op_info[0xa7].operands_count = 2;
	op_info[0xc8].operands_count = 4;
	op_info[0x91].operands_count = 0;
	op_info[0x92].operands_count = 0;
	op_info[0x87].operands_count = 0;
	op_info[0x86].operands_count = 0;
	op_info[0x85].operands_count = 0;
	op_info[0x93].operands_count = 0;
	op_info[0x60].operands_count = 0;
	op_info[0x2e].operands_count = 0;
	op_info[0x7e].operands_count = 0;
	op_info[0x4f].operands_count = 0;
	op_info[0x02].operands_count = 0;
	op_info[0x03].operands_count = 0;
	op_info[0x04].operands_count = 0;
	op_info[0x05].operands_count = 0;
	op_info[0x06].operands_count = 0;
	op_info[0x07].operands_count = 0;
	op_info[0x08].operands_count = 0;
	op_info[0x6c].operands_count = 0;
	op_info[0xa5].operands_count = 2;
	op_info[0xa6].operands_count = 2;
	op_info[0x9f].operands_count = 2;
	op_info[0xa0].operands_count = 2;
	op_info[0xa1].operands_count = 2;
	op_info[0xa2].operands_count = 2;
	op_info[0xa3].operands_count = 2;
	op_info[0xa4].operands_count = 2;
	op_info[0x99].operands_count = 2;
	op_info[0x9a].operands_count = 2;
	op_info[0x9b].operands_count = 2;
	op_info[0x9c].operands_count = 2;
	op_info[0x9d].operands_count = 2;
	op_info[0x9e].operands_count = 2;
	op_info[0xc7].operands_count = 2;
	op_info[0xc6].operands_count = 2;
	op_info[0x84].operands_count = 2;
	op_info[0x15].operands_count = 1;
	op_info[0x1a].operands_count = 0;
	op_info[0x1b].operands_count = 0;
	op_info[0x1c].operands_count = 0;
	op_info[0x1d].operands_count = 0;
	op_info[0x68].operands_count = 0;
	op_info[0x74].operands_count = 0;
	op_info[0xc1].operands_count = 2;
	op_info[0xb9].operands_count = 4;
	op_info[0xb7].operands_count = 2;
	op_info[0xb8].operands_count = 2;
	op_info[0xb6].operands_count = 2;
	op_info[0x80].operands_count = 0;
	op_info[0x70].operands_count = 0;
	op_info[0xac].operands_count = 0;
	op_info[0x78].operands_count = 0;
	op_info[0x7a].operands_count = 0;
	op_info[0x36].operands_count = 1;
	op_info[0x3b].operands_count = 0;
	op_info[0x3c].operands_count = 0;
	op_info[0x3d].operands_count = 0;
	op_info[0x3e].operands_count = 0;
	op_info[0x64].operands_count = 0;
	op_info[0x7c].operands_count = 0;
	op_info[0x82].operands_count = 0;
	op_info[0xa8].operands_count = 2;
	op_info[0xc9].operands_count = 4;
	op_info[0x8a].operands_count = 0;
	op_info[0x89].operands_count = 0;
	op_info[0x88].operands_count = 0;
	op_info[0x61].operands_count = 0;
	op_info[0x2f].operands_count = 0;
	op_info[0x7f].operands_count = 0;
	op_info[0x50].operands_count = 0;
	op_info[0x94].operands_count = 0;
	op_info[0x09].operands_count = 0;
	op_info[0x0a].operands_count = 0;
	op_info[0x12].operands_count = 1;
	op_info[0x13].operands_count = 2;
	op_info[0x14].operands_count = 2;
	op_info[0x6d].operands_count = 0;
	op_info[0x16].operands_count = 1;
	op_info[0x1e].operands_count = 0;
	op_info[0x1f].operands_count = 0;
	op_info[0x20].operands_count = 0;
	op_info[0x21].operands_count = 0;
	op_info[0x69].operands_count = 0;
	op_info[0x75].operands_count = 0;
	op_info[0xab].operands_count = 10; /*TODO Ver se realmente são 10 operandos */
	op_info[0x81].operands_count = 0;
	op_info[0x71].operands_count = 0;
	op_info[0xad].operands_count = 0;
	op_info[0x79].operands_count = 0;
	op_info[0x7b].operands_count = 0;
	op_info[0x37].operands_count = 1;
	op_info[0x3f].operands_count = 0;
	op_info[0x40].operands_count = 0;
	op_info[0x41].operands_count = 0;
	op_info[0x42].operands_count = 0;
	op_info[0x65].operands_count = 0;
	op_info[0x7d].operands_count = 0;
	op_info[0x83].operands_count = 0;
	op_info[0xc2].operands_count = 0;
	op_info[0xc3].operands_count = 0;
	op_info[0xc5].operands_count = 3;
	op_info[0xbb].operands_count = 2;
	op_info[0xbc].operands_count = 1;
	op_info[0x00].operands_count = 0;
	op_info[0x57].operands_count = 0;
	op_info[0x58].operands_count = 0;
	op_info[0xb5].operands_count = 2;
	op_info[0xb3].operands_count = 2;
	op_info[0xa9].operands_count = 1;
	op_info[0xb1].operands_count = 0;
	op_info[0x35].operands_count = 0;
	op_info[0x56].operands_count = 0;
	op_info[0x11].operands_count = 2;
	op_info[0x5f].operands_count = 0;
	op_info[0xaa].operands_count = 14; /*TODO Ver se realmente são 14 operandos */
	op_info[0xc4].operands_count = 7;  /*TODO Ver se realmente são 7 operandos */
	op_info[0xca].operands_count = 0;
	op_info[0xfe].operands_count = 0;
	op_info[0xff].operands_count = 0;
	op_info[0xba].operands_count = 0;

	for (i = 0xcb; i < 0xfe; i++) {
	  op_info[i].operands_count = 0;
	}
}
