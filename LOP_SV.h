#ifndef DanhSachLop_SV_H
#define DanhSachLop_SV_H

#include "LOPHOC.h"
#include "SINHVIEN.h"

char* KiemTraTrungMaSV(LISTLOP ds, char* masv)
{
    for(int i = 0; i < ds.soluong ; i++)
    {
        NODESV *sv = ds.nodeLop[i]->listsv->pHeadSV;
        while(sv!=NULL)
        {
            if(strcmp(sv->DataSV.MASV,masv)==0)
                /*{
                    char str[50]= {' '};
                    strcat(str,ds.nodeLop[i]->TENLOP);
                    strcat(str," (");
                    strcat(str,ds.nodeLop[i]->MALOP);
                    strcat(str,")!!");
                    return str;
                }*/
                return ds.nodeLop[i]->MALOP;
            sv = sv->pNextSV;
        }
    }
    return NULL;
}


bool KiemTraDuLieuRongCuaMenuSinhVien(LISTLOP ds,int x,int y,string text[6], int checkDuplicate)
{
    if(text[0].length()==0)
    {
        BaoLoi("CHUA NHAP MA SV!!", x,y);
        return false;
    }
    else if(text[1].length()==0)
    {
        BaoLoi("CHUA NHAP HO SV!!", x,y+3);
        return false;
    }
    else if(KiemTraChuoiRong(text[2]))
    {
        BaoLoi("CHUA NHAP TEN SV!!", x,y+6);
        return false;
    }
    else if(text[3].length()==0)
    {
        BaoLoi("CHUA NHAP NGAY SINH!!", x,y+9);
        return false;
    }
    else if(text[3].length()<6)
    {
        BaoLoi("NGAY SINH KHONG HOP LE!!", x,y+9);
        return false;
    }
    else if(text[4].length()==0)
    {
        BaoLoi("CHUA NHAP GIOI TINH!!", x,y+12);
        return false;
    }
    else if(text[5].length()==0)
    {
        BaoLoi("CHUA NHAP PASSWORD!!", x,y+15);
        return false;
    }
    else if(checkDuplicate == 0 && KiemTraTrungMaSV(ds,string_to_charptr(text[0]))!=NULL)
    {
        char str[50]= {' '};
        strcat(str,"MA SV DA TON TAI O LOP ");
        strcat(str,KiemTraTrungMaSV(ds,string_to_charptr(text[0])));
        BaoLoi(str, x-11-35+12,y-3);
        return false;
    }
    return true;
}


