#ifndef __GUARD_MYSIMPLECOMPUTER
#define __GUARD_MYSIMPLECOMPUTER

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define memsize 100

#define SET(flag,reg) (flag = ((flag) | (1 << (reg))))
#define NOL(flag,reg) (flag = ((flag) & ~(1 << (reg))))
#define VAL(flag,reg) (((flag) >> reg) & 1)


extern int sc_memory[memsize];


extern int sc_flag;

int int_cmp(const void *a, const void *b);
int sc_memoryInit();
int sc_memorySet(int address, int value);
int sc_memoryGet(int address, int *value);
int sc_memorySave(char *file);
int sc_memoryLoad(char *file);
int sc_regInit();
int sc_regSet (int reg, int value);
int sc_regGet(int reg, int *value);
int sc_commandEncode(int command, int operand, int *value);
int sc_commandDecode(int value, int *command, int *operand);

#endif
