#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>

#include "instructions.h"

#include "constantes.h"
#include "mnemonics.h"
#include "stack.h"
#include "frame.h"
#include "types.h"
#include "methods.h"
#include "heap.h"

extern struct frame *frameAtual;
extern struct array *arrayLength;
extern u4 numArrays;

/* Variaveis usadas para saber qual o retorno da funcao */
extern u1 returnType;
extern u8 returnValue;

int next_is_wide = 0;

extern opcode_info *op_info;


void execute_instruction(u1 opcode) {
	instr[opcode]();
}

void  iniciarInstrucoes() {
	instr[0x00] = funct_nop;
	instr[0x01] = funct_aconst_null;
	instr[0x02] = funct_iconst_m1;
	instr[0x03] = funct_iconst_0;
	instr[0x04] = funct_iconst_1;
	instr[0x05] = funct_iconst_2;
	instr[0x06] = funct_iconst_3;
	instr[0x07] = funct_iconst_4;
	instr[0x08] = funct_iconst_5;
	instr[0x09] = funct_lconst_0;
	instr[0x0a] = funct_lconst_1;
	instr[0x0b] = funct_fconst_0;
	instr[0x0c] = funct_fconst_1;
	instr[0x0d] = funct_fconst_2;
	instr[0x0e] = funct_dconst_0;
	instr[0x0f] = funct_dconst_1;
	instr[0x10] = funct_bipush;
	instr[0x11] = funct_sipush;
	instr[0x12] = funct_ldc;
	instr[0x13] = funct_ldc_w;
	instr[0x14] = funct_ldc2_w;
	instr[0x15] = funct_iload;
	instr[0x16] = funct_lload;
	instr[0x17] = funct_fload;
	instr[0x18] = funct_dload;
	instr[0x19] = funct_aload;
	instr[0x1a] = funct_iload_0;
	instr[0x1b] = funct_iload_1;
	instr[0x1c] = funct_iload_2;
	instr[0x1d] = funct_iload_3;
	instr[0x1e] = funct_lload_0;
	instr[0x1f] = funct_lload_1;
	instr[0x20] = funct_lload_2;
	instr[0x21] = funct_lload_3;
	instr[0x22] = funct_fload_0;
	instr[0x23] = funct_fload_1;
	instr[0x24] = funct_fload_2;
	instr[0x25] = funct_fload_3;
	instr[0x26] = funct_dload_0;
	instr[0x27] = funct_dload_1;
	instr[0x28] = funct_dload_2;
	instr[0x29] = funct_dload_3;
	instr[0x2a] = funct_aload_0;
	instr[0x2b] = funct_aload_1;
	instr[0x2c] = funct_aload_2;
	instr[0x2d] = funct_aload_3;
	instr[0x2e] = funct_iaload;
	instr[0x2f] = funct_laload;
	instr[0x30] = funct_faload;
	instr[0x31] = funct_daload;
	instr[0x32] = funct_aaload;
	instr[0x33] = funct_baload;
	instr[0x34] = funct_caload;
	instr[0x35] = funct_saload;
	instr[0x36] = funct_istore;
	instr[0x37] = funct_lstore;
	instr[0x38] = funct_fstore;
	instr[0x39] = funct_dstore;
	instr[0x3a] = funct_astore;
	instr[0x3b] = funct_istore_0;
	instr[0x3c] = funct_istore_1;
	instr[0x3d] = funct_istore_2;
	instr[0x3e] = funct_istore_3;
	instr[0x3f] = funct_lstore_0;
	instr[0x40] = funct_lstore_1;
	instr[0x41] = funct_lstore_2;
	instr[0x42] = funct_lstore_3;
	instr[0x43] = funct_fstore_0;
	instr[0x44] = funct_fstore_1;
	instr[0x45] = funct_fstore_2;
	instr[0x46] = funct_fstore_3;
	instr[0x47] = funct_dstore_0;
	instr[0x48] = funct_dstore_1;
	instr[0x49] = funct_dstore_2;
	instr[0x4a] = funct_dstore_3;
	instr[0x4b] = funct_astore_0;
	instr[0x4c] = funct_astore_1;
	instr[0x4d] = funct_astore_2;
	instr[0x4e] = funct_astore_3;
	instr[0x4f] = funct_iastore;
	instr[0x50] = funct_lastore;
	instr[0x51] = funct_fastore;
	instr[0x52] = funct_dastore;
	instr[0x53] = funct_aastore;
	instr[0x54] = funct_bastore;
	instr[0x55] = funct_castore;
	instr[0x56] = funct_sastore;
	instr[0x60] = funct_iadd;
	instr[0x61] = funct_ladd;
	instr[0x62] = funct_fadd;
	instr[0x63] = funct_dadd;
	instr[0x64] = funct_isub;
	instr[0x65] = funct_lsub;
	instr[0x66] = funct_fsub;
	instr[0x67] = funct_dsub;
	instr[0x68] = funct_imul;
	instr[0x69] = funct_lmul;
	instr[0x6a] = funct_fmul;
	instr[0x6b] = funct_dmul;
	instr[0x6c] = funct_idiv;
	instr[0x6d] = funct_ldiv;
	instr[0x6e] = funct_fdiv;
	instr[0x6f] = funct_ddiv;
	instr[0x70] = funct_irem;
	instr[0x71] = funct_lrem;
	instr[0x72] = funct_frem;
	instr[0x73] = funct_drem;
	instr[0x74] = funct_ineg;
	instr[0x75] = funct_lneg;
	instr[0x76] = funct_fneg;
	instr[0x77] = funct_dneg;
	instr[0x78] = funct_ishl;
	instr[0x79] = funct_lshl;
	instr[0x7a] = funct_ishr;
	instr[0x7b] = funct_lshr;
	instr[0x7c] = funct_iushr;
	instr[0x7d] = funct_lushr;
	instr[0x7e] = funct_iand;
	instr[0x7f] = funct_land;
	instr[0x80] = funct_ior;
	instr[0x81] = funct_lor;
	instr[0x82] = funct_ixor;
	instr[0x83] = funct_lxor;
	instr[0x84] = funct_iinc;
	instr[0x85] = funct_i2l;
	instr[0x86] = funct_i2f;
	instr[0x87] = funct_i2d;
	instr[0x88] = funct_l2i;
	instr[0x89] = funct_l2f;
	instr[0x8a] = funct_l2d;
	instr[0x8b] = funct_f2i;
	instr[0x8c] = funct_f2l;
	instr[0x8d] = funct_f2d;
	instr[0x8e] = funct_d2i;
	instr[0x8f] = funct_d2l;
	instr[0x90] = funct_d2f;
	instr[0x91] = funct_i2b;
	instr[0x92] = funct_i2c;
	instr[0x93] = funct_i2s;
	instr[0x94] = funct_lcmp;
	instr[0x95] = funct_fcmpl;
	instr[0x96] = funct_fcmpg;
	instr[0x97] = funct_dcmpl;
	instr[0x98] = funct_dcmpg;
	instr[0x99] = funct_ifeq;
	instr[0x9a] = funct_ifne;
	instr[0x9b] = funct_iflt;
	instr[0x9c] = funct_ifge;
	instr[0x9d] = funct_ifgt;
	instr[0x9e] = funct_ifle;
	instr[0x9f] = funct_if_icmpeq;
	instr[0xa0] = funct_if_icmpne;
	instr[0xa1] = funct_if_icmplt;
	instr[0xa2] = funct_if_icmpge;
	instr[0xa3] = funct_if_icmpgt;
	instr[0xa4] = funct_if_icmple;
	instr[0xa5] = funct_if_acmpeq;
	instr[0xa6] = funct_if_acmpne;
	instr[0xa7] = funct_goto;
	instr[0xa8] = funct_jsr;
	instr[0xa9] = funct_ret;
	instr[0xaa] = funct_tableswitch;
	instr[0xab] = funct_lookupswitch;
	instr[0xac] = funct_ireturn;
	instr[0xad] = funct_lreturn;
	instr[0xae] = funct_freturn;
	instr[0xaf] = funct_dreturn;
	instr[0xb0] = funct_areturn;
	instr[0xb1] = funct_return;
	instr[0xb2] = funct_getstatic;
	instr[0xb3] = funct_putstatic;
	instr[0xb4] = funct_getfield;
	instr[0xb5] = funct_putfield;
	instr[0xb6] = funct_invokevirtual;
	instr[0xb7] = funct_invokespecial;
	instr[0xb8] = funct_invokestatic;
	instr[0xb9] = funct_invokeinterface;
	instr[0xbb] = funct_new;
	instr[0xbc] = funct_newarray;
	instr[0xbd] = funct_anewarray;
	instr[0xc4] = funct_wide;
	instr[0xc5] = funct_multianewarray;
	instr[0xc6] = funct_ifnull;
	instr[0xc7] = funct_ifnonnull;
	instr[0xc8] = funct_goto_w;
	instr[0xc9] = funct_jsr_w;
}

void funct_nop() {
	frameAtual->pc++;
}

void funct_aconst_null() {
	push (CONSTANT_Null);
	frameAtual->pc++;
}

void funct_iconst_m1() {
	push(-1);
	frameAtual->pc++;
}

void funct_iconst_0() {
	push(0);
	frameAtual->pc++;
}

void funct_iconst_1() {
	push(1);
	frameAtual->pc++;
}

void funct_iconst_2() {
	push(2);
	frameAtual->pc++;
}

void funct_iconst_3() {
	push(3);
	frameAtual->pc++;
}

void funct_iconst_4() {
	push(4);
	frameAtual->pc++;
}

void funct_iconst_5() {
	push(5);
	frameAtual->pc++;
}

void funct_lconst_0() {
	push (0);
	push (0);
	frameAtual->pc++;
}

void funct_lconst_1() {
	push (0);
	push (1);
	frameAtual->pc++;
}

void funct_fconst_0() {
	u4 *aux;
	float f = 0.0;
	aux = (u4*) malloc(sizeof(u4));
	memcpy(aux, &f, sizeof(u4));
	push(*aux); /* Para recuperar o valor, deve-se fazer outro memcpy para um float */
	frameAtual->pc++;
}

void funct_fconst_1() {
	u4 *aux;
	float f = 1.0;
	aux = (u4*) malloc(sizeof(u4));
	memcpy(aux, &f, sizeof(u4));
	push(*aux); /* Para recuperar o valor, deve-se fazer outro memcpy para um float */
	frameAtual->pc++;
}

void funct_fconst_2() {
	u4 *aux;
	float f = 2.0;
	aux = (u4*) malloc(sizeof(u4));
	memcpy(aux, &f, sizeof(u4));
	push(*aux); /* Para recuperar o valor, deve-se fazer outro memcpy para um float */
	frameAtual->pc++;
}

void funct_dconst_0() {
	u4 aux_4;
	u8 *aux_8;
	double d = 0.0;
	aux_8 = (u8*) malloc(sizeof(u8));
	memcpy(aux_8, &d, 2*sizeof(u4));
	aux_4 = *aux_8 >> 32;
	push(aux_4);
	aux_4 = *aux_8;
	push(aux_4);
	frameAtual->pc++;

	/*  Funcao para recuperar o double:
	 *
		double d;
		u8 x = 0x0000000000000000, y = 0x0000000000000000;
		memcpy(&x, &high, sizeof(u4));
		memcpy(&y, &aux_4, sizeof(u4));
		x <<= 32;
		x |= y;
		memcpy(&d, &x, 2*sizeof(u4));
	 */
}

