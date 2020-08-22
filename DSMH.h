#ifndef DanhSachMonHoc_H
#define DanhSachMonHoc_H

#include <iostream>
#include <string>
#include <string.h>
#include <fstream>
#include <windows.h>
#include "Menu.h"
#include "KHUNG.h"

#define STACKSIZE 500
#define MAXLISTMONHOC 300
using namespace std;


//Cau truc danh sach mon hoc
struct MonHoc
{
    char MAMH[15];
    char TENMH[30];
};
typedef struct MonHoc MONHOC;

struct listMH
{
    //int key;
    int soluongMH;
    MonHoc *nodeMH[MAXLISTMONHOC];
};
typedef struct listMH LISTMH;
//////////////////////////////
//////

//int CountNode(PTR_NODEMH T)
//{
//    if( T == NULL)
//        return 0;
//    else
//        return 1 + CountNode(T->pLeft) + CountNode(T->pRight);
//}
void khoi_tao_danh_sach_MH(LISTMH &ds)
{
    ds.soluongMH = 0;
}


int Tim_MH(MONHOC x,  LISTMH ds, MONHOC &y)
{

    for(int i=0; i<ds.soluongMH; i++)
    {
        if(strcmp(ds.nodeMH[i]->MAMH,x.MAMH)==0){
        	y=*ds.nodeMH[i];
            return 1;
		}
    }
    return 0;
}

//Them mon hoc
int InsertOrder_MH(LISTMH &ds, MONHOC x)
{
    MONHOC y;
    if(Tim_MH(x,ds,y)==1)
        return 0;

    int j, k;
    if (ds.soluongMH ==MAXLISTMONHOC )
        return 0;
    
    for (j=0; j < ds.soluongMH &&strcmp(ds.nodeMH[j]->MAMH,x.MAMH)<0 ; j++ );
    for ( k = ds.soluongMH-1; k >=j  ; k--)
        ds.nodeMH[k+1]= ds.nodeMH[k];
    ds.nodeMH[j]= new MONHOC;
    *ds.nodeMH[j]=x;
    ds.soluongMH++;
    return 1;
}

//////////////doc& ghi file mon hoc
void DocFileMH(LISTMH &t,char* filename)
{
    ifstream filein;
    MONHOC mh;
    filein.open(filename, ios_base::in);
    if(!filein.fail())
    {
        while(!filein.eof())
        {
            if (emptyFile(filein))
            {
                break;
            }
            filein.getline(mh.MAMH,sizeof(mh.MAMH),'|');
            filein.getline(mh.TENMH,sizeof(mh.TENMH));
            InsertOrder_MH(t,mh);

        }
        filein.close();
    }
}


void GhiFileMH(LISTMH &ds,char* filename)
{
    ofstream fileout;
    fileout.open(filename, ios_base::out);
    if(!fileout.fail())
    {
        for (int i=0; i < ds.soluongMH; i++)
        {

            fileout << ds.nodeMH[i]->MAMH<<"|";
        	fileout << ds.nodeMH[i]->TENMH<<endl;
        }

        fileout.close();
    }
}
////////////////////////////////////////////

//Xoa mon hoc
int  xoa_MH (MONHOC x,  LISTMH &ds )
{
    for(int i = 0; i < ds.soluongMH; i++)
    {
        if(ds.nodeMH[i]->MAMH==x.MAMH)
        {
            delete  ds.nodeMH[i];
            for(int j=i+1; j<ds.soluongMH; j++)
            {
                ds.nodeMH[j-1] = ds.nodeMH[j];
            }
            ds.soluongMH--;
            return 1;
        }
    }
    return 0;
}


int Sua_MH(MONHOC &x,  LISTMH &ds)
{
    for(int i = 0; i < ds.soluongMH; i++)
    {
        if(ds.nodeMH[i]->MAMH == x.MAMH)
        {
            //delete  ds.nodeCHT[i];
            //ds.nodeCHT[i]= new CHT;
            *ds.nodeMH[i] = x;
            return 1;
        }
    }
    return 0;
}
/*
void Xoa_1dong_MH(int y)
{
    int dem=0;
    gotoXY(4,y);while(dem<29){cout<<" "; dem++;}
    gotoXY(34,y);while(dem<29+29){cout<<" "; dem++;}
    gotoXY(64,y);while(dem<29+29+10){cout<<" "; dem++;}
}

void Xoa_nhieu_dong_MH()
{
    for (int i = 0; i <SODONG; i++)
    {
        Xoa_1dong_MH(i+7);
    }

}

void Xuat_1MH(PTR_NODEMH tree,int &y)
{
    Xoa_1dong_MH(y);
    TextColor(Blue);
    gotoXY(4,y);
    cout<<tree->data.MAMH;
    gotoXY(34,y);
    cout<<tree->data.TENMH;
    y++;
}

void Xuat_nhieu_MH_theo_trang(PTR_NODEMH tree, int index)
{
    int y=7;
    Xoa_nhieu_dong_MH();
    index--;


    for (int i =  SODONG * index;  i < SODONG*( 1 + index)  && i <  CountNode(tree) ; i++)
    {
        Xuat_1MH(tree,y);
    }

    TextColor(White);
}

*/
void Duyet_MH(LISTMH ds)
{
    for(int i = 0; i < ds.soluongMH; i++)
    {
        TextColor(Blue);
        gotoXY(4,6+i+1);
        cout<<ds.nodeMH[i]->MAMH;
        gotoXY(34,6+i+1);
        cout<<ds.nodeMH[i]->TENMH;
    }
        
}


