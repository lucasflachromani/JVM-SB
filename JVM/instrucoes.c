#include "instrucoes.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>

#include "const.h"
#include "frame.h"
#include "heap.h"
#include "metodos.h"
#include "pilha.h"
#include "tipos.h"

extern struct frame *frameAtual;
extern struct array *arrayLength;
extern u4 numArrays;

/* Variaveis usadas para saber qual o retorno da funcao */
extern u1 returnType;
extern u8 returnValue;

int next_is_wide = 0;

//extern opcode_informacao *op_info;

void executarInstrucoes(u1 opcode) {
	instrucao[opcode]();
}

void  iniciarInstrucoes(){
	instrucao[0x00] = i_nop;
	instrucao[0x01] = i_aconst_null;
	instrucao[0x02] = i_iconst_m1;
	instrucao[0x03] = i_iconst_0;
	instrucao[0x04] = i_iconst_1;
	instrucao[0x05] = i_iconst_2;
	instrucao[0x06] = i_iconst_3;
	instrucao[0x07] = i_iconst_4;
	instrucao[0x08] = i_iconst_5;
	instrucao[0x09] = i_lconst_0;
	instrucao[0x0a] = i_lconst_1;
	instrucao[0x0b] = i_fconst_0;
	instrucao[0x0c] = i_fconst_1;
	instrucao[0x0d] = i_fconst_2;
	instrucao[0x0e] = i_dconst_0;
	instrucao[0x0f] = i_dconst_1;
	instrucao[0x10] = i_bipush;
	instrucao[0x11] = i_sipush;
	instrucao[0x12] = i_ldc;
	instrucao[0x13] = i_ldc_w;
	instrucao[0x14] = i_ldc2_w;
	instrucao[0x15] = i_iload;
	instrucao[0x16] = i_lload;
	instrucao[0x17] = i_fload;
	instrucao[0x18] = i_dload;
	instrucao[0x19] = i_aload;
	instrucao[0x1a] = i_iload_0;
	instrucao[0x1b] = i_iload_1;
	instrucao[0x1c] = i_iload_2;
	instrucao[0x1d] = i_iload_3;
	instrucao[0x1e] = i_lload_0;
	instrucao[0x1f] = i_lload_1;
	instrucao[0x20] = i_lload_2;
	instrucao[0x21] = i_lload_3;
	instrucao[0x22] = i_fload_0;
	instrucao[0x23] = i_fload_1;
	instrucao[0x24] = i_fload_2;
	instrucao[0x25] = i_fload_3;
	instrucao[0x26] = i_dload_0;
	instrucao[0x27] = i_dload_1;
	instrucao[0x28] = i_dload_2;
	instrucao[0x29] = i_dload_3;
	instrucao[0x2a] = i_aload_0;
	instrucao[0x2b] = i_aload_1;
	instrucao[0x2c] = i_aload_2;
	instrucao[0x2d] = i_aload_3;
	instrucao[0x2e] = i_iaload;
	instrucao[0x2f] = i_laload;
	instrucao[0x30] = i_faload;
	instrucao[0x31] = i_daload;
	instrucao[0x32] = i_aaload;
	instrucao[0x33] = i_baload;
	instrucao[0x34] = i_caload;
	instrucao[0x35] = i_saload;
	instrucao[0x36] = i_istore;
	instrucao[0x37] = i_lstore;
	instrucao[0x38] = i_fstore;
	instrucao[0x39] = i_dstore;
	instrucao[0x3a] = i_astore;
	instrucao[0x3b] = i_istore_0;
	instrucao[0x3c] = i_istore_1;
	instrucao[0x3d] = i_istore_2;
	instrucao[0x3e] = i_istore_3;
	instrucao[0x3f] = i_lstore_0;
	instrucao[0x40] = i_lstore_1;
	instrucao[0x41] = i_lstore_2;
	instrucao[0x42] = i_lstore_3;
	instrucao[0x43] = i_fstore_0;
	instrucao[0x44] = i_fstore_1;
	instrucao[0x45] = i_fstore_2;
	instrucao[0x46] = i_fstore_3;
	instrucao[0x47] = i_dstore_0;
	instrucao[0x48] = i_dstore_1;
	instrucao[0x49] = i_dstore_2;
	instrucao[0x4a] = i_dstore_3;
	instrucao[0x4b] = i_astore_0;
	instrucao[0x4c] = i_astore_1;
	instrucao[0x4d] = i_astore_2;
	instrucao[0x4e] = i_astore_3;
	instrucao[0x4f] = i_iastore;
	instrucao[0x50] = i_lastore;
	instrucao[0x51] = i_fastore;
	instrucao[0x52] = i_dastore;
	instrucao[0x53] = i_aastore;
	instrucao[0x54] = i_bastore;
	instrucao[0x55] = i_castore;
	instrucao[0x56] = i_sastore;
	instrucao[0x60] = i_iadd;
	instrucao[0x61] = i_ladd;
	instrucao[0x62] = i_fadd;
	instrucao[0x63] = i_dadd;
	instrucao[0x64] = i_isub;
	instrucao[0x65] = i_lsub;
	instrucao[0x66] = i_fsub;
	instrucao[0x67] = i_dsub;
	instrucao[0x68] = i_imul;
	instrucao[0x69] = i_lmul;
	instrucao[0x6a] = i_fmul;
	instrucao[0x6b] = i_dmul;
	instrucao[0x6c] = i_idiv;
	instrucao[0x6d] = i_ldiv;
	instrucao[0x6e] = i_fdiv;
	instrucao[0x6f] = i_ddiv;
	instrucao[0x70] = i_irem;
	instrucao[0x71] = i_lrem;
	instrucao[0x72] = i_frem;
	instrucao[0x73] = i_drem;
	instrucao[0x74] = i_ineg;
	instrucao[0x75] = i_lneg;
	instrucao[0x76] = i_fneg;
	instrucao[0x77] = i_dneg;
	instrucao[0x78] = i_ishl;
	instrucao[0x79] = i_lshl;
	instrucao[0x7a] = i_ishr;
	instrucao[0x7b] = i_lshr;
	instrucao[0x7c] = i_iushr;
	instrucao[0x7d] = i_lushr;
	instrucao[0x7e] = i_iand;
	instrucao[0x7f] = i_land;
	instrucao[0x80] = i_ior;
	instrucao[0x81] = i_lor;
	instrucao[0x82] = i_ixor;
	instrucao[0x83] = i_lxor;
	instrucao[0x84] = i_iinc;
	instrucao[0x85] = i_i2l;
	instrucao[0x86] = i_i2f;
	instrucao[0x87] = i_i2d;
	instrucao[0x88] = i_l2i;
	instrucao[0x89] = i_l2f;
	instrucao[0x8a] = i_l2d;
	instrucao[0x8b] = i_f2i;
	instrucao[0x8c] = i_f2l;
	instrucao[0x8d] = i_f2d;
	instrucao[0x8e] = i_d2i;
	instrucao[0x8f] = i_d2l;
	instrucao[0x90] = i_d2f;
	instrucao[0x91] = i_i2b;
	instrucao[0x92] = i_i2c;
	instrucao[0x93] = i_i2s;
	instrucao[0x94] = i_lcmp;
	instrucao[0x95] = i_fcmpl;
	instrucao[0x96] = i_fcmpg;
	instrucao[0x97] = i_dcmpl;
	instrucao[0x98] = i_dcmpg;
	instrucao[0x99] = i_ifeq;
	instrucao[0x9a] = i_ifne;
	instrucao[0x9b] = i_iflt;
	instrucao[0x9c] = i_ifge;
	instrucao[0x9d] = i_ifgt;
	instrucao[0x9e] = i_ifle;
	instrucao[0x9f] = i_if_icmpeq;
	instrucao[0xa0] = i_if_icmpne;
	instrucao[0xa1] = i_if_icmplt;
	instrucao[0xa2] = i_if_icmpge;
	instrucao[0xa3] = i_if_icmpgt;
	instrucao[0xa4] = i_if_icmple;
	instrucao[0xa5] = i_if_acmpeq;
	instrucao[0xa6] = i_if_acmpne;
	instrucao[0xa7] = i_goto;
	instrucao[0xa8] = i_jsr;
	instrucao[0xa9] = i_ret;
	instrucao[0xaa] = i_tableswitch;
	instrucao[0xab] = i_lookupswitch;
	instrucao[0xac] = i_ireturn;
	instrucao[0xad] = i_lreturn;
	instrucao[0xae] = i_freturn;
	instrucao[0xaf] = i_dreturn;
	instrucao[0xb0] = i_areturn;
	instrucao[0xb1] = i_return;
	instrucao[0xb2] = i_getstatic;
	instrucao[0xb3] = i_putstatic;
	instrucao[0xb4] = i_getfield;
	instrucao[0xb5] = i_putfield;
	instrucao[0xb6] = i_invokevirtual;
	instrucao[0xb7] = i_invokespecial;
	instrucao[0xb8] = i_invokestatic;
	instrucao[0xb9] = i_invokeinterface;
	instrucao[0xbb] = i_new;
	instrucao[0xbc] = i_newarray;
	instrucao[0xbd] = i_anewarray;
	instrucao[0xc4] = i_wide;
	instrucao[0xc5] = i_multianewarray;
	instrucao[0xc6] = i_ifnull;
	instrucao[0xc7] = i_ifnonnull;
	instrucao[0xc8] = i_goto_w;
	instrucao[0xc9] = i_jsr_w;
}

void i_nop() {
	frameAtual->pc++;
}

void i_aconst_null() {
	push(CONSTANT_Null);
	frameAtual->pc++;
}

void i_iconst_m1() {
	push(-1);
	frameAtual->pc++;
}

void i_iconst_0() {
	push(0);
	frameAtual->pc++;
}

void i_iconst_1() {
	push(1);
	frameAtual->pc++;
}

void i_iconst_2() {
	push(2);
	frameAtual->pc++;
}

void i_iconst_3() {
	push(3);
	frameAtual->pc++;
}

void i_iconst_4() {
	push(4);
	frameAtual->pc++;
}

void i_iconst_5() {
	push(5);
	frameAtual->pc++;
}

void i_lconst_0() {
	push(0);
	push(0);
	frameAtual->pc++;
}

void i_lconst_1() {
	push(0);
	push(1);
	frameAtual->pc++;
}

void i_fconst_0() {
	u4 *auxiliar;
	float floatNum = 0.0;
	auxiliar = (u4*) malloc(sizeof(u4));
	memcpy(auxiliar, &floatNum, sizeof(u4));
	push(*auxiliar);
	frameAtual->pc++;
}

void i_fconst_1() {
	u4 *auxiliar;
	float f = 1.0;
	auxiliar = (u4*) malloc(sizeof(u4));
	memcpy(auxiliar, &f, sizeof(u4));
	push(*auxiliar);
	frameAtual->pc++;
}

void i_fconst_2() {
	u4 *auxiliar;
	float f = 2.0;
	auxiliar = (u4*) malloc(sizeof(u4));
	memcpy(auxiliar, &f, sizeof(u4));
	push(*auxiliar);
	frameAtual->pc++;
}

void i_dconst_0() {
	u4 auxiliar4;
	u8 *auxiliar8;
	double doubleNum = 0.0;
	auxiliar8 = (u8*) malloc(sizeof(u8));
	memcpy(auxiliar8, &doubleNum, 2*sizeof(u4));
	auxiliar4 = *auxiliar8 >> 32;
	push(auxiliar4);
	auxiliar4 = *auxiliar8;
	push(auxiliar4);
	frameAtual->pc++;
}

