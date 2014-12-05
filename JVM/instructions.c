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

//extern opcode_informacao *op_info;


void execute_instruction(u1 opcode) {
	instrucao[opcode]();
}


void  iniciarInstrucoes()
{
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
	push ( CONSTANT_Null );
	frameAtual->pc++;
}

void i_iconst_m1() {
	push( -1 );

	frameAtual->pc++;
}

void i_iconst_0()
{
	push( 0 );

	frameAtual->pc++;
}

void i_iconst_1()
{
	push( 1 );

	frameAtual->pc++;
}

void i_iconst_2()
{
	push( 2 );

	frameAtual->pc++;
}

void i_iconst_3()
{
	push( 3 );

	frameAtual->pc++;
}

void i_iconst_4()
{
	push( 4 );

	frameAtual->pc++;
}

void i_iconst_5()
{
	push( 5 );

	frameAtual->pc++;
}

void i_lconst_0()
{
	push (0);
	push (0);

	frameAtual->pc++;
}

void i_lconst_1()
{
	push (0);
	push (1);

	frameAtual->pc++;
}

void i_fconst_0()
{
	u4 *aux;
	float f = 0.0;

	aux = (u4*) malloc(sizeof(u4));
	memcpy(aux, &f, sizeof(u4));

	push(*aux); /* Para recuperar o valor, deve-se fazer outro memcpy para um float */

	frameAtual->pc++;
}

void i_fconst_1()
{
	u4 *aux;
	float f = 1.0;

	aux = (u4*) malloc(sizeof(u4));
	memcpy(aux, &f, sizeof(u4));

	push(*aux); /* Para recuperar o valor, deve-se fazer outro memcpy para um float */

	frameAtual->pc++;
}

void i_fconst_2()
{
	u4 *aux;
	float f = 2.0;

	aux = (u4*) malloc(sizeof(u4));
	memcpy(aux, &f, sizeof(u4));

	push(*aux); /* Para recuperar o valor, deve-se fazer outro memcpy para um float */

	frameAtual->pc++;
}

void i_dconst_0()
{
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
		memcpy(&x, &high, sizeof(u4) );
		memcpy(&y, &aux_4, sizeof(u4) );
		x <<= 32;
		x |= y;
		memcpy(&d, &x, 2*sizeof(u4));
	 */
}

