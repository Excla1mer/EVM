#include "myTerm.h"

int main()
{
	printf("Ti pidor\n");
	mt_clrscr();
	mt_gotoXY(10,5);
	mt_setfgcolor(1);
	mt_setbgcolor(0);
	printf("Sergey top");
	mt_gotoXY(8,6);
        mt_setfgcolor(2);
        mt_setbgcolor(7);
	printf("Dima top");
	mt_gotoXY(0,10);
        mt_setfgcolor(7);
        mt_setbgcolor(8);
	printf("121321\n");
}
