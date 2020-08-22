#ifndef Menu_H
#define Menu_H

#include <iostream>
#include <conio.h>
#include <windows.h>
#include <stdio.h>
#include <dos.h>
#include <string.h>
#include "mylib.h"
#include <sstream>
#include "KHUNG.h"

using namespace std;

#define key_up 1072
#define key_dw 1080
#define key_left 1075
#define key_right 1077
#define key_alt 27
#define key_esc 27
#define key_enter 13
#define key_back 8
#define key_tab 9
#define key_space 32

#define Black			0
#define DarkBlue		1
#define DarkGreen		2
#define DarkCyan		3
#define DarkRed			4
#define DarkPink		5
#define DarkYellow		6
#define DarkWhite		7
#define Grey			8
#define Blue			9
#define Green			10
#define Cyan			11
#define Red				12
#define Pink			13
#define Yellow			14
#define White			15

#define SODONG 18
#define SODONGCHT 3
void TextColor(int color)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

//ham bat mot phim
int getKey()
{
    int key = _getch();
    if(key==224)
        key=_getch()+1000;
    return key;
}

int menu(int x,int y,char a[5][30],int soluongmenu)
{
    ShowCur(false);
    int key = 0; // luu gia tri phim duoc nhan
    int menuduocchon = 0;// luu menu dang duoc chon
    do
    {
        //in ra menu
        TextColor(DarkWhite);
        for	(int i =0; i<soluongmenu; ++i)
        {
            vekhung(x-1,y+3*i-1,1,30);
            gotoXY(x,y+3*i);
            cout<<a[i]<<endl;
        }
        //chon mau va to nen cho menu duoc chon
        TextColor(Blue);
        gotoXY(x,y+3*menuduocchon);
        cout<<a[menuduocchon]; // in lai menu duoc chon

        key = getKey(); // bat phim

        switch(key)
        {
        case key_up:
        {
            if(menuduocchon>0)
                menuduocchon--; // truong hop menu dang tren dau
            break;
        }
        case key_dw:
        {
            if(menuduocchon < soluongmenu-1)
                menuduocchon++;//truong hop menu duoi cuoi dung
            break;
        }
        case key_enter:
        {
            return menuduocchon; // tra ra gia tri menu dang duoc chon
            break;
        }
        }
    }
    while(key!=key_esc);
    return -1;
}

int menu_xoa(int x,int y,char a[4][30],int soluongmenu)
{
    ShowCur(false);
    int key = 0; // luu gia tri phim duoc nhan
    int menuduocchon = 0;// luu menu dang duoc chon
    do
    {
        //in ra menu
        TextColor(White);
        for	(int i =0; i<soluongmenu; ++i)
        {
            gotoXY(x,y+1*i);
            cout<<a[i]<<endl;
        }
        //chon mau va to nen cho menu duoc chon
        TextColor(Red);
        gotoXY(x,y+1*menuduocchon);
        cout<<a[menuduocchon]; // in lai menu duoc chon

        key = getKey(); // bat phim

        switch(key)
        {
        case key_up:
        {
            if(menuduocchon>0)
                menuduocchon--; // truong hop menu dang tren dau
            break;
        }
        case key_dw:
        {
            if(menuduocchon < soluongmenu-1)
                menuduocchon++;//truong hop menu duoi cuoi dung
            break;
        }
        case key_enter:
        {
            return menuduocchon; // tra ra gia tri menu dang duoc chon
            break;
        }
        }
    }
    while(key!=key_esc);
    return -1;
}

void BaoLoi (char *s,int x, int y)
{
    TextColor(Red);
    gotoXY (x,y);
    cout <<s;
    Sleep(2000);
    gotoXY(x,y);
    for(int i =0; i<strlen(s); i++)
        cout<<" ";
    TextColor(White);
}

void ThanhCong (char *s,int x, int y)
{
    TextColor(Green);
    gotoXY (x,y);
    cout <<s;
    Sleep(2000);
    gotoXY(x,y);
    for(int i =0; i<strlen(s); i++)
        cout<<" ";
    TextColor(White);
}


void strdelete(char *s,int vt,int sl)
{
    int n=strlen(s),i;
    for (i=vt; i<=n-sl; ++i)
        s[i]=s[i+sl];
}

char* ChuanHoa(char a[])
{
    int i;
    while(a[strlen(a)-1]==' ')// xoa het cac ki tu trong o cuoi chuoi
        a[strlen(a)-1]=0;
    while(a[0]==' ')          //xoa het cac ki tu trong o dau chuoi
        strdelete(a,0,1);

    i=0;
    while(i<strlen(a))                //xoa hai ki tu trong lien tiep
        if((a[i]==' ')&&(a[i+1]==' '))
            strdelete(a,i,1);
        else ++i;

    return a;
}

char* string_to_charptr(string s)
{
    char cstr[s.size() + 1];

    copy(s.begin(), s.end(), cstr);
    cstr[s.size()] = '\0';
    char* str =ChuanHoa(cstr);

    return str;
}

string ChuanHoaString(string s)
{
    char cstr[s.size() + 1];

    copy(s.begin(), s.end(), cstr);
    cstr[s.size()] = '\0';
    //s.c_str();
    char* str =ChuanHoa(cstr);

    return string(str);
}


bool KiemTraChuoiRong(string s)
{
    s= ChuanHoaString(s);
    if(s.length()==0)
        return true;
    return false;
}

string DateFormat(string s)
{
    string dd,mm,yy;
    dd= s.substr(0,2);
    mm= s.substr(2,2);
    yy=s.substr(4,7);
    return s=dd+"/"+mm+"/"+yy;
}

string replaceAll(string subject, const string& search, const string& replace)
{
    size_t pos = 0;
    // Hàm find sẽ trả về string::npos nếu không tìm thấy chuỗi con.
    while ((pos = subject.find(search, pos)) != string::npos)
    {
        subject.replace(pos, search.length(), replace);
        pos += replace.length();
    }
    return subject;
}

string DoiGioiTinh(string s)
{
    if(s=="NAM")
        return "0";
    if(s=="NU")
        return "1";
}

bool emptyFile(ifstream& pFile)
{
    return pFile.peek() == ifstream::traits_type::eof();
}


int demSoDong(const char *file_path)
{
    char buff[500];
    FILE *f = fopen(file_path, "r");

    if (f == NULL)
    {
        printf("Khong the mo file de doc.\n");
        return -1;
    }

    int row = 0;
    while (fgets(buff, 500, (FILE*)f))
    {
        row++;
    }

    fclose(f);
    return row;
}

void show_tittle()
{
    TextColor(Green);
    gotoxy(20,2);
    cout << " _______ __     __   _______                     _______         __     __                  \n";
    gotoxy(20,3);
    cout << "|_     _|  |--.|__| |_     _|.----.---.-.----.  |    |  |.-----.|  |--.|__|.-----.--------. \n";
    gotoxy(20,4);
    cout << "  |   | |     ||  |   |   |  |   _|  _  |  __|  |       ||  _  ||     ||  ||  -__|        | \n";
    gotoxy(20,5);
    cout << "  |___| |__|__||__|   |___|  |__| |___._|____|  |__|____||___  ||__|__||__||_____|__|__|__| \n";
    gotoxy(20,6);
    cout << "                                                        |_____|							 \n";
}

#endif
