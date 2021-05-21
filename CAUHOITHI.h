#ifndef DanhSachDiemThi_H
#define DanhSachDiemThi_H

#include<stdlib.h>
#include<stdio.h>
#include <iostream>
#include <string.h>
#include <fstream>
#include <algorithm>

#include "Menu.h"
#include "KHUNG.h"
//#include "DSMH.h"

#define MAXLISTCHT 2000
#define STACKSIZE 500

using namespace std;

//Cau truc danh sach diem thi
struct DiemThi
{
    char MAMH[15];
    float DIEM;
};
typedef struct DiemThi DIEMTHI;

struct nodeDT
{
    DIEMTHI DT;
    struct nodeDT *pNextDT;
};
typedef struct nodeDT NODEDT;
struct listDiemThi
{
    NODEDT *pHeadDT;
    int lanthi;
};
typedef struct listDiemThi LISTDT;
//////////////////////////////

//Cau truc danh sach cau hoi thi
struct CauHoiThi
{
    int ID;
    char MAMH[15];
    char NOIDUNG[100];
    char A[30];
    char B[30];
    char C[30];
    char D[30];
    char DAPAN[30];

};
typedef struct CauHoiThi CHT;

struct nodeCHT
{
    CHT DataCHT;
    struct nodeCHT *pLeft;
    struct nodeCHT *pRight;
};
typedef struct nodeCHT NODECHT;
typedef NODECHT* PTR_NODECHT;
////////////////////////////////

void Khoi_Tao_Danh_Sach_Diem(LISTDT &dsdiem)//dsd: danh sach diem
{
    dsdiem.pHeadDT=NULL;
    dsdiem.lanthi=0;
}

NODEDT *Khoi_Tao_Node_Diem(DIEMTHI diem)
{
    NODEDT *a=new NODEDT;
    if(a==NULL)
    {
        cout<<"\n\t Bo nho khong du dung luong! Xin vui long kiem tra lai.";
        return NULL;

    }
    //a->DT=diem;
    a->pNextDT=NULL;
    return a;
}

// Phep toan Insert_first: them nut moi vao dau danh sach lien ket
void Insert_first_DT(NODEDT* &First, DIEMTHI x)
{
    NODEDT* p;
    p = Khoi_Tao_Node_Diem(x);
    p->DT = x;
    p->pNextDT = First;
    First = p;
}


// Phep toan Insert_after: them nut moi sau nut co dia chi p
void Insert_after_DT(NODEDT* p, DIEMTHI x)
{
    NODEDT* q;
    if(p == NULL)
        //printf("khong them sinh vien vao danh sach duoc");
        BaoLoi("LOI",82,4);
    else
    {
        q = Khoi_Tao_Node_Diem(x);
        q->DT = x;
        q->pNextDT = p->pNextDT;
        p->pNextDT = q;
    }
}


int Insert_Order_DT(LISTDT &ds,NODEDT* &First, DIEMTHI x)
{
    NODEDT* q;
    NODEDT* p;  // q la nut truoc, p la nut sau
    q = NULL;
    for(p = First; p != NULL && p->DT.DIEM<x.DIEM; p = p->pNextDT)
        q = p;
    if(q == NULL)  // them nut vao dau danh sach lien ket
    {
        Insert_first_DT(First, x);
        ds.lanthi++;
        return 1;
    }
    else           // them nut vao sau nut q
    {
        Insert_after_DT(q, x);
        ds.lanthi++;
        return 1;
    }
    return 0;
}

void khoi_tao_danh_sach_cht(PTR_NODECHT &tree)
{
    tree =NULL;
}

