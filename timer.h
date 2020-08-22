#ifndef Timer_H
#define Timer_H




#include <iostream>
#include <windows.h>
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

using namespace std;

char chuoigio[8] = {'0','0',':','0','0',':','0','0'};//mang luu cau hinh gio 00:00:00
bool stop = 1;// dung de dung vong lap while tring ham in dong ho

struct ThoiGian
{
    int _gio,_phut,_giay;
};

char inToA(int k)  // doi mot so (int) don sang 1 ky tu (char)
{
    switch (k)
    {
    case 0:
        return '0';
    case 1:
        return '1';
    case 2:
        return '2';
    case 3:
        return '3';
    case 4:
        return '4';
    case 5:
        return '5';
    case 6:
        return '6';
    case 7:
        return '7';
    case 8:
        return '8';
    case 9:
        return '9';
    default:
        break;
    }
}
void insertarray(ThoiGian &h)  //chuyen bien h thuoc kieu ThoiGian sang mang chuoigio
{

//	chuoigio[8] = {'0','0',':','0','0',':','0','0'} cau hinh cua chuoi gio
    int bait = 0;

    bait = h._giay;
    chuoigio[7] = inToA(bait % 10); // chia lay du, lay mot so tu ben phai qua trai vd: 23%10 = 3;  2%10 = 2
    chuoigio[6] = inToA(bait /= 10); // chia lay nguyen, lay tu trai qua phai vd: 23/10 = 2;  2/10 = 0
    //chuoigio[7] la vi tri cua giay, so ben phai
    //chuoigio[6] la vi tri cua giay, so ben trai
    bait = h._phut;
    chuoigio[4] = inToA(bait % 10);
    chuoigio[3] = inToA(bait /= 10);

    bait = h._gio;
    chuoigio[1] = inToA(bait % 10);
    chuoigio[0] = inToA(bait /= 10);
}

bool giamMotGiay(ThoiGian &h)  // ham tinh toan giam di mot giay
{
// co hai truong hop x=0 va 1<x<59 , x co the la gio , phut hoac giay

    if (h._giay > 0)
        --h._giay; // truong hop giay > 0
    else if (h._phut > 0)
    {
        //truong hop giay =0 va phut >0
        h._giay = 59;
        --h._phut;
    }
    else if (h._gio > 0)
    {
        //truong hop giay = phut = 0 va gio > 0
        --h._gio;
        h._phut = h._giay = 59;
    }
    else
        return 0; // truong hop giay = phut = gio  = 0

    return 1;
}
//dung de in ra mot chuoi thay the ham cout
void MyCout(char * chuoi,//chuoi can in ra man hinh
            int doDaiChuoi, // do dai cua chuoi
            int x, int y, // toa do muon in tren man hinh console
            int color)// chon mau nen va mau chuoi
{
    CHAR_INFO *charater = new CHAR_INFO[doDaiChuoi];
    for (int i = 0; i < doDaiChuoi; i++)
    {
        charater[i].Attributes = color;
        charater[i].Char.AsciiChar = chuoi[i];
    }
    COORD sizebuff = { doDaiChuoi,1};
    COORD pos = { 0,0 };
    SMALL_RECT earea = { x,y,x + doDaiChuoi - 1,y};
    WriteConsoleOutput(GetStdHandle(STD_OUTPUT_HANDLE), charater, sizebuff, pos, &earea);
    delete[] charater;
}
void printclock(ThoiGian tg)  //ham dung de in dong h
{
    while (stop)//vong lap dung khi stop = 0
    {
        if (!giamMotGiay(tg)) //giam di mot giam va kiem tra het gio chua
        {
            //truong hop dong ho het gio
            stop = 0;
        }
        insertarray(tg); // chuyen bien tg thuong struct ThoiGian sang chuoigio
        MyCout(chuoigio,8,100,4,Blue);// in chuoi ra man hinh
        Sleep(990);// delay 0,99 giay
    }
    return;
}
#endif