void funct_dconst_1() {
	u4 aux_4;
	u8 *aux_8;
	double d = 1.0;
	aux_8 = (u8*) malloc(sizeof(u8));
	memcpy(aux_8, &d, 2*sizeof(u4));
	aux_4 = *aux_8 >> 32;
	push(aux_4);
	aux_4 = *aux_8;
	push(aux_4);
	frameAtual->pc++;
}

void funct_bipush() {
	int8_t aux = (int8_t) frameAtual->code[(++frameAtual->pc)];
	push((u4)aux);
	frameAtual->pc++;
}

void funct_sipush() {
	u1 low, high;
	int16_t aux;
	frameAtual->pc++;
	high = frameAtual->code[frameAtual->pc];
	frameAtual->pc++;
	low = frameAtual->code[frameAtual->pc];
	aux = (int16_t)convert_2x8_to_32_bits(low, high);
	push((u4)aux);
	frameAtual->pc++;
}

void funct_ldc() {
	u1 indice, tag;
	u2 string_index;
	frameAtual->pc++;
	indice = frameAtual->code[frameAtual->pc];
	tag = ((struct CONSTANT_Integer_info *) frameAtual->constant_pool[indice-1])->tag;

	switch(tag) {
		case (CONSTANT_Integer):
			push (((struct CONSTANT_Integer_info *) frameAtual->constant_pool[indice-1])->bytes);
			break;
		case (CONSTANT_Float):
			push (((struct CONSTANT_Float_info *) frameAtual->constant_pool[indice-1])->bytes);
			break;
		case (CONSTANT_String):
			string_index = ((struct CONSTANT_String_info *) frameAtual->constant_pool[indice-1])->string_index;
			push ((u4)getName(frameAtual->class, string_index));
			break;
	}
	frameAtual->pc++;
}

void funct_ldc_w() {
	u1 tag;
	u4 indice;
	u4 high, low;
	u2 string_index;

	frameAtual->pc++;
	high = frameAtual->code[frameAtual->pc];

	frameAtual->pc++;
	low = frameAtual->code[frameAtual->pc];

	indice = convert_2x8_to_32_bits(low, high);

	tag = ((struct CONSTANT_Integer_info *) frameAtual->constant_pool[indice-1])->tag;

	switch(tag) {
		case (CONSTANT_Integer):
			push (((struct CONSTANT_Integer_info *) frameAtual->constant_pool[indice-1])->bytes);
			break;
		case (CONSTANT_Float):
			push (((struct CONSTANT_Float_info *) frameAtual->constant_pool[indice-1])->bytes);
			break;
		case (CONSTANT_String):
			string_index = ((struct CONSTANT_String_info *) frameAtual->constant_pool[indice-1])->string_index;
			push ((u4)getName(frameAtual->class, string_index));
			break;
	}

	frameAtual->pc++;
}

void funct_ldc2_w() {
	u1 tag;
	u4 indice;
	u4 high, low;

	frameAtual->pc++;
	high = frameAtual->code[frameAtual->pc];

	frameAtual->pc++;
	low = frameAtual->code[frameAtual->pc];

	indice = convert_2x8_to_32_bits(low, high);

	tag = ((struct CONSTANT_Long_info *) frameAtual->constant_pool[indice-1])->tag;

	switch(tag) {
		case (CONSTANT_Long):
			push (((struct CONSTANT_Long_info *) frameAtual->constant_pool[indice-1])->high_bytes);
			push (((struct CONSTANT_Long_info *) frameAtual->constant_pool[indice-1])->low_bytes);
			break;
		case (CONSTANT_Double):
			push (((struct CONSTANT_Double_info *) frameAtual->constant_pool[indice-1])->high_bytes);
			push (((struct CONSTANT_Double_info *) frameAtual->constant_pool[indice-1])->low_bytes);
			break;
	}

	frameAtual->pc++;
}

void funct_iload() {
	u2 index;
	frameAtual->pc++;
	index = frameAtual->code[frameAtual->pc];

	if (next_is_wide == 1) {
		index = index << 8;
		frameAtual->pc++;
		index = index | frameAtual->code[frameAtual->pc];
		next_is_wide = 0;
	}

	push (frameAtual->fields[index]);
	frameAtual->pc++;
}

void funct_lload() {
	u2 index = 0;

	frameAtual->pc++;
	index = frameAtual->code[frameAtual->pc];

	if (next_is_wide == 1) {
		index = index << 8;
		frameAtual->pc++;
		index = index | frameAtual->code[frameAtual->pc];
		next_is_wide = 0;
	}

	/* push high first */
	push (frameAtual->fields[index]);
	push (frameAtual->fields[index+1]);

	frameAtual->pc++;
}


void funct_fload() {
	u2 index;
	frameAtual->pc++;
	index = frameAtual->code[frameAtual->pc];

	if (next_is_wide == 1){
		index = index << 8;
		frameAtual->pc++;
		index = index | frameAtual->code[frameAtual->pc];
		next_is_wide = 0;
	}

	push(frameAtual->fields[index]);
	frameAtual->pc++;
}

void funct_dload() {
	u2 index;
	frameAtual->pc++;
	index = frameAtual->code[frameAtual->pc];

	if (next_is_wide == 1){
		index = index << 8;
		frameAtual->pc++;
		index = index | frameAtual->code[frameAtual->pc];
		next_is_wide = 0;
	}

	/* push high first */
	push (frameAtual->fields[index]);
	push (frameAtual->fields[index+1]);
	frameAtual->pc++;
}

void funct_aload() {
	u2 index;
	frameAtual->pc++;
	index = frameAtual->code[frameAtual->pc];

	if (next_is_wide == 1){
		index = index << 8;
		frameAtual->pc++;
		index = index | frameAtual->code[frameAtual->pc];
		next_is_wide = 0;
	}

	push (frameAtual->fields[index]);
	frameAtual->pc++;
}

void funct_iload_0() {
	push(frameAtual->fields[0]);
	frameAtual->pc++;
}

void funct_iload_1() {
	push(frameAtual->fields[1]);
	frameAtual->pc++;
}

void funct_iload_2() {
	push(frameAtual->fields[2]);
	frameAtual->pc++;
}

void funct_iload_3() {
	push(frameAtual->fields[3]);
	frameAtual->pc++;
}

void funct_lload_0() {
	push(frameAtual->fields[0]);
	push(frameAtual->fields[1]);
	frameAtual->pc++;
}

void funct_lload_1() {
	push(frameAtual->fields[1]);
	push(frameAtual->fields[2]);
	frameAtual->pc++;
}

void funct_lload_2() {
	push(frameAtual->fields[2]);
	push(frameAtual->fields[3]);
	frameAtual->pc++;
}

void funct_lload_3() {
	push(frameAtual->fields[3]);
	push(frameAtual->fields[4]);
	frameAtual->pc++;
}

void funct_fload_0() {
	push(frameAtual->fields[0]);
	frameAtual->pc++;
}

void funct_fload_1() {
	push(frameAtual->fields[1]);
	frameAtual->pc++;
}

void funct_fload_2() {
	push(frameAtual->fields[2]);
	frameAtual->pc++;
}

void funct_fload_3() {
	push(frameAtual->fields[3]);
	frameAtual->pc++;
}

void funct_dload_0() {
	push(frameAtual->fields[0]);
	push(frameAtual->fields[1]);
	frameAtual->pc++;
}

void funct_dload_1() {
	push(frameAtual->fields[1]);
	push(frameAtual->fields[2]);
	frameAtual->pc++;
}

void funct_dload_2() {
	push(frameAtual->fields[2]);
	push(frameAtual->fields[3]);
	frameAtual->pc++;
}

void funct_dload_3() {
	push(frameAtual->fields[3]);
	push(frameAtual->fields[4]);
	frameAtual->pc++;
}

void funct_aload_0() {
	push(frameAtual->fields[0]);
	frameAtual->pc++;
}

void funct_aload_1() {
	push(frameAtual->fields[1]);
	frameAtual->pc++;
}

void funct_aload_2() {
	push(frameAtual->fields[2]);
	frameAtual->pc++;
}

void funct_aload_3() {
	push(frameAtual->fields[3]);
	frameAtual->pc++;
}

void funct_iaload() {
	u4 index;
	void *ref;
	index = pop();
	ref = (void *)pop();
	push(((u4 *)ref)[index]);
	frameAtual->pc++;
}

void funct_laload() {
	u4 index;
	void *ref;
	index = pop();
	ref = (void *)pop();
	pushU8(((u8 *)ref)[index]);
	frameAtual->pc++;
}

void funct_faload() {
	u4 index, res;
	void *ref;
	index = pop();
	ref = (void *)pop();
	memcpy(&res, &((float *)ref)[index], sizeof(u4));
	push(res);
	frameAtual->pc++;
}

void funct_daload() {
	u4 index;
	void *ref;
	index = pop();
	ref = (void *)pop();
	pushU8(((u8 *)ref)[index]);
	frameAtual->pc++;
}

void funct_aaload() {
	u4 index;
	void *ref;
	index = pop();
	ref = (void *)pop();
	push(((u4 *)ref)[index]);
	frameAtual->pc++;
}

void funct_baload() {
	u4 index;
	void *ref;
	index = pop();
	ref = (void *)pop();
	push((u4)(((u1*)ref)[index]));
	frameAtual->pc++;
}

void funct_caload() {
	u4 index;
	void *ref;
	index = pop();
	ref = (void *)pop();
	push((u4)(((u2*)ref)[index]));
	frameAtual->pc++;
}

void funct_saload() {
	u4 index;
	void *ref;
	index = pop();
	ref = (void *)pop();
	push((u4)(((u2*)ref)[index]));
	frameAtual->pc++;
}

void funct_istore() {
	u2 index;
	u4 value;
	frameAtual->pc++;
	index = frameAtual->code[frameAtual->pc];
	value = pop();
	frameAtual->fields[index] = value;
	frameAtual->pc++;
}

void funct_lstore() {
	u2 index;
	u4 high, low;
	frameAtual->pc++;
	index = frameAtual->code[frameAtual->pc];
	low = pop();
	high = pop();
	frameAtual->fields[index] = high;
	frameAtual->fields[index + 1] = low;
	frameAtual->pc++;
}

void funct_fstore() {
	u2 index;
	u4 value;
	frameAtual->pc++;
	index = frameAtual->code[frameAtual->pc];
	value = pop();
	frameAtual->fields[index] = value;
	frameAtual->pc++;
}

void funct_dstore() {
	u2 index;
	u4 high, low;
	frameAtual->pc++;
	index = frameAtual->code[frameAtual->pc];
	low = pop();
	high = pop();
	frameAtual->fields[index] = low;
	frameAtual->fields[index + 1] = high;
	frameAtual->pc++;
}

void funct_astore() {
	u2 index;
	u4 value;
	frameAtual->pc++;
	index = frameAtual->code[frameAtual->pc];
	value = pop();
	frameAtual->fields[index] = value;
	frameAtual->pc++;
}

void funct_istore_0() {
	u4 value;
	value = pop();
	frameAtual->fields[0] = value;
	frameAtual->pc++;
}

void funct_istore_1() {
	u4 value;
	value = pop();
	frameAtual->fields[1] = value;
	frameAtual->pc++;
}

void funct_istore_2() {
	u4 value;
	value = pop();
	frameAtual->fields[2] = value;
	frameAtual->pc++;
}

void funct_istore_3() {
	u4 value;
	value = pop();
	frameAtual->fields[3] = value;
	frameAtual->pc++;
}

void funct_lstore_0() {
	u4 high, low;
	low = pop();
	high = pop();
	frameAtual->fields[0] = high;
	frameAtual->fields[1] = low;
	frameAtual->pc++;
}

