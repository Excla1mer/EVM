#include <stdio.h>
#include <string.h>
#include <locale.h>

int C, H, S;

typedef struct {
	unsigned int C:  10;
	unsigned int H:  4;
	unsigned int S:  6;
} tCHS;

typedef struct {
	unsigned int C:  10;
	unsigned int H:  8;
	unsigned int S:  6;
} tLARGE;

typedef struct {
	unsigned int C:  16;
	unsigned int H:  4;
	unsigned int S:  8;
} tIDECHS;

typedef struct {unsigned int S:  32;} tLBA;

struct table
{
	char is_active[4], os[4], identifer;
	tLARGE begin, end;
	tLBA start;
	int size;
};


int g_large2lba (tLARGE LARGE, tLBA* LBA)
{
	LBA -> S = (LARGE.C * H + LARGE.H) * S + LARGE.S - 1;
	return 0;
}

int g_idechs2lba (tIDECHS IDECHS, tLBA* LBA)
{
	LBA -> S = (IDECHS.C * H + IDECHS.H) * S + IDECHS.S - 1;
	return 0;
}

int g_idechs2large (tIDECHS IDECHS, tLARGE* LARGE)
{
	LARGE -> S = IDECHS.S; LARGE -> H = IDECHS.H;
	LARGE -> C = IDECHS.C;
	return 0;
}

int g_chs2lba (tCHS CHS, tLBA *LBA)
{
	LBA -> S = (CHS.C * 255 + CHS.H) * 63 + CHS.S - 1;
	return 0;
}

int g_lba2chs (tLBA LBA, tCHS* CHS)
{
	int temp1, temp2, divider, i;
	CHS -> S = 63;
	temp1 = LBA.S / 63; temp2 = temp1 / 1023;
	for (i = 2; i <= 256; i *= 2) {
		if (i / 2 < temp2 && i > temp2) {
			if (i == 256) --i;
			divider = i;
			break;
		}
	}
	CHS -> H = divider;
	CHS -> C = temp1 / divider;
	return 0;
}

int a_chs2large(tCHS geometry1, tLARGE geometry2, tLARGE LARGE, tCHS* CHS)
{
	CHS -> S = LARGE.S;
	CHS -> C = geometry2.C * (LARGE.H % 2) + LARGE.C;
	CHS -> H = (int)LARGE.H / 2;
	return 0;
}

int a_large2chs(tLARGE geometry1, tCHS geometry2, tCHS CHS, tLARGE* LARGE)
{
	LARGE -> S = CHS.S;
	LARGE -> C = CHS.C % geometry1.C;
	LARGE -> H = (int)(geometry1.H / 2) * (CHS.C % 2) + CHS.H;
	return 0;
}

int a_lba2large(tLARGE geometry, tLBA LBA, tLARGE* LARGE)
{
	LARGE -> S = LBA.S % geometry.S + 1;
	LARGE -> H = ((LBA.S - (LARGE -> S - 1)) / geometry.S) % geometry.H;
	LARGE -> C = ((LBA.S - (LARGE -> S - 1) - (LARGE -> H * geometry.S)) / (geometry.S * geometry.H));
	return 0;
}

int a_lba2idechs(tIDECHS geometry, tLBA LBA, tIDECHS* IDECHS)
{
	IDECHS -> S = LBA.S % geometry.S + 1;
	IDECHS -> H = ((LBA.S - (IDECHS -> S - 1)) / geometry.S) % geometry.H;
	IDECHS -> C = ((LBA.S - (IDECHS -> S - 1) - (IDECHS -> H * geometry.S)) / (geometry.S * geometry.H));
	return 0;
}

int a_lba2chs(tCHS geometry, tLBA LBA, tCHS* CHS)
{
	CHS -> S = LBA.S % 63 + 1;
	CHS -> H = ((LBA.S - (CHS -> S - 1)) / 63) % 255;
	CHS -> C = ((LBA.S - (CHS -> S - 1) - (CHS -> H * 63)) / (63 * 255));
	return 0;
}

