#ifndef DanhSachSinhVien_H
#define DanhSachSinhVien_H

#include <iostream>
#include <string.h>
#include<string>
#include"CAUHOITHI.h"
//#include "LOPHOC.h"
#include "Menu.h"
#include "KHUNG.h"

using namespace std;

//Cau truc danh sach sinh vien
struct SinhVien
{
    char MASV[15];
    char HO[15];
    char TEN[20];
    char NgaySinh[12];
    char GioiTinh[5];
    char password[15];
    //con tro ds diem thi
    LISTDT*  listdt;
};
typedef struct SinhVien SV;

struct nodeSV
{
    SV DataSV;
    struct nodeSV *pNextSV;
};
typedef struct nodeSV NODESV;
struct listSinhVien
{
    NODESV *pHeadSV;
    int soluongSV;
};
typedef struct listSinhVien LISTSV;
/////////////////////////////////

void Khoi_Tao_DSSV(LISTSV &ds)
{
    ds.pHeadSV=NULL;
    ds.soluongSV=0;
}

NODESV *Khoi_Tao_Node_SV()
{
    NODESV *p=new NODESV;
    if(p==NULL)
    {
        BaoLoi("KHONG DU BO NHO,VUI LONG KIEM TRA LAI!!",82,4);
        return  NULL;
    }
    //p->DataSV=sv;
    p->pNextSV=NULL;
    return p;
}

void Xoa_1dong_SV(int y)
{
    int dem=0;
    gotoXY(4,y);
    while(dem<14)
    {
        cout<<" ";
        dem++;
    }
    gotoXY(19,y);
    while(dem<14+9)
    {
        cout<<" ";
        dem++;
    }
    gotoXY(29,y);
    while(dem<14+9+19)
    {
        cout<<" ";
        dem++;
    }
    gotoXY(49,y);
    while(dem<14+9+19+11)
    {
        cout<<" ";
        dem++;
    }
    gotoXY(61,y);
    while(dem<14+9+19+11+9)
    {
        cout<<" ";
        dem++;
    }
    gotoXY(71,y);
    while(dem<14+9+19+11+9+15)
    {
        cout<<" ";
        dem++;
    }
}

void Xoa_nhieu_dong_SV()
{
    for (int i = 0; i <SODONG; i++)
    {
        Xoa_1dong_SV(i+7);
    }

}

void Xuat_1SV(NODESV* k,int &y)
{
    Xoa_1dong_SV(y);
    TextColor(Blue);
    gotoXY(4,y);
    cout<<k->DataSV.MASV;
    gotoXY(19,y);
    cout<<k->DataSV.HO;
    gotoXY(29,y);
    cout<<k->DataSV.TEN;
    gotoXY(49,y);
    cout<<k->DataSV.NgaySinh;
    gotoXY(61,y);
    cout<<k->DataSV.GioiTinh;
    gotoXY(71,y);
    cout<<k->DataSV.password;
    y++;
}

void Xuat_nhieu_SV_theo_trang(LISTSV ds, int index)
{
    int y=7;
    Xoa_nhieu_dong_SV();
    index--;

    NODESV *k=ds.pHeadSV;
    for(int j=0; j<SODONG*index; j++)
        k=k->pNextSV;// bo qua trang truoc


    for (int i =  SODONG * index;  i < SODONG*( 1 + index)  && i < ds.soluongSV &&k!=NULL; i++)
    {
        Xuat_1SV(k,y);
        k=k->pNextSV;
    }

    TextColor(White);
}

void Xuat_Danh_Sach_SV(LISTSV ds)
{

    TextColor(White);
    vekhung(3,3,3,15); //MA SV
    vekhung(3,6,20,15);//MA SV
    vekhung(18,3,3,10);//HO
    vekhung(18,6,20,10);//HO
    vekhung(28,3,3,22); //TEN
    vekhung(28,6,20,22);//TEN
    vekhung(48,3,3,12);//NGAY SINH
    vekhung(48,6,20,12);//NGAY SINH
    vekhung(60,3,3,10); //GIOI TINH
    vekhung(60,6,20,10);//GIOI TINH
    vekhung(70,3,3,15);//PASSWORD
    vekhung(70,6,20,15);//PASSWORD
    gotoXY(34,2);
    cout<<"DANH SACH SINH VIEN";
    gotoXY(9,5);
    cout<<"MA SV";
    gotoXY(22,5);
    cout<<"HO";
    gotoXY(37,5);
    cout<<"TEN";
    gotoXY(50,5);
    cout<<"NGAY SINH";
    gotoXY(61,5);
    cout<<"GIOI TINH";
    gotoXY(74,5);
    cout<<"PASSWORD";

    int page=1,total_page = (ds.soluongSV%SODONG==0) ? ds.soluongSV / SODONG : ds.soluongSV/SODONG+1;//chia trang

    vekhung(3,25,1,82);
    PutCharXY(3,26,"<-: TRANG TRUOC |\t\t\t \t\t\t\t| TRANG SAU :->",Green);
    TextColor(White);
    gotoXY(29+15,26);
    cout<<"TRANG: ";
    TextColor(Yellow);
    cout<<page<<"/"<<total_page;
    TextColor(White);
    Xuat_nhieu_SV_theo_trang(ds,1);
}