void funct_lstore_1() {
	u4 high, low;
	low = pop();
	high = pop();
	frameAtual->fields[1] = high;
	frameAtual->fields[2] = low;
	frameAtual->pc++;
}

void funct_lstore_2() {
	u4 high, low;
	low = pop();
	high = pop();
	frameAtual->fields[2] = high;
	frameAtual->fields[3] = low;
	frameAtual->pc++;
}

void funct_lstore_3() {
	u4 high, low;
	low = pop();
	high = pop();
	frameAtual->fields[3] = high;
	frameAtual->fields[4] = low;
	frameAtual->pc++;
}

void funct_fstore_0() {
	u4  value;
	value = pop();
	frameAtual->fields[0] = value;
	frameAtual->pc++;
}

void funct_fstore_1() {
	u4 value;
	value = pop();
	frameAtual->fields[1] = value;
	frameAtual->pc++;
}

void funct_fstore_2() {
	u4 value;
	value = pop();
	frameAtual->fields[2] = value;
	frameAtual->pc++;
}

void funct_fstore_3() {
	u4 value;
	value = pop();
	frameAtual->fields[3] = value;
	frameAtual->pc++;
}

void funct_dstore_0() {
	u4 high, low;
	low = pop();
	high = pop();
	frameAtual->fields[0] = low;
	frameAtual->fields[1] = high;
	frameAtual->pc++;
}

void funct_dstore_1() {
	u4 high, low;
	low = pop();
	high = pop();
	frameAtual->fields[1] = low;
	frameAtual->fields[2] = high;
	frameAtual->pc++;
}

void funct_dstore_2() {
	u4 high, low;
	low = pop();
	high = pop();
	frameAtual->fields[2] = low;
	frameAtual->fields[3] = high;
	frameAtual->pc++;
}

void funct_dstore_3() {
	u4 high, low;
	low = pop();
	high = pop();
	frameAtual->fields[3] = low;
	frameAtual->fields[4] = high;
	frameAtual->pc++;
}

void funct_astore_0() {
	u4 value;
	value = pop();
	frameAtual->fields[0] = value;
	frameAtual->pc++;
}

void funct_astore_1() {
	u4 value;
	value = pop();
	frameAtual->fields[1] = value;
	frameAtual->pc++;
}

void funct_astore_2() {
	u4 value;
	value = pop();
	frameAtual->fields[2] = value;
	frameAtual->pc++;
}

void funct_astore_3() {
	u4 value;
	value = pop();
	frameAtual->fields[3] = value;
	frameAtual->pc++;
}

void funct_iastore() {
	u4 index, value;
	void *ref;
	value = pop();
	index = pop();
	ref = (void *)pop();
	((u4 *)ref)[index] = value;
	frameAtual->pc++;
}

void funct_lastore() {
	u4 index, low, high;
	u8 value;
	void *ref;
	low = pop();
	high = pop();
	value = convert_2x32_to_64_bits(low, high);
	index = pop();
	ref = (void *)pop();
	((u8 *)ref)[index] = value;
	frameAtual->pc++;
}

void funct_fastore() {
	u4 index, value;
	void *ref;
	value = pop();
	index = pop();
	ref = (void *)pop();
	((u4 *)ref)[index] = value;
	frameAtual->pc++;
}

void funct_dastore() {
	u4 index, low, high;
	u8 value;
	void *ref;
	low = pop();
	high = pop();
	value = convert_2x32_to_64_bits(low, high);
	index = pop();
	ref = (void *)pop();
	((u8 *)ref)[index] = value;
	frameAtual->pc++;
}

void funct_aastore() {
	u4 index, value;
	void *ref;
	value = pop();
	index = pop();
	ref = (void *)pop();
	((u4 *)ref)[index] = value;
	frameAtual->pc++;
}

void funct_bastore() {
	u4 index, value;
	void *ref;
	value = pop();
	index = pop();
	ref = (void *)pop();
	((u1 *)ref)[index] = (u1)value;
	frameAtual->pc++;
}

void funct_castore() {
	u4 index, value;
	void *ref;
	value = pop();
	index = pop();
	ref = (void *)pop();
	((u2 *)ref)[index] = (u2)value;
	frameAtual->pc++;
}

void funct_sastore() {
	u4 index, value;
	void *ref;
	value = pop();
	index = pop();
	ref = (void *)pop();
	((u2 *)ref)[index] = (u2)value;
	frameAtual->pc++;
}

void funct_pop() {
	pop();
	frameAtual->pc++;
}

void funct_pop2() {
	pop();
	pop();
	frameAtual->pc++;
}

void funct_dup() {
	u4 aux;
	aux = pop();
	push(aux);
	push(aux);
	frameAtual->pc++;
}

void funct_dup_x1() {
	u4 aux1, aux2;
	aux1 = pop();
	aux2 = pop();
	push(aux1);
	push(aux2);
	push(aux1);
	frameAtual->pc++;
}

void funct_dup_x2() {
	u4 value1, value2, value3;
	value1 = pop();
	value2 = pop();
	value3 = pop();
	push(value1);
	push(value3);
	push(value2);
	push(value1);
	frameAtual->pc++;
}

void funct_dup2() {
	u4 value1, value2;
	value1 = pop();
	value2 = pop();
	push(value2);
	push(value1);
	push(value2);
	push(value1);
	frameAtual->pc++;
}

void funct_dup2_x1() {
	u4 value1, value2, value3;
	value1 = pop();
	value2 = pop();
	value3 = pop();
	push(value2);
	push(value1);
	push(value3);
	push(value2);
	push(value1);
	frameAtual->pc++;
}

void funct_dup2_x2() {
	u4 value1, value2, value3, value4;
	value1 = pop();
	value2 = pop();
	value3 = pop();
	value4 = pop();
	push(value2);
	push(value1);
	push(value4);
	push(value3);
	push(value2);
	push(value1);
	frameAtual->pc++;
}

void funct_swap() {
	u4 aux1, aux2;
	aux1 = pop();
	aux2 = pop();
	push(aux1);
	push(aux2);
	frameAtual->pc++;
}

void funct_iadd() {
	u4 aux1, aux2;
	aux1 = pop();
	aux2 = pop();
	push (aux1 + aux2);
	frameAtual->pc++;
}

void funct_ladd() {
	int64_t aux1, aux2;
	u4 low, high;
	low = pop();
	high = pop();
	aux1 = convert_2x32_to_64_bits(low, high);
	low = pop();
	high = pop();
	aux2 = convert_2x32_to_64_bits(low, high);
	pushU8(aux1 + aux2);
	frameAtual->pc++;
}

void funct_fadd() {
	float f1, f2;
	u4 aux1, aux2;
	aux1 = pop();
	memcpy(&f1, &aux1, sizeof(u4));
	aux2 = pop();
	memcpy(&f2, &aux2, sizeof(u4));
	f1 += f2;
	memcpy(&aux1, &f1, sizeof(u4));
	push(aux1);
	frameAtual->pc++;
}

void funct_dadd() {
	double aux1, aux2;
	u4 high, low;
	u8 aux;
	low = pop();
	high = pop();
	aux = convert_2x32_to_64_bits(low, high);
	memcpy(&aux1, &aux, sizeof(u8));
	low = pop();
	high = pop();
	aux = convert_2x32_to_64_bits(low, high);
	memcpy(&aux2, &aux, sizeof(u8));
	aux1 += aux2;
	memcpy(&aux, &aux1, sizeof(u8));
	convert_64_bits_to_2x32(aux, &low, &high);
	push(high);
	push(low);
	frameAtual->pc++;
}

void funct_isub() {
	u4 aux1, aux2;
	aux1 = pop();
	aux2 = pop();
	push (aux2 - aux1);
	frameAtual->pc++;
}

void funct_lsub() {
	int64_t aux1, aux2;
	u4 low, high;
	low = pop();
	high = pop();
	aux1 = (signed)convert_2x32_to_64_bits(low, high);
	low = pop();
	high = pop();
	aux2 = (signed)convert_2x32_to_64_bits(low, high);
	pushU8(aux2 - aux1);
	frameAtual->pc++;
}

void funct_fsub() {
	u4 aux1, aux2, result;
	float value1, value2;
	aux2 = pop();
	aux1 = pop();
	memcpy(&value1, &aux1, sizeof(u4));
	memcpy(&value2, &aux2, sizeof(u4));
	value1 -= value2;
	memcpy(&result, &value1, sizeof(u4));
	push(result);
	frameAtual->pc++;
}

void funct_dsub() {
	u4 high1, low1, high2, low2;
	double value1, value2;
	u8 result;
	low2 = pop();
	high2 = pop();
	low1 = pop();
	high1 = pop();
	value1 = convert_cast_2x32_bits_to_double(low1, high1);
	value2 = convert_cast_2x32_bits_to_double(low2, high2);
	value1 -= value2;
	memcpy(&result, &value1, sizeof(u8));
	pushU8(result);
	frameAtual->pc++;
}

void funct_imul() {
	int32_t value1, value2;
	value1 = (int32_t)pop();
	value2 = (int32_t)pop();
	push((u4)(value1 * value2));
	frameAtual->pc++;
}

void funct_lmul() {
	int64_t value1, value2, result;
	u4 high1, low1, high2, low2;
	low1 = pop();
	high1 = pop();
	low2 = pop();
	high2 = pop();
	value1 = (int64_t)convert_2x32_to_64_bits(low1, high1);
	value2 = (int64_t)convert_2x32_to_64_bits(low2, high2);
	result = value1 * value2;
	pushU8(((u8)result));
	frameAtual->pc++;
}

void funct_fmul() {
	u4 aux1, aux2, result;
	float value1, value2;
	aux1 = pop();
	aux2 = pop();
	memcpy(&value1, &aux1, sizeof(u4));
	memcpy(&value2, &aux2, sizeof(u4));
	value1 *= value2;
	memcpy(&result, &value1, sizeof(u4));
	push(result);
	frameAtual->pc++;
}

void funct_dmul() {
	u4 high1, low1, high2, low2;
	double value1, value2;
	u8 value;
	low1 = pop();
	high1 = pop();
	low2 = pop();
	high2 = pop();
	value1 = convert_cast_2x32_bits_to_double(low1, high1);
	value2 = convert_cast_2x32_bits_to_double(low2, high2);
	value1 *= value2;
	memcpy(&value, &value1, sizeof(u8));
	pushU8(value);
	frameAtual->pc++;
}

void funct_idiv() {
	int32_t value1, value2;
	value2 = (int32_t)pop();
	value1 = (int32_t)pop();
	push(value1 / value2);
	frameAtual->pc++;
}

void funct_ldiv() {
	int64_t value1, value2, result;
	u4 high1, low1, high2, low2;
	low2 = pop();
	high2 = pop();
	low1 = pop();
	high1 = pop();
	value1 = (int64_t)convert_2x32_to_64_bits(low1, high1);
	value2 = (int64_t)convert_2x32_to_64_bits(low2, high2);
	result = value1 / value2;
	pushU8(result);
	frameAtual->pc++;
}

void funct_fdiv() {
	u4 aux1, aux2, result;
	float value1, value2;
	aux2 = pop();
	aux1 = pop();
	memcpy(&value1, &aux1, sizeof(u4));
	memcpy(&value2, &aux2, sizeof(u4));
	value1 /= value2;
	memcpy(&result, &value1, sizeof(u4));
	push(result);
	frameAtual->pc++;
}

