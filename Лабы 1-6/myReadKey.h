#include <iostream>
#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>

using namespace std;

struct termios term;

enum keys {K_UNDEF, K_L, K_S, K_R,
			K_T, K_I, K_F5, K_F6,
			K_DOWN, K_UP, K_LEFT,
			K_RIGHT, K_ENTER, K_ESC, K_Q };

int rk_readkey (enum keys &k) {
	char c[2];
	k = K_UNDEF;
	int j = 0;
	while(1) {
		if(!read(0,&c,2)) return -1;
		switch(j) {
			case 0: switch(c[0]) {
				case 'l': k = K_L; break;
				case 'q': k = K_Q; break;
				case 's': k = K_S; break;
				case 'r': k = K_R; break;
				case 't': k = K_T; break;
				case 'i': k = K_I; break;
				case '\n': k = K_ENTER; break;
				}
				if(c[0] == '\E' && c[1] == '[') { j++; continue; }
				else if (c[0] == '\E') { k = K_ESC; break; }

				break;
			case 1: switch(c[0]) {
					case 'A': k = K_UP; break;
					case 'B': k = K_DOWN; break;
					case 'C': k = K_RIGHT; break;
					case 'D': k = K_LEFT; break;
					case '1':
						if(c[1] == '5') k = K_F5;
						if(c[1] == '7') k = K_F6; read(0,&c,1);
						break;
					}
					break;
			}
		break;
		}
		return 0;
}

int rk_mytermsave(void)
{
	if((tcgetattr(1, &term))==-1) //в term записывает структуру, описывающую режимы работы терминала
	{
		perror("Error: tcgetattr");
		return -1;
	}
	return 0;
}

int rk_mytermload(void)
{
	if((tcsetattr(1, TCSANOW, &term)) < 0) //устанавливает новые параметры, сохраненные в структуре term
	{
		perror("Error: tcsetattr");
		return -1;
	}
	return 0;
}

int rk_mytermregime(int regime,int vtime,int vmin,int echo,int sigint) {
 	struct termios myterm;

	tcgetattr(1,&myterm);

	if(regime) myterm.c_lflag |= ICANON;
 	else myterm.c_lflag &= ~ICANON;

	if(echo) myterm.c_lflag |= ECHO;
 	else myterm.c_lflag &= ~ECHO;

	if(sigint) myterm.c_lflag |= ISIG;
 	else myterm.c_lflag &= ~ISIG;

	myterm.c_cc[VMIN] = vmin;
 	myterm.c_cc[VTIME] = vtime;

	return tcsetattr(1,TCSANOW,&myterm);
}
