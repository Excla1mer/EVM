#ifndef __GUARD_MYBIGCHARS
#define __GUARD_MYBIGCHARS

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include "myTerm.h"




int bc_printA(char *str);
int bc_box(int x1, int y1, int x2, int y2);
int bc_printbigchar(long big, int x, int y, enum colors fg, enum colors bg);
int bc_setbigcharpos(long *big, int x, int y, int value);
int bc_getbigcharpos(long big, int x, int y, int *value);
int bc_bigcharwrite(int fd, int *big, int count);
int bc_bigcharread(int fd, int *big, int need_count, int *count);


#endif /* __GUARD_MYBIGCHARS */
