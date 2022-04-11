/*
	Author: A. S. Miller
*/
#ifndef PREFIX_H
#define PREFIX_H
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

/*
	Base address is held as unsigned 32 bit int
	instead of 4 element char array, because
	comparisons for searching will be faster 
	than per-element array comparison.
*/
typedef struct Prefix {
	uint32_t base;
	uint8_t mask;
	struct Prefix* next;
} Prefix;

// as per task requirements
int add(unsigned int base, char mask);
int del(unsigned int base, char mask);
char check(unsigned int ip);
// for tests and debugging
void ddec(uint32_t);
void list();

#endif
