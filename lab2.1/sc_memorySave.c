#include "mySimpleComputer.h"

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