void funct_ddiv() {
	u4 high1, low1, high2, low2;
	double value1, value2;
	u8 aux;
	low2 = pop();
	high2 = pop();
	low1 = pop();
	high1 = pop();
	value1 = convert_cast_2x32_bits_to_double(low1, high1);
	value2 = convert_cast_2x32_bits_to_double(low2, high2);
	value1 /= value2;
	memcpy(&aux, &value1, sizeof(u8));
	pushU8(aux);
	frameAtual->pc++;
}

void funct_irem() {
	u4 value1, value2;
	value2 = pop();
	value1 = pop();
	push(value1 % value2);
	frameAtual->pc++;
}

void funct_lrem() {
	int64_t aux1, aux2;
	u4 low, high;
	low = pop();
	high = pop();
	aux2 = (signed) convert_2x32_to_64_bits(low , high);
	low = pop();
	high = pop();
	aux1 = (signed) convert_2x32_to_64_bits(low , high);
	aux1 = aux1 % aux2;
	push((u8)aux1);
	frameAtual->pc++;
}

void funct_frem() {
	float f1, f2;
	u4 aux1, aux2;
	aux1 = pop();
	memcpy(&f2, &aux1, sizeof(u4));
	aux2 = pop();
	memcpy(&f1, &aux2, sizeof(u4));
	f1 = fmodf(f1 , f2);
	memcpy(&aux1, &f1, sizeof(u4));
	push(aux1);
	frameAtual->pc++;
}

void funct_drem() {
	double d1, d2;
	u4 low, high;
	u8 aux;
	low = pop();
	high = pop();
	aux = convert_2x32_to_64_bits(low , high);
	memcpy(&d2, &aux, sizeof(u8));
	low = pop();
	high = pop();
	aux = convert_2x32_to_64_bits(low , high);
	memcpy(&d1, &aux, sizeof(u8));
	d1 = fmod(d1 , d2);
	memcpy(&aux, &d1, sizeof(u8));
	pushU8(aux);
	frameAtual->pc++;
}

void funct_ineg() {
	int32_t aux;
	aux = (int32_t) pop();
	aux = -aux;
	push((u4)aux);
	frameAtual->pc++;
}

void funct_lneg() {
	int64_t aux;
	u4 low, high;
	low = pop();
	high = pop();
	aux = (int64_t) convert_2x32_to_64_bits(low , high);
	aux = -aux;
	pushU8((u8)aux);
	frameAtual->pc++;
}

void funct_fneg() {
	float f;
	u4 aux;
	aux = pop();
	memcpy(&f, &aux, sizeof(u4));
	f = -f;
	memcpy(&aux, &f, sizeof(u4));
	push(aux);
	frameAtual->pc++;
}

void funct_dneg() {
	double d;
	u4 low, high;
	u8 aux;
	low = pop();
	high = pop();
	aux = convert_2x32_to_64_bits(low , high);
	memcpy(&d, &aux, sizeof(u8));
	d = -d;
	memcpy(&aux, &d, sizeof(u8));
	pushU8(aux);
	frameAtual->pc++;
}

void funct_ishl() {
	u4 mask = 0x1f;  /*... 0001 1111*/
	u4 aux1, aux2;
	aux2 = pop();
	aux2 &= mask;
	aux1 = pop();
	aux1 <<= aux2;
	push(aux1);
	frameAtual->pc++;
}

void funct_lshl() {
	int64_t aux1;
	u4 mask = 0x3f;  /*... 00011 1111*/
	u4 low, high, aux2;
	aux2 = pop();
	aux2 &= mask;
	low = pop();
	high = pop();
	aux1 = (signed) convert_2x32_to_64_bits(low , high);
	aux1 <<= aux2;
	push((u8)aux1);
	frameAtual->pc++;
}

void funct_ishr() {
	u4 mask = 0x1f;  /* ... 0001 1111 */
	u4 aux1, i;
	int32_t aux2;
	aux1 = pop();
	aux1 &= mask;
	aux2 = (int32_t)pop();
	for (i = 0; i < aux1; i++) {
		aux2 /= 2;
	}
	push((u4)aux2);
	frameAtual->pc++;
}

void funct_lshr() {
	u4 mask = 0x3f;  /*... 00011 1111*/
	u8 aux1 = 0xffffffffffffffff;  /* 1111 1111 ... */
	u8 aux4 = 0x8000000000000000;  /* 1000 0000 ... */
	u4 low, high;
	int64_t aux3;
	u4 aux2;
	aux2 = pop();
	aux2 &= mask;
	/* Deixa os (64-aux2) bits iniciais com 1 */
	aux1 <<= (64-aux2);
	low = pop();
	high = pop();
	aux3 = (signed) convert_2x32_to_64_bits(low , high);
	/* Verifica qual é o primeiro bit */
	aux4 = aux3 & aux4;
	aux3 >>= aux2;
	if (aux4) {
		aux3 |= aux1;
	}
	push((u8)aux3);
	frameAtual->pc++;
}

void funct_iushr() {
	u4 mask = 0x1f;  /* ... 0001 1111 */
	u4 aux1, aux2;
	aux2 = pop();
	aux2 &= mask;
	aux1 = pop();
	aux1 >>= aux2;
	push(aux1);
	frameAtual->pc++;
}

void funct_lushr() {
	int64_t aux1;
	u4 mask = 0x3f;  /*... 00011 1111*/
	u4 aux2;
	u4 low, high;
	aux2 = pop();
	aux2 &= mask;
	low = pop();
	high = pop();
	aux1 = (signed) convert_2x32_to_64_bits(low , high);
	aux1 >>= aux2;
	pushU8((u8)aux1);
	frameAtual->pc++;
}

void funct_iand() {
	u4 aux1, aux2;
	aux1 = pop();
	aux2 = pop();
	aux1 &= aux2;
	push(aux1);
	frameAtual->pc++;
}

void funct_land() {
	u8 aux1, aux2;
	u4 low, high;
	low = pop();
	high = pop();
	aux1 = convert_2x32_to_64_bits(low , high);
	low = pop();
	high = pop();
	aux2 = convert_2x32_to_64_bits(low , high);
	aux1 &= aux2;
	pushU8(aux1);
	frameAtual->pc++;
}

void funct_ior() {
	u4 aux1, aux2;
	aux1 = pop();
	aux2 = pop();
	aux1 |= aux2;
	push(aux1);
	frameAtual->pc++;
}

void funct_lor() {
	u8 aux1, aux2;
	u4 low, high;
	low = pop();
	high = pop();
	aux1 = convert_2x32_to_64_bits(low , high);
	low = pop();
	high = pop();
	aux2 = convert_2x32_to_64_bits(low , high);
	aux1 |= aux2;
	pushU8(aux1);
	frameAtual->pc++;
}

void funct_ixor() {
	u4 aux1, aux2;
	aux1 = pop();
	aux2 = pop();
	aux1 ^= aux2;
	push(aux1);
	frameAtual->pc++;
}

void funct_lxor() {
	u8 aux1, aux2;
	u4 low, high;
	low = pop();
	high = pop();
	aux1 = convert_2x32_to_64_bits(low , high);
	low = pop();
	high = pop();
	aux2 = convert_2x32_to_64_bits(low , high);
	aux1 ^= aux2;
	pushU8(aux1);
	frameAtual->pc++;
}

void funct_iinc() {
	u1 field_index = frameAtual->code[++(frameAtual->pc)];
	u4 aux = frameAtual->fields[field_index];
	u1 aux2 = frameAtual->code[++(frameAtual->pc)];
	int8_t index = (int8_t) aux;
	int8_t constant = (int8_t) aux2;
	index += constant;
	frameAtual->fields[field_index] = (u4) index;
	frameAtual->pc++;
}

void funct_i2l() {
	u4 mask = 0x80000000;  /* 1000 0000 ... */
	u8 extend = 0xffffffff00000000;
	u4 aux1, aux3;
	int64_t aux2;
	aux1 = pop();
	/* Verifica qual é o primeiro bit */
	aux3 = aux1 & mask;
	aux2 = (int64_t) aux1;
	/* Extende o 1 do sinal caso seja */
	if (aux3) {
		aux2 |= extend;
	}
	pushU8(aux2);
	frameAtual->pc++;
}

void funct_i2f() {
	u4 aux2;
	int32_t aux;
	float f;
	aux = (int32_t)pop();
	f = (float)aux;
	memcpy(&aux2, &f, sizeof(u4));
	push(aux2);
	frameAtual->pc++;
}

void funct_i2d() {
	double d;
	int32_t aux1;
	u8 aux2;
	aux1 = (int32_t)pop();
	d = (double)aux1;
	memcpy(&aux2, &d, sizeof(u8));
	pushU8(aux2);
	frameAtual->pc++;
}

void funct_l2i() {
	u4 low, high;
	low = pop();
	high = pop();
	push(low);
	frameAtual->pc++;
}

void funct_l2f() {
	u4 low, high, *aux;
	float f;
	low = pop();
	high = pop();
	f = (float) convert_cast_2x32_bits_to_double(low, high);
	aux = (u4*) malloc(sizeof(u4));
	memcpy(aux, &f, sizeof(u4));
	push(*aux); /* Para recuperar o valor, deve-se fazer outro memcpy para um float */
	frameAtual->pc++;
}

void funct_l2d() {
	u4 low, high, aux_4;
	u8 *aux_8;
	double d;
	low = pop();
	high = pop();
	d =  convert_cast_2x32_bits_to_double(low, high);
	aux_8 = (u8*) malloc(sizeof(u8));
	memcpy(aux_8, &d, 2*sizeof(u4));
	aux_4 = *aux_8 >> 32;
	push(aux_4);
	aux_4 = *aux_8;
	push(aux_4);
	frameAtual->pc++;
}

void funct_f2i() {
	u4 aux;
	float f;
	aux = pop();
	memcpy(&f, &aux, sizeof(u4));
	aux = (u4) f;
	push(aux);
	frameAtual->pc++;
}

void funct_f2l() {
	u4 aux_4;
	u8 aux_8;
	float f;
	aux_4 = pop();
	memcpy(&f, &aux_4, sizeof(u4));
	aux_8 = (u8) f;
	pushU8(aux_8);
	frameAtual->pc++;
}

void funct_f2d() {
	u4 aux_4;
	u8 aux_8;
	float f;
	double d;
	aux_4 = pop();
	memcpy(&f, &aux_4, sizeof(u4));
	d = (double) f;
	memcpy(&aux_8, &d, 2*sizeof(u4));
	pushU8(aux_8);
	frameAtual->pc++;
}

void funct_d2i() {
	u4 low, high;
	int32_t resp;
	u8 aux;
	double d;
	low = pop();
	high = pop();
	aux = convert_2x32_to_64_bits(low, high);
	memcpy(&d, &aux, 2*sizeof(u4));
	resp = (int32_t) d;
	push((u4)resp);
	frameAtual->pc++;
}

void funct_d2l() {
	u4 low, high;
	u8 aux;
	double d;
	low = pop();
	high = pop();
	aux = convert_2x32_to_64_bits(low, high);
	memcpy(&d, &aux, 2*sizeof(u4));
	aux = (u8) d;
	push(aux);
	frameAtual->pc++;
}

void funct_d2f() {
	u4 low, high, resp;
	u8 aux;
	double d;
	float f;
	low = pop();
	high = pop();
	aux = convert_2x32_to_64_bits(low, high);
	memcpy(&d, &aux, 2*sizeof(u4));
	f = (float) d;
	memcpy(&resp, &f, sizeof(u4));
	push(resp);
	frameAtual->pc++;
}

void funct_i2b() {
	int8_t aux;
	int32_t aux2;
	aux = (int8_t) pop();
	aux2 = (int32_t)aux;
	push((u4)aux2);
	frameAtual->pc++;
}

