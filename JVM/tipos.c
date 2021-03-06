
#include "tipos.h"

u8 converter2x32To64bits(u4 low, u4 high) {
	u8 value;
	value = high;
	value <<= 32;
	value += low;
	return value;
}

u4 converter2x8To32bits(u4 low, u4 high) {
	u4 value;
	value = high;
	value <<= 8;
	value |= low;
	return value;
}

void converter64bitsTo2x32(u8 value, u4 *low, u4 *high) {
	*high = value >> 32;
	*low = value & 0xffffffff;
}

float converterCast32bitsToFloat(u4 bits) {
	int64_t s, e;
	float m, pot;
	int32_t i, j;
	s = ((bits >> 31) == 0) ? 1 : -1;
	e = ((bits >> 23) & 0xff);
	m = 0;
	for(i = 1; i <= 23; i++) {
		if(((int32_t) bits >> (23 - i)) & 1) {
			pot = 1;
			for(j = 1; j <= i; j++) {
				pot = pot * 2;
			}
			m = m + (1.0 / pot);
		}
	}
	m = m + 1;
	pot = 1;
	if((e-127) > 0) {
		for(j = 1; j <= (e - 127); j++) {
			pot = pot * 2;
		}
	}
	else {
		for(j = 1; j <= -(e - 127); j++) {
			pot = pot / 2;
		}
	}
	return s*m*pot;
}

double convertCast2x32bitsToDouble(u4 low, u4 high) {
	double m, pot;
	int64_t bits, s, e, aux_high;
	int32_t i, j;
	aux_high = high;
	bits = (aux_high << 32) + low;
	s = ((bits >> 63) == 0) ? 1 : -1;
	e = ((bits >> 52) & 0x7ffL);
	m = 0;
	for(i = 1; i <= 52; i++) {
		if((bits >> (52 - i)) & 1)	{
			pot = 1;
			for(j = 1; j <= i; j++) {
				pot = pot * 2;
			}
			m = m + (1.0 / pot);
		}
	}
	m = m + 1;
	pot = 1;
	if((e-1023) > 0) {
		for(j = 1; j <= (e - 1023); j++) {
			pot = pot * 2;
		}
	} else {
		for(j = 1; j <= -(e - 1023); j++) {
			pot = pot / 2;
		}
	}
	return s*m*pot;
}
