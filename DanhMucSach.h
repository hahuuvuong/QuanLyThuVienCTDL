#ifndef DANHMUCSACH_H
#define DANHMUCSACH_H
#include "CauTruc.h"
#include "DauSach.h"

NodeDMSPtr newNodeDMS(void) {
	NodeDMSPtr p;
	p = new NodeDMS;
	p->next = NULL;
	return p;
}

int isEmptyDMS(NodeDMSPtr first) {
	return(first == NULL ? true : false);
}
void insertFirstDMS(NodeDMSPtr &first, DanhMucSach x) {
	NodeDMSPtr p;
	p = newNodeDMS();
	p->info = x;
	p->next = first;
	first = p;
}
void insertLastDMS(NodeDMSPtr &first, DanhMucSach x) {
	NodeDMSPtr p, q;
	q = newNodeDMS();
	p = first;
	if (isEmptyDMS(first)) {
		insertFirstDMS(first, x);
	}
	else {
		while (p->next != NULL)
		{
			p = p->next;
		}
		q->info = x;
		p->next = q;
		q->next = NULL;
	}
}

void deleteFirstDMS(NodeDMSPtr &first) {
	NodeDMSPtr p;
	if (isEmptyDMS(first)){
		
	}
	else {
		p = first;
		first = p->next;
		free(p);
	}
}
void deleteAllDMSList(NodeDMSPtr &first) {
	while (first != NULL) {
		deleteFirstDMS(first);
	}
}
int demSoLuongDanhMucSachCuaDauSach(NodeDMSPtr First)
{ 	
	NodeDMSPtr p;
   	int stt = 0;
   	if(First == NULL)
      	return 0;
   	for(p = First ; p != NULL; p = p->next){
      	stt++;
   	}
    return stt;
}
int demSoLuongDanhMucSach(LISTDAUSACH listDauSach){
	int soLuong = 0;
	for (int i=0; i < listDauSach.soLuong; i++){
        soLuong += demSoLuongDanhMucSachCuaDauSach(listDauSach.ArrDauSach[i]->list_dms);
	}
	return soLuong;
}

DAUSACH *searchDMS(LISTDAUSACH listDauSach, DAUSACH dauSach){
	for (int i=0; i < listDauSach.soLuong; i++){
		if(strcmp(dauSach.tenSach, listDauSach.ArrDauSach[i]->tenSach) == 0){
			return listDauSach.ArrDauSach[i];
		}
	}
	return NULL;
}

DAUSACH *searchDMSByMa(LISTDAUSACH listDauSach, DAUSACH dauSach){
	for (int i=0; i < listDauSach.soLuong; i++){
		if(strcmp(dauSach.tenSach, listDauSach.ArrDauSach[i]->tenSach) == 0){
			return listDauSach.ArrDauSach[i];
		}
	}
	return NULL;
}

void Xuat_1DS(DAUSACH ds,int &y)
{
    Xoa_1dong_DG(y,62);
    TextColor(Blue);
    gotoXY(4,y);
    cout<<ds.isbnCode;
    gotoXY(16,y);
    cout<<ds.tenSach;
    gotoXY(16 + 30 + 5,y);
    cout<<ds.soTrang;
    gotoXY(16 + 30 + 4 + 10,y);
    cout<<ds.tacGia;
    gotoXY(16 + 60 + 4 + 15,y);
    cout<<ds.namXuatBan;
    gotoXY(16 + 60 + 4 + 25,y);
    cout<<ds.theLoai;
    TextColor(Green);
    y+=1;
}
bool kiemTraMaSachTonTaiMuonSach(int maSach,NodeDMSPtr First){
	NodeDMSPtr p;
   	if(First == NULL)
      	return false;
   	for(p = First ; p != NULL; p = p->next){
      	if(strcmp(to_string(maSach).c_str(),to_string(p->info.ma_sach).c_str())== 0){
			return true;
		}
   	}
    return false;
}

