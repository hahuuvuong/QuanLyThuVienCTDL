#ifndef DAUSACH_H
#define DAUSACH_H
#include "TheDocGia.h"
#include "DanhMucSach.h"
#include "CauTruc.h"
#define MAXLISTDAUSACH 500

void khoi_tao_danh_sach_DS(LISTDAUSACH& listDauSach)
{
    listDauSach.soLuong = 0;
}

int InsertOrder_DS(LISTDAUSACH& ds, DAUSACH* x)
{
    if (Tim_DauSach(*x, ds) != NULL)
        return 0;

    int j, k;
    if (ds.soLuong == MAXLISTDAUSACH)
        return 0;

    for (j = 0; j < ds.soLuong && strcmp(ds.ArrDauSach[j]->isbnCode, x->isbnCode) < 0; j++)
        ;
    for (k = ds.soLuong - 1; k >= j; k--)
        ds.ArrDauSach[k + 1] = ds.ArrDauSach[k];
    ds.ArrDauSach[j] = x;
    ds.soLuong++;
    return 1;
}

void DocFileDS(LISTDAUSACH& t, char* filename)
{
    ifstream filein;
    filein.open(filename, ios_base::in);
    int i = 0;
    if (!filein.fail()) {
        while (!filein.eof()) {

            DAUSACH* ds = new DAUSACH();
            if (emptyFile(filein)) {
                break;
            }
            char temp[5];
            int soLuongDMS;
            filein.getline(ds->isbnCode, sizeof(ds->isbnCode), '|');
            filein.getline(ds->tenSach, sizeof(ds->tenSach), '|');
            filein.getline(ds->tacGia, sizeof(ds->tacGia), '|');
            filein.getline(ds->namXuatBan, sizeof(ds->namXuatBan), '|');
            filein.getline(ds->theLoai, sizeof(ds->theLoai), '|');
            filein.getline(temp, sizeof(temp), '|');
            ds->soTrang = atoi(temp);
            filein >> soLuongDMS;
            filein.ignore();

            for (int i = 0; i < soLuongDMS; i++) {
                DanhMucSach* dms = new DanhMucSach();
                filein.getline(dms->vi_tri, sizeof(dms->vi_tri), '|');
                filein.getline(temp, sizeof(temp), '|');
                dms->ma_sach = atoi(temp);
                filein >> dms->trang_thai;
                filein.ignore();

                insertLastDMS(ds->list_dms, *dms);
            }
            InsertOrder_DS(t, ds);
        }
        filein.close();
    }
}
void initDS(LISTDAUSACH& ds){
	for(int i = 0; i < ds.soLuong; i++){
		ds.ArrDauSach[i] = new DAUSACH();
		ds.ArrDauSach[i]->trangThaiDeSapXep = 0;
	}
	
	ds.sortTheLoaiSach = NULL;
	ds.sortTenSach = NULL;
	ds.sortTheLoaiThenTenSach = NULL;
}
void GhiFileDS(LISTDAUSACH& ds, char* filename)
{
    ofstream fileout;
    fileout.open(filename, ios_base::out);
    if (!fileout.fail()) {
        for (int i = 0; i < ds.soLuong; i++) {
            int soLuongDMS = demSoLuongDanhMucSachCuaDauSach(ds.ArrDauSach[i]->list_dms);

            fileout << ds.ArrDauSach[i]->isbnCode << "|";
            fileout << ds.ArrDauSach[i]->tenSach << "|";
            fileout << ds.ArrDauSach[i]->tacGia << "|";
            fileout << ds.ArrDauSach[i]->namXuatBan << "|";
            fileout << ds.ArrDauSach[i]->theLoai << "|";
            fileout << ds.ArrDauSach[i]->soTrang << "|";
            fileout << soLuongDMS << endl;

            NodeDMSPtr p;
            // luu DMS
            for (p = ds.ArrDauSach[i]->list_dms; p != NULL; p = p->next) {
                fileout << p->info.vi_tri << "|";
                fileout << p->info.ma_sach << "|";
                fileout << p->info.trang_thai << endl;
            }
        }

        fileout.close();
    }
}
void Xuat_Danh_Sach_DS(LISTDAUSACH listDauSach)
{
    TextColor(0x0007);
    vekhung(3, 3, 20, 16 + 60 + 4 + 25 + 30);

    gotoXY(24, 2);
    cout << "DANH SACH DAU SACH";

    int page = 1, total_page = (listDauSach.soLuong % SODONGDG == 0) ? listDauSach.soLuong / SODONGDG : listDauSach.soLuong / SODONGDG + 1; //chia trang
    vekhung(3, 25, 1, 60);
    PutCharXY(4, 26, "<-: TRANG TRUOC | \t\t \t\t | TRANG SAU :->", Green);
    TextColor(White);
    gotoXY(29, 26);
    cout << "TRANG: ";
    TextColor(Yellow);
    cout << page << "/" << total_page;
    TextColor(White);
   	Xuat_nhieu_DS_theo_trang(listDauSach, page);
	
}

