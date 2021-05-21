 #ifndef THEDOCGIA_H
 #define THEDOCGIA_H
#include "MuonSach.h"
#include "CauTruc.h"
#define MAXLISTMADG 2000
#define STACKSIZE 500



void initualizeTreeDG(NODE_DG_PTR &NODE_DG_PTR){
	NODE_DG_PTR = NULL;
}

int Insert_nodeDG(NODE_DG_PTR &p, DG info)
{
    if(p == NULL)  
    {
        p = new nodeDG;
        p->infoDG = info;
        p->pLeft = NULL;
        p->pRight = NULL;
        return 1;
    }
    else
    {
        if(p->infoDG.maThe>info.maThe)
            Insert_nodeDG(p->pLeft, info);
        else if(p->infoDG.maThe<info.maThe)
            Insert_nodeDG(p->pRight, info);
    }
}
int isTreeEmpty(NODE_DG_PTR tree){
	return tree == NULL ? true : false;	
}

NODE_DG_PTR rm;
void remove_case_3 (NODE_DG_PTR &r )
{
    if (r->pLeft != NULL)
        remove_case_3 (r->pLeft);
    //den day r la nut cuc trai cua cay con ben phai co nut goc la rp}
    else
    {
    	
        rm->infoDG.maThe = r->infoDG.maThe;

        rm->infoDG =r->infoDG;	//  de lat nua free(rp)
        rm = r;
        r = rm->pRight;
    }
}

int Xoa_DG (  NODE_DG_PTR &p,DG x )
{
    if (p == NULL)
        return 0; //printf ("Khong tim thay");
    else if (x.maThe < p->infoDG.maThe)
        Xoa_DG ( p->pLeft,x);
    else if (x.maThe > p->infoDG.maThe)
        Xoa_DG (p->pRight,x);
    else    	// p->key = x
    {
        rm = p;
        if (rm->pRight == NULL)
            p = rm->pLeft;   // p là nút lá hoac la nut chi co cay con ben trai
        else if (rm->pLeft == NULL)
            p = rm->pRight;  // p là nut co cay con ben phai
        else
            remove_case_3 (rm->pRight);
        delete rm;
        return 1;
    }
}

bool KiemTraDuLieuRongCuaMenuDocGia(int x,int y,string text[2])
{

    if(text[0].length()==0)
    {
        BaoLoi("CHUA NHAP HO!!", x,y);
        return false;
    }
    else if(KiemTraChuoiRong(text[1]))
    {
        BaoLoi("CHUA NHAP TEN!!", x,y+3);
        return false;
    }
    else if(KiemTraChuoiRong(text[2])){
    	BaoLoi("CHUA NHAP GIOI TINH!!", x,y+6);
        return false;
    }
    return true;
}

void DuyetFileDG(NODE_DG_PTR &t, ofstream &fileout)
{
    if(t!=NULL)
    {
        DuyetFileDG(t->pLeft, fileout);
        fileout << t->infoDG.maThe << "|";
            fileout << t->infoDG.ho << "|";
            fileout << t->infoDG.ten << "|";
            fileout << t->infoDG.gioiTinh << "|";
            fileout << t->infoDG.trangThai << endl;
        DuyetFileDG(t->pRight, fileout);
    }
}

void DocFileMaDG(int t[])
{
    ifstream filein;
    filein.open("MADOCGIA.txt", ios_base::in);
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

int DocFileSoLuongDG()
{
    ifstream filein;
    filein.open("SOLUONGDOCGIA.txt", ios_base::in);
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
            return temp;

        }
        filein.close();
    }
    return 0;
}

void ghiFileSoLuongDocGia(int soLuong)
{
    ofstream fileout;
    fileout.open("SOLUONGDOCGIA.txt", ios_base::out);
    if(!fileout.fail())
    {
        fileout << soLuong<<endl;

        fileout.close();
    }
}

