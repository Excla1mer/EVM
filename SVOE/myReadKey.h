#ifndef __GUARD_MYREADKEY_H
#define __GUARD_MYREADKEY_H

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/ioctl.h>
#include <termios.h>
#include <stdlib.h>

enum keys   { 	
				KEY_l, KEY_s, KEY_r, KEY_t,
				KEY_i, KEY_enter, KEY_f5,
				KEY_f6, KEY_down, KEY_up, KEY_right, KEY_left
			};

int rk_readkey(enum keys *key);
int rk_mytermsave();
int rk_mytermrestore();
int rk_mytermregime(int regime, int vtime, int vmin, int echo, int sigint);

#endif