int random(int minN, int maxN)
{
    return minN + rand() % (maxN + 1 - minN);
}
int SLCHT(PTR_NODECHT tree){
	PTR_NODECHT Stack[STACKSIZE];
	int sp = -1;
	PTR_NODECHT p = tree;
	int dem = 0;
	while(p!=NULL){
		dem++;
		if(p->pRight !=NULL)
			Stack[++sp] = p->pRight;
		if(p->pLeft != NULL)
			p = p->pLeft;
		else if(sp==-1)
			break;
		else 
			p = Stack[sp--];
	}
	return dem;
}
int SLCHTTheoMH(PTR_NODECHT tree, char mh[]){
	PTR_NODECHT Stack[STACKSIZE];
	int sp = -1;
	PTR_NODECHT p = tree;
	int dem = 0;
	while(p!=NULL){
		if(strcmp(p->DataCHT.MAMH,mh)==0)
		dem++;
		if(p->pRight !=NULL)
			Stack[++sp] = p->pRight;
		if(p->pLeft != NULL)
			p = p->pLeft;
		else if(sp==-1)
			break;
		else 
			p = Stack[sp--];
	}
	return dem;
}


void Xoa_1dong_CHT(int y)
{
    int dem=0;
    gotoXY(4,y);while(dem<60){cout<<" "; dem++;}
}

void Xoa_nhieu_dong_CHT()
{
    for (int i = 0; i <SODONGCHT*7; i++)
    {
        Xoa_1dong_CHT(i+4);
    }

}
CHT searchCHT(PTR_NODECHT root, int id ){
	PTR_NODECHT p;
    p = root;
    while( p!= NULL && p->DataCHT.ID != id)
    	if(id < p->DataCHT.ID)
    		p = p->pLeft;
    	else
    	 	p = p->pRight;
    return p->DataCHT;
}

void Xuat_1CHT(PTR_NODECHT tree,int id,int &y)
{
    Xoa_1dong_CHT(y);
    TextColor(Blue);
    gotoXY(4,y);
    CHT p = searchCHT(tree,id);
    cout<<"CAU "<<p.ID<<": "<<p.NOIDUNG
        <<"\n\tA. "<<p.A
        <<"\n\tB. "<<p.B
        <<"\n\tC. "<<p.C
        <<"\n\tD. "<<p.D
        <<"\n\tDAP AN: ";
    TextColor(Green);
    gotoXY(15,y+5);
    cout<<p.DAPAN;
    y+=7;
}

void Xuat_nhieu_CHT_theo_trang(PTR_NODECHT tree, int index,char* mmh)
{
    int y=4;
    Xoa_nhieu_dong_CHT();
    index--;
    int dem=0,j=0;
    
    PTR_NODECHT Stack[STACKSIZE];
	int sp = -1;
	PTR_NODECHT p = tree;
	while(p!=NULL){
		if(dem==SLCHTTheoMH(tree,mmh)) break;
        if(strcmp(p->DataCHT.MAMH,mmh)==0 )
        {
        		if(dem>= SODONGCHT*( index) && dem< SODONGCHT*(index)+SODONGCHT)
                Xuat_1CHT(tree,p->DataCHT.ID,y);
        		dem++;
        }
		if(p->pRight !=NULL)
			Stack[++sp] = p->pRight;
		if(p->pLeft != NULL)
			p = p->pLeft;
		else if(sp==-1)
			break;
		else 
			p = Stack[sp--];
	}

    TextColor(White);
}


void Xuat_Danh_Sach_CHT(PTR_NODECHT tree,char* mmh)
{

    TextColor(0x0007);
    vekhung(3,3,23,60);
    gotoXY(24,2);
    cout<<"DANH SACH CAU HOI";

    int page=1,total_page = (SLCHTTheoMH(tree,mmh)%SODONGCHT==0) ? SLCHTTheoMH(tree,mmh) / SODONGCHT : SLCHTTheoMH(tree,mmh)/SODONGCHT+1;//chia trang
    vekhung(3,25,1,60);
    PutCharXY(4,26,"<-: TRANG TRUOC | \t\t \t\t | TRANG SAU :->",Green);
    TextColor(White);
    gotoXY(29,26);
    cout<<"TRANG: ";
    TextColor(Yellow);
    cout<<page<<"/"<<total_page;
    TextColor(White);
    Xuat_nhieu_CHT_theo_trang(tree,page,mmh);
}