void funct_i2c() {
	int16_t aux;
	int32_t aux2;
	aux = (int16_t) pop();
	aux2 = (int32_t)aux;
	push((u4)aux2);
	frameAtual->pc++;
}

void funct_i2s() {
	int16_t aux;
	int32_t aux2;
	aux = (int16_t) pop();
	aux2 = (int32_t)aux;
	push((u4)aux2);
	frameAtual->pc++;
}

void funct_lcmp() {
	int32_t resp;
	u4 low, high;
	u8 aux1, aux2;
	low = pop();
	high = pop();
	aux2 = convert_2x32_to_64_bits(low, high);
	low = pop();
	high = pop();
	aux1 = convert_2x32_to_64_bits(low, high);
	if (aux1 == aux2) {
		resp = 0;
	} else if (aux1 > aux2) {
		resp = 1;
	} else {
		resp = -1;
	}
	push((u4) resp);
	frameAtual->pc++;
}

void funct_fcmpl() {
	int32_t resp;
	u4 aux;
	float f1, f2;
	aux = pop();
	memcpy(&f2, &aux, sizeof(u4));
	aux = pop();
	memcpy(&f1, &aux, sizeof(u4));
	if (f1 == f2) {
		resp = 0;
	} else if (f1 > f2) {
		resp = 1;
	} else {
		resp = -1;
	}
	push((u4) resp);
	frameAtual->pc++;
}

void funct_fcmpg() {
	int32_t resp;
	u4 aux;
	float f1, f2;
	aux = pop();
	memcpy(&f2, &aux, sizeof(u4));
	aux = pop();
	memcpy(&f1, &aux, sizeof(u4));
	if (f1 == f2) {
		resp = 0;
	} else if (f1 > f2) {
		resp = 1;
	} else {
		resp = -1;
	}
	push((u4) resp);
	frameAtual->pc++;
}

void funct_dcmpl() {
	int32_t resp;
	u4 low, high;
	u8 aux;
	double d1, d2;
	low = pop();
	high = pop();
	aux = convert_2x32_to_64_bits(low, high);
	memcpy(&d2, &aux, 2*sizeof(u4));
	low = pop();
	high = pop();
	aux = convert_2x32_to_64_bits(low, high);
	memcpy(&d1, &aux, 2*sizeof(u4));
	if (d1 == d2) {
		resp = 0;
	} else if (d1 > d2) {
		resp = 1;
	} else {
		resp = -1;
	}
	push((u4) resp);
	frameAtual->pc++;
}

void funct_dcmpg() {
	int32_t resp;
	u4 low, high;
	u8 aux;
	double d1, d2;
	low = pop();
	high = pop();
	aux = convert_2x32_to_64_bits(low, high);
	memcpy(&d2, &aux, 2*sizeof(u4));
	low = pop();
	high = pop();
	aux = convert_2x32_to_64_bits(low, high);
	memcpy(&d1, &aux, 2*sizeof(u4));
	if (d1 == d2) {
		resp = 0;
	} else if (d1 > d2) {
		resp = 1;
	} else {
		resp = -1;
	}
	push((u4) resp);
	frameAtual->pc++;
}

void funct_ifeq() {
	int32_t aux;
	int16_t offset;
	u1 branchbyte1, branchbyte2;
	branchbyte1 = frameAtual->code[(frameAtual->pc)+1];
	branchbyte2 = frameAtual->code[(frameAtual->pc)+2];
	aux = (signed) pop();
	if (aux == 0) {
		offset = (int16_t)convert_2x8_to_32_bits(branchbyte2, branchbyte1);
		frameAtual->pc += offset;
	} else {
		frameAtual->pc += 3;
	}
}

void funct_ifne() {
	int32_t aux;
	int16_t offset;
	u1 branchbyte1, branchbyte2;
	branchbyte1 = frameAtual->code[(frameAtual->pc)+1];
	branchbyte2 = frameAtual->code[(frameAtual->pc)+2];
	aux = (signed) pop();
	if (aux != 0) {
		offset = (int16_t)convert_2x8_to_32_bits(branchbyte2, branchbyte1);
		frameAtual->pc += offset;
	} else {
		frameAtual->pc += 3;
	}
}

void funct_iflt() {
	int32_t aux;
	int16_t offset;
	u1 branchbyte1, branchbyte2;
	branchbyte1 = frameAtual->code[(frameAtual->pc)+1];
	branchbyte2 = frameAtual->code[(frameAtual->pc)+2];
	aux = (signed) pop();
	if (aux < 0) {
		offset = (int16_t)convert_2x8_to_32_bits(branchbyte2, branchbyte1);
		frameAtual->pc += offset;
	} else {
		frameAtual->pc += 3;
	}
}

void funct_ifge() {
	int32_t aux;
	int16_t offset;
	u1 branchbyte1, branchbyte2;
	branchbyte1 = frameAtual->code[(frameAtual->pc)+1];
	branchbyte2 = frameAtual->code[(frameAtual->pc)+2];
	aux = (signed) pop();
	if (aux >= 0) {
		offset = (int16_t)convert_2x8_to_32_bits(branchbyte2, branchbyte1);
		frameAtual->pc += offset;
	} else {
		frameAtual->pc += 3;
	}
}

void funct_ifgt() {
	int32_t aux;
	int16_t offset;
	u1 branchbyte1, branchbyte2;
	branchbyte1 = frameAtual->code[(frameAtual->pc)+1];
	branchbyte2 = frameAtual->code[(frameAtual->pc)+2];
	aux = (signed) pop();
	if (aux > 0) {
		offset = (int16_t)convert_2x8_to_32_bits(branchbyte2, branchbyte1);
		frameAtual->pc += offset;
	} else {
		frameAtual->pc += 3;
	}
}

void funct_ifle() {
	int32_t aux;
	int16_t offset;
	u1 branchbyte1, branchbyte2;
	branchbyte1 = frameAtual->code[(frameAtual->pc)+1];
	branchbyte2 = frameAtual->code[(frameAtual->pc)+2];
	aux = (signed) pop();
	if (aux <= 0) {
		offset = (int16_t)convert_2x8_to_32_bits(branchbyte2, branchbyte1);
		frameAtual->pc += offset;
	} else {
		frameAtual->pc += 3;
	}
}

void funct_if_icmpeq() {
	int32_t aux1, aux2;
	int16_t offset;
	u1 branchbyte1, branchbyte2;
	branchbyte1 = frameAtual->code[(frameAtual->pc)+1];
	branchbyte2 = frameAtual->code[(frameAtual->pc)+2];
	aux1 = (signed) pop();
	aux2 = (signed) pop();
	if (aux1 == aux2) {
		offset = (int16_t)convert_2x8_to_32_bits(branchbyte2, branchbyte1);
		frameAtual->pc += offset;
	} else {
		frameAtual->pc += 3;
	}
}

void funct_if_icmpne() {
	int32_t aux1, aux2;
	int16_t offset;
	u1 branchbyte1, branchbyte2;
	branchbyte1 = frameAtual->code[(frameAtual->pc)+1];
	branchbyte2 = frameAtual->code[(frameAtual->pc)+2];
	aux1 = (signed) pop();
	aux2 = (signed) pop();
	if (aux1 != aux2) {
		offset = (int16_t)convert_2x8_to_32_bits(branchbyte2, branchbyte1);
		frameAtual->pc += offset;
	} else {
		frameAtual->pc += 3;
	}
}

void funct_if_icmplt() {
	int32_t aux1, aux2;
	int16_t offset;
	u1 branchbyte1, branchbyte2;
	branchbyte1 = frameAtual->code[(frameAtual->pc)+1];
	branchbyte2 = frameAtual->code[(frameAtual->pc)+2];
	aux2 = (signed) pop();
	aux1 = (signed) pop();
	if (aux1 < aux2) {
		offset = (int16_t)convert_2x8_to_32_bits(branchbyte2, branchbyte1);
		frameAtual->pc += offset;
	} else {
		frameAtual->pc += 3;
	}
}

void funct_if_icmpge() {
	int32_t aux1, aux2;
	int16_t offset;
	u1 branchbyte1, branchbyte2;
	branchbyte1 = frameAtual->code[(frameAtual->pc)+1];
	branchbyte2 = frameAtual->code[(frameAtual->pc)+2];
	aux2 = (signed) pop();
	aux1 = (signed) pop();
	if (aux1 >= aux2) {
		offset = (int16_t)convert_2x8_to_32_bits(branchbyte2, branchbyte1);
		frameAtual->pc += offset;
		printf("if_icmpge fez o branch para o PC = %d\n", current_frame->pc);
	} else {
		frameAtual->pc += 3;
	}
}

void funct_if_icmpgt() {
	int32_t aux1, aux2;
	int16_t offset;
	u1 branchbyte1, branchbyte2;
	branchbyte1 = frameAtual->code[(frameAtual->pc)+1];
	branchbyte2 = frameAtual->code[(frameAtual->pc)+2];
	aux2 = (signed) pop();
	aux1 = (signed) pop();
	if (aux1 > aux2) {
		offset = (int16_t)convert_2x8_to_32_bits(branchbyte2, branchbyte1);
		frameAtual->pc += offset;
	} else {
		frameAtual->pc += 3;
	}
}

void funct_if_icmple() {
	int32_t aux1, aux2;
	int16_t offset;
	u1 branchbyte1, branchbyte2;
	branchbyte1 = frameAtual->code[(frameAtual->pc)+1];
	branchbyte2 = frameAtual->code[(frameAtual->pc)+2];
	aux2 = (signed) pop();
	aux1 = (signed) pop();
	if (aux1 <= aux2) {
		offset = (int16_t)convert_2x8_to_32_bits(branchbyte2, branchbyte1);
		frameAtual->pc += offset;
	} else {
		frameAtual->pc += 3;
	}
}

void funct_if_acmpeq() {
	int32_t aux1, aux2;
	int16_t offset;
	u1 branchbyte1, branchbyte2;
	branchbyte1 = frameAtual->code[(frameAtual->pc)+1];
	branchbyte2 = frameAtual->code[(frameAtual->pc)+2];
	aux2 = (signed) pop();
	aux1 = (signed) pop();
	if (aux1 == aux2) {
		offset = (int16_t)convert_2x8_to_32_bits(branchbyte2, branchbyte1);
		frameAtual->pc += offset;
	} else {
		frameAtual->pc += 3;
	}
}

void funct_if_acmpne() {
	int32_t aux1, aux2;
	int16_t offset;
	u1 branchbyte1, branchbyte2;
	branchbyte1 = frameAtual->code[(frameAtual->pc)+1];
	branchbyte2 = frameAtual->code[(frameAtual->pc)+2];
	aux2 = (signed) pop();
	aux1 = (signed) pop();
	if (aux1 != aux2) {
		offset = (int16_t)convert_2x8_to_32_bits(branchbyte2, branchbyte1);
		frameAtual->pc += offset;
	} else {
		frameAtual->pc += 3;
	}
}

void funct_goto() {
	int16_t offset;
	u1 branchbyte1, branchbyte2;
	branchbyte1 = frameAtual->code[(frameAtual->pc)+1];
	branchbyte2 = frameAtual->code[(frameAtual->pc)+2];
	offset = (int16_t)convert_2x8_to_32_bits(branchbyte2, branchbyte1);
	frameAtual->pc += offset;
}

void funct_jsr() {
	int16_t offset;
	u1 branchbyte1, branchbyte2;
	push((frameAtual->pc) + 3); /* pc da proxima instrucao */
	branchbyte1 = frameAtual->code[(frameAtual->pc)+1];
	branchbyte2 = frameAtual->code[(frameAtual->pc)+2];
	offset = (int16_t)convert_2x8_to_32_bits(branchbyte2, branchbyte1);
	frameAtual->pc += offset;
}

