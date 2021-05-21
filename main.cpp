#include <iostream>
#include <conio.h>
#include <string.h>
#include  <fstream>
#include <time.h>
#include <stdlib.h>
#include <thread>
#include <windows.h>

#include "Menu.h"
#include "KHUNG.h"
#include "DauSach.h"
#include "MuonTra.h"
//#include "SINHVIEN.h"
#include "LOP_SV.h"
#include "MH_CHT.h"
#include "timer.h"
#include "TheDocGia.h"

using namespace std;

SV *svlogin;

bool KiemTraDuLieuRongDangNhap(int x,int y,string text[2])
{
    if(text[0].length()==0)
    {
        BaoLoi("CHUA NHAP TAI KHOAN!!", x,y);
        return false;
    }
    //else if(KiemTraChuoiRong(text[1]))
    else if(text[1].length()==0)
    {
        BaoLoi("CHUA NHAP MAT KHAU!!", x,y+3);
        return false;
    }
    return true;
}

int DangNhap(int x,int y,LISTLOP ds)
{
    ShowCur(true);
    TextColor(Green);
    vekhung(x-3,y-5,12,75);
    TextColor(Blue);
    gotoXY(x+22,y-3);
    cout<<"DANG NHAP";
    TextColor(White);
    gotoXY(x,y);
    cout<<"TAI KHOAN:";
    vekhung(x+11,y-1,1,30);
    gotoXY(x,y+3);
    cout<<"MAT KHAU:";
    vekhung(x+11,y+2,1,30);
    //gotoXY(x,y+6);
    int key=0, dx = x +12,dy = y;
    int trangthai = 0;//con tro dangnhap cho tai khoan hay mat khau
    string text[2] = {"",""};
    gotoXY(dx,dy);
    do
    {
        key = getKey();//doi nhap mot phim
        switch(key)
        {
        case key_enter:
        {
            bool kt =KiemTraDuLieuRongDangNhap(x+11+35,y,text);
            if(kt)
            {
                if(text[0]=="GV"&&text[1]=="GV")
                    return 1;
                else
                {
                    NODESV *duyet;
                    for(int i=0; i<ds.soluong; ++i)
                    {
                        if(ds.nodeLop[i]->listsv!=NULL)
                        {

                            duyet = ds.nodeLop[i]->listsv->pHeadSV;

                            while(duyet!=NULL)
                            {

                                if(text[0]== duyet->DataSV.MASV && text[1]==duyet->DataSV.password)
                                {
                                    svlogin=&duyet->DataSV;
                                    return 2;
                                }
                                duyet=duyet->pNextSV;
                            }
                        }

                    }
                    BaoLoi("TAI KHOAN HOAC MAT KHAU KHONG CHINH XAC, VUI LONG KIEM TRA LAI!!", x,y+6);
                }
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
        case key_tab:
        {
            if(trangthai == 1)
            {
                trangthai = 0;
                dy = y;
                gotoXY(dx,dy);
                cout<<text[trangthai];
            }
            else
            {
                trangthai = 1;
                dy= y+3;
                gotoXY(dx,dy);
                cout<<text[trangthai];
            }
            break;
        }
        default:
        {
            if(((key>47&&key<58)||(key>64&&key<91)||(key>96&&key<123))&&text[trangthai].length()<15)
            {
                gotoXY(dx,dy);
                text[trangthai]+=char(key);
                if(trangthai ==1 )
                {
                    cout.fill('*');
                    cout<<setw(text[trangthai].length())<<'*';
                }
                else
                {
                    cout<<text[trangthai];
                }

            }
            break;
        }
        }
    }
    while(key!=key_esc);
    return 0;
}

bool KiemTraDuLieuRongCuaTTT(int x,int y,string text[3],LISTMH tree,PTR_NODECHT ds)
{
    if(text[0].length()==0)
    {
        BaoLoi("CHUA NHAP MA MON HOC!!", x,y);
        return false;
    }
    MONHOC mh,mh1;
    strcpy(mh.MAMH,text[0].c_str());
    if(Tim_MH(mh,tree,mh1)==1)
        return true;
    else
    {
        BaoLoi("MON HOC KHONG TON TAI!!", x,y);
        return false;
    }

    if(text[1].length()==0)
    {
        BaoLoi("CHUA NHAP SO LUONG CHT!!", x,y+3);
        return false;
    }
    if(atoi(text[1].c_str())>SLCHTTheoMH(ds,string_to_charptr(text[0]))||atoi(text[1].c_str())<1)
    {
        BaoLoi("SO LUONG CHT KHONG HOP LE!!", x,y+3);
        return false;
    }
    if(text[2].length()==0)
    {
        BaoLoi("CHUA NHAP THOI GIAN THI!!", x,y+6);
        return false;
    }
}

void Thong_tin_thi(int &soluongch,int &thoigianthi,int x,int y,LISTMH tree,PTR_NODECHT ds,char mmh[])
{
    ShowCur(true);

    TextColor(White);
    vekhung(x+11,y+10,1,30);
    gotoXY(x+11+11,y+10+1);
    cout<<"SINH VIEN";
    vekhung(x+11,y+12,4,30);
    gotoXY(x+13,y+13);
    cout<< "MA SV:   "<<svlogin->MASV;
    gotoXY(x+13,y+14);
    cout<< "TEN:     "<<svlogin->HO<<" "<<svlogin->TEN;
    gotoXY(x+13,y+15);
    cout<< "N/S:     "<<svlogin->NgaySinh;
    gotoXY(x+13,y+16);
    cout<< "G/T:     "<<svlogin->GioiTinh;

    TextColor(Green);
    vekhung(x,y+18,1,54);
    PutCharXY(x+1,y+18+1,"ESC: THOAT | TAB: DOI VI TRI CON TRO | ENTER: XAC NHAN",Green);

    Xuat_Danh_Sach_MH(tree);
    Xuat_SL_CHT(tree,ds);

    PutCharXY(92,2,"======NHAP THONG TIN THI======",Blue);
    TextColor(White);
    gotoXY(x,y);
    cout<<"MA MON HOC:";
    vekhung(x+11,y-1,1,30);
    gotoXY(x,y+3);
    cout<<"SL CAU HOI:";
    vekhung(x+11,y+2,1,30);
    gotoXY(x,y+6);
    cout<<"T/G THI:";
    vekhung(x+11,y+5,1,30);
    PutCharXY(x+11+19+6,y+6,"(PHUT)",Yellow);
    TextColor(White);
    int key=0, dx = x +12,dy = y;
    int trangthai = 0;
    string text[3] = {"","",""};
    gotoXY(dx,dy);
    do
    {
        key = getKey();
        switch(key)
        {
        case key_enter:
        {
            bool kt =KiemTraDuLieuRongCuaTTT(x+11+35,y,text,tree,ds);
            if(kt)
            {
                strcpy(mmh,text[0].c_str());
                //text[0].copy(mmh,);
                soluongch =atoi(text[1].c_str());//atoi la ep kieu chu thanh so
                thoigianthi=atoi(text[2].c_str());
                return;
                //return text[0];
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
        case key_tab:
        {
            trangthai = ++trangthai%3;//xoay vong
            dy = y+trangthai*3;
            gotoXY(dx,dy);
            cout<<text[trangthai];

            break;
        }
        default:
        {
            if(trangthai==0)
            {
                if(((key>47&&key<58)||(key>64&&key<91)||(key>96&&key<123))&&text[trangthai].length()<15)
                {
                    gotoXY(dx,dy);
                    text[trangthai]+=toupper(char(key));
                    cout<<text[trangthai];
                }
            }
            else
            {
                if((key>47&&key<58)&&text[trangthai].length()<3)
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

    //return "exit";
}
//phan danh cho sinh vien
CHT *Random_Cau_hoi(CHT ch[],int n,int soluongcanlay)//n so luong cau hoi vua loc dung
{
    if(n<1)
        return NULL;
    else
    {
        //so luong cau hoi hien co luon luon lon hon so luong cau hoi can co
        srand(time(NULL));//bo nho ngau nhien
        CHT *ds_cauHoi = new CHT[soluongcanlay];
        int index = 0, i=0;//index de chua chi so random dc

        while(i<soluongcanlay)
        {
            index = rand()%n;  //so cau hoi random luon luon nho hon so cau hoi co trong cay

        	ds_cauHoi[i++]=ch[index];// lay cau hoi can lay
        	ch[index] = ch[n-1];
        	n--;
        }
        return ds_cauHoi;
    }
}

void LocMonHoc(PTR_NODECHT ds,char mmh[],int &n,CHT ch[])// n so luong cau hoi
{
	PTR_NODECHT Stack[STACKSIZE];
	int sp = -1;
	PTR_NODECHT p = ds;
	while(p!=NULL){
		if(strcmp(p->DataCHT.MAMH,mmh)==0)
			ch[n++] = p->DataCHT;
		if(p->pRight !=NULL)
			Stack[++sp] = p->pRight;
		if(p->pLeft != NULL)
			p = p->pLeft;
		else if(sp==-1)
			break;
		else 
			p = Stack[sp--];
	}
}

void LocID(PTR_NODECHT ds,int &n,int cht[])// n so luong cau hoi
{
	PTR_NODECHT Stack[STACKSIZE];
	int sp = -1;
	PTR_NODECHT p = ds;
	while(p!=NULL){
		cht[n++] = p->DataCHT.ID;
			
		if(p->pRight !=NULL)
			Stack[++sp] = p->pRight;
		if(p->pLeft != NULL)
			p = p->pLeft;
		else if(sp==-1)
			break;
		else 
			p = Stack[sp--];
	}
}

void incauhoi(int x,int y,CHT ch, int cauhoihientai, int soluong, char dapanhientai,LISTMH ds)
{
    MONHOC a,b;
    strcpy(a.MAMH,ch.MAMH);
    Tim_MH(a,ds,b);// tim mon hoc de in ra thong tin mon hoc vao bien b
    vekhung(x-5,y-5,1,75);
    TextColor(Yellow);
    gotoXY(x,y-4);
    cout<<"MON HOC: "<<b.TENMH<<" ("<<b.MAMH<<")";
    TextColor(White);

    vekhung(x-5,y-3,15,75);//khung cau hoi
    vekhung(x-5,y+12,1,75);
    PutCharXY(x-2,y+13,"<-: CAU TRUOC\t|\t\t\t\t|\tCAU SAU: ->",Green);
    TextColor(Green);
    vekhung(x-5,y+15,1,45);
    PutCharXY(x-4,y+16,"ESC: KET THUC BAI THI | A,B,C,D: CHON DAP AN",Green);
    //TextColor(White);vekhung(x+56,y-7,1,14);//khung thoi gian

    PutCharXY(x,y,"                              ",White);
    PutCharXY(x,y+1,"                              ",White);
    PutCharXY(x,y+2,"                              ",White);
    PutCharXY(x,y+3,"                              ",White);
    PutCharXY(x,y+4,"                              ",White);
    PutCharXY(x,y+5,"                              ",White);
    gotoXY(x,y);
    cout<<"CAU: ";
    TextColor(Yellow);
    cout<<cauhoihientai+1<<"/"<<soluong;
    TextColor(White);
    gotoXY(x,++y);
    cout<<"NOI DUNG: "<<ch.NOIDUNG;
    gotoXY(x,++y);
    cout<<"A: "<<ch.A;
    gotoXY(x,++y);
    cout<<"B: "<<ch.B;
    gotoXY(x,++y);
    cout<<"C: "<<ch.C;
    gotoXY(x,++y);
    cout<<"D: "<<ch.D;
    gotoXY(x,y+=4);
    cout<<"DAP AN: ";
    TextColor(Blue);
    cout<<dapanhientai;
    TextColor(White);
}

float Cham_diem(CHT *danhsachcauhoi, int soluong, char traloi[],bool flag[])
{
    float diemmotcau = 10/(float)soluong;
    float tongdiem = 0;

    for(int i=0; i<soluong; i++)
    {
        if(*danhsachcauhoi[i].DAPAN==traloi[i])
        {
            flag[i]=true;
            tongdiem+=diemmotcau;
        }
        else
            flag[i]=false;
    }
    return tongdiem;
}

float batdauthi(CHT cauhoithi[],int soluong, int timethi,LISTMH tree,bool flag[])
{
    system("cls");
    int cauhoihientai = 0;
    int x=40,y=10;
    char *traloi = new char[soluong];

    vekhung(1,5,1,30);
    gotoXY(12,6);
    cout<<"SINH VIEN";
    vekhung(1,5+2,4,30);
    gotoXY(2,8);
    cout<< "MA SV:   "<<svlogin->MASV;
    gotoXY(2,9);
    cout<< "TEN:     "<<svlogin->HO<<" "<<svlogin->TEN;
    gotoXY(2,10);
    cout<<"N/S:     "<<svlogin->NgaySinh;
    gotoXY(2,11);
    cout<<"G/T:     "<<svlogin->GioiTinh;

    vekhung(x+75,y-5,1,20);
    gotoXY(x+83,y-4);
    cout<<"DAP AN";
    vekhung(x+75,y-5+2,14,20);//khung dap an
    vekhung(x+75,y+12,1,20);//khung diem
    //khoi gan mang tra loi

    for(int i=0; i<soluong; ++i)
        traloi[i]=' ';
    if(cauhoihientai<soluong)
    {
        stop=1;
        thread clock;
        ThoiGian tg;
        tg._gio=timethi/60;
        tg._phut=timethi%60;
        tg._giay=0;
        clock=thread(printclock,tg);
        int key;
        do
        {
            incauhoi(x,y,cauhoithi[cauhoihientai],cauhoihientai, soluong, traloi[cauhoihientai],tree);
            key=getKey();
            switch(key)
            {
            case key_left:
            {
                if(cauhoihientai>0)
                    cauhoihientai--;
                break;
            }
            case key_right:
            {
                if(cauhoihientai<soluong-1)
                    cauhoihientai++;
                break;
            }
            default:
            {
                if(key==65||key==66||key==67||key==68||key==97||key==98||key==99||key==100)
                {
                    traloi[cauhoihientai]=toupper(char(key));
                }
                break;
            }
            }
        }
        while (key!=key_esc&&stop==1);


        stop=0;// dung dong ho
        clock.join();
        //Tinh diem thi


        float diem = Cham_diem(cauhoithi,soluong,traloi,flag);
        delete [] traloi;

        int j=8,k=8;
        for(int i=0; i<soluong; i++)
        {
            if(i>13)
            {
                gotoXY(x+75+12,k++);
                cout<<"CAU "<<i+1<<": ";
                if(flag[i]==true)
                {
                    TextColor(Green);
                    cout<<cauhoithi[i].DAPAN;
                    TextColor(White);
                }
                else
                {
                    TextColor(Red);
                    cout<<cauhoithi[i].DAPAN;
                    TextColor(White);
                }
            }
            gotoXY(x+75+1,j++);
            cout<<"CAU "<<i+1<<": ";
            if(flag[i]==true)
            {
                TextColor(Green);
                cout<<cauhoithi[i].DAPAN;
                TextColor(White);
            }
            else
            {
                TextColor(Red);
                cout<<cauhoithi[i].DAPAN;
                TextColor(White);
            }
        }

        gotoXY(x+76,y+13);
        cout<<"DIEM: "<<diem;
        PutCharXY(x+45,y+16,"AN PHIM BAT KY DE THOAT!!",Cyan);
        ShowCur(false);
        _getch();
        return diem;

    }
}


void PhanThi(LISTMH ds,PTR_NODECHT tree,LISTLOP l)
{
    system("cls");

    int soluong=0,timethi=0;
    char mmh[15];
    CHT dscauhoi1mon[100];
    CHT *cauhoithi = NULL;
    int n = 0;
    Thong_tin_thi(soluong,timethi,80,7,ds,tree,mmh);
    system("cls");
    LocMonHoc(tree,mmh,n,dscauhoi1mon);// lay ra cau hoi thi cua mon hoc do gan vao bien


    cauhoithi = Random_Cau_hoi(dscauhoi1mon,n,soluong);

    if(cauhoithi!=NULL)
    {
        bool flag[soluong];
        float diem = batdauthi(cauhoithi,soluong, timethi,ds,flag);



        if(svlogin->listdt==NULL)
        {
            svlogin->listdt= new LISTDT();
            Khoi_Tao_Danh_Sach_Diem(*svlogin->listdt);
        }
        DIEMTHI DT;
        strcpy(DT.MAMH, mmh);
        DT.DIEM=diem;

        Insert_Order_DT(*svlogin->listdt,svlogin->listdt->pHeadDT,DT);

        GhiFileLop_SV_Diem(l,"Lop_SV_Diem.txt");
    }
}

void Xuat_Danh_Sach_Diem(SV *sv)
{
    int x=80,y=7;
    NODEDT *duyet=sv->listdt->pHeadDT;

    TextColor(White);
    vekhung(x+11,y+12,1,30);
    gotoXY(x+11+11,y+12+1);
    cout<<"SINH VIEN";
    vekhung(x+11,y+14,4,30);
    gotoXY(x+13,y+15);
    cout<< "MA SV:   "<<svlogin->MASV;
    gotoXY(x+13,y+16);
    cout<< "TEN:     "<<svlogin->HO<<" "<<svlogin->TEN;
    gotoXY(x+13,y+17);
    cout<< "N/S:     "<<svlogin->NgaySinh;
    gotoXY(x+13,y+18);
    cout<< "G/T:     "<<svlogin->GioiTinh;
    TextColor(White);
    vekhung(3,3,3,30);
    vekhung(33,3,3,30);
    vekhung(3,6,20,30);
    vekhung(33,6,20,30);
    gotoXY(29,2);
    cout<<"DIEM THI";
    gotoXY(10,4);
    cout<<"MA MON HOC";
    gotoXY(40,4);
    cout<<"DIEM";
    int j=7;
    while(duyet!=NULL)
    {
        TextColor(Blue);

        gotoXY(4,j);
        cout<<duyet->DT.MAMH;
        gotoXY(34,j++);
        cout<<duyet->DT.DIEM;
        duyet=duyet->pNextDT;
    }
    _getch();
}

void PhanSinhVien(LISTMH tree,PTR_NODECHT ds,LISTLOP l)
{

    char a[2][30] =
    {
        "THI",
        "XEM DIEM"

    };
    int soluongmenu = 2;
    int m = -1,x=80,y=7;
    do
    {
        system("cls");

        TextColor(White);
        vekhung(x+11,y+12,1,30);
        gotoXY(x+11+11,y+12+1);
        cout<<"SINH VIEN";
        vekhung(x+11,y+14,4,30);
        gotoXY(x+13,y+15);
        cout<< "MA SV:   "<<svlogin->MASV;
        gotoXY(x+13,y+16);
        cout<< "TEN:     "<<svlogin->HO<<" "<<svlogin->TEN;
        gotoXY(x+13,y+17);
        cout<< "N/S:     "<<svlogin->NgaySinh;
        gotoXY(x+13,y+18);
        cout<< "G/T:     "<<svlogin->GioiTinh;

        TextColor(Green);
        vekhung(54,24,1,30);
        PutCharXY(56,25,"ESC: THOAT | ENTER: XAC NHAN",Green);

        m = menu(55,13,a,soluongmenu);


        switch(m)
        {
        case 0:
        {
            system("cls");
            PhanThi(tree,ds,l);
            break;
        }
        case 1:
        {
            TextColor(0x0004);
            system("cls");
            Xuat_Danh_Sach_Diem(svlogin);
            break;
        }
        }
    }
    while(m!=-1);
}

void XuatSV(SV sv,int y)
{
    TextColor(Blue);
    gotoXY(4,y);
    cout << sv.MASV;
    gotoXY(24,y);
    cout << sv.HO<<" "<<sv.TEN;
}



void Xoa_Diem(int y)
{
    gotoXY(56,y);
    cout<<"         ";
}


int main()
{
	NODE_DG_PTR tree;
    initualizeTreeDG(tree);
    
    PTR_NODECHT ds_CHT;
    khoi_tao_danh_sach_cht(ds_CHT);

    LISTDAUSACH listDauSach;
	khoi_tao_danh_sach_DS(listDauSach);

    LISTLOP ds_LOP;
    khoi_tao_danh_sach_lop(ds_LOP);

    LISTDT ds_DT;
    Khoi_Tao_Danh_Sach_Diem(ds_DT);

    DocFileLop_SV_Diem(ds_LOP,"Lop_SV_Diem.txt");
//    DocFileMH(ds_MH,"MonHoc.txt");
    DocFileCHT(ds_CHT,"CauHoiThi.txt");


	DocFileDG(tree,"TheDocGia.txt");
	
    initDS(listDauSach);
    DocFileDS(listDauSach, "DauSach.txt");
    //man hinh dang nhap
    int tmp=0;
    do
    {

        system("cls");
        TextColor(Green);
        vekhung(42,23,1,54);
        PutCharXY(43,24,"ESC: THOAT | TAB: DOI VI TRI CON TRO | ENTER: XAC NHAN",Green);
            //-----tao ra danhTREE sach menu-----
            int soluongmenu = 4;// so luong menu

            char a[4][30] =  // khai bao mang co 4 hang va moi hang co 20 ky tu
            {

                "QUAN LY DOC GIA",
                "QUAN LY DAU SACH",
                "QUAN LY MUON TRA",
                "QUAN LY CAU HOI THI",
            };
            // goi ham menu trong menu.h
            int m;
            do
            {

                ShowCur(false);

                TextColor(0x0004);
                system("cls");
                TextColor(Green);
                vekhung(54,25,1,30);
                PutCharXY(56,26,"ESC: THOAT | ENTER: XAC NHAN",Green);
                m = menu(55,10,a,soluongmenu);

                switch (m)
                {
                case  0 ://xu ly quan ly DOC GIA
                {

                    //TextColor(0x0004);
                    system("cls");
                    QuanLyDocGia(tree);
                    break;
                }
                case 1://xu ly quan ly DAU SACH
                {
                    //TextColor(0x0004);
                    system("cls");
                    QuanLySach(listDauSach);
                    break;
                }
                case 2://xu ly quan ly muon tra
                {
                    //TextColor(0x0004);
                    system("cls");
                    QuanLyMuonTra(tree,listDauSach);
                    break;
                }
                case 3:
                {
                    //TextColor(0x0004);
                    system("cls");
//                    QuanLyCauHoi(ds_CHT,ds_MH);
                    break;

                }
                }
            }
            while(m!=-1);  // khi nhan esc menu tra ve -1 va thoat
    }
    while (tmp!=0);

    return 0;
}