int search_sv(NODESV* First, SV &x)
{
    NODESV* p;
    p = First;
    while(p != NULL)
    {
        if(strcmp(p->DataSV.MASV,x.MASV) == 0)
        {
            x = p->DataSV;
            return 1;
        }
        p = p->pNextSV;
    }
    return 0;
}

NODESV* search_nodesv(NODESV* First, char* MaSV)
{
    NODESV* p;
    p = First;
    while(p != NULL)
    {
        if(strcmp(p->DataSV.MASV,MaSV) == 0)
            return p;
        p = p->pNextSV;
    }
    return NULL;
}

SV* search_sv_ptr(NODESV* First, char* MaSV)
{
    NODESV* p;
    p = First;
    while(p != NULL)
    {
        if(strcmp(p->DataSV.MASV,MaSV) == 0)
            return &p->DataSV;
        p = p->pNextSV;
    }
    return NULL;
}


// Phep toan Insert_first: them nut moi vao dau danh sach lien ket
void Insert_first(NODESV* &First, SV x)
{
    NODESV* p;
    p = Khoi_Tao_Node_SV();
    p->DataSV = x;
    p->pNextSV = First;
    First = p;
}


// Phep toan Insert_after: them nut moi sau nut co dia chi p
void Insert_after(NODESV* p, SV x)
{
    NODESV* q;
    if(p == NULL)
        //printf("khong them sinh vien vao danh sach duoc");
        BaoLoi("LOI",82,4);
    else
    {
        q = Khoi_Tao_Node_SV();
        q->DataSV = x;
        q->pNextSV = p->pNextSV;
        p->pNextSV = q;
    }
}


int Insert_Order_SV(LISTSV &ds,NODESV* &First, SV x)
{
    NODESV* q;
    NODESV* p;  // q la nut truoc, p la nut sau
    q = NULL;
    for(p = First; p != NULL && strcmp(p->DataSV.MASV,x.MASV)<0; p = p->pNextSV)//q , node can them, p
        q = p;
    if(q == NULL)  // them nut vao dau danh sach lien ket
    {
        Insert_first(First, x);
        ds.soluongSV++;
        return 1;
    }
    else           // them nut vao sau nut q
    {
        Insert_after(q, x);
        ds.soluongSV++;
        return 1;
    }
    return 0;
}

int Delete_info(LISTSV &ds,SV x)
{
    if (ds.pHeadSV==NULL)
        return 0;
    if (strcmp(ds.pHeadSV->DataSV.MASV,x.MASV) ==0 )//xoa dau
    {
        NODESV* p=ds.pHeadSV;
        ds.pHeadSV = ds.pHeadSV->pNextSV ;
        delete p ;
        ds.soluongSV--;
        return 1;
    }

    //xoa node l tai vi tri bat ky sau nut q
    for ( NODESV* q = ds.pHeadSV; q!=NULL ; q=q->pNextSV) //q dung tai vi tri truoc vi tri can xoa (truoc node l)
    {
        if (strcmp(q->pNextSV->DataSV.MASV,x.MASV) == 0)//xoa node l sau q
        {
            NODESV* l=q->pNextSV;
            q->pNextSV=l->pNextSV;
            delete l;
            ds.soluongSV--;
            return 1;
        }
    }

    return 0;
}

int Sua_SV(LISTSV &ds, SV x)
{
    for (NODESV *k = ds.pHeadSV; k != NULL; k = k->pNextSV)
    {
        if (strcmp(k->DataSV.MASV, x.MASV) == 0)
        {
            k->DataSV=x;
            return 1;
        }
    }
    return 0;
}


SV *NhapMaSVVaoKhung(LISTSV* ds,int x,int y)
{
    ShowCur(true);
    TextColor(0x0007);
    //system("cls");
    gotoXY(x,y);
    cout<<"MA SV:";
    vekhung(x+11,y-1,1,30);
    int key=0, dx = x +12,dy = y;

    int page=1,total_page = (ds->soluongSV%SODONG==0) ? ds->soluongSV / SODONG : ds->soluongSV/SODONG+1;//chia trang

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
                BaoLoi("CHUA NHAP MA SINH VIEN!!",x+11+35,y);
                //return NULL;
            }
            else
            {
                SV * temp = new SV();
                text[0].copy(temp->MASV,20);
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
        case key_left:
            (page > 1) ? page-- : page = total_page;
            Xuat_nhieu_SV_theo_trang(*ds,page);
            TextColor(White);
            gotoXY(29+15,26);
            cout<<"TRANG: ";
            TextColor(Yellow);
            cout<<page<<"/"<<total_page;
            TextColor(White);
            break;
        case key_right:
            (page <  total_page) ? page++ : page = 1;
            Xuat_nhieu_SV_theo_trang(*ds,page);
            TextColor(White);
            gotoXY(29+15,26);
            cout<<"TRANG: ";
            TextColor(Yellow);
            cout<<page<<"/"<<total_page;
            TextColor(White);
            break;
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
    while(key!=27);
    ShowCur(false);
    return NULL;
}

#endif

