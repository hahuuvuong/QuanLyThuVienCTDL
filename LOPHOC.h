#ifndef DanhSachLopHoc_H
#define DanhSachLopHoc_H


#include <iostream>
#include <string.h>
#include <string>
#include  <fstream>
#include "SINHVIEN.h"
#include "Menu.h"
#include "KHUNG.h"

#define MAXLISTLOP 500


using namespace std;

//Cau truc danh sach lop
struct Lop
{
    char MALOP[15];
    char TENLOP[30];
    char NIENKHOA[4];
    //con tro dssv
    LISTSV* listsv;
};
typedef struct Lop LOP;

struct listLop
{
    int soluong;
    Lop *nodeLop[MAXLISTLOP];

};
typedef struct listLop LISTLOP;
/////////////////////////////////

//new
void khoi_tao_danh_sach_lop(LISTLOP &ds)
{
    ds.soluong = 0;

}


LISTLOP TimLopTheoNienKhoa(LISTLOP ds,char Ma[])
{
	LISTLOP dsReturn;
	dsReturn.soluong = 0;
    for(int i=0; i<ds.soluong; i++)
    {
        if(strcmp(Ma,ds.nodeLop[i]->NIENKHOA) == 0)
        {
            dsReturn.nodeLop[dsReturn.soluong++] =  ds.nodeLop[i]; 
        }
    }
    return dsReturn;
}

void Xoa_1dong_Lop(int y)
{
    int dem=0;
    gotoXY(4,y);
    while(dem<29)
    {
        cout<<" ";
        dem++;
    }
    gotoXY(34,y);
    while(dem<29+30)
    {
        cout<<" ";
        dem++;
    }
    gotoXY(34+30+20,y);
    while(dem<29+30+20)
    {
        cout<<" ";
        dem++;
    }
}

void Xoa_nhieu_dong_Lop()
{
    for (int i = 0; i <SODONG; i++)
    {
        Xoa_1dong_Lop(i+7);
    }

}

void Xuat_1Lop(LISTLOP ds,int i,int &y)
{
    Xoa_1dong_Lop(y);
    TextColor(Blue);
    gotoXY(4,y);
    cout<<ds.nodeLop[i]->MALOP;
    gotoXY(34,y);
    cout<<ds.nodeLop[i]->TENLOP;
    gotoXY(54,y);
    cout<<ds.nodeLop[i]->NIENKHOA;
    y++;
}

void Xuat_nhieu_Lop_theo_trang(LISTLOP ds, int index)
{
    int y=7;
    Xoa_nhieu_dong_Lop();
    index--;
    for (int i =  SODONG * index;  i < SODONG*( 1 + index)  && i <  ds.soluong ; i++)
    {
        Xuat_1Lop(ds,i,y);
    }

    TextColor(White);
}

void Xuat_Danh_Sach_LOP(LISTLOP ds)
{
    TextColor(White);
    vekhung(3,3,3,30);
    vekhung(33,3,3,30);
    vekhung(3,6,20,30);
    vekhung(33,6,20,30);
    TextColor(White);
    gotoXY(24,2);
    cout<<"DANH SACH LOP HOC";
    gotoXY(15,5);
    cout<<"MA LOP ";
    gotoXY(35,5);
    cout<<"TEN LOP";
    gotoXY(50,5);
    cout<<"NIEN KHOA";
    int page=1,total_page = (ds.soluong%SODONG==0) ? ds.soluong / SODONG : ds.soluong/SODONG+1;//chia trang
    vekhung(3,25,1,60);
    PutCharXY(4,26,"<-: TRANG TRUOC | \t\t \t\t | TRANG SAU :->",Green);
    TextColor(White);
    gotoXY(29,26);
    cout<<"TRANG: ";
    TextColor(Yellow);
    cout<<page<<"/"<<total_page;
    TextColor(White);
    Xuat_nhieu_Lop_theo_trang(ds,page);

}


