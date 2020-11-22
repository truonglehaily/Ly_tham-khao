#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <windows.h>
#include <ctype.h>
#pragma GCC diagnostic ignored "-Wwrite-strings"
typedef struct nhapsanpham{
	char masp[8];
	char tensp[35];
	char manhacc[8];
	char tennhacc[25];
	int soluong, ngay, thang, nam, thanhtien, dongia;
}SANPHAM;
 typedef struct thanhtoan{
	char makh[8];
	char tenkh[35];
	char diachi[25];
	char muahang[25];
	char sdt[15];
	int ngay, thang, nam, soluong, thanhtien, giaban;
}KHACHHANG;
SANPHAM A[100]; KHACHHANG B[100];
int a=0, b=0, c=0;
void nhapsanpham(SANPHAM A[]);
void insanpham(SANPHAM A[]);
int tksanpham(SANPHAM A[], char s[]);
int timkiemsanpham(SANPHAM A[]);
int suasanpham(SANPHAM A[]);
int xoasanpham(SANPHAM A[]);
void nhapkhachhang(KHACHHANG B[], SANPHAM A[]);
void inkhachhang(KHACHHANG B[]);
int tkkhachhang(KHACHHANG B[], char kh[]);
int timkiemkhachhang(KHACHHANG B[]);
int suakhachhang(KHACHHANG B[], SANPHAM A[]);
int xoakhachhang(KHACHHANG B[]);
int menu();
void xoadau(char k[])
{
	int i;
	while(k[0]==' ')
	{
		for(i=0;i<strlen(k);i++)
		{
			k[i]=k[i+1];
		}
	}
}
void xoacuoi(char k[])
{
	int i=strlen(k)-1;
	while(k[i]==' ')
	{
		k[i]=k[i+1];
		i--;
	}
}
void xoagiua(char k[])
{
	int i, j;
	for(i=0;i<strlen(k)-1;i++)
	{
		if(k[i]!=' ' && k[i+1]==' ' && k[i+2]==' ')
		{
			for(j=i+1;j<strlen(k);j++)
			{
				k[j]=k[j+1];
			}
			i--;
		}
	}
}
void viethoa(char k[])
{
	int i;
    if(k[0]!=' ')
	{
        k[0]=toupper(k[0]); // viet chu dau thanh chu hoa
        for(i=1;i<strlen(k);i++)
		{
            if(k[i]==' '&& k[i+1]!=' ') //viet ki tu sau dau cach thanh chu hoa
                k[i+1]=toupper(k[i+1]);
        }
    }
}
void xoakhoangtrang(char t[])
{
	xoadau(t);	xoacuoi(t);	xoagiua(t);
}
void chuanhoaten(char s[])
{
	xoadau(s);	xoacuoi(s);	xoagiua(s);	viethoa(s);
}
void textcolor(int x)
{
	HANDLE mau;
	mau = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(mau,x);
}
void gotoxy(int x, int y)
{
  static HANDLE h=NULL;
  if(!h)
    h=GetStdHandle(STD_OUTPUT_HANDLE);
  COORD c={x,y};
  SetConsoleCursorPosition(h,c);
}
void xoamanhinh()
{
        CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
        HANDLE hConsoleOut;
        COORD Home = {0, 0};
        DWORD dummy;

        hConsoleOut = GetStdHandle(STD_OUTPUT_HANDLE);
        GetConsoleScreenBufferInfo(hConsoleOut,&csbiInfo);

        FillConsoleOutputCharacter(hConsoleOut, ' ' , csbiInfo.dwSize.X * csbiInfo.dwSize.Y,Home,&dummy);
        csbiInfo.dwCursorPosition.X = 0;
        csbiInfo.dwCursorPosition.Y = 0;
        SetConsoleCursorPosition(hConsoleOut,csbiInfo.dwCursorPosition);
}
void viet(int x, int y, int z)
{
	gotoxy(x,y);
	printf("%c",z);
}
void vietchuoi(int x, int y, char s[], int mau)
{
	gotoxy(x,y);
	textcolor(mau);
	puts(s);
}
void trolaisua(int x, int y, char l[])
{
	int i;
	for(i=0;i<strlen(l)+1;i++)
	{
		gotoxy(x+strlen(l)-i,y);
		printf(" ");
	}
}
void gioihan(char *s, int x, int y, int b)
{
    int i, i1=0,i2=0,v=0,k;
    gotoxy(x,y);
    a:
        for(i=i2;i<b;i++)
        {
            s[v]=getch();
            if(s[v]==13)
            {
               s[v]='\0';	break;
            }
            else if(s[v]!=8)
            { 
				printf("%c",s[v]); v++;
			}
            else
            {
				if(i!=0)
                {
                    i=i-2;	v--;	s[v]='\0';
					gotoxy(x+i+1,y);	printf(" ");gotoxy(x+i+1,y);
                }
                else i--;
            }
       	}
        	if(i==b)
            while(i1!=13)
        	{
	            i1=getch();
	            if(i1==8)
            	{
	                i2=i-1;	v--;	s[v]='\0';
					gotoxy(x+i-1,y);	printf(" ");	gotoxy(x+i-1,y);
	                goto a;
            	}
        	}
        	s[v]='\0';
}
void xoaso(int x, int y, int so)
{
	int i;
	char s[15];
	itoa(so,s,15);
	for(i=0;i<strlen(s)+1;i++)
	{
		gotoxy(x+strlen(s)-i,y);
		printf(" ");
	}
}
int chuantime(int ngay, int thang, int nam)
{
    int ngaymax;
    if(nam < 1900 || nam > 2222 ||thang <1 || thang > 12 || ngay < 1 || ngay > 31 )
    {
        return 0;
    }
    else
    {
        switch(thang)
        {
          case 1:
		  case 3:
		  case 5:
		  case 7:
		  case 8:
		  case 10:
		  case 12:	ngaymax = 31;
		  			break;
         case 2:
			if (nam%4==0)
				ngaymax=29;
			else
				ngaymax=28;
			break;
		case 4:
		case 6:
		case 9:
		case 11:	ngaymax= 30;
					break;
        }
        if(ngay<=ngaymax)
            return 1;
        else
			return 0;
    }
}
void viethoafull(char s[])
{
    int i;
    for(i=0;i<strlen(s);i++)
    {
    	s[i]=toupper(s[i]);
	}
}
int nhapso(char *s)
{
    int i,l;
    l=strlen(s);
    for(i=0;i<=l;i++)
    {
        if (s[i]!='\0')
        	if(s[i]< 48 || s[i]>57) return 0;
    }
    return 1;
}
int nhapchu(char *s)
{
    int i,l;
    l=strlen(s);
    for(i=0;i<=l;i++)
    {
        if(s[i]!='\0')
            if((s[i]<65 || s[i] >90) && (s[i]<97 || s[i]>122) && (s[i]<32 || s[i]>32)) return 0;
    }
    return 1;
}
int batphim()
{
	int c=getch();
	if(c==8) //phim Backspace
		return 1;
	else if(c==9) //phim Tab
		return 2;
	else if(c==13) //phim Enter
		return 3;
	else if(c==27) //phim Esc
		return 4;
	else if(c==224)
	{
		c=getch();
		if(c==72) //Keyup
			return 5;
		else if(c==80) //KeyDown
			return 6;
		else if(c==75) //KeyLeft
			return 7;
		else if(c==77) //KeyRight
			return 8;
		else if(c==83) //Delete
			return 9;
	}
	else if(c==0)
	{
		c=getch();
		if(c==60) //F2
			return 12;
		if(c==62) //F4
			return 13;
	}
}
int bangmenu(int x, int y, int m, int n, int mau)
{
	int i, j;
	textcolor(mau);
	for(i=x;i<=x+m;i++)
		for(j=y;j<=y+n;j++)
		{
			if(i==x || i==x+m)
			{
				if(j==y && i!=x+m)
					viet(i,j,218);
				else if(j==y && i!=x)
					viet(i,j,191);
				else if(j==y+n && i!=x+m)
					viet(i,j,192);
				else if(j==y+n && i!=x)
					viet(i,j,217);
				else viet(i,j,179);
			}
			else if(j==y || j==y+n)
					viet(i,j,196);
		}
}
void bangsanpham(int x, int y, int sl)
{
	int i, j;
	textcolor(2);
	for(i=x;i<=x+117;i++)
		for(j=y;j<=y+sl;j++)
		{
			if(i==x || i==x+4 || i==x+15 || i==x+43 || i==x+57 || i==x+72 || i==x+86 || i==x+92 || i==x+104 || i==x+117)
			{
				if(j==y && i!=x && i!=x+117)
					viet(i,j,194);
				else if(j==y && i!=x+117)
					viet(i,j,218);
				else if(j==y && i!=x)
					viet(i,j,191);
				else if(j==y+2 && i!=x && i!=x+117)
					viet(i,j,197);
				else if(j==y+2 && i!=x+117)
					viet(i,j,195);
				else if(j==y+2 && i!=x)
					viet(i,j,180);
				else if(j==y+sl && i!=x && i!=x+117)
					viet(i,j,193);
				else if(j==y+sl && i!=x+117)
					viet(i,j,192);
				else if(j==y+sl && i!=x)
					viet(i,j,217);
				else viet(i,j,179);
			}
			else if(j==y || j==y+2 || j==y+sl)
					viet(i,j,196);
		}
		vietchuoi(x+1,y+1,"STT",11);
		vietchuoi(x+5,y+1,"Ma SP",11);
		vietchuoi(x+16,y+1,"Ten san pham",11);
		vietchuoi(x+44,y+1,"Ma NCC",11);
		vietchuoi(x+58,y+1,"Ten NCC",11);
		vietchuoi(x+73,y+1,"DD/MM/YYYY",11);
		vietchuoi(x+87,y+1,"SL",11);
		vietchuoi(x+93,y+1,"Don gia",11);
		vietchuoi(x+105,y+1,"Thanh tien",11);
}
void bangkhachhang(int x, int y, int sl)
{
	int i, j;
	textcolor(2);
	for(i=x;i<=x+158;i++)
		for(j=y;j<=y+sl;j++)
		{
			if(i==x || i==x+4 || i==x+14 || i==x+42 || i==x+60 || i==x+76 || i==x+89 || i==x+119 || i==x+132 || i==x+145 || i==x+158)
			{
				if(j==y && i!=x && i!=x+158)
					viet(i,j,194);
				else if(j==y && i!=x+158)
					viet(i,j,218);
				else if(j==y && i!=x)
					viet(i,j,191);
				else if(j==y+2 && i!=x && i!=x+158)
					viet(i,j,197);
				else if(j==y+2 && i!=x+158)
					viet(i,j,195);
				else if(j==y+2 && i!=x)
					viet(i,j,180);
				else if(j==y+sl && i!=x && i!=x+158)
					viet(i,j,193);
				else if(j==y+sl && i!=x+158)
					viet(i,j,192);
				else if(j==y+sl && i!=x)
					viet(i,j,217);
				else viet(i,j,179);
			}
			else if(j==y || j==y+2 || j==y+sl)
					viet(i,j,196);
		}
		vietchuoi(x+1,y+1,"STT",11);
		vietchuoi(x+5,y+1,"Ma KH",11);
		vietchuoi(x+15,y+1,"Ten khach hang",11);
		vietchuoi(x+43,y+1,"Dia chi",11);
		vietchuoi(x+61,y+1,"SDT",11);
		vietchuoi(x+77,y+1,"DD/MM/YYYY",11);
		vietchuoi(x+90,y+1,"Ma mat hang",11);
		vietchuoi(x+120,y+1,"SL",11);
		vietchuoi(x+133,y+1,"Gia ban",11);
		vietchuoi(x+146,y+1,"Thanh tien",11);
}
int menu1(int x, int y)
{
	int kt=0; bangmenu(x,y+21,90,4,10);
	bangmenu(x+2,y+22,10,2,14);	vietchuoi(x+4,y+23,"THEM DL",15);
	vietchuoi(x+20,y+23,"TIM KIEM",6);	vietchuoi(x+35,y+23,"SUA DL",6);
	vietchuoi(x+50,y+23,"XOA DL",6);	vietchuoi(x+65,y+23,"TRO VE",6);
	vietchuoi(x+80,y+23,"THOAT",6);	gotoxy(x+66,28);
	for(;;)
	{
		int h=batphim(); gotoxy(x+66,28);
		if(h==8) //right
		{
			if(kt==0)
			{
				kt=1;
				bangmenu(x+2,y+22,10,2,0);	vietchuoi(x+4,y+23,"THEM DL",6);
				bangmenu(x+18,y+22,10,2,14);vietchuoi(x+20,y+23,"TIM KIEM",15);
				vietchuoi(x+35,y+23,"SUA DL",6);	vietchuoi(x+50,y+23,"XOA DL",6);
				vietchuoi(x+65,y+23,"TRO VE",6);	vietchuoi(x+80,y+23,"THOAT",6);
			}
			else if(kt==1)
			{
				kt=2;
				vietchuoi(x+4,y+23,"THEM DL",6);
				bangmenu(x+18,y+22,10,2,0);	vietchuoi(x+20,y+23,"TIM KIEM",6);
				bangmenu(x+33,y+22,10,2,14);	vietchuoi(x+35,y+23,"SUA DL",15);
				vietchuoi(x+50,y+23,"XOA DL",6);	vietchuoi(x+65,y+23,"TRO VE",6);	vietchuoi(x+80,y+23,"THOAT",6);
			}
			else if(kt==2)
			{
				kt=3;
				vietchuoi(x+4,y+23,"THEM DL",6);	vietchuoi(x+20,y+23,"TIM KIEM",6);
				bangmenu(x+33,y+22,10,2,0);	vietchuoi(x+35,y+23,"SUA DL",6);
				bangmenu(x+48,y+22,10,2,14);	vietchuoi(x+50,y+23,"XOA DL",15);
				vietchuoi(x+65,y+23,"TRO VE",6);	vietchuoi(x+80,y+23,"THOAT",6);
			}
			else if(kt==3)
			{
				kt=4;
				vietchuoi(x+4,y+23,"THEM DL",6);	vietchuoi(x+20,y+23,"TIM KIEM",6);	vietchuoi(x+35,y+23,"SUA DL",6);
				bangmenu(x+48,y+22,10,2,0);	vietchuoi(x+50,y+23,"XOA DL",6);
				bangmenu(x+63,y+22,10,2,14);	vietchuoi(x+65,y+23,"TRO VE",15);	vietchuoi(x+80,y+23,"THOAT",6);
			}
			else if(kt==4)
			{
				kt=5;
				vietchuoi(x+4,y+23,"THEM DL",6);	vietchuoi(x+20,y+23,"TIM KIEM",6);
				vietchuoi(x+35,y+23,"SUA DL",6);	vietchuoi(x+50,y+23,"XOA DL",6);
				bangmenu(x+63,y+22,10,2,0);	vietchuoi(x+65,y+23,"TRO VE",6);
				bangmenu(x+78,y+22,10,2,14);	vietchuoi(x+80,y+23,"THOAT",15);
			}
			else if(kt==5)
			{
				kt=0;
				bangmenu(x+2,y+22,10,2,14);	vietchuoi(x+4,y+23,"THEM DL",15);	vietchuoi(x+20,y+23,"TIM KIEM",6);
				vietchuoi(x+35,y+23,"SUA DL",6);	vietchuoi(x+50,y+23,"XOA DL",6);	vietchuoi(x+65,y+23,"TRO VE",6);
				bangmenu(x+78,y+22,10,2,0);	vietchuoi(x+80,y+23,"THOAT",6);
			}
		}
		else if(h==7) //left
		{
			if(kt==0)
			{
				kt=5;
				bangmenu(x+2,y+22,10,2,0);	vietchuoi(x+4,y+23,"THEM DL",6);	vietchuoi(x+20,y+23,"TIM KIEM",6);
				vietchuoi(x+35,y+23,"SUA DL",6);	vietchuoi(x+50,y+23,"XOA DL",6);	vietchuoi(x+65,y+23,"TRO VE",6);
				bangmenu(x+78,y+22,10,2,14);	vietchuoi(x+80,y+23,"THOAT",15);
			}
			else if(kt==5)
			{
				kt=4;
				vietchuoi(x+4,y+23,"THEM DL",6);	vietchuoi(x+20,y+23,"TIM KIEM",6);
				vietchuoi(x+35,y+23,"SUA DL",6);	vietchuoi(x+50,y+23,"XOA DL",6);
				bangmenu(x+63,y+22,10,2,14);	vietchuoi(x+65,y+23,"TRO VE",15);
				bangmenu(x+78,y+22,10,2,0);	vietchuoi(x+80,y+23,"THOAT",6);
			}
			else if(kt==4)
			{
				kt=3;
				vietchuoi(x+4,y+23,"THEM DL",6);	vietchuoi(x+20,y+23,"TIM KIEM",6);	vietchuoi(x+35,y+23,"SUA DL",6);
				bangmenu(x+48,y+22,10,2,14);	vietchuoi(x+50,y+23,"XOA DL",15);
				bangmenu(x+63,y+22,10,2,0);	vietchuoi(x+65,y+23,"TRO VE",6);	vietchuoi(x+80,y+23,"THOAT",6);
			}
			else if(kt==3)
			{
				kt=2;
				vietchuoi(x+4,y+23,"THEM DL",6);	vietchuoi(x+20,y+23,"TIM KIEM",6);
				bangmenu(x+33,y+22,10,2,14);	vietchuoi(x+35,y+23,"SUA DL",15);
				bangmenu(x+48,y+22,10,2,0);	vietchuoi(x+50,y+23,"XOA DL",6);
				vietchuoi(x+65,y+23,"TRO VE",6);	vietchuoi(x+80,y+23,"THOAT",6);
			}
			else if(kt==2)
			{
				kt=1;
				vietchuoi(x+4,y+23,"THEM DL",6);	bangmenu(x+18,y+22,10,2,14);	vietchuoi(x+20,y+23,"TIM KIEM",15);
				bangmenu(x+33,y+22,10,2,0);	vietchuoi(x+35,y+23,"SUA DL",6);
				vietchuoi(x+50,y+23,"XOA DL",6);	vietchuoi(x+65,y+23,"TRO VE",6);	vietchuoi(x+80,y+23,"THOAT",6);
			}
			else if(kt==1)
			{
				kt=0;
				bangmenu(x+2,y+22,10,2,14);	vietchuoi(x+4,y+23,"THEM DL",15);
				bangmenu(x+18,y+22,10,2,0);	vietchuoi(x+20,y+23,"TIM KIEM",6);
				vietchuoi(x+35,y+23,"SUA DL",6);	vietchuoi(x+50,y+23,"XOA DL",6);
				vietchuoi(x+65,y+23,"TRO VE",6);	vietchuoi(x+80,y+23,"THOAT",6);
			}
		}
		else if(h==3) //enter
		{
			if(kt==0)
			{
				return 1;
			}
			else if(kt==1)
			{
				return 2;
			}
			else if(kt==2)
			{
				return 3;
			}
			else if(kt==3)
			{
				return 4;
			}
			else if(kt==4)
			{
				return 5;
			}
			else if(kt==5)
			{
				return 6;
			}
		}
	}
}
int menu2(int x, int y)
{
	bangmenu(x+5,y+5,8,2,3);	bangmenu(x+1,y+8,50,4,14);	vietchuoi(x+7,y+6,"MENU",11);
	bangmenu(x+3,y+9,9,2,2);	vietchuoi(x+5,y+10,"SUA",14);
	vietchuoi(x+17,y+10,"XOA",15);	vietchuoi(x+27,y+10,"TRO VE",15);
	vietchuoi(x+41,y+10,"THOAT",15);	int kt=1;	gotoxy(x+5,y+15);
	for(;;)
	{
		gotoxy(x+5,y+15);	int h=batphim();
		if(h==8) //phim sang phai
		{
			if(kt==1)
			{
				kt=2;
				bangmenu(x+3,y+9,9,2,0);	vietchuoi(x+5,y+10,"SUA",15);
				bangmenu(x+15,y+9,9,2,2);	vietchuoi(x+17,y+10,"XOA",14);
				vietchuoi(x+27,y+10,"TRO VE",15);	vietchuoi(x+41,y+10,"THOAT",15);
			}
			else if(kt==2)
			{
				kt=3;
				vietchuoi(x+5,y+10,"SUA",15);
				bangmenu(x+15,y+9,9,2,0);	vietchuoi(x+17,y+10,"XOA",15);
				bangmenu(x+25,y+9,9,2,2);	vietchuoi(x+27,y+10,"TRO VE",14);	vietchuoi(x+41,y+10,"THOAT",15);
			}
			else if(kt==3)
			{
				kt=4;
				vietchuoi(x+5,y+10,"SUA",15);	vietchuoi(x+17,y+10,"XOA",15);
				bangmenu(x+25,y+9,9,2,0);	vietchuoi(x+27,y+10,"TRO VE",15);
				bangmenu(x+39,y+9,9,2,2);	vietchuoi(x+41,y+10,"THOAT",14);
			}
			else if(kt==4)
			{
				kt=1;
				bangmenu(x+3,y+9,9,2,2);	vietchuoi(x+5,y+10,"SUA",14);
				vietchuoi(x+17,y+10,"XOA",15);	vietchuoi(x+27,y+10,"TRO VE",15);
				bangmenu(x+39,y+9,9,2,0);	vietchuoi(x+41,y+10,"THOAT",15);
			}
		}
		else if(h==7) //phim sang trai
		{
			if(kt==1)
			{
				kt=4;
				bangmenu(x+3,y+9,9,2,0);	vietchuoi(x+5,y+10,"SUA",15);
				vietchuoi(x+17,y+10,"XOA",15);	vietchuoi(x+27,y+10,"TRO VE",15);
				bangmenu(x+39,y+9,9,2,2);	vietchuoi(x+41,y+10,"THOAT",14);
			}
			else if(kt==4)
			{
				kt=3;
				vietchuoi(x+5,y+10,"SUA",15);	vietchuoi(x+17,y+10,"XOA",15);
				bangmenu(x+25,y+9,9,2,2);	vietchuoi(x+27,y+10,"TRO VE",14);
				bangmenu(x+39,y+9,9,2,0);	vietchuoi(x+41,y+10,"THOAT",15);
			}
			else if(kt==3)
			{
				kt=2;
				vietchuoi(x+5,y+10,"SUA",15);
				bangmenu(x+15,y+9,9,2,2);	vietchuoi(x+17,y+10,"XOA",14);
				bangmenu(x+25,y+9,9,2,0);	vietchuoi(x+27,y+10,"TRO VE",15);	vietchuoi(x+41,y+10,"THOAT",15);
			}
			else if(kt==2)
			{
				kt=1;
				bangmenu(x+3,y+9,9,2,2);	vietchuoi(x+5,y+10,"SUA",14);
				bangmenu(x+15,y+9,9,2,0);	vietchuoi(x+17,y+10,"XOA",15);	vietchuoi(x+27,y+10,"TRO VE",15);	vietchuoi(x+41,y+10,"THOAT",15);
			}
		}
		else if(h==3) // phim enter
		{
			if(kt==1)
			{
				return 1;
			}
			else if(kt==2)
			{
				return 2;
			}
			else if(kt==3)
			{
				return 3;
			}
			else if(kt==4)
			{
				return 4;
			}
		}
	}
}
int menu3(int x, int y)
{
	bangmenu(x+90,y-5,10,2,2);	vietchuoi(x+93,y-4,"XOA",15);
	vietchuoi(x+110,y-4,"TRO VE",6);	vietchuoi(x+127,y-4,"THOAT",6);
	int kt=1;	gotoxy(x+99,y+7);
	for(;;)
	{
		gotoxy(x+99,y+7);	int h=batphim();
		if(h==8) //phim sang phai
		{
			if(kt==1)
			{
				kt=2;
				bangmenu(x+90,y-5,10,2,0);	vietchuoi(x+93,y-4,"XOA",6);
				bangmenu(x+107,y-5,10,2,2);	vietchuoi(x+110,y-4,"TRO VE",15);	vietchuoi(x+127,y-4,"THOAT",6);
			}
			else if(kt==2)
			{
				kt=3;
				vietchuoi(x+93,y-4,"XOA",6);	bangmenu(x+107,y-5,10,2,0);	vietchuoi(x+110,y-4,"TRO VE",6);
				bangmenu(x+124,y-5,10,2,2);	vietchuoi(x+127,y-4,"THOAT",15);
			}
			else if(kt==3)
			{
				kt=1;
				bangmenu(x+90,y-5,10,2,2);	vietchuoi(x+93,y-4,"XOA",15);	vietchuoi(x+110,y-4,"TRO VE",6);
				bangmenu(x+124,y-5,10,2,0);	vietchuoi(x+127,y-4,"THOAT",6);
			}
		}
		else if(h==7) // phim sang trai
		{
			if(kt==1)
			{
				kt=3;
				bangmenu(x+90,y-5,10,2,0);	vietchuoi(x+93,y-4,"XOA",6);	vietchuoi(x+110,y-4,"TRO VE",6);
				bangmenu(x+124,y-5,10,2,2);	vietchuoi(x+127,y-4,"THOAT",15);
			}
			else if(kt==3)
			{
				kt=2;
				vietchuoi(x+93,y-4,"XOA",6);	bangmenu(x+107,y-5,10,2,2);	vietchuoi(x+110,y-4,"TRO VE",15);
				bangmenu(x+124,y-5,10,2,0);	vietchuoi(x+127,y-4,"THOAT",6);
			}
			else if(kt==2)
			{
				kt=1;
				bangmenu(x+90,y-5,10,2,2);	vietchuoi(x+93,y-4,"XOA",15);
				bangmenu(x+107,y-5,10,2,0);	vietchuoi(x+110,y-4,"TRO VE",6);	vietchuoi(x+127,y-4,"THOAT",6);
			}
		}
		else if(h==3) // phim enter
		{
			if(kt==1)
			{
				return 1;
			}
			else if(kt==2)
			{
				return 2;
			}
			else if(kt==3)
			{
				return 3;
			}
		}
	}
}
int menu4(int x, int y)
{
	vietchuoi(x+38,y+7,"Ban co muon xoa khach hang nay khong? Chon [CO] hoac [KHONG].",12);
	bangmenu(x+51,y+8,10,4,2);	vietchuoi(x+55,y+10,"CO",14);	vietchuoi(x+73,y+10,"KHONG",15);
	int kt=1;	gotoxy(x+99,y+7);
	for(;;)
	{
		gotoxy(x+99,y+7);	int h=batphim();
		if(h==8) //phim sang phai
		{
			if(kt==1)
			{
				kt=2;
				bangmenu(x+51,y+8,10,4,0);	vietchuoi(x+55,y+10,"CO",15);
				bangmenu(x+70,y+8,10,4,2);	vietchuoi(x+73,y+10,"KHONG",14);
			}
			else if(kt==2)
			{
				kt=1;
				bangmenu(x+51,y+8,10,4,2);	vietchuoi(x+55,y+10,"CO",14);
				bangmenu(x+70,y+8,10,4,0);	vietchuoi(x+73,y+10,"KHONG",15);
			}
		}
		else if(h==7) //phim sang trai
		{
			if(kt==1)
			{
				kt=2;
				bangmenu(x+51,y+8,10,4,0);	vietchuoi(x+55,y+10,"CO",15);
				bangmenu(x+70,y+8,10,4,2);	vietchuoi(x+73,y+10,"KHONG",14);
			}
			else if(kt==2)
			{
				kt=1;
				bangmenu(x+51,y+8,10,4,2);	vietchuoi(x+55,y+10,"CO",14);
				bangmenu(x+70,y+8,10,4,0);	vietchuoi(x+73,y+10,"KHONG",15);
			}
		}
		else if(h==3) //phim enter
		{
			if(kt==1)
			{
				return 1;
			}
			else if(kt==2)
			{
				return 2;
			}
		}
	}
}
int menu5(int x, int y)
{
	bangmenu(x+4,y+6,45,4,10);
	bangmenu(x+6,y+7,10,2,2);	vietchuoi(x+9,y+8,"SAVE",15);
	vietchuoi(x+24,y+8,"TRO VE",6);	vietchuoi(x+39,y+8,"THOAT",6);
	int kt=1;	gotoxy(x+4,y+9);
	for(;;)
	{
		gotoxy(x+4,y+9);	int h=batphim();
		if(h==8) // phim sang phai
		{
			if(kt==1)
			{
				kt=2;
				bangmenu(x+6,y+7,10,2,0);	vietchuoi(x+9,y+8,"SAVE",6);
				bangmenu(x+21,y+7,10,2,2);	vietchuoi(x+24,y+8,"TRO VE",15);
				bangmenu(x+36,y+7,10,2,0);	vietchuoi(x+39,y+8,"THOAT",6);
			}
			else if(kt==2)
			{
				kt=3;
				bangmenu(x+6,y+7,10,2,0);	vietchuoi(x+9,y+8,"SAVE",6);
				bangmenu(x+21,y+7,10,2,0);	vietchuoi(x+24,y+8,"TRO VE",6);
				bangmenu(x+36,y+7,10,2,2);	vietchuoi(x+39,y+8,"THOAT",15);
			}
			else if(kt==3)
			{
				kt=1;
				bangmenu(x+6,y+7,10,2,2);	vietchuoi(x+9,y+8,"SAVE",15);
				bangmenu(x+21,y+7,10,2,0);	vietchuoi(x+24,y+8,"TRO VE",6);
				bangmenu(x+36,y+7,10,2,0);	vietchuoi(x+39,y+8,"THOAT",6);
			}
		}
		else if(h==7) // phim sang trai
		{
			if(kt==1)
			{
				kt=3;
				bangmenu(x+6,y+7,10,2,0);	vietchuoi(x+9,y+8,"SAVE",6);
				bangmenu(x+21,y+7,10,2,0);	vietchuoi(x+24,y+8,"TRO VE",6);
				bangmenu(x+36,y+7,10,2,2);	vietchuoi(x+39,y+8,"THOAT",15);
			}
			else if(kt==3)
			{
				kt=2;
				bangmenu(x+6,y+7,10,2,0);	vietchuoi(x+9,y+8,"SAVE",6);
				bangmenu(x+21,y+7,10,2,2);	vietchuoi(x+24,y+8,"TRO VE",15);
				bangmenu(x+36,y+7,10,2,0);	vietchuoi(x+39,y+8,"THOAT",6);
			}
			else if(kt==2)
			{
				kt=1;
				bangmenu(x+6,y+7,10,2,2);	vietchuoi(x+9,y+8,"SAVE",15);
				bangmenu(x+21,y+7,10,2,0);	vietchuoi(x+24,y+8,"TRO VE",6);
				bangmenu(x+36,y+7,10,2,0);	vietchuoi(x+39,y+8,"THOAT",6);
			}
		}
		else if(h==3) //phim enter
		{
			if(kt==1)
			{
				return 1;
			}
			else if(kt==2)
			{
				return 2;
			}
			else if(kt==3)
			{
				return 3;
			}
		}
	}
}
ghisanpham(SANPHAM A[])
{
	int i;
	FILE *f=fopen("sanpham.txt","w");
	fwrite(&a,sizeof(int),1,f);
	for(i=0;i<a;i++)
	{
		fwrite(&A[i],sizeof(SANPHAM),1,f);
	}
	fclose(f);
}
ghikhachhang(KHACHHANG B[])
{
	int i;
	FILE *e=fopen("khachhang.txt","w");
	fwrite(&b,sizeof(int),1,e);
	for(i=0;i<b;i++)
	{
		fwrite(&B[i],sizeof(KHACHHANG),1,e);
	}
	fclose(e);
}
void docsanpham(SANPHAM A[])
{
	int i;
	FILE *f;
	f=fopen("sanpham.txt","r");
	fread(&a,sizeof(int),1,f);
	for(i=0;i<a;i++)
	{
		fread(&A[i],sizeof(SANPHAM),1,f);
	}
	fclose(f);
}
void dockhachhang(KHACHHANG B[])
{
	int i;
	FILE *e;
	e=fopen("khachhang.txt","r");
	fread(&b,sizeof(int),1,e);
	for(i=0;i<b;i++)
	{
		fread(&B[i],sizeof(KHACHHANG),1,e);
	}
	fclose(e);
}
void sapxepsanpham(SANPHAM A[])
{
	int i,j;
	for(i=0;i<a-1;i++)
		for(j=i+1;j<a;j++)
		{
			if(strcmp(A[i].masp,A[j].masp)>0)
			{
				SANPHAM m=A[i];
				A[i]=A[j];
				A[j]=m;
			}
		}
}
void sapxepkhachhang(KHACHHANG B[])
{
	int i,j;
	for(i=0;i<b-1;i++)
		for(j=i+1;j<b;j++)
		{
			if(strcmp(B[i].makh,B[j].makh)>0)
			{
				KHACHHANG m=B[i];
				B[i]=B[j];
				B[j]=m;
			}
		}
}
int tksanpham(SANPHAM A[], char s[])
{
	int i;
	for(i=0;i<a;i++)
	{
		if(stricmp(s,A[i].masp)==0)
		{
			return i;
		}
	}
	return -1;
}
int tkslsp(SANPHAM A[], char s[])
{
	int i;
	for(i=0;i<a;i++)
	{
		if(stricmp(s,A[i].masp)==0)
		{
			return A[i].soluong;
		}
	}
	return -1;
}
int tkgiasp(SANPHAM A[], char s[])
{
	int i;
	for(i=0;i<a;i++)
	{
		if(stricmp(s,A[i].masp)==0)
		{
			return A[i].dongia;
		}
	}
	return -1;
}
int tkspnam(SANPHAM A[],int nam)
{
	int i;
	for(i=0;i<a;i++)
	{
		if(A[i].nam==nam)
		{
			return 1;
		}
	}
	return 0;
}
int tkspthang(SANPHAM A[],int thang)
{
	int i;
	for(i=0;i<a;i++)
	{
		if(A[i].thang==thang)
		{
			return 1;
		}
	}
	return 0;
}
int tkkhnam(KHACHHANG B[],int nam)
{
	int i;
	for(i=0;i<b;i++)
	{
		if(B[i].nam==nam)
		{
			return 1;
		}
	}
	return 0;
}
int tkkhthang(KHACHHANG B[],int thang)
{
	int i;
	for(i=0;i<b;i++)
	{
		if(B[i].thang==thang)
		{
			return 1;
		}
	}
	return 0;
}
void nhapsanpham(SANPHAM A[])
{
	int x=24, y=4, i=0, n, t=1, t1=1, z;
	char soluong[30], dongia[30], ngay[5], thang[5], nam[5];
	nhap:
	bangsanpham(x,y,22);
	vietchuoi(x+105,y-1,"Trang:",7);
	gotoxy(x+112,y-1);
	printf("%d/%d",t1,t);
	vietchuoi(x+1,y-2,"[THEM SAN PHAM]",14);
	vietchuoi(x+1,y-1,"---------------",14);
	textcolor(15);
	for(;;)
	{
		i=a; bangmenu(x+30,1,60,2,13); textcolor(15);
		gotoxy(x+1,y+3);
		printf("%d",i+1);
		n1:
		vietchuoi(x+35,2,"Ma san pham phai co 4 ky tu va khong duoc trung nhau!",14); textcolor(15);
		fflush(stdin);	gioihan(A[i].masp,x+5,y+3,4);
		z=tksanpham(A,A[i].masp);
		if(z!=-1 || strlen(A[i].masp)!=4)
		{
			trolaisua(x+5,y+3,A[i].masp);
			goto n1;
		} viethoafull(A[i].masp);
		n2:
		vietchuoi(x+35,2,"Ma san pham phai co 4 ky tu va khong duoc trung nhau!",0); 
		vietchuoi(x+37,2,"Ten san pham khong duoc co do dai nho hon 4 ky tu!",14);	textcolor(15);
		fflush(stdin);	gioihan(A[i].tensp,x+16,y+3,25);
		if(strlen(A[i].tensp)<4)
		{
			trolaisua(x+16,y+3,A[i].tensp);	goto n2;
		} xoakhoangtrang(A[i].tensp);
		n3:
		vietchuoi(x+37,2,"Ten san pham khong duoc co do dai nho hon 4 ky tu!",0);
		vietchuoi(x+45,2,"Ma nha cung cap phai gom 5 ky tu!",14); textcolor(15);
		fflush(stdin);	gioihan(A[i].manhacc,x+44,y+3,5);
		if(strlen(A[i].manhacc)!=5)
		{
			trolaisua(x+44,y+3,A[i].manhacc);	goto n3;
		} viethoafull(A[i].manhacc);
		tncc:
		vietchuoi(x+45,2,"Ma nha cung cap phai gom 5 ky tu!",0);
		vietchuoi(x+45,2,"Ten nha cung cap khong duoc bo trong!",14); textcolor(15);	fflush(stdin);	gioihan(A[i].tennhacc,x+58,y+3,13);
		if(strlen(A[i].tennhacc)<1)
		{				
			trolaisua(x+58,y+3,A[i].tennhacc);	goto tncc;
		} xoakhoangtrang(A[i].tennhacc);
		do
		{
			trolaisua(x+73,y+3,ngay); xoaso(x+75,y+3,A[i].ngay); xoaso(x+78,y+3,A[i].thang);	trolaisua(x+76,y+3,thang);	trolaisua(x+79,y+3,nam);
			ngay:
			vietchuoi(x+45,2,"Ten nha cung cap khong duoc bo trong!",0);
			vietchuoi(x+40,2,"Nhap ngay tu 1 - 31! (Thang 2 co 28 ngay)",14); textcolor(15);
			fflush(stdin);	gioihan(ngay,x+73,y+3,2);
			if(nhapso(ngay)==0 || strlen(ngay)<1)
			{
				trolaisua(x+73,y+3,ngay);	goto ngay;
			} A[i].ngay=atoi(ngay);
			vietchuoi(x+75,y+3,"/",15);
			thang:
			vietchuoi(x+40,2,"Nhap ngay tu 1 - 31! (Thang 2 co 28 ngay)",0);
			vietchuoi(x+50,2,"Nhap thang tu 1 - 12!",14); textcolor(15);
			fflush(stdin);	gioihan(thang,x+76,y+3,2);
			if(nhapso(thang)==0 || strlen(thang)<1)
			{
				trolaisua(x+76,y+3,thang); goto thang;
			} A[i].thang=atoi(thang);
			vietchuoi(x+78,y+3,"/",15);
			nam:
			vietchuoi(x+50,2,"Nhap thang tu 1 - 12!",0);
			vietchuoi(x+50,2,"Nhap nam co 4 chu so!",14); textcolor(15);
			fflush(stdin);	gioihan(nam,x+79,y+3,4);
			if(nhapso(nam)==0 || strlen(nam)<1)
			{
				trolaisua(x+79,y+3,nam); goto nam;
			} A[i].nam=atoi(nam);
		}while(chuantime(A[i].ngay,A[i].thang,A[i].nam)==0);
		n4:
		vietchuoi(x+50,2,"Nhap nam co 4 chu so!",0);
		vietchuoi(x+48,2,"So luong phai nho hon 999!",14); textcolor(15);
		fflush(stdin);	gioihan(soluong,x+87,y+3,3);
		if(strlen(soluong)<1 || nhapso(soluong)==0)
		{
			trolaisua(x+87,y+3,soluong);	goto n4;
		} A[i].soluong=atoi(soluong);
		n5:
		vietchuoi(x+48,2,"So luong phai nho hon 999!",0);
		vietchuoi(x+48,2,"Don gia phai lon hon 1000!",14); textcolor(15);
		fflush(stdin);	gioihan(dongia,x+93,y+3,9);
		if(strlen(dongia)<4 || nhapso(dongia)==0)
		{
			trolaisua(x+93,y+3,dongia);	goto n5;
		} A[i].dongia=atoi(dongia);
		vietchuoi(x+48,2,"Don gia phai lon hon 1000!",0);
		vietchuoi(x+45,2,"Nhan nut [Tab] de ket thuc nhap!",14); textcolor(15);
		gotoxy(x+105,y+3);	printf("%d",A[i].thanhtien=A[i].dongia*A[i].soluong);
		y=y+2;	i++;	a++;
		if(y-2>20)
		{
			t=t+1;	t1=t1+1;	y=6;
			xoamanhinh();
			goto nhap;
		}
		else if(batphim()==2)
		{
			x=24, y=7;
			vietchuoi(x+4,y+23,"[F2]  SAVE & BACK",6);    vietchuoi(x+30,y+23,"[ESC]  EXIT",6);
			int kt=0;	gotoxy(x+38,y+21);
			for(;;)
			{
				gotoxy(x+38,y+21);	int h=batphim();
				if(h==12) // phim F2
				{
					bangmenu(x+2,y+22,22,2,9);
					vietchuoi(x+4,y+23,"[F2]  SAVE & BACK",15);   vietchuoi(x+30,y+23,"[ESC]  EXIT",6);
					kt=1;	ghisanpham(A);
					gotoxy(5,25);	MessageBox(0, "Ghi File thanh cong!", "THONG BAO", MB_OK);	xoamanhinh();
					sapxepsanpham(A);	insanpham(A); //menu();
				}
				else if(h==4) // phim ESC
				{
					if(kt==0)
					{
						bangmenu(x+28,y+22,22,2,2); bangmenu(x+2,y+22,22,2,0);
						vietchuoi(x+4,y+23,"[F2]  SAVE & BACK",6);   vietchuoi(x+30,y+23,"[ESC]  EXIT",15);
						vietchuoi(x+2,y+26,"Ban chua luu du lieu vua nhap! Ban co muon luu khong?",12);
						bangmenu(x+14,y+27,10,2,14); vietchuoi(x+18,y+28,"YES",15); vietchuoi(x+30,y+28,"NO",6);
						gotoxy(x+38,y+21); t=0;
						for(;;)
						{
							int h=batphim(); gotoxy(x+38,y+21);
							if(h==8) //right
							{
								if(t==0)
								{
									t=1;
									bangmenu(x+26,y+27,10,2,14); bangmenu(x+14,y+27,10,2,0);
									vietchuoi(x+18,y+28,"YES",6); vietchuoi(x+30,y+28,"NO",15);
								}
								else if(t==1)
								{
									t=0;
									bangmenu(x+14,y+27,10,2,14); bangmenu(x+26,y+27,10,2,0);
									vietchuoi(x+18,y+28,"YES",15); vietchuoi(x+30,y+28,"NO",6);
								}
							}
							else if(h==7) //left
							{
								if(t==0)
								{
									t=1;
									bangmenu(x+26,y+27,10,2,14); bangmenu(x+14,y+27,10,2,0);
									vietchuoi(x+18,y+28,"YES",6); vietchuoi(x+30,y+28,"NO",15);
								}
								else if(t==1)
								{
									t=0;
									bangmenu(x+14,y+27,10,2,14); bangmenu(x+26,y+27,10,2,0);
									vietchuoi(x+18,y+28,"YES",15); vietchuoi(x+30,y+28,"NO",6);
								}
							}
							else if(h==3)
							{
								if(t==0)
								{
									ghisanpham(A);
									gotoxy(5,25);	MessageBox(0, "Ghi File thanh cong!", "THONG BAO", MB_OK);
									gotoxy(x+2,y+29); exit(0);
								}
								else if(t==1)
								{
									gotoxy(5,25);	MessageBox(0, "Dang thoat chuong trinh!", "THONG BAO", MB_OK);
									gotoxy(x+2,y+29); exit(0);
								}
							}
						}
					}
				}
			}
		}
	}
}
void insanpham(SANPHAM A[])
{
	int x=24, y=4, i, t, t1=1, dem=0;
	if(a>10 && (a%10)!=0)
	{
		t=(a/10)+1;
	}
	else if(a>10 && (a%10)==0)
	{
		t=a/10;
	}
	else if(a<=10)
	{
		t=1;
		t1=1;
	}
	in:
	bangsanpham(x,y,23);
	vietchuoi(x+1,y-2,"[THONG TIN SAN PHAM]",14);
	vietchuoi(x+1,y-1,"--------------------",14);
	vietchuoi(x+80,y-1,"nhan [TAB] de vao menu",12);
	vietchuoi(x+3,y+24,"Nhan nut [RIGHT] de sang trang, [LEFT] de tro ve trang truoc!!",12);
	vietchuoi(x+105,y-1,"Trang:",7);
	gotoxy(x+112,y-1); printf("%d/%d",t1,t);
	for(;;)
	{
		i=dem; dem<a;	textcolor(15);
		gotoxy(x+1,y+3);	printf("%d",i+1);
		gotoxy(x+5,y+3);	printf("%s",A[i].masp);
		gotoxy(x+16,y+3);	printf("%s",A[i].tensp);
		gotoxy(x+44,y+3);	printf("%s",A[i].manhacc);
		gotoxy(x+58,y+3);	printf("%s",A[i].tennhacc);
		gotoxy(x+73,y+3);	printf("%-2d/%-2d/%-4d",A[i].ngay,A[i].thang,A[i].nam);
		gotoxy(x+87,y+3);	printf("%d",A[i].soluong);
		gotoxy(x+93,y+3);	printf("%d",A[i].dongia);
		gotoxy(x+105,y+3);	printf("%d",A[i].thanhtien);
		y=y+2;	dem++;
		if(y-2>20)
		{
			for(;;)
			{
				int h=batphim();	gotoxy(x+66,28);
				if(h==8 && a-dem-1>=0)// Mui ten phai
				{
					xoamanhinh();
					t1++;	dem=10*(t1-1);
					y=4;	goto in;
				}
				else if(h==7 && t1!=1)// Mui ten trai
				{
					xoamanhinh();
					t1--;	dem=10*(t1-1);
					y=4;	goto in;
				}
			 	else if(h==2) // phim tab
				{
					int mn=menu1(30,9);
					if(mn==1)
					{
						xoamanhinh();	nhapsanpham(A);
					}
					else if(mn==2)
					{
						xoamanhinh();	timkiemsanpham(A);
					}
					else if(mn==3)
					{
						xoamanhinh();	suasanpham(A);
					}
					else if(mn==4)
					{
						xoamanhinh();	xoasanpham(A);
					}
					else if(mn==5)
					{
						xoamanhinh();	menu();
					}
					else if(mn==6)
					{
						gotoxy(5,25);	MessageBox(0, "Dang thoat chuong trinh!", "THONG BAO", MB_OK);
						gotoxy(3,32);	exit(0);
					}
				}
			}
		}
	}
}
int timkiemsanpham(SANPHAM A[])
{
	int i, z, x, y;	char s[35];
	nhap:
	bangmenu(5,3,35,2,3);	vietchuoi(6,4,"Nhap ma san pham:  ",11);
	bangmenu(80,1,38,2,2);	vietchuoi(90,2,"TIM KIEM SAN PHAM",14);
	textcolor(15);	fflush(stdin);	gioihan(s,25,4,4);
	docsanpham(A);	z=tksanpham(A,s);
	if(z==-1)
	{
		gotoxy(5,25);	MessageBox(0, "San pham ban vua nhap khong ton tai!", "THONG BAO", MB_OK);
		trolaisua(25,4,s);	goto nhap;
	}
	else
	{
		textcolor(3);	bangsanpham(x=10,y=10,6);
		textcolor(12);	vietchuoi(x+3,y-1,"[ THONG TIN SAN PHAM ]",14);
		for(i=z;i<a;i++)
		{
			textcolor(15);	gotoxy(x+1,y+3);	printf("%d",i+1);
			gotoxy(x+5,y+3);	printf("%s",A[i].masp);
			gotoxy(x+16,y+3);	printf("%s",A[i].tensp);
			gotoxy(x+44,y+3);	printf("%s",A[i].manhacc);
			gotoxy(x+58,y+3);	printf("%s",A[i].tennhacc);
			gotoxy(x+73,y+3);	printf("%-2d/%-2d/%-4d",A[i].ngay,A[i].thang,A[i].nam);
			gotoxy(x+87,y+3);	printf("%d",A[i].soluong);
			gotoxy(x+93,y+3);	printf("%d",A[i].dongia);
			gotoxy(x+105,y+3);	printf("%d",A[i].thanhtien);
			y=y+2;	break;
		}
		int mn=menu2(10,15);
		if(mn==1)
		{
			xoamanhinh();	suasanpham(A);
		}
		else if(mn==2)
		{
			xoamanhinh();	xoasanpham(A);
		}
		else if(mn==3)
		{
			xoamanhinh();	docsanpham(A);	sapxepsanpham(A);	insanpham(A);
		}
		else if(mn==4)
		{
			gotoxy(5,25);	MessageBox(0, "Dang thoat chuong trinh!", "THONG BAO", MB_OK);
			gotoxy(x+5,y+15);	exit(0);
		}
	}
}
int suasanpham(SANPHAM A[])
{
	int i, z, x, y, t;	char sua[35], ngay[35], thang[35], nam[35], soluong[35], dongia[35], ma[30];
	nhap:
	bangmenu(5,3,35,2,3);	vietchuoi(6,4,"Nhap ma san pham:  ",11);
	bangmenu(80,1,38,2,2);	vietchuoi(90,2,"CHINH SUA SAN PHAM",14);
	textcolor(15);	fflush(stdin);	gioihan(sua,25,4,4);
	docsanpham(A);	z=tksanpham(A,sua);
	if(z==-1)
	{
		gotoxy(5,25);	MessageBox(0, "San pham ban vua nhap khong ton tai!", "THONG BAO", MB_OK);
		trolaisua(25,4,sua);	goto nhap;
	}
	else
	{
		textcolor(3);	bangsanpham(x=10,y=10,6);
		textcolor(12);	vietchuoi(x+3,y-1,"[ THONG TIN SAN PHAM ]",14);
		for(i=z;i<a;i++)
		{
			textcolor(15);	gotoxy(x+1,y+3);	printf("%d",i+1);
			gotoxy(x+5,y+3);	printf("%s",A[i].masp);
			gotoxy(x+16,y+3);	printf("%s",A[i].tensp);
			gotoxy(x+44,y+3);	printf("%s",A[i].manhacc);
			gotoxy(x+58,y+3);	printf("%s",A[i].tennhacc);
			gotoxy(x+73,y+3);	printf("%-2d/%-2d/%-4d",A[i].ngay,A[i].thang,A[i].nam);
			gotoxy(x+87,y+3);	printf("%d",A[i].soluong);
			gotoxy(x+93,y+3);	printf("%d",A[i].dongia);
			gotoxy(x+105,y+3);	printf("%d",A[i].thanhtien);
			y=y+2;	strcpy(ma,A[i].masp);	A[i]=A[i+1];	break;
		}
	}
	textcolor(2);	bangsanpham(x=10,y=20,6);
	vietchuoi(x+3,y-1,"[ SUA SAN PHAM ]",14);	textcolor(15);
	{
		i=z;	bangmenu(x+30,17,60,2,13); textcolor(15);
		gotoxy(x+1,y+3);
		printf("%d",i+1);
		strcpy(A[i].masp,ma);	gotoxy(x+5,y+3); printf("%s",A[i].masp);
		n2:
		vietchuoi(x+35,18,"Ma san pham phai co 4 ky tu va khong duoc trung nhau!",0); 
		vietchuoi(x+37,18,"Ten san pham khong duoc co do dai nho hon 4 ky tu!",14);	textcolor(15);
		fflush(stdin);	gioihan(A[i].tensp,x+16,y+3,25);
		if(strlen(A[i].tensp)<4)
		{
			trolaisua(x+16,y+3,A[i].tensp);	goto n2;
		} xoakhoangtrang(A[i].tensp);
		n3:
		vietchuoi(x+37,18,"Ten san pham khong duoc co do dai nho hon 4 ky tu!",0);
		vietchuoi(x+45,18,"Ma nha cung cap phai gom 5 ky tu!",14); textcolor(15);
		fflush(stdin);	gioihan(A[i].manhacc,x+44,y+3,5);
		if(strlen(A[i].manhacc)!=5)
		{
			trolaisua(x+44,y+3,A[i].manhacc);	goto n3;
		} viethoafull(A[i].manhacc);
		tncc:
		vietchuoi(x+45,2,"Ma nha cung cap phai gom 5 ky tu!",0);
		vietchuoi(x+45,2,"Ten nha cung cap khong duoc bo trong!",14); textcolor(15);
		fflush(stdin);	gioihan(A[i].tennhacc,x+58,y+3,13);
		if(strlen(A[i].tennhacc)<1)
		{
			trolaisua(x+58,y+3,A[i].tennhacc);	goto tncc;
		} xoakhoangtrang(A[i].tennhacc);
		do
		{
			trolaisua(x+73,y+3,ngay); xoaso(x+75,y+3,A[i].ngay); xoaso(x+78,y+3,A[i].thang);	trolaisua(x+76,y+3,thang);	trolaisua(x+79,y+3,nam);
			ngay:
			vietchuoi(x+45,18,"Ten nha cung cap khong duoc bo trong!",0);
			vietchuoi(x+40,18,"Nhap ngay tu 1 - 31! (Thang 2 co 28 ngay)",14); textcolor(15);
			fflush(stdin);	gioihan(ngay,x+73,y+3,2);
			if(nhapso(ngay)==0 || strlen(ngay)<1)
			{
				trolaisua(x+73,y+3,ngay);	goto ngay;
			} A[i].ngay=atoi(ngay);
			vietchuoi(x+75,y+3,"/",15);
			thang:
			vietchuoi(x+40,18,"Nhap ngay tu 1 - 31! (Thang 2 co 28 ngay)",0);
			vietchuoi(x+50,18,"Nhap thang tu 1 - 12!",14); textcolor(15);
			fflush(stdin);	gioihan(thang,x+76,y+3,2);
			if(nhapso(thang)==0 || strlen(thang)<1)
			{
				trolaisua(x+76,y+3,thang); goto thang;
			} A[i].thang=atoi(thang);
			vietchuoi(x+78,y+3,"/",15);
			nam:
			vietchuoi(x+50,18,"Nhap thang tu 1 - 12!",0);
			vietchuoi(x+50,18,"Nhap nam co 4 chu so!",14); textcolor(15);
			fflush(stdin);	gioihan(nam,x+79,y+3,4);
			if(nhapso(nam)==0 || strlen(nam)<1)
			{
				trolaisua(x+79,y+3,nam); goto nam;
			} A[i].nam=atoi(nam);
		}while(chuantime(A[i].ngay,A[i].thang,A[i].nam)==0);
		n4:
		vietchuoi(x+50,18,"Nhap nam co 4 chu so!",0);
		vietchuoi(x+48,18,"So luong phai nho hon 999!",14); textcolor(15);
		fflush(stdin);	gioihan(soluong,x+87,y+3,3);
		if(strlen(soluong)<1 || nhapso(soluong)==0)
		{
			trolaisua(x+87,y+3,soluong);	goto n4;
		} A[i].soluong=atoi(soluong);
		n5:
		vietchuoi(x+48,18,"So luong phai nho hon 999!",0);
		vietchuoi(x+48,18,"Don gia phai lon hon 1000!",14); textcolor(15);
		fflush(stdin);	gioihan(dongia,x+93,y+3,9);
		if(strlen(dongia)<4 || nhapso(dongia)==0)
		{
			trolaisua(x+93,y+3,dongia);	goto n5;
		} A[i].dongia=atoi(dongia);
		vietchuoi(x+48,18,"Don gia phai lon hon 1000!",0); textcolor(15);
		gotoxy(x+105,y+3);	printf("%d",A[i].thanhtien=A[i].dongia*A[i].soluong);
		y=y+2;
	}
	int mn=menu5(10,23);
	if(mn==1)
	{
		ghisanpham(A);
		gotoxy(5,25);	MessageBox(0, "Ghi File thanh cong!", "THONG BAO", MB_OK);
		xoamanhinh();	docsanpham(A);	sapxepsanpham(A);	insanpham(A);
	}
	else if(mn==2)
	{
		xoamanhinh();	docsanpham(A);	sapxepsanpham(A);	insanpham(A);
	}
	else if(mn==3)
	{
		gotoxy(5,25);	MessageBox(0, "Dang thoat chuong trinh!", "THONG BAO", MB_OK);
		gotoxy(x+5,y+20);	exit(0);
	}
}
int xoasanpham(SANPHAM A[])
{
	int i, x, y, z;	char xoa[35];
	nhap:
	bangmenu(5,3,35,2,3);	vietchuoi(6,4,"Nhap ma san pham:  ",11);
	bangmenu(80,1,31,2,2);	vietchuoi(90,2,"XOA SAN PHAM",14);
	fflush(stdin);	gioihan(xoa,25,4,4);	z=tksanpham(A,xoa);
	if(z==-1)
	{
		gotoxy(5,25);	MessageBox(0, "San pham ban vua nhap khong ton tai!", "THONG BAO", MB_OK);
		trolaisua(25,4,xoa);	goto nhap;
	}
	else
	{
		textcolor(3);	bangsanpham(x=10,y=10,6);
		textcolor(12);	vietchuoi(x+3,y-1,"[ THONG TIN SAN PHAM ]",14);
		for(i=z;i<a;i++)
		{
			textcolor(15);	gotoxy(x+1,y+3);
			printf("%d",i+1);
			gotoxy(x+5,y+3);	printf("%s",A[i].masp);
			gotoxy(x+16,y+3);	printf("%s",A[i].tensp);
			gotoxy(x+44,y+3);	printf("%s",A[i].manhacc);
			gotoxy(x+58,y+3);	printf("%s",A[i].tennhacc);
			gotoxy(x+73,y+3);	printf("%-2d/%-2d/%-4d",A[i].ngay,A[i].thang,A[i].nam);
			gotoxy(x+87,y+3);	printf("%d",A[i].soluong);
			gotoxy(x+93,y+3);	printf("%d",A[i].dongia);
			gotoxy(x+105,y+3);	printf("%d",A[i].thanhtien=A[i].dongia*A[i].soluong);
			y=y+2;	break;
		}
		int mn1=menu4(5,12);
		if(mn1==1)
		{
			for(i=z;i<a;i++)
			{
				A[i]=A[i+1];
				z--;
			}
			a--;
			ghisanpham(A);	gotoxy(5,25);	MessageBox(0, "Xoa san pham thanh cong!", "THONG BAO", MB_OK);
			int mn2=menu3(10,11);
			if(mn2==1)
			{
				xoamanhinh();	goto nhap;
			}
			else if(mn2==2)
			{
				xoamanhinh();	docsanpham(A);	sapxepsanpham(A);	insanpham(A);
			}
			else if(mn2==3)
			{
				gotoxy(5,25);	MessageBox(0, "Dang thoat chuong trinh!", "THONG BAO", MB_OK);
				gotoxy(x+5,y+16);	exit(0);
			}
		}
		else if(mn1==2)
		{
			xoamanhinh();	docsanpham(A);	sapxepsanpham(A);	insanpham(A);
		}
	}
}
int tkkhachhang(KHACHHANG B[], char kh[])
{
	int i;
	for(i=0;i<b;i++)
	{
		if(stricmp(kh,B[i].makh)==0)
		{
			return i;
		}
	}
	return -1;
}
void nhapkhachhang(KHACHHANG B[], SANPHAM A[])
{
	int x=3, y=3, i=0, j=0, n, t=1, t1=1, z, o, sl, vt, gia;
	char ngay[30], thang[30], nam[30], soluong[30], giaban[30];
	docsanpham(A);
	nhap:
	bangkhachhang(x,y,22);	vietchuoi(x+135,y-1,"Trang:",7);
	gotoxy(x+142,y-1);	printf("%d/%d",t1,t);
	vietchuoi(x+1,y-2,"[ THEM KHACH HANG ]",14);	vietchuoi(x+1,y-1,"-------------------",14);
	for(;;)
	{
		i=b;  bangmenu(x+40,0,70,2,13);	textcolor(15);
		gotoxy(x+1,y+3);	printf("%d",i+1);
		n1:
		vietchuoi(x+50,1,"Ma khach hang khong duoc trung nhau va phai co 4 ky tu!",14); textcolor(15);
		fflush(stdin);	gioihan(B[i].makh,x+5,y+3,4);
		z=tkkhachhang(B,B[i].makh);
		if(z!=-1 || strlen(B[i].makh)!=4)
		{
			trolaisua(x+5,y+3,B[i].makh);	goto n1;
		}	viethoafull(B[i].makh);
		n2:
		vietchuoi(x+50,1,"Ma khach hang khong duoc trung nhau va phai co 4 ky tu!",0);
		vietchuoi(x+45,1,"Ten khach hang khong duoc khong duoc duoi co 4 ky tu va co so!",14); textcolor(15);
		fflush(stdin);	gioihan(B[i].tenkh,x+15,y+3,25);
		if(strlen(B[i].tenkh)<4 || nhapchu(B[i].tenkh)==0)
		{
			trolaisua(x+15,y+3,B[i].tenkh);	goto n2;
		}	chuanhoaten(B[i].tenkh);
		n3:
		vietchuoi(x+45,1,"Ten khach hang khong duoc khong duoc duoi co 4 ky tu va co so!",0);
		vietchuoi(x+50,1,"Dia chi khach hang khong duoc khong duoc duoi co 3 ky tu!",14); textcolor(15);
		gotoxy(x+43,y+3);
		fflush(stdin);	gioihan(B[i].diachi,x+43,y+3,15);
		if(strlen(B[i].diachi)<3)
		{
			trolaisua(x+43,y+3,B[i].diachi);	goto n2;
		} chuanhoaten(B[i].diachi);
		sdt:
		vietchuoi(x+50,1,"Dia chi khach hang khong duoc khong duoc duoi co 3 ky tu!",0);
		vietchuoi(x+50,1,"So dien thoai khach hang la so va khong nho hon 9 ky tu!",14); textcolor(15);
		fflush(stdin);	gioihan(B[i].sdt,x+61,y+3,12);
		if(strlen(B[i].sdt)<9 || nhapso(B[i].sdt)==0)
		{
			trolaisua(x+61,y+3,B[i].sdt);	goto sdt;
		}
		do
		{
			trolaisua(x+77,y+3,ngay); trolaisua(x+80,y+3,thang); trolaisua(x+83,y+3,nam); trolaisua(x+79,y+3,ngay); trolaisua(x+82,y+3,thang);
			ngay:
			vietchuoi(x+50,1,"So dien thoai khach hang la so va khong nho hon 9 ky tu!",0);
			vietchuoi(x+50,1,"Nhap ngay tu 1 - 31! (Thang 2 co 28 ngay)",14); textcolor(15);
			fflush(stdin);	gioihan(ngay,x+77,y+3,2);
			if(strlen(ngay)<1 || nhapso(ngay)==0)
			{
				trolaisua(x+77,y+3,ngay); goto ngay;
			} B[i].ngay=atoi(ngay);
			vietchuoi(x+79,y+3,"/",15);
			thang:
			vietchuoi(x+50,1,"Nhap ngay tu 1 - 31! (Thang 2 co 28 ngay)",0);
			vietchuoi(x+65,1,"Nhap thang tu 1 - 12!",14); textcolor(15);
			fflush(stdin);	gioihan(thang,x+80,y+3,2);
			if(strlen(thang)<1 || nhapso(thang)==0)
			{
				trolaisua(x+80,y+3,thang); goto thang;
			} B[i].thang=atoi(thang);
			vietchuoi(x+82,y+3,"/",15);
			nam:
			vietchuoi(x+65,1,"Nhap thang tu 1 - 12!",0);
			vietchuoi(x+65,1,"Nhap nam gom co 4 chu so!",14); textcolor(15);
			fflush(stdin);	gioihan(nam,x+83,y+3,4);
			if(strlen(nam)<1 || nhapso(nam)==0)
			{
				trolaisua(x+83,y+3,nam); goto nam;
			} B[i].nam=atoi(nam);
		}while(chuantime(B[i].ngay,B[i].thang,B[i].nam)==0);
		buy:
		vietchuoi(x+65,1,"Nhap nam gom co 4 chu so!",0);	vietchuoi(x+60,1,"Mat hang ban vua nhap da het!",0);
		vietchuoi(x+55,1,"Ma mat hang phai trung voi ma san pham!",14); textcolor(15);
		het:
		fflush(stdin);	gioihan(B[i].muahang,x+90,y+3,4);
		o=tksanpham(A,B[i].muahang);
		sl=tkslsp(A,B[i].muahang);
		if(o==-1 || strlen(B[i].muahang)<1)
		{
			trolaisua(x+90,y+3,B[i].muahang);	goto buy;
		}
		if(sl==0)
		{
			vietchuoi(x+55,1,"Ma mat hang phai trung voi ma san pham!",0);
			vietchuoi(x+60,1,"Mat hang ban vua nhap da het!",14); textcolor(15);
			trolaisua(x+90,y+3,B[i].muahang);	goto het;
		}
		sl:
		vietchuoi(x+55,1,"Ma mat hang phai trung voi ma san pham!",0);
		vietchuoi(x+50,1,"So luong mat hang phai nho hon so luong dang co!",14); textcolor(15);
		fflush(stdin);	gioihan(soluong,x+120,y+3,3);	B[i].soluong=atoi(soluong);
		vt=o;
		if(B[i].soluong<1 || sl<B[i].soluong || nhapso(soluong)==0)
		{
			trolaisua(x+120,y+3,soluong);	goto sl;
		}
		sl=sl-B[i].soluong;		A[o].soluong=A[o].soluong-B[i].soluong;
		gia:
		vietchuoi(x+50,1,"So luong mat hang phai nho hon so luong dang co!",0);	
		vietchuoi(x+55,1,"Gia ban phai lon hon hoac bang gia nhap!",14); textcolor(15);
		fflush(stdin);	gioihan(giaban,x+133,y+3,9);	B[i].giaban=atoi(giaban);
		gia=tkgiasp(A,B[i].muahang);
		if(strlen(giaban)<1 || gia>B[i].giaban || nhapso(giaban)==0)
		{
			trolaisua(x+133,y+3,giaban);	goto gia;
		}
		vietchuoi(x+55,1,"Gia ban phai lon hon hoac bang gia nhap!",0);
		vietchuoi(x+60,1,"Nhan nut [Tab] de ket thuc nhap!",14); textcolor(15);
		gotoxy(x+146,y+3);	
		printf("%d",B[i].thanhtien=B[i].soluong*B[i].giaban);
		y=y+2;	i++;	b++;
		if(y-2>20)
		{
			t=t+1;	t1=t1+1;	y=3;
			xoamanhinh();	goto nhap;
		}
		else if(batphim()==2)
		{
			x=5, y=6;
			vietchuoi(x+4,y+23,"[F2]  SAVE & BACK",6);    vietchuoi(x+30,y+23,"[ESC]  EXIT",6);
			int kt=0;	gotoxy(x+38,y+20);
			for(;;)
			{
				gotoxy(x+38,y+20);	int h=batphim();
				if(h==12) // phim F2
				{
					bangmenu(x+2,y+22,22,2,9);
					vietchuoi(x+4,y+23,"[F2]  SAVE & BACK",15);   vietchuoi(x+30,y+23,"[ESC]  EXIT",6);
					kt=1;	ghikhachhang(B); ghisanpham(A);
					gotoxy(5,25);	MessageBox(0, "Ghi File thanh cong!", "THONG BAO", MB_OK);	xoamanhinh(); sapxepkhachhang(B);
					inkhachhang(B);
				}
				else if(h==4) // phim ESC
				{
					if(kt==0)
					{
						bangmenu(x+28,y+22,22,2,2); bangmenu(x+2,y+22,22,2,0);
						vietchuoi(x+4,y+23,"[F2]  SAVE & BACK",6);   vietchuoi(x+30,y+23,"[ESC]  EXIT",15);
						vietchuoi(x+2,y+26,"Ban chua luu du lieu vua nhap! Ban co muon luu khong?",12);
						bangmenu(x+14,y+27,10,2,14); vietchuoi(x+18,y+28,"YES",15); vietchuoi(x+30,y+28,"NO",6);
						gotoxy(x+38,y+21); t=0;
						for(;;)
						{
							int h=batphim(); gotoxy(x+38,y+21);
							if(h==8) //right
							{
								if(t==0)
								{
									t=1;
									bangmenu(x+26,y+27,10,2,14); bangmenu(x+14,y+27,10,2,0);
									vietchuoi(x+18,y+28,"YES",6); vietchuoi(x+30,y+28,"NO",15);
								}
								else if(t==1)
								{
									t=0;
									bangmenu(x+14,y+27,10,2,14); bangmenu(x+26,y+27,10,2,0);
									vietchuoi(x+18,y+28,"YES",15); vietchuoi(x+30,y+28,"NO",6);
								}
							}
							else if(h==7) //left
							{
								if(t==0)
								{
									t=1;
									bangmenu(x+26,y+27,10,2,14); bangmenu(x+14,y+27,10,2,0);
									vietchuoi(x+18,y+28,"YES",6); vietchuoi(x+30,y+28,"NO",15);
								}
								else if(t==1)
								{
									t=0;
									bangmenu(x+14,y+27,10,2,14); bangmenu(x+26,y+27,10,2,0);
									vietchuoi(x+18,y+28,"YES",15); vietchuoi(x+30,y+28,"NO",6);
								}
							}
							else if(h==3)
							{
								if(t==0)
								{
									ghikhachhang(B); ghisanpham(A);
									gotoxy(5,25);	MessageBox(0, "Ghi File thanh cong!", "THONG BAO", MB_OK);
									gotoxy(x+2,y+29); exit(0);
								}
								else if(t==1)
								{
									gotoxy(5,25);	MessageBox(0, "Dang thoat chuong trinh!", "THONG BAO", MB_OK);
									gotoxy(x+2,y+29); exit(0);
								}
							}
						}
					}
				}
			}
		}
	}
}
void inkhachhang(KHACHHANG B[])
{
	int x=3, y=3, i, t, t1=1, dem=0;
	if(b>10 && (b%10)!=0)
	{
		t=(b/10)+1;
	}
	else if(b>10 && (b%10)==0)
	{
		t=b/10;
	}
	else if(b<=10)
	{
		t=1;
		t1=1;
	}
	khachhang:
	bangkhachhang(x,y,23);	vietchuoi(x+1,y-2,"[ THONG TIN KHACH HANG ]",14);	vietchuoi(x+1,y-1,"------------------------",14);
	vietchuoi(x+110,y-1,"nhan [TAB] de vao menu",12);
	vietchuoi(x+3,y+24,"Nhan nut [RIGHT] de sang trang, [LEFT] de tro ve trang truoc!!",12);
	vietchuoi(x+135,y-1,"Trang:",7);	gotoxy(x+142,y-1); printf("%d/%d",t1,t);
	for(;;)
	{
		i=dem; dem<b;
		textcolor(15);	gotoxy(x+1,y+3);	printf("%d",i+1);
		gotoxy(x+5,y+3);	printf("%s",B[i].makh);
		gotoxy(x+15,y+3);	printf("%s",B[i].tenkh);
		gotoxy(x+43,y+3);	printf("%s",B[i].diachi);
		gotoxy(x+61,y+3);	printf("%s",B[i].sdt);
		gotoxy(x+77,y+3);	printf("%d/%d/%d",B[i].ngay,B[i].thang,B[i].nam);
		gotoxy(x+90,y+3);	printf("%s",B[i].muahang);
		gotoxy(x+120,y+3);	printf("%d",B[i].soluong);
		gotoxy(x+133,y+3);	printf("%d",B[i].giaban);
		gotoxy(x+146,y+3);	printf("%d",B[i].thanhtien);
		y=y+2;	dem++;
		if(y-2>20)
		{
			for(;;)
			{
				int h=batphim();	gotoxy(x+66,27);
				if(h==8 && b-dem-1>=0) // Mui ten phai
				{
					xoamanhinh();
					t1++;	dem=10*(t1-1);	y=3;
					goto khachhang;
				}
				else if(h==7 && t1!=1) // Mui ten trai
				{
					xoamanhinh();
					t1--;	dem=10*(t1-1);	y=3;
					goto khachhang;
				}
				else if(h==2) //phim tab
				{
					gotoxy(x+66,y+4); int mn=menu1(13,8);
					if(mn==1)
					{
						xoamanhinh(); docsanpham(A);	nhapkhachhang(B,A);
					}
					else if(mn==2)
					{
						xoamanhinh();	timkiemkhachhang(B);
					}
					else if(mn==3)
					{
						xoamanhinh();	suakhachhang(B,A);
					}
					else if(mn==4)
					{
						xoamanhinh();	xoakhachhang(B);
					}
					else if(mn==5)
					{
						xoamanhinh();	menu();
					}
					else if(mn==6)
					{
						gotoxy(5,25);	MessageBox(0, "Dang thoat chuong trinh!", "THONG BAO", MB_OK);
						gotoxy(x+3,y+8);	exit(0);
					}
				}
			}
		}
	}
}
int timkiemkhachhang(KHACHHANG B[])
{
	int i, z, x, y;	char s[35];
	nhap:
	bangmenu(5,3,37,2,3);	vietchuoi(6,4,"Nhap ma khach hang:  ",11);
	bangmenu(80,1,40,2,2);	vietchuoi(90,2,"TIM KIEM KHACH HANG",14);
	textcolor(15);	fflush(stdin);	gioihan(s,27,4,4);
	dockhachhang(B);	z=tkkhachhang(B,s);
	if(z==-1)
	{
		gotoxy(5,25);	MessageBox(0, "Khach hang ban vua nhap khong ton tai!", "THONG BAO", MB_OK);
		trolaisua(27,4,s);	goto nhap;
	}
	else
	{
		textcolor(3);	bangkhachhang(x=3,y=10,6);
		textcolor(12);	vietchuoi(x+3,y-1,"[ THONG TIN KHACH HANG ]",14);
		for(i=z;i<b;i++)
		{
			textcolor(15);	gotoxy(x+1,y+3);	printf("%d",i+1);
			gotoxy(x+5,y+3);	printf("%s",B[i].makh);
			gotoxy(x+15,y+3);	printf("%s",B[i].tenkh);
			gotoxy(x+43,y+3);	printf("%s",B[i].diachi);
			gotoxy(x+61,y+3);	printf("%s",B[i].sdt);
			gotoxy(x+77,y+3);	printf("%d/%d/%d",B[i].ngay,B[i].thang,B[i].nam);
			gotoxy(x+90,y+3);	printf("%s",B[i].muahang);
			gotoxy(x+120,y+3);	printf("%d",B[i].soluong);
			gotoxy(x+133,y+3);	printf("%d",B[i].giaban);
			gotoxy(x+146,y+3);	printf("%d",B[i].thanhtien);
			y=y+2;	break;
		}
		int mn=menu2(3,15);
		if(mn==1)
		{
			xoamanhinh();	suakhachhang(B,A);
		}
		else if(mn==2)
		{
			xoamanhinh();	xoakhachhang(B);
		}
		else if(mn==3)
		{
			xoamanhinh();	dockhachhang(B); sapxepkhachhang(B);	inkhachhang(B);
		}
		else if(mn==4)
		{
			gotoxy(5,25);	MessageBox(0, "Dang thoat chuong trinh!", "THONG BAO", MB_OK);
			gotoxy(x+5,y+15);	exit(0);
		}
	}
}
int suakhachhang(KHACHHANG B[], SANPHAM A[])
{
	int i, z, x, y, o, sl, vt, ss, slg, gia;	
	char sua[35], ma[30], ngay[30], thang[30], nam[30], soluong[30], giaban[30];
	docsanpham(A);
	nhap:
	bangmenu(5,3,35,2,3);	vietchuoi(6,4,"Nhap ma khach hang:  ",11);
	bangmenu(80,1,40,2,2);	vietchuoi(90,2,"CHINH SUA KHACH HANG",14);
	textcolor(15);	fflush(stdin);	gioihan(sua,27,4,4);
	dockhachhang(B);	z=tkkhachhang(B,sua);
	if(z==-1)
	{
		gotoxy(5,25);	MessageBox(0, "Khach hang ban vua nhap khong ton tai!", "THONG BAO", MB_OK);
		trolaisua(27,4,sua);	goto nhap;
	}
	else
	{
		textcolor(3);	bangkhachhang(x=3,y=10,6);
		textcolor(12);	vietchuoi(x+3,y-1,"[ THONG TIN KHACH HANG ]",14);
		for(i=z;i<b;i++)
		{
			textcolor(15);	gotoxy(x+1,y+3);	printf("%d",i+1);
			gotoxy(x+5,y+3);	printf("%s",B[i].makh);
			gotoxy(x+15,y+3);	printf("%s",B[i].tenkh);
			gotoxy(x+43,y+3);	printf("%s",B[i].diachi);
			gotoxy(x+61,y+3);	printf("%s",B[i].sdt);
			gotoxy(x+77,y+3);	printf("%d/%d/%d",B[i].ngay,B[i].thang,B[i].nam);
			gotoxy(x+90,y+3);	printf("%s",B[i].muahang);
			gotoxy(x+120,y+3);	printf("%d",B[i].soluong);
			gotoxy(x+133,y+3);	printf("%d",B[i].giaban);
			gotoxy(x+146,y+3);	printf("%d",B[i].thanhtien);
			y=y+2;	strcpy(ma,B[i].makh);	slg=B[i].soluong;	B[i]=B[i+1];	break;
		}
	}
	textcolor(2);	bangkhachhang(x=3,y=20,6);	vietchuoi(x+3,y-1,"[ SUA THONG TIN KHACH HANG ]",14);
	textcolor(15);
	{
		i=z;	bangmenu(x+40,17,70,2,13);	textcolor(15);
		gotoxy(x+1,y+3);	printf("%d",i+1);
		gotoxy(x+5,y+3);	strcpy(B[i].makh,ma); printf("%s",B[i].makh);
		n2:
		vietchuoi(x+50,18,"Ma khach hang khong duoc trung nhau va phai co 4 ky tu!",0);
		vietchuoi(x+45,18,"Ten khach hang khong duoc khong duoc duoi co 4 ky tu va co so!",14); textcolor(15);
		fflush(stdin);	gioihan(B[i].tenkh,x+15,y+3,25);
		if(strlen(B[i].tenkh)<4 || nhapchu(B[i].tenkh)==0)
		{
			trolaisua(x+15,y+3,B[i].tenkh);	goto n2;
		}	chuanhoaten(B[i].tenkh);
		n3:
		vietchuoi(x+45,18,"Ten khach hang khong duoc khong duoc duoi co 4 ky tu va co so!",0);
		vietchuoi(x+50,18,"Dia chi khach hang khong duoc khong duoc duoi co 3 ky tu!",14); textcolor(15);
		gotoxy(x+43,y+3);
		fflush(stdin);	gioihan(B[i].diachi,x+43,y+3,15);
		if(strlen(B[i].diachi)<3)
		{
			trolaisua(x+43,y+3,B[i].diachi);	goto n2;
		} chuanhoaten(B[i].diachi);
		sdt:
		vietchuoi(x+50,18,"Dia chi khach hang khong duoc khong duoc duoi co 3 ky tu!",0);
		vietchuoi(x+50,18,"So dien thoai khach hang la so va khong nho hon 9 ky tu!",14); textcolor(15);
		fflush(stdin);	gioihan(B[i].sdt,x+61,y+3,12);
		if(strlen(B[i].sdt)<9 || nhapso(B[i].sdt)==0)
		{
			trolaisua(x+61,y+3,B[i].sdt);	goto sdt;
		}
		do
		{
			trolaisua(x+77,y+3,ngay); trolaisua(x+80,y+3,thang); trolaisua(x+83,y+3,nam); trolaisua(x+79,y+3,ngay); trolaisua(x+82,y+3,thang);
			ngay:
			vietchuoi(x+50,18,"So dien thoai khach hang la so va khong nho hon 9 ky tu!",0);
			vietchuoi(x+50,18,"Nhap ngay tu 1 - 31! (Thang 2 co 28 ngay)",14); textcolor(15);
			fflush(stdin);	gioihan(ngay,x+77,y+3,2);
			if(strlen(ngay)<1 || nhapso(ngay)==0)
			{
				trolaisua(x+77,y+3,ngay); goto ngay;
			} B[i].ngay=atoi(ngay);
			vietchuoi(x+79,y+3,"/",15);
			thang:
			vietchuoi(x+50,18,"Nhap ngay tu 1 - 31! (Thang 2 co 28 ngay)",0);
			vietchuoi(x+65,18,"Nhap thang tu 1 - 12!",14); textcolor(15);
			fflush(stdin);	gioihan(thang,x+80,y+3,2);
			if(strlen(thang)<1 || nhapso(thang)==0)
			{
				trolaisua(x+80,y+3,thang); goto thang;
			} B[i].thang=atoi(thang);
			vietchuoi(x+82,y+3,"/",15);
			nam:
			vietchuoi(x+65,18,"Nhap thang tu 1 - 12!",0);
			vietchuoi(x+65,18,"Nhap nam gom co 4 chu so!",14); textcolor(15);
			fflush(stdin);	gioihan(nam,x+83,y+3,4);
			if(strlen(nam)<1 || nhapso(nam)==0)
			{
				trolaisua(x+83,y+3,nam); goto nam;
			} B[i].nam=atoi(nam);
		}while(chuantime(B[i].ngay,B[i].thang,B[i].nam)==0);
		buy:
		vietchuoi(x+65,18,"Nhap nam gom co 4 chu so!",0);	vietchuoi(x+60,1,"Mat hang ban vua nhap da het!",0);
		vietchuoi(x+55,18,"Ma mat hang phai trung voi ma san pham!",14); textcolor(15);
		het:
		fflush(stdin);	gioihan(B[i].muahang,x+90,y+3,4);
		o=tksanpham(A,B[i].muahang);
		sl=tkslsp(A,B[i].muahang);	sl=sl+slg;
		if(o==-1 || strlen(B[i].muahang)<1)
		{
			trolaisua(x+90,y+3,B[i].muahang);	goto buy;
		}
		if(sl==0)
		{
			vietchuoi(x+55,18,"Ma mat hang phai trung voi ma san pham!",0);
			vietchuoi(x+60,18,"Mat hang ban vua nhap da het!",14); textcolor(15);
			trolaisua(x+90,y+3,B[i].muahang);	goto het;
		}
		sl:
		vietchuoi(x+55,18,"Ma mat hang phai trung voi ma san pham!",0);
		vietchuoi(x+50,18,"So luong mat hang phai nho hon so luong dang co!",14); textcolor(15);
		fflush(stdin);	gioihan(soluong,x+120,y+3,3);	B[i].soluong=atoi(soluong);
		vt=o;
		if(B[i].soluong<1 || sl<B[i].soluong || nhapso(soluong)==0)
		{
			trolaisua(x+120,y+3,soluong);	goto sl;
		}
		sl=sl-B[i].soluong;		A[o].soluong=sl;
		gia:
		vietchuoi(x+50,18,"So luong mat hang phai nho hon so luong dang co!",0);	
		vietchuoi(x+55,18,"Gia ban phai lon hon hoac bang gia nhap!",14); textcolor(15);
		fflush(stdin);	gioihan(giaban,x+133,y+3,9);	B[i].giaban=atoi(giaban);
		gia=tkgiasp(A,B[i].muahang);
		if(strlen(giaban)<1 || gia>B[i].giaban || nhapso(giaban)==0)
		{
			trolaisua(x+133,y+3,giaban);	goto gia;
		}
		vietchuoi(x+55,18,"Gia ban phai lon hon hoac bang gia nhap!",0);
		vietchuoi(x+60,18,"Nhan nut [Tab] de ket thuc nhap!",14); textcolor(15);
		gotoxy(x+146,y+3);	
		printf("%d",B[i].thanhtien=B[i].soluong*B[i].giaban);
		y=y+2;
	}
	int mn=menu5(10,23);
	if(mn==1)
	{
		ghikhachhang(B); ghisanpham(A);	gotoxy(5,25);	MessageBox(0, "Ghi File thanh cong!", "THONG BAO", MB_OK);
		xoamanhinh();	dockhachhang(B); sapxepkhachhang(B);	inkhachhang(B);
	}
	else if(mn==2)
	{
		xoamanhinh();	dockhachhang(B); sapxepkhachhang(B);	inkhachhang(B);
	}
	else if(mn==3)
	{
		gotoxy(5,25);	MessageBox(0, "Dang thoat chuong trinh!", "THONG BAO", MB_OK);
		gotoxy(x+4,y+9);	exit(0);
	}
}
int xoakhachhang(KHACHHANG B[])
{
	int i, x, y, z;	char xoa[35];
	nhap:
	bangmenu(5,3,35,2,3);	vietchuoi(6,4,"Nhap ma khach hang:  ",11);
	bangmenu(80,1,33,2,2);	vietchuoi(90,2,"XOA KHACH HANG",14);
	fflush(stdin);	gioihan(xoa,27,4,4);	dockhachhang(B);	z=tkkhachhang(B,xoa);
	if(z==-1)
	{
		gotoxy(5,25);	MessageBox(0, "Khach hang ban vua nhap khong ton tai!", "THONG BAO", MB_OK);
		trolaisua(27,4,xoa);	goto nhap;
	}
	else
	{
		textcolor(3);	bangkhachhang(x=3,y=10,6);
		textcolor(12);	vietchuoi(x+3,y-1,"[ THONG TIN KHACH HANG ]",14);
		for(i=z;i<b;i++)
		{
			textcolor(15);	gotoxy(x+1,y+3);	printf("%d",i+1);
			gotoxy(x+5,y+3);	printf("%s",B[i].makh);
			gotoxy(x+15,y+3);	printf("%s",B[i].tenkh);
			gotoxy(x+43,y+3);	printf("%s",B[i].diachi);
			gotoxy(x+61,y+3);	printf("%s",B[i].sdt);
			gotoxy(x+77,y+3);	printf("%d/%d/%d",B[i].ngay,B[i].thang,B[i].nam);
			gotoxy(x+90,y+3);	printf("%s",B[i].muahang);
			gotoxy(x+120,y+3);	printf("%d",B[i].soluong);
			gotoxy(x+133,y+3);	printf("%d",B[i].giaban);
			gotoxy(x+146,y+3);	printf("%d",B[i].thanhtien);
			y=y+2;	break;
		}
		int mn1=menu4(3,10);
		if(mn1==1)
		{
			for(i=z;i<b;i++)
			{
				B[i]=B[i+1];
				z--;
			}
			b--;
			ghikhachhang(B);	gotoxy(5,25);	MessageBox(0, "Xoa khach hang thanh cong!", "THONG BAO", MB_OK);
			int mn2=menu3(3,11);
			if(mn2==1)
			{
				xoamanhinh();	goto nhap;
			}
			else if(mn2==2)
			{
				xoamanhinh();	dockhachhang(B); sapxepkhachhang(B);	inkhachhang(B);
			}
			else if(mn2==3)
			{
				gotoxy(5,25);	MessageBox(0, "Dang thoat chuong trinh!", "THONG BAO", MB_OK);
				gotoxy(x+3,y+15);	exit(0);
			}
		}
		else if(mn1==2)
		{
			xoamanhinh();	dockhachhang(B); sapxepkhachhang(B);	inkhachhang(B);
		}
	}
}
void tbthongke(int x, int y)
{
	int i, j;
	textcolor(2);
	for(i=x;i<=x+100;i++)
		for(j=y;j<=y+33;j++)
		{
			if(i==x || i==x+33 || i==x+100)
			{
				if(j==y && i!=x && i!=x+100)
					viet(i,j,203);
				else if(j==y && i!=x+100)
					viet(i,j,201);
				else if(j==y && i!=x)
					viet(i,j,187);
				else if(j==y+33 && i!=x && i!=x+100)
					viet(i,j,202);
				else if(j==y+33 && i!=x+100)
					viet(i,j,200);
				else if(j==y+33 && i!=x)
					viet(i,j,188);
				else viet(i,j,186);
			}
			else if(j==y || j==y+33)
					viet(i,j,205);
		}	textcolor(15);
}
void thongke(SANPHAM A[], KHACHHANG B[])
{
	int x=30, y=4, i, j, q, p, nam, thang, id, is, dem, dem1, t, t1, khsl, kht, spsl, spt;
	char sp[]="san pham", kh[]="khach hang", muc[35], nm[10], tg[10];
	docsanpham(A);
	dockhachhang(B);
	tbthongke(x,y);
	vietchuoi(63,1,"[ THONG KE THONG TIN CUA HANG ]",14);
	vietchuoi(63,2,"-------------------------------",14);
	for(i=0;i<a;i++)
	{
		vietchuoi(x+2,y+3,"Tong so san pham:",15); gotoxy(x+20,y+3); printf("%d",A[i].soluong+=A[i-1].soluong);
		A[i].thanhtien+=A[i-1].thanhtien;	p=A[i].thanhtien;
		vietchuoi(x+2,y+7,"Von nhap hang:",15); gotoxy(x+17,y+7); printf("%d",p);
	}
	for(j=0;j<b;j++)
	{
		vietchuoi(x+2,y+5,"San pham da ban:",15); gotoxy(x+19,y+5); printf("%d",B[j].soluong+=B[j-1].soluong);
		B[j].thanhtien+=B[j-1].thanhtien; q=B[j].thanhtien;
		vietchuoi(x+2,y+9,"Tien ban duoc:",15); gotoxy(x+17,y+9); printf("%d",q);
		vietchuoi(x+2,y+11,"Tong khach hang:",15); gotoxy(x+19,y+11); printf("%d",j+1);
	}
	int tinh;	tinh=q-p;
	vietchuoi(x+2,y+13,"Thu nhap:",15); gotoxy(x+12,y+13); printf("%d",tinh);
	vietchuoi(x+2,y+15,"tinh trang phat trien:",15);
	gotoxy(x+25,y+15);
	{
		if(tinh<0)
		{
			textcolor(12); printf("THUA LO");
		}
		if(tinh==0)
		{
			textcolor(14); printf("HOA VON");
		}
		if(tinh>0)
		{
			textcolor(10); printf("RAT TOT");
		}
	} textcolor(15); bangmenu(x+3,y+23,11,2,11); vietchuoi(x+5,y+24,"CHI TIET",15);	vietchuoi(x+20,y+24,"TRO VE",6);	int kt=1;
	gotoxy(x+3,y+35);
	{
		for(;;)
		{
			gotoxy(x+3,y+35); int h=batphim();
			if(h==8) // sang phai
			{
				if(kt==1)
				{
					kt=2;
					bangmenu(x+3,y+23,11,2,0); vietchuoi(x+5,y+24,"CHI TIET",6);
					bangmenu(x+18,y+23,11,2,11);	vietchuoi(x+20,y+24,"TRO VE",15);
				}
				else if(kt==2)
				{
					kt=1;
					bangmenu(x+3,y+23,11,2,11); vietchuoi(x+5,y+24,"CHI TIET",15);
					bangmenu(x+18,y+23,11,2,0);	vietchuoi(x+20,y+24,"TRO VE",6);
				}
			}
			else if(h==7) // sang trai
			{
				if(kt==1)
				{
					kt=2;
					bangmenu(x+3,y+23,11,2,0); vietchuoi(x+5,y+24,"CHI TIET",6);
					bangmenu(x+18,y+23,11,2,11);	vietchuoi(x+20,y+24,"TRO VE",15);
				}
				else if(kt==2)
				{
					kt=1;
					bangmenu(x+3,y+23,11,2,11); vietchuoi(x+5,y+24,"CHI TIET",15);
					bangmenu(x+18,y+23,11,2,0);	vietchuoi(x+20,y+24,"TRO VE",6);
				}
			}
			else if(h==3)
			{
				if(kt==1)
				{
					bg:
					bangmenu(x+35,y+1,63,2,13); vietchuoi(x+50,y+2,"Nhap muc 'san pham' hoac 'khach hang'",14);
					bangmenu(x+35,y+4,23,2,10);	vietchuoi(x+36,y+5,"Chon muc: ",14);	gioihan(muc,x+46,y+5,10);
					if(stricmp(muc,sp)!=0 && stricmp(muc,kh)!=0)
					{
						trolaisua(x+46,y+5,muc); goto bg;
					}
					else if(stricmp(muc,sp)==0)
					{
						A:
						docsanpham(A);
						vietchuoi(x+50,y+2,"Nhap muc 'san pham' hoac 'khach hang'",0);
						vietchuoi(x+40,y+2,"Nhap nam gom co 4 chu so va trung voi nam nhap san pham",14);
						bangmenu(x+35,y+7,20,2,10); vietchuoi(x+36,y+8,"Nhap nam: ",14);	fflush(stdin);	gioihan(nm,x+46,y+8,4);
						nam=atoi(nm);	id=tkspnam(A,nam);
						if(nhapso(nm)==0 || id==0)
						{
							trolaisua(x+46,y+8,nm);	goto A;
						}
						A1:
						vietchuoi(x+40,y+2,"Nhap nam gom co 4 chu so va trung voi nam nhap san pham",0);
						vietchuoi(x+38,y+2,"Nhap thang gom co 2 chu so va trung voi thang nhap san pham",14);
						bangmenu(x+35,y+10,20,2,10);	vietchuoi(x+36,y+11,"Nhap thang: ",14);	fflush(stdin);	gioihan(tg,x+48,y+11,2);
						thang=atoi(tg);
						if(nhapso(tg)==0 || thang<1 || thang>12)
						{
							trolaisua(x+48,y+11,tg);	goto A1;
						}
						dem=0; spsl=0; spt=0; bangmenu(x+35,y+13,63,12,14);
						for(i=0;i<a;i++)
						{
							if(nam==A[i].nam && thang==A[i].thang)
							{
								dem++;
								spsl=spsl+A[i].soluong;
								spt=spt+A[i].thanhtien;
							}
						}
						textcolor(15);
						gotoxy(x+40,y+15); printf("Trong thang %d nam %d :",thang,nam);
						gotoxy(x+40,y+17); printf("Da nhap %d mat hang",dem);
						gotoxy(x+40,y+19); printf("So luong: %d",spsl);
						gotoxy(x+40,y+21); printf("Tong von: %d",spt);
						textcolor(15); bangmenu(x+60,y+27,9,2,11); vietchuoi(x+62,y+28,"Tro ve",15);
						gotoxy(x+3,y+30);
						{
							for(;;)
							{
								gotoxy(x+3,y+30); int h=batphim();
								if(h==3)
								{
									xoamanhinh(); thongke(A,B);
								}
							}
						}
					}
					else if(stricmp(muc,kh)==0)
					{
						B:
						dockhachhang(B);
						vietchuoi(x+50,y+2,"Nhap muc 'san pham' hoac 'khach hang'",0);
						vietchuoi(x+36,y+2,"Nhap nam gom co 4 chu so, trung voi nam khach hang da mua",14);
						bangmenu(x+35,y+7,20,2,10); vietchuoi(x+36,y+8,"Nhap nam: ",14);	fflush(stdin);	gioihan(nm,x+46,y+8,4);
						nam=atoi(nm);	id=tkkhnam(B,nam);
						if(nhapso(nm)==0 || id==0)
						{
							trolaisua(x+46,y+8,nm);	goto B;
						}
						B1:
						vietchuoi(x+36,y+2,"Nhap nam gom co 4 chu so, trung voi nam khach hang da mua",0);
						vietchuoi(x+36,y+2,"Nhap thang gom co 2 chu so, trung voi thang khach hang da mua",14);
						bangmenu(x+35,y+10,20,2,10);	vietchuoi(x+36,y+11,"Nhap thang: ",14);	fflush(stdin);	gioihan(tg,x+48,y+11,2);
						thang=atoi(tg);
						if(nhapso(tg)==0 || thang<1 || thang>12)
						{
							trolaisua(x+48,y+11,tg); goto B1;
						}
						dem1=0; khsl=0; kht=0; bangmenu(x+35,y+13,63,12,14);
						for(j=0;j<b;j++)
						{
							if(nam==B[j].nam && thang==B[j].thang)
							{
								dem1++;
								khsl=khsl+B[j].soluong;
								kht=kht+B[j].thanhtien;
							}
						}
						textcolor(15);
						gotoxy(x+40,y+15); printf("Trong thang %d nam %d :",thang,nam);
						gotoxy(x+40,y+17); printf("Da co %d khach hang mua hang",dem1);
						gotoxy(x+40,y+19); printf("Da ban %d san pham",khsl);
						gotoxy(x+40,y+21); printf("Tong so tien thu duoc: %d",kht);
						textcolor(15); bangmenu(x+60,y+27,9,2,11); vietchuoi(x+62,y+28,"Tro ve",15);
						gotoxy(x+3,y+30);
						{
							for(;;)
							{
								gotoxy(x+3,y+30); int h=batphim();
								if(h==3)
								{
									xoamanhinh(); thongke(A,B);
								}
							}
						}
					}
				}
				else if(kt==2)
				{
					xoamanhinh(); menu();
				}
			}
		}
	}
}
void tbmenu(int x, int y)
{
	int i, j;
	for(i=x;i<=x+90;i++)
		for(j=y;j<=y+25;j++)
		{
			if(i==x || i==x+30 || i==x+90)
			{
				if(j==y && i!=x && i!=x+90)
					viet(i,j,203);
				else if(j==y && i!=x+90)
					viet(i,j,201);
				else if(j==y && i!=x)
					viet(i,j,187);
				else if(j==y+25 && i!=x && i!=x+90)
					viet(i,j,202);
				else if(j==y+25 && i!=x+90)
					viet(i,j,200);
				else if(j==y+25 && i!=x)
					viet(i,j,188);
				else viet(i,j,186);
			}
			else if(j==y || j==y+25)
					viet(i,j,205);
		}
}
void menusanpham()
{
	int x, y;
	bangmenu(48,1,67,2,11);	vietchuoi(53,2,"CHUONG TRINH QUAN LY CUA HANG DIEN TU DIEN LANH KHANH TOAN",14);
	textcolor(2);	tbmenu(x=36,y=6);	textcolor(3);
	bangmenu(x+42,y+2,40,2,14);	vietchuoi(x+45,y+3,"1>  Nhap san pham",15);
	vietchuoi(x+45,y+6,"2>  Quan ly san pham",6);
	vietchuoi(x+45,y+9,"3>  Tro ve",6);
	int kt=1;
	gotoxy(x+5,y+26);
	for(;;)
	{
		gotoxy(x+5,y+26);
		int h=batphim();
		if(h==6) // phim xuong
		{
			if(kt==1)
			{
				kt=2;
				bangmenu(x+42,y+2,40,2,0);	vietchuoi(x+45,y+3,"1>  Nhap san pham",6);
				bangmenu(x+42,y+5,40,2,14);	vietchuoi(x+45,y+6,"2>  Quan ly san pham",15);
				bangmenu(x+42,y+8,40,2,0);	vietchuoi(x+45,y+9,"3>  Tro ve",6);
			}
			else if(kt==2)
			{
				kt=3;
				bangmenu(x+42,y+2,40,2,0);	vietchuoi(x+45,y+3,"1>  Nhap san pham",6);
				bangmenu(x+42,y+5,40,2,0);	vietchuoi(x+45,y+6,"2>  Quan ly san pham",6);
				bangmenu(x+42,y+8,40,2,14);	vietchuoi(x+45,y+9,"3>  Tro ve",15);
			}
			else if(kt==3)
			{
				kt=1;
				bangmenu(x+42,y+2,40,2,14);	vietchuoi(x+45,y+3,"1>  Nhap san pham",15);
				bangmenu(x+42,y+5,40,2,0);	vietchuoi(x+45,y+6,"2>  Quan ly san pham",6);
				bangmenu(x+42,y+8,40,2,0);	vietchuoi(x+45,y+9,"3>  Tro ve",6);
			}
		}
		else if(h==5) // phim len
		{
			if(kt==1)
			{
				kt=3;
				bangmenu(x+42,y+2,40,2,0);	vietchuoi(x+45,y+3,"1>  Nhap san pham",6);
				bangmenu(x+42,y+5,40,2,0);	vietchuoi(x+45,y+6,"2>  Quan ly san pham",6);
				bangmenu(x+42,y+8,40,2,14);	vietchuoi(x+45,y+9,"3>  Tro ve",15);
			}
			else if(kt==3)
			{
				kt=2;
				bangmenu(x+42,y+2,40,2,0);	vietchuoi(x+45,y+3,"1>  Nhap san pham",6);
				bangmenu(x+42,y+5,40,2,14);	vietchuoi(x+45,y+6,"2>  Quan ly san pham",15);
				bangmenu(x+42,y+8,40,2,0);	vietchuoi(x+45,y+9,"3>  Tro ve",6);
			}
			else if(kt==2)
			{
				kt=1;
				bangmenu(x+42,y+2,40,2,14);	vietchuoi(x+45,y+3,"1>  Nhap san pham",15);
				bangmenu(x+42,y+5,40,2,0);	vietchuoi(x+45,y+6,"2>  Quan ly san pham",6);
				bangmenu(x+42,y+8,40,2,0);	vietchuoi(x+45,y+9,"3>  Tro ve",6);
			}
		}
		else if(h==3) //phim enter
		{
			if(kt==1)
			{
				vietchuoi(x+40,y+13,"Ban co muon xoa toan bo du lieu dang luu?",12);
				bangmenu(x+46,y+15,10,2,10);	vietchuoi(x+50,y+16,"CO",15);
				vietchuoi(x+65,y+16,"KHONG",6);
				int t=1; gotoxy(x+82,y+13);
				for(;;)
				{
					int h=batphim(); gotoxy(x+82,y+13);
					if(h==8)
					{
						if(t==1)
						{
							t=0;
							bangmenu(x+46,y+15,10,2,0);	vietchuoi(x+50,y+16,"CO",6);
							bangmenu(x+63,y+15,10,2,10);	vietchuoi(x+65,y+16,"KHONG",15);
						}
						else if(t==0)
						{
							t=1;
							bangmenu(x+46,y+15,10,2,10);	vietchuoi(x+50,y+16,"CO",15);
							bangmenu(x+63,y+15,10,2,0);	vietchuoi(x+65,y+16,"KHONG",6);
						}
					}
					else if(h==7)
					{
						if(t==1)
						{
							t=0;
							bangmenu(x+46,y+15,10,2,0);	vietchuoi(x+50,y+16,"CO",6);
							bangmenu(x+63,y+15,10,2,10);	vietchuoi(x+65,y+16,"KHONG",15);
						}
						else if(t==0)
						{
							t=1;
							bangmenu(x+46,y+15,10,2,10);	vietchuoi(x+50,y+16,"CO",15);
							bangmenu(x+63,y+15,10,2,0);	vietchuoi(x+65,y+16,"KHONG",6);
						}
					}
					else if(h==3)
					{
						if(t==1)
						{
							xoamanhinh();	nhapsanpham(A);
						}
						else if(t==0)
						{
							xoamanhinh();	docsanpham(A);	nhapsanpham(A);
						}
					}
				}
			}
			else if(kt==2)
			{
				xoamanhinh();	docsanpham(A);	sapxepsanpham(A);	insanpham(A);
			}
			else if(kt==3)
			{
				xoamanhinh();	menu();
			}
		}
	}
}
void menukhachhang()
{
	int x, y;
	bangmenu(48,1,67,2,11);	vietchuoi(53,2,"CHUONG TRINH QUAN LY CUA HANG DIEN TU DIEN LANH KHANH TOAN",14);
	textcolor(2);	tbmenu(x=36,y=6);	textcolor(3);
	bangmenu(x+42,y+2,40,2,14);	vietchuoi(x+45,y+3,"1>  Nhap khach hang",15);
	vietchuoi(x+45,y+6,"2>  Quan ly khach hang",6);
	vietchuoi(x+45,y+9,"3>  Tro ve",6);
	int kt=1;
	gotoxy(x+5,y+26);
	for(;;)
	{
		gotoxy(x+5,y+26);
		int h=batphim();
		if(h==6) // phim xuong
		{
			if(kt==1)
			{
				kt=2;
				bangmenu(x+42,y+2,40,2,0);	vietchuoi(x+45,y+3,"1>  Nhap khach hang",6);
				bangmenu(x+42,y+5,40,2,14);	vietchuoi(x+45,y+6,"2>  Quan ly khach hang",15);
				bangmenu(x+42,y+8,40,2,0);	vietchuoi(x+45,y+9,"3>  Tro ve",6);
			}
			else if(kt==2)
			{
				kt=3;
				bangmenu(x+42,y+2,40,2,0);	vietchuoi(x+45,y+3,"1>  Nhap khach hang",6);
				bangmenu(x+42,y+5,40,2,0);	vietchuoi(x+45,y+6,"2>  Quan ly khach hang",6);
				bangmenu(x+42,y+8,40,2,14);	vietchuoi(x+45,y+9,"3>  Tro ve",15);
			}
			else if(kt==3)
			{
				kt=1;
				bangmenu(x+42,y+2,40,2,14);	vietchuoi(x+45,y+3,"1>  Nhap khach hang",15);
				bangmenu(x+42,y+5,40,2,0);	vietchuoi(x+45,y+6,"2>  Quan ly khach hang",6);
				bangmenu(x+42,y+8,40,2,0);	vietchuoi(x+45,y+9,"3>  Tro ve",6);
			}
		}
		else if(h==5) // phim len
		{
			if(kt==1)
			{
				kt=3;
				bangmenu(x+42,y+2,40,2,0);	vietchuoi(x+45,y+3,"1>  Nhap khach hang",6);
				bangmenu(x+42,y+5,40,2,0);	vietchuoi(x+45,y+6,"2>  Quan ly khach hang",6);
				bangmenu(x+42,y+8,40,2,14);	vietchuoi(x+45,y+9,"3>  Tro ve",15);
			}
			else if(kt==3)
			{
				kt=2;
				bangmenu(x+42,y+2,40,2,0);	vietchuoi(x+45,y+3,"1>  Nhap khach hang",6);
				bangmenu(x+42,y+5,40,2,14);	vietchuoi(x+45,y+6,"2>  Quan ly khach hang",15);
				bangmenu(x+42,y+8,40,2,0);	vietchuoi(x+45,y+9,"3>  Tro ve",6);
			}
			else if(kt==2)
			{
				kt=1;
				bangmenu(x+42,y+2,40,2,14);	vietchuoi(x+45,y+3,"1>  Nhap khach hang",15);
				bangmenu(x+42,y+5,40,2,0);	vietchuoi(x+45,y+6,"2>  Quan ly khach hang",6);
				bangmenu(x+42,y+8,40,2,0);	vietchuoi(x+45,y+9,"3>  Tro ve",6);
			}
		}
		else if(h==3) //phim enter
		{
			if(kt==1)
			{
				vietchuoi(x+40,y+13,"Ban co muon xoa toan bo du lieu dang luu?",12);
				bangmenu(x+46,y+15,10,2,10);	vietchuoi(x+50,y+16,"CO",15);
				vietchuoi(x+65,y+16,"KHONG",6);
				int t=1; gotoxy(x+82,y+13);
				for(;;)
				{
					int h=batphim(); gotoxy(x+82,y+13);
					if(h==8)
					{
						if(t==1)
						{
							t=0;
							bangmenu(x+46,y+15,10,2,0);	vietchuoi(x+50,y+16,"CO",6);
							bangmenu(x+63,y+15,10,2,10);	vietchuoi(x+65,y+16,"KHONG",15);
						}
						else if(t==0)
						{
							t=1;
							bangmenu(x+46,y+15,10,2,10);	vietchuoi(x+50,y+16,"CO",15);
							bangmenu(x+63,y+15,10,2,0);	vietchuoi(x+65,y+16,"KHONG",6);
						}
					}
					else if(h==7)
					{
						if(t==1)
						{
							t=0;
							bangmenu(x+46,y+15,10,2,0);	vietchuoi(x+50,y+16,"CO",6);
							bangmenu(x+63,y+15,10,2,10);	vietchuoi(x+65,y+16,"KHONG",15);
						}
						else if(t==0)
						{
							t=1;
							bangmenu(x+46,y+15,10,2,10);	vietchuoi(x+50,y+16,"CO",15);
							bangmenu(x+63,y+15,10,2,0);	vietchuoi(x+65,y+16,"KHONG",6);
						}
					}
					else if(h==3)
					{
						if(t==1)
						{
							xoamanhinh();	nhapkhachhang(B,A);
						}
						else if(t==0)
						{
							xoamanhinh();	dockhachhang(B); docsanpham(A);	nhapkhachhang(B,A);
						}
					}
				}
			}
			else if(kt==2)
			{
				xoamanhinh();	dockhachhang(B); sapxepkhachhang(B);	inkhachhang(B);
			}
			else if(kt==3)
			{
				xoamanhinh();	menu();
			}
		}
	}
}
int menu()
{
	int x, y;
	bangmenu(48,1,67,2,11);	vietchuoi(53,2,"CHUONG TRINH QUAN LY CUA HANG DIEN TU DIEN LANH KHANH TOAN",14);
	textcolor(2);	tbmenu(x=36,y=6);	textcolor(3);
	bangmenu(x+2,y+2,26,2,11);	vietchuoi(x+5,y+3,"1>  San pham",15);
	vietchuoi(x+5,y+6,"2>  Khach hang",6);
	vietchuoi(x+5,y+9,"3>  Thong tin",6);
	vietchuoi(x+5,y+12,"4>  Thong ke",6);
	vietchuoi(x+5,y+15,"5>  Thoat",6);
	int kt=1;
	gotoxy(x+5,y+26);
	for(;;)
	{
		gotoxy(x+5,y+26);
		int h=batphim();
		if(h==6) // phim xuong
		{
			if(kt==1)
			{
				kt=2;
				bangmenu(x+2,y+2,26,2,0);	vietchuoi(x+5,y+3,"1>  San pham",6);
				bangmenu(x+2,y+5,26,2,11);	vietchuoi(x+5,y+6,"2>  Khach hang",15);
				bangmenu(x+2,y+8,26,2,0);	vietchuoi(x+5,y+9,"3>  Thong tin",6);
				bangmenu(x+2,y+11,26,2,0);	vietchuoi(x+5,y+12,"4>  Thong ke",6);
				bangmenu(x+2,y+14,26,2,0);	vietchuoi(x+5,y+15,"5>  Thoat",6);
			}
			else if(kt==2)
			{
				kt=3;
				bangmenu(x+2,y+2,26,2,0);	vietchuoi(x+5,y+3,"1>  San pham",6);
				bangmenu(x+2,y+5,26,2,0);	vietchuoi(x+5,y+6,"2>  Khach hang",6);
				bangmenu(x+2,y+8,26,2,11);	vietchuoi(x+5,y+9,"3>  Thong tin",15);
				bangmenu(x+2,y+11,26,2,0);	vietchuoi(x+5,y+12,"4>  Thong ke",6);
				bangmenu(x+2,y+14,26,2,0);	vietchuoi(x+5,y+15,"5>  Thoat",6);
			}
			else if(kt==3)
			{
				kt=4;
				bangmenu(x+2,y+2,26,2,0);	vietchuoi(x+5,y+3,"1>  San pham",6);
				bangmenu(x+2,y+5,26,2,0);	vietchuoi(x+5,y+6,"2>  Khach hang",6);
				bangmenu(x+2,y+8,26,2,0);	vietchuoi(x+5,y+9,"3>  Thong tin",6);
				bangmenu(x+2,y+11,26,2,11);	vietchuoi(x+5,y+12,"4>  Thong ke",15);
				bangmenu(x+2,y+14,26,2,0);	vietchuoi(x+5,y+15,"5>  Thoat",6);
			}
			else if(kt==4)
			{
				kt=5;
				bangmenu(x+2,y+2,26,2,0);	vietchuoi(x+5,y+3,"1>  San pham",6);
				bangmenu(x+2,y+5,26,2,0);	vietchuoi(x+5,y+6,"2>  Khach hang",6);
				bangmenu(x+2,y+8,26,2,0);	vietchuoi(x+5,y+9,"3>  Thong tin",6);
				bangmenu(x+2,y+11,26,2,0);	vietchuoi(x+5,y+12,"4>  Thong ke",6);
				bangmenu(x+2,y+14,26,2,11);	vietchuoi(x+5,y+15,"5>  Thoat",15);
			}
			else if(kt==5)
			{
				kt=1;
				bangmenu(x+2,y+2,26,2,11);	vietchuoi(x+5,y+3,"1>  San pham",15);
				bangmenu(x+2,y+5,26,2,0);	vietchuoi(x+5,y+6,"2>  Khach hang",6);
				bangmenu(x+2,y+8,26,2,0);	vietchuoi(x+5,y+9,"3>  Thong tin",6);
				bangmenu(x+2,y+11,26,2,0);	vietchuoi(x+5,y+12,"4>  Thong ke",6);
				bangmenu(x+2,y+14,26,2,0);	vietchuoi(x+5,y+15,"5>  Thoat",6);
			}
		}
		else if(h==5) // phim len
		{
			if(kt==1)
			{
				kt=5;
				bangmenu(x+2,y+2,26,2,0);	vietchuoi(x+5,y+3,"1>  San pham",6);
				bangmenu(x+2,y+5,26,2,0);	vietchuoi(x+5,y+6,"2>  Khach hang",6);
				bangmenu(x+2,y+8,26,2,0);	vietchuoi(x+5,y+9,"3>  Thong tin",6);
				bangmenu(x+2,y+11,26,2,0);	vietchuoi(x+5,y+12,"4>  Thong ke",6);
				bangmenu(x+2,y+14,26,2,11);	vietchuoi(x+5,y+15,"5>  Thoat",15);
			}
			else if(kt==5)
			{
				kt=4;
				bangmenu(x+2,y+2,26,2,0);	vietchuoi(x+5,y+3,"1>  San pham",6);
				bangmenu(x+2,y+5,26,2,0);	vietchuoi(x+5,y+6,"2>  Khach hang",6);
				bangmenu(x+2,y+8,26,2,0);	vietchuoi(x+5,y+9,"3>  Thong tin",6);
				bangmenu(x+2,y+11,26,2,11);	vietchuoi(x+5,y+12,"4>  Thong ke",15);
				bangmenu(x+2,y+14,26,2,0);	vietchuoi(x+5,y+15,"5>  Thoat",6);
			}
			else if(kt==4)
			{
				kt=3;
				bangmenu(x+2,y+2,26,2,0);	vietchuoi(x+5,y+3,"1>  San pham",6);
				bangmenu(x+2,y+5,26,2,0);	vietchuoi(x+5,y+6,"2>  Khach hang",6);
				bangmenu(x+2,y+8,26,2,11);	vietchuoi(x+5,y+9,"3>  Thong tin",15);
				bangmenu(x+2,y+11,26,2,0);	vietchuoi(x+5,y+12,"4>  Thong ke",6);
				bangmenu(x+2,y+14,26,2,0);	vietchuoi(x+5,y+15,"5>  Thoat",6);
			}
			else if(kt==3)
			{
				kt=2;
				bangmenu(x+2,y+2,26,2,0);	vietchuoi(x+5,y+3,"1>  San pham",6);
				bangmenu(x+2,y+5,26,2,11);	vietchuoi(x+5,y+6,"2>  Khach hang",15);
				bangmenu(x+2,y+8,26,2,0);	vietchuoi(x+5,y+9,"3>  Thong tin",6);
				bangmenu(x+2,y+11,26,2,0);	vietchuoi(x+5,y+12,"4>  Thong ke",6);
				bangmenu(x+2,y+14,26,2,0);	vietchuoi(x+5,y+15,"5>  Thoat",6);
			}
			else if(kt==2)
			{
				kt=1;
				bangmenu(x+2,y+2,26,2,11);	vietchuoi(x+5,y+3,"1>  San pham",15);
				bangmenu(x+2,y+5,26,2,0);	vietchuoi(x+5,y+6,"2>  Khach hang",6);
				bangmenu(x+2,y+8,26,2,0);	vietchuoi(x+5,y+9,"3>  Thong tin",6);
				bangmenu(x+2,y+11,26,2,0);	vietchuoi(x+5,y+12,"4>  Thong ke",6);
				bangmenu(x+2,y+14,26,2,0);	vietchuoi(x+5,y+15,"5>  Thoat",6);
			}
		}
		else if(h==3)
		{
			if(kt==1)
			{
				menusanpham();
			}
			else if(kt==2)
			{
				menukhachhang();
			}
			else if(kt==3)
			{
				vietchuoi(x+57,y+3,"DO AN 1",12);
				vietchuoi(x+32,y+5,"Chuong trinh quan ly cua hang dien tu dien lanh Khanh Toan",13);
				vietchuoi(x+33,y+9,"Nguoi thuc hien: Le Thanh Tung",10);
				vietchuoi(x+33,y+11,"Nguoi huong dan: Thay Chu Ba Thanh",10);
				vietchuoi(x+33,y+13,"Cam on: Cac thay, co giao trong bo mon da giup do",14);
				vietchuoi(x+33,y+15,"va ho tro tai lieu giup em hoan thanh chuong trinh nay!!",14);
				bangmenu(x+55,y+18,10,2,9); vietchuoi(x+57,y+19,"Tro ve",15);
				gotoxy(x+5,y+26);
				for(;;)
				{
					gotoxy(x+5,y+26); int h=batphim();
					if(h==3)
					{
						xoamanhinh(); menu();
					}
				}
			}
			else if(kt==4)
			{
				xoamanhinh(); thongke(A,B);
			}
			else if(kt==5)
			{
				gotoxy(8,22);	MessageBox(0, "Dang thoat chuong trinh!", "THONG BAO", MB_OK);
				gotoxy(x+5,y+26);	exit(0);
			}
		}
	}
}
int main()
{
	menu();
	return 0;
}