CHT *TimCHTTheoID(PTR_NODECHT tree,int id)
{
    PTR_NODECHT p = NULL;
    p = tree;
    while( p!= NULL && p->DataCHT.ID!= id)
    	if(id < p->DataCHT.ID)
    		p = p->pLeft;
    	else
    	 	p = p->pRight;
    return &(p->DataCHT);
}



int Insert_nodeCHT (PTR_NODECHT &p, CHT cht)
{
    if(p == NULL)    // nút p hiện tại sẽ là nút lá
    {
        p = new NODECHT;
        p->DataCHT = cht;
        p->pLeft = NULL;
        p->pRight = NULL;
        return 1;
    }
    else
    {
        if(p->DataCHT.ID>cht.ID)
            Insert_nodeCHT(p->pLeft,cht);
        else if(p->DataCHT.ID<cht.ID)
            Insert_nodeCHT(p->pRight, cht);
    }

}


////////////////////////////////////////doc & ghi file
void DocFileCHT(PTR_NODECHT &tree, char *filename)
{

    ifstream filein;
    CHT cht;
    filein.open(filename, ios_base::in);
    if(filein.fail())
        return;
    else
    {
        while(!filein.eof())
        {
            if (emptyFile(filein))
            {
                break;
            }

            filein.getline(cht.MAMH,sizeof(cht.MAMH),'|');
            filein.getline(cht.NOIDUNG,sizeof(cht.NOIDUNG),'|');
            filein.getline(cht.A,sizeof(cht.A),'|');
            filein.getline(cht.B,sizeof(cht.B),'|');
            filein.getline(cht.C,sizeof(cht.C),'|');
            filein.getline(cht.D,sizeof(cht.D),'|');
            filein.getline(cht.DAPAN,sizeof(cht.DAPAN),'|');
            filein>>cht.ID;
            filein.ignore();

            Insert_nodeCHT(tree,cht);
        }
        filein.close();
    }
}
void DuyetFileCHT(PTR_NODECHT &t, ofstream &fileout)
{
    if(t!=NULL)
    {
        DuyetFileCHT(t->pLeft, fileout);
        fileout << t->DataCHT.MAMH << "|";
            fileout << t->DataCHT.NOIDUNG << "|";
            fileout << t->DataCHT.A << "|";
            fileout << t->DataCHT.B << "|";
            fileout << t->DataCHT.C << "|";
            fileout << t->DataCHT.D << "|";
            fileout << t->DataCHT.DAPAN<<"|";
            fileout << t->DataCHT.ID <<endl;
        DuyetFileCHT(t->pRight, fileout);
    }
}
void GhiFileCHT(PTR_NODECHT &t,char *filename)
{
    ofstream fileout;
    fileout.open(filename, ios_base::out);
    if(!fileout.fail())
    {
         DuyetFileCHT(t, fileout);
        fileout.close();
    }
}


PTR_NODECHT rp;

void  remove_case_3 ( PTR_NODECHT &r )
{
    if (r->pLeft != NULL)
        remove_case_3 (r->pLeft);
    //den day r la nut cuc trai cua cay con ben phai co nut goc la rp}
    else
    {
    	
        rp->DataCHT.ID = r->DataCHT.ID;

        rp->DataCHT =r->DataCHT;	//  de lat nua free(rp)
        rp = r;
        r = rp->pRight;
    }
}
int  Xoa_CHT (  PTR_NODECHT &p,CHT x )
{
    if (p == NULL)
        return 0; //printf ("Khong tim thay");
    else if (x.ID < p->DataCHT.ID)
        Xoa_CHT ( p->pLeft,x);
    else if (x.ID > p->DataCHT.ID)
        Xoa_CHT (p->pRight,x);
    else    	// p->key = x
    {
        rp = p;
        if (rp->pRight == NULL)
            p = rp->pLeft;   // p là nút lá hoac la nut chi co cay con ben trai
        else if (rp->pLeft == NULL)
            p = rp->pRight;  // p là nut co cay con ben phai
        else
            remove_case_3 (rp->pRight);
        delete rp;
        return 1;
    }
}