void thayDoiTrangThaiSach(int maSach,NodeDMSPtr& First, int trangThai){
	NodeDMSPtr p;
   	if(First == NULL)
      	return ;
   	for(p = First ; p != NULL; p = p->next){
      	if(strcmp(to_string(maSach).c_str(),to_string(p->info.ma_sach).c_str())== 0){
      		p->info.trang_thai = trangThai;
			return;
		}
   	}
}
void Xuat_nhieu_DS_theo_DG(LISTDAUSACH listDauSach, DG dg)
{
    int y=5;
    Xoa_nhieu_dong_DG(100);
    TextColor(Blue);
    gotoXY(4,4);
    cout<<"ISBN";
    
    gotoXY(16,4);
    cout<<"TENSACH";
    
    gotoXY(16 + 30 + 5,4);
    cout<<"TRANG";
    
    gotoXY(16 + 30 + 4 + 10,4);
    cout<<"TACGIA";
    
    gotoXY(16 + 60 + 4 + 15,4);
    cout<<"NXB";
    
    gotoXY(16 + 60 + 4 + 25,4);
	cout<<"THELOAI";
    TextColor(Green);
    
    MuonSachPTR p, First = dg.firstMS;
   	if(First == NULL)
   		return;
   	for(p = First ; p != NULL; p = p->next){
	    for(int j=0; j<listDauSach.soLuong; j++){
	       	if(kiemTraMaSachTonTaiMuonSach(p->info.ma_sach,listDauSach.ArrDauSach[j]->list_dms)){
	       		Xuat_1DS(*listDauSach.ArrDauSach[j],y);
	       	}
		}
   	}
    
    TextColor(White);
}

void Xuat_nhieu_DS_theo_trang(LISTDAUSACH listDauSach, int index)
{
    int y=5;
    Xoa_nhieu_dong_DG(100);
    TextColor(Blue);
    gotoXY(4,4);
    cout<<"ISBN";
    
    gotoXY(16,4);
    cout<<"TENSACH";
    
    gotoXY(16 + 30 + 5,4);
    cout<<"TRANG";
    
    gotoXY(16 + 30 + 4 + 10,4);
    cout<<"TACGIA";
    
    gotoXY(16 + 60 + 4 + 15,4);
    cout<<"NXB";
    
    gotoXY(16 + 60 + 4 + 25,4);
	cout<<"THELOAI";
    TextColor(Green);
    index--;
    int dem=0;
    for(int j=0; j<listDauSach.soLuong ; j++){
		if(dem==listDauSach.soLuong) break;
       	if(dem>= SODONGDG*(index) && dem< SODONGDG*(index)+SODONGDG)
	        Xuat_1DS(*listDauSach.ArrDauSach[dem],y);
	      	dem++;

	}

    TextColor(White);
}

void Xuat_nhieu_DS_The_Loai_theo_trang(LISTDAUSACH listDauSach, int index)
{
    int y=5;
    Xoa_nhieu_dong_DG(100);
    TextColor(Blue);
    gotoXY(4,4);
    cout<<"ISBN";
    
    gotoXY(16,4);
    cout<<"TENSACH";
    
    gotoXY(16 + 30 + 5,4);
    cout<<"TRANG";
    
    gotoXY(16 + 30 + 4 + 10,4);
    cout<<"TACGIA";
    
    gotoXY(16 + 60 + 4 + 15,4);
    cout<<"NXB";
    
    gotoXY(16 + 60 + 4 + 25,4);
	cout<<"THELOAI";
    TextColor(Green);
    index--;
    int dem=0;
    for(int j=0; j<listDauSach.soLuong ; j++){
		if(dem==listDauSach.soLuong) break;
       	if(dem>= SODONGDG*(index) && dem< SODONGDG*(index)+SODONGDG)
	        Xuat_1DS(*listDauSach.ArrDauSach[dem],y);
	      	dem++;

	}

    TextColor(White);
}

void Xuat_1DMS(NodeDMSPtr First,int &y)
{
    Xoa_1dong_DG(y,62);
    TextColor(Blue);
    gotoXY(4,y);
    cout<<First->info.ma_sach;
    gotoXY(10,y);
    string trangThai = First->info.trang_thai == 0? "CHO MUON": First->info.trang_thai == 1? "DA MUON":"DA THANH LY";
    cout<<"\t\t"<<trangThai
        <<"\t\t\t\t"<<First->info.vi_tri;
    TextColor(Green);
    y+=1;
}
void Xuat_nhieu_DMS_theo_trang(NodeDMSPtr First, int index)
{
    int y=5;
    Xoa_nhieu_dong_DG(62);
    TextColor(Blue);
    gotoXY(4,4);
    cout<<"MA SACH"
        <<"\t\tTRANG THAI"
        <<"\t\t\tVI TRI";
    TextColor(Green);
    index--;
    
	NodeDMSPtr p;
    int dem=0;
    int sumSLDMS = demSoLuongDanhMucSachCuaDauSach(First);
   	if(First == NULL)
      	return ;
    for(p = First ; p != NULL; p = p->next){
		if(dem==sumSLDMS) break;
       	if(dem>= SODONGDG*(index) && dem< SODONGDG*(index)+SODONGDG)
	        Xuat_1DMS(p,y);
	      	dem++;

	}

    TextColor(White);
}