void Xuat_Danh_Sach_DS_Theo_The_Loai(LISTDAUSACH listDauSach)
{
    TextColor(0x0007);
    vekhung(3, 3, 20, 16 + 60 + 4 + 25 + 30);

    gotoXY(24, 2);
    cout << "DANH SACH DAU SACH THEO THE LOAI";

    int page = 1, total_page = (listDauSach.soLuong % SODONGDG == 0) ? listDauSach.soLuong / SODONGDG : listDauSach.soLuong / SODONGDG + 1; //chia trang
    vekhung(3, 25, 1, 60);
    PutCharXY(4, 26, "<-: TRANG TRUOC | \t\t \t\t | TRANG SAU :->", Green);
    TextColor(White);
    gotoXY(29, 26);
    cout << "TRANG: ";
    TextColor(Yellow);
    cout << page << "/" << total_page;
    TextColor(White);
    Xuat_nhieu_DS_The_Loai_theo_trang(listDauSach, page);
}

void Xuat_Danh_Sach_DS_Va_Ma_Sach(DAUSACH ds)
{
	Xoa_nhieu_dong_DG(100);
    TextColor(0x0007);
    
	TextColor(White);
	
	int y = 7;
	int x = 80;
	gotoXY(x, y );
    cout << "ISBN:";
    vekhung(x + 11, y - 1, 1, 30);

    gotoXY(x, y + 3);
    cout << "TEN SACH:";
    vekhung(x + 11, y + 2, 1, 30);

    gotoXY(x, y + 6);
    cout << "SO TRANG:";
    vekhung(x + 11, y + 5, 1, 30);

    gotoXY(x, y + 9);
    cout << "TAC GIA:";
    vekhung(x + 11, y + 8, 1, 30);

    gotoXY(x, y + 12);
    cout << "NXB:";
    vekhung(x + 11, y + 11, 1, 30);

    gotoXY(x, y + 15);
    cout << "THE LOAI:";
	vekhung(x + 11, y + 14, 1, 30);
	
	TextColor(Blue);
    gotoXY(x + 11 + 2,y - 1 + 1);
    cout<<ds.isbnCode;
    gotoXY(x + 11 + 2,y + 2+ 1);
    cout<<ds.tenSach;
    gotoXY(x + 11 + 2,y + 5+ 1);
    cout<<ds.soTrang;
    gotoXY(x + 11 + 2,y + 8+ 1);
    cout<<ds.tacGia;
    gotoXY(x + 11 + 2,y + 11+ 1);
    cout<<ds.namXuatBan;
    gotoXY(x + 11 + 2,y + 14+1);
    cout<<ds.theLoai;
    TextColor(Green);
    int key = 0;
    Xuat_Danh_Sach_DMS(ds.list_dms);
    do {
        key = getKey();
	} while (key != key_esc);
}