//Them lop co thu tu theo ma lop
int InsertOrder_Lop (LISTLOP &ds, LOP lop)
{
    int j, k;
    if (ds.soluong ==MAXLISTLOP)
        return 0;
    for (j=0; j < ds.soluong && strcmp(ds.nodeLop[j]->MALOP,lop.MALOP)<0 ; j++ );//tim vi tri dau tien lon hon gia tri can them
    for ( k = ds.soluong-1; k >=j  ; k--)
        ds.nodeLop[k+1]= ds.nodeLop[k];
    ds.nodeLop[j]= new LOP;
    *ds.nodeLop[j]=lop;
    ds.soluong++;
    return 1;

}

////////////////////////doc & ghi lop hoc ,sinhh vien, diem

void DocFileLop_SV_Diem(LISTLOP &dsl,char* filename)
{
    fstream myfile(filename,ios::in);
    int sll=0,slsv,sldt=0;
    myfile>>sll;
    myfile.ignore();
    for(int i=0; i<sll; i++)
    {

        LOP *lop = new LOP;
        myfile.getline(lop->MALOP,sizeof(lop->MALOP),'|');
        myfile.getline(lop->TENLOP,sizeof(lop->TENLOP),'|');
		myfile.getline(lop->NIENKHOA,sizeof(lop->NIENKHOA),'|');
	    lop->listsv = new LISTSV;
        Khoi_Tao_DSSV(*lop->listsv);

        InsertOrder_Lop(dsl,*lop);

        myfile>>slsv;
        myfile.ignore();

        for(int j = 0; j < slsv ; j++)
        {
            SV* sv= new SV;

            myfile.getline(sv->MASV,sizeof(sv->MASV),'|');
            myfile.getline(sv->HO,sizeof(sv->HO),'|');
            myfile.getline(sv->TEN,sizeof(sv->TEN),'|');
            myfile.getline(sv->NgaySinh,sizeof(sv->NgaySinh),'|');
            myfile.getline(sv->GioiTinh,sizeof(sv->GioiTinh),'|');
            myfile.getline(sv->password,sizeof(sv->password),'|');

            sv->listdt = new LISTDT();
            Khoi_Tao_Danh_Sach_Diem(*sv->listdt);

            Insert_Order_SV(*lop->listsv,lop->listsv->pHeadSV,*sv);

            myfile>>sldt;
            myfile.ignore();

            for(int k = 0; k < sldt ; k++)
            {
                DIEMTHI * dt = new DIEMTHI();

                myfile.getline(dt->MAMH,sizeof(dt->MAMH),'|');
                myfile >> dt->DIEM;
                myfile.ignore();

                Insert_Order_DT(*sv->listdt,sv->listdt->pHeadDT,*dt);
            }
        }

    }
    myfile.close();
}
void GhiFileLop_SV_Diem(LISTLOP dsl,char* filename)
{
    fstream myfile(filename,ios::out);
    int n=0;
    myfile<<dsl.soluong<<endl;
    for(int i=0; i<dsl.soluong; ++i)
    {

        myfile<<dsl.nodeLop[i]->MALOP<<"|";
        myfile<<dsl.nodeLop[i]->TENLOP<<"|";
        myfile<<dsl.nodeLop[i]->NIENKHOA<<"|";
        if(dsl.nodeLop[i]->listsv==NULL)
            myfile<<n<<endl;
        else
            myfile<<dsl.nodeLop[i]->listsv->soluongSV<<endl;
        if(dsl.nodeLop[i]->listsv->soluongSV > 0)
        {
            NODESV *sv = dsl.nodeLop[i]->listsv->pHeadSV;
            while(sv!=NULL)
            {
                myfile << sv->DataSV.MASV << "|";
                myfile << sv->DataSV.HO << "|";
                myfile << sv->DataSV.TEN << "|";
                myfile << sv->DataSV.NgaySinh << "|";
                myfile << sv->DataSV.GioiTinh << "|";
                myfile << sv->DataSV.password << "|";

                if(sv->DataSV.listdt==NULL||sv->DataSV.listdt->pHeadDT==NULL)
                    myfile<<n<<endl;
                else
                    myfile<<sv->DataSV.listdt->lanthi<<endl;

                if(sv->DataSV.listdt->lanthi > 0)
                {
                    NODEDT * dt = sv->DataSV.listdt->pHeadDT;
                    while(dt!=NULL)
                    {
                        myfile << dt->DT.MAMH<<"|";
                        myfile << dt->DT.DIEM<<endl;

                        dt =dt->pNextDT;
                    }
                }
                sv = sv->pNextSV;
            }
        }

    }
    myfile.close();

}