int SLMaDG(NODE_DG_PTR tree){
	NODE_DG_PTR Stack[STACKSIZE];
	int sp = -1;
	NODE_DG_PTR p = tree;
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

int random_MaDG(NODE_DG_PTR tree)
{
	int arr[MAXLISTMADG];
	DocFileMaDG(arr);
	int soLuongDocGia = DocFileSoLuongDG();
	int id = arr[soLuongDocGia];
	return id;
}

void Swap(int* number_1, int* number_2)
{
	int temp = *number_1;
	*number_1 = *number_2;
	*number_2 = temp;
}
void ShuffleArray(int* arr, int n)
{
	srand(time(NULL));

	int minPosition;
	int maxPosition = n - 1;
	int swapPosition;

	int i = 0;
	while (i < n - 1)
	{
		minPosition = i + 1;
		swapPosition = rand() % (maxPosition - minPosition + 1) + minPosition;

		Swap(&arr[i], &arr[swapPosition]);
		i++;
	}
}

void generateFileMaDocGia()
{
    ofstream fileout;
    fileout.open("MADOCGIA.txt", ios_base::out);
    int maGD[MAXLISTMADG];
    
    for (int i=0; i < MAXLISTMADG; i++)
    {
    	maGD[i] = i+1;
    }
    ShuffleArray(maGD,MAXLISTMADG);
    if(!fileout.fail())
    {
        for (int i=0; i < MAXLISTMADG; i++)
        {
        	fileout << maGD[i]<<endl;
        }

        fileout.close();
    }
}

void GhiFileDG(NODE_DG_PTR &t,char *filename)
{
    ofstream fileout;
    fileout.open(filename, ios_base::out);
    if(!fileout.fail())
    {
        DuyetFileDG(t, fileout);
        fileout.close();
    }
}

void Xoa_1dong_DG(int y,int width)
{
    int dem=0;
    gotoXY(4,y);while(dem<width){cout<<" "; dem++;}
}
void Xoa_nhieu_dong_DG(int width)
{
    for (int i = 0; i <SODONGDG; i++)
    {
        Xoa_1dong_DG(i+6,width);
    }

}
void Xuat_1DG(DG dg,int &y)
{
    Xoa_1dong_DG(y,62);
    TextColor(Blue);
    gotoXY(4,y);
    cout<<dg.maThe;
    gotoXY(10,y);
    cout<<"\t"<<dg.ho
        <<"\t\t"<<dg.ten
        <<"\t\t"<<((strcmp(dg.gioiTinh,"0")==0)?"NAM":"NU")
        <<"\t\t"<<dg.trangThai;
    TextColor(Green);
    y+=1;
}

void Xuat_nhieu_DG_theo_trang(NODE_DG_PTR tree, int index)
{
    int y=5;
    Xoa_nhieu_dong_DG(62);
    TextColor(Blue);
    gotoXY(4,4);
    cout<<"MA THE "
        <<"\tHO "
        <<"\t\tTEN"
        <<"\t\tGIOI TINH"
        <<"\tTT";
    TextColor(Green);
    index--;
    int dem=0,j=0;
    
    NODE_DG_PTR Stack[STACKSIZE];
	int sp = -1;
	NODE_DG_PTR p = tree;
	while(p!=NULL){
		
		Stack[++sp] = p;
		p = p->pLeft;
		if(sp!=-1)
		{
			p = Stack[sp--];
			
			if(dem==SLMaDG(tree)) break;
		
        	if(dem>= SODONGDG*( index) && dem< SODONGDG*(index)+SODONGDG)
            Xuat_1DG(p->infoDG,y);
        	dem++;
			p = p->pRight;
		}
		else break;
	}

    TextColor(White);
}

void Xuat_nhieu_DG_theo_trang_Theo_Ten(DG *dg, int index, int soLuong)
{
    int y=5;
    Xoa_nhieu_dong_DG(62);
    TextColor(Blue);
    gotoXY(4,4);
    cout<<"MA THE "
        <<"\tHO "
        <<"\t\tTEN"
        <<"\t\tGIOI TINH"
        <<"\tTT";
    TextColor(Green);
    index--;
    int dem=0,j=0;
    
    for(int i = 0; i< soLuong; i++){
			if(dem==soLuong) break;
		
        	if(dem>= SODONGDG*( index) && dem< SODONGDG*(index)+SODONGDG)
            Xuat_1DG(dg[i],y);
        	dem++;
    }

    TextColor(White);
}

DG *NhapDocGiaVaoKhung(NODE_DG_PTR &p,int x,int y, DG* dg)
{
    ShowCur(true);
    TextColor(White);
    gotoXY(x,y);
    cout<<"HO:";
    vekhung(x+11,y-1,1,30);
    gotoXY(x,y+3);
    cout<<"TEN:";
    vekhung(x+11,y+2,1,30);
    gotoXY(x,y+6);
    cout<<"GIOI TINH:";
    vekhung(x+11,y+5,1,30);
    PutCharXY(x+11+19,y+8,"(0:NAM,1:NU)",Yellow);
    
    int key=0, dx = x +12,dy = y;

    TextColor(White);
	int page=1,total_page = (SLMaDG(p)%SODONGDG==0) ? SLMaDG(p) / SODONGDG : SLMaDG(p)/SODONGDG+1;//chia trang
    int trangthai = 0;
    string text[3];
    if(dg == NULL){
    	text[0] = "";
    	text[1] = "";
    	text[2] = "";
    }
    else{
    	text[0] += dg->ho;
    	gotoXY(dx,dy);
        cout<<text[0];

    	text[1] += dg->ten;
    	gotoXY(dx,dy+3);
        cout<<text[1];
        
    	text[2] += dg->gioiTinh;
    	gotoXY(dx,dy+6);
        cout<<text[2];
	}
    gotoXY(dx,dy);
    do
    {
        key = getKey();
        switch(key)
        {
        case key_enter:
        {
            bool kt = KiemTraDuLieuRongCuaMenuDocGia(x+11+35,y,text);
            if(kt)
            {
                DG *temp = new DG();
                ChuanHoaString(text[0]).copy(temp->ho,30);
                ChuanHoaString(text[1]).copy(temp->ten,15);
                text[2].copy(temp->gioiTinh,2);
                temp->trangThai = 1;// trang thai the duoc muon
                temp->maThe = (dg == NULL)?random_MaDG(p): dg->maThe;
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

            trangthai = ++trangthai%3;//xoay vong
            dy = y+trangthai*3;
            gotoXY(dx,dy);
            cout<<text[trangthai];

            break;
        }
        {
            case key_left:
                (page > 1) ? page-- : page = total_page;
                Xuat_nhieu_DG_theo_trang(p,page);
                TextColor(White);
                gotoXY(29,26);
                cout<<"TRANG: ";
                TextColor(Yellow);
                cout<<page<<"/"<<total_page;
                TextColor(White);
                break;
            case key_right:
                (page <  total_page) ? page++ : page = 1;
                Xuat_nhieu_DG_theo_trang(p,page);
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
                if((((key>47&&key<58)||(key>64&&key<91)||(key>96&&key<123))||key==key_space) &&text[trangthai].length()<30)
                {
                    gotoXY(dx,dy);
                    text[trangthai]+=toupper(char(key));
                    cout<<text[trangthai];
                }

            }
            else if(trangthai==1) 
            {
                if(((key>47&&key<58)||(key>64&&key<91)||(key>96&&key<123))&&text[trangthai].length()<15)
                {
                    gotoXY(dx,dy);
                    text[trangthai]+=toupper(char(key));
                    cout<<text[trangthai];
                }
            }
			else{
            	if((key==48||key==49) &&text[trangthai].length()<1)
                {
                    gotoXY(dx,dy);
                    text[trangthai]=toupper(char(key));
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
void listenToEscapeKeyDocGia(NODE_DG_PTR &p)
{
	int key=0;
	int page=1,total_page = (SLMaDG(p)%SODONGDG==0) ? SLMaDG(p) / SODONGDG : SLMaDG(p)/SODONGDG+1;//chia trang
    do
    {
        key = getKey();
        switch(key)
        {
        {
            case key_left:
                (page > 1) ? page-- : page = total_page;
                Xuat_nhieu_DG_theo_trang(p,page);
                TextColor(White);
                gotoXY(29,26);
                cout<<"TRANG: ";
                TextColor(Yellow);
                cout<<page<<"/"<<total_page;
                TextColor(White);
                break;
            case key_right:
                (page <  total_page) ? page++ : page = 1;
                Xuat_nhieu_DG_theo_trang(p,page);
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
            break;
        }
        }
    }
    while(key!= key_esc);
    ShowCur(false);

}

void Xuat_Danh_Sach_DG(NODE_DG_PTR tree)
{

    TextColor(0x0007);
    vekhung(3,3,23,62);
    gotoXY(24,2);
    cout<<"DANH SACH DOC GIA";

    int page=1,total_page = (SLMaDG(tree)%SODONGDG==0) ? SLMaDG(tree) / SODONGDG : SLMaDG(tree)/SODONGDG+1;//chia trang
    vekhung(3,25,1,60);
    PutCharXY(4,26,"<-: TRANG TRUOC | \t\t \t\t | TRANG SAU :->",Green);
    TextColor(White);
    gotoXY(29,26);
    cout<<"TRANG: ";
    TextColor(Yellow);
    cout<<page<<"/"<<total_page;
    TextColor(White);
    Xuat_nhieu_DG_theo_trang(tree,page);
}

void Xuat_Danh_Sach_DG_Theo_Ten(DG *dg,int soLuong)
{

    TextColor(0x0007);
    vekhung(3,3,23,62);
    gotoXY(24,2);
    cout<<"DANH SACH DOC GIA";

    int page=1,total_page = (soLuong%SODONGDG==0) ? soLuong / SODONGDG : soLuong/SODONGDG+1;//chia trang
    vekhung(3,25,1,60);
    PutCharXY(4,26,"<-: TRANG TRUOC | \t\t \t\t | TRANG SAU :->",Green);
    TextColor(White);
    gotoXY(29,26);
    cout<<"TRANG: ";
    TextColor(Yellow);
    cout<<page<<"/"<<total_page;
    TextColor(White);
    Xuat_nhieu_DG_theo_trang_Theo_Ten(dg,page,soLuong);
}

////////////////////////////////////////doc & ghi file
void DocFileDG(NODE_DG_PTR &tree, char* filename)
{

    ifstream filein;
    DG dg;
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
			char temp[5];
            filein.getline(temp,sizeof(temp),'|');
            dg.maThe = atoi(temp);
            filein.getline(dg.ho,sizeof(dg.ho),'|');
            filein.getline(dg.ten,sizeof(dg.ten),'|');
            filein.getline(dg.gioiTinh,sizeof(dg.gioiTinh),'|');
            filein>>dg.trangThai;
            filein.ignore();

            Insert_nodeDG(tree,dg);
        }
        filein.close();
    }
}

DG *NhapMaDGVaoKhung(NODE_DG_PTR tree,int x,int y)
{
    ShowCur(true);
    TextColor(0x0007);
    //system("cls");
    gotoXY(x,y);
    cout<<"MA DOC GIA:";
    vekhung(x+11,y-1,1,30);
    int key=0, dx = x +12,dy = y;

    int page=1,total_page = (SLMaDG(tree)%SODONGDG==0) ? SLMaDG(tree) / SODONGDG : SLMaDG(tree)/SODONGDG+1;//chia trang

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
                BaoLoi("CHUA NHAP MA DOC GIA!!",x+11+35,y);
            }
            else
            {
                DG *dg = new DG();
                dg->maThe = atoi(text[0].c_str());
                return dg;
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
            Xuat_nhieu_DG_theo_trang(tree,page);
            TextColor(White);
            gotoXY(29,26);
            cout<<"TRANG: ";
            TextColor(Yellow);
            cout<<page<<"/"<<total_page;
            TextColor(White);
            break;
        case key_right:
            (page <  total_page) ? page++ : page = 1;
            Xuat_nhieu_DG_theo_trang(tree,page);
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

DG *TimDGTheoID(NODE_DG_PTR tree,DG* dg)
{
    NODE_DG_PTR p = NULL;
    p = tree;
    while( p!= NULL && p->infoDG.maThe!= dg->maThe)
    	if(dg->maThe < p->infoDG.maThe)
    		p = p->pLeft;
    	else
    	 	p = p->pRight;
    return &(p->infoDG);
}

int Sua_DG(NODE_DG_PTR tree, DG &x)
{
    NODE_DG_PTR Stack[STACKSIZE];
    int sp= -1;	// Khoi tao Stack rong

    while (tree !=NULL )
    {
        if(tree->infoDG.maThe == x.maThe)
        {
            tree->infoDG=x;
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
void themMangDocGia(NODE_DG_PTR tree, DG* dg, int &sl) {
	if (tree != NULL) {
		dg[sl] = tree->infoDG; sl++;
		themMangDocGia(tree->pLeft, dg, sl);
		themMangDocGia(tree->pRight, dg, sl);
	}
}

void QuanLyDocGia(NODE_DG_PTR &tree)
{
    int soluongmenu = 5;
    char a[5][30] =
    {
        "THEM DOC GIA",
        "XOA DOC GIA",
        "SUA DOC GIA",
        "XUAT DOC GIA THEO HO TEN",
        "XUAT DOC GIA THEO MA THE",
    };
    int m;
    do
    {
        system("cls");
        PutCharXY(55,5,"========QUAN LY DOC GIA=======",Blue);
        TextColor(Yellow);
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
            PutCharXY(82,2,"===========THEM DOC GIA============",Blue);
            TextColor(Green);
            vekhung(69,25,1,54);
            PutCharXY(70,26,"ESC: THOAT | TAB: DOI VI TRI CON TRO | ENTER: XAC NHAN",Green);
            do
            {
                TextColor(Yellow);
                gotoXY(4,2);
                Xuat_Danh_Sach_DG(tree);
                int x = SLMaDG(tree);
                DG* dg = NhapDocGiaVaoKhung(tree,70,7,NULL);
                if(dg != NULL)
                {
                    n = Insert_nodeDG(tree, *dg);
                    if(n==0)
                        BaoLoi("THEM DOC GIA THAT BAI, VUI LONG KIEM TRA LAI!!",82,4);
                    if(n==1)
                    {
                        ThanhCong("THEM DOC GIA THANH CONG!!",82,4);
                        GhiFileDG(tree,"TheDocGia.txt");
                        int soLuongDocGia = DocFileSoLuongDG();
                        ghiFileSoLuongDocGia(soLuongDocGia + 1);
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
            DG *dg=NULL;
            PutCharXY(82,2,"=====XOA DOC GIA THEO MA ======",Blue);
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
                        cout<<"BAN CO CHAC CHAN MUON XOA DOC GIA?";
                        m = menu_xoa(82,15,a,soluachon);
                        switch (m)
                        {
                        case 0:
                        {
                            {
                                    n = Xoa_DG(tree,*dg);
                                    if(n==1)
                                    {
                                        PutCharXY(82,13,"                                  ",White);
                                        PutCharXY(82,15,"  ",White);
                                        PutCharXY(82,16,"     ",White);
                                        TextColor(Yellow);
                                        gotoXY(4,2);
                                       	cout<<"SL DOC GIA: "<<SLMaDG(tree)<<"/"<<MAXLISTMADG;
                                        Xuat_Danh_Sach_DG(tree);
                                        ThanhCong("XOA DOC GIA THANH CONG!!",82,4);
                                        GhiFileDG(tree,"TheDocGia.txt");
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
            DG* tempL=NULL;
            PutCharXY(82,2,"=====SUA DOC GIA THEO MA ======",Blue);
            TextColor(Green);
            vekhung(69,25,1,82);
            PutCharXY(70,26,"ESC: THOAT | TAB: DOI VI TRI CON TRO | ENTER: XAC NHAN | `: TU DONG DIEN TH0NG TIN",Green);
            do
            {
                TextColor(Yellow);
                gotoXY(4,2);
                cout<<"SL DOC GIA: "<<SLMaDG(tree)<<"/"<<MAXLISTMADG;
                Xuat_Danh_Sach_DG(tree);
                if(SLMaDG(tree)==0)
                {
                    PutCharXY(82,4,"DANH SACH DOC GIA TRONG, VUI LONG THEM LOP!!",Red);
                    _getch();
                    break;
                }
                DG* dg = NhapMaDGVaoKhung(tree,70,7);
                if(dg != NULL)
                {
                	tempL = TimDGTheoID(tree,dg);
                    if(tempL==NULL)
                        BaoLoi("MA DOC GIA KHONG TON TAI, VUI LONG KIEM TRA LAI!!",82,4);
                    else{
                    	DG dg1 = *tempL;
                    	tempL = NhapDocGiaVaoKhung(tree,70,7,tempL);
                    	dg1 = *tempL;
                    	n = Sua_DG(tree,*tempL);
	                    if(n==1)
	                    {
	                        TextColor(Yellow);
	                        gotoXY(4,2);
	                        cout<<"SL DOC GIA: "<<SLMaDG(tree)<<"/"<<MAXLISTMADG;
	                        Xuat_Danh_Sach_DG(tree);
	                        ThanhCong("SUA DOC GIA THANH CONG!!",82,4);
	                        GhiFileDG(tree,"TheDocGia.txt");
	                    }	
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
            int n=0;
            PutCharXY(82,2,"===========XUAT DOC GIA THEO HO TEN============",Blue);
            TextColor(Green);
            vekhung(69,25,1,54);
            PutCharXY(70,26,"ESC: THOAT | TAB: DOI VI TRI CON TRO | ENTER: XAC NHAN",Green);
            do
            {
                TextColor(Yellow);
                gotoXY(4,2);
                int dem_sl_doc_gia = SLMaDG(tree);
                DG *dg = new DG[dem_sl_doc_gia];
				dem_sl_doc_gia = 0;
				themMangDocGia(tree, dg, dem_sl_doc_gia);
				for (int q = 0; q < dem_sl_doc_gia; q++){
					for (int k = dem_sl_doc_gia - 1; k > q; k--) {
						
						if (strcmp(dg[k - 1].ten,dg[k].ten) > 0 || strcmp(dg[k - 1].ten,dg[k].ten) == 0 && strcmp(dg[k - 1].ho,dg[k].ho)>0){
							DG temp;
							temp = dg[k - 1];
							dg[k - 1] = dg[k];
							dg[k] = temp;
						}
					}
				}
                Xuat_Danh_Sach_DG_Theo_Ten(dg,dem_sl_doc_gia);
                listenToEscapeKeyDocGia(tree);
                delete [] dg;
                    break;
            }
            while(1);
            break;
        }
        case 4:
        {
            system("cls");
            int n=0;
            PutCharXY(82,2,"===========XUAT DOC GIA THEO MA THE DOC GIA============",Blue);
            TextColor(Green);
            vekhung(69,25,1,54);
            PutCharXY(70,26,"ESC: THOAT | TAB: DOI VI TRI CON TRO | ENTER: XAC NHAN",Green);
            do
            {
                TextColor(Yellow);
                gotoXY(4,2);
                Xuat_Danh_Sach_DG(tree);
                listenToEscapeKeyDocGia(tree);
                    break;
            }
            while(1);
            break;
        }
        }
    }
    while(m!=-1);
}
 #endif
