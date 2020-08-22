#ifndef DanhSachMH_CHT_H
#define DanhSachMH_CHT_H

#include "DSMH.h"
#include "CAUHOITHI.h"

using namespace std;



void In_SLCHT(LISTMH ds,int &dem,PTR_NODECHT tree)
{
    for(int i = 0; i < ds.soluongMH; i++)
    {
        gotoXY(64,6+i+1);
        cout<<SLCHTTheoMH(tree,ds.nodeMH[i]->MAMH);
    }
}
void Xuat_SL_CHT(LISTMH ds,PTR_NODECHT tree)
{
    TextColor(White);
    vekhung(63,3,3,10);
    vekhung(63,6,20,10);
    gotoXY(65,4);
    cout<<"SO LUONG";
    gotoXY(65,5);
    cout<<"CAU HOI";
    int j=0;
    TextColor(Yellow);
    In_SLCHT(ds,j,tree);
}

void QuanLyMonHoc(LISTMH &tree,PTR_NODECHT ds)
{
    int soluongmenu = 4;
    char a[4][30] =
    {
        "THEM MON HOC",
        "XOA MON HOC THEO MA MH",
        "SUA MON HOC THEO MA MH",
        "XUAT DS MON HOC",
    };
    int m;

    do
    {
        DocFileMH(tree,"MonHoc.txt");
        system("cls");
        PutCharXY(55,5,"========QUAN LY MON HOC=======",Blue);


        TextColor(Yellow);
        gotoXY(55,4);
        cout<<"SL MH: "<<tree.soluongMH;

        TextColor(Green);
        vekhung(54,25,1,30);
        PutCharXY(56,26,"ESC: THOAT | ENTER: XAC NHAN",Green);

        m= menu(55,10,a,soluongmenu);

        switch(m)
        {
        case 0:
        {
            system("cls");
            int n=0;
            MONHOC *temp;
            PutCharXY(92,2,"=========THEM MON HOC=========",Blue);
            TextColor(Green);
            vekhung(79,25,1,54);
            PutCharXY(80,26,"ESC: THOAT | TAB: DOI VI TRI CON TRO | ENTER: XAC NHAN",Green);
            do
            {
                TextColor(Yellow);
                gotoXY(4,2);
                cout<<"SL MH: "<<tree.soluongMH;
                Xuat_Danh_Sach_MH(tree);
                Xuat_SL_CHT(tree,ds);
                gotoXY(60,2);
                cout<<"SL CHT: "<<SLCHT(ds)<<"/"<<MAXLISTCHT;
                temp = NhapThongTinMonHocVaoKhung(tree,80,7);;
                if(temp != NULL)
                {
                    n=InsertOrder_MH(tree,*temp);
                    if(n==0)
                        BaoLoi("MA MON HOC DA TON TAI, VUI LONG KIEM TRA LAI!!",92,4);
                    if(n==1)
                    {
                        TextColor(Yellow);
                        gotoXY(4,2);
                        cout<<"SL MH: "<<tree.soluongMH;
                        Xuat_Danh_Sach_MH(tree);
                        Xuat_SL_CHT(tree,ds);
                        ThanhCong("THEM MON HOC THANH CONG!!",92,4);
                        GhiFileMH(tree,"MonHoc.txt");
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
            MONHOC *temp;
            PutCharXY(92,2,"======XOA MON THEO MA MH======",Blue);
            TextColor(Green);
            vekhung(79,25,1,54);
            PutCharXY(80,26,"ESC: THOAT | TAB: DOI VI TRI CON TRO | ENTER: XAC NHAN",Green);
            do
            {
                TextColor(Yellow);
                gotoXY(4,2);
                cout<<"SL MH: "<<tree.soluongMH;
                Xuat_Danh_Sach_MH(tree);
                Xuat_SL_CHT(tree,ds);
                gotoXY(60,2);
                cout<<"SL CHT: "<<SLCHT(ds)<<"/"<<MAXLISTCHT;
                if(tree.soluongMH == 0)
                {
                    PutCharXY(82,4,"DANH SACH MON HOC TRONG, VUI LONG THEM MON HOC!!",Red);
                    _getch();
                    break;
                }
                temp = NhapMaMHVaoKhung(80,7);
                if(temp!=NULL)
                {
                    n = Tim_MH(*temp,tree,*temp);
                    if(n == 0)
                        BaoLoi("MA MON HOC KHONG TON TAI, VUI LONG KIEM TRA LAI!!",92,4);
                    if(n == 1)
                    {
                        int soluachon = 2;// so luong menu
                        char a[2][30] =
                        {
                            "CO",
                            "KHONG"
                        };
                        int m;
                        gotoXY(92,13);
                        TextColor(Yellow);
                        cout<<"BAN CO CHAC CHAN MUON XOA MON HOC?";
                        m = menu_xoa(92,15,a,soluachon);
                        switch (m)
                        {
                        case 0:
                        {
                            DocFileMH(tree,"MonHoc.txt");
                            if(SLCHTTheoMH(ds,temp->MAMH)>0)
                            {
                                PutCharXY(92,13,"                                  ",White);
                                PutCharXY(92,15,"  ",White);
                                PutCharXY(92,16,"     ",White);
                                BaoLoi("MON HOC DA CO CAU HOI, KHONG THE XOA!!",92,4);
                            }
                            else
                            {
                                n=xoa_MH(*temp,tree);
                                if(n==1)
                                {

                                    PutCharXY(92,13,"                                    ",White);
                                    PutCharXY(92,15,"  ",White);
                                    PutCharXY(92,16,"     ",White);
                                    TextColor(Yellow);
                                    gotoXY(4,2);
                                    cout<<"SL MH: "<<tree.soluongMH;
                                    Xuat_Danh_Sach_MH(tree);
                                    Xuat_SL_CHT(tree,ds);
                                    ThanhCong("XOA MON HOC THANH CONG!!",92,4);
                                    GhiFileMH(tree,"MonHoc.txt");
                                }
                            }

                            break;
                        }


                        case 1:
                        {
                            PutCharXY(92,13,"                                    ",White);
                            PutCharXY(92,15,"  ",White);
                            PutCharXY(92,16,"     ",White);
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
            MONHOC* temp;
            PutCharXY(92,2,"===SUA MON HOC THEO MA MH=====",Blue);
            TextColor(Green);
            vekhung(79,25,2,82-28);
            PutCharXY(80,26,"ESC: THOAT | TAB: DOI VI TRI CON TRO | ENTER: XAC NHAN",Green);
            PutCharXY(80,27,"            `: TU DONG DIEN TH0NG TIN                 ",Green);
            do
            {
                TextColor(Yellow);
                gotoXY(4,2);
                cout<<"SL MH: "<<tree.soluongMH;
                Xuat_Danh_Sach_MH(tree);
                Xuat_SL_CHT(tree,ds);
                gotoXY(60,2);
                cout<<"SL CHT: "<<SLCHT(ds)<<"/"<<MAXLISTCHT;
                if(tree.soluongMH==0)
                {
                    PutCharXY(92,4,"DANH SACH MON HOC TRONG, VUI LONG THEM MON HOC!!",Red);
                    _getch();
                    break;
                }
                temp = NhapThongTinMonHocVaoKhung(tree,80,7);

                if(temp != NULL)
                {
                    n=Sua_MH(*temp,tree);
                    if(n==0)
                        BaoLoi("MON HOC KHONG TON TAI, VUI LONG KIEM TRA LAI!!",92,4);
                    if(n==1)
                    {
                        DocFileMH(tree,"MonHoc.txt");
                        TextColor(Yellow);
                        gotoXY(4,2);
                        cout<<"SL MH: "<<tree.soluongMH;
                        Xuat_Danh_Sach_MH(tree);
                        Xuat_SL_CHT(tree,ds);
                        ThanhCong("SUA MON HOC THANH CONG!!",92,4);
                        GhiFileMH(tree,"MonHoc.txt");
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
            TextColor(0x0007);
            TextColor(Green);
            vekhung(79,25,1,54);
            PutCharXY(80,26,"ESC: THOAT | TAB: DOI VI TRI CON TRO | ENTER: XAC NHAN",Green);
            TextColor(Yellow);
            gotoXY(4,2);
            cout<<"SL MH: "<<tree.soluongMH;
            Xuat_Danh_Sach_MH(tree);
            Xuat_SL_CHT(tree,ds);
            gotoXY(60,2);
            cout<<"SL CHT: "<<SLCHT(ds)<<"/"<<MAXLISTCHT;
            _getch();
            break;
        }

        }
        //GhiFileMH(tree,"MonHoc.txt");
    }
    while(m!=-1);

}


void QuanLyCauHoi(PTR_NODECHT &ds,LISTMH tree)
{
    DocFileMH(tree,"MonHoc.txt");
    int n=0;
    MONHOC* temp;
    MONHOC tmp1 ;
    PutCharXY(92,1,"========QUAN LY CAU HOI=======",Blue);
    PutCharXY(92,2,"=========THEO MON HOC=========",Blue);
    TextColor(Green);
    vekhung(79,25,1,54);
    PutCharXY(80,26,"ESC: THOAT | TAB: DOI VI TRI CON TRO | ENTER: XAC NHAN",Green);
    do
    {
        TextColor(Yellow);
        gotoXY(4,2);
        cout<<"SL MH: "<<tree.soluongMH;
        gotoXY(60,2);
        cout<<"SL CHT: "<<SLCHT(ds)<<"/"<<MAXLISTCHT;
        Xuat_Danh_Sach_MH(tree);
        Xuat_SL_CHT(tree,ds);
        if(tree.soluongMH==0)
        {
            PutCharXY(92,4,"DANH SACH MON HOC TRONG, VUI LONG THEM MON HOC!!",Red);
            _getch();
            return;
        }
        temp = NhapMaMHVaoKhung(80,7);
        if(temp != NULL)
        {
            n = Tim_MH(*temp,tree,tmp1);
            if(n==0)
                BaoLoi("MA MON HOC KHONG TON TAI, VUI LONG KIEM TRA LAI!!",92,4);
            else
                break;
        }
        else
            return;
    }
    while(1);



    int soluongmenu = 4;// so luong menu
    char a[4][30] =
    {
        "THEM CAU HOI",
        "XOA CAU HOI THEO ID",
        "SUA CAU HOI THEO ID",
        "XUAT DS CAU HOI"
    };
    // goi ham menu trong menu.h
    int m;
    do
    {
        system("cls");
        PutCharXY(55,5,"========QUAN LY CAU HOI=======",Blue);

        //dem = SLCHTTheoMH(ds,tmp1.MAMH);
        TextColor(Yellow);
        gotoXY(55,4);
        cout<<"SL CHT: "<<SLCHTTheoMH(ds,tmp1.MAMH);

        TextColor(Green);
        vekhung(54,25,1,30);
        PutCharXY(56,26,"ESC: THOAT | ENTER: XAC NHAN",Green);

        TextColor(Green);
        gotoXY(55,2);
        cout<<"MON HOC: "<<tmp1.TENMH<<" ("<<tmp1.MAMH<<")";

        m = menu(55,10,a,soluongmenu);
        switch (m)
        {
        case  0 :
        {
            system("cls");
            gotoXY(42,2);
            TextColor(Green);
            cout<<"MON HOC: "<<tmp1.TENMH<<" ("<<tmp1.MAMH<<")";
            int n=0;
            CHT* tmp;
            CHT* tam;
            PutCharXY(82,2,"=========THEM CAU HOI=========",Blue);
            TextColor(Green);
            vekhung(69,25,1,54);
            PutCharXY(70,26,"ESC: THOAT | TAB: DOI VI TRI CON TRO | ENTER: XAC NHAN",Green);
            do
            {

                TextColor(Yellow);
                gotoXY(4,2);
                cout<<"SL CHT: "<<SLCHTTheoMH(ds,tmp1.MAMH);
                Xuat_Danh_Sach_CHT(ds,temp->MAMH);
 	            tmp = NhapCHTVaoKhung(70,7,temp->MAMH,ds);
                if(tmp != NULL)
                {
                    n = Insert_nodeCHT(ds,*tmp);
                    if(n==0)
                        BaoLoi("DANH SACH CHT DAY, VUI LONG KIEM TRA LAI!!",82,4);
                    if(n==1)
                    {
                        TextColor(Yellow);
                        gotoXY(4,2);
                        cout<<"SL CHT: "<<SLCHTTheoMH(ds,tmp1.MAMH);
                        Xuat_Danh_Sach_CHT(ds,temp->MAMH);
                        ThanhCong("THEM CAU HOI THANH CONG!!",82,4);
                        GhiFileCHT(ds,"CauHoiThi.txt");
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
            gotoXY(42,2);
            TextColor(Green);
            cout<<"MON HOC: "<<tmp1.TENMH<<" ("<<tmp1.MAMH<<")";
            int n=0;
            CHT *tmp;
            PutCharXY(82,2,"=====XOA CAU HOI THEO ID======",Blue);
            TextColor(Green);
            vekhung(69,25,1,54);
            PutCharXY(70,26,"ESC: THOAT | TAB: DOI VI TRI CON TRO | ENTER: XAC NHAN",Green);
            do
            {
                TextColor(Yellow);
                gotoXY(4,2);
                cout<<"SL CHT: "<<SLCHTTheoMH(ds,tmp1.MAMH);
                Xuat_Danh_Sach_CHT(ds,temp->MAMH);
                if(SLCHT(ds)==0)
                {
                    PutCharXY(82,4,"DANH SACH CAU HOI TRONG, VUI LONG THEM CAU HOI!!",Red);
                    _getch();
                    break;
                }
                tmp = NhapIDCHTVaoKhung(ds,70,7,temp->MAMH);
                if(tmp!=NULL)
                {

                    tmp = TimCHTTheoID(ds,tmp->ID);
                    if(tmp == NULL)
                        BaoLoi("ID KHONG TON TAI, VUI LONG KIEM TRA LAI!!",82,4);
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
                        cout<<"BAN CO CHAC CHAN MUON XOA MON HOC?";
                        m = menu_xoa(82,15,a,soluachon);
                        switch (m)
                        {
                        case 0:
                        {

                            n = Xoa_CHT(ds,*tmp);
                            //if(n==0) BaoLoi("ID KHONG TON TAI, VUI LONG KIEM TRA LAI!!",82,4);
                            if(n==1)
                            {
                                PutCharXY(82,13,"                                    ",White);
                                PutCharXY(82,15,"  ",White);
                                PutCharXY(82,16,"     ",White);
                                TextColor(Yellow);
                                gotoXY(4,2);
                                cout<<"SL CHT: "<<SLCHTTheoMH(ds,tmp1.MAMH);//<<"/"<<MAXLISTCHT;
                                Xuat_Danh_Sach_CHT(ds,temp->MAMH);
                                ThanhCong("XOA CHT THANH CONG!!",82,4);
                                GhiFileCHT(ds,"CauHoiThi.txt");
                            }
                            break;
                        }
                        case 1:
                        {
                            PutCharXY(82,13,"                                    ",White);
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
            gotoXY(42,2);
            TextColor(Green);
            cout<<"MON HOC: "<<tmp1.TENMH<<" ("<<tmp1.MAMH<<")";
            int n=0;
            CHT* tmp;
            PutCharXY(82,1,"=====SUA CAU HOI THEO ID======",Blue);
            TextColor(Green);
            vekhung(69,25,1,82);
            PutCharXY(70,26,"ESC: THOAT | TAB: DOI VI TRI CON TRO | ENTER: XAC NHAN | `: TU DONG DIEN TH0NG TIN",Green);
            do
            {
                TextColor(Yellow);
                gotoXY(4,2);
                cout<<"SL CHT: "<<SLCHTTheoMH(ds,tmp1.MAMH);//<<"/"<<MAXLISTCHT;
                Xuat_Danh_Sach_CHT(ds,temp->MAMH);
                if(SLCHT(ds)==0)
                {
                    PutCharXY(82,3,"DANH SACH CAU HOI TRONG, VUI LONG THEM CAU HOI!!",Red);
                    _getch();
                    break;
                }
                tmp = NhapCHTVaoKhungSua(70,5,temp->MAMH,ds);
                if(tmp != NULL)
                {
                    n = Sua_CHT(ds,*tmp);
                    if(n==0)
                        BaoLoi("ID KHONG TON TAI, VUI LONG KIEM TRA LAI!!",82,3);
                    if(n==1)
                    {
                        TextColor(Yellow);
                        gotoXY(4,2);
                        cout<<"SL CHT: "<<SLCHTTheoMH(ds,tmp1.MAMH);//<<"/"<<MAXLISTCHT;
                        Xuat_Danh_Sach_CHT(ds,temp->MAMH);
                        ThanhCong("SUA CAU HOI THANH CONG!!",82,3);
                        GhiFileCHT(ds,"CauHoiThi.txt");
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
            gotoXY(42,2);
            TextColor(Green);
            cout<<"MON HOC: "<<tmp1.TENMH<<" ("<<tmp1.MAMH<<")";
            TextColor(0x0007);
            TextColor(Green);
            vekhung(69,25,1,54);
            PutCharXY(70,26,"ESC: THOAT | TAB: DOI VI TRI CON TRO | ENTER: XAC NHAN",Green);
            TextColor(Yellow);
            gotoXY(4,2);
            cout<<"SL CHT: "<<SLCHTTheoMH(ds,tmp1.MAMH);//<<"/"<<MAXLISTCHT;
            Xuat_Danh_Sach_CHT(ds,temp->MAMH);

            int key;
            int page=1,total_page = (SLCHTTheoMH(ds,temp->MAMH)%SODONGCHT==0) ? SLCHTTheoMH(ds,temp->MAMH) / SODONGCHT : SLCHTTheoMH(ds,temp->MAMH)/SODONGCHT+1;//chia trang
            do
            {
                key=getKey();
                switch(key)
                {
                case key_left:
                    (page > 1) ? page-- : page = total_page;
                    Xuat_nhieu_CHT_theo_trang(ds,page,temp->MAMH);
                    TextColor(White);
                    gotoXY(29,26);
                    cout<<"TRANG: ";
                    TextColor(Yellow);
                    cout<<page<<"/"<<total_page;
                    TextColor(White);
                    break;
                case key_right:
                    (page <  total_page) ? page++ : page = 1;
                    Xuat_nhieu_CHT_theo_trang(ds,page,temp->MAMH);
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

            //_getch();
            break;
        }
        }
        //GhiFileCHT(ds,"CauHoiThi.txt");
    }
    while(m!=-1);  // khi nhan esc menu tra ve -1 va thoat
}

#endif
