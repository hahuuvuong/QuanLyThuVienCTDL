#ifndef MUONTRA_H
#define MUONTRA_H

MuonSachPTR newNodeMuonSach(void) {
	MuonSachPTR p;
	p = new nodeMS;
	p->next = NULL;
	return p;
}

int isEmptyMS(MuonSachPTR first) {
	return(first == NULL ? true : false);
}
void insertFirstMS(MuonSachPTR &first, MuonSach x) {
	MuonSachPTR p;
	p = newNodeMuonSach();
	p->info = x;
	p->next = first;
	first = p;
}
void insertLastMS(MuonSachPTR &first, MuonSach x) {
	MuonSachPTR p, q;
	q = newNodeMuonSach();
	p = first;
	if (isEmptyMS(first)) {
		insertFirstMS(first, x);
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

void hienDSMuonTraCuaDocGia(DG dg, LISTDAUSACH listDauSach){
    system("cls");
	
    TextColor(0x0007);
    vekhung(3, 3, 20, 16 + 60 + 4 + 25 + 30);

    gotoXY(24, 2);
    cout << "DANH SACH DAU SACH";

   	Xuat_nhieu_DS_theo_DG(listDauSach, dg);
}
DG *TimVaHienDSMuonTra(NODE_DG_PTR tree,LISTDAUSACH listDauSach)
{
	system("cls");
    int n=0;
    DG *dg=NULL;
    PutCharXY(82,2,"=====NHAP MA DOC GIA ======",Blue);
    TextColor(Green);
    vekhung(69,25,1,54);
    PutCharXY(70,26,"ESC: THOAT | TAB: DOI VI TRI CON TRO | ENTER: XAC NHAN",Green);
    do
    	{
        	TextColor(Yellow);
            gotoXY(4,2);
            cout<<"SL DOC GIA: "<<SLMaDG(tree)<<"/"<<MAXLISTMADG;
            Xuat_Danh_Sach_DG(tree);
            if(SLMaDG(tree)==0)
            {
                PutCharXY(82,4,"DANH SACH DOC GIA TRONG, VUI LONG THEM DOC GIA!!",Red);
                _getch();
                break;
            }
            dg = NhapMaDGVaoKhung(tree,70,7);
            if(dg!=NULL)
            {
                dg = TimDGTheoID(tree,dg);
                if(dg==NULL)
                    BaoLoi("MA DOC GIA KHONG TON TAI, VUI LONG KIEM TRA LAI!!",82,4);
                    
                else{
                	hienDSMuonTraCuaDocGia(*dg,listDauSach);
                	return dg;
                }
            }
            else
                break;
   	}
    while(1);
}
void buildNodeMuonSach()
void QuanLyMuonTra(NODE_DG_PTR &tree,LISTDAUSACH listDauSach)
{
	DG* dg = TimVaHienDSMuonTra(tree, listDauSach);
    int soluongmenu = 2;
    char a[2][30] = {
        "MUON SACH",
        "TRA SACH",
    };
    int m;
    do {
        m = menu(155, 10, a, soluongmenu);

        switch (m) {
        case 0: {
            do {
                system("cls");
                int n = 0;
                PutCharXY(82, 2, "===========MUON SACH============", Blue);
                TextColor(Green);
                vekhung(68, 25, 1, 54);
                PutCharXY(70, 26, "ESC: THOAT | TAB: DOI VI TRI CON TRO | ENTER: XAC NHAN", Green);
                TextColor(Yellow);
                gotoXY(4, 2);
                Xuat_Danh_Sach_DS(listDauSach);
                int index = -1;
                DAUSACH* ds = NhapMaISBNVaoKhung(listDauSach, 16 + 60 + 4 + 25 + 30 + 10, 7, index);
                if (ds != NULL) {
                    system("cls");
                    Xuat_Danh_Sach_DMS(listDauSach.ArrDauSach[index]->list_dms);
                    string maSach = NhapMaSachVaoKhung(listDauSach.ArrDauSach[index]->list_dms, 80, 7);  
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
                PutCharXY(82, 2, "===========TRA SACH============", Blue);
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
        }
    } while (m != -1);
}

#endif