void i_dconst_1() {
	u4 auxiliar4;
	u8 *auxiliar8;
	double doubleNum = 1.0;
	auxiliar8 = (u8*) malloc(sizeof(u8));
	memcpy(auxiliar8, &doubleNum, 2*sizeof(u4));
	auxiliar4 = *auxiliar8 >> 32;
	push(auxiliar4);
	auxiliar4 = *auxiliar8;
	push(auxiliar4);
	frameAtual->pc++;
}

void i_bipush() {
	int8_t auxiliar = (int8_t) frameAtual->code[(++frameAtual->pc)];
	push((u4)auxiliar);
	frameAtual->pc++;
}

void i_sipush() {
	u1 low, high;
	int16_t auxiliar;
	frameAtual->pc++;
	high = frameAtual->code[frameAtual->pc];
	frameAtual->pc++;
	low = frameAtual->code[frameAtual->pc];
	auxiliar = (int16_t)convert_2x8_to_32_bits(low, high);
	push((u4)auxiliar);
	frameAtual->pc++;
}

void i_ldc() {
	u1 indice, tag;
	u2 stringIndex;
	frameAtual->pc++;
	indice = frameAtual->code[frameAtual->pc];
	tag = frameAtual->constantPool[indice-1].tag;
	switch(tag) {
		case(CInteger):
			push(frameAtual->constantPool[indice-1].type.Integer.bytes);
			break;
		case(CFloat):
			push(frameAtual->constantPool[indice-1].type.Float.bytes);
			break;
		case(CString):
			stringIndex = frameAtual->constantPool[indice-1].type.String.stringIndex;
			push((u4)getName(frameAtual->class, stringIndex));
			break;
	}
	frameAtual->pc++;
}

void i_ldc_w() {
	u1 tag;
	u4 indice;
	u4 high, low;
	u2 stringIndex;

	frameAtual->pc++;
	high = frameAtual->code[frameAtual->pc];
	frameAtual->pc++;
	low = frameAtual->code[frameAtual->pc];
	indice = convert_2x8_to_32_bits(low, high);
	tag = frameAtual->constantPool[indice-1].tag;

	switch(tag) {
		case(CInteger):
			push(frameAtual->constantPool[indice-1].type.Integer.bytes);
			break;
		case(CFloat):
			push(frameAtual->constantPool[indice-1].type.Float.bytes);
			break;
		case(CString):
			stringIndex = frameAtual->constantPool[indice-1].type.String.stringIndex;
			push((u4)getName(frameAtual->class, stringIndex));
			break;
	}
	frameAtual->pc++;
}

void i_ldc2_w() {
	u1 tag;
	u4 indice;
	u4 high, low;

	frameAtual->pc++;
	high = frameAtual->code[frameAtual->pc];
	frameAtual->pc++;
	low = frameAtual->code[frameAtual->pc];
	indice = convert_2x8_to_32_bits(low, high);
	tag = (frameAtual->constantPool[indice-1]).tag;

	switch(tag) {
		case(CLong):
			push(frameAtual->constantPool[indice-1].type.Long.highBytes);
			push(frameAtual->constantPool[indice-1].type.Long.lowBytes);
			break;
		case(CDouble):
			push(frameAtual->constantPool[indice-1].type.Double.highBytes);
			push(frameAtual->constantPool[indice-1].type.Double.lowBytes);
			break;
	}
	frameAtual->pc++;
}

void i_iload() {
	u2 index;
	frameAtual->pc++;
	index = frameAtual->code[frameAtual->pc];

	if(next_is_wide == 1){
		index = index << 8;
		frameAtual->pc++;
		index = index | frameAtual->code[frameAtual->pc];
		next_is_wide = 0;
	}
	push(frameAtual->fields[index]);
	frameAtual->pc++;
}

void i_lload() {
	u2 index = 0;
	frameAtual->pc++;
	index = frameAtual->code[frameAtual->pc];

	if(next_is_wide == 1){
		index = index << 8;
		frameAtual->pc++;
		index = index | frameAtual->code[frameAtual->pc];
		next_is_wide = 0;
	}
	push(frameAtual->fields[index]);
	push(frameAtual->fields[index+1]);
	frameAtual->pc++;
}

void i_fload() {
	u2 index;
	frameAtual->pc++;
	index = frameAtual->code[frameAtual->pc];

	if(next_is_wide == 1){
		index = index << 8;
		frameAtual->pc++;
		index = index | frameAtual->code[frameAtual->pc];
		next_is_wide = 0;
	}
	push(frameAtual->fields[index]);
	frameAtual->pc++;
}

void i_dload() {
	u2 index;
	frameAtual->pc++;
	index = frameAtual->code[frameAtual->pc];

	if(next_is_wide == 1){
		index = index << 8;
		frameAtual->pc++;
		index = index | frameAtual->code[frameAtual->pc];
		next_is_wide = 0;
	}
	push(frameAtual->fields[index]);
	push(frameAtual->fields[index+1]);
	frameAtual->pc++;
}

void i_aload() {
	u2 index;
	frameAtual->pc++;
	index = frameAtual->code[frameAtual->pc];

	if(next_is_wide == 1){
		index = index << 8;
		frameAtual->pc++;
		index = index | frameAtual->code[frameAtual->pc];
		next_is_wide = 0;
	}
	push(frameAtual->fields[index]);
	frameAtual->pc++;
}

void i_iload_0() {
	push(frameAtual->fields[0]);
	frameAtual->pc++;
}

void i_iload_1() {
	push(frameAtual->fields[1]);
	frameAtual->pc++;
}

void i_iload_2() {
	push(frameAtual->fields[2]);
	frameAtual->pc++;
}

void i_iload_3() {
	push(frameAtual->fields[3]);
	frameAtual->pc++;
}

void i_lload_0() {
	push(frameAtual->fields[0]);
	push(frameAtual->fields[1]);
	frameAtual->pc++;
}

void i_lload_1() {
	push(frameAtual->fields[1]);
	push(frameAtual->fields[2]);
	frameAtual->pc++;
}

void i_lload_2() {
	push(frameAtual->fields[2]);
	push(frameAtual->fields[3]);
	frameAtual->pc++;
}

void i_lload_3() {
	push(frameAtual->fields[3]);
	push(frameAtual->fields[4]);
	frameAtual->pc++;
}

void i_fload_0() {
	push(frameAtual->fields[0]);
	frameAtual->pc++;
}

void i_fload_1() {
	push(frameAtual->fields[1]);
	frameAtual->pc++;
}

void i_fload_2() {
	push(frameAtual->fields[2]);
	frameAtual->pc++;
}

void i_fload_3() {
	push(frameAtual->fields[3]);
	frameAtual->pc++;
}

void i_dload_0() {
	push(frameAtual->fields[0]);
	push(frameAtual->fields[1]);
	frameAtual->pc++;
}

void i_dload_1() {
	push(frameAtual->fields[1]);
	push(frameAtual->fields[2]);
	frameAtual->pc++;
}

void i_dload_2() {
	push(frameAtual->fields[2]);
	push(frameAtual->fields[3]);
	frameAtual->pc++;
}

void i_dload_3() {
	push(frameAtual->fields[3]);
	push(frameAtual->fields[4]);
	frameAtual->pc++;
}

void i_aload_0() {
	push(frameAtual->fields[0]);
	frameAtual->pc++;
}

void i_aload_1() {
	push(frameAtual->fields[1]);
	frameAtual->pc++;
}

void i_aload_2() {
	push(frameAtual->fields[2]);
	frameAtual->pc++;
}

void i_aload_3() {
	push(frameAtual->fields[3]);
	frameAtual->pc++;
}

void i_iaload() {
	u4 index;
	void *ref;
	index = pop();
	ref = (void *)pop();
	push(((u4 *)ref)[index]);
	frameAtual->pc++;
}

void i_laload() {
	u4 index;
	void *ref;
	index = pop();
	ref = (void *)pop();
	pushU8(((u8 *)ref)[index]);
	frameAtual->pc++;
}

void i_faload() {
	u4 index, res;
	void *ref;
	index = pop();
	ref = (void *)pop();
	memcpy(&res, &((float *)ref)[index], sizeof(u4));
	push(res);
	frameAtual->pc++;
}

void i_daload() {
	u4 index;
	void *ref;
	index = pop();
	ref = (void *)pop();
	pushU8(((u8 *)ref)[index]);
	frameAtual->pc++;
}

void i_aaload() {
	u4 index;
	void *ref;
	index = pop();
	ref = (void *)pop();
	push(((u4 *)ref)[index]);
	frameAtual->pc++;
}

void i_baload() {
	u4 index;
	void *ref;
	index = pop();
	ref = (void *)pop();
	push((u4)(((u1*)ref)[index]));
	frameAtual->pc++;
}

void i_caload() {
	u4 index;
	void *ref;
	index = pop();
	ref = (void *)pop();
	push((u4)(((u2*)ref)[index]));
	frameAtual->pc++;
}

void i_saload() {
	u4 index;
	void *ref;
	index = pop();
	ref = (void *)pop();
	push((u4)(((u2*)ref)[index]));
	frameAtual->pc++;
}

void i_istore() {
	u2 index;
	u4 valor;
	frameAtual->pc++;
	index = frameAtual->code[frameAtual->pc];
	valor = pop();
	frameAtual->fields[index] = valor;
	frameAtual->pc++;
}

