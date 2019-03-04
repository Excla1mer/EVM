#include "mySimpleComputer.h"

int sc_memorySet(int address, int value)
{
	if ((address >= 0) && (address < memsize)) 
	{
		sc_memory[address] = value;
		return 0;
	}
	else
		return -1;
}