void Xuat_Danh_Sach_DMS(NodeDMSPtr first)
{
    TextColor(0x0007);
    vekhung(3,3,20,72);
    gotoXY(24,2);
    cout<<"DANH SACH DANH MUC SACH";

    int page=1,total_page = (demSoLuongDanhMucSachCuaDauSach(first)%SODONGDG==0) ? demSoLuongDanhMucSachCuaDauSach(first)/ SODONGDG : demSoLuongDanhMucSachCuaDauSach(first)/SODONGDG+1;//chia trang
    vekhung(3,25,1,60);
    PutCharXY(4,26,"<-: TRANG TRUOC | \t\t \t\t | TRANG SAU :->",Green);
    TextColor(White);
    gotoXY(29,26);
    cout<<"TRANG: ";
    TextColor(Yellow);
    cout<<page<<"/"<<total_page;
    TextColor(White);
    Xuat_nhieu_DMS_theo_trang(first,page);
}
DAUSACH *Tim_DauSach(DAUSACH x,LISTDAUSACH ds)
{

    for(int i=0; i<ds.soLuong; i++)
    {
        if(strcmp(ds.ArrDauSach[i]->isbnCode,x.isbnCode)==0){
        	return (ds.ArrDauSach[i]);
		}
    }
    return NULL;
}

