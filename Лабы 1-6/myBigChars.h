#include <iostream>	
#include <fstream>

using namespace std;

unsigned long long bigChar[18] =
{
0x7EFFE7EFF7E7FF7E, // 0
0x383838383838381C, // 1
0xFFFF07077EE0E07F, // 2
0x7FE0E07878E0E07F, // 3
0xE0E0E0FEFFE7E7E7, // 4
0x7FE0E0FE7F0707FF, // 5
0x7EFFE7E77F0707FE, // 6
0xE0E0E0E0E0E0E07F, // 7
0x7EFFE77E7EE7FF7E, // 8
0x7FE0E0FEE7E7FF7E, // 9
0xC3C3FFE7667E3C18, // A
0x7FE3E37F3F737F3F, // B
0xF0FC0E07070EFCF0, // C
0x3F7BE3E3E3733F1F, // D
0xFFFF07FFFF07FFFF, // E
0x070707FFFF07FFFF, // F
0x3C3C3CFFFF3C3C3C, // +
0x000000FFFF000000  // -
};

int bc_box (int x1, int y1, int x2, int y2)
{
	int i;
	
	cout << "\E(0";
	
	if (x1 == 0) x1 = 1;
	if (y1 == 0) y1 = 1;
	
	mt_gotoXY(x1,y1);
	cout << "l";
	
	for (i=0; i<y2-2; i++) cout << "q";
	cout << "k";
	
	for (i=1; i<=x2-2; i++) { mt_gotoXY(x1+i,y1+y2-1); cout << "x"; }
	
	for (i=1; i<=x2-2; i++) { mt_gotoXY(x1+i,y1); cout << "x"; }
	
	mt_goDown (1);
	mt_goLeft (1);
	cout << "m";
	
	mt_gotoXY(x1+x2-1,y1);
	mt_goRight (1);
	for (i=0; i<y2-2; i++) cout << "q";
	cout << "j";
	cout<<"\E(B";
	
	return 0;
}

int bc_printbigchar(unsigned long long big, int x, int y)
{
	int i,k=0;
   	cout<<"\E(0";

	mt_gotoXY(x++,y); 

	for(i=0; i<64; i++) {
        	if((big&1)==1) cout<<"a";
        	else cout<<" ";
        	k++;
        	if(k>=8) {
            		mt_gotoXY(x++, y);
            		k=0;
        		}
        	big=big>>1;
	}
     	cout<<"\E(B";
    	return 0;		
}


int bc_getbigcharpos (unsigned long long big, int x, int y, int &value) {
	int k;
	k=(x-1)*8+y;
	value=(big>>(k-1))&0x1;
	return 0;
}

int bc_setbigcharpos(unsigned long long &big, int x, int y, int value)
{
	int k;
	k=(x-1)*8+y;
	if(value) {
            	big=big|(1<<(k-1));
    	}
    	else {
        	big=big&(~(1<<(k-1)));
    	}
	return 0;
}

int bc_bigcharwrite (unsigned long long *big, int count)
{
	ofstream out("bigchar.out");
	if(!out) {
		cerr<<"Can not open file 'bigchar.tru' for write!";
		return -1;
		}
	for(int i=0;i<count;i++) {
		out<<*big<<" ";
	}
	return 0;
}


int bc_bigcharread (unsigned long long *big)
{
	ifstream in("bigchar.in");
	if(!in) {
		cerr<<"Can not open file 'bigchar.tru' for read!";
		return -1;
		}
	in>>*big;
	return 0;
}
