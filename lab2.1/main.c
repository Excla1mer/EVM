#include "mySimpleComputer.h"

int main()
{
	int value=0;
	sc_memoryInit();
	for(int i = 0; i < 100; i++)
		sc_memorySet(i,i);
	sc_memoryGet(5,&value);
	printf("5ya echeika=%d value=%d\n",sc_memory[5],value);
	sc_memorySave("file.txt");
	for(int i = 0; i < 100; i++)
		sc_memorySet(i,0);
	printf("zanulenie %d\n",sc_memory[50]);
	sc_memoryLoad("file.txt");
	for(int i = 0; i < 100; i++)
		printf("%d ",sc_memory[i]);
	printf("\n");
	sc_regInit();
	sc_regSet(2,1);
	sc_regSet(0,0);
	sc_regSet(1,1);
	sc_regSet(3,0);
	sc_regSet(4,1);
	sc_regSet(5,1);
	sc_regGet(2, &value);
	printf("%d\n",value);
	sc_regGet(7, &value);
	printf("%d\n",sc_regGet(7, &value));
	return 0;
}
