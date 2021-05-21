#ifndef VeKhung_H
#define VeKhung_H

#include <iostream>
#include <iomanip>
#include <windows.h>
#include "Menu.h"


using namespace std;

void ShowCur(bool CursorVisibility)
{
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursor = { 1, CursorVisibility };
    SetConsoleCursorInfo(handle, &cursor);
}

void gotoXY(int column, int line)
{
    COORD coord;
    coord.X = column;
    coord.Y = line;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void PutCharXY(int x, int y,const char* KyTu, int color)
{
    gotoXY(x, y);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
    printf(KyTu);
}

void vekhung(int x,int y,int h,int w)
{
    cout.fill(196);
    gotoXY(x,y);
    cout<<char(218)<<setw(w)<<char(196)<<char(191);
    cout.fill(' ');
    for(int i=1; i<=h; ++i)
    {
        gotoXY(x,y+i);
        cout<<char(179)<<setw(w)<<' '<<char(179);
    }
    gotoXY(x,y+h+1);
    cout.fill(196);
    cout<<char(192)<<setw(w)<<char(196)<<char(217);
}
void veCay(int x,int y,int h)
{
    for(int i=1; i<=h; ++i)
    {
        gotoXY(x,y+i);
        cout<<char(179);
    }
}
#endif