/////////////////////////////////////////

//Xoa lop hoc theo ma lop
int Xoa_lop(LISTLOP &ds, LOP x)
{
    for(int i = 0; i < ds.soluong; i++)
    {
        if((strcmp((char *)x.MALOP, (char*)ds.nodeLop[i]->MALOP) == 0)) //MOI SUA LAI NGOAN XEM NHA :)))
        {
            delete  ds.nodeLop[i];
            for(int j=i+1; j<ds.soluong; j++)
            {
                ds.nodeLop[j-1] = ds.nodeLop[j];
            }
            ds.soluong--;
            return 1;
        }
    }
    return 0;
}

int Sua_lop(LISTLOP &ds, LOP x)
{
    for(int i = 0; i < ds.soluong; i++)
    {
        if(strcmp(x.MALOP, ds.nodeLop[i]->MALOP) == 0) //MOI SUA LAI NGOAN XEM NHA :)))
        {
            *ds.nodeLop[i] = x;
            return 1;
        }
    }
    return 0;

}
LOP *TimLopTheoMa(LISTLOP ds,char Ma[])
{
    for(int i=0; i<ds.soluong; i++)
    {
        if(strcmp(Ma,ds.nodeLop[i]->MALOP) == 0)
        {
            return ds.nodeLop[i]; 
        }
    }
    return NULL;
}
char *NhapNienKhoaVaoKhung(LISTLOP ds,int x,int y)
{
    ShowCur(true);
    TextColor(0x0007);
    //system("cls");
    gotoXY(x,y);
    cout<<"NIEN KHOA:";
    vekhung(x+11,y-1,1,30);
    int key=0, dx = x +12,dy = y;

    int page=1,total_page = (ds.soluong%SODONG==0) ? ds.soluong / SODONG : ds.soluong/SODONG+1;//chia trang

    TextColor(White);
    gotoXY(29,26);
    cout<<"TRANG: ";
    TextColor(Yellow);
    cout<<page<<"/"<<total_page;
    TextColor(White);

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
                BaoLoi("CHUA NHAP NIEN KHOA!!",x+11+35,y);
            }
            else
            {
                return string_to_charptr(text[0]);
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
            Xuat_nhieu_Lop_theo_trang(ds,page);
            TextColor(White);
            gotoXY(29,26);
            cout<<"TRANG: ";
            TextColor(Yellow);
            cout<<page<<"/"<<total_page;
            TextColor(White);
            break;
        case key_right:
            (page <  total_page) ? page++ : page = 1;
            Xuat_nhieu_Lop_theo_trang(ds,page);
            TextColor(White);
            gotoXY(29,26);
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
    while(key!= key_esc);
    ShowCur(false);
    return NULL;
}
bool KiemTraDuLieuRongCuaMenuLopHoc(int x,int y,string text[2])
{

    if(text[0].length()==0)
    {
        BaoLoi("CHUA NHAP MA LOP!!", x,y);
        return false;
    }
    else if(KiemTraChuoiRong(text[1]))
    {
        BaoLoi("CHUA NHAP TEN LOP!!", x,y+3);
        return false;
    }
    return true;
}