void funct_ret() {
	u2 index;
	frameAtual->pc++;
	index = frameAtual->code[frameAtual->pc];
	if (next_is_wide == 1) {
		index = index << 8;
		frameAtual->pc++;
		index = index | frameAtual->code[frameAtual->pc];
		next_is_wide = 0;
	}
	frameAtual->pc = frameAtual->fields[index];
}

void funct_tableswitch() {
	int32_t default_, high, low, index;
	int32_t *tableswitch;
	u4 byte1, byte2, byte3, byte4, tableswitch_address, target, table_size, i, offset;
	index = (int32_t)pop();
	tableswitch_address = frameAtual->pc;
	/* pula os padding bytes */
	while ((frameAtual->pc + 1) % 4 != 0) {
		frameAtual->pc++;
	}
	frameAtual->pc++;

	byte1 = frameAtual->code[frameAtual->pc++];
	byte2 = frameAtual->code[frameAtual->pc++];
	byte3 = frameAtual->code[frameAtual->pc++];
	byte4 = frameAtual->code[frameAtual->pc++];

	default_ = ((byte1 & 0xFF) << 24) | ((byte2 & 0xFF) << 16) | ((byte3 & 0xFF) << 8) | (byte4 & 0xFF);

	byte1 = frameAtual->code[frameAtual->pc++];
	byte2 = frameAtual->code[frameAtual->pc++];
	byte3 = frameAtual->code[frameAtual->pc++];
	byte4 = frameAtual->code[frameAtual->pc++];

	low = ((byte1 & 0xFF) << 24) | ((byte2 & 0xFF) << 16) | ((byte3 & 0xFF) << 8) | (byte4 & 0xFF);

	byte1 = frameAtual->code[frameAtual->pc++];
	byte2 = frameAtual->code[frameAtual->pc++];
	byte3 = frameAtual->code[frameAtual->pc++];
	byte4 = frameAtual->code[frameAtual->pc++];

	high = ((byte1 & 0xFF) << 24) | ((byte2 & 0xFF) << 16) | ((byte3 & 0xFF) << 8) | (byte4 & 0xFF);

	table_size = high - low + 1;
	tableswitch = calloc(sizeof(u4), table_size);

	for (i = 0; i < table_size; i++) {
		byte1 = frameAtual->code[frameAtual->pc++];
		byte2 = frameAtual->code[frameAtual->pc++];
		byte3 = frameAtual->code[frameAtual->pc++];
		byte4 = frameAtual->code[frameAtual->pc++];
		tableswitch[i] = ((byte1 & 0xFF) << 24) | ((byte2 & 0xFF) << 16) | ((byte3 & 0xFF) << 8) | (byte4 & 0xFF);
	}

	if (index < low || index > high) {
		target = tableswitch_address + default_;
	} else {
		offset = tableswitch[index - low];
		target = tableswitch_address + offset;
	}

	frameAtual->pc = target;
}

void funct_lookupswitch() {
	int32_t default_, npairs, key;
	int32_t *match, *offset;
	u4 byte1, byte2, byte3, byte4, target, lookupswitch_address, i;
	u1 found;

	key = (int32_t)pop();
	lookupswitch_address = frameAtual->pc;

	/* pula os padding bytes */
	while ((frameAtual->pc + 1) % 4 != 0) {
		frameAtual->pc++;
	}
	frameAtual->pc++;

	byte1 = frameAtual->code[frameAtual->pc++];
	byte2 = frameAtual->code[frameAtual->pc++];
	byte3 = frameAtual->code[frameAtual->pc++];
	byte4 = frameAtual->code[frameAtual->pc++];

	default_ = ((byte1 & 0xFF) << 24) | ((byte2 & 0xFF) << 16) | ((byte3 & 0xFF) << 8) | (byte4 & 0xFF);

	byte1 = frameAtual->code[frameAtual->pc++];
	byte2 = frameAtual->code[frameAtual->pc++];
	byte3 = frameAtual->code[frameAtual->pc++];
	byte4 = frameAtual->code[frameAtual->pc++];

	npairs = ((byte1 & 0xFF) << 24) | ((byte2 & 0xFF) << 16) | ((byte3 & 0xFF) << 8) | (byte4 & 0xFF);

	match = calloc(sizeof(int32_t), npairs);
	offset = calloc(sizeof(int32_t), npairs);
	for (i = 0; i < npairs; i++) {
		byte1 = frameAtual->code[frameAtual->pc++];
		byte2 = frameAtual->code[frameAtual->pc++];
		byte3 = frameAtual->code[frameAtual->pc++];
		byte4 = frameAtual->code[frameAtual->pc++];

		match[i] = ((byte1 & 0xFF) << 24) | ((byte2 & 0xFF) << 16) | ((byte3 & 0xFF) << 8) | (byte4 & 0xFF);

		byte1 = frameAtual->code[frameAtual->pc++];
		byte2 = frameAtual->code[frameAtual->pc++];
		byte3 = frameAtual->code[frameAtual->pc++];
		byte4 = frameAtual->code[frameAtual->pc++];

		offset[i] = ((byte1 & 0xFF) << 24) | ((byte2 & 0xFF) << 16) | ((byte3 & 0xFF) << 8) | (byte4 & 0xFF);
	}

	i = 0;
	found = 0;
	while ((i < npairs) && (!found)) {
		if (match[i] == key) {
			found = 1;
		}
		i++;
	}
	i--;

	if (found) {
		target = offset[i] + lookupswitch_address;
	} else {
		target = default_ + lookupswitch_address;
	}

	frameAtual->pc = target;
}

void funct_ireturn() {
	u4 value;
	value = pop();
	returnType = RETURN_32bits;
	returnValue = (u8)value;
	frameAtual->pc++;
}

void funct_lreturn() {
	u4 low, high;
	low = pop();
	high = pop();
	returnType = RETURN_64bits;
	returnValue = convert_2x32_to_64_bits(low, high);
	frameAtual->pc++;
}

void funct_freturn() {
	u4 value;
	value = pop();
	returnType = RETURN_32bits;
	returnValue = (u8)value;
	frameAtual->pc++;
}

void funct_dreturn() {
	u4 low, high;
	low = pop();
	high = pop();
	returnType = RETURN_64bits;
	returnValue = convert_2x32_to_64_bits(low, high);
	frameAtual->pc++;
}

void funct_areturn() {
	u4 value;
	value = pop();
	returnType = RETURN_32bits;
	returnValue = (u8)value;
	frameAtual->pc++;
}

void funct_return() {
	returnType = RETURN_none;
	returnValue = 0;
	frameAtual->pc++;
}

void funct_getstatic() {
	u1 index1, index2;
	u2 index, name_type_index;
	u4 class_index_tmp;
	int32_t class_index, field_index;
	u8 value;
	char *class_name, *name, *type;


	index1 = (u1) frameAtual->code[++(frameAtual->pc)];
	index2 = (u1) frameAtual->code[++(frameAtual->pc)];

	index = ((u2)index1 << 8) | (u2)index2;

	class_index_tmp = ((struct CONSTANT_Fieldref_info *)(frameAtual->constant_pool[index-1]))->class_index;

	class_name = getName(frameAtual->class,
			((struct CONSTANT_Class_info *)(frameAtual->constant_pool[class_index_tmp-1]))->name_index);

	name_type_index = ((struct CONSTANT_Fieldref_info *)(frameAtual->constant_pool[index-1]))->name_and_type_index;

	name = getName(frameAtual->class,
			((struct CONSTANT_NameAndType_info *)(frameAtual->constant_pool[name_type_index-1]))->name_index);
	type = getName(frameAtual->class,
			((struct CONSTANT_NameAndType_info *)(frameAtual->constant_pool[name_type_index-1]))->descriptor_index);


	/* -1 informa que nao encontrou o field na casse corrente */
	while ((field_index = getFieldIndexByNameAndDesc(class_name, name, strlen(name), type, strlen(type))) == -1) {
		class_name = getParentName(getClassByName(class_name));
	}

	/* Verifica se deu algum erro (ou classe nao aceita) ao buscar o field (-2) */
	if (field_index == -2) {
		if (type[0] == 'J' || type[0] == 'D') {
			pushU8(0);
		} else {
			push(0);
		}

		frameAtual->pc++;
		return;
	}

	class_index = carregarClass(class_name);

	value = getStaticFieldValue(class_index , field_index);

	/* Verifica se eh Double ou Long para saber quantos bits colocar na pilha */
	if (type[0] == 'J' || type[0] == 'D') {
		pushU8(value);
	} else {
		push((u4)value);
	}

	frameAtual->pc++;
}

void funct_putstatic() {
	u1 index1, index2;
	u2 index, name_type_index;
	u4 class_index_tmp;
	int32_t class_index, field_index;
	u4 value1, value2;
	u8 value;
	char *class_name, *name, *type;

	index1 = (u1) frameAtual->code[++(frameAtual->pc)];
	index2 = (u1) frameAtual->code[++(frameAtual->pc)];

	index = ((u2)index1 << 8) | (u2)index2;

	class_index_tmp = ((struct CONSTANT_Fieldref_info *)(frameAtual->constant_pool[index-1]))->class_index;

	class_name = getName(frameAtual->class,
			((struct CONSTANT_Class_info *)(frameAtual->constant_pool[class_index_tmp-1]))->name_index);

	name_type_index = ((struct CONSTANT_Fieldref_info *)(frameAtual->constant_pool[index-1]))->name_and_type_index;

	name = getName(frameAtual->class,
			((struct CONSTANT_NameAndType_info *)(frameAtual->constant_pool[name_type_index-1]))->name_index);
	type = getName(frameAtual->class,
			((struct CONSTANT_NameAndType_info *)(frameAtual->constant_pool[name_type_index-1]))->descriptor_index);

	/* -1 informa que nao encontrou o field na casse corrente */
	while ((field_index = getFieldIndexByNameAndDesc(class_name, name, strlen(name), type, strlen(type))) == -1) {
		class_name = getParentName(getClassByName(class_name));
	}

	/* Verifica se deu algum erro (ou classe nao aceita) ao buscar o field (-2) */
	if (field_index == -2) {
		if (type[0] == 'J' || type[0] == 'D') {
			pop();
			pop();
		} else {
			pop();
		}

		frameAtual->pc++;
		return;
	}

	/* Pega o valor a ser inserido no field static */
	if (type[0] == 'J' || type[0] == 'D') {
		value1 = pop();
		value2 = pop();
		value = convert_2x32_to_64_bits(value1 , value2);
	} else {
		value = (u8) pop();
	}

	class_index = carregarClass(class_name);
	setStaticFieldValue(class_index , field_index , value);
	frameAtual->pc++;
}

