#include "myReadKey.h"

struct termios term;

int rk_readkey(enum keys *key)
{
	
	char buf[16];
	int num_read;
	
	if (tcgetattr(0, &term) != 0)
		return -1;
		
	num_read = read(0, buf, 15);
	
	if (num_read < 0)
		return -1;
	buf[num_read] = '\0';
	
	if (strcmp(buf, "l") == 0)
		*key = KEY_l;
	else
	if (strcmp(buf, "s") == 0)
		*key = KEY_s;
	else
	if (strcmp(buf, "r") == 0)
		*key = KEY_r;
	else
	if (strcmp(buf, "t") == 0)
		*key = KEY_t;
	else
	if (strcmp(buf, "i") == 0)
		*key = KEY_i;
	else
	if (strcmp(buf, "\n") == 0)
		*key = KEY_enter;
	else
	if (strcmp(buf, "\E[15~") == 0)
		*key = KEY_f5;
	else
	if (strcmp(buf, "\E[17~") == 0)
		*key = KEY_f6;
	else
	if (strcmp(buf, "\E[B") == 0)
		*key = KEY_down;
	else
	if (strcmp(buf, "\E[C") == 0)
		*key = KEY_right;
	else
	if (strcmp(buf, "\E[A") == 0)
		*key = KEY_up;
	else
	if (strcmp(buf, "\E[D") == 0)
		*key = KEY_left;
		
	if (tcsetattr(0, TCSADRAIN, &term) != 0)
		return -1;

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
