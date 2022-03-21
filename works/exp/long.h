#pragma once

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define AMENDMENT 4

typedef struct Long {
	int size;
	int* digits;
	int integer;
} Long;

void print(Long* number) {
	printf("%d.", number->integer);
	int len = number->size;
	int i;
	for(i = 0; i < len / AMENDMENT; ++i) {
		printf("%d", number->digits[i]);
	}
	printf("\n");
}

Long* init(Long* l, int integ, int sz) {
	l->size = sz;
	l->integer = integ;
	void* flag = l->digits = (int*) calloc(sz, sizeof(int));
	if ( !flag ) {
		printf("%s\n", "Error in calloc");
		exit(-1);
	}
	int i;
	for(i = 0; i < sz; ++i) {
		l->digits[i] = 0;
	}
	return l;
}

void assignment(Long* a, Long* b) {
	b->size = a->size;
	b->integer = a->integer;
	b->digits = (int*) calloc(b->size, sizeof(int));
	int i;
	for(i = 0; i < b->size; ++i) {
		b->digits[i] = a->digits[i];
	}
}

void clear(Long* l) {
	l->size = 0;
	free(l->digits);
	l = NULL;
}

void add_one(Long* l) {
        l->integer++;
}

void zero_long(Long* number) {
	number->integer = 0;
	int i;
	int sz = number->size;
	for(i = 0; i < sz; ++i) {
		number->digits[i] = 0;
	}
}

int minimum(int a, int b);

int compare_long(Long* a, Long* b) {	//a > b => 1, a < b => -1, a = b => 0
	if ( a->integer > b->integer ) {
		return 1;
	}
	else if ( b->integer > a->integer ) {
		return -1;
	}
	int sz = minimum(a->size, b->size);
	int i;
	for(i = 0; i < sz; ++i) {
		if ( a->digits[i] > b->digits[i] ) {
			return 1;
       		}
        	else if ( b->digits[i] > a->digits[i] ) {
                	return -1;
        	}
	}
	if ( a->size == b->size ) {
		return 0;
	}
	else if ( a->size > b->size ) {
		for(i = sz; i < a->size; ++i) {
			if ( a->digits[i] > 0 ) {
				return 1;
			}
		}
		return 0;
	}
	else if ( a->size < b->size ) {
		for(i = sz; i < b->size; ++i) {
			if ( b->digits[i] > 0 ) {
				return -1;
			}
		}
		return 0;
	}
}

int maximum(int a, int b) {
	if ( a > b ) {
		return a;
	}
	return b;
}

int minimum(int a, int b) {
        if ( a < b ) {
                return a;
        }
        return b;
}
void add(Long* left, Long* right, Long* result) { //result.size = max(a.size, b.size)
	int max = maximum(left->size, right->size);
	result->size = max;
	result->integer = left->integer + right->integer;
	int i;
	for(i = 0; i < max; ++i) {
		if ( i >= left->size ) {
			result->digits[i] = right->digits[i];
		}
		else if ( i >= right->size ) {
			result->digits[i] = left->digits[i];
		}
		else {
			result->digits[i] = left->digits[i] + right->digits[i];
		}
	}
	for(i = max - 1; i >= 1; i--) {
		if ( result->digits[i] > 9 ) {
			result->digits[i] %= 10;
			result->digits[i - 1]++;
		}
	}
	if ( result->digits[0] > 9 ) {
                result->digits[0] %= 10;
                result->integer++;
        }
	while ( result->digits[max - 1] == 0 ) {
                max--;
        }
        result->size = max;
}

void mul(Long* left, Long* right, Long* result) { // result.size = a.size + b.size + 1
	int l_sz = left->size;
	int r_sz = right->size;
	int sz = result->size;
	int ix, jx, i;
	result->integer = left->integer * right->integer;
	for(ix = 0; ix < l_sz; ++ix) {
		for(jx = 0; jx < r_sz; ++jx) {
			result->digits[ix + jx - 1] += left->digits[ix] * right->digits[jx];
		}
	}
	for(i = sz - 1; i >= 1; i--) {
                if ( result->digits[i] > 9 ) {
                        result->digits[i] %= 10;
                        result->digits[i - 1]++;
                }
        }
        if ( result->digits[0] > 9 ) {
                result->digits[0] %= 10;
                result->integer++;
        }
	while ( result->digits[sz] == 0 ) {
		sz--;
	}
	result->size = sz;
}

void divide(int x, Long* result) { // result = 1 / x, result.size = anything
	if ( x == 0 ) {
		fprintf(stderr, "ERROR, divide 0\n");
		return;
	}
	result->integer = 0;
	int i;
	int sz = result->size;
	int a = 10;
	int mod = -1;
	for(i = 0; i < sz; ++i) {
		if ( a == 0 ) {
			break;
		}
		if ( a < x ) {
			a *= 10;
		}
		else {
			result->digits[i] = a / x;
			a %= x;
			a *= 10;
		}
	}
}

void divide_long(int x, Long* result) {
	int i;
	int sz = result->size;
	for(i = 0; i < sz; ++i) {
		if ( i >= 0 ) {
			result->digits[i + 1] += ( result->digits[i] % x ) * 10;
		}
		result->digits[i] /= x;
	}
}