bool KiemTraDuLieuRongCuaMenuDauSach(int x, int y, string text[5])
{

    if (KiemTraChuoiRong(text[0])) {
        BaoLoi("CHUA NHAP ISBN!!", x, y);
        return false;
    }
    else if (text[0].length() < 8) {
        BaoLoi("VUI LONG NHAP ISBN 8 KY TU!!", x, y);
        return false;
    }
    else if (KiemTraChuoiRong(text[1])) {
        BaoLoi("CHUA NHAP TEN SACH!!", x, y + 3);
        return false;
    }
    else if (KiemTraChuoiRong(text[2])) {
        BaoLoi("CHUA NHAP TRANG!!", x, y + 6);
        return false;
    }
    else if (KiemTraChuoiRong(text[3])) {
        BaoLoi("CHUA NHAP TAC GIA!!", x, y + 6);
        return false;
    }
    else if (KiemTraChuoiRong(text[4])) {
        BaoLoi("CHUA NHAP NXB!!", x, y + 6);
        return false;
    }
    else if (KiemTraChuoiRong(text[5])) {
        BaoLoi("CHUA NHAP THE LOAI!!", x, y + 6);
        return false;
    }
    return true;
}
DAUSACH* NhapDauSachVaoKhung(LISTDAUSACH& listDauSach, int x, int y, DAUSACH* ds)
{
    ShowCur(true);
    TextColor(White);

    gotoXY(x, y);
    cout << "ISBN:";
    vekhung(x + 11, y - 1, 1, 30);

    gotoXY(x, y + 3);
    cout << "TEN SACH:";
    vekhung(x + 11, y + 2, 1, 30);

    gotoXY(x, y + 6);
    cout << "SO TRANG:";
    vekhung(x + 11, y + 5, 1, 30);

    gotoXY(x, y + 9);
    cout << "TAC GIA:";
    vekhung(x + 11, y + 8, 1, 30);

    gotoXY(x, y + 12);
    cout << "NXB:";
    vekhung(x + 11, y + 11, 1, 30);

    gotoXY(x, y + 15);
    cout << "THE LOAI:";
    vekhung(x + 11, y + 14, 1, 30);
    int key = 0, dx = x + 12, dy = y;

    TextColor(White);
    int page = 1, total_page = (listDauSach.soLuong % SODONGDG == 0) ? listDauSach.soLuong / SODONGDG : listDauSach.soLuong / SODONGDG + 1; //chia trang
    int trangthai = 0;
    string text[6];
    if (ds == NULL) {
        text[0] = "";
        text[1] = "";
        text[2] = "";
        text[3] = "";
        text[4] = "";
        text[5] = "";
    }
    else {
        //    	text[0] += dg->ho;
        //    	gotoXY(dx,dy);
        //        cout<<text[0];
        //
        //    	text[1] += dg->ten;
        //    	gotoXY(dx,dy+3);
        //        cout<<text[1];
        //
        //    	text[2] += dg->gioiTinh;
        //    	gotoXY(dx,dy+6);
        //        cout<<text[2];
    }
    gotoXY(dx, dy);
    do {
        key = getKey();
        switch (key) {
        case key_enter: {
            bool kt = KiemTraDuLieuRongCuaMenuDauSach(x + 11 + 35, y, text);
            if (kt) {
                DAUSACH* temp = new DAUSACH();

                ChuanHoaString(text[0]).copy(temp->isbnCode, 8);
                ChuanHoaString(text[4]).copy(temp->namXuatBan, 5);
                ChuanHoaString(text[3]).copy(temp->tacGia, 30);
                ChuanHoaString(text[1]).copy(temp->tenSach, 30);
                ChuanHoaString(text[5]).copy(temp->theLoai, 30);

                temp->soTrang = atoi(text[2].c_str());
                return temp;
            }
            break;
        }
        case key_back: {
            if (text[trangthai].length() > 0) {
                text[trangthai].erase(text[trangthai].length() - 1, 1);
                cout << "\b \b";
            }
            break;
        }

        case key_tab: {

            trangthai = ++trangthai % 6; //xoay vong
            dy = y + trangthai * 3;
            gotoXY(dx, dy);
            cout << text[trangthai];

            break;
        }
            {
            case key_left:
                (page > 1) ? page-- : page = total_page;
                Xuat_nhieu_DS_theo_trang(listDauSach, page);
                TextColor(White);
                gotoXY(29, 26);
                cout << "TRANG: ";
                TextColor(Yellow);
                cout << page << "/" << total_page;
                TextColor(White);
                break;
            case key_right:
                (page < total_page) ? page++ : page = 1;
                Xuat_nhieu_DS_theo_trang(listDauSach, page);
                TextColor(White);
                gotoXY(29, 26);
                cout << "TRANG: ";
                TextColor(Yellow);
                cout << page << "/" << total_page;
                TextColor(White);
                break;
            }
        default: {
            if (trangthai == 0) {
                if (((key > 47 && key < 58)) && text[trangthai].length() < 8) {
                    gotoXY(dx, dy);
                    text[trangthai] += toupper(char(key));
                    cout << text[trangthai];
                }
            }
            else if (trangthai == 1) {
                if (((key > 47 && key < 58) || (key > 64 && key < 91) || (key > 96 && key < 123) || key == key_space) && text[trangthai].length() < 30) {
                    gotoXY(dx, dy);
                    text[trangthai] += toupper(char(key));
                    cout << text[trangthai];
                }
            }
            else if (trangthai == 2) {
                if (((key > 47 && key < 58)) && text[trangthai].length() < 4) {
                    gotoXY(dx, dy);
                    text[trangthai] += toupper(char(key));
                    cout << text[trangthai];
                }
            }
            else if (trangthai == 3) {
                if (((key > 47 && key < 58) || (key > 64 && key < 91) || (key > 96 && key < 123) || key == key_space) && text[trangthai].length() < 30) {
                    gotoXY(dx, dy);
                    text[trangthai] += toupper(char(key));
                    cout << text[trangthai];
                }
            }
            else if (trangthai == 4) {
                if (((key > 47 && key < 58) || (key > 64 && key < 91)) && text[trangthai].length() < 5) {
                    gotoXY(dx, dy);
                    text[trangthai] += toupper(char(key));
                    cout << text[trangthai];
                }
            }
            else {
                if (((key > 47 && key < 58) || (key > 64 && key < 91) || (key > 96 && key < 123) || key == key_space) && text[trangthai].length() < 30) {
                    gotoXY(dx, dy);
                    text[trangthai] += toupper(char(key));
                    cout << text[trangthai];
                }
            }
            break;
        }
        }
    } while (key != key_esc);
    ShowCur(false);
    return NULL;
}
void resetTrangThai(LISTDAUSACH& ds) {
	for (int i = 0; i < ds.soLuong ; i++) {
		ds.ArrDauSach[i]->trangThaiDeSapXep = 0;
	}
}
void sortTheLoaiSach(LISTDAUSACH& ds) {
	int index = 0;
	int oldIndex = -1;
	char * max_str_the_loai_sach, c = SPACE;
	for (int j = 0; j < ds.soLuong + 1; j++) {
		max_str_the_loai_sach = &c;
		for (int i = 0; i < ds.soLuong; i++) {
			if (ds.ArrDauSach[i]->trangThaiDeSapXep == 0) {
				if (strcmp(max_str_the_loai_sach, ds.ArrDauSach[i]->theLoai) == -1) {
					max_str_the_loai_sach = ds.ArrDauSach[i]->theLoai; 
					index = i;
				}
			}
		}//thoat loop tim duoc min_str_the_loai;
		if(oldIndex == -1){
			ds.ArrDauSach[index]->nextTheLoai = NULL;
			ds.sortTheLoaiSach = ds.ArrDauSach[index];
		}
		else if(index != oldIndex){
			ds.ArrDauSach[index]->nextTheLoai = ds.ArrDauSach[oldIndex];
			ds.sortTheLoaiSach = ds.ArrDauSach[index];
		}
		
		ds.ArrDauSach[index]->trangThaiDeSapXep = 1;
		oldIndex = index;
	}
	resetTrangThai(ds);
}