int Sua_CHT( PTR_NODECHT &tree, CHT &x)
{
    PTR_NODECHT Stack[STACKSIZE];
    int sp=  -1;	// Khoi tao Stack rong

    while (tree!=NULL )
    {
        if(tree->DataCHT.ID == x.ID)
        {
            tree->DataCHT=x;
            return 1;
        }

        if (tree->pRight != NULL)
            Stack[++sp]= tree->pRight;
        if (tree->pLeft != NULL)
            tree=tree->pLeft;
        else  if (sp==-1)
            break;
        else
            tree=Stack[sp--];
    }
    return 0;
}
void DocFileIDCHT(int t[])
{
    ifstream filein;
    filein.open("IDCHT.txt", ios_base::in);
    int i = 0;
    int temp;
    if(!filein.fail())
    {
        while(!filein.eof())
        {
            if (emptyFile(filein))
            {
                break;
            }
            filein>>temp;
            filein.ignore();
            t[i++] = temp;

        }
        filein.close();
    }
}
bool KiemTraTrungND(PTR_NODECHT tree,char* nd){
    PTR_NODECHT Stack[STACKSIZE];
	int sp = -1;
	while(tree!=NULL){
		if(tree->DataCHT.NOIDUNG==nd)
			true;
		if(tree->pRight !=NULL)
			Stack[++sp] = tree->pRight;
		if(tree->pLeft != NULL)
			tree = tree->pLeft;
		else if(sp==-1)
			break;
		else 
			tree = Stack[sp--];
	}
	return false;
}


bool KiemTraDuLieuRongCauHoi(PTR_NODECHT tree,int x,int y,string text[])
{
    if(KiemTraChuoiRong(text[0]))
    {
        BaoLoi("CHUA NHAP NOI DUNG CAU HOI!!", x,y);
        return false;
    }
    else if(KiemTraChuoiRong(text[1]))
    {
        BaoLoi("CHUA NHAP DAP AN A!!", x,y+3);
        return false;
    }
    else if(KiemTraChuoiRong(text[2]))
    {
        BaoLoi("CHUA NHAP DAP AN B!!", x,y+6);
        return false;
    }
    else if(KiemTraChuoiRong(text[3]))
    {
        BaoLoi("CHUA NHAP DAP AN C!!", x,y+9);
        return false;
    }
    else if(KiemTraChuoiRong(text[4]))
    {
        BaoLoi("CHUA NHAP DAP AN D!!", x,y+12);
        return false;
    }
    else if(text[5].length()==0)
    {
        BaoLoi("CHUA NHAP DAP AN!!", x,y+15);
        return false;
    }else if(text[1]==text[2]||text[1]==text[3]||text[1]==text[4]||
             text[2]==text[3]||text[2]==text[4]||
             text[3]==text[4])
    {
        BaoLoi("CAU TRA LOI KHONG DUOC TRUNG NHAU!!", x-11-35+12,y-3);
        return false;
    }
	//else if(KiemTraTrungND(tree,string_to_charptr(text[0])))  {BaoLoi("CAU HOI DA TON TAI!!",x,y); return false;}
    return true;
}

