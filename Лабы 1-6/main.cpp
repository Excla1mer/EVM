#include <iostream>
#include <stdio.h>
#include <limits.h>
#include <signal.h>
#include <sys/time.h>
#include "myReadKey.h"
#include "mySimpleComputer.h"
#include "myTerm.h"
#include "myBigChars.h"

#define defColor 30
#define defBgColor 44
#define selColor 34
#define selBgColor 40
#define fontBold 0

#define rowWidth 10
#define fileNameLen 30

#define iorow 23
#define minRows 24
#define minCols 80

using namespace std;

int printEl (int value, int row, int col, int color, int bgcolor)
{
	int comm, oper, k;
	sc_commandDecode(value, &comm, &oper);
	k = value >> 14;
	mt_gotoXY(row, col);
	
	if (color != -1) mt_setFont (fontBold, color, bgcolor);
	printf("%c%02X%02X",(k == 0) ? '+' : '-',comm,oper);
	if (color != -1) mt_setFont (fontBold, defColor, defBgColor);
	
	return 0;
}

int printMemory ()
{
    int i, j = 1;
	int value;
	for(i = 0; i < 100; i++)
	{
		if(i % rowWidth == 0) j++;
		sc_memoryGet(i, &value);
		if (i != icounter)
			printEl (value, j, (i % rowWidth) * 6 + 2, -1, -1);
		else
			printEl (value, j, (i % rowWidth) * 6 + 2, selColor, selBgColor);
	}
	return 0;
}

int printBigMemory (int address, int row, int col, int margin)
{
	int value, comm, oper, i;
	sc_memoryGet (address, &value);
	sc_commandDecode (value, &comm, &oper);
	
	int k = value >> 14;
	k == 0 ? bc_printbigchar (bigChar[16], row, col) :
				bc_printbigchar (bigChar[17], row, col);
			col += 8 + margin;
	for (i=1; i>=0; i--)
	{
		bc_printbigchar (bigChar[comm >> (i*4) & 15], row, col);
		col += 8 + margin;
	}
	for (i=1; i>=0; i--)
	{
		bc_printbigchar (bigChar[oper >> (i*4) & 15], row, col);
		col += 8 + margin;
	}
	return 0;
}

void init ()
{
	sc_memoryInit ();
	sc_comms_init ();
	sc_regInit ();
	icounter = 0;
	accumulator = 0;
}

void drawConsole ()
{
	mt_setFont (fontBold, defColor, defBgColor);
	mt_clrscr ();
	
	bc_box (1, 1, 12, 61);
	bc_box (13, 1, 10, 52);
	bc_box (13, 53, 10, 27);
	for (int i=0; i<4; i++)
		bc_box (1+i*3, 62, 3, 18);
		
	int tmp = 55;
	mt_gotoXY(13, tmp);	printf("Keys:");
	mt_gotoXY(14, tmp); printf("l  - load");
	mt_gotoXY(15, tmp); printf("s  - save");
	mt_gotoXY(16, tmp); printf("r  - run");
	mt_gotoXY(17, tmp); printf("t  - step");
	mt_gotoXY(18, tmp); printf("i  - reset");
	mt_gotoXY(19, tmp); printf("F5 - accumulator");
	mt_gotoXY(20, tmp); printf("F6 - instr-n counter");
	mt_gotoXY(21, tmp); printf("q - redraw all");
   
    mt_gotoXY (0, 2); 	printf("\tMemory");
    mt_gotoXY (1, 64); 	printf("Accumulator");
    mt_gotoXY (4, 64); 	printf("Inst-n Counter");
	mt_gotoXY (7, 64); 	printf("Operation");
	mt_gotoXY (10, 64); printf("Flags");
	
	mt_cursorVisible (0);
}

void drawHud ()
{
    int flag = 0;
	
    mt_gotoXY (11, 64); sc_regGet (P, &flag);
		if ( flag == 1 ) cout << "P ";
		else cout << " ";
	mt_gotoXY (11, 66); sc_regGet (O, &flag);
		if ( flag == 1 ) cout << "O ";
		else cout << " ";
	mt_gotoXY (11, 68); sc_regGet (M, &flag);
		if ( flag == 1 ) cout << "M ";
		else cout << " ";
	mt_gotoXY (11, 70); sc_regGet (T, &flag);
		if ( flag == 1 ) cout << "T ";
		else cout << " ";
	mt_gotoXY (11, 72); sc_regGet (E, &flag);
		if ( flag == 1 ) cout << "E ";
		else cout << " ";
	
	printEl (icounter, 5, 68, -1, -1);
	printEl (accumulator, 2, 68, -1, -1);
}

void drawData ()
{
	printMemory();
	printBigMemory (icounter, 14, 3, 2);
	
	int val;
	sc_regGet (M, &val);
	if (val)
	{
		if (icounter >= 0 && icounter < memSize)
			sc_regSet (M, 0);
	}
	
	drawHud ();
	mt_gotoXY (iorow, 1);
}

void clearIO ()
{
	mt_gotoXY(iorow, 1);
	mt_clearLine ();
}

int checkWin ()
{
	int rows, cols;
	mt_getscreensize (rows, cols);
	if (rows < minRows || cols < minCols)
		return 0;
	return 1;
}