int a_chs2lba(tCHS geometry, tLBA LBA, tCHS* CHS)
{
	CHS -> S = (LBA.S % geometry.S) + 1;
	CHS -> H = (LBA.S / geometry.S) % geometry.H;
	CHS -> C = (LBA.S / geometry.S) / geometry.H;
	return 0;
}

int main()
{
	setlocale(0, "Rus");
	tIDECHS IDECHS; tLBA LBA; tLARGE LARGE;
	struct table t[10];
	int active = 0, start = 1, i = 0, j ;
	float c, h, s;
	double size;

	printf ("Введите геометрию диска:\n");
	printf ("C: "); scanf ("%fl", &c);
	printf ("H: "); scanf ("%fl", &h);
	printf ("S: "); scanf ("%fl", &s);
	IDECHS.C = c; IDECHS.H = h; IDECHS.S = s;
	double size1;
	size1 = c * h  * s * 512 / 1024 / 1024 / 1024;
	size = c * h  * s * 512 / 1024;
	printf ("\nРазмер диска в ГБ: %f\n", size1);

	g_idechs2large (IDECHS, &LARGE);

	while(1) {
		printf ("\nРазмер диска в КБ: %f\n", size);
		printf ("Введите размер раздела диска: "); scanf ("%d", &t[i].size);
		size -= t[i].size;
		if (t[i].size == 0 || size <= 0) { break; }

		printf ("Введите тип раздела диска:\n");
        printf ("FAT12\n");
        printf ("FAT16\n");
        printf ("Extended\n");
        printf ("MS-DOS_FAT16\n");
        printf ("NTFS\n");
        printf ("Win95_FAT32\n");
        printf ("Win95_FAT16\n");
        printf ("Linux_swap\n");
        printf ("Linux\n");
        scanf("%s", &t[i].identifer);
		if (strcmp (&t[i].identifer, "FAT12") == 0) strcpy (t[i].os, "01");
		else if  (strcmp (&t[i].identifer, "FAT16") == 0) strcpy (t[i].os, "04");
		else if  (strcmp (&t[i].identifer, "Extended") == 0) strcpy (t[i].os, "05");
		else if  (strcmp (&t[i].identifer, "MS-DOS_FAT16") == 0) strcpy (t[i].os, "06");
		else if  (strcmp (&t[i].identifer, "NTFS") == 0) strcpy (t[i].os, "07");
		else if  (strcmp (&t[i].identifer, "Win95_FAT32") == 0) strcpy (t[i].os, "0c");
		else if  (strcmp (&t[i].identifer, "Win95_FAT16") == 0) strcpy (t[i].os, "0Eh");
		else if  (strcmp (&t[i].identifer, "Linux_swap") == 0) strcpy (t[i].os, "82");
		else if  (strcmp (&t[i].identifer, "Linux") == 0) strcpy (t[i].os, "83");
		else strcpy (t[i].os, "00");

		if (active == 0) {
			printf ("Активен ли раздел? (1 or 0) "); scanf ("%d", &active);
			if (active != 1 && active != 0) {
				printf ("Ошибка! Неверно введено значение активности; Активность раздела может быть равна только 0 или 1.\n");
				printf ("Попробуйте еще раз.\n");
				active = 0;
				continue;
			}
			strcpy (t[i].is_active, "80h");
		} else  strcpy (t[i].is_active, "0");

		t[i].start.S = start;
		start = t[i].start.S + t[i].size;
		LBA.S = start;

		a_lba2large (LARGE, t[i].start, &t[i].begin);
		a_lba2large (LARGE, LBA, &t[i].end);
		++i;
	}
    printf ("\n");
	for (j = 0; j < i; ++j) {
		printf("Активность раздела %s\n", t[j].is_active);
		printf("CHS начальный %d %d %d\n", t[j].begin.C, t[j].begin.H, t[j].begin.S);
		printf("OC %s\n", t[j].os);
		printf ("CHS конечный %d %d %d\n", t[j].end.C , t[j].end.H , t[j].end.S);
		printf("LBA %d\tразмер %d \n\n", t[j].start.S, t[j].size);
	}
	system("pause");
	return 0;
}
