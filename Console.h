#ifndef CSL_H_INCLUDED
#define CSL_H_INCLUDED
#include <iostream>
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <ctype.h>
#define _WIN32_WINNT 0x0500
#include <windows.h>
using namespace std;
inline void settitle(char *title);//dat tieu de chon console
inline void clrscr(void);//xoa mang hinh(fill space character full screen)
void gotoxy(int x, int y);//move cursor to x,y
char getcharxy(int x, int y);//lay ky tu tai vi tri chuot
int wherex();//lay vi tri toa do hien tai x cua con tro
int wherey();//lay vi tri toa do hien tai y cua con tro
void setcolor(WORD color);//dat mau cho chu tren console
void settextbgcolor(WORD color);//dat mau nen cua chu tren console
void Nocursortype();//xóa con trỏ chuột trên màn hình console
void ShowCur(bool CursorVisibility);//xóa con trỏ chuột trên màn hình console
inline void setbgcolor(int color);//dat mau nen console
inline void resizecsl(int width, int height);//thay doi kich thuoc console window
inline void sprint(int x, int y, string st);//in xau st, tai toa do x,y
inline void cprint(int x, int y, char c);//in char c, tai toa do x,y
inline void clprint(int x, int y, char c, WORD color);//in c tai toa do xy voi mau color
inline void scprint(int x, int y, char *st, WORD tcolor, WORD bcolor);//in xau st vow mau chu tcolor va mau bgtext bcolor, tai toa do x,y
inline void iprint(int x, int y, int i);//in int i, tai toa do x,y
inline void fprint(int x, int y, float f);//in float f, tai toa do x,y
inline void clstext(int x, int y, char *s);//xoa doan text 's' da show tren console
inline void cloneprint(char x, char y, char num, char c, WORD color);//in xau toan ky tu 'c' voi so luong 'num' tai to do x,y va mau 'color'
inline string strclone(string st, int n);//nhan ban ky tu them nhieu lan
void fillscr(char c);//dien ky tu c vao nen screen(fill c charater full screen)
HWND WINAPI GetConsoleWindow(void);
inline void clrscr(void)
{
	fillscr(' ');
}
inline void gotoxy(int x, int y)
{
	HANDLE hConsoleOutput;
	COORD Cursor_an_Pos = { x, y };
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsoleOutput, Cursor_an_Pos);
}
inline int wherex()
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if (!GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi)) return -1;
	else return csbi.dwCursorPosition.X;
}
inline int wherey()
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if (!GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi)) return -1;
	else return csbi.dwCursorPosition.Y;
}
inline void setcolor(WORD color)
{
	HANDLE hConsoleOutput;
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_SCREEN_BUFFER_INFO screen_buffer_info;
	GetConsoleScreenBufferInfo(hConsoleOutput, &screen_buffer_info);

	WORD wAttributes = screen_buffer_info.wAttributes;
	color &= 0x000f;
	wAttributes &= 0xfff0;
	wAttributes |= color;

	SetConsoleTextAttribute(hConsoleOutput, wAttributes);
}
inline void settextbgcolor(WORD color)
{
	HANDLE hConsoleOutput;
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO screen_buffer_info;
	GetConsoleScreenBufferInfo(hConsoleOutput, &screen_buffer_info);
	WORD wAttributes = screen_buffer_info.wAttributes;
	color &= 0x000f;
	color <<= 4;
	wAttributes &= 0xff0f;
	wAttributes |= color;
	SetConsoleTextAttribute(hConsoleOutput, wAttributes);
}
inline void setbgcolor(int color)
{
	settextbgcolor(color);
	clrscr();
}
inline void resizecsl(int width, int height)
{
	HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r);
	MoveWindow(console, r.left, r.top, width * 15, height * 15, TRUE);
}
inline void sprint(int x, int y, string st)
{
	gotoxy(x, y);
	cout << st;
}
inline void cprint(int x, int y, char c)
{
	gotoxy(x, y);
	printf("%c", c);
}
inline void clprint(int x, int y, char c, WORD color)
{
	gotoxy(x, y);
	setcolor(color);
	printf("%c", c);
}
inline void scprint(int x, int y, char *st, WORD tcolor, WORD bcolor)
{
	gotoxy(x, y);
	setcolor(tcolor);
	settextbgcolor(bcolor);
	printf("%s", st);
}
inline void iprint(int x, int y, int i)
{
	gotoxy(x, y);
	printf("%d", i);
}
inline void fprint(int x, int y, float f)
{
	gotoxy(x, y);
	printf("%f", f);
}
inline void clstext(int x, int y, char *s)
{
	for (int i = strlen(s); i >= 0; i--)//xoa cau tho cu in cau tho moi
	{
		cprint(x + i, y, 32);
	}
}
inline void cloneprint(char x, char y, char num, char c, WORD color)
{
	for (char i = 0; i<num; i++)
	{
		setcolor(color);
		cprint(x + i, y, c);
	}
}
inline void fillscr(char c)
{
	CONSOLE_SCREEN_BUFFER_INFO  csbiInfo;
	HANDLE  hConsoleOut;
	COORD   Home = { 0, 0 };
	DWORD   dummy;
	hConsoleOut = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(hConsoleOut, &csbiInfo);
	FillConsoleOutputCharacter(hConsoleOut, c, csbiInfo.dwSize.X * csbiInfo.dwSize.Y, Home, &dummy);
	SetConsoleCursorPosition(hConsoleOut, Home);
}
string strclone(string st, int n)
{
	string t = "";
	for (; n>0; n--)
	{
		t += st;
	}
	return t;
}
void Nocursortype()
{
	CONSOLE_CURSOR_INFO Info;
	Info.bVisible = FALSE;
	Info.dwSize = 20;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &Info);
}
void ShowCur(bool CursorVisibility)
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursor = { 1, CursorVisibility };
	SetConsoleCursorInfo(handle, &cursor);
}
#endif // CSL_H_INCLUDED