bool KiemTraDuLieuRongSuaCHT(PTR_NODECHT tree,int x,int y,string text[])
{
    if(text[0].length()==0)
    {
        BaoLoi("CHUA NHAP ID!!", x,y);
        return false;
    }
    else if(KiemTraChuoiRong(text[1]))
    {
        BaoLoi("CHUA NHAP NOI DUNG CAU HOI!!", x,y+3);
        return false;
    }
    else if(KiemTraChuoiRong(text[2]))
    {
        BaoLoi("CHUA NHAP DAP AN A!!", x,y+6);
        return false;
    }
    else if(KiemTraChuoiRong(text[3]))
    {
        BaoLoi("CHUA NHAP DAP AN B!!", x,y+9);
        return false;
    }
    else if(KiemTraChuoiRong(text[4]))
    {
        BaoLoi("CHUA NHAP DAP AN C!!", x,y+12);
        return false;
    }
    else if(KiemTraChuoiRong(text[5]))
    {
        BaoLoi("CHUA NHAP DAP AN D!!", x,y+15);
        return false;
    }
    else if(text[6].length()==0)
    {
        BaoLoi("CHUA NHAP DAP AN!!", x,y+18);
        return false;
    }
    else if(text[1]==text[2]||text[1]==text[3]||text[1]==text[4]||
             text[2]==text[3]||text[2]==text[4]||
             text[3]==text[4])
    {
        BaoLoi("CAU TRA LOI KHONG DUOC TRUNG NHAU!!", x-11-35+12,y-3);
        return false;
    }//else if(KiemTraTrungND(ds,string_to_charptr(text[0])))  {BaoLoi("CAU HOI DA TON TAI!!",x,y+3); return false;}
    return true;
}

int random_number(PTR_NODECHT tree)
{
	int arr[MAXLISTCHT];
	DocFileIDCHT(arr);
	int id = arr[SLCHT(tree)];
	return id;
}


