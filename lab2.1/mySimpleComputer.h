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
/*extern const int correct_ops[]={
0x10, 0x11, 0x20, 0x21, 0x30, 0x31, 0x32,0x33,
0x40, 0x41, 0x42, 0x43, 0x51, 0x52,0x53, 0x54,
0x55, 0x56, 0x57, 0x58, 0x59,0x60, 0x61, 0x62,
0x63, 0x64, 0x65, 0x66,0x67, 0x68, 0x69, 0x70,
0x71, 0x72, 0x73,0x74, 0x75, 0x76
};
extern const int ops_num;*/

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