void Xuat_Danh_Sach_MH(LISTMH ds)
{
    TextColor(White);
    vekhung(3,3,3,30);
    vekhung(3,6,20,30);
    vekhung(33,3,3,30);
    vekhung(33,6,20,30);
    gotoXY(24,2);
    cout<<"DANH SACH MON HOC";
    gotoXY(12,4);
    cout<<"MA MON HOC";
    gotoXY(42,4);
    cout<<"TEN MON HOC";
    Duyet_MH(ds);
}


bool KiemTraDuLieuRongCuaMenuMonHoc(int x,int y,string text[2])
{
    if(text[0].length()==0)
    {
        BaoLoi("CHUA NHAP MA MON HOC!!", x,y);
        return false;
    }
    else if(KiemTraChuoiRong(text[1]))
    {
        BaoLoi("CHUA NHAP TEN MON HOC!!", x,y+3);
        return false;
    }
    return true;
}
MONHOC *NhapThongTinMonHocVaoKhung(LISTMH ds,int x,int y)
{
    ShowCur(true);
    TextColor(0x0007);
    //system("cls");
    gotoXY(x,y);
    cout<<"MA MON HOC:";
    vekhung(x+11,y-1,1,30);
    gotoXY(x,y+3);
    cout<<"TEN MON HOC:";
    vekhung(x+11,y+2,1,30);
    gotoXY(x,y+6);
    int key=0, dx = x +12,dy = y;
    int trangthai = 0;
    string text[2] = {"",""};
    gotoXY(dx,dy);
    do
    {
        key = getKey();
        switch(key)
        {
        case key_enter:
        {
            bool kt = KiemTraDuLieuRongCuaMenuMonHoc(x+11+35,y,text);
            if(kt)
            {
                MONHOC * temp = new MONHOC();
                strcpy(temp->MAMH,text[0].c_str());
                //text[0].copy(temp->MAMH,15);
                //ChuanHoaString(text[1]).copy(temp->TENMH,30);
                ChuanHoa(strcpy(temp->TENMH,text[1].c_str()));
                return temp;
            }
            else
            {
                gotoXY(dx,dy);
                cout<<text[trangthai];
            }
            break;
        }
        case key_back:
        {
            if(text[trangthai].length()>0)
            {
                text[trangthai].erase(text[trangthai].length()-1,1);
                cout<<"\b \b";
            }
            break;
        }
        case 96:
        {
            /*int n=0;
            MONHOC* temp;
            MONHOC tmp;
            strcpy(temp->MAMH, text[0].c_str());

            n = Tim_MH_LNR(*temp,tree, tmp);
            if(n == 1) {
                PutCharXY(x+12,y+3,"                              ",White);
                text[1] = string(tmp.TENMH); gotoXY(x+12,y+3); cout<<text[1];
                }
            //break;*/

        }
        case key_tab:
        {

            trangthai = ++trangthai%2;//xoay vong
            dy = y+trangthai*3;
            gotoXY(dx,dy);
            cout<<text[trangthai];

            break;
        }
        default:
        {
            if(trangthai==1)
            {
                if((((key>47&&key<58)||(key>64&&key<91)||(key>96&&key<123))||key==key_space) &&text[trangthai].length()<30)
                {
                    gotoXY(dx,dy);
                    text[trangthai]+=toupper(char(key));
                    cout<<text[trangthai];
                }

            }
            else
            {
                if(((key>47&&key<58)||(key>64&&key<91)||(key>96&&key<123))&&text[trangthai].length()<15)
                {
                    gotoXY(dx,dy);
                    text[trangthai]+=toupper(char(key));
                    cout<<text[trangthai];
                }
            }
            break;
        }
        }
    }
    while(key!=key_esc);
    ShowCur(false);
    return NULL;
}

MONHOC *NhapMaMHVaoKhung(int x,int y)
{
    ShowCur(true);
    TextColor(0x0007);
    //system("cls");
    gotoXY(x,y);
    cout<<"MA MON HOC:";
    vekhung(x+11,y-1,1,30);
    //gotoXY(x,y+3); cout<<"TEN MON HOC:"; vekhung(x+11,y+2,1,30);
    //gotoXY(x,y+6);
    int key=0, dx = x +12,dy = y;
    int trangthai = 0;
    string text[1] = "";
    gotoXY(dx,dy);
    do
    {
        key = getKey();
        switch(key)
        {
        case key_enter:
        {
            if(text[0].length()==0)
            {
                BaoLoi("CHUA NHAP MA MON HOC!!",x+11+35,y);
                //return NULL;
            }
            else
            {
                MONHOC * temp = new MONHOC();
                text[0].copy(temp->MAMH,15);
                return temp;
            }

            gotoXY(dx,dy);
            cout<<text[trangthai];

            break;
        }
        case key_back:
        {
            if(text[trangthai].length()>0)
            {
                text[trangthai].erase(text[trangthai].length()-1,1);
                cout<<"\b \b";
            }
            break;
        }
        case key_tab:
        {
            break;
        }
        default:
        {
            if(((key>47&&key<58)||(key>64&&key<91)||(key>96&&key<123))&&text[trangthai].length()<15)
            {
                gotoXY(dx,dy);
                text[trangthai]+=toupper(char(key));
                cout<<text[trangthai];
            }
            break;
        }
        }
    }
    while(key!=key_esc);
    ShowCur(false);
    return NULL;
}

#endif