void sortTenSach(LISTDAUSACH& ds) {
	int index = 0;
	int oldIndex = -1;
	char * max_str_ten_sach_sach, c = SPACE;
	for (int j = 0; j < ds.soLuong + 1; j++) {
		max_str_ten_sach_sach = &c;
		for (int i = 0; i < ds.soLuong; i++) {
			if (ds.ArrDauSach[i]->trangThaiDeSapXep == 0) {
				if (strcmp(max_str_ten_sach_sach, ds.ArrDauSach[i]->tenSach) == -1) {
					max_str_ten_sach_sach = ds.ArrDauSach[i]->tenSach; 
					index = i;
				}
			}
		}//thoat loop tim duoc min_str_the_loai;
		if(oldIndex == -1){
			ds.ArrDauSach[index]->nextTenSach = NULL;
			ds.sortTenSach = ds.ArrDauSach[index];
		}
		else if(index != oldIndex){
			ds.ArrDauSach[index]->nextTenSach = ds.ArrDauSach[oldIndex];
			ds.sortTenSach = ds.ArrDauSach[index];
		}
		
		ds.ArrDauSach[index]->trangThaiDeSapXep = 1;
		oldIndex = index;
	}
	resetTrangThai(ds);
}
void sortTheLoaiSachAndTenSach(LISTDAUSACH& ds) {
	sortTenSach(ds);
	sortTheLoaiSach(ds);
	
	DAUSACH *pTenSach, *pTheLoai; 
	int index = 0;
	char *a, *b;
	pTheLoai = ds.sortTheLoaiSach;
	while (pTheLoai != NULL) {
		
		pTenSach = ds.sortTenSach;
		
		while (pTenSach != NULL) {
			
			if (strcmp(pTheLoai->theLoai, pTenSach->theLoai) == 0 && pTenSach->trangThaiDeSapXep == 0) {
				
				pTenSach->nextTheLoaiThenTenSach = ds.sortTheLoaiThenTenSach;
				ds.sortTheLoaiThenTenSach = pTenSach;
				pTenSach->trangThaiDeSapXep = 1;
			}
			pTenSach = pTenSach->nextTenSach;
		}
		pTheLoai = pTheLoai->nextTheLoai;
	}
	resetTrangThai(ds);
	
	DAUSACH *sort;
	for (int i = 0; i < ds.soLuong; i++) {
		sort = ds.sortTheLoaiThenTenSach;
		while (sort->nextTheLoaiThenTenSach != NULL && sort->nextTheLoaiThenTenSach->trangThaiDeSapXep == 0) {
			sort = sort->nextTheLoaiThenTenSach;
		}
		ds.ArrDauSach[i] = sort;
		sort->trangThaiDeSapXep = 1;
	}
}