void sghandler (int sign)
{
	switch (sign)
	{
		case SIGALRM:
			int val;
			sc_regGet (T, &val);
			if (!val)
			{
				if (icounter >= memSize - 1)
				{
					sc_regSet (T, 1);
					sc_regSet (M, 1);
				}
				else icounter++;
				drawData ();
			}
			break;
		case SIGUSR1: 
			init ();
			drawConsole ();
			drawData ();
			break;
		default: break;
	}
	
}

int main ()
{
	if (!checkWin ()) 
	{
		cout << "Too small window size!\n";
		return 0;
	}
	setvbuf (stdout, NULL, _IONBF, 0);
	struct itimerval nval, oval;
	signal (SIGALRM, sghandler);
	signal (SIGUSR1, sghandler);
	nval.it_interval.tv_sec = 1;
	nval.it_interval.tv_usec  = 0;
	nval.it_value.tv_sec = 1;
	nval.it_value.tv_usec = 0;
	enum keys key = K_UNDEF;
	char filename[fileNameLen];
	int value, comm, oper, reg, t_reg;
	
	drawConsole ();
	init ();
	drawData ();
	
	setitimer (ITIMER_REAL, &nval, &oval);
    rk_mytermsave();
    rk_mytermregime (0,0,1,0,1);
    while (key != K_ESC) 
    {
		sc_regGet (T, &t_reg);
		key = K_UNDEF;
		rk_readkey(key);
		switch (key) 
		{
			case K_UP:
				icounter -= rowWidth;
				if (icounter < 0) icounter += memSize;
				drawData ();
				break;
			case K_DOWN:
				icounter += rowWidth;
				if (icounter >= memSize) icounter -= memSize;
				drawData ();
				break;
			case K_LEFT:
				icounter -= 1;
				if (icounter < 0) icounter += memSize;
				drawData ();
				break;
			case K_RIGHT:
				icounter += 1;
				if (icounter >= memSize) icounter -= memSize;
				drawData ();
				break;
			case K_F5:/*
				if (t_reg)
				{
					int num;
					clearIO ();
					mt_cursorVisible (1);
					rk_mytermregime (1,0,1,1,1);
					cout  << "Accumulator: "; cin >> num; clearIO ();
					rk_mytermregime (0,0,1,0,1);
					mt_cursorVisible (0);
					clearIO ();
					if (cin.fail())
					{
						cout << "cin failed, it's not int";
						cin.clear();
						cin.ignore(INT_MAX,'\n');
						continue;
					}
					else icounter = num - 1;
					drawData ();
				}*/
				break;
			case K_F6:
				if (t_reg)
				{
					int num;
					clearIO ();
					mt_cursorVisible (1);
					rk_mytermregime (1,0,1,1,1);
					cout  << "Memory number: "; cin >> num; clearIO ();
					rk_mytermregime (0,0,1,0,1);
					mt_cursorVisible (0);
					clearIO ();
					if (cin.fail())
					{
						cout << "cin failed, it's not int";
						cin.clear();
						cin.ignore(INT_MAX,'\n');
						continue;
					}
					else icounter = num - 1;
					drawData ();
				}
				break;
			case K_ESC:
				break;
			case K_R:
				sc_regGet (T, &reg);
				if (reg) sc_regSet (T, 0);
				else sc_regSet (T, 1);
				drawData ();
				break;
			case K_I:
				raise (SIGUSR1);
				break;
			case K_Q:
				drawConsole ();
				drawData ();
				break;
			case K_ENTER:
				if (t_reg)
				{
					clearIO ();
					mt_cursorVisible (1);
					rk_mytermregime (1,0,1,1,1);
					cout  << "Command: "; cin >> comm; clearIO ();
					cout  << "Operand: "; cin >> oper; clearIO ();
					rk_mytermregime (0,0,1,0,1);
					mt_cursorVisible (0);
					clearIO ();
					if (cin.fail())
					{
						cout << "cin failed, it's not int";
						cin.clear();
						cin.ignore(INT_MAX,'\n');
						continue;
					}
					if (sc_commandEncode (comm, oper, &value))
					{
						if (sc_memorySet (icounter, value))
							cout << "memory changed";
						else cout << "write error";
					}
					else cout << "wrong values";
					drawData ();
				}
				break;
					
			case K_L:
				if (t_reg)
				{
					clearIO ();
					cout << "filename (load): ";
					mt_cursorVisible (1);
					rk_mytermregime (1,0,1,1,1);
					cin >> filename;
					rk_mytermregime (0,0,1,0,1);
					clearIO ();
					mt_cursorVisible (0);
					if (sc_memoryLoad (filename))
						cout << "memory load from " << filename;
					else cout << "memory don't load";
					drawData ();
				}
				break;
					
			case K_S:
				if (t_reg)
				{
					clearIO ();
					cout << "filename (save): ";
					mt_cursorVisible (1);
					rk_mytermregime (1,0,1,1,1);
					cin >> filename;
					rk_mytermregime (0,0,1,0,1);
					clearIO ();
					mt_cursorVisible (0);
					if (sc_memorySave (filename))
						cout << "memory saved in " << filename;
					else cout << "memory don't saved";
				}
				break;
					
			default: break;
		}
    }	
    rk_mytermload ();
    mt_cursorVisible (1);
	
	return 0;
}