DAUSACH *TimDauSachByString(string x,LISTDAUSACH ds, int &index)
{

    for(int i=0; i<ds.soLuong; i++)
    {
        if(strcmp(ds.ArrDauSach[i]->isbnCode,x.c_str())==0){
        	index = i;
        	return (ds.ArrDauSach[i]);
		}
    }
    return NULL;
}
DAUSACH *NhapMaISBNVaoKhung(LISTDAUSACH &listDauSach,int x,int y, int &index)
{
    ShowCur(true);
    TextColor(White);
    
    gotoXY(x,y);
    cout<<"MA ISBN:";
    vekhung(x+11,y-1,1,30);
    
    int key=0, dx = x +12,dy = y;

    TextColor(White);
	int page=1,total_page = (listDauSach.soLuong%SODONGDG==0) ? listDauSach.soLuong / SODONGDG : listDauSach.soLuong/SODONGDG+1;//chia trang
    int trangthai = 0;
    string text[1] = {""};
    gotoXY(dx,dy);
    do
    {
        key = getKey();
        switch(key)
        {
        case key_enter:
        {
            if(!KiemTraChuoiRong(text[0]))
            {
                DAUSACH *targetDS = new DAUSACH();
                targetDS = TimDauSachByString(text[0],listDauSach,index);
                if(targetDS == NULL){
                	BaoLoi("ISBN KHONG TON TAI!!", x,y+3);
				}
				else{
					return targetDS;
				}
            }
            else{
            	BaoLoi("CHUA NHAP ISBN!!", x,y+3);
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
 			gotoXY(dx,dy);
 			cout<<text[trangthai];
            break;
        }
        {
            case key_left:
                (page > 1) ? page-- : page = total_page;
                Xuat_nhieu_DS_theo_trang(listDauSach,page);
                TextColor(White);
                gotoXY(29,26);
                cout<<"TRANG: ";
                TextColor(Yellow);
                cout<<page<<"/"<<total_page;
                TextColor(White);
                break;
            case key_right:
                (page <  total_page) ? page++ : page = 1;
                Xuat_nhieu_DS_theo_trang(listDauSach,page);
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
            if(trangthai==0)
            {
                if(((key>47&&key<58)) &&text[trangthai].length()<8)
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

string NhapMaSachVaoKhung(NodeDMSPtr& first,int x,int y)
{
    ShowCur(true);
    TextColor(White);
    
    gotoXY(x,y);
    cout<<"MA SACH:";
    vekhung(x+11,y-1,1,30);
    
    int key=0, dx = x +12,dy = y;

    TextColor(White);
	int trangthai = 0;
    string text[1] = {""};
    gotoXY(dx,dy);
    do
    {
        key = getKey();
        switch(key)
        {
        case key_enter:
        {
            if(!KiemTraChuoiRong(text[0]))
            {
                bool isExisted = kiemTraMaSachTonTaiMuonSach(atoi(text[0].c_str()),first);
                if(!isExisted){
                	BaoLoi("MA SACH KHONG TON TAI!!", x,y+3);
				}
				else{
					thayDoiTrangThaiSach(atoi(text[0].c_str()),first,1);
					BaoLoi("MUON SACH THANH CONG!!", x,y+3);
					return text[0];
				}
            }
            else{
            	BaoLoi("CHUA NHAP MA SACH!!", x,y+3);
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
 			gotoXY(dx,dy);
 			cout<<text[trangthai];
            break;
        }
        default:
        {
            if(trangthai==0)
            {
                if(((key>47&&key<58)) &&text[trangthai].length()<8)
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
    return "";
}

DAUSACH *NhapTenSachVaoKhung(int x,int y, int &index,LISTDAUSACH listDauSach)
{
    ShowCur(true);
    TextColor(White);
    
    gotoXY(x-20,y);
    cout<<"NHAP TEN SACH:";
    vekhung(x,y-1,1,30);
    
    int key=0, dx = x +1,dy = y;

    TextColor(White);

    int trangthai = 0;
    string text[1] = {""};
    gotoXY(dx,dy);
    do
    {
        key = getKey();
        switch(key)
        {
        case key_enter:
        {
            if(!KiemTraChuoiRong(text[0]))
            {
                DAUSACH *targetDS = new DAUSACH();
                ChuanHoaString(text[0]).copy(targetDS->tenSach, 30);
                if(searchDMS(listDauSach,*targetDS) != NULL){
                	return searchDMS(listDauSach,*targetDS);
				}
				else{
					BaoLoi("KHONG TIM THAY TEN SACH!!", x,y+3);
				}
            }
            else{
            	BaoLoi("CHUA NHAP TEN SACH!!", x,y+3);
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
 			gotoXY(dx,dy);
 			cout<<text[trangthai];
            break;
        }
        default:
        {
            if(trangthai==0)
            {
                if(((key>47&&key<58)||(key>64&&key<91)||(key>96&&key<123)||key== key_space) &&text[trangthai].length()<30)
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

bool KiemTraDuLieuRongCuaMenuDMS(int x,int y,string text[3])
{

    if(KiemTraChuoiRong(text[1]))
    {
        BaoLoi("CHUA NHAP TRANG THAI!!", x,y+3);
        return false;
    }
    else if(KiemTraChuoiRong(text[2])){
    	BaoLoi("CHUA NHAP VI TRI!!", x,y+6);
        return false;
    }
    return true;
}


DanhMucSach *NhapDanhMucSachVaoKhung(LISTDAUSACH &listDauSach,int x,int y)
{
    ShowCur(true);
    TextColor(White);
    
    gotoXY(x,y);
    cout<<"MA SACH";
    vekhung(x+11,y-1,1,30);
    
    gotoXY(x,y+3);
    cout<<"VI TRI:";
    vekhung(x+11,y+2,1,30);
    
    gotoXY(x,y+6);
    cout<<"TRANG THAI:";
    vekhung(x+11,y+5,1,30);
    PutCharXY(x+11+9,y+8,"(0:CHO MUON,1:DA MUON,2:DA THANH LY)",Yellow);
    
    int key=0, dx = x +12,dy = y;

    TextColor(White);
	int page=1,total_page = 1;//chia trang
    int trangthai = 0;
    string maSach =to_string(demSoLuongDanhMucSach(listDauSach)+1);
    string text[2] = {"",""};
    gotoXY(dx,dy);
    cout<<maSach;
    dy = dy+3;
    y = y+3;
    gotoXY(dx,dy);
    do
    {
        key = getKey();
        switch(key)
        {
        case key_enter:
        {
            bool kt = KiemTraDuLieuRongCuaMenuDMS(x+11+35,y,text);
            if(kt)
            {
                DanhMucSach *temp = new DanhMucSach();
                ChuanHoaString(text[0]).copy(temp->vi_tri,30);
                temp->trang_thai = atoi(text[1].c_str());
                temp->ma_sach = atoi(maSach.c_str());
                return temp;
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

            trangthai = ++trangthai%2;//xoay vong
            dy = y+(trangthai)*3;
            gotoXY(dx,dy);
            cout<<text[trangthai];
            break;
        }
        {
            case key_left:
                (page > 1) ? page-- : page = total_page;
                Xuat_nhieu_DS_theo_trang(listDauSach,page);
                TextColor(White);
                gotoXY(29,26);
                cout<<"TRANG: ";
                TextColor(Yellow);
                cout<<page<<"/"<<total_page;
                TextColor(White);
                break;
            case key_right:
                (page <  total_page) ? page++ : page = 1;
                Xuat_nhieu_DS_theo_trang(listDauSach,page);
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
            if((trangthai)==0)
            {
                if(((key>47&&key<58)||(key>64&&key<91)||(key>96&&key<123)||key== key_space) &&text[trangthai].length()<30)
                {
                    gotoXY(dx,dy);
                    text[trangthai]+=toupper(char(key));
                    cout<<text[trangthai];
                }

            }
            else if((trangthai )==1) 
            {
                if(( (key>47&&key<51))&&text[trangthai].length()<1)
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
#endif