void QuanLySach(LISTDAUSACH listDauSach)
{
    int soluongmenu = 4;
    char a[4][30] = {
        "THEM DAU SACH",
        "THEM SACH",
        "IN DANH SACH DAU SACH",
        "TIM THONG TIN SACH THEO TEN",
    };
    int m;
    do {
        system("cls");
        PutCharXY(55, 5, "========QUAN LY DAU SACH=======", Blue);
        TextColor(Yellow);
        TextColor(Green);
        vekhung(54, 25, 1, 30);
        PutCharXY(56, 26, "ESC: THOAT | ENTER: XAC NHAN", Green);
        m = menu(55, 10, a, soluongmenu);

        switch (m) {
        case 0: {
            system("cls");
            int n = 0;
            PutCharXY(16 + 60 + 4 + 25 + 30 + 10, 2, "===========THEM DAU SACH============", Blue);
            TextColor(Green);
            vekhung(69, 25, 1, 54);
            PutCharXY(70, 26, "ESC: THOAT | TAB: DOI VI TRI CON TRO | ENTER: XAC NHAN", Green);
            do {
                TextColor(Yellow);
                gotoXY(4, 2);
                Xuat_Danh_Sach_DS(listDauSach);
                DAUSACH* ds = NhapDauSachVaoKhung(listDauSach, 16 + 60 + 4 + 25 + 30 + 10, 7, NULL);
                if (ds != NULL) {

                    n = InsertOrder_DS(listDauSach, ds);

                    if (n == 0)
                        BaoLoi("THEM DAU SACH THAT BAI, VUI LONG KIEM TRA LAI!!", 82, 4);
                    if (n == 1) {
                        ThanhCong("THEM DAU SACH THANH CONG!!", 82, 4);
                        GhiFileDS(listDauSach, "DauSach.txt");
                    }
                }
                else
                    break;
            } while (1);
            break;
        }
        case 1: {
            do {
                system("cls");
                int n = 0;
                PutCharXY(82, 2, "===========THEM SACH============", Blue);
                TextColor(Green);
                vekhung(68, 25, 1, 54);
                PutCharXY(70, 26, "ESC: THOAT | TAB: DOI VI TRI CON TRO | ENTER: XAC NHAN", Green);
                TextColor(Yellow);
                gotoXY(4, 2);
                Xuat_Danh_Sach_DS(listDauSach);
                int index = -1;
                DAUSACH* ds = NhapMaISBNVaoKhung(listDauSach, 16 + 60 + 4 + 25 + 30 + 10, 7, index);
                if (ds != NULL) {
                    Xuat_Danh_Sach_DMS(listDauSach.ArrDauSach[index]->list_dms);
                    DanhMucSach* dms = NhapDanhMucSachVaoKhung(listDauSach, 80, 7);
                    if (dms != NULL) {
                        insertLastDMS(listDauSach.ArrDauSach[index]->list_dms, *dms);

                        ThanhCong("THEM DANH MUC SACH THANH CONG!!", 82, 4);
                        GhiFileDS(listDauSach, "DauSach.txt");
                    }
                }
                else
                    break;

            } while (1);

            break;
        }

        case 2: {
            do {
                system("cls");
                int n = 0;
                PutCharXY(82, 2, "===========IN DANH SACH DAU SACH============", Blue);
                TextColor(Green);
                vekhung(68, 25, 1, 54);
                PutCharXY(70, 26, "ESC: THOAT | TAB: DOI VI TRI CON TRO | ENTER: XAC NHAN", Green);
                TextColor(Yellow);
                gotoXY(4, 2);
                int key = 0;
                sortTheLoaiSachAndTenSach(listDauSach);
                Xuat_Danh_Sach_DS_Theo_The_Loai(listDauSach);
                do {
                	int page = 1, total_page = (listDauSach.soLuong % SODONGDG == 0) ? listDauSach.soLuong / SODONGDG : listDauSach.soLuong / SODONGDG + 1; //chia trang
			        key = getKey();
			        switch (key) {
			
			            case key_left:
			                (page > 1) ? page-- : page = total_page;
			                Xuat_nhieu_DS_The_Loai_theo_trang(listDauSach, page);
			                TextColor(White);
			                gotoXY(29, 26);
			                cout << "TRANG: ";
			                TextColor(Yellow);
			                cout << page << "/" << total_page;
			                TextColor(White);
			                break;
			            case key_right:
			                (page < total_page) ? page++ : page = 1;
			                Xuat_nhieu_DS_The_Loai_theo_trang(listDauSach, page);
			                TextColor(White);
			                gotoXY(29, 26);
			                cout << "TRANG: ";
			                TextColor(Yellow);
			                cout << page << "/" << total_page;
			                TextColor(White);
			                break;
			        default: {
			            break;
			        }
			        }
			    } while (key != key_esc);

            } while (1);

            break;
        }
        case 3: {
            do {
                system("cls");
                int n = 0;
                PutCharXY(42, 2, "===========TIM THONG TIN SACH THEO TEN============", Blue);
                TextColor(Yellow);
                gotoXY(4, 2);
                int index = -1;
                DAUSACH* ds = NhapTenSachVaoKhung(32 + 10, 7, index,listDauSach);
                if (ds != NULL) {
                    Xuat_Danh_Sach_DS_Va_Ma_Sach(*ds);
                }
                else
                    break;

            } while (1);

            break;
        }
        }
    } while (m != -1);
}
#endif