void i_lstore() {
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

void i_fstore() {
	u2 index;
	u4 valor;
	frameAtual->pc++;
	index = frameAtual->code[frameAtual->pc];
	valor = pop();
	frameAtual->fields[index] = valor;
	frameAtual->pc++;
}

void i_dstore() {
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

void i_astore() {
	u2 index;
	u4 valor;
	frameAtual->pc++;
	index = frameAtual->code[frameAtual->pc];
	valor = pop();
	frameAtual->fields[index] = valor;
	frameAtual->pc++;
}

void i_istore_0() {
	u4 valor;
	valor = pop();
	frameAtual->fields[0] = valor;
	frameAtual->pc++;
}

void i_istore_1() {
	u4 valor;
	valor = pop();
	frameAtual->fields[1] = valor;
	frameAtual->pc++;
}

void i_istore_2() {
	u4 valor;
	valor = pop();
	frameAtual->fields[2] = valor;
	frameAtual->pc++;
}

void i_istore_3() {
	u4 valor;
	valor = pop();
	frameAtual->fields[3] = valor;
	frameAtual->pc++;
}

void i_lstore_0() {
	u4 high, low;
	low = pop();
	high = pop();
	frameAtual->fields[0] = high;
	frameAtual->fields[1] = low;
	frameAtual->pc++;
}

void i_lstore_1() {
	u4 high, low;
	low = pop();
	high = pop();
	frameAtual->fields[1] = high;
	frameAtual->fields[2] = low;
	frameAtual->pc++;
}

void i_lstore_2() {
	u4 high, low;
	low = pop();
	high = pop();
	frameAtual->fields[2] = high;
	frameAtual->fields[3] = low;
	frameAtual->pc++;
}

void i_lstore_3() {
	u4 high, low;
	low = pop();
	high = pop();
	frameAtual->fields[3] = high;
	frameAtual->fields[4] = low;
	frameAtual->pc++;
}

void i_fstore_0() {
	u4  valor;
	valor = pop();
	frameAtual->fields[0] = valor;
	frameAtual->pc++;
}

void i_fstore_1() {
	u4 valor;
	valor = pop();
	frameAtual->fields[1] = valor;
	frameAtual->pc++;
}

void i_fstore_2() {
	u4 valor;
	valor = pop();
	frameAtual->fields[2] = valor;
	frameAtual->pc++;
}

void i_fstore_3() {
	u4 valor;
	valor = pop();
	frameAtual->fields[3] = valor;
	frameAtual->pc++;
}

void i_dstore_0() {
	u4 high, low;
	low = pop();
	high = pop();
	frameAtual->fields[0] = low;
	frameAtual->fields[1] = high;
	frameAtual->pc++;
}

void i_dstore_1() {
	u4 high, low;
	low = pop();
	high = pop();
	frameAtual->fields[1] = low;
	frameAtual->fields[2] = high;
	frameAtual->pc++;
}

void i_dstore_2() {
	u4 high, low;
	low = pop();
	high = pop();
	frameAtual->fields[2] = low;
	frameAtual->fields[3] = high;
	frameAtual->pc++;
}

void i_dstore_3() {
	u4 high, low;
	low = pop();
	high = pop();
	frameAtual->fields[3] = low;
	frameAtual->fields[4] = high;
	frameAtual->pc++;
}

void i_astore_0() {
	u4 valor;
	valor = pop();
	frameAtual->fields[0] = valor;
	frameAtual->pc++;
}

void i_astore_1() {
	u4 valor;
	valor = pop();
	frameAtual->fields[1] = valor;
	frameAtual->pc++;
}

void i_astore_2() {
	u4 valor;
	valor = pop();
	frameAtual->fields[2] = valor;
	frameAtual->pc++;
}

void i_astore_3() {
	u4 valor;
	valor = pop();
	frameAtual->fields[3] = valor;
	frameAtual->pc++;
}

void i_iastore() {
	u4 index, valor;
	void *ref;
	valor = pop();
	index = pop();
	ref = (void *)pop();
	((u4 *)ref)[index] = valor;
	frameAtual->pc++;
}

void i_lastore() {
	u4 index, low, high;
	u8 valor;
	void *ref;
	low = pop();
	high = pop();
	valor = convert_2x32_to_64_bits(low, high);
	index = pop();
	ref = (void *)pop();
	((u8 *)ref)[index] = valor;
	frameAtual->pc++;
}

void i_fastore() {
	u4 index, valor;
	void *ref;
	valor = pop();
	index = pop();
	ref = (void *)pop();
	((u4 *)ref)[index] = valor;
	frameAtual->pc++;
}

void i_dastore() {
	u4 index, low, high;
	u8 valor;
	void *ref;
	low = pop();
	high = pop();
	valor = convert_2x32_to_64_bits(low, high);
	index = pop();
	ref = (void *)pop();
	((u8 *)ref)[index] = valor;
	frameAtual->pc++;
}

void i_aastore() {
	u4 index, valor;
	void *ref;
	valor = pop();
	index = pop();
	ref = (void *)pop();
	((u4 *)ref)[index] = valor;
	frameAtual->pc++;
}

void i_bastore() {
	u4 index, valor;
	void *ref;
	valor = pop();
	index = pop();
	ref = (void *)pop();
	((u1 *)ref)[index] = (u1)valor;
	frameAtual->pc++;
}

void i_castore() {
	u4 index, valor;
	void *ref;
	valor = pop();
	index = pop();
	ref = (void *)pop();
	((u2 *)ref)[index] = (u2)valor;
	frameAtual->pc++;
}

void i_sastore() {
	u4 index, valor;
	void *ref;
	valor = pop();
	index = pop();
	ref = (void *)pop();
	((u2 *)ref)[index] = (u2)valor;
	frameAtual->pc++;
}

void i_pop() {
	pop();
	frameAtual->pc++;
}

void i_pop2() {
	pop();
	pop();
	frameAtual->pc++;
}

void i_dup() {
	u4 auxiliar;
	auxiliar = pop();
	push(auxiliar);
	push(auxiliar);
	frameAtual->pc++;
}

void i_dup_x1() {
	u4 auxiliar1, auxiliar2;
	auxiliar1 = pop();
	auxiliar2 = pop();
	push(auxiliar1);
	push(auxiliar2);
	push(auxiliar1);
	frameAtual->pc++;
}

void i_dup_x2() {
	u4 valor1, valor2, valor3;
	valor1 = pop();
	valor2 = pop();
	valor3 = pop();
	push(valor1);
	push(valor3);
	push(valor2);
	push(valor1);
	frameAtual->pc++;
}

void i_dup2() {
	u4 valor1, valor2;
	valor1 = pop();
	valor2 = pop();
	push(valor2);
	push(valor1);
	push(valor2);
	push(valor1);
	frameAtual->pc++;
}

void i_dup2_x1() {
	u4 valor1, valor2, valor3;
	valor1 = pop();
	valor2 = pop();
	valor3 = pop();
	push(valor2);
	push(valor1);
	push(valor3);
	push(valor2);
	push(valor1);
	frameAtual->pc++;
}

void i_dup2_x2() {
	u4 valor1, valor2, valor3, valor4;
	valor1 = pop();
	valor2 = pop();
	valor3 = pop();
	valor4 = pop();
	push(valor2);
	push(valor1);
	push(valor4);
	push(valor3);
	push(valor2);
	push(valor1);
	frameAtual->pc++;
}

void i_swap() {
	u4 auxiliar1, auxiliar2;
	auxiliar1 = pop();
	auxiliar2 = pop();
	push(auxiliar1);
	push(auxiliar2);
	frameAtual->pc++;
}

void i_iadd() {
	u4 auxiliar1, auxiliar2;
	auxiliar1 = pop();
	auxiliar2 = pop();
	push(auxiliar1 + auxiliar2);
	frameAtual->pc++;
}

void i_ladd() {
	int64_t auxiliar1, auxiliar2;
	u4 low, high;
	low = pop();
	high = pop();
	auxiliar1 = convert_2x32_to_64_bits(low, high);
	low = pop();
	high = pop();
	auxiliar2 = convert_2x32_to_64_bits(low, high);
	pushU8(auxiliar1 + auxiliar2);
	frameAtual->pc++;
}

void i_fadd() {
	float f1, f2;
	u4 auxiliar1, auxiliar2;
	auxiliar1 = pop();
	memcpy(&f1, &auxiliar1, sizeof(u4));
	auxiliar2 = pop();
	memcpy(&f2, &auxiliar2, sizeof(u4));
	f1 += f2;
	memcpy(&auxiliar1, &f1, sizeof(u4));
	push(auxiliar1);
	frameAtual->pc++;
}

void i_dadd() {
	double auxiliar1, auxiliar2;
	u4 high, low;
	u8 auxiliar;
	low = pop();
	high = pop();
	auxiliar = convert_2x32_to_64_bits(low, high);
	memcpy(&auxiliar1, &auxiliar, sizeof(u8));
	low = pop();
	high = pop();
	auxiliar = convert_2x32_to_64_bits(low, high);
	memcpy(&auxiliar2, &auxiliar, sizeof(u8));
	auxiliar1 += auxiliar2;
	memcpy(&auxiliar, &auxiliar1, sizeof(u8));
	convert_64_bits_to_2x32(auxiliar, &low, &high);
	push(high);
	push(low);
	frameAtual->pc++;
}

void i_isub() {
	u4 auxiliar1, auxiliar2;
	auxiliar1 = pop();
	auxiliar2 = pop();
	push(auxiliar2 - auxiliar1);
	frameAtual->pc++;
}

void i_lsub() {
	int64_t auxiliar1, auxiliar2;
	u4 low, high;
	low = pop();
	high = pop();
	auxiliar1 = (signed)convert_2x32_to_64_bits(low, high);
	low = pop();
	high = pop();
	auxiliar2 = (signed)convert_2x32_to_64_bits(low, high);
	pushU8(auxiliar2 - auxiliar1);
	frameAtual->pc++;
}

void i_fsub() {
	u4 auxiliar1, auxiliar2, resulto;
	float valor1, valor2;
	auxiliar2 = pop();
	auxiliar1 = pop();
	memcpy(&valor1, &auxiliar1, sizeof(u4));
	memcpy(&valor2, &auxiliar2, sizeof(u4));
	valor1 -= valor2;
	memcpy(&resulto, &valor1, sizeof(u4));
	push(resulto);
	frameAtual->pc++;
}

void i_dsub() {
	u4 high1, low1, high2, low2;
	double valor1, valor2;
	u8 resulto;
	low2 = pop();
	high2 = pop();
	low1 = pop();
	high1 = pop();
	valor1 = convert_cast_2x32_bits_to_double(low1, high1);
	valor2 = convert_cast_2x32_bits_to_double(low2, high2);
	valor1 -= valor2;
	memcpy(&resulto, &valor1, sizeof(u8));
	pushU8(resulto);
	frameAtual->pc++;
}

void i_imul() {
	int32_t valor1, valor2;
	valor1 = (int32_t)pop();
	valor2 = (int32_t)pop();
	push((u4)(valor1 * valor2));
	frameAtual->pc++;
}

void i_lmul() {
	int64_t valor1, valor2, resulto;
	u4 high1, low1, high2, low2;
	low1 = pop();
	high1 = pop();
	low2 = pop();
	high2 = pop();
	valor1 = (int64_t)convert_2x32_to_64_bits(low1, high1);
	valor2 = (int64_t)convert_2x32_to_64_bits(low2, high2);
	resulto = valor1 * valor2;
	pushU8(((u8)resulto));
	frameAtual->pc++;
}

void i_fmul() {
	u4 auxiliar1, auxiliar2, resulto;
	float valor1, valor2;
	auxiliar1 = pop();
	auxiliar2 = pop();
	memcpy(&valor1, &auxiliar1, sizeof(u4));
	memcpy(&valor2, &auxiliar2, sizeof(u4));
	valor1 *= valor2;
	memcpy(&resulto, &valor1, sizeof(u4));
	push(resulto);
	frameAtual->pc++;
}

void i_dmul() {
	u4 high1, low1, high2, low2;
	double valor1, valor2;
	u8 valor;
	low1 = pop();
	high1 = pop();
	low2 = pop();
	high2 = pop();
	valor1 = convert_cast_2x32_bits_to_double(low1, high1);
	valor2 = convert_cast_2x32_bits_to_double(low2, high2);
	valor1 *= valor2;
	memcpy(&valor, &valor1, sizeof(u8));
	pushU8(valor);
	frameAtual->pc++;
}

void i_idiv() {
	int32_t valor1, valor2;
	valor2 = (int32_t)pop();
	valor1 = (int32_t)pop();
	push(valor1 / valor2);
	frameAtual->pc++;
}

void i_ldiv() {
	int64_t valor1, valor2, resulto;
	u4 high1, low1, high2, low2;
	low2 = pop();
	high2 = pop();
	low1 = pop();
	high1 = pop();
	valor1 = (int64_t)convert_2x32_to_64_bits(low1, high1);
	valor2 = (int64_t)convert_2x32_to_64_bits(low2, high2);
	resulto = valor1 / valor2;
	pushU8(resulto);
	frameAtual->pc++;
}

void i_fdiv() {
	u4 auxiliar1, auxiliar2, resulto;
	float valor1, valor2;
	auxiliar2 = pop();
	auxiliar1 = pop();
	memcpy(&valor1, &auxiliar1, sizeof(u4));
	memcpy(&valor2, &auxiliar2, sizeof(u4));
	valor1 /= valor2;
	memcpy(&resulto, &valor1, sizeof(u4));
	push(resulto);
	frameAtual->pc++;
}

void i_ddiv() {
	u4 high1, low1, high2, low2;
	double valor1, valor2;
	u8 auxiliar;
	low2 = pop();
	high2 = pop();
	low1 = pop();
	high1 = pop();
	valor1 = convert_cast_2x32_bits_to_double(low1, high1);
	valor2 = convert_cast_2x32_bits_to_double(low2, high2);
	valor1 /= valor2;
	memcpy(&auxiliar, &valor1, sizeof(u8));
	pushU8(auxiliar);
	frameAtual->pc++;
}

void i_irem() {
	u4 valor1, valor2;
	valor2 = pop();
	valor1 = pop();
	push(valor1 % valor2);
	frameAtual->pc++;
}

void i_lrem() {
	int64_t auxiliar1, auxiliar2;
	u4 low, high;
	low = pop();
	high = pop();
	auxiliar2 = (signed) convert_2x32_to_64_bits(low , high);
	low = pop();
	high = pop();
	auxiliar1 = (signed) convert_2x32_to_64_bits(low , high);
	auxiliar1 = auxiliar1 % auxiliar2;
	push((u8)auxiliar1);
	frameAtual->pc++;
}

void i_frem() {
	float f1, f2;
	u4 auxiliar1, auxiliar2;
	auxiliar1 = pop();
	memcpy(&f2, &auxiliar1, sizeof(u4));
	auxiliar2 = pop();
	memcpy(&f1, &auxiliar2, sizeof(u4));
	f1 = fmodf(f1 , f2);
	memcpy(&auxiliar1, &f1, sizeof(u4));
	push(auxiliar1);
	frameAtual->pc++;
}

void i_drem() {
	double d1, d2;
	u4 low, high;
	u8 auxiliar;
	low = pop();
	high = pop();
	auxiliar = convert_2x32_to_64_bits(low , high);
	memcpy(&d2, &auxiliar, sizeof(u8));
	low = pop();
	high = pop();
	auxiliar = convert_2x32_to_64_bits(low , high);
	memcpy(&d1, &auxiliar, sizeof(u8));
	d1 = fmod(d1 , d2);
	memcpy(&auxiliar, &d1, sizeof(u8));
	pushU8(auxiliar);
	frameAtual->pc++;
}

void i_ineg() {
	int32_t auxiliar;
	auxiliar = (int32_t) pop();
	auxiliar = -auxiliar;
	push((u4)auxiliar);
	frameAtual->pc++;
}

void i_lneg() {
	int64_t auxiliar;
	u4 low, high;
	low = pop();
	high = pop();
	auxiliar = (int64_t) convert_2x32_to_64_bits(low , high);
	auxiliar = -auxiliar;
	pushU8((u8)auxiliar);
	frameAtual->pc++;
}

void i_fneg() {
	float f;
	u4 auxiliar;
	auxiliar = pop();
	memcpy(&f, &auxiliar, sizeof(u4));
	f = -f;
	memcpy(&auxiliar, &f, sizeof(u4));
	push(auxiliar);
	frameAtual->pc++;
}

void i_dneg() {
	double d;
	u4 low, high;
	u8 auxiliar;
	low = pop();
	high = pop();
	auxiliar = convert_2x32_to_64_bits(low , high);
	memcpy(&d, &auxiliar, sizeof(u8));
	d = -d;
	memcpy(&auxiliar, &d, sizeof(u8));
	pushU8(auxiliar);
	frameAtual->pc++;
}

void i_ishl() {
	u4 mask = 0x1f;  /*... 0001 1111*/
	u4 auxiliar1, auxiliar2;
	auxiliar2 = pop();
	auxiliar2 &= mask;
	auxiliar1 = pop();
	auxiliar1 <<= auxiliar2;
	push(auxiliar1);
	frameAtual->pc++;
}

void i_lshl() {
	int64_t auxiliar1;
	u4 mask = 0x3f;  /*... 00011 1111*/
	u4 low, high, auxiliar2;
	auxiliar2 = pop();
	auxiliar2 &= mask;
	low = pop();
	high = pop();
	auxiliar1 = (signed) convert_2x32_to_64_bits(low , high);
	auxiliar1 <<= auxiliar2;
	push((u8)auxiliar1);
	frameAtual->pc++;
}

void i_ishr() {
	u4 mask = 0x1f;
	u4 auxiliar1, i;
	int32_t auxiliar2;
	auxiliar1 = pop();
	auxiliar1 &= mask;
	auxiliar2 = (int32_t)pop();
	for(i = 0; i < auxiliar1; i++) {
		auxiliar2 /= 2;
	}
	push((u4)auxiliar2);
	frameAtual->pc++;
}

void i_lshr() {
	u4 mask = 0x3f;
	u8 auxiliar1 = 0xffffffffffffffff;
	u8 auxiliar4 = 0x8000000000000000;
	u4 low, high;
	int64_t auxiliar3;
	u4 auxiliar2;
	auxiliar2 = pop();
	auxiliar2 &= mask;

	// Seta os bits (64-auxiliar2) mais significativos com 1
	auxiliar1 <<= (64-auxiliar2);
	low = pop();
	high = pop();
	auxiliar3 = (signed) convert_2x32_to_64_bits(low , high);

	//Verificar qual e o primeiro bit
	auxiliar4 = auxiliar3 & auxiliar4;
	auxiliar3 >>= auxiliar2;
	if(auxiliar4) {
		auxiliar3 |= auxiliar1;
	}
	push((u8)auxiliar3);
	frameAtual->pc++;
}

void i_iushr() {
	u4 mask = 0x1f;  /* ... 0001 1111 */
	u4 auxiliar1, auxiliar2;
	auxiliar2 = pop();
	auxiliar2 &= mask;
	auxiliar1 = pop();
	auxiliar1 >>= auxiliar2;
	push(auxiliar1);
	frameAtual->pc++;
}

void i_lushr() {
	int64_t auxiliar1;
	u4 mask = 0x3f;  /*... 00011 1111*/
	u4 auxiliar2;
	u4 low, high;
	auxiliar2 = pop();
	auxiliar2 &= mask;
	low = pop();
	high = pop();
	auxiliar1 = (signed) convert_2x32_to_64_bits(low , high);
	auxiliar1 >>= auxiliar2;
	pushU8((u8)auxiliar1);
	frameAtual->pc++;
}

void i_iand() {
	u4 auxiliar1, auxiliar2;
	auxiliar1 = pop();
	auxiliar2 = pop();
	auxiliar1 &= auxiliar2;
	push(auxiliar1);
	frameAtual->pc++;
}

void i_land() {
	u8 auxiliar1, auxiliar2;
	u4 low, high;
	low = pop();
	high = pop();
	auxiliar1 = convert_2x32_to_64_bits(low , high);
	low = pop();
	high = pop();
	auxiliar2 = convert_2x32_to_64_bits(low , high);
	auxiliar1 &= auxiliar2;
	pushU8(auxiliar1);
	frameAtual->pc++;
}

void i_ior() {
	u4 auxiliar1, auxiliar2;
	auxiliar1 = pop();
	auxiliar2 = pop();
	auxiliar1 |= auxiliar2;
	push(auxiliar1);
	frameAtual->pc++;
}

void i_lor() {
	u8 auxiliar1, auxiliar2;
	u4 low, high;
	low = pop();
	high = pop();
	auxiliar1 = convert_2x32_to_64_bits(low , high);
	low = pop();
	high = pop();
	auxiliar2 = convert_2x32_to_64_bits(low , high);
	auxiliar1 |= auxiliar2;
	pushU8(auxiliar1);
	frameAtual->pc++;
}

void i_ixor() {
	u4 auxiliar1, auxiliar2;
	auxiliar1 = pop();
	auxiliar2 = pop();
	auxiliar1 ^= auxiliar2;
	push(auxiliar1);
	frameAtual->pc++;
}

void i_lxor() {
	u8 auxiliar1, auxiliar2;
	u4 low, high;
	low = pop();
	high = pop();
	auxiliar1 = convert_2x32_to_64_bits(low , high);
	low = pop();
	high = pop();
	auxiliar2 = convert_2x32_to_64_bits(low , high);
	auxiliar1 ^= auxiliar2;
	pushU8(auxiliar1);
	frameAtual->pc++;
}

void i_iinc() {
	u1 field_index = frameAtual->code[++(frameAtual->pc)];
	u4 auxiliar = frameAtual->fields[field_index];
	u1 auxiliar2 = frameAtual->code[++(frameAtual->pc)];
	int8_t index = (int8_t) auxiliar;
	int8_t constant = (int8_t) auxiliar2;
	index += constant;
	frameAtual->fields[field_index] = (u4) index;
	frameAtual->pc++;
}

void i_i2l() {
	u4 mask = 0x80000000;
	u8 extend = 0xffffffff00000000;
	u4 auxiliar1, auxiliar3;
	int64_t auxiliar2;
	auxiliar1 = pop();
	auxiliar3 = auxiliar1 & mask;
	auxiliar2 = (int64_t) auxiliar1;
	if(auxiliar3) {
		auxiliar2 |= extend;
	}
	pushU8(auxiliar2);
	frameAtual->pc++;
}

void i_i2f() {
	u4 auxiliar2;
	int32_t auxiliar;
	float f;
	auxiliar = (int32_t)pop();
	f = (float)auxiliar;
	memcpy(&auxiliar2, &f, sizeof(u4));
	push(auxiliar2);
	frameAtual->pc++;
}

void i_i2d() {
	double doubleNum;
	int32_t auxiliar1;
	u8 auxiliar2;
	auxiliar1 = (int32_t)pop();
	doubleNum = (double)auxiliar1;
	memcpy(&auxiliar2, &doubleNum, sizeof(u8));
	pushU8(auxiliar2);
	frameAtual->pc++;
}

void i_l2i() {
	u4 low, high;
	low = pop();
	high = pop();
	push(low);
	frameAtual->pc++;
}

void i_l2f() {
	u4 low, high, *auxiliar;
	float floatNUm;
	low = pop();
	high = pop();
	floatNUm = (float) convert_cast_2x32_bits_to_double(low, high);
	auxiliar = (u4*) malloc(sizeof(u4));
	memcpy(auxiliar, &floatNUm, sizeof(u4));
	push(*auxiliar); /* Para recuperar o valor, deve-se fazer outro memcpy para um float */
	frameAtual->pc++;
}

void i_l2d() {
	u4 low, high, auxiliar4;
	u8 *auxiliar8;
	double doubleNum;
	low = pop();
	high = pop();
	doubleNum =  convert_cast_2x32_bits_to_double(low, high);
	auxiliar8 = (u8*) malloc(sizeof(u8));
	memcpy(auxiliar8, &doubleNum, 2*sizeof(u4));
	auxiliar4 = *auxiliar8 >> 32;
	push(auxiliar4);
	auxiliar4 = *auxiliar8;
	push(auxiliar4);
	frameAtual->pc++;
}

void i_f2i() {
	u4 auxiliar;
	float f;
	auxiliar = pop();
	memcpy(&f, &auxiliar, sizeof(u4));
	auxiliar = (u4) f;
	push(auxiliar);
	frameAtual->pc++;
}

void i_f2l() {
	u4 auxiliar4;
	u8 auxiliar8;
	float f;
	auxiliar4 = pop();
	memcpy(&f, &auxiliar4, sizeof(u4));
	auxiliar8 = (u8) f;
	pushU8(auxiliar8);
	frameAtual->pc++;
}

void i_f2d() {
	u4 auxiliar4;
	u8 auxiliar8;
	float floatNum;
	double doubleNum;
	auxiliar4 = pop();
	memcpy(&floatNum, &auxiliar4, sizeof(u4));
	doubleNum = (double) floatNum;
	memcpy(&auxiliar8, &doubleNum, 2*sizeof(u4));
	pushU8(auxiliar8);
	frameAtual->pc++;
}

void i_d2i() {
	u4 low, high;
	int32_t resp;
	u8 auxiliar;
	double doubleNum;
	low = pop();
	high = pop();
	auxiliar = convert_2x32_to_64_bits(low, high);
	memcpy(&doubleNum, &auxiliar, 2*sizeof(u4));
	resp = (int32_t) doubleNum;
	push((u4)resp);
	frameAtual->pc++;
}

void i_d2l() {
	u4 low, high;
	u8 auxiliar;
	double doubleNum;
	low = pop();
	high = pop();
	auxiliar = convert_2x32_to_64_bits(low, high);
	memcpy(&doubleNum, &auxiliar, 2*sizeof(u4));
	auxiliar = (u8) doubleNum;
	push(auxiliar);
	frameAtual->pc++;
}

void i_d2f() {
	u4 low, high, resp;
	u8 auxiliar;
	double d;
	float f;
	low = pop();
	high = pop();
	auxiliar = convert_2x32_to_64_bits(low, high);
	memcpy(&d, &auxiliar, 2*sizeof(u4));
	f = (float) d;
	memcpy(&resp, &f, sizeof(u4));
	push(resp);
	frameAtual->pc++;
}

void i_i2b() {
	int8_t auxiliar;
	int32_t auxiliar2;
	auxiliar = (int8_t) pop();
	auxiliar2 = (int32_t)auxiliar;
	push((u4)auxiliar2);
	frameAtual->pc++;
}

void i_i2c() {
	int16_t auxiliar;
	int32_t auxiliar2;
	auxiliar = (int16_t) pop();
	auxiliar2 = (int32_t)auxiliar;
	push((u4)auxiliar2);
	frameAtual->pc++;
}

void i_i2s() {
	int16_t auxiliar;
	int32_t auxiliar2;
	auxiliar = (int16_t) pop();
	auxiliar2 = (int32_t)auxiliar;
	push((u4)auxiliar2);
	frameAtual->pc++;
}

void i_lcmp() {
	int32_t resp;
	u4 low, high;
	u8 auxiliar1, auxiliar2;
	low = pop();
	high = pop();
	auxiliar2 = convert_2x32_to_64_bits(low, high);
	low = pop();
	high = pop();
	auxiliar1 = convert_2x32_to_64_bits(low, high);
	if(auxiliar1 == auxiliar2) {
		resp = 0;
	} else if(auxiliar1 > auxiliar2) {
		resp = 1;
	} else {
		resp = -1;
	}
	push((u4) resp);
	frameAtual->pc++;
}

void i_fcmpl() {
	int32_t resultado;
	u4 auxiliar;
	float floatNum1, floatNum2;
	auxiliar = pop();
	memcpy(&floatNum2, &auxiliar, sizeof(u4));
	auxiliar = pop();
	memcpy(&floatNum1, &auxiliar, sizeof(u4));
	if(floatNum1 == floatNum2) {
		resultado = 0;
	} else if(floatNum1 > floatNum2) {
		resultado = 1;
	} else {
		resultado = -1;
	}
	push((u4) resultado);
	frameAtual->pc++;
}

void i_fcmpg() {
	float floatNum1, floatNum2;
	u4 auxiliar;
	int32_t resultado;
	auxiliar = pop();
	memcpy(&floatNum2, &auxiliar, sizeof(u4));
	auxiliar = pop();
	memcpy(&floatNum1, &auxiliar, sizeof(u4));
	if(floatNum1 == floatNum2) {
		resultado = 0;
	} else if(floatNum1 > floatNum2) {
		resultado = 1;
	} else {
		resultado = -1;
	}
	push((u4) resultado);
	frameAtual->pc++;
}

void i_dcmpl() {
	double doubleNum1, doubleNum2;
	u4 low, high;
	u8 auxiliar;
	int32_t resultado;
	low = pop();
	high = pop();
	auxiliar = convert_2x32_to_64_bits(low, high);
	memcpy(&doubleNum2, &auxiliar, 2*sizeof(u4));
	low = pop();
	high = pop();
	auxiliar = convert_2x32_to_64_bits(low, high);
	memcpy(&doubleNum1, &auxiliar, 2*sizeof(u4));
	if(doubleNum1 == doubleNum2) {
		resultado = 0;
	} else if(doubleNum1 > doubleNum2) {
		resultado = 1;
	} else {
		resultado = -1;
	}
	push((u4) resultado);
	frameAtual->pc++;
}

void i_dcmpg() {
	double doubleNum1, doubleNum2;
	u4 low, high;
	u8 auxiliar;
	int32_t resultado;
	low = pop();
	high = pop();
	auxiliar = convert_2x32_to_64_bits(low, high);
	memcpy(&doubleNum2, &auxiliar, 2*sizeof(u4));
	low = pop();
	high = pop();
	auxiliar = convert_2x32_to_64_bits(low, high);
	memcpy(&doubleNum1, &auxiliar, 2*sizeof(u4));
	if(doubleNum1 == doubleNum2) {
		resultado = 0;
	} else if(doubleNum1 > doubleNum2) {
		resultado = 1;
	} else {
		resultado = -1;
	}
	push((u4) resultado);
	frameAtual->pc++;
}

void i_ifeq() {
	u1 branchbyte1, branchbyte2;
	int16_t offset;
	int32_t auxiliar;
	branchbyte1 = frameAtual->code[(frameAtual->pc)+1];
	branchbyte2 = frameAtual->code[(frameAtual->pc)+2];
	auxiliar = (signed) pop();
	if(auxiliar == 0) {
		offset = (int16_t)convert_2x8_to_32_bits(branchbyte2, branchbyte1);
		frameAtual->pc += offset;
	} else {
		frameAtual->pc += 3;
	}
}

void i_ifne() {
	u1 branchbyte1, branchbyte2;
	int16_t offset;
	int32_t auxiliar;
	branchbyte1 = frameAtual->code[(frameAtual->pc)+1];
	branchbyte2 = frameAtual->code[(frameAtual->pc)+2];
	auxiliar = (signed) pop();
	if(auxiliar != 0) {
		offset = (int16_t)convert_2x8_to_32_bits(branchbyte2, branchbyte1);
		frameAtual->pc += offset;
	} else {
		frameAtual->pc += 3;
	}
}

void i_iflt() {
	u1 branchbyte1, branchbyte2;
	int32_t auxiliar;
	int16_t offset;
	branchbyte1 = frameAtual->code[(frameAtual->pc)+1];
	branchbyte2 = frameAtual->code[(frameAtual->pc)+2];
	auxiliar = (signed) pop();
	if(auxiliar < 0) {
		offset = (int16_t)convert_2x8_to_32_bits(branchbyte2, branchbyte1);
		frameAtual->pc += offset;
	} else {
		frameAtual->pc += 3;
	}
}

void i_ifge() {
	u1 branchbyte1, branchbyte2;
	int32_t auxiliar;
	int16_t offset;
	branchbyte1 = frameAtual->code[(frameAtual->pc)+1];
	branchbyte2 = frameAtual->code[(frameAtual->pc)+2];
	auxiliar = (signed) pop();
 	if(auxiliar >= 0) {
		offset = (int16_t)convert_2x8_to_32_bits(branchbyte2, branchbyte1);
		frameAtual->pc += offset;
	} else {
		frameAtual->pc += 3;
	}
}

void i_ifgt() {
	u1 branchbyte1, branchbyte2;
	int32_t auxiliar;
	int16_t offset;
	branchbyte1 = frameAtual->code[(frameAtual->pc)+1];
	branchbyte2 = frameAtual->code[(frameAtual->pc)+2];
	auxiliar = (signed) pop();
	if(auxiliar > 0) {
		offset = (int16_t)convert_2x8_to_32_bits(branchbyte2, branchbyte1);
		frameAtual->pc += offset;
	} else {
		frameAtual->pc += 3;
	}
}

void i_ifle() {
	u1 branchbyte1, branchbyte2;
	int32_t auxiliar;
	int16_t offset;
	branchbyte1 = frameAtual->code[(frameAtual->pc)+1];
	branchbyte2 = frameAtual->code[(frameAtual->pc)+2];
	auxiliar = (signed) pop();
	if(auxiliar <= 0) {
		offset = (int16_t)convert_2x8_to_32_bits(branchbyte2, branchbyte1);
		frameAtual->pc += offset;
	} else {
		frameAtual->pc += 3;
	}
}

void i_if_icmpeq() {
	u1 branchbyte1, branchbyte2;
	int32_t auxiliar1, auxiliar2;
	int16_t offset;
	branchbyte1 = frameAtual->code[(frameAtual->pc)+1];
	branchbyte2 = frameAtual->code[(frameAtual->pc)+2];
	auxiliar1 = (signed) pop();
	auxiliar2 = (signed) pop();
	if(auxiliar1 == auxiliar2) {
		offset = (int16_t)convert_2x8_to_32_bits(branchbyte2, branchbyte1);
		frameAtual->pc += offset;
	} else {
		frameAtual->pc += 3;
	}
}

void i_if_icmpne() {
	u1 branchbyte1, branchbyte2;
	int32_t auxiliar1, auxiliar2;
	int16_t offset;
	branchbyte1 = frameAtual->code[(frameAtual->pc)+1];
	branchbyte2 = frameAtual->code[(frameAtual->pc)+2];
	auxiliar1 = (signed) pop();
	auxiliar2 = (signed) pop();
	if(auxiliar1 != auxiliar2) {
		offset = (int16_t)convert_2x8_to_32_bits(branchbyte2, branchbyte1);
		frameAtual->pc += offset;
	} else {
		frameAtual->pc += 3;
	}
}

void i_if_icmplt() {
	u1 branchbyte1, branchbyte2;
	int32_t auxiliar1, auxiliar2;
	int16_t offset;
	branchbyte1 = frameAtual->code[(frameAtual->pc)+1];
	branchbyte2 = frameAtual->code[(frameAtual->pc)+2];
	auxiliar2 = (signed) pop();
	auxiliar1 = (signed) pop();
 	if(auxiliar1 < auxiliar2) {
		offset = (int16_t)convert_2x8_to_32_bits(branchbyte2, branchbyte1);
		frameAtual->pc += offset;
	} else {
		frameAtual->pc += 3;
	}
}

void i_if_icmpge() {
	u1 branchbyte1, branchbyte2;
	int32_t auxiliar1, auxiliar2;
	int16_t offset;
	branchbyte1 = frameAtual->code[(frameAtual->pc)+1];
	branchbyte2 = frameAtual->code[(frameAtual->pc)+2];
	auxiliar2 = (signed) pop();
	auxiliar1 = (signed) pop();
	if(auxiliar1 >= auxiliar2) {
		offset = (int16_t)convert_2x8_to_32_bits(branchbyte2, branchbyte1);
		frameAtual->pc += offset;
	} else {
		frameAtual->pc += 3;
	}
}

void i_if_icmpgt() {
	u1 branchbyte1, branchbyte2;
	int32_t auxiliar1, auxiliar2;
	int16_t offset;
	branchbyte1 = frameAtual->code[(frameAtual->pc)+1];
	branchbyte2 = frameAtual->code[(frameAtual->pc)+2];
	auxiliar2 = (signed) pop();
	auxiliar1 = (signed) pop();
	if(auxiliar1 > auxiliar2) {
		offset = (int16_t)convert_2x8_to_32_bits(branchbyte2, branchbyte1);
		frameAtual->pc += offset;
	} else {
		frameAtual->pc += 3;
	}
}

void i_if_icmple() {
	u1 branchbyte1, branchbyte2;
	int32_t auxiliar1, auxiliar2;
	int16_t offset;
	branchbyte1 = frameAtual->code[(frameAtual->pc)+1];
	branchbyte2 = frameAtual->code[(frameAtual->pc)+2];
	auxiliar2 = (signed) pop();
	auxiliar1 = (signed) pop();
	if(auxiliar1 <= auxiliar2) {
		offset = (int16_t)convert_2x8_to_32_bits(branchbyte2, branchbyte1);
		frameAtual->pc += offset;
	} else {
		frameAtual->pc += 3;
	}
}

void i_if_acmpeq() {
	u1 branchbyte1, branchbyte2;
	int32_t auxiliar1, auxiliar2;
	int16_t offset;
	branchbyte1 = frameAtual->code[(frameAtual->pc)+1];
	branchbyte2 = frameAtual->code[(frameAtual->pc)+2];
	auxiliar2 = (signed) pop();
	auxiliar1 = (signed) pop();
	if(auxiliar1 == auxiliar2) {
		offset = (int16_t)convert_2x8_to_32_bits(branchbyte2, branchbyte1);
		frameAtual->pc += offset;
	} else {
		frameAtual->pc += 3;
	}
}

void i_if_acmpne() {
	u1 branchbyte1, branchbyte2;
	int32_t auxiliar1, auxiliar2;
	int16_t offset;
	branchbyte1 = frameAtual->code[(frameAtual->pc)+1];
	branchbyte2 = frameAtual->code[(frameAtual->pc)+2];
	auxiliar2 = (signed) pop();
	auxiliar1 = (signed) pop();
	if(auxiliar1 != auxiliar2) {
		offset = (int16_t)convert_2x8_to_32_bits(branchbyte2, branchbyte1);
		frameAtual->pc += offset;
	} else {
		frameAtual->pc += 3;
	}
}

void i_goto() {
	u1 branchbyte1, branchbyte2;
	int16_t offset;
	branchbyte1 = frameAtual->code[(frameAtual->pc)+1];
	branchbyte2 = frameAtual->code[(frameAtual->pc)+2];
	offset = (int16_t)convert_2x8_to_32_bits(branchbyte2, branchbyte1);
	frameAtual->pc += offset;
}

void i_jsr() {
	u1 branchbyte1, branchbyte2;
	int16_t offset;
	push((frameAtual->pc) + 3);
	branchbyte1 = frameAtual->code[(frameAtual->pc)+1];
	branchbyte2 = frameAtual->code[(frameAtual->pc)+2];
	offset = (int16_t)convert_2x8_to_32_bits(branchbyte2, branchbyte1);
	frameAtual->pc += offset;
}

void i_ret() {
	u2 index;
	frameAtual->pc++;
	index = frameAtual->code[frameAtual->pc];
	if(next_is_wide == 1){
		index = index << 8;
		frameAtual->pc++;
		index = index | frameAtual->code[frameAtual->pc];
		next_is_wide = 0;
	}
	frameAtual->pc = frameAtual->fields[index];
}

void i_tableswitch() {
	int32_t defaulT, high, low, index;
	int32_t *tableswitch;
	u4 byte1, byte2, byte3, byte4;
	u4 tableswitch_address;
	u4 target, tableSize;
	u4 i, offset;

	index = (int32_t)pop();
	tableswitch_address = frameAtual->pc;

	while((frameAtual->pc + 1) % 4 != 0) {
		frameAtual->pc++;
	}
	frameAtual->pc++;

	byte1 = frameAtual->code[frameAtual->pc++];
	byte2 = frameAtual->code[frameAtual->pc++];
	byte3 = frameAtual->code[frameAtual->pc++];
	byte4 = frameAtual->code[frameAtual->pc++];
	defaulT = ((byte1 & 0xFF) << 24) |((byte2 & 0xFF) << 16) |((byte3 & 0xFF) << 8) |(byte4 & 0xFF);

	byte1 = frameAtual->code[frameAtual->pc++];
	byte2 = frameAtual->code[frameAtual->pc++];
	byte3 = frameAtual->code[frameAtual->pc++];
	byte4 = frameAtual->code[frameAtual->pc++];
	low = ((byte1 & 0xFF) << 24) |((byte2 & 0xFF) << 16) |((byte3 & 0xFF) << 8) |(byte4 & 0xFF);

	byte1 = frameAtual->code[frameAtual->pc++];
	byte2 = frameAtual->code[frameAtual->pc++];
	byte3 = frameAtual->code[frameAtual->pc++];
	byte4 = frameAtual->code[frameAtual->pc++];
	high = ((byte1 & 0xFF) << 24) |((byte2 & 0xFF) << 16) |((byte3 & 0xFF) << 8) |(byte4 & 0xFF);

	tableSize = high - low + 1;
	tableswitch = calloc(sizeof(u4), tableSize);

	for(i = 0; i < tableSize; i++) 	{
		byte1 = frameAtual->code[frameAtual->pc++];
		byte2 = frameAtual->code[frameAtual->pc++];
		byte3 = frameAtual->code[frameAtual->pc++];
		byte4 = frameAtual->code[frameAtual->pc++];
		tableswitch[i] = ((byte1 & 0xFF) << 24) |((byte2 & 0xFF) << 16) |((byte3 & 0xFF) << 8) |(byte4 & 0xFF);
	}

	if(index < low || index > high) {
		target = tableswitch_address + defaulT;
	} else {
		offset = tableswitch[index - low];
		target = tableswitch_address + offset;
	}
	frameAtual->pc = target;
}

void i_lookupswitch() {
	int32_t defaulT, npairs, key;
	int32_t *match, *offset;
	u4 byte1, byte2, byte3, byte4;
	u4 target, lookupswitch_address;
	u4 i;
	u1 encontrado;

	key = (int32_t)pop();
	lookupswitch_address = frameAtual->pc;

	while((frameAtual->pc + 1) % 4 != 0) {
		frameAtual->pc++;
	}
	frameAtual->pc++;

	byte1 = frameAtual->code[frameAtual->pc++];
	byte2 = frameAtual->code[frameAtual->pc++];
	byte3 = frameAtual->code[frameAtual->pc++];
	byte4 = frameAtual->code[frameAtual->pc++];
	defaulT = ((byte1 & 0xFF) << 24) |((byte2 & 0xFF) << 16) |((byte3 & 0xFF) << 8) |(byte4 & 0xFF);

	byte1 = frameAtual->code[frameAtual->pc++];
	byte2 = frameAtual->code[frameAtual->pc++];
	byte3 = frameAtual->code[frameAtual->pc++];
	byte4 = frameAtual->code[frameAtual->pc++];
	npairs = ((byte1 & 0xFF) << 24) |((byte2 & 0xFF) << 16) |((byte3 & 0xFF) << 8) |(byte4 & 0xFF);

	match = calloc(sizeof(int32_t), npairs);
	offset = calloc(sizeof(int32_t), npairs);
	for(i = 0; i < npairs; i++) {
		byte1 = frameAtual->code[frameAtual->pc++];
		byte2 = frameAtual->code[frameAtual->pc++];
		byte3 = frameAtual->code[frameAtual->pc++];
		byte4 = frameAtual->code[frameAtual->pc++];
		match[i] = ((byte1 & 0xFF) << 24) |((byte2 & 0xFF) << 16) |((byte3 & 0xFF) << 8) |(byte4 & 0xFF);
		byte1 = frameAtual->code[frameAtual->pc++];
		byte2 = frameAtual->code[frameAtual->pc++];
		byte3 = frameAtual->code[frameAtual->pc++];
		byte4 = frameAtual->code[frameAtual->pc++];
		offset[i] = ((byte1 & 0xFF) << 24) |((byte2 & 0xFF) << 16) |((byte3 & 0xFF) << 8) |(byte4 & 0xFF);
	}

	i = 0;
	encontrado = 0;
	while((i < npairs) &&(!encontrado)) {
		if(match[i] == key)
			encontrado = 1;
		i++;
	}
	i--;

	if(encontrado) {
		target = offset[i] + lookupswitch_address;
	} else {
		target = defaulT + lookupswitch_address;
	}
	frameAtual->pc = target;
}

void i_ireturn() {
	u4 valor;
	valor = pop();
	returnType = RETURN_32bits;
	returnValue = (u8)valor;
	frameAtual->pc++;
}

void i_lreturn() {
	u4 low, high;
	low = pop();
	high = pop();
	returnType = RETURN_64bits;
	returnValue = convert_2x32_to_64_bits(low, high);
	frameAtual->pc++;
}

void i_freturn() {
	u4 valor;
	valor = pop();
	returnType = RETURN_32bits;
	returnValue = (u8)valor;
	frameAtual->pc++;
}

void i_dreturn() {
	u4 low, high;
	low = pop();
	high = pop();
	returnType = RETURN_64bits;
	returnValue = convert_2x32_to_64_bits(low, high);
	frameAtual->pc++;
}

void i_areturn() {
	u4 valor;
	valor = pop();
	returnType = RETURN_32bits;
	returnValue = (u8)valor;
	frameAtual->pc++;
}

void i_return() {
	returnType = RETURN_none;
	returnValue = 0;
	frameAtual->pc++;
}

void i_getstatic() {
	u1 index1, index2;
	u2 index, nameTypeIndex;
	u4 classIndexTemp;
	int32_t classIndex, field_index;
	u8 valor;
	char *className, *name, *type;

	index1 = (u1) frameAtual->code[++(frameAtual->pc)];
	index2 = (u1) frameAtual->code[++(frameAtual->pc)];
	index = ((u2)index1 << 8) |(u2)index2;
	classIndexTemp = frameAtual->constantPool[index-1].type.FieldRef.classIndex;
	className = getName(frameAtual->class, frameAtual->constantPool[classIndexTemp-1].type.Class.nameIndex);
	nameTypeIndex = frameAtual->constantPool[index-1].type.FieldRef.nameTypeIndex;
	name = getName(frameAtual->class, frameAtual->constantPool[nameTypeIndex-1].type.NameType.nameIndex);
	type = getName(frameAtual->class, frameAtual->constantPool[nameTypeIndex-1].type.NameType.descriptorIndex);

	while((field_index = getFieldIndexByNameAndDesc(className, name, strlen(name), type, strlen(type))) == -1) {
		className = getParentName(getClassByName(className));
	}

	if(field_index == -2) {
		if(type[0] == 'J' || type[0] == 'D') {
			pushU8(0);
		} else {
			push(0);
		}
		frameAtual->pc++;
		return;
	}

	classIndex = carregarClass(className);
	valor = getStaticFieldValue(classIndex , field_index);
	if(type[0] == 'J' || type[0] == 'D') {
		pushU8(valor);
	} else {
		push((u4)valor);
	}
	frameAtual->pc++;
}

void i_putstatic() {
	u1 index1, index2;
	u2 index, nameTypeIndex;
	u4 classIndexTemp;
	int32_t classIndex, field_index;
	u4 valor1, valor2;
	u8 valor;
	char *className, *name, *type;

	index1 = (u1) frameAtual->code[++(frameAtual->pc)];
	index2 = (u1) frameAtual->code[++(frameAtual->pc)];
	index = ((u2)index1 << 8) |(u2)index2;
	classIndexTemp = frameAtual->constantPool[index-1].type.FieldRef.classIndex;
	className = getName(frameAtual->class, frameAtual->constantPool[classIndexTemp-1].type.Class.nameIndex);
	nameTypeIndex = frameAtual->constantPool[index-1].type.FieldRef.nameTypeIndex;
	name = getName(frameAtual->class, frameAtual->constantPool[nameTypeIndex-1].type.NameType.nameIndex);
	type = getName(frameAtual->class, frameAtual->constantPool[nameTypeIndex-1].type.NameType.descriptorIndex);
	while((field_index = getFieldIndexByNameAndDesc(className, name, strlen(name), type, strlen(type))) == -1) {
		className = getParentName(getClassByName(className));
	}

	if(field_index == -2) {
		if(type[0] == 'J' || type[0] == 'D') {
			pop();
			pop();
		} else {
			pop();
		}
		frameAtual->pc++;
		return;
	}

	if(type[0] == 'J' || type[0] == 'D') {
		valor1 = pop();
		valor2 = pop();
		valor = convert_2x32_to_64_bits(valor1 , valor2);
	} else {
		valor = (u8) pop();
	}
	classIndex = carregarClass(className);
	setStaticFieldValue(classIndex , field_index , valor);
	frameAtual->pc++;
}

void i_getfield() {
	u1 low, high;
	u4 index;
	int32_t classIndex, field_index, nameIndex;
	u2 nameTypeIndex;
	char *className, *name, *type;
	struct Object *objeto;
	u4 valor_auxiliar;
	u8 valor;

	high = frameAtual->code[++(frameAtual->pc)];
	low = frameAtual->code[++(frameAtual->pc)];
	index = convert_2x8_to_32_bits(low, high);
	classIndex = frameAtual->constantPool[index-1].type.FieldRef.classIndex;
	className = getName(frameAtual->class, frameAtual->constantPool[classIndex-1].type.Class.nameIndex);
	nameTypeIndex = frameAtual->constantPool[index-1].type.FieldRef.nameTypeIndex;
	name = getName(frameAtual->class, frameAtual->constantPool[nameTypeIndex-1].type.NameType.nameIndex);
	type = getName(frameAtual->class, frameAtual->constantPool[nameTypeIndex-1].type.NameType.descriptorIndex);
	objeto = (struct Object *) pop();

	while((field_index = getFieldIndexByNameAndDesc(className, name, strlen(name), type, strlen(type))) == -1) {
		className = getParentName(getClassByName(className));
	}

	if(field_index == -2) {
		if(type[0] == 'J' || type[0] == 'D') {
			pushU8(0);
		} else {
			push(0);
		}
		frameAtual->pc++;
		return;
	}

	nameIndex = frameAtual->class->fields[field_index].nameIndex;
	if(type[0] == 'J' || type[0] == 'D') {
		valor = getObjectFieldWide(objeto, nameIndex);
		pushU8(valor);
	} else {
		valor_auxiliar = getObjectField(objeto, nameIndex);
		push(valor_auxiliar);
	}
	frameAtual->pc++;
}

void i_putfield() {
	u1 low, high;
	u4 index;
	int32_t classIndex, field_index, nameIndex;
	u2 nameTypeIndex;
	char *className, *name, *type;

	struct Object *objeto;
	u4 valor1, valor2;
	u8 valor;

	high = frameAtual->code[++(frameAtual->pc)];
	low = frameAtual->code[++(frameAtual->pc)];
	index = convert_2x8_to_32_bits(low, high);
	classIndex = frameAtual->constantPool[index-1].type.FieldRef.classIndex;
	className = getName(frameAtual->class, frameAtual->constantPool[classIndex-1].type.Class.nameIndex);
	nameTypeIndex = frameAtual->constantPool[index-1].type.FieldRef.nameTypeIndex;
	name = getName(frameAtual->class, frameAtual->constantPool[nameTypeIndex-1].type.NameType.nameIndex);
	type = getName(frameAtual->class, frameAtual->constantPool[nameTypeIndex-1].type.NameType.descriptorIndex);

	while((field_index = getFieldIndexByNameAndDesc(className, name, strlen(name), type, strlen(type))) == -1) {
		className = getParentName(getClassByName(className));
	}

	if(field_index == -2) {
		if(type[0] == 'J' || type[0] == 'D') {
			pop();
			pop();
		} else {
			pop();
		}
		frameAtual->pc++;
		return;
	}

	nameIndex = frameAtual->class->fields[field_index].nameIndex;
	if(type[0] == 'J' || type[0] == 'D') {
		valor1 = pop();
		valor2 = pop();
		objeto = (struct Object *) pop();
		valor = convert_2x32_to_64_bits(valor1, valor2);
		setObjectFieldWide(objeto, nameIndex, valor);

	} else {
		valor1 = pop();
		objeto = (struct Object *) pop();
		setObjectField(objeto, nameIndex, valor1);
	}
	frameAtual->pc++;
}

void i_invokevirtual()
{
	u4 index, valor_high, valor_low, vU4, array_ref;
	u8 valor;
	u1 low, high;
	int32_t numParams, i, j;
	int32_t classIndex, classIndexTemp;
	u2 nameTypeIndex, method_name_index, method_desc_index;
	char *className, *method_name, *method_desc;
	u4 *fields_tmp;
	float vfloat;

	u1 *bytes;
	u2 length;

	classStructure *class;
	methodInfo *method;


	high = frameAtual->code[++(frameAtual->pc)];
	low = frameAtual->code[++(frameAtual->pc)];

	index = convert_2x8_to_32_bits(low, high);


	classIndexTemp = frameAtual->constantPool[index-1].type.MethodRef.classIndex;

	className = getName(frameAtual->class, frameAtual->constantPool[classIndexTemp-1].type.Class.nameIndex);

	nameTypeIndex = frameAtual->constantPool[index-1].type.MethodRef.nameTypeIndex;

	method_name_index = frameAtual->constantPool[nameTypeIndex-1].type.NameType.nameIndex;
	method_desc_index = frameAtual->constantPool[nameTypeIndex-1].type.NameType.descriptorIndex;

	method_desc = getName(frameAtual->class, method_desc_index);
	method_name = getName(frameAtual->class, method_name_index);

	/* se for print ou println */
	if((strcmp(className, "java/io/PrintStream") == 0)
			&&((strcmp(method_name,"print") == 0) ||(strcmp(method_name,"println") == 0))
	){

		/* LONG */
		if(strstr(method_desc, "J") != NULL){
			valor_low = pop();
			valor_high = pop();
			valor = convert_2x32_to_64_bits(valor_low, valor_high);
			printf("%"PRIi64,(int64_t)valor);

			/* DOUBLE */
		} else if(strstr(method_desc, "D") != NULL) {
			valor_low = pop();
			valor_high = pop();
			valor = convert_2x32_to_64_bits(valor_low, valor_high);
			printf("%.15f", valor);

			/* BOOLEAN */
		} else if(strstr(method_desc, "Z") != NULL) {

			if(pop())
				printf("true");
			else
				printf("false");

			/* CHAR */
		} else if(strstr(method_desc, "C") != NULL) {

			/* ARRAY */
			if(strstr(method_desc, "[C") != NULL){

				array_ref = pop();

				for(i = 0; i < numArrays; i++){
					if(arrayLength[i].ref == array_ref)
						break;
				}

				for(j = 0; j < arrayLength[i].size; j++){
					printf("%c",(int16_t)array_ref +i);
				}

				/* CHAR */
			} else {
				printf("%c",(int16_t)pop());
			}

			/* INTEIRO */
		}else if(strstr(method_desc, "I") != NULL) {
			printf("%"PRIi32,(int32_t)pop());

			/* FLOAT */
		}else if(strstr(method_desc, "F") != NULL) {
			vU4 = pop();
			memcpy(&vfloat, &vU4, sizeof(u4));
			printf("%f", vfloat);

			/* STRING */
		}else if(strstr(method_desc, "Ljava/lang/String") != NULL) {
			vU4 = pop();
			printf("%s",(char *)vU4);

			/* OBJECT */
		}else if(strstr(method_desc, "Ljava/lang/Object") != NULL) {
			printf("%p",(void *)pop());
			/* chamar m�todo toString do object e depois toCharArray()*/
		}

		if(strcmp(method_name,"println") == 0)
			printf("\n");

	} else {

		classIndex = carregarClass(className);
		class = getClassByIndex(classIndex);


		while(class != NULL &&(method = getMethodByNameAndDescIndex(class, frameAtual->class, nameTypeIndex)) == NULL) {
			className = getParentName(class);

			classIndex = carregarClass(className);
			class = getClassByIndex(classIndex);
		}

		if(class == NULL) {
			printf(" Erro: Metodo nao encontrando.\n");
			exit(1);
		}

		numParams = getNumParameters(class , method);

		fields_tmp = calloc(sizeof(u4),numParams+1);
		for(i = numParams; i >= 0; i--) {
			fields_tmp[i] = pop();
		}

		if(((method->accessFlags) & AFNative) || strcmp("println", getName(class, method->nameIndex)) == 0) {
			bytes = class->constantPool[(method->descriptorIndex-1)].type.Utf8.bytes;
			length = class->constantPool[(method->descriptorIndex-1)].type.Utf8.length;

			if(bytes[length-1] == 'D' || bytes[length-1] == 'J') {
				pushU8(0);
			} else if(bytes[length-1] != 'V') {
				push(0);
			}

		} else {
			prepararMetodo(class, method);

			for(i = numParams; i >= 0; i--) {
				frameAtual->fields[i] = fields_tmp[i];
			}

			runMethod();
		}

	}

	frameAtual->pc++;
}

void i_invokespecial()
{
	u4 index;
	u1 low, high;
	int32_t numParams, i;
	int32_t classIndex, classIndexTemp;
	u2 nameTypeIndex;
	char *className;
	u4 *fields_tmp;

	u1 *bytes;
	u2 length;

	classStructure *class;
	methodInfo *method;

	high = frameAtual->code[++(frameAtual->pc)];
	low = frameAtual->code[++(frameAtual->pc)];

	index = convert_2x8_to_32_bits(low, high);


	classIndexTemp = (frameAtual->constantPool[index-1]).type.MethodRef.classIndex;

	className = getName(frameAtual->class,(frameAtual->constantPool[classIndexTemp-1]).type.Class.nameIndex);

	classIndex = carregarClass(className);
	class = getClassByIndex(classIndex);

	nameTypeIndex = ((frameAtual->constantPool[index-1])).type.MethodRef.nameTypeIndex;

	while(class != NULL &&(method = getMethodByNameAndDescIndex(class, frameAtual->class, nameTypeIndex)) == NULL) {
		className = getParentName(class);

		classIndex = carregarClass(className);
		class = getClassByIndex(classIndex);
	}

	if(class == NULL) {
		printf("Metodo nao encontrando.\n");
	}

	numParams = getNumParameters(class , method);

	fields_tmp = calloc(sizeof(u4),numParams+1);
	for(i = numParams; i >= 0; i--) {
		fields_tmp[i] = pop();
	}

	if(method->accessFlags & AFNative) {

		bytes = class->constantPool[(method->descriptorIndex-1)].type.Utf8.bytes;
		length = class->constantPool[(method->descriptorIndex-1)].type.Utf8.length;

		if(bytes[length-1] == 'D' || bytes[length-1] == 'J') {
			pushU8(0);
		} else if(bytes[length-1] != 'V') {
			push(0);
		}

	} else {
		prepararMetodo(class, method);

		for(i = numParams; i >= 0; i--) {
			frameAtual->fields[i] = fields_tmp[i];
		}

		runMethod();
	}

	frameAtual->pc++;
}

void i_invokestatic(){

	u4 index;
	u1 low, high;
	int32_t numParams, i;
	int32_t classIndex, classIndexTemp;
	u2 nameTypeIndex;
	char *className;
	u4 *fields_tmp;

	u1 *bytes;
	u2 length;

	classStructure *class;
	methodInfo *method;

	high = frameAtual->code[++(frameAtual->pc)];
	low = frameAtual->code[++(frameAtual->pc)];

	index = convert_2x8_to_32_bits(low, high);


	classIndexTemp = frameAtual->constantPool[index-1].type.MethodRef.classIndex;

	className = getName(frameAtual->class, frameAtual->constantPool[classIndexTemp-1].type.Class.nameIndex);

	nameTypeIndex = frameAtual->constantPool[index-1].type.MethodRef.nameTypeIndex;

	classIndex = carregarClass(className);
	class = getClassByIndex(classIndex);

	method = getMethodByNameAndDescIndex(class, frameAtual->class, nameTypeIndex);

	numParams = getNumParameters(class , method);

	fields_tmp = calloc(sizeof(u4),numParams+1);
	for(i = numParams-1; i >= 0; i--) { /* �nica diferen�a pra invokespecial */
		index = pop();
		fields_tmp[i] = index;
	}

	if(method->accessFlags & AFNative) {

		bytes = class->constantPool[(method->descriptorIndex-1)].type.Utf8.bytes;
		length = class->constantPool[(method->descriptorIndex-1)].type.Utf8.length;

		if(bytes[length-1] == 'D' || bytes[length-1] == 'J') {
			pushU8(0);
		} else if(bytes[length-1] != 'V') {
			push(0);
		}

	} else {
		prepararMetodo(class, method);

		for(i = numParams-1; i >= 0; i--) {
			frameAtual->fields[i] = fields_tmp[i];
		}

		runMethod();
	}

	frameAtual->pc++;
}

void i_invokeinterface()
{
	u4 index;
	u1 low, high, args_count, zero;
	int32_t classIndex, classIndexTemp, i;
	u2 nameTypeIndex;
	char *className;
	u4 *fields_tmp;

	classStructure *class;
	methodInfo *method;

	high = frameAtual->code[++(frameAtual->pc)];
	low = frameAtual->code[++(frameAtual->pc)];
	index = convert_2x8_to_32_bits(low, high);

	args_count = frameAtual->code[++(frameAtual->pc)];
	zero = frameAtual->code[++(frameAtual->pc)];

	/* pega da pilha os argumentos e o objectref */
	fields_tmp = calloc(sizeof(u4),args_count+1);
	for(i = args_count; i >= 0; i--) {
		fields_tmp[i] = pop();
	}

	classIndexTemp = frameAtual->constantPool[index-1].type.MethodRef.classIndex;

	className = getName(frameAtual->class, frameAtual->constantPool[classIndexTemp-1].type.Class.nameIndex);

	classIndex = carregarClass(className);
	class = getClassByIndex(classIndex);

	nameTypeIndex = (frameAtual->constantPool[index-1].type.MethodRef.nameTypeIndex);

	while(class != NULL &&(method = getMethodByNameAndDescIndex(class, frameAtual->class, nameTypeIndex)) == NULL) {
		className = getParentName(class);

		classIndex = carregarClass(className);
		class = getClassByIndex(classIndex);
	}

	if(class == NULL) {
		printf("Metodo nao encontrando.\n");
	}

	/* Prepara e executa o metodo */
	prepararMetodo(class, method);

	for(i = args_count; i >= 0; i--) {
		frameAtual->fields[i] = fields_tmp[i];
	}

	runMethod();

	frameAtual->pc++;
}

void i_new()
{
	u1 low, high;
	u4 index;
	char *className;
	int32_t classIndex;
	classStructure *class;
	struct Object *objeto;

	high = frameAtual->code[++(frameAtual->pc)];
	low = frameAtual->code[++(frameAtual->pc)];

	index = convert_2x8_to_32_bits(low, high);

	className = getName(frameAtual->class, frameAtual->constantPool[index-1].type.Class.nameIndex);

	classIndex = carregarClass(className);
	class = getClassByIndex(classIndex);

	objeto = newObject(class);

	push((u4)objeto);

	frameAtual->pc++;
}

void i_newarray(){

	u4 count;
	u1 type;

	count = pop();
	frameAtual->pc++;
	type = frameAtual->code[frameAtual->pc];

	if(count < 0) {
		printf("Erro: Tamanho invalido do array\n");
	}

	push((u4)newArray(count, type));

	frameAtual->pc++;
}

void i_anewarray(){

	/* algumas coisas est�o comentadas pq provavelmente
	 * n�o s�o necess�rias  */

	u4 count;
	/*u2 index;
	u1 type;*/

	count = pop();

	frameAtual->pc++;
	/*index = current_frame->code[current_frame->pc];
	index = index << 8;*/

	frameAtual->pc++;
	/*index = index | current_frame->code[current_frame->pc];*/

	if(count < 0) {
		printf("Erro: Tamanho invalido do array\n");
	}

	push((u4)newArray(count, 0));

	frameAtual->pc++;

}

void i_arraylength()
{
	int i;

	u4 aref;

	aref = pop();

	for(i = 0; i < numArrays; i++)
	{
		if(arrayLength[i].ref == aref)
		{
			push(arrayLength[i].ref);
			frameAtual->pc++;
			return;
		}

		frameAtual->pc++;
	}

	push(0);

	frameAtual->pc++;
}

void i_athrow(){ frameAtual->pc++;  } /* N�o precisa fazer nada al�m disso */

void i_checkcast()
{
	struct Object *ref;
	u2 index;

	frameAtual->pc++;
	index = frameAtual->code[frameAtual->pc];
	index = index << 8;
	frameAtual->pc++;
	index = index | frameAtual->code[frameAtual->pc];

	ref = (struct Object *)pop();

	if(ref == NULL) {
		printf("Erro: Referencia nula\n");
	}


	if(strcmp(getName(frameAtual->class, index), getClassName(ref->this)) == 0)
	{
		printf(" Erro: Objeto do tipo errado\n");
	}


	push((u4)ref);
	frameAtual->pc++;
}

void i_instanceof(){
	struct Object *ref;
	u2 index;

	frameAtual->pc++;
	index = frameAtual->code[frameAtual->pc];
	index = index << 8;
	frameAtual->pc++;
	index = index | frameAtual->code[frameAtual->pc];

	ref = (struct Object *)pop();

	if(ref == NULL) {
		printf("Erro: Referencia nula\n");
	}

	if(strcmp(getName(frameAtual->class, index), getClassName(ref->this)) == 0)
	{
		push(1);
		frameAtual->pc++;
		return;
	}

	push(0);
	frameAtual->pc++;
}

void i_monitorenter(){ pop(); frameAtual->pc++;  } /* s� precisa disso */

void i_monitorexit(){ pop(); frameAtual->pc++;  } /* s� precisa disso */

void i_wide(){

	next_is_wide = 1;

	frameAtual->pc++;
}

void i_multianewarray()
{
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

	index = ((indexbyte1 & 0xFF) << 8) |(indexbyte2 & 0xFF);



	dimension = pop();
	arrayref = newArray(dimension, TYPE_reference);
	array_type = getName(frameAtual->class, frameAtual->constantPool[index -1].type.Class.nameIndex);

	i = 0;
	while(array_type[i] == '[')
		i++;
	switch(array_type[i])
	{
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
	for(i = 0; i < dimensions; i++)
	{
		size = pop();
		if(size == 0)
			break;

		if(atype == 1)
			((u1**)arrayref)[i] = (u1*)newArray(type, size);
		else if(atype == 2)
			((u2**)arrayref)[i] = (u2*)newArray(type, size);
		else if(atype == 4)
			((u4**)arrayref)[i] = (u4*)newArray(type, size);
		else
			((u8**)arrayref)[i] = (u8*)newArray(type, size);

	}

	push((u4)arrayref);

	frameAtual->pc++;
}

void i_ifnull()
{
	int32_t auxiliar;
	u4 offset;
	u1 branchbyte1, branchbyte2;

	branchbyte1 = frameAtual->code[(frameAtual->pc)+1];
	branchbyte2 = frameAtual->code[(frameAtual->pc)+2];

	auxiliar = (signed) pop();

	if(auxiliar == CONSTANT_Null)
	{
		offset = convert_2x8_to_32_bits(branchbyte2, branchbyte1);
		frameAtual->pc += offset;

	}
	else
	{
		frameAtual->pc += 3;

	}
}

void i_ifnonnull()
{
	int32_t auxiliar;
	int16_t offset;
	u1 branchbyte1, branchbyte2;

	branchbyte1 = frameAtual->code[(frameAtual->pc)+1];
	branchbyte2 = frameAtual->code[(frameAtual->pc)+2];

	auxiliar = (signed) pop();

	if(auxiliar != CONSTANT_Null)
	{
		offset = (int16_t)convert_2x8_to_32_bits(branchbyte2, branchbyte1);
		frameAtual->pc += offset;

	}
	else
	{
		frameAtual->pc += 3;

	}
}

void i_goto_w()
{
	int32_t offset;
	u4 branchbyte1, branchbyte2, branchbyte3, branchbyte4;

	branchbyte1 = frameAtual->code[(frameAtual->pc)+1];
	branchbyte2 = frameAtual->code[(frameAtual->pc)+2];
	branchbyte3 = frameAtual->code[(frameAtual->pc)+3];
	branchbyte4 = frameAtual->code[(frameAtual->pc)+4];

	offset = (int32_t)(((branchbyte1 & 0xFF)<<24) |((branchbyte2 & 0xFF)<<16) |((branchbyte3 & 0xFF)<<8) |(branchbyte1 & 0xFF));

	frameAtual->pc += offset;

}

void i_jsr_w()
{
	int32_t offset;
	u4 branchbyte1, branchbyte2, branchbyte3, branchbyte4;

	push((frameAtual->pc) + 5);

	branchbyte1 = frameAtual->code[(frameAtual->pc)+1];
	branchbyte2 = frameAtual->code[(frameAtual->pc)+2];
	branchbyte3 = frameAtual->code[(frameAtual->pc)+3];
	branchbyte4 = frameAtual->code[(frameAtual->pc)+4];

	offset = (int32_t)(((branchbyte1 & 0xFF)<<24) |((branchbyte2 & 0xFF)<<16) |((branchbyte3 & 0xFF)<<8) |(branchbyte1 & 0xFF));

	frameAtual->pc += offset;

}