void timLopTheoNienKhoa(LISTLOP ds,LISTLOP &dsReturn){
    TextColor(Green);
    vekhung(69,25,1,54);
    PutCharXY(70,26,"ESC: THOAT | TAB: DOI VI TRI CON TRO | ENTER: XAC NHAN",Green);
    do
    {
        TextColor(Yellow);
        gotoXY(4,2);
        cout<<"SL LOP: "<<ds.soluong<<"/"<<MAXLISTLOP;
        Xuat_Danh_Sach_LOP(ds);
        if(ds.soluong==0)
        {
            PutCharXY(82,4,"DANH SACH LOP HOC TRONG, VUI LONG THEM LOP!!",Red);
            _getch();
            return;
        }
        char *tempL = NhapNienKhoaVaoKhung(ds,70,7);
        if(tempL != NULL)
        {
            dsReturn = TimLopTheoNienKhoa(ds,tempL);
            if(tempL==NULL)
                BaoLoi("MA LOP KHONG TON TAI, VUI LONG KIEM TRA LAI!!",82,4);
            else
                break;
        }
        else
            return;
    }
    while(1);
}
LOP *NhapLopVaoKhung(LISTLOP ds,int x,int y)
{
    ShowCur(true);
    TextColor(White);
    gotoXY(x,y);
    cout<<"MA LOP:";
    vekhung(x+11,y-1,1,30);
    gotoXY(x,y+3);
    cout<<"TEN LOP:";
    vekhung(x+11,y+2,1,30);
    gotoXY(x,y+6);
    cout<<"NIEN KHOA:";
    vekhung(x+11,y+5,1,30);
    gotoXY(x,y+9);
    int key=0, dx = x +12,dy = y;

    int page=1,total_page = (ds.soluong%SODONG==0) ? ds.soluong / SODONG : ds.soluong/SODONG+1;//chia trang

    TextColor(White);
    gotoXY(29,26);
    cout<<"TRANG: ";
    TextColor(Yellow);
    cout<<page<<"/"<<total_page;
    TextColor(White);

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
            bool kt = KiemTraDuLieuRongCuaMenuLopHoc(x+11+35,y,text);
            if(kt)
            {
                LOP *temp = new LOP();
                text[0].copy(temp->MALOP,15);
                ChuanHoaString(text[1]).copy(temp->TENLOP,30);
                ChuanHoaString(text[2]).copy(temp->NIENKHOA,4);
                return temp;
            }
            //else
            //{
                gotoXY(dx,dy);
                cout<<text[trangthai];
            //}
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
            LOP *tmp;
            tmp = TimLopTheoMa(ds,string_to_charptr(text[0]));
            if(tmp != NULL)
            {
                PutCharXY(x+12,y+3,"                              ",White);
                text[1] = string(tmp->TENLOP);
                gotoXY(x+12,y+3);
                cout<<text[1];
            }
            //break;
        }

        case key_tab:
        {

            trangthai = ++trangthai%3;//xoay vong
            dy = y+trangthai*3;
            gotoXY(dx,dy);
            cout<<text[trangthai];

            break;
        }
        {
            case key_left:
                (page > 1) ? page-- : page = total_page;
                Xuat_nhieu_Lop_theo_trang(ds,page);
                TextColor(White);
                gotoXY(29,26);
                cout<<"TRANG: ";
                TextColor(Yellow);
                cout<<page<<"/"<<total_page;
                TextColor(White);
                break;
            case key_right:
                (page <  total_page) ? page++ : page = 1;
                Xuat_nhieu_Lop_theo_trang(ds,page);
                TextColor(White);
                gotoXY(29,26);
                cout<<"TRANG: ";
                TextColor(Yellow);
                cout<<page<<"/"<<total_page;
                TextColor(White);
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
    while(key!= key_esc);
    ShowCur(false);
    return NULL;

}

LOP *NhapMaLopVaoKhung(LISTLOP ds,int x,int y)
{
    ShowCur(true);
    TextColor(0x0007);
    //system("cls");
    gotoXY(x,y);
    cout<<"MA LOP:";
    vekhung(x+11,y-1,1,30);
    int key=0, dx = x +12,dy = y;

    int page=1,total_page = (ds.soluong%SODONG==0) ? ds.soluong / SODONG : ds.soluong/SODONG+1;//chia trang

    TextColor(White);
    gotoXY(29,26);
    cout<<"TRANG: ";
    TextColor(Yellow);
    cout<<page<<"/"<<total_page;
    TextColor(White);

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
                BaoLoi("CHUA NHAP MA LOP!!",x+11+35,y);
            }
            else
            {
                LOP * temp = new LOP();
                text[0].copy(temp->MALOP,15);
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
            Xuat_nhieu_Lop_theo_trang(ds,page);
            TextColor(White);
            gotoXY(29,26);
            cout<<"TRANG: ";
            TextColor(Yellow);
            cout<<page<<"/"<<total_page;
            TextColor(White);
            break;
        case key_right:
            (page <  total_page) ? page++ : page = 1;
            Xuat_nhieu_Lop_theo_trang(ds,page);
            TextColor(White);
            gotoXY(29,26);
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
    while(key!= key_esc);
    ShowCur(false);
    return NULL;
}

#endif
