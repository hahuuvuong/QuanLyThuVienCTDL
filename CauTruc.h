 #ifndef CAUTRUC_H
 #define CAUTRUC_H
#define MAXLISTDAUSACH 500

struct DanhMucSach {
	unsigned int ma_sach;
	unsigned int trang_thai;
	char vi_tri[31];
};

struct NodeDMS {
	DanhMucSach info;
	NodeDMS *next;
};
typedef struct NodeDMS *NodeDMSPtr;

struct DauSach {
	char isbnCode[9], tenSach[31], tacGia[31], namXuatBan[5], theLoai[31];
	unsigned int soTrang;
	NodeDMSPtr list_dms;
	int demDMS,demLuotMuonSach;
	DauSach *nextTheLoai,*nextTenSach,*nextTheLoaiThenTenSach;
	int trangThaiDeSapXep;
};
typedef struct DauSach DAUSACH;
typedef struct ListDauSach{
	int soLuong;
	DAUSACH *ArrDauSach[MAXLISTDAUSACH];
	DAUSACH *sortTheLoaiSach, *sortTenSach, *sortTheLoaiThenTenSach;
};
typedef struct ListDauSach LISTDAUSACH;

struct Date
{
	int ngay, thang, nam;
	void dateOut() {
		cout<< this->ngay <<"/"<< this->thang << "/" << this->nam;
	}
};
typedef struct Date d;

struct MuonSach {
	unsigned int ma_sach;
	Date ngayMuon;
	Date ngayTra;
	unsigned int trangThai;
};
typedef struct MuonSach MS;
struct nodeMS {
	MS info;
	nodeMS *next;
};
typedef struct nodeMS *MuonSachPTR;


struct DocGia {
	unsigned int maThe;
	char ho[30];
	char ten[15];
	char gioiTinh[2];
	int trangThai;
	MuonSachPTR firstMS;
};
typedef struct DocGia DG;

struct nodeDG {
	DG infoDG;
	nodeDG *pLeft;
	nodeDG *pRight;
};

typedef struct nodeDG NODEDG;
typedef NODEDG* NODE_DG_PTR;

 #endif