void funct_getfield() {
	u1 low, high;
	u4 index;
	int32_t class_index, field_index, name_index;
	u2 name_type_index;
	char *class_name, *name, *type;

	struct Object *objeto;
	u4 value_aux;
	u8 value;

	high = frameAtual->code[++(frameAtual->pc)];
	low = frameAtual->code[++(frameAtual->pc)];

	index = convert_2x8_to_32_bits(low, high);

	class_index = ((struct CONSTANT_Fieldref_info *)(frameAtual->constant_pool[index-1]))->class_index;

	class_name = getName(frameAtual->class,
			((struct CONSTANT_Class_info *)(frameAtual->constant_pool[class_index-1]))->name_index);


	name_type_index = ((struct CONSTANT_Fieldref_info *)(frameAtual->constant_pool[index-1]))->name_and_type_index;

	name = getName(frameAtual->class,
			((struct CONSTANT_NameAndType_info *)(frameAtual->constant_pool[name_type_index-1]))->name_index);
	type = getName(frameAtual->class,
			((struct CONSTANT_NameAndType_info *)(frameAtual->constant_pool[name_type_index-1]))->descriptor_index);

	/* Pega a referencia do objeto que tera o field alterado de valor */
	objeto = (struct Object *) pop();

	/* -1 informa que nao encontrou o field na casse corrente */
	while ((field_index = getFieldIndexByNameAndDesc(class_name, name, strlen(name), type, strlen(type))) == -1) {
		class_name = getParentName(getClassByName(class_name));
	}

	/* Verifica se deu algum erro (ou classe nao aceita) ao buscar o field (-2) */
	if (field_index == -2) {
		if (type[0] == 'J' || type[0] == 'D') {
			pushU8(0);
		} else {
			push(0);
		}

		frameAtual->pc++;
		return;
	}

	name_index = frameAtual->class->fields[field_index].name_index;

	/* Pega o valor do field */
	if (type[0] == 'J' || type[0] == 'D') {
		value = getObjectFieldWide(objeto, name_index);
		pushU8(value);

	} else {
		value_aux = getObjectField(objeto, name_index);
		push(value_aux);
	}

	frameAtual->pc++;
}

void funct_putfield() {
	u1 low, high;
	u4 index;
	int32_t class_index, field_index, name_index;
	u2 name_type_index;
	char *class_name, *name, *type;

	struct Object *objeto;
	u4 value1, value2;
	u8 value;


	high = frameAtual->code[++(frameAtual->pc)];
	low = frameAtual->code[++(frameAtual->pc)];

	index = convert_2x8_to_32_bits(low, high);

	class_index = ((struct CONSTANT_Fieldref_info *)(frameAtual->constant_pool[index-1]))->class_index;

	class_name = getName(frameAtual->class,
			((struct CONSTANT_Class_info *)(frameAtual->constant_pool[class_index-1]))->name_index);

	name_type_index = ((struct CONSTANT_Fieldref_info *)(frameAtual->constant_pool[index-1]))->name_and_type_index;

	name = getName(frameAtual->class,
			((struct CONSTANT_NameAndType_info *)(frameAtual->constant_pool[name_type_index-1]))->name_index);
	type = getName(frameAtual->class,
			((struct CONSTANT_NameAndType_info *)(frameAtual->constant_pool[name_type_index-1]))->descriptor_index);

	/* -1 informa que nao encontrou o field na casse corrente */
	while ((field_index = getFieldIndexByNameAndDesc(class_name, name, strlen(name), type, strlen(type))) == -1) {
		class_name = getParentName(getClassByName(class_name));
	}

	/* Verifica se deu algum erro (ou classe nao aceita) ao buscar o field (-2) */
	if (field_index == -2) {
		if (type[0] == 'J' || type[0] == 'D') {
			pop();
			pop();
		} else {
			pop();
		}

		frameAtual->pc++;
		return;
	}

	name_index = frameAtual->class->fields[field_index].name_index;

	/* Pega o valor a ser colocado no field */
	if (type[0] == 'J' || type[0] == 'D') {
		value1 = pop();
		value2 = pop();
		/* Pega a referencia do objeto que tera o field alterado de valor */
		objeto = (struct Object *) pop();
		value = convert_2x32_to_64_bits(value1, value2);
		setObjectFieldWide(objeto, name_index, value);

	} else {
		value1 = pop();
		/* Pega a referencia do objeto que tera o field alterado de valor */
		objeto = (struct Object *) pop();
		setObjectField(objeto, name_index, value1);
	}

	frameAtual->pc++;
}

void funct_invokevirtual() {
	u4 index, value_high, value_low, vU4, array_ref;
	u8 value;
	u1 low, high;
	int32_t numParams, i, j;
	int32_t class_index, class_index_tmp;
	u2 name_type_index, method_name_index, method_desc_index;
	char *class_name, *method_name, *method_desc;
	u4 *fields_tmp;
	float vfloat;

	u1 *bytes;
	u2 length;

	struct ClassFile *class;
	method_info *method;

	high = frameAtual->code[++(frameAtual->pc)];
	low = frameAtual->code[++(frameAtual->pc)];

	index = convert_2x8_to_32_bits(low, high);

	class_index_tmp = ((struct CONSTANT_Methodref_info *)(frameAtual->constant_pool[index-1]))->class_index;

	class_name = getName(frameAtual->class,
			((struct CONSTANT_Class_info *)(frameAtual->constant_pool[class_index_tmp-1]))->name_index);

	name_type_index = ((struct CONSTANT_Methodref_info *)(frameAtual->constant_pool[index-1]))->name_and_type_index;

	method_name_index = ((struct CONSTANT_NameAndType_info *)(frameAtual->constant_pool[name_type_index-1]))->name_index;
	method_desc_index = ((struct CONSTANT_NameAndType_info *)(frameAtual->constant_pool[name_type_index-1]))->descriptor_index;

	method_desc = getName(frameAtual->class, method_desc_index);
	method_name = getName(frameAtual->class, method_name_index);

	/* se for print ou println */
	if ((strcmp(class_name, "java/io/PrintStream") == 0)
			&& ((strcmp(method_name,"print") == 0) || (strcmp(method_name,"println") == 0))
	){

		/* LONG */
		if (strstr(method_desc, "J") != NULL){
			value_low = pop();
			value_high = pop();
			value = convert_2x32_to_64_bits(value_low, value_high);
			printf("%"PRIi64, (int64_t)value);

			/* DOUBLE */
		} else if(strstr(method_desc, "D") != NULL) {
			value_low = pop();
			value_high = pop();
			value = convert_2x32_to_64_bits(value_low, value_high);
			printf("%.15f", value);

			/* BOOLEAN */
		} else if(strstr(method_desc, "Z") != NULL) {
			if (pop()) {
				printf("true");
			} else {
				printf("false");
			}
			/* CHAR */
		} else if(strstr(method_desc, "C") != NULL) {

			/* ARRAY */
			if(strstr(method_desc, "[C") != NULL) {

				array_ref = pop();

				for (i = 0; i < numArrays; i++) {
					if (arrayLength[i].ref == array_ref)
						break;
				}

				for (j = 0; j < arrayLength[i].size; j++) {
					printf("%c", (int16_t)array_ref +i);
				}

				/* CHAR */
			} else {
				printf("%c", (int16_t)pop());
			}

			/* INTEIRO */
		}else if(strstr(method_desc, "I") != NULL) {
			printf("%"PRIi32, (int32_t)pop());

			/* FLOAT */
		}else if(strstr(method_desc, "F") != NULL) {
			vU4 = pop();
			memcpy(&vfloat, &vU4, sizeof(u4));
			printf("%f", vfloat);

			/* STRING */
		}else if(strstr(method_desc, "Ljava/lang/String") != NULL) {
			vU4 = pop();
			printf("%s", (char *)vU4);

			/* OBJECT */
		}else if(strstr(method_desc, "Ljava/lang/Object") != NULL) {
			printf("%p", (void *)pop());
			/* chamar método toString do object e depois toCharArray() */
		}

		if (strcmp(method_name,"println") == 0)
			printf("\n");

	} else {
		class_index = carregarClass(class_name);
		class = getClassByIndex(class_index);

		while (class != NULL && (method = getMethodByNameAndDescIndex(class, frameAtual->class, name_type_index)) == NULL) {
			class_name = getParentName(class);

			class_index = carregarClass(class_name);
			class = getClassByIndex(class_index);
		}

		if (class == NULL) {
			printf(" Erro: Metodo nao encontrando.\n");
			exit(1);
		}

		numParams = getNumParameters(class , method);

		fields_tmp = calloc(sizeof(u4),numParams+1);
		for (i = numParams; i >= 0; i--) {
			fields_tmp[i] = pop();
		}

		if (method->access_flags & ACC_NATIVE ||
				strcmp("println", getName(class, method->name_index)) == 0) {

			bytes = ((struct CONSTANT_Utf8_info *)(class->constant_pool[(method->descriptor_index-1)]))->bytes;
			length = ((struct CONSTANT_Utf8_info *)(class->constant_pool[(method->descriptor_index-1)]))->length;

			if (bytes[length-1] == 'D' || bytes[length-1] == 'J') {
				pushU8(0);
			} else if (bytes[length-1] != 'V') {
				push(0);
			}

		} else {
			prepararMetodo(class, method);

			for (i = numParams; i >= 0; i--) {
				frameAtual->fields[i] = fields_tmp[i];
			}

			runMethod();
		}

	}

	frameAtual->pc++;
}

void funct_invokespecial() {
	u4 index;
	u1 low, high;
	int32_t numParams, i;
	int32_t class_index, class_index_tmp;
	u2 name_type_index;
	char *class_name;
	u4 *fields_tmp;

	u1 *bytes;
	u2 length;

	struct ClassFile *class;
	method_info *method;

	high = frameAtual->code[++(frameAtual->pc)];
	low = frameAtual->code[++(frameAtual->pc)];

	index = convert_2x8_to_32_bits(low, high);

	class_index_tmp = ((struct CONSTANT_Methodref_info *)(frameAtual->constant_pool[index-1]))->class_index;

	class_name = getName(frameAtual->class,
			((struct CONSTANT_Class_info *)(frameAtual->constant_pool[class_index_tmp-1]))->name_index);

	class_index = carregarClass(class_name);
	class = getClassByIndex(class_index);

	name_type_index = ((struct CONSTANT_Methodref_info *)(frameAtual->constant_pool[index-1]))->name_and_type_index;

	while (class != NULL && (method = getMethodByNameAndDescIndex(class, frameAtual->class, name_type_index)) == NULL) {
		class_name = getParentName(class);

		class_index = carregarClass(class_name);
		class = getClassByIndex(class_index);
	}

	if (class == NULL) {
		printf("Metodo nao encontrando.\n");
	}

	numParams = getNumParameters(class , method);

	fields_tmp = calloc(sizeof(u4),numParams+1);
	for (i = numParams; i >= 0; i--) {
		fields_tmp[i] = pop();
	}

	if (method->access_flags & ACC_NATIVE) {

		bytes = ((struct CONSTANT_Utf8_info *)(class->constant_pool[(method->descriptor_index-1)]))->bytes;
		length = ((struct CONSTANT_Utf8_info *)(class->constant_pool[(method->descriptor_index-1)]))->length;

		if (bytes[length-1] == 'D' || bytes[length-1] == 'J') {
			pushU8(0);
		} else if (bytes[length-1] != 'V') {
			push(0);
		}

	} else {
		prepararMetodo(class, method);

		for (i = numParams; i >= 0; i--) {
			frameAtual->fields[i] = fields_tmp[i];
		}

		runMethod();
	}

	frameAtual->pc++;
}

