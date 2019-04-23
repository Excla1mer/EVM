#include "mySimpleComputer.h"

int sc_memory[memsize];

int sc_memoryInit()
{
	memset(sc_memory, 0, sizeof(*sc_memory));
	return 0;
}

const int correct_ops[]= {
	0x10, 0x11, 0x20, 0x21, 0x30, 0x31, 0x32,0x33,
	0x40, 0x41, 0x42, 0x43, 0x51, 0x52,0x53, 0x54,
	0x55, 0x56, 0x57, 0x58, 0x59,0x60, 0x61, 0x62,
	0x63, 0x64, 0x65, 0x66,0x67, 0x68, 0x69, 0x70,
	0x71, 0x72, 0x73,0x74, 0x75, 0x76
};
const int ops_num=sizeof(correct_ops)/sizeof(int);

int cmp(const void *a, const void *b)
{
     return ( *(int*)a - *(int*)b );
}

int sc_commandEncode(int command, int operand, int *value)
{
	void *command_ptr;
	command_ptr = bsearch(&command, correct_ops, ops_num, sizeof(int), cmp);
	if (command_ptr != NULL) {
		*value = (command << 7) | operand;
		return 0;
	}
	else
	{
		sc_regSet(4, 1);
		return -1;
	}
}

int sc_commandDecode(int value, int *command, int *operand)
{
        void *correct_command;
        int attribute;
        int tmp_command, tmp_operand;
        attribute = (value >> 14) & 1;
        if (attribute == 0) {
                tmp_command = (value >> 7) & 0x7F;
                tmp_operand = value & 0x7F;
                correct_command = bsearch(&tmp_command, correct_ops, ops_num,sizeof(int), cmp);
                if (correct_command != NULL) {
                        *command = tmp_command;
                        *operand = tmp_operand;
                }
                else
		{
			sc_regSet(4, 1);
                        return -1;
		}
        }
        else
                return -1;
        return 0;
}

int sc_memoryGet(int address, int *value)
{
	if ((address >= 0) && (address < memsize)) {
		*value = sc_memory[address];
		return 0;
	}
	else
	{
		sc_regSet(2, 1);
		return -1;
	}
}

int sc_memoryLoad(char *file)
{
	FILE *F;
	int  mfile;
	F = fopen(file, "rb");
	if (F==0)
		return -1;
	mfile = fread(sc_memory, sizeof(*sc_memory) * 100, 1, F);
	fclose(F);
	if(mfile != 1)
		return -1;
	else
		return 0;
}

int sc_memorySave(char *file)
{
	FILE *F;
	int mfile;
	F = fopen(file, "wb");
	if (F == 0)
		return -1;
	mfile = fwrite(&sc_memory, sizeof(int) * 100, 1, F);
	fclose(F);
	if (mfile != 1)
		return -1;
	else
		return 0;
}

int sc_memorySet(int address, int value)
{
	if ((address >= 0) && (address < memsize)) 
	{
		sc_memory[address] = value;
		return 0;
	}
	else
	{
		sc_regSet(2, 1);
		return -1;
	}
}

int sc_regGet(int reg, int *value)
{
	if ((reg >= 0) && (reg <=4)) {
		*value = VAL(sc_flag, reg);
	}
	else
		return -2;
	return 0;
}


int sc_flag;

int sc_regInit()
{
	sc_flag = 0;
	return 0;
}

int sc_regSet(int reg, int value)
{

	if ((reg >= 0) && (reg <=4))
	{
		if (value == 1)
			SET(sc_flag, reg);
		else if (value == 0)
			NOL(sc_flag, reg);
		else
			return 0;
	}
	else
		return -1;
	return 0;
}
