#include "mySimpleComputer.h"

int main()
{
	int a,b,c,x,d,e,f,h;
	int value;
	int *value0 = &e;
	int *value1 = &f;
	sc_memoryInit();
        sc_regInit();
	while(1)
	{
		printf("|1|Test mem |2|Test File |3|Test flag |4| Test Encode/Decode |5| Show memory |6| Show register\n");
		scanf("%d",&a);
		switch(a)
		{
			case 1:
				do
				{
					printf("Select <cell> and <value>\n");
					scanf("%d %d",&b,&c);
					sc_memorySet(b,c);
					printf("Repeat?\n");
					scanf("%d",&x);
				}while(x==1);

				do
                                {
                                        printf("Select cell->value\n");
                                        scanf("%d",&b);
					if(b>=0&&b<=99)
					{
                                        	sc_memoryGet(b,&value);
						printf("%d\n",value);
					}
					else
					{
						printf("Wrong cell!\n");
					}
                                        printf("Repeat?\n");
                                        scanf("%d",&x);
                                }while(x==1);
				break;
			case 2:
				printf("|1| Save |2| Load\n");
				scanf("%d",&d);
				switch(d)
				{
					case 1:
						sc_memorySave("file.txt");
						break;
					case 2:
						sc_memoryLoad("file.txt");
						break;
					default :
						printf("Wrong value!\n");break;

				}
				break;
			case 3:
				do
                                {
                                        printf("Select <register> and <value>\n");
                                        scanf("%d %d",&b,&c);
					if(b>=0&&b<=4)
                                        {
                                                sc_regSet(b,c);
                                        }
                                        else
                                        {
                                                printf("Wrong register!\n");
                                        }
                                        printf("Repeat?\n");
					scanf("%d",&x);
                                }while(x==1);

				do
                                {
                                        printf("Select register->value\n");
                                        scanf("%d",&b);
					if(b>=0&&b<=4)
					{
                                        	sc_regGet(b,&value);
						printf("%d\n",value);
					}
					else
					{
						printf("Wrong register!\n");
					}
                                      	printf("Repeat?\n");
					scanf("%d",&x);
                                }while(x==1);
				break;
			case 4:
				printf("Choose command and operand\n");
				scanf("%d%d",&b,&c);
				sc_commandEncode(b,c,&value);
				printf("%x\n",value);
				/*int z=value;
				sc_commandDecode(z,value,value0);
				printf("command=%x operand=%x",value,*value0);*/
				break;
			case 5:
				for(int i=0;i<10;i++)
				{
					for(int j=0;j<10;j++)
					{
						printf("%4d",sc_memory[i*10+j]);
					}
					printf("\n");
				}
				break;
			default :
				printf("Wrong value!\n");break;
			case 6:
				printf("\nRegister: ");
    				for(int i=0; i <5; i++) {
    				    sc_regGet(i,&value);
    				    printf("[%d]%d ", i, value );
   				 }
    				printf("\n\n");
				break;
		}
	}
	/*sc_memoryInit();
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
	printf("%d\n",sc_regGet(7, &value));*/
	return 0;
}

