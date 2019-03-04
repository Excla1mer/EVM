#include "mySimpleComputer.h"

int sc_commandDecode(int value, int *command, int *operand)
{
	void *correct_command;
	int attribute;
	int tmp_command, tmp_operand;
	attribute = (value >> 14) & 1;
	if (attribute == 0) {
		tmp_command = (value >> 7) & 0x7F;
		tmp_operand = value & 0x7F;
		correct_command = bsearch(&tmp_command, correct_ops, ops_num,sizeof(int), int_cmp);
		if (correct_command != NULL) {
			*command = tmp_command;
			*operand = tmp_operand;
		}
		else
			return -1;
	}
	else
		return -1;
	return 0;
}