void i_dconst_1()
{
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

void i_bipush()
{
	int8_t aux = (int8_t) frameAtual->code[(++frameAtual->pc)];

	push( (u4)aux );

	frameAtual->pc++;
}

void i_sipush()
{
	u1 low, high;
	int16_t aux;

	frameAtual->pc++;
	high = frameAtual->code[frameAtual->pc];
	frameAtual->pc++;
	low = frameAtual->code[frameAtual->pc];

	aux = (int16_t)convert_2x8_to_32_bits( low, high );
	push( (u4)aux );

	frameAtual->pc++;
}

void i_ldc()
{
	u1 indice, tag;
	u2 stringIndex;

	frameAtual->pc++;
	indice = frameAtual->code[frameAtual->pc];

	tag = frameAtual->constantPool[indice-1].tag;

	switch(tag)
	{
	case (CONSTANT_Integer):
		push(frameAtual->constantPool[indice-1].type.Integer.bytes);
		break;
	case (CONSTANT_Float):
		push(frameAtual->constantPool[indice-1].type.Float.bytes);
		break;
	case (CONSTANT_String):
		stringIndex = frameAtual->constantPool[indice-1].type.String.stringIndex;
		push ((u4)getName(frameAtual->class, stringIndex) );
		break;
	}

	frameAtual->pc++;
}

void i_ldc_w()
{
	u1 tag;
	u4 indice;
	u4 high, low;
	u2 stringIndex;

	frameAtual->pc++;
	high = frameAtual->code[frameAtual->pc];

	frameAtual->pc++;
	low = frameAtual->code[frameAtual->pc];

	indice = convert_2x8_to_32_bits( low, high );

	tag = frameAtual->constantPool[indice-1].tag;

	switch(tag)
	{
	case (CONSTANT_Integer):
									push (frameAtual->constantPool[indice-1].type.Integer.bytes);
	break;
	case (CONSTANT_Float):
									push (frameAtual->constantPool[indice-1].type.Float.bytes);
	break;
	case (CONSTANT_String):
									stringIndex = frameAtual->constantPool[indice-1].type.String.stringIndex;
	push ( (u4)getName(frameAtual->class, stringIndex) );
	break;
	}

	frameAtual->pc++;
}

void i_ldc2_w()
{
	u1 tag;
	u4 indice;
	u4 high, low;

	frameAtual->pc++;
	high = frameAtual->code[frameAtual->pc];

	frameAtual->pc++;
	low = frameAtual->code[frameAtual->pc];

	indice = convert_2x8_to_32_bits( low, high );

	tag = ( frameAtual->constantPool[indice-1]).tag;

	switch(tag)
	{
	case (CONSTANT_Long):
		push(frameAtual->constantPool[indice-1].type.Long.highBytes);
		push(frameAtual->constantPool[indice-1].type.Long.lowBytes);
		break;
	case (CONSTANT_Double):
		push(frameAtual->constantPool[indice-1].type.Double.highBytes);
		push(frameAtual->constantPool[indice-1].type.Double.lowBytes);
		break;
	}

	frameAtual->pc++;
}

void i_iload()
{

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

void i_lload()
{
	u2 index = 0;

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


void i_fload()
{

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

void i_dload()
{

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

void i_aload()
{

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

void i_iload_0()
{
	push( frameAtual->fields[0] );

	frameAtual->pc++;
}

void i_iload_1()
{
	push( frameAtual->fields[1] );

	frameAtual->pc++;
}

void i_iload_2()
{
	push( frameAtual->fields[2] );

	frameAtual->pc++;
}

void i_iload_3()
{
	push( frameAtual->fields[3] );

	frameAtual->pc++;
}

void i_lload_0()
{

	push( frameAtual->fields[0] );
	push( frameAtual->fields[1] );

	frameAtual->pc++;
}

void i_lload_1()
{
	push( frameAtual->fields[1] );
	push( frameAtual->fields[2] );

	frameAtual->pc++;
}

void i_lload_2()
{
	push( frameAtual->fields[2] );
	push( frameAtual->fields[3] );

	frameAtual->pc++;
}

void i_lload_3()
{
	push( frameAtual->fields[3] );
	push( frameAtual->fields[4] );

	frameAtual->pc++;
}

void i_fload_0()
{
	push( frameAtual->fields[0] );

	frameAtual->pc++;
}

void i_fload_1()
{
	push( frameAtual->fields[1] );

	frameAtual->pc++;
}

void i_fload_2()
{
	push( frameAtual->fields[2] );

	frameAtual->pc++;
}

void i_fload_3()
{
	push( frameAtual->fields[3] );

	frameAtual->pc++;
}


void i_dload_0()
{
	push( frameAtual->fields[0] );
	push( frameAtual->fields[1] );

	frameAtual->pc++;
}

void i_dload_1()
{
	push( frameAtual->fields[1] );
	push( frameAtual->fields[2] );

	frameAtual->pc++;
}
void i_dload_2()
{
	push( frameAtual->fields[2] );
	push( frameAtual->fields[3] );

	frameAtual->pc++;
}

void i_dload_3()
{
	push( frameAtual->fields[3] );
	push( frameAtual->fields[4] );

	frameAtual->pc++;
}

void i_aload_0()
{
	push( frameAtual->fields[0] );
	frameAtual->pc++;
}

void i_aload_1()
{
	push( frameAtual->fields[1] );

	frameAtual->pc++;
}

void i_aload_2()
{
	push( frameAtual->fields[2] );

	frameAtual->pc++;
}

void i_aload_3()
{
	push( frameAtual->fields[3] );

	frameAtual->pc++;
}

void i_iaload()
{

	u4 index;
	void *ref;

	index = pop();
	ref = (void *)pop();

	push( ((u4 *)ref)[index]);

	frameAtual->pc++;
}

void i_laload()
{

	u4 index;
	void *ref;

	index = pop();
	ref = (void *)pop();

	pushU8(((u8 *)ref)[index]);

	frameAtual->pc++;
}

void i_faload()
{

	u4 index, res;
	void *ref;

	index = pop();
	ref = (void *)pop();

	memcpy(&res, &((float *)ref)[index], sizeof(u4));
	push(res);

	frameAtual->pc++;
}

void i_daload()
{

	u4 index;
	void *ref;

	index = pop();
	ref = (void *)pop();

	pushU8(((u8 *)ref)[index]);

	frameAtual->pc++;
}

void i_aaload()
{

	u4 index;
	void *ref;

	index = pop();
	ref = (void *)pop();

	push( ((u4 *)ref)[index]);

	frameAtual->pc++;
}

void i_baload()
{

	u4 index;
	void *ref;

	index = pop();
	ref = (void *)pop();

	push((u4)( ((u1*)ref)[index] ));

	frameAtual->pc++;
}

void i_caload()
{

	u4 index;
	void *ref;

	index = pop();
	ref = (void *)pop();

	push((u4)( ((u2*)ref)[index] ));

	frameAtual->pc++;

}

void i_saload()
{

	u4 index;
	void *ref;

	index = pop();
	ref = (void *)pop();

	push((u4)( ((u2*)ref)[index] ));

	frameAtual->pc++;

}

void i_istore()
{
	u2 index;
	u4 value;

	frameAtual->pc++;
	index = frameAtual->code[frameAtual->pc];

	value = pop();

	frameAtual->fields[index] = value;

	frameAtual->pc++;
}

void i_lstore()
{
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

void i_fstore()
{
	u2 index;
	u4 value;

	frameAtual->pc++;
	index = frameAtual->code[frameAtual->pc];

	value = pop();

	frameAtual->fields[index] = value;

	frameAtual->pc++;
}

void i_dstore()
{
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

void i_astore()
{
	u2 index;
	u4 value;

	frameAtual->pc++;
	index = frameAtual->code[frameAtual->pc];

	value = pop();

	frameAtual->fields[index] = value;

	frameAtual->pc++;
}

void i_istore_0()
{
	u4 value;

	value = pop();

	frameAtual->fields[0] = value;

	frameAtual->pc++;
}

void i_istore_1()
{
	u4 value;

	value = pop();

	frameAtual->fields[1] = value;

	frameAtual->pc++;
}

void i_istore_2()
{
	u4 value;

	value = pop();

	frameAtual->fields[2] = value;

	frameAtual->pc++;
}

void i_istore_3()
{
	u4 value;

	value = pop();

	frameAtual->fields[3] = value;

	frameAtual->pc++;
}

void i_lstore_0()
{
	u4 high, low;

	low = pop();
	high = pop();

	frameAtual->fields[0] = high;
	frameAtual->fields[1] = low;

	frameAtual->pc++;
}

void i_lstore_1()
{
	u4 high, low;

	low = pop();
	high = pop();

	frameAtual->fields[1] = high;
	frameAtual->fields[2] = low;

	frameAtual->pc++;
}

void i_lstore_2()
{
	u4 high, low;

	low = pop();
	high = pop();

	frameAtual->fields[2] = high;
	frameAtual->fields[3] = low;

	frameAtual->pc++;
}

void i_lstore_3()
{
	u4 high, low;

	low = pop();
	high = pop();

	frameAtual->fields[3] = high;
	frameAtual->fields[4] = low;

	frameAtual->pc++;
}

void i_fstore_0()
{
	u4  value;

	value = pop();

	frameAtual->fields[0] = value;

	frameAtual->pc++;
}

void i_fstore_1()
{
	u4 value;

	value = pop();

	frameAtual->fields[1] = value;

	frameAtual->pc++;
}

void i_fstore_2()
{
	u4 value;

	value = pop();

	frameAtual->fields[2] = value;

	frameAtual->pc++;
}

void i_fstore_3()
{
	u4 value;

	value = pop();

	frameAtual->fields[3] = value;

	frameAtual->pc++;
}

void i_dstore_0()
{
	u4 high, low;

	low = pop();
	high = pop();

	frameAtual->fields[0] = low;
	frameAtual->fields[1] = high;

	frameAtual->pc++;
}

void i_dstore_1()
{
	u4 high, low;

	low = pop();
	high = pop();

	frameAtual->fields[1] = low;
	frameAtual->fields[2] = high;

	frameAtual->pc++;
}

void i_dstore_2()
{
	u4 high, low;

	low = pop();
	high = pop();

	frameAtual->fields[2] = low;
	frameAtual->fields[3] = high;

	frameAtual->pc++;
}

void i_dstore_3()
{
	u4 high, low;

	low = pop();
	high = pop();

	frameAtual->fields[3] = low;
	frameAtual->fields[4] = high;

	frameAtual->pc++;
}

void i_astore_0()
{
	u4 value;

	value = pop();

	frameAtual->fields[0] = value;

	frameAtual->pc++;
}

void i_astore_1()
{
	u4 value;

	value = pop();

	frameAtual->fields[1] = value;

	frameAtual->pc++;
}

void i_astore_2()
{
	u4 value;

	value = pop();

	frameAtual->fields[2] = value;

	frameAtual->pc++;
}

void i_astore_3()
{
	u4 value;

	value = pop();

	frameAtual->fields[3] = value;

	frameAtual->pc++;
}

void i_iastore()
{

	u4 index, value;
	void *ref;

	value = pop();
	index = pop();
	ref = (void *)pop();

	((u4 *)ref)[index] = value;

	frameAtual->pc++;
}

void i_lastore()
{

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

void i_fastore()
{

	u4 index, value;
	void *ref;

	value = pop();
	index = pop();
	ref = (void *)pop();

	((u4 *)ref)[index] = value;

	frameAtual->pc++;
}

void i_dastore()
{

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

void i_aastore()
{

	u4 index, value;
	void *ref;

	value = pop();
	index = pop();
	ref = (void *)pop();

	((u4 *)ref)[index] = value;

	frameAtual->pc++;
}

void i_bastore()
{

	u4 index, value;
	void *ref;

	value = pop();
	index = pop();
	ref = (void *)pop();

	((u1 *)ref)[index] = (u1)value;

	frameAtual->pc++;
}

void i_castore()
{

	u4 index, value;
	void *ref;

	value = pop();
	index = pop();
	ref = (void *)pop();

	((u2 *)ref)[index] = (u2)value;

	frameAtual->pc++;
}

void i_sastore()
{

	u4 index, value;
	void *ref;

	value = pop();
	index = pop();
	ref = (void *)pop();

	((u2 *)ref)[index] = (u2)value;

	frameAtual->pc++;
}

void i_pop()
{
	pop();

	frameAtual->pc++;
}

void i_pop2()
{
	pop();
	pop();

	frameAtual->pc++;
}

void i_dup()
{
	u4 aux;

	aux = pop();
	push(aux);
	push(aux);

	frameAtual->pc++;
}

void i_dup_x1()
{
	u4 aux1, aux2;

	aux1 = pop();
	aux2 = pop();

	push(aux1);
	push(aux2);
	push(aux1);

	frameAtual->pc++;
}

void i_dup_x2()
{
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

void i_dup2()
{
	u4 value1, value2;

	value1 = pop();
	value2 = pop();

	push(value2);
	push(value1);
	push(value2);
	push(value1);

	frameAtual->pc++;
}

void i_dup2_x1()
{
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
void i_dup2_x2()
{
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


void i_swap()
{
	u4 aux1, aux2;

	aux1 = pop();
	aux2 = pop();

	push(aux1);
	push(aux2);

	frameAtual->pc++;
}

void i_iadd()
{
	u4 aux1, aux2;

	aux1 = pop();
	aux2 = pop();

	push (aux1 + aux2);

	frameAtual->pc++;
}

void i_ladd()
{
	int64_t aux1, aux2;
	u4 low, high;

	low = pop();
	high = pop();
	aux1 = convert_2x32_to_64_bits( low, high );

	low = pop();
	high = pop();
	aux2 = convert_2x32_to_64_bits( low, high );

	pushU8(aux1 + aux2);

	frameAtual->pc++;
}

void i_fadd()
{
	float f1, f2;
	u4 aux1, aux2;

	aux1 = pop();
	memcpy(&f1, &aux1, sizeof(u4));
	aux2 = pop();
	memcpy(&f2, &aux2, sizeof(u4));

	f1 += f2;
	memcpy(&aux1, &f1, sizeof(u4));

	push( aux1 );

	frameAtual->pc++;
}

void i_dadd()
{
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

void i_isub()
{
	u4 aux1, aux2;

	aux1 = pop();
	aux2 = pop();

	push (aux2 - aux1);

	frameAtual->pc++;
}

void i_lsub()
{
	int64_t aux1, aux2;
	u4 low, high;

	low = pop();
	high = pop();
	aux1 = (signed)convert_2x32_to_64_bits( low, high );

	low = pop();
	high = pop();
	aux2 = (signed)convert_2x32_to_64_bits( low, high );


	pushU8(aux2 - aux1);

	frameAtual->pc++;
}

void i_fsub()
{
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

void i_dsub()
{
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

void i_imul()
{
	int32_t value1, value2;

	value1 = (int32_t)pop();
	value2 = (int32_t)pop();

	push((u4)(value1 * value2));

	frameAtual->pc++;
}

void i_lmul()
{
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

void i_fmul()
{
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

void i_dmul()
{
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

	pushU8( value );

	frameAtual->pc++;
}

void i_idiv()
{
	int32_t value1, value2;

	value2 = (int32_t)pop();
	value1 = (int32_t)pop();

	push(value1 / value2);

	frameAtual->pc++;
}

void i_ldiv()
{
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

void i_fdiv()
{
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

void i_ddiv()
{
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
	pushU8( aux );

	frameAtual->pc++;
}

void i_irem()
{
	u4 value1, value2;

	value2 = pop();
	value1 = pop();

	push( value1 % value2 );

	frameAtual->pc++;

}

void i_lrem()
{
	int64_t aux1, aux2;
	u4 low, high;

	low = pop();
	high = pop();
	aux2 = (signed) convert_2x32_to_64_bits( low , high );

	low = pop();
	high = pop();
	aux1 = (signed) convert_2x32_to_64_bits( low , high );

	aux1 = aux1 % aux2;

	push( (u8)aux1 );

	frameAtual->pc++;
}

void i_frem()
{
	float f1, f2;
	u4 aux1, aux2;

	aux1 = pop();
	memcpy(&f2, &aux1, sizeof(u4));
	aux2 = pop();
	memcpy(&f1, &aux2, sizeof(u4));

	f1 = fmodf( f1 , f2 );
	memcpy(&aux1, &f1, sizeof(u4));

	push( aux1 );

	frameAtual->pc++;
}

void i_drem()
{
	double d1, d2;
	u4 low, high;
	u8 aux;

	low = pop();
	high = pop();
	aux = convert_2x32_to_64_bits( low , high );
	memcpy(&d2, &aux, sizeof(u8));

	low = pop();
	high = pop();
	aux = convert_2x32_to_64_bits( low , high );
	memcpy(&d1, &aux, sizeof(u8));

	d1 = fmod( d1 , d2 );

	memcpy(&aux, &d1, sizeof(u8));

	pushU8( aux );

	frameAtual->pc++;
}

void i_ineg()
{
	int32_t aux;

	aux = (int32_t) pop();
	aux = -aux;

	push( (u4)aux );

	frameAtual->pc++;
}

void i_lneg()
{
	int64_t aux;
	u4 low, high;

	low = pop();
	high = pop();
	aux = (int64_t) convert_2x32_to_64_bits( low , high );

	aux = -aux;

	pushU8( (u8)aux );

	frameAtual->pc++;
}

void i_fneg()
{
	float f;
	u4 aux;

	aux = pop();
	memcpy(&f, &aux, sizeof(u4));

	f = -f;

	memcpy(&aux, &f, sizeof(u4));
	push( aux );

	frameAtual->pc++;
}

void i_dneg()
{
	double d;
	u4 low, high;
	u8 aux;

	low = pop();
	high = pop();
	aux = convert_2x32_to_64_bits( low , high );
	memcpy(&d, &aux, sizeof(u8));

	d = -d;

	memcpy(&aux, &d, sizeof(u8));
	pushU8( aux );

	frameAtual->pc++;
}

void i_ishl()
{
	u4 mask = 0x1f;  /*... 0001 1111*/
	u4 aux1, aux2;

	aux2 = pop();
	aux2 &= mask;

	aux1 = pop();
	aux1 <<= aux2;

	push( aux1 );

	frameAtual->pc++;
}

void i_lshl()
{
	int64_t aux1;
	u4 mask = 0x3f;  /*... 00011 1111*/
	u4 low, high, aux2;

	aux2 = pop();
	aux2 &= mask;

	low = pop();
	high = pop();
	aux1 = (signed) convert_2x32_to_64_bits( low , high );

	aux1 <<= aux2;

	push( (u8)aux1 );

	frameAtual->pc++;
}

void i_ishr()
{
	u4 mask = 0x1f;  /* ... 0001 1111 */
	u4 aux1, i;
	int32_t aux2;

	aux1 = pop();
	aux1 &= mask;

	aux2 = (int32_t)pop();

	for (i = 0; i < aux1; i++) {
		aux2 /= 2;
	}

	push( (u4)aux2 );

	frameAtual->pc++;
}

void i_lshr()
{
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
	aux3 = (signed) convert_2x32_to_64_bits( low , high );

	/* Verifica qual é o primeiro bit */
	aux4 = aux3 & aux4;

	aux3 >>= aux2;

	if (aux4) {
		aux3 |= aux1;
	}

	push( (u8)aux3 );

	frameAtual->pc++;
}

void i_iushr()
{
	u4 mask = 0x1f;  /* ... 0001 1111 */
	u4 aux1, aux2;

	aux2 = pop();
	aux2 &= mask;

	aux1 = pop();
	aux1 >>= aux2;

	push( aux1 );

	frameAtual->pc++;
}

void i_lushr()
{
	int64_t aux1;
	u4 mask = 0x3f;  /*... 00011 1111*/
	u4 aux2;
	u4 low, high;

	aux2 = pop();
	aux2 &= mask;

	low = pop();
	high = pop();
	aux1 = (signed) convert_2x32_to_64_bits( low , high );

	aux1 >>= aux2;

	pushU8( (u8)aux1 );

	frameAtual->pc++;
}

void i_iand()
{
	u4 aux1, aux2;

	aux1 = pop();
	aux2 = pop();

	aux1 &= aux2;

	push( aux1 );

	frameAtual->pc++;
}

void i_land()
{
	u8 aux1, aux2;
	u4 low, high;

	low = pop();
	high = pop();
	aux1 = convert_2x32_to_64_bits( low , high );

	low = pop();
	high = pop();
	aux2 = convert_2x32_to_64_bits( low , high );

	aux1 &= aux2;

	pushU8( aux1 );

	frameAtual->pc++;
}

void i_ior()
{
	u4 aux1, aux2;

	aux1 = pop();
	aux2 = pop();

	aux1 |= aux2;

	push( aux1 );

	frameAtual->pc++;
}

void i_lor()
{
	u8 aux1, aux2;
	u4 low, high;

	low = pop();
	high = pop();
	aux1 = convert_2x32_to_64_bits( low , high );

	low = pop();
	high = pop();
	aux2 = convert_2x32_to_64_bits( low , high );

	aux1 |= aux2;

	pushU8( aux1 );

	frameAtual->pc++;
}

void i_ixor()
{
	u4 aux1, aux2;

	aux1 = pop();
	aux2 = pop();

	aux1 ^= aux2;

	push( aux1 );

	frameAtual->pc++;
}

void i_lxor()
{
	u8 aux1, aux2;
	u4 low, high;

	low = pop();
	high = pop();
	aux1 = convert_2x32_to_64_bits( low , high );

	low = pop();
	high = pop();
	aux2 = convert_2x32_to_64_bits( low , high );

	aux1 ^= aux2;

	pushU8( aux1 );

	frameAtual->pc++;
}

void i_iinc()
{
	u1 field_index = frameAtual->code[++(frameAtual->pc)];

	u4 aux = frameAtual->fields[field_index];
	u1 aux2 = frameAtual->code[++(frameAtual->pc)];

	int8_t index = (int8_t) aux;
	int8_t constant = (int8_t) aux2;

	index += constant;

	frameAtual->fields[field_index] = (u4) index;

	frameAtual->pc++;
}

void i_i2l()
{
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

	pushU8( aux2 );

	frameAtual->pc++;
}

void i_i2f()
{
	u4 aux2;
	int32_t aux;
	float f;

	aux = (int32_t)pop();
	f = (float)aux;

	memcpy(&aux2, &f, sizeof(u4));

	push( aux2 );

	frameAtual->pc++;

}

void i_i2d()
{
	double d;
	int32_t aux1;
	u8 aux2;

	aux1 = (int32_t)pop();

	d = (double)aux1;

	memcpy(&aux2, &d, sizeof(u8));

	pushU8( aux2 );

	frameAtual->pc++;

}

void i_l2i()
{
	u4 low, high;

	low = pop();
	high = pop();

	push(low);

	frameAtual->pc++;

}

void i_l2f()
{
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

void i_l2d()
{
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

void i_f2i()
{
	u4 aux;
	float f;

	aux = pop();
	memcpy(&f, &aux, sizeof(u4));

	aux = (u4) f;
	push( aux );

	frameAtual->pc++;

}

void i_f2l()
{
	u4 aux_4;
	u8 aux_8;
	float f;

	aux_4 = pop();
	memcpy(&f, &aux_4, sizeof(u4));

	aux_8 = (u8) f;
	pushU8( aux_8 );

	frameAtual->pc++;

}

void i_f2d()
{
	u4 aux_4;
	u8 aux_8;
	float f;
	double d;

	aux_4 = pop();
	memcpy(&f, &aux_4, sizeof(u4));

	d = (double) f;
	memcpy(&aux_8, &d, 2*sizeof(u4));
	pushU8( aux_8 );

	frameAtual->pc++;

}

void i_d2i()
{
	u4 low, high;
	int32_t resp;
	u8 aux;
	double d;

	low = pop();
	high = pop();
	aux = convert_2x32_to_64_bits(low, high);
	memcpy(&d, &aux, 2*sizeof(u4));

	resp = (int32_t) d;
	push( (u4)resp );

	frameAtual->pc++;

}

void i_d2l()
{
	u4 low, high;
	u8 aux;
	double d;

	low = pop();
	high = pop();
	aux = convert_2x32_to_64_bits(low, high);

	memcpy(&d, &aux, 2*sizeof(u4));
	aux = (u8) d;
	push( aux );

	frameAtual->pc++;

}

void i_d2f()
{
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
	push( resp );

	frameAtual->pc++;

}

void i_i2b()
{
	int8_t aux;
	int32_t aux2;

	aux = (int8_t) pop();
	aux2 = (int32_t)aux;

	push( (u4)aux2 );

	frameAtual->pc++;

}

void i_i2c()
{
	int16_t aux;
	int32_t aux2;

	aux = (int16_t) pop();
	aux2 = (int32_t)aux;

	push( (u4)aux2 );

	frameAtual->pc++;

}

void i_i2s()
{
	int16_t aux;
	int32_t aux2;

	aux = (int16_t) pop();
	aux2 = (int32_t)aux;

	push( (u4)aux2 );

	frameAtual->pc++;

}

void i_lcmp()
{
	int32_t resp;
	u4 low, high;
	u8 aux1, aux2;

	low = pop();
	high = pop();
	aux2 = convert_2x32_to_64_bits(low, high);

	low = pop();
	high = pop();
	aux1 = convert_2x32_to_64_bits(low, high);

	if ( aux1 == aux2 )
		resp = 0;
	else if ( aux1 > aux2 )
		resp = 1;
	else
		resp = -1;

	push((u4) resp);

	frameAtual->pc++;

}

void i_fcmpl()
{
	int32_t resp;
	u4 aux;
	float f1, f2;

	aux = pop();
	memcpy(&f2, &aux, sizeof(u4));

	aux = pop();
	memcpy(&f1, &aux, sizeof(u4));

	if ( f1 == f2 )
		resp = 0;
	else if ( f1 > f2 )
		resp = 1;
	else
		resp = -1;

	push((u4) resp);

	frameAtual->pc++;

}

void i_fcmpg()
{
	int32_t resp;
	u4 aux;
	float f1, f2;

	aux = pop();
	memcpy(&f2, &aux, sizeof(u4));

	aux = pop();
	memcpy(&f1, &aux, sizeof(u4));

	if ( f1 == f2 )
		resp = 0;
	else if ( f1 > f2 )
		resp = 1;
	else
		resp = -1;

	push((u4) resp);

	frameAtual->pc++;

}

void i_dcmpl()
{
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

	if ( d1 == d2 )
		resp = 0;
	else if ( d1 > d2 )
		resp = 1;
	else
		resp = -1;

	push((u4) resp);

	frameAtual->pc++;

}

void i_dcmpg()
{
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

	if ( d1 == d2 )
		resp = 0;
	else if ( d1 > d2 )
		resp = 1;
	else
		resp = -1;

	push((u4) resp);

	frameAtual->pc++;

}

void i_ifeq()
{
	int32_t aux;
	int16_t offset;
	u1 branchbyte1, branchbyte2;

	branchbyte1 = frameAtual->code[(frameAtual->pc)+1];
	branchbyte2 = frameAtual->code[(frameAtual->pc)+2];

	aux = (signed) pop();

	if ( aux == 0 )
	{
		offset = (int16_t)convert_2x8_to_32_bits(branchbyte2, branchbyte1);
		frameAtual->pc += offset;

	}
	else
	{
		frameAtual->pc += 3;

	}
}

void i_ifne()
{
	int32_t aux;
	int16_t offset;
	u1 branchbyte1, branchbyte2;

	branchbyte1 = frameAtual->code[(frameAtual->pc)+1];
	branchbyte2 = frameAtual->code[(frameAtual->pc)+2];

	aux = (signed) pop();

	if ( aux != 0 )
	{
		offset = (int16_t)convert_2x8_to_32_bits(branchbyte2, branchbyte1);
		frameAtual->pc += offset;

	}
	else
	{
		frameAtual->pc += 3;

	}
}

void i_iflt()
{
	int32_t aux;
	int16_t offset;
	u1 branchbyte1, branchbyte2;

	branchbyte1 = frameAtual->code[(frameAtual->pc)+1];
	branchbyte2 = frameAtual->code[(frameAtual->pc)+2];

	aux = (signed) pop();

	if ( aux < 0 )
	{
		offset = (int16_t)convert_2x8_to_32_bits(branchbyte2, branchbyte1);
		frameAtual->pc += offset;

	}
	else
	{
		frameAtual->pc += 3;

	}
}

void i_ifge()
{
	int32_t aux;
	int16_t offset;
	u1 branchbyte1, branchbyte2;

	branchbyte1 = frameAtual->code[(frameAtual->pc)+1];
	branchbyte2 = frameAtual->code[(frameAtual->pc)+2];

	aux = (signed) pop();

	if ( aux >= 0 )
	{
		offset = (int16_t)convert_2x8_to_32_bits(branchbyte2, branchbyte1);
		frameAtual->pc += offset;

	}
	else
	{
		frameAtual->pc += 3;

	}
}

void i_ifgt()
{
	int32_t aux;
	int16_t offset;
	u1 branchbyte1, branchbyte2;

	branchbyte1 = frameAtual->code[(frameAtual->pc)+1];
	branchbyte2 = frameAtual->code[(frameAtual->pc)+2];

	aux = (signed) pop();

	if ( aux > 0 )
	{
		offset = (int16_t)convert_2x8_to_32_bits(branchbyte2, branchbyte1);
		frameAtual->pc += offset;

	}
	else
	{
		frameAtual->pc += 3;

	}
}

void i_ifle()
{
	int32_t aux;
	int16_t offset;
	u1 branchbyte1, branchbyte2;

	branchbyte1 = frameAtual->code[(frameAtual->pc)+1];
	branchbyte2 = frameAtual->code[(frameAtual->pc)+2];

	aux = (signed) pop();

	if ( aux <= 0 )
	{
		offset = (int16_t)convert_2x8_to_32_bits(branchbyte2, branchbyte1);
		frameAtual->pc += offset;

	}
	else
	{
		frameAtual->pc += 3;

	}
}

void i_if_icmpeq()
{
	int32_t aux1, aux2;
	int16_t offset;
	u1 branchbyte1, branchbyte2;

	branchbyte1 = frameAtual->code[(frameAtual->pc)+1];
	branchbyte2 = frameAtual->code[(frameAtual->pc)+2];

	aux1 = (signed) pop();
	aux2 = (signed) pop();

	if ( aux1 == aux2 )
	{
		offset = (int16_t)convert_2x8_to_32_bits(branchbyte2, branchbyte1);
		frameAtual->pc += offset;

	}
	else
	{
		frameAtual->pc += 3;

	}
}

void i_if_icmpne()
{
	int32_t aux1, aux2;
	int16_t offset;
	u1 branchbyte1, branchbyte2;

	branchbyte1 = frameAtual->code[(frameAtual->pc)+1];
	branchbyte2 = frameAtual->code[(frameAtual->pc)+2];

	aux1 = (signed) pop();
	aux2 = (signed) pop();

	if ( aux1 != aux2 )
	{
		offset = (int16_t)convert_2x8_to_32_bits(branchbyte2, branchbyte1);
		frameAtual->pc += offset;

	}
	else
	{
		frameAtual->pc += 3;

	}
}

void i_if_icmplt()
{
	int32_t aux1, aux2;
	int16_t offset;
	u1 branchbyte1, branchbyte2;

	branchbyte1 = frameAtual->code[(frameAtual->pc)+1];
	branchbyte2 = frameAtual->code[(frameAtual->pc)+2];

	aux2 = (signed) pop();
	aux1 = (signed) pop();

	if ( aux1 < aux2 )
	{
		offset = (int16_t)convert_2x8_to_32_bits(branchbyte2, branchbyte1);
		frameAtual->pc += offset;

	}
	else
	{
		frameAtual->pc += 3;

	}
}

void i_if_icmpge()
{
	int32_t aux1, aux2;
	int16_t offset;
	u1 branchbyte1, branchbyte2;

	branchbyte1 = frameAtual->code[(frameAtual->pc)+1];
	branchbyte2 = frameAtual->code[(frameAtual->pc)+2];

	aux2 = (signed) pop();
	aux1 = (signed) pop();

	if ( aux1 >= aux2 )
	{
		offset = (int16_t)convert_2x8_to_32_bits(branchbyte2, branchbyte1);
		frameAtual->pc += offset;

	}
	else
	{
		frameAtual->pc += 3;

	}
}

void i_if_icmpgt()
{
	int32_t aux1, aux2;
	int16_t offset;
	u1 branchbyte1, branchbyte2;

	branchbyte1 = frameAtual->code[(frameAtual->pc)+1];
	branchbyte2 = frameAtual->code[(frameAtual->pc)+2];

	aux2 = (signed) pop();
	aux1 = (signed) pop();

	if ( aux1 > aux2 )
	{
		offset = (int16_t)convert_2x8_to_32_bits(branchbyte2, branchbyte1);
		frameAtual->pc += offset;

	}
	else
	{
		frameAtual->pc += 3;

	}
}

void i_if_icmple()
{
	int32_t aux1, aux2;
	int16_t offset;
	u1 branchbyte1, branchbyte2;

	branchbyte1 = frameAtual->code[(frameAtual->pc)+1];
	branchbyte2 = frameAtual->code[(frameAtual->pc)+2];

	aux2 = (signed) pop();
	aux1 = (signed) pop();

	if ( aux1 <= aux2 )
	{
		offset = (int16_t)convert_2x8_to_32_bits(branchbyte2, branchbyte1);
		frameAtual->pc += offset;

	}
	else
	{
		frameAtual->pc += 3;

	}
}

void i_if_acmpeq()
{
	int32_t aux1, aux2;
	int16_t offset;
	u1 branchbyte1, branchbyte2;

	branchbyte1 = frameAtual->code[(frameAtual->pc)+1];
	branchbyte2 = frameAtual->code[(frameAtual->pc)+2];

	aux2 = (signed) pop();
	aux1 = (signed) pop();

	if ( aux1 == aux2 )
	{
		offset = (int16_t)convert_2x8_to_32_bits(branchbyte2, branchbyte1);
		frameAtual->pc += offset;

	}
	else
	{
		frameAtual->pc += 3;

	}
}

void i_if_acmpne()
{
	int32_t aux1, aux2;
	int16_t offset;
	u1 branchbyte1, branchbyte2;

	branchbyte1 = frameAtual->code[(frameAtual->pc)+1];
	branchbyte2 = frameAtual->code[(frameAtual->pc)+2];

	aux2 = (signed) pop();
	aux1 = (signed) pop();

	if ( aux1 != aux2 )
	{
		offset = (int16_t)convert_2x8_to_32_bits(branchbyte2, branchbyte1);
		frameAtual->pc += offset;

	}
	else
	{
		frameAtual->pc += 3;

	}
}

void i_goto()
{
	int16_t offset;
	u1 branchbyte1, branchbyte2;

	branchbyte1 = frameAtual->code[(frameAtual->pc)+1];
	branchbyte2 = frameAtual->code[(frameAtual->pc)+2];

	offset = (int16_t)convert_2x8_to_32_bits(branchbyte2, branchbyte1);
	frameAtual->pc += offset;

}

void i_jsr()
{
	int16_t offset;
	u1 branchbyte1, branchbyte2;

	push((frameAtual->pc) + 3); /* pc da proxima instrucao */

	branchbyte1 = frameAtual->code[(frameAtual->pc)+1];
	branchbyte2 = frameAtual->code[(frameAtual->pc)+2];

	offset = (int16_t)convert_2x8_to_32_bits(branchbyte2, branchbyte1);
	frameAtual->pc += offset;

}

void i_ret()
{
	u2 index;

	frameAtual->pc++;
	index = frameAtual->code[frameAtual->pc];

	if (next_is_wide == 1){
		index = index << 8;
		frameAtual->pc++;
		index = index | frameAtual->code[frameAtual->pc];
		next_is_wide = 0;
	}

	frameAtual->pc = frameAtual->fields[index];

}

void i_tableswitch()
{
	int32_t default_, high, low, index;
	int32_t *tableswitch;
	u4 byte1, byte2, byte3, byte4, tableswitch_address, target, table_size, i, offset;

	index = (int32_t)pop();
	tableswitch_address = frameAtual->pc;

	/* pula os padding bytes */
	while ((frameAtual->pc + 1) % 4 != 0)
		frameAtual->pc++;
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

	for (i = 0; i < table_size; i++)
	{
		byte1 = frameAtual->code[frameAtual->pc++];
		byte2 = frameAtual->code[frameAtual->pc++];
		byte3 = frameAtual->code[frameAtual->pc++];
		byte4 = frameAtual->code[frameAtual->pc++];

		tableswitch[i] = ((byte1 & 0xFF) << 24) | ((byte2 & 0xFF) << 16) | ((byte3 & 0xFF) << 8) | (byte4 & 0xFF);
	}

	if (index < low || index > high)
		target = tableswitch_address + default_;
	else
	{
		offset = tableswitch[index - low];
		target = tableswitch_address + offset;
	}

	frameAtual->pc = target;
}

void i_lookupswitch()
{
	int32_t default_, npairs, key;
	int32_t *match, *offset;
	u4 byte1, byte2, byte3, byte4, target, lookupswitch_address, i;
	u1 found;

	key = (int32_t)pop();
	lookupswitch_address = frameAtual->pc;

	/* pula os padding bytes */
	while ((frameAtual->pc + 1) % 4 != 0)
		frameAtual->pc++;
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
	for (i = 0; i < npairs; i++)
	{
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
	while ((i < npairs) && (!found))
	{
		if (match[i] == key)
			found = 1;
		i++;
	}
	i--;

	if (found)
		target = offset[i] + lookupswitch_address;
	else
		target = default_ + lookupswitch_address;

	frameAtual->pc = target;
}

void i_ireturn()
{
	u4 value;

	value = pop();

	returnType = RETURN_32bits;
	returnValue = (u8)value;

	frameAtual->pc++;
}

void i_lreturn()
{
	u4 low, high;

	low = pop();
	high = pop();

	returnType = RETURN_64bits;
	returnValue = convert_2x32_to_64_bits(low, high);

	frameAtual->pc++;
}

void i_freturn()
{
	u4 value;

	value = pop();

	returnType = RETURN_32bits;
	returnValue = (u8)value;

	frameAtual->pc++;
}

void i_dreturn()
{
	u4 low, high;

	low = pop();
	high = pop();

	returnType = RETURN_64bits;
	returnValue = convert_2x32_to_64_bits(low, high);

	frameAtual->pc++;
}

void i_areturn()
{
	u4 value;

	value = pop();

	returnType = RETURN_32bits;
	returnValue = (u8)value;

	frameAtual->pc++;
}

void i_return()
{
	returnType = RETURN_none;
	returnValue = 0;

	frameAtual->pc++;
}

void i_getstatic()
{
	u1 index1, index2;
	u2 index, name_type_index;
	u4 class_index_tmp;
	int32_t classIndex, field_index;
	u8 value;
	char *className, *name, *type;


	index1 = (u1) frameAtual->code[++(frameAtual->pc)];
	index2 = (u1) frameAtual->code[++(frameAtual->pc)];

	index = ((u2)index1 << 8) | (u2)index2;

	class_index_tmp = frameAtual->constantPool[index-1].type.FieldRef.classIndex;

	className = getName(frameAtual->class, frameAtual->constantPool[class_index_tmp-1].type.Class.nameIndex);

	name_type_index = frameAtual->constantPool[index-1].type.FieldRef.nameTypeIndex;

	name = getName(frameAtual->class, frameAtual->constantPool[name_type_index-1].type.NameType.nameIndex);
	type = getName(frameAtual->class, frameAtual->constantPool[name_type_index-1].type.NameType.descriptorIndex);

	/* -1 informa que nao encontrou o field na casse corrente */
	while ((field_index = getFieldIndexByNameAndDesc(className, name, strlen(name), type, strlen(type))) == -1) {
		className = getParentName(getClassByName(className));
	}

	/* Verifica se deu algum erro (ou classe nao aceita) ao buscar o field (-2) */
	if (field_index == -2) {

		if (type[0] == 'J' || type[0] == 'D') {
			pushU8( 0 );
		} else {
			push( 0 );
		}

		frameAtual->pc++;
		return;
	}


	classIndex = carregarClass( className );

	value = getStaticFieldValue( classIndex , field_index );

	/* Verifica se eh Double ou Long para saber quantos bits colocar na pilha */
	if (type[0] == 'J' || type[0] == 'D') {
		pushU8( value );
	} else {
		push( (u4)value );
	}

	frameAtual->pc++;
}

void i_putstatic()
{
	u1 index1, index2;
	u2 index, name_type_index;
	u4 class_index_tmp;
	int32_t classIndex, field_index;
	u4 value1, value2;
	u8 value;
	char *className, *name, *type;


	index1 = (u1) frameAtual->code[++(frameAtual->pc)];
	index2 = (u1) frameAtual->code[++(frameAtual->pc)];

	index = ((u2)index1 << 8) | (u2)index2;

	class_index_tmp = frameAtual->constantPool[index-1].type.FieldRef.classIndex;

	className = getName(frameAtual->class, frameAtual->constantPool[class_index_tmp-1].type.Class.nameIndex);

	name_type_index = frameAtual->constantPool[index-1].type.FieldRef.nameTypeIndex;

	name = getName(frameAtual->class, frameAtual->constantPool[name_type_index-1].type.NameType.nameIndex);
	type = getName(frameAtual->class, frameAtual->constantPool[name_type_index-1].type.NameType.descriptorIndex);

	/* -1 informa que nao encontrou o field na casse corrente */
	while ((field_index = getFieldIndexByNameAndDesc(className, name, strlen(name), type, strlen(type))) == -1) {
		className = getParentName(getClassByName(className));
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

		value = convert_2x32_to_64_bits( value1 , value2 );
	} else {
		value = (u8) pop();
	}

	classIndex = carregarClass( className );

	setStaticFieldValue( classIndex , field_index , value );

	frameAtual->pc++;
}

void i_getfield()
{
	u1 low, high;
	u4 index;
	int32_t classIndex, field_index, nameIndex;
	u2 name_type_index;
	char *className, *name, *type;

	struct Object *objeto;
	u4 value_aux;
	u8 value;

	high = frameAtual->code[++(frameAtual->pc)];
	low = frameAtual->code[++(frameAtual->pc)];

	index = convert_2x8_to_32_bits(low, high);


	classIndex = frameAtual->constantPool[index-1].type.FieldRef.classIndex;

	className = getName(frameAtual->class, frameAtual->constantPool[classIndex-1].type.Class.nameIndex);

	name_type_index = frameAtual->constantPool[index-1].type.FieldRef.nameTypeIndex;

	name = getName(frameAtual->class, frameAtual->constantPool[name_type_index-1].type.NameType.nameIndex);
	type = getName(frameAtual->class, frameAtual->constantPool[name_type_index-1].type.NameType.descriptorIndex);

	/* Pega a referencia do objeto que tera o field alterado de valor */
	objeto = (struct Object *) pop();

	/* -1 informa que nao encontrou o field na casse corrente */
	while ((field_index = getFieldIndexByNameAndDesc(className, name, strlen(name), type, strlen(type))) == -1) {
		className = getParentName(getClassByName(className));
	}

	/* Verifica se deu algum erro (ou classe nao aceita) ao buscar o field (-2) */
	if (field_index == -2) {

		if (type[0] == 'J' || type[0] == 'D') {
			pushU8( 0 );
		} else {
			push( 0 );
		}

		frameAtual->pc++;
		return;
	}

	nameIndex = frameAtual->class->fields[field_index].nameIndex;

	/* Pega o valor do field */
	if (type[0] == 'J' || type[0] == 'D') {
		value = getObjectFieldWide(objeto, nameIndex);
		pushU8( value );

	} else {
		value_aux = getObjectField(objeto, nameIndex);
		push( value_aux );
	}

	frameAtual->pc++;
}

void i_putfield()
{
	u1 low, high;
	u4 index;
	int32_t classIndex, field_index, nameIndex;
	u2 name_type_index;
	char *className, *name, *type;

	struct Object *objeto;
	u4 value1, value2;
	u8 value;


	high = frameAtual->code[++(frameAtual->pc)];
	low = frameAtual->code[++(frameAtual->pc)];

	index = convert_2x8_to_32_bits(low, high);


	classIndex = frameAtual->constantPool[index-1].type.FieldRef.classIndex;

	className = getName(frameAtual->class, frameAtual->constantPool[classIndex-1].type.Class.nameIndex);

	name_type_index = frameAtual->constantPool[index-1].type.FieldRef.nameTypeIndex;

	name = getName(frameAtual->class, frameAtual->constantPool[name_type_index-1].type.NameType.nameIndex);
	type = getName(frameAtual->class, frameAtual->constantPool[name_type_index-1].type.NameType.descriptorIndex);

	/* -1 informa que nao encontrou o field na casse corrente */
	while ((field_index = getFieldIndexByNameAndDesc(className, name, strlen(name), type, strlen(type))) == -1) {
		className = getParentName(getClassByName(className));
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


	nameIndex = frameAtual->class->fields[field_index].nameIndex;

	/* Pega o valor a ser colocado no field */
	if (type[0] == 'J' || type[0] == 'D') {
		value1 = pop();
		value2 = pop();

		/* Pega a referencia do objeto que tera o field alterado de valor */
		objeto = (struct Object *) pop();

		value = convert_2x32_to_64_bits(value1, value2);
		setObjectFieldWide(objeto, nameIndex, value);

	} else {
		value1 = pop();

		/* Pega a referencia do objeto que tera o field alterado de valor */
		objeto = (struct Object *) pop();

		setObjectField(objeto, nameIndex, value1);
	}

	frameAtual->pc++;
}

void i_invokevirtual()
{
	u4 index, value_high, value_low, vU4, array_ref;
	u8 value;
	u1 low, high;
	int32_t numParams, i, j;
	int32_t classIndex, class_index_tmp;
	u2 name_type_index, method_name_index, method_desc_index;
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


	class_index_tmp = frameAtual->constantPool[index-1].type.MethodRef.classIndex;

	className = getName(frameAtual->class, frameAtual->constantPool[class_index_tmp-1].type.Class.nameIndex);

	name_type_index = frameAtual->constantPool[index-1].type.MethodRef.nameTypeIndex;

	method_name_index = frameAtual->constantPool[name_type_index-1].type.NameType.nameIndex;
	method_desc_index = frameAtual->constantPool[name_type_index-1].type.NameType.descriptorIndex;

	method_desc = getName(frameAtual->class, method_desc_index);
	method_name = getName(frameAtual->class, method_name_index);

	/* se for print ou println */
	if ( (strcmp(className, "java/io/PrintStream") == 0)
			&& ((strcmp(method_name,"print") == 0) || (strcmp(method_name,"println") == 0) )
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

			if (pop())
				printf("true");
			else
				printf("false");

			/* CHAR */
		} else if(strstr(method_desc, "C") != NULL) {

			/* ARRAY */
			if(strstr(method_desc, "[C") != NULL){

				array_ref = pop();

				for (i = 0; i < numArrays; i++){
					if (arrayLength[i].ref == array_ref)
						break;
				}

				for (j = 0; j < arrayLength[i].size; j++){
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
			/* chamar método toString do object e depois toCharArray()*/
		}

		if (strcmp(method_name,"println") == 0)
			printf("\n");

	} else {

		classIndex = carregarClass( className );
		class = getClassByIndex( classIndex );


		while (class != NULL && (method = getMethodByNameAndDescIndex(class, frameAtual->class, name_type_index)) == NULL) {
			className = getParentName(class);

			classIndex = carregarClass( className );
			class = getClassByIndex( classIndex );
		}

		if (class == NULL) {
			printf(" Erro: Metodo nao encontrando.\n");
			exit(1);
		}

		numParams = getNumParameters( class , method );

		fields_tmp = calloc(sizeof(u4),numParams+1);
		for (i = numParams; i >= 0; i--) {
			fields_tmp[i] = pop();
		}

		if (((method->accessFlags) & ACC_NATIVE) || strcmp("println", getName(class, method->nameIndex)) == 0) {
			bytes = class->constantPool[(method->descriptorIndex-1)].type.Utf8.bytes;
			length = class->constantPool[(method->descriptorIndex-1)].type.Utf8.length;

			if (bytes[length-1] == 'D' || bytes[length-1] == 'J') {
				pushU8( 0 );
			} else if (bytes[length-1] != 'V') {
				push( 0 );
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

void i_invokespecial()
{
	u4 index;
	u1 low, high;
	int32_t numParams, i;
	int32_t classIndex, class_index_tmp;
	u2 name_type_index;
	char *className;
	u4 *fields_tmp;

	u1 *bytes;
	u2 length;

	classStructure *class;
	methodInfo *method;

	high = frameAtual->code[++(frameAtual->pc)];
	low = frameAtual->code[++(frameAtual->pc)];

	index = convert_2x8_to_32_bits(low, high);


	class_index_tmp = (frameAtual->constantPool[index-1]).type.MethodRef.classIndex;

	className = getName(frameAtual->class, (frameAtual->constantPool[class_index_tmp-1]).type.Class.nameIndex);

	classIndex = carregarClass( className );
	class = getClassByIndex( classIndex );

	name_type_index = ((frameAtual->constantPool[index-1])).type.MethodRef.nameTypeIndex;

	while (class != NULL && (method = getMethodByNameAndDescIndex(class, frameAtual->class, name_type_index)) == NULL) {
		className = getParentName(class);

		classIndex = carregarClass( className );
		class = getClassByIndex( classIndex );
	}

	if (class == NULL) {
		printf("Metodo nao encontrando.\n");
	}

	numParams = getNumParameters( class , method );

	fields_tmp = calloc(sizeof(u4),numParams+1);
	for (i = numParams; i >= 0; i--) {
		fields_tmp[i] = pop();
	}

	if (method->accessFlags & ACC_NATIVE) {

		bytes = class->constantPool[(method->descriptorIndex-1)].type.Utf8.bytes;
		length = class->constantPool[(method->descriptorIndex-1)].type.Utf8.length;

		if (bytes[length-1] == 'D' || bytes[length-1] == 'J') {
			pushU8( 0 );
		} else if (bytes[length-1] != 'V') {
			push( 0 );
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

void i_invokestatic(){

	u4 index;
	u1 low, high;
	int32_t numParams, i;
	int32_t classIndex, class_index_tmp;
	u2 name_type_index;
	char *className;
	u4 *fields_tmp;

	u1 *bytes;
	u2 length;

	classStructure *class;
	methodInfo *method;

	high = frameAtual->code[++(frameAtual->pc)];
	low = frameAtual->code[++(frameAtual->pc)];

	index = convert_2x8_to_32_bits(low, high);


	class_index_tmp = frameAtual->constantPool[index-1].type.MethodRef.classIndex;

	className = getName(frameAtual->class, frameAtual->constantPool[class_index_tmp-1].type.Class.nameIndex);

	name_type_index = frameAtual->constantPool[index-1].type.MethodRef.nameTypeIndex;

	classIndex = carregarClass( className );
	class = getClassByIndex( classIndex );

	method = getMethodByNameAndDescIndex(class, frameAtual->class, name_type_index);

	numParams = getNumParameters( class , method );

	fields_tmp = calloc(sizeof(u4),numParams+1);
	for (i = numParams-1; i >= 0; i--) { /* única diferença pra invokespecial */
		index = pop();
		fields_tmp[i] = index;
	}

	if (method->accessFlags & ACC_NATIVE) {

		bytes = class->constantPool[(method->descriptorIndex-1)].type.Utf8.bytes;
		length = class->constantPool[(method->descriptorIndex-1)].type.Utf8.length;

		if (bytes[length-1] == 'D' || bytes[length-1] == 'J') {
			pushU8( 0 );
		} else if (bytes[length-1] != 'V') {
			push( 0 );
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

void i_invokeinterface()
{
	u4 index;
	u1 low, high, args_count, zero;
	int32_t classIndex, class_index_tmp, i;
	u2 name_type_index;
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
	for (i = args_count; i >= 0; i--) {
		fields_tmp[i] = pop();
	}

	class_index_tmp = frameAtual->constantPool[index-1].type.MethodRef.classIndex;

	className = getName(frameAtual->class, frameAtual->constantPool[class_index_tmp-1].type.Class.nameIndex);

	classIndex = carregarClass( className );
	class = getClassByIndex( classIndex );

	name_type_index = (frameAtual->constantPool[index-1].type.MethodRef.nameTypeIndex);

	while (class != NULL && (method = getMethodByNameAndDescIndex(class, frameAtual->class, name_type_index)) == NULL) {
		className = getParentName(class);

		classIndex = carregarClass( className );
		class = getClassByIndex( classIndex );
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

	push( (u4)objeto );

	frameAtual->pc++;
}

void i_newarray(){

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

void i_anewarray(){

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

void i_arraylength()
{
	int i;

	u4 aref;

	aref = pop();

	for (i = 0; i < numArrays; i++)
	{
		if (arrayLength[i].ref == aref)
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

void i_athrow(){ frameAtual->pc++;  } /* Näo precisa fazer nada além disso */

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

	if (ref == NULL) {
		printf("Erro: Referencia nula\n");
	}


	if (strcmp(getName(frameAtual->class, index), getClassName(ref->this)) == 0)
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

	if (ref == NULL) {
		printf("Erro: Referencia nula\n");
	}

	if (strcmp( getName(frameAtual->class, index), getClassName(ref->this)) == 0)
	{
		push(1);
		frameAtual->pc++;
		return;
	}

	push(0);
	frameAtual->pc++;
}

void i_monitorenter(){ pop(); frameAtual->pc++;  } /* só precisa disso */

void i_monitorexit(){ pop(); frameAtual->pc++;  } /* só precisa disso */

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

	index = ((indexbyte1 & 0xFF) << 8) | (indexbyte2 & 0xFF);



	dimension = pop();
	arrayref = newArray(dimension, TYPE_reference);
	array_type = getName(frameAtual->class, frameAtual->constantPool[index -1].type.Class.nameIndex);

	i = 0;
	while (array_type[i] == '[')
		i++;
	switch (array_type[i])
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
	for (i = 0; i < dimensions; i++)
	{
		size = pop();
		if (size == 0)
			break;

		if (atype == 1)
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
	int32_t aux;
	u4 offset;
	u1 branchbyte1, branchbyte2;

	branchbyte1 = frameAtual->code[(frameAtual->pc)+1];
	branchbyte2 = frameAtual->code[(frameAtual->pc)+2];

	aux = (signed) pop();

	if ( aux == CONSTANT_Null )
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
	int32_t aux;
	int16_t offset;
	u1 branchbyte1, branchbyte2;

	branchbyte1 = frameAtual->code[(frameAtual->pc)+1];
	branchbyte2 = frameAtual->code[(frameAtual->pc)+2];

	aux = (signed) pop();

	if ( aux != CONSTANT_Null )
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

	offset = (int32_t)(((branchbyte1 & 0xFF)<<24) | ((branchbyte2 & 0xFF)<<16) | ((branchbyte3 & 0xFF)<<8) | (branchbyte1 & 0xFF));

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

	offset = (int32_t)(((branchbyte1 & 0xFF)<<24) | ((branchbyte2 & 0xFF)<<16) | ((branchbyte3 & 0xFF)<<8) | (branchbyte1 & 0xFF));

	frameAtual->pc += offset;

}