CHT *NhapCHTVaoKhung(int x,int y,char* mmh,PTR_NODECHT tree)
{
    ShowCur(true);
    TextColor(0x0007);
    //system("cls");
    gotoXY(x,y);
    cout<<"NOI DUNG:";
    vekhung(x+11,y-1,1,30);
    gotoXY(x,y+3);
    cout<<"A:";
    vekhung(x+11,y+2,1,30);
    gotoXY(x,y+6);
    cout<<"B:";
    vekhung(x+11,y+5,1,30);
    gotoXY(x,y+9);
    cout<<"C:";
    vekhung(x+11,y+8,1,30);
    gotoXY(x,y+12);
    cout<<"D:";
    vekhung(x+11,y+11,1,30);
    gotoXY(x,y+15);
    cout<<"DAP AN:";
    vekhung(x+11,y+14,1,30);
    int key=0, dx = x +12,dy = y;
    int page=1,total_page = (SLCHTTheoMH(tree,mmh)%SODONGCHT==0) ? SLCHTTheoMH(tree,mmh) / SODONGCHT : SLCHTTheoMH(tree,mmh)/SODONGCHT+1;//chia trang

    int trangthai = 0;
    string text[7] = {"","","","","","",mmh};
    gotoXY(dx,dy);
    do
    {
        key = getKey();

        switch(key)
        {
        case key_enter:
        {
            if( KiemTraDuLieuRongCauHoi(tree,x+11+35,y,text))
            {
                CHT *temp = new CHT();

                temp->ID=random_number(tree);//////////////////////////////////////////////////////////////////////////////////////////////

                text[6].copy(temp->MAMH,15);
                ChuanHoaString(text[0]).copy(temp->NOIDUNG,100);
                ChuanHoaString(text[1]).copy(temp->A,30);
                ChuanHoaString(text[2]).copy(temp->B,30);
                ChuanHoaString(text[3]).copy(temp->C,30);
                ChuanHoaString(text[4]).copy(temp->D,30);
                text[5].copy(temp->DAPAN,5);

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
            trangthai = ++trangthai%6;//xoay vong
            dy = y+trangthai*3;
            gotoXY(dx,dy);
            cout<<text[trangthai];

            break;
        }
        case key_left:
                (page > 1) ? page-- : page = total_page;
                Xuat_nhieu_CHT_theo_trang(tree,page,mmh);
                TextColor(White);
                gotoXY(29,26);
                cout<<"TRANG: ";
                TextColor(Yellow);
                cout<<page<<"/"<<total_page;
                TextColor(White);
                break;
            case key_right:
                (page <  total_page) ? page++ : page = 1;
                Xuat_nhieu_CHT_theo_trang(tree,page,mmh);
                TextColor(White);
                gotoXY(29,26);
                cout<<"TRANG: ";
                TextColor(Yellow);
                cout<<page<<"/"<<total_page;
                TextColor(White);
                break;
        default:
        {
            if(trangthai==5)
            {
                if((key==65||key==66||key==67||key==68||key==97||key==98||key==99||key==100)&&text[trangthai].length()<1)
                {
                    gotoXY(dx,dy);
                    text[trangthai]+=toupper(char(key));
                    cout<<text[trangthai];
                }

            }
            else if(trangthai== 0)
            {
                if(((key>32&&key<127)||key==key_space) &&text[trangthai].length()<100)
                {
                    gotoXY(dx,dy);
                    text[trangthai]+=toupper(char(key));
                    cout<<text[trangthai];
                }
            }
            else
            {
                if(((key>32&&key<127)||key==key_space) &&text[trangthai].length()<30)
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

CHT *NhapCHTVaoKhungSua(int x,int y,char* mmh,PTR_NODECHT tree)
{
    ShowCur(true);
    TextColor(0x0007);
    //system("cls");
    gotoXY(x,y);
    cout<<"ID:";
    vekhung(x+11,y-1,1,30);
    gotoXY(x,y+3);
    cout<<"NOI DUNG:";
    vekhung(x+11,y+2,1,30);
    gotoXY(x,y+6);
    cout<<"A:";
    vekhung(x+11,y+5,1,30);
    gotoXY(x,y+9);
    cout<<"B:";
    vekhung(x+11,y+8,1,30);
    gotoXY(x,y+12);
    cout<<"C:";
    vekhung(x+11,y+11,1,30);
    gotoXY(x,y+15);
    cout<<"D:";
    vekhung(x+11,y+14,1,30);
    gotoXY(x,y+18);
    cout<<"DAP AN:";
    vekhung(x+11,y+17,1,30);
    int page=1,total_page = (SLCHTTheoMH(tree,mmh)%SODONGCHT==0) ? SLCHTTheoMH(tree,mmh) / SODONGCHT : SLCHTTheoMH(tree,mmh)/SODONGCHT+1;//chia trang
    int key=0, dx = x +12,dy = y;
    int trangthai = 0;
    string text[8] = {"","","","","","","",mmh};
    gotoXY(dx,dy);
    do
    {
        key = getKey();

        switch(key)
        {
        case key_enter:
        {
            if( KiemTraDuLieuRongSuaCHT(tree,x+11+35,y,text))
            {
                CHT *temp = new CHT();

                temp->ID = atoi(text[0].c_str());

                ChuanHoaString(text[1]).copy(temp->NOIDUNG,100);
                ChuanHoaString(text[2]).copy(temp->A,30);
                ChuanHoaString(text[3]).copy(temp->B,30);
                ChuanHoaString(text[4]).copy(temp->C,30);
                ChuanHoaString(text[5]).copy(temp->D,30);
                text[6].copy(temp->DAPAN,5);
                text[7].copy(temp->MAMH,15);;

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
        case 96:
        {
            CHT *tmp;
            tmp = TimCHTTheoID(tree,atoi(text[0].c_str()));
            if(&tmp != NULL)
            {
                PutCharXY(x+12,y+3,"                              ",White);
                PutCharXY(x+12,y+6,"                              ",White);
                PutCharXY(x+12,y+9,"                              ",White);
                PutCharXY(x+12,y+12,"                              ",White);
                PutCharXY(x+12,y+15,"                              ",White);
                PutCharXY(x+12,y+18,"                              ",White);

                text[1] = string(tmp->NOIDUNG);
                gotoXY(x+12,y+3);
                cout<<text[1];
                text[2] = string(tmp->A);
                gotoXY(x+12,y+6);
                cout<<text[2];
                text[3] = string(tmp->B);
                gotoXY(x+12,y+9);
                cout<<text[3];
                text[4] = string(tmp->C);
                gotoXY(x+12,y+12);
                cout<<text[4];
                text[5] = string(tmp->D);
                gotoXY(x+12,y+15);
                cout<<text[5];
                text[6] = string(tmp->DAPAN);
                gotoXY(x+12,y+18);
                cout<<text[6];
            }
            //break;
        }
        case key_tab:
        {
            trangthai = ++trangthai%7;//xoay vong
            dy = y+trangthai*3;
            gotoXY(dx,dy);
            cout<<text[trangthai];

            break;
        }
        case key_left:
                (page > 1) ? page-- : page = total_page;
                Xuat_nhieu_CHT_theo_trang(tree,page,mmh);
                TextColor(White);
                gotoXY(29,26);
                cout<<"TRANG: ";
                TextColor(Yellow);
                cout<<page<<"/"<<total_page;
                TextColor(White);
                break;
            case key_right:
                (page <  total_page) ? page++ : page = 1;
                Xuat_nhieu_CHT_theo_trang(tree,page,mmh);
                TextColor(White);
                gotoXY(29,26);
                cout<<"TRANG: ";
                TextColor(Yellow);
                cout<<page<<"/"<<total_page;
                TextColor(White);
                break;
        default:
        {
            if(trangthai==0)
            {
                if((key>47&&key<58)&&text[trangthai].length()<4)
                {
                    gotoXY(dx,dy);
                    text[trangthai]+=toupper(char(key));
                    cout<<text[trangthai];
                }

            }
            else if(trangthai==6)
            {
                if((key==65||key==66||key==67||key==68||key==97||key==98||key==99||key==100)&&text[trangthai].length()<1)
                {
                    gotoXY(dx,dy);
                    text[trangthai]+=toupper(char(key));
                    cout<<text[trangthai];
                }

            }
            else if(trangthai== 1)
            {
                if(((key>32&&key<127)||key==key_space) &&text[trangthai].length()<100)
                {
                    gotoXY(dx,dy);
                    text[trangthai]+=toupper(char(key));
                    cout<<text[trangthai];
                }
            }
            else
            {
                if(((key>32&&key<127)||key==key_space) &&text[trangthai].length()<30)
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


CHT *NhapIDCHTVaoKhung(PTR_NODECHT tree,int x,int y,char* mmh)
{
    ShowCur(true);
    TextColor(0x0007);
    //system("cls");
    gotoXY(x,y);
    cout<<"ID:";
    vekhung(x+11,y-1,1,30);

    int page=1,total_page = (SLCHTTheoMH(tree,mmh)%SODONGCHT==0) ? SLCHTTheoMH(tree,mmh) / SODONGCHT : SLCHTTheoMH(tree,mmh)/SODONGCHT+1;//chia trang

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
                BaoLoi("CHUA NHAP ID CAU HOI!!",x+11+35,y);
                //return NULL;
            }
            else
            {
                CHT *temp = new CHT();

                temp->ID = atoi(text[0].c_str());

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
        case key_left:
                (page > 1) ? page-- : page = total_page;
                Xuat_nhieu_CHT_theo_trang(tree,page,mmh);
                TextColor(White);
                gotoXY(29,26);
                cout<<"TRANG: ";
                TextColor(Yellow);
                cout<<page<<"/"<<total_page;
                TextColor(White);
                break;
            case key_right:
                (page <  total_page) ? page++ : page = 1;
                Xuat_nhieu_CHT_theo_trang(tree,page,mmh);
                TextColor(White);
                gotoXY(29,26);
                cout<<"TRANG: ";
                TextColor(Yellow);
                cout<<page<<"/"<<total_page;
                TextColor(White);
                break;
        default:
        {
            if((key>47&&key<58)&&text[trangthai].length()< 4)
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
