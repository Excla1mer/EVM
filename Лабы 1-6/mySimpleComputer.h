#include <iostream>
#include <stdio.h>

#define P (0x1 << 0)
#define O (0x1 << 1)
#define M (0x1 << 2)
#define T (0x1 << 3)
#define E (0x1 << 4)

enum COMMANDS {READ = 10, WRITE = 11, LOAD = 20, STORE = 21, \
			   ADD = 30, SUB = 31, DIVIDE = 32, MUL = 33, \
			   JUMP = 40, JNEG = 41, JZ = 42, HALT = 43,  \
			   NOT = 51, AND = 52, OR = 53, XOR = 54, JNS = 55, \
			   JC = 56, JNC = 57, JP = 58, JNP = 59, CHL = 60, \
			   SHR = 61, RCL = 62, \
			   RCR = 63, NEG = 64, ADDC = 65, SUBC = 66,  \
			   LOGLC = 67, LOGRC = 68, RCCL = 69, RCCR = 70, \
			   MOVA = 71, MOVR = 72, MOVCA = 73, MOVCR = 74 \
			  };

const int memSize = 100;
unsigned int sc_memory[memSize];

short int flags;
short int accumulator;
short int icounter = 0;
int comms[37];

void sc_memoryInit ()
{
	for (int i=0;i<memSize;i++) sc_memory[i] = 0;
}

void sc_comms_init()
{
     int i, j = 0;
     for(i=10;i<=11;i++)
     comms[j++] = i;
     for(i=20;i<=21;i++)
     comms[j++] = i;
     for(i=30;i<=33;i++)
     comms[j++] = i;
     for(i=40;i<=43;i++)
     comms[j++] = i;
     for(i=51;i<=76;i++)
     comms[j++] = i;
}

int sc_memorySet (int address, int value)
{
	if (address >= memSize || address < 0) { flags |= M; return 0; }
	if (value >= 0x7FFF) { flags = flags | P; return 0; }
	sc_memory[address] = value;
	return 1;
}

int sc_memoryGet (int address, int *value)
{
	if (address > memSize) { flags |= M; return 0; }
	*value = sc_memory[address];
	return 1;
}

int sc_memorySave (char *filename)
{
	FILE *file;
	file = fopen (filename, "wb");
	if (!file) return 0;
	fwrite (sc_memory, sizeof(int), memSize, file);
	fclose (file);
	return 1;
}

int sc_memoryLoad (char *filename)
{
	FILE *file;
	file = fopen (filename, "rb");
	if (!file) return 0;
	fread (sc_memory, sizeof(int), memSize, file);
	fclose (file);
	return 1;
}

int sc_regSet (int reg, int value)
{
    if ((reg != P && reg != O && reg != M && reg != T && reg != E) ||
		(value != 1 && value != 0)) return 0;
    if (value) flags = flags | reg;
    else flags = flags & ~reg;
    return 1;
}

int sc_regGet (int reg, int *value)
{
	int k;
	switch (reg)
	{
		case P: k = 0; break;
		case O: k = 1; break;
		case M: k = 2; break;
		case T: k = 3; break;
		case E: k = 4; break;
		default: return 0;
	}
	*value = flags >> k & 0x1;
	return 1;
}

void sc_regInit ()
{
     flags = 0;
}

int sc_commandEncode (int command, int operand, int *value)
{
    int i;
    int flag = 0;
    for(i=0;i<37;i++)
		if(command == comms[i]) flag = 1;
	if (!flag) return 0;
    if (operand > 127) return 0;
    *value = (command << 7) + operand;
    return 1;
}

int sc_commandDecode (int value, int * command, int *operand)
{
	if (value > 0x7FFF ) {
        flags = flags | E;
        *command = 0;
        *operand = 0;
        return 0;
    }
    int i;
    *command = value >> 7;
    *operand = value & 127;
    int flag = 0;
    for (i=0;i<37;i++)
		if (*command == comms[i]) flag = 1;
	if (*command == 0) flag = 1;
    if (!flag) { flags = flags | E; return 0; }
    
    return 1;
}