SV *NhapSinhVienVaoKhung(LISTLOP dsl,LISTSV* ds,int x,int y,int checkDuplicate)
{
    ShowCur(true);
    TextColor(0x0007);
    gotoXY(x,y);
    cout<<"MSSV:";
    vekhung(x+11,y-1,1,30);
    gotoXY(x,y+3);
    cout<<"HO:";
    vekhung(x+11,y+2,1,30);
    gotoXY(x,y+6);
    cout<<"TEN:";
    vekhung(x+11,y+5,1,30);
    gotoXY(x,y+9);
    cout<<"NGAY SINH:";
    vekhung(x+11,y+8,1,30);
    PutCharXY(x+11+19,y+9,"(DD/MM/YYYY)",Yellow);
    TextColor(White);
    gotoXY(x,y+12);
    cout<<"GIOI TINH:";
    vekhung(x+11,y+11,1,30);
    PutCharXY(x+11+19,y+12,"(0:NAM,1:NU)",Yellow);
    TextColor(White);
    gotoXY(x,y+15);
    cout<<"PASSWORD:";
    vekhung(x+11,y+14,1,30);
    int key=0, dx = x +12,dy = y;

    int page=1,total_page = (ds->soluongSV%SODONG==0) ? ds->soluongSV / SODONG : ds->soluongSV/SODONG+1;//chia trang

    int trangthai = 0;
    string text[6] = {"","","","","",""};
    gotoXY(dx,dy);
    do
    {
        key = getKey();
        switch(key)
        {
        case key_enter:
        {
            bool kt =KiemTraDuLieuRongCuaMenuSinhVien(dsl,x+11+35,y,text,checkDuplicate);
            if(kt)
            {
                if(text[4]=="0")
                    text[4]="NAM";
                else if(text[4]=="1")
                    text[4]="NU";
                SV * temp = new SV();

                text[4].copy(temp->GioiTinh,5);
                text[0].copy(temp->MASV,15);
                text[1].copy(temp->HO,15);
                ChuanHoaString(text[2]).copy(temp->TEN,20);
                DateFormat(text[3]).copy(temp->NgaySinh,12);
                text[5].copy(temp->password,15);
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

        case key_tab:
        {
            trangthai = ++trangthai%6;//xoay vong
            dy = y+trangthai*3;
            gotoXY(dx,dy);
            cout<<text[trangthai];

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
            if(trangthai==0)
            {
                if(((key>47&&key<58)||(key>64&&key<91)||(key>96&&key<123))&&text[trangthai].length()<15)
                {
                    gotoXY(dx,dy);
                    text[trangthai]+=toupper(char(key));
                    cout<<text[trangthai];
                }

            }
            else if(trangthai==1)
            {
                if(((key>64&&key<91)||(key>96&&key<123))&&text[trangthai].length()<15)
                {
                    gotoXY(dx,dy);
                    text[trangthai]+=toupper(char(key));
                    cout<<text[trangthai];
                }

            }
            else if(trangthai==2)
            {
                if((((key>64&&key<91)||(key>96&&key<123))||key==key_space) &&text[trangthai].length()<20)
                {
                    gotoXY(dx,dy);
                    text[trangthai]+=toupper(char(key));
                    cout<<text[trangthai];
                }

            }
            else if(trangthai==3)
            {
                if((key>47&&key<58) &&text[trangthai].length()<8)
                {
                    gotoXY(dx,dy);
                    text[trangthai]+=toupper(char(key));
                    cout<<text[trangthai];
                }

            }
            else if(trangthai==4)
            {
                if((key==48||key==49) &&text[trangthai].length()<1)
                {
                    gotoXY(dx,dy);
                    text[trangthai]+=toupper(char(key));
                    cout<<text[trangthai];
                }

            }
            else if(trangthai == 5 )
            {
                if(((key>47&&key<58)||(key>64&&key<91)||(key>96&&key<123))&&text[trangthai].length()<12)
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
    while(key!=27);
    ShowCur(false);
    return NULL;
}

void QuanLyLopHoc(LISTLOP &ds)
{
    int soluongmenu = 4;
    char a[4][30] =
    {
        "THEM LOP",
        "XOA LOP THEO MA LOP",
        "SUA LOP THEO MA LOP",
        "XUAT DS LOP THEO NIEN KHOA"
    };
    int m;
    //LISTSV * dssv;

    do
    {
        system("cls");
        PutCharXY(55,5,"========QUAN LY LOP HOC=======",Blue);
        TextColor(Yellow);
        gotoXY(55,4);
        cout<<"SL LOP: "<<ds.soluong<<"/"<<MAXLISTLOP;
        TextColor(Green);
        vekhung(54,25,1,30);
        PutCharXY(56,26,"ESC: THOAT | ENTER: XAC NHAN",Green);
        m = menu(55,10,a,soluongmenu);

        switch(m)
        {
        case 0:
        {
            system("cls");
            int n=0;
            LOP* tempL=NULL;
            LOP* tmpL=NULL;
            PutCharXY(82,2,"===========THEM LOP===========",Blue);
            TextColor(Green);
            vekhung(69,25,1,54);
            PutCharXY(70,26,"ESC: THOAT | TAB: DOI VI TRI CON TRO | ENTER: XAC NHAN",Green);
            do
            {
                TextColor(Yellow);
                gotoXY(4,2);
                cout<<"SL LOP: "<<ds.soluong<<"/"<<MAXLISTLOP;
                Xuat_Danh_Sach_LOP(ds);

                tempL = NhapLopVaoKhung(ds,70,7);
                if(tempL != NULL)
                {
                    tmpL=TimLopTheoMa(ds,tempL->MALOP);
                    if(tmpL!=NULL)
                        BaoLoi("MA LOP DA TON TAI, VUI LONG KIEM TRA LAI!!",82,4);
                    else
                    {
                        tempL->listsv = new LISTSV;
                        Khoi_Tao_DSSV(*tempL->listsv);

                        n = InsertOrder_Lop(ds,*tempL);
                        if(n==0)
                            BaoLoi("DANH SACH LOP DAY, VUI LONG KIEM TRA LAI!!",82,4);
                        if(n==1)
                        {
                            TextColor(Yellow);
                            gotoXY(4,2);
                            cout<<"SL LOP: "<<ds.soluong<<"/"<<MAXLISTLOP;
                            Xuat_Danh_Sach_LOP(ds);
                            ThanhCong("THEM LOP THANH CONG!!",82,4);
                            //GhiFileLop(ds,"LopHoc.txt");
                            GhiFileLop_SV_Diem(ds,"Lop_SV_Diem.txt");
                        }
                    }
                }
                else
                    break;
            }
            while(1);
            break;
        }
        case 1:
        {
            system("cls");
            int n=0;
            LOP *tempL=NULL;
            PutCharXY(82,2,"=====XOA LOP THEO MA LOP======",Blue);
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
                    break;
                }
                tempL = NhapMaLopVaoKhung(ds,70,7);
                if(tempL!=NULL)
                {
                    tempL = TimLopTheoMa(ds,tempL->MALOP);
                    if(tempL==NULL)
                        BaoLoi("MA LOP KHONG TON TAI, VUI LONG KIEM TRA LAI!!",82,4);
                    else
                    {
                        int soluachon = 2;// so luong menu
                        char a[2][30] =
                        {
                            "CO",
                            "KHONG"
                        };
                        int m;
                        gotoXY(82,13);
                        TextColor(Yellow);
                        cout<<"BAN CO CHAC CHAN MUON XOA LOP HOC?";
                        m = menu_xoa(82,15,a,soluachon);
                        switch (m)
                        {
                        case 0:
                        {
                            {
                                if(tempL->listsv->soluongSV>0)
                                {
                                    PutCharXY(82,13,"                                  ",White);
                                    PutCharXY(82,15,"  ",White);
                                    PutCharXY(82,16,"     ",White);
                                    BaoLoi("LOP HOC DA CO SINH VIEN, KHONG THE XOA!!",82,4);
                                }
                                else
                                {
                                    n = Xoa_lop(ds,*tempL);
                                    //if(n==0) BaoLoi("MA LOP KHONG TON TAI, VUI LONG KIEM TRA LAI!!",82,4);
                                    if(n==1)
                                    {
                                        PutCharXY(82,13,"                                  ",White);
                                        PutCharXY(82,15,"  ",White);
                                        PutCharXY(82,16,"     ",White);
                                        TextColor(Yellow);
                                        gotoXY(4,2);
                                        cout<<"SL LOP: "<<ds.soluong<<"/"<<MAXLISTLOP;
                                        Xuat_Danh_Sach_LOP(ds);
                                        ThanhCong("XOA LOP HOC THANH CONG!!",82,4);
                                        //GhiFileLop(ds,"LopHoc.txt");
                                        GhiFileLop_SV_Diem(ds,"Lop_SV_Diem.txt");
                                    }
                                }
                            }

                            break;
                        }
                        case 1:
                        {
                            PutCharXY(82,13,"                                  ",White);
                            PutCharXY(82,15,"  ",White);
                            PutCharXY(82,16,"     ",White);
                            break;
                        }

                        }
                    }
                }
                else
                    break;
            }
            while(1);
            break;
        }
        case 2:
        {
            system("cls");
            int n=0;
            LOP* tempL=NULL;
            PutCharXY(82,2,"=====SUA LOP THEO MA LOP======",Blue);
            TextColor(Green);
            vekhung(69,25,1,82);
            PutCharXY(70,26,"ESC: THOAT | TAB: DOI VI TRI CON TRO | ENTER: XAC NHAN | `: TU DONG DIEN TH0NG TIN",Green);
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
                    break;
                }
                tempL = NhapLopVaoKhung(ds,70,7);
                if(tempL != NULL)
                {
                    n = Sua_lop(ds,*tempL);
                    if(n==0)
                        BaoLoi("MA LOP KHONG TON TAI, VUI LONG KIEM TRA LAI!!",82,4);
                    if(n==1)
                    {
                        TextColor(Yellow);
                        gotoXY(4,2);
                        cout<<"SL LOP: "<<ds.soluong<<"/"<<MAXLISTLOP;
                        Xuat_Danh_Sach_LOP(ds);
                        ThanhCong("SUA LOP HOC THANH CONG!!",82,4);
                        //GhiFileLop(ds,"LopHoc.txt");
                        GhiFileLop_SV_Diem(ds,"Lop_SV_Diem.txt");
                    }

                }
                else
                    break;
            }
            while(1);
            break;
        }
        case 3:
        {
            system("cls");
            LISTLOP ds_LOP;
    		khoi_tao_danh_sach_lop(ds_LOP);
            timLopTheoNienKhoa(ds,ds_LOP);
            
            TextColor(Green);
            vekhung(69,25,1,54);
            PutCharXY(70,26,"ESC: THOAT | TAB: DOI VI TRI CON TRO | ENTER: XAC NHAN",Green);
            TextColor(0x0007);
            TextColor(Yellow);
            gotoXY(4,2);
            cout<<"SL LOP: "<<ds_LOP.soluong<<"/"<<MAXLISTLOP;
            Xuat_Danh_Sach_LOP(ds_LOP);

            int key;
            int page=1,total_page = (ds_LOP.soluong/SODONG)+1;//chia trang
            do
            {
                key=getKey();
                switch(key)
                {
                case key_left:
                    (page > 1) ? page-- : page = total_page;
                    Xuat_nhieu_Lop_theo_trang(ds_LOP,page);
                    TextColor(White);
                    gotoXY(29,26);
                    cout<<"TRANG: ";
                    TextColor(Yellow);
                    cout<<page<<"/"<<total_page;
                    TextColor(White);
                    break;
                case key_right:
                    (page <  total_page) ? page++ : page = 1;
                    Xuat_nhieu_Lop_theo_trang(ds_LOP,page);
                    TextColor(White);
                    gotoXY(29,26);
                    cout<<"TRANG: ";
                    TextColor(Yellow);
                    cout<<page<<"/"<<total_page;
                    TextColor(White);
                    break;
                }
            }
            while(key!=key_esc);

            _getch();
            break;
        }
        }
        //GhiFileLop(ds,"LopHoc.txt");
    }
    while(m!=-1);
}


void QuanLySinhVien(LISTLOP &ds)
{

    LOP* tempL=NULL;
    PutCharXY(82,1,"=======QUAN LY SINH VIEN======",Blue);
    PutCharXY(82,2,"============THEO LOP==========",Blue);
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
        tempL = NhapMaLopVaoKhung(ds,70,7);
        if(tempL != NULL)
        {
            tempL = TimLopTheoMa(ds,tempL->MALOP);
            if(tempL==NULL)
                BaoLoi("MA LOP KHONG TON TAI, VUI LONG KIEM TRA LAI!!",82,4);
            else
                break;
        }
        else
            return;
    }
    while(1);

    /*if(tempL->listsv==NULL)
    {
        tempL->listsv = new LISTSV;
        Khoi_Tao_DSSV(*tempL->listsv);
    }
    LISTSV *listsv = tempL->listsv;*/

    int soluongmenu = 4;
    char a[4][30] =
    {
        "THEM SINH VIEN",
        "XOA SINH VIEN THEO MA SV",
        "SUA SINH VIEN THEO MA SV",
        "XUAT DS SINH VIEN",
    };

    int m = -1;
    LISTDT* dsdt;
    do
    {
        system("cls");
        PutCharXY(55,5,"=======QUAN LY SINH VIEN======",Blue);
        TextColor(Green);
        gotoXY(55,2);
        cout<<"LOP: "<<tempL->TENLOP<<" ("<<tempL->MALOP<<")";
        TextColor(Yellow);
        gotoXY(55,4);
        cout<<"SL SV: "<<tempL->listsv->soluongSV;
        TextColor(Green);
        vekhung(54,25,1,30);
        PutCharXY(56,26,"ESC: THOAT | ENTER: XAC NHAN",Green);

        m = menu(55,10,a,soluongmenu);

        switch(m)
        {
        case 0:
        {
            system("cls");
            gotoXY(54,2);
            TextColor(Green);
            cout<<"LOP: "<<tempL->TENLOP<<" ("<<tempL->MALOP<<")";
            int m=0,n=0;
            SV* tempSV=NULL;
            //NODESV* p;
            PutCharXY(101,2,"========THEM SINH VIEN========",Blue);
            TextColor(Green);
            vekhung(88,25,1,54);
            PutCharXY(89,26,"ESC: THOAT | TAB: DOI VI TRI CON TRO | ENTER: XAC NHAN",Green);
            do
            {
                TextColor(Yellow);
                gotoXY(4,2);
                cout<<"SL SV: "<<tempL->listsv->soluongSV;
                Xuat_Danh_Sach_SV(*tempL->listsv);

                tempSV = NhapSinhVienVaoKhung(ds,tempL->listsv,89,7,0);
                if(tempSV != NULL)
                {
                    m=search_sv(tempL->listsv->pHeadSV,*tempSV);

                    if(m==1)
                        BaoLoi("MA SV BI TRUNG, VUI LONG KIEM TRA LAI!!",101,4);
                    else
                    {
                        tempSV->listdt = new LISTDT;
                        Khoi_Tao_Danh_Sach_Diem(*tempSV->listdt);

                        n = Insert_Order_SV(*tempL->listsv,tempL->listsv->pHeadSV,*tempSV);
                        if(n==0)
                            BaoLoi("THEM SINH VIEN THAT BAI!!",101,4);
                        if(n==1)
                        {
                            TextColor(Yellow);
                            gotoXY(4,2);
                            cout<<"SL SV: "<<tempL->listsv->soluongSV;
                            Xuat_Danh_Sach_SV(*tempL->listsv);
                            ThanhCong("THEM SINH VIEN THANH CONG!!",101,4);
                            //GhiFileSV(ds,"SinhVien.txt");
                            //GhiFileDiem(ds,"DiemThi.txt");
                            GhiFileLop_SV_Diem(ds,"Lop_SV_Diem.txt");
                        }
                    }
                }
                else
                    break;
            }
            while(1);

            break;

        }
        case 1:
        {
            system("cls");
            gotoXY(54,2);
            TextColor(Green);
            cout<<"LOP: "<<tempL->TENLOP<<" ("<<tempL->MALOP<<")";
            int n=0;
            SV *tempSV=NULL;
            PutCharXY(101,2,"===XOA SINH VIEN THEO MA SV===",Blue);
            TextColor(Green);
            vekhung(88,25,1,54);
            PutCharXY(89,26,"ESC: THOAT | TAB: DOI VI TRI CON TRO | ENTER: XAC NHAN",Green);
            do
            {
                TextColor(Yellow);
                gotoXY(4,2);
                cout<<"SL SV: "<<tempL->listsv->soluongSV;
                Xuat_Danh_Sach_SV(*tempL->listsv);
                if(tempL->listsv->soluongSV==0)
                {
                    PutCharXY(101,4,"DANH SACH SINH VIEN TRONG, VUI LONG THEM SINH VIEN!!",Red);
                    _getch();
                    break;
                }
                tempSV = NhapMaSVVaoKhung(tempL->listsv,89,7);
                if(tempSV!=NULL)
                {

                    n = search_sv(tempL->listsv->pHeadSV,*tempSV);
                    if(n == 0)
                        BaoLoi("MA SV KHONG TON TAI, VUI LONG KIEM TRA LAI!!",101,4);
                    if(n == 1)
                    {
                        int soluachon = 2;// so luong menu
                        char a[2][30] =
                        {
                            "CO",
                            "KHONG"
                        };
                        int m;
                        gotoXY(101,13);
                        TextColor(Yellow);
                        cout<<"BAN CO CHAC CHAN MUON XOA SINH VIEN?";
                        m = menu_xoa(101,15,a,soluachon);
                        switch (m)
                        {
                        case 0:
                        {
                            //gotoXY(1,1);cout<<tempSV->listdt->lanthi;
                            if(tempSV->listdt->lanthi>0)
                            {
                                PutCharXY(101,13,"                                    ",White);
                                PutCharXY(101,15,"  ",White);
                                PutCharXY(101,16,"     ",White);
                                BaoLoi("SINH VIEN DA CO DIEM THI, KHONG THE XOA!!",101,4);
                            }
                            else
                            {
                                n=Delete_info(*tempL->listsv,*tempSV);
                                if(n==1)
                                {
                                    PutCharXY(101,13,"                                    ",White);
                                    PutCharXY(101,15,"  ",White);
                                    PutCharXY(101,16,"     ",White);
                                    TextColor(Yellow);
                                    gotoXY(4,2);
                                    cout<<"SL SV: "<<tempL->listsv->soluongSV;
                                    Xuat_Danh_Sach_SV(*tempL->listsv);
                                    ThanhCong("XOA SINH VIEN THANH CONG!!",101,4);
                                    //GhiFileSV(ds,"SinhVien.txt");
                                    GhiFileLop_SV_Diem(ds,"Lop_SV_Diem.txt");
                                }
                            }

                            break;
                        }
                        case 1:
                        {
                            PutCharXY(101,13,"                                    ",White);
                            PutCharXY(101,15,"  ",White);
                            PutCharXY(101,16,"     ",White);
                            break;
                        }

                        }
                    }

                }
                else
                    break;
            }
            while(1);
            break;

        }
        case 2:
        {
            system("cls");
            gotoXY(54,2);
            TextColor(Green);
            cout<<"LOP: "<<tempL->TENLOP<<" ("<<tempL->MALOP<<")";
            int n;
            SV* tempSV=NULL;
            PutCharXY(101,2,"===SUA SINH VIEN THEO MA SV===",Blue);
            TextColor(Green);
            vekhung(88,25,2,54);
            PutCharXY(89,26,"ESC: THOAT | TAB: DOI VI TRI CON TRO | ENTER: XAC NHAN",Green);
            PutCharXY(89,27,"             `: TU DONG DIEN TH0NG TIN                ",Green);
            do
            {
                TextColor(Yellow);
                gotoXY(4,2);
                cout<<"SL SV: "<<tempL->listsv->soluongSV;
                Xuat_Danh_Sach_SV(*tempL->listsv);
                if(tempL->listsv->soluongSV==0)
                {
                    PutCharXY(101,4,"DANH SACH SINH VIEN TRONG, VUI LONG THEM SINH VIEN!!",Red);
                    _getch();
                    break;
                }
                tempSV = NhapSinhVienVaoKhung(ds,tempL->listsv,89,7,1);
                if(tempSV != NULL)
                {
                    n = Sua_SV(*tempL->listsv,*tempSV);
                    if(n==0)
                        BaoLoi("MA SV KHONG TON TAI, VUI LONG KIEM TRA LAI!!",101,4);
                    if(n==1)
                    {
                        TextColor(Yellow);
                        gotoXY(4,2);
                        cout<<"SL SV: "<<tempL->listsv->soluongSV;
                        Xuat_Danh_Sach_SV(*tempL->listsv);
                        ThanhCong("SUA SINH VIEN THANH CONG!!",101,4);
                        //GhiFileSV(ds,"SinhVien.txt");
                        GhiFileLop_SV_Diem(ds,"Lop_SV_Diem.txt");
                    }

                }
                else
                    break;
            }
            while(1);
            break;

        }
        case 3:
        {
            system("cls");
            gotoXY(54,2);
            TextColor(Green);
            cout<<"LOP: "<<tempL->TENLOP<<" ("<<tempL->MALOP<<")";
            TextColor(0x0007);
            TextColor(Green);
            vekhung(88,25,1,54);
            PutCharXY(89,26,"ESC: THOAT | TAB: DOI VI TRI CON TRO | ENTER: XAC NHAN",Green);
            TextColor(Yellow);
            gotoXY(4,2);
            cout<<"SL SV: "<<tempL->listsv->soluongSV;
            Xuat_Danh_Sach_SV(*tempL->listsv);
            int key;
            int page=1,total_page = (tempL->listsv->soluongSV/SODONG)+1;//chia trang

            do
            {
                key=getKey();
                switch(key)
                {
                case key_left:
                    (page > 1) ? page-- : page = total_page;
                    Xuat_nhieu_SV_theo_trang(*tempL->listsv,page);
                    TextColor(White);
                    gotoXY(29+15,26);
                    cout<<"TRANG: ";
                    TextColor(Yellow);
                    cout<<page<<"/"<<total_page;
                    TextColor(White);
                    break;
                case key_right:
                    (page <  total_page) ? page++ : page = 1;
                    Xuat_nhieu_SV_theo_trang(*tempL->listsv,page);
                    TextColor(White);
                    gotoXY(29+15,26);
                    cout<<"TRANG: ";
                    TextColor(Yellow);
                    cout<<page<<"/"<<total_page;
                    TextColor(White);
                    break;
                }
            }
            while(key!=key_esc);

            break;

        }
        }
    }
    while(m!=-1);
}


#endif // DanhSachLop_SV_H
