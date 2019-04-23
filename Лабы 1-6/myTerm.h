#include <iostream>
#include <sys/ioctl.h>

using namespace std;

enum colors {BLACK, RED, GREEN, YELLOW, BLUE, PURPLE, LIGHT_BLUE, WHITE};

int mt_clrscr ()
{
	cout << "\E[2J\E[H";
	return 0;
}

int mt_gotoXY (int row, int col)
{
	if((row < 0) || (col < 0)) return -1;
	cout << "\E[" << row << ";" << col << "H";
	return 0;
}

int mt_goDown (int rows)
{
	cout << "\E[" << rows << "B";
	return 0;
}

int mt_goRight (int cols)
{
	cout << "\E[" << cols << "C";
	return 0;
}

int mt_goUp (int rows)
{
	cout << "\E[" << rows << "A";
	return 0;
}

int mt_goLeft (int cols)
{
	cout << "\E[" << cols << "D";
	return 0;
}

int mt_clearLine ()
{
	cout << "\e[2K";
	return 0;
}

int mt_getscreensize (int &rows, int &cols)
{
	struct winsize ws;
	if (!ioctl (1,TIOCGWINSZ,&ws)){
		rows = ws.ws_row;
		cols = ws.ws_col;
	} else {
		return -1;
	}
	return 0;
}

int mt_cursorVisible (int flag)
{   
    if ((flag != 0) && (flag != 1)) return -1; 

    if (flag)
        cout << "\E[?12;25h";
    else
        cout << "\E[?25l";
	return 0;
}

int mt_setfgcolor (int color)
{
	cout << "\E[3" << color << "m";
	return 0;
}

int mt_setbgcolor (int color)
{
	cout << "\E[4" << color << "m";
	return 0;
}

int mt_setColor (int color)
{
	cout << "\E[" << color << "m";
	return 0;
}


int mt_setFontBold (int type)
{
	cout << "\E[0" << type << "m";
	return 0;
}

int mt_setFontDefault ()
{
	cout << "\E[0m";
	return 0;
}

int mt_setFont (int type, int color1, int color2)
{
	cout << "\E[" << type << ";" << color1 << ";" << color2 << "m";
	return 0;
} 
