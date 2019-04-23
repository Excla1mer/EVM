#include "myBigChars.h"

int bc_printA(char *str)
{
        printf("\E(0%s\E(B", str);
        return 0;
}



int bc_box (int x1, int y1, int x2, int y2)
{
	int i;
	
	printf("\E(0");
	
	if (x1 == 0) x1 = 1;
	if (y1 == 0) y1 = 1;
	
	mt_gotoXY(x1,y1);
	printf("l");
	
	for (i=0; i<y2-2; i++) printf("q");
	printf("k");
	
	for (i=1; i<=x2-2; i++) { mt_gotoXY(x1+i,y1+y2-1); printf("x"); }
	
	for (i=1; i<=x2-2; i++) { mt_gotoXY(x1+i,y1); printf("x"); }
	
	mt_goDown (1);
	mt_goLeft (1);
	printf("m");
	
	mt_gotoXY(x1+x2-1,y1);
	mt_goRight (1);
	for (i=0; i<y2-2; i++) printf("q");
	printf("j");
	cout<<"\E(B";
	
	return 0;
}


int bc_printbigchar(long big, int x, int y, enum colors fg, enum colors bg)
{
	int maxx, maxy;
	//int pos, bit;
	int i, /*j,*/ k=0;
	//char row[9];
	
	mt_getscreensize(&maxy, &maxx);
	if ((x < 0) || (y < 0) || (x + 8 > maxx) || (y + 8 > maxy))
		return -1;
	//row[8] = '\0';
	mt_setfgcolor(fg);
	mt_setbgcolor(bg);
	mt_gotoXY(x,y);
	for(i=0; i<64; i++) {
        	if((big&1)==1) 
		{
			bc_printA("a");
		}
        	else
		{ 
			printf(" ");
		}
        	k++;
        	if(k>=8) 
		{
			y++;
            		mt_gotoXY(x, y);
            		k=0;
       		}
		else
		{
			//mt_gotoXY(k, y);
		}
        	big=big>>1;
	}
	/*for (i = 0; i < 8; i++) {
		for (j = 0; j < 8; j++) {
			pos = i >> 2;
			bit = (big[pos] >> ((i % 4) * 8 + j)) & 1;
			if (bit == 0)
				row[j] = ' ';
			else
				row[j] = 'a';
		}
		mt_gotoXY(x, y + i);
		bc_printA(row);
	}*/
	mt_setfgcolor(clr_default);
	mt_setbgcolor(clr_default);
	return 0;
}

int bc_setbigcharpos(long *big, int x, int y, int value)
{
	long k;
	k=(x-1)*8+y;
	if(value) {
            	*big=*big|(1<<(k-1));
    	}
    	else {
        	*big=*big&(~(1<<(k-1)));
    	}
	return 0;
}

/*int bc_getbigcharpos(int *big, int x, int y, int *value)
{
	int pos;

	if ((x < 0) || (y < 0) || (x > 7) || (y > 7))
		return -1;
	if (y <= 3)
		pos = 0;
	else
		pos = 1;
	y = y % 4;
	*value = (big[pos] >> (y*8 + x)) & 1;

	return 0;
}*/
int bc_getbigcharpos (long big, int x, int y, int *value) {
	long k;
	k=(x-1)*8+y;
	*value=(big>>(k-1))&0x1;
	return 0;
}

int bc_bigcharwrite(int fd, int *big, int count)
{
	int err;
	
	err = write(fd, &count, sizeof(count));
	if (err == -1)
		return -1;
	err = write(fd, big, count * (sizeof(int)) * 2);
	if (err == -1)
		return -1;
	
	return 0;
}

int bc_bigcharread(int fd, int *big, int need_count, int *count)
{
	int n, cnt, err;
	
	err = read(fd, &n, sizeof(n));
	if (err == -1 || (err != sizeof(n)))
		return -1;
	cnt = read(fd, big, need_count * sizeof(int) * 2);
	if (cnt == -1)
		return -1;
	*count = cnt / (sizeof(int) * 2);
	
	return 0;
}
