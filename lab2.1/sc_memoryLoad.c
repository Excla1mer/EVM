#include "mySimpleComputer.h"

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
