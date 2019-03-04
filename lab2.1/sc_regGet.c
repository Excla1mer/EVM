#include "mySimpleComputer.h"

int sc_regGet(int reg, int *value)
{
	if ((reg >= 0) && (reg <=4)) {
		*value = VAL(sc_flag, reg);
	}
	else
		return -2;
	return 0;
}
