#include "mySimpleComputer.h"

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