void funct_invokestatic() {

	u4 index;
	u1 low, high;
	int32_t numParams, i;
	int32_t class_index, class_index_tmp;
	u2 name_type_index;
	char *class_name;
	u4 *fields_tmp;

	u1 *bytes;
	u2 length;

	struct ClassFile *class;
	method_info *method;

	high = frameAtual->code[++(frameAtual->pc)];
	low = frameAtual->code[++(frameAtual->pc)];

	index = convert_2x8_to_32_bits(low, high);

	class_index_tmp = ((struct CONSTANT_Methodref_info *)(frameAtual->constant_pool[index-1]))->class_index;

	class_name = getName(frameAtual->class,
			((struct CONSTANT_Class_info *)(frameAtual->constant_pool[class_index_tmp-1]))->name_index);

	name_type_index = ((struct CONSTANT_Methodref_info *)(frameAtual->constant_pool[index-1]))->name_and_type_index;

	class_index = carregarClass(class_name);
	class = getClassByIndex(class_index);

	method = getMethodByNameAndDescIndex(class, frameAtual->class, name_type_index);

	numParams = getNumParameters(class , method);

	fields_tmp = calloc(sizeof(u4),numParams+1);
	for (i = numParams-1; i >= 0; i--) { /* única diferença pra invokespecial */
		index = pop();
		fields_tmp[i] = index;
	}

	if (method->access_flags & ACC_NATIVE) {
		bytes = ((struct CONSTANT_Utf8_info *)(class->constant_pool[(method->descriptor_index-1)]))->bytes;
		length = ((struct CONSTANT_Utf8_info *)(class->constant_pool[(method->descriptor_index-1)]))->length;

		if (bytes[length-1] == 'D' || bytes[length-1] == 'J') {
			pushU8(0);
		} else if (bytes[length-1] != 'V') {
			push(0);
		}

	} else {
		prepararMetodo(class, method);

		for (i = numParams-1; i >= 0; i--) {
			frameAtual->fields[i] = fields_tmp[i];
		}

		runMethod();
	}

	frameAtual->pc++;
}

void funct_invokeinterface() {
	u4 index;
	u1 low, high, args_count, zero;
	int32_t class_index, class_index_tmp, i;
	u2 name_type_index;
	char *class_name;
	u4 *fields_tmp;

	struct ClassFile *class;
	method_info *method;

	high = frameAtual->code[++(frameAtual->pc)];
	low = frameAtual->code[++(frameAtual->pc)];
	index = convert_2x8_to_32_bits(low, high);

	args_count = frameAtual->code[++(frameAtual->pc)];
	zero = frameAtual->code[++(frameAtual->pc)];

	/* pega da pilha os argumentos e o objectref */
	fields_tmp = calloc(sizeof(u4),args_count+1);
	for (i = args_count; i >= 0; i--) {
		fields_tmp[i] = pop();
	}

	class_index_tmp = ((struct CONSTANT_Methodref_info *)(frameAtual->constant_pool[index-1]))->class_index;

	class_name = getName(frameAtual->class,
			((struct CONSTANT_Class_info *)(frameAtual->constant_pool[class_index_tmp-1]))->name_index);

	class_index = carregarClass(class_name);
	class = getClassByIndex(class_index);

	name_type_index = ((struct CONSTANT_Methodref_info *)(frameAtual->constant_pool[index-1]))->name_and_type_index;

	while (class != NULL && (method = getMethodByNameAndDescIndex(class, frameAtual->class, name_type_index)) == NULL) {
		class_name = getParentName(class);
		class_index = carregarClass(class_name);
		class = getClassByIndex(class_index);
	}

	if (class == NULL) {
		printf("Metodo nao encontrando.\n");
	}

	/* Prepara e executa o metodo */
	prepararMetodo(class, method);

	for (i = args_count; i >= 0; i--) {
		frameAtual->fields[i] = fields_tmp[i];
	}

	runMethod();
	frameAtual->pc++;
}

void funct_new() {
	u1 low, high;
	u4 index;
	char *class_name;
	int32_t class_index;
	struct ClassFile *class;
	struct Object *objeto;

	high = frameAtual->code[++(frameAtual->pc)];
	low = frameAtual->code[++(frameAtual->pc)];

	index = convert_2x8_to_32_bits(low, high);

	class_name = getName(frameAtual->class,
			((struct CONSTANT_Class_info *)(frameAtual->constant_pool[index-1]))->name_index);

	class_index = carregarClass(class_name);
	class = getClassByIndex(class_index);

	objeto = newObject(class);
	push((u4)objeto);
	frameAtual->pc++;
}

void funct_newarray() {
	u4 count;
	u1 type;

	count = pop();
	frameAtual->pc++;
	type = frameAtual->code[frameAtual->pc];

	if (count < 0) {
		printf("Erro: Tamanho invalido do array\n");
	}

	push ((u4)newArray(count, type));
	frameAtual->pc++;
}

//TODO:OLHAR DEPOIS
void funct_anewarray() {

	/* algumas coisas estão comentadas pq provavelmente
	 * não são necessárias  */

	u4 count;
	/*u2 index;
	u1 type;*/

	count = pop();

	frameAtual->pc++;
	/*index = current_frame->code[current_frame->pc];
	index = index << 8;*/

	frameAtual->pc++;
	/*index = index | current_frame->code[current_frame->pc];*/

	if (count < 0) {
		printf("Erro: Tamanho invalido do array\n");
	}

	push ((u4)newArray(count, 0));
	frameAtual->pc++;
}

void funct_arraylength() {
	int i;
	u4 aref;
	aref = pop();

	for (i = 0; i < numArrays; i++) {
		if (arrayLength[i].ref == aref) {
			push(arrayLength[i].ref);
			frameAtual->pc++;
			return;
		}

		frameAtual->pc++;
	}

	push(0);
	frameAtual->pc++;
}

void funct_athrow() {
	frameAtual->pc++;
}

void funct_checkcast() {
	struct Object *ref;
	u2 index;

	frameAtual->pc++;
	index = frameAtual->code[frameAtual->pc];
	index = index << 8;
	frameAtual->pc++;
	index = index | frameAtual->code[frameAtual->pc];

	ref = (struct Object *)pop();

	if (ref == NULL) {
		printf("Erro: Referencia nula\n");
	}

	if (strcmp(getName(frameAtual->class, index), getClassName(ref->this)) == 0) {
		printf(" Erro: Objeto do tipo errado\n");
	}

	push((u4)ref);
	frameAtual->pc++;
}

void funct_instanceof() {
	struct Object *ref;
	u2 index;

	frameAtual->pc++;
	index = frameAtual->code[frameAtual->pc];
	index = index << 8;
	frameAtual->pc++;
	index = index | frameAtual->code[frameAtual->pc];

	ref = (struct Object *)pop();

	if (ref == NULL) {
		printf("Erro: Referencia nula\n");
	}

	if (strcmp(getName(frameAtual->class, index), getClassName(ref->this)) == 0) {
		push(1);
		frameAtual->pc++;
		return;
	}

	push(0);
	frameAtual->pc++;
}

void funct_monitorenter() {
	pop();
	frameAtual->pc++;
}

void funct_monitorexit() {
	pop();
	frameAtual->pc++;
}

void funct_wide() {
	next_is_wide = 1;
	frameAtual->pc++;
}

void funct_multianewarray() {
	u2 indexbyte1, indexbyte2, index, type, atype;
	u1 dimensions;
	u4 i, dimension, size;
	void *arrayref;
	char *array_type;

	frameAtual->pc++;
	indexbyte1 = frameAtual->code[frameAtual->pc];
	frameAtual->pc++;
	indexbyte1 = frameAtual->code[frameAtual->pc];
	frameAtual->pc++;
	indexbyte1 = frameAtual->code[frameAtual->pc];
	frameAtual->pc++;
	dimensions = frameAtual->code[frameAtual->pc];

	index = ((indexbyte1 & 0xFF) << 8) | (indexbyte2 & 0xFF);

	dimension = pop();
	arrayref = newArray(dimension, TYPE_reference);
	array_type = getName(frameAtual->class, ((struct CONSTANT_Class_info*)frameAtual->constant_pool[index -1])->name_index);

	i = 0;
	while (array_type[i] == '[') {
		i++;
	}

	switch (array_type[i]) {
		case 'L':
			type = TYPE_reference;
			atype = TYPE_reference;
			break;
		case 'Z':
			type = TYPE_boolean;
			atype = TYPE_boolean_size;
			break;
		case 'C':
			type = TYPE_char;
			atype = TYPE_char_size;
			break;
		case 'F':
			type = TYPE_float;
			atype = TYPE_float_size;
			break;
		case 'D':
			type = TYPE_double;
			atype = TYPE_double_size;
			break;
		case 'B':
			type = TYPE_byte;
			atype = TYPE_byte_size;
			break;
		case 'S':
			type = TYPE_short;
			atype = TYPE_short_size;
			break;
		case 'I':
			type = TYPE_int;
			atype = TYPE_int_size;
			break;
		case 'J':
			type = TYPE_long;
			atype = TYPE_long_size;
			break;
		default:
			type = TYPE_reference;
			atype = TYPE_reference_size;
	}
	for (i = 0; i < dimensions; i++) {
		size = pop();
		if (size == 0) {
			break;
		}

		if (atype == 1) {
			((u1**)arrayref)[i] = (u1*)newArray(type, size);
		} else if(atype == 2) {
			((u2**)arrayref)[i] = (u2*)newArray(type, size);
		} else if(atype == 4) {
			((u4**)arrayref)[i] = (u4*)newArray(type, size);
		} else {
			((u8**)arrayref)[i] = (u8*)newArray(type, size);
		}
	}

	push((u4)arrayref);
	frameAtual->pc++;
}

void funct_ifnull() {
	int32_t aux;
	u4 offset;
	u1 branchbyte1, branchbyte2;

	branchbyte1 = frameAtual->code[(frameAtual->pc)+1];
	branchbyte2 = frameAtual->code[(frameAtual->pc)+2];

	aux = (signed) pop();

	if (aux == CONSTANT_Null) {
		offset = convert_2x8_to_32_bits(branchbyte2, branchbyte1);
		frameAtual->pc += offset;
	} else {
		frameAtual->pc += 3;
	}
}

void funct_ifnonnull() {
	int32_t aux;
	int16_t offset;
	u1 branchbyte1, branchbyte2;

	branchbyte1 = frameAtual->code[(frameAtual->pc)+1];
	branchbyte2 = frameAtual->code[(frameAtual->pc)+2];

	aux = (signed) pop();

	if (aux != CONSTANT_Null) {
		offset = (int16_t)convert_2x8_to_32_bits(branchbyte2, branchbyte1);
		frameAtual->pc += offset;
	} else {
		frameAtual->pc += 3;
	}
}

void funct_goto_w() {
	int32_t offset;
	u4 branchbyte1, branchbyte2, branchbyte3, branchbyte4;
	branchbyte1 = frameAtual->code[(frameAtual->pc)+1];
	branchbyte2 = frameAtual->code[(frameAtual->pc)+2];
	branchbyte3 = frameAtual->code[(frameAtual->pc)+3];
	branchbyte4 = frameAtual->code[(frameAtual->pc)+4];
	offset = (int32_t)(((branchbyte1 & 0xFF)<<24) | ((branchbyte2 & 0xFF)<<16) | ((branchbyte3 & 0xFF)<<8) | (branchbyte1 & 0xFF));
	frameAtual->pc += offset;
}

void funct_jsr_w() {
	int32_t offset;
	u4 branchbyte1, branchbyte2, branchbyte3, branchbyte4;
	push((frameAtual->pc) + 5);
	branchbyte1 = frameAtual->code[(frameAtual->pc)+1];
	branchbyte2 = frameAtual->code[(frameAtual->pc)+2];
	branchbyte3 = frameAtual->code[(frameAtual->pc)+3];
	branchbyte4 = frameAtual->code[(frameAtual->pc)+4];
	offset = (int32_t)(((branchbyte1 & 0xFF)<<24) | ((branchbyte2 & 0xFF)<<16) | ((branchbyte3 & 0xFF)<<8) | (branchbyte1 & 0xFF));
	frameAtual->pc += offset;
}

