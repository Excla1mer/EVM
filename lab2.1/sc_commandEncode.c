#include "mySimpleComputer.h"
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
		return -1;
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
                        return -1;
        }
        else
                return -1;
        return 0;
}

