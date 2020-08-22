#include <stdio.h>
#include <string.h>

#define MAXLISTLOP 500
#define MAXLISTMONHOC 300
#define MAXLISTCHT 2000
#define STACKSIZE 500


//Cau truc danh sach mon hoc
struct MonHoc
{
    char MAMH[15];
    char TENMH[30];
};
typedef struct MonHoc MONHOC;

struct listMH
{
    //int key;
    int soluongMH;
    MonHoc *nodeMH[MAXLISTMONHOC];
};
typedef struct listMH LISTMH;

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
//Cau truc danh sach sinh vien
struct SinhVien
{
    char MASV[15];
    char HO[50];
    char TEN[10];
    char NgaySinh[20];
    char GioiTinh[5];
    char password[12];
    //con tro ds diem thi
    LISTDT*  listdt;
};
typedef struct SinhVien SV;

struct nodeSV
{
    SV DataSV;
    struct nodeSV *pNextSV;
};
typedef struct nodeSV NODESV;
struct listSinhVien
{
    NODESV *pHeadSV;
    int soluongSV;
};
typedef struct listSinhVien LISTSV;
/////////////////////////////////
//Cau truc danh sach lop
struct Lop
{
    //int MALOP;
    char MALOP[15];
    char TENLOP[30];
    char NIENKHOA[4];
    //con tro dssv
    LISTSV*  listsv;
};
typedef struct Lop LOP;

struct listLop
{
    int soluong;
    Lop *nodeLop[MAXLISTLOP];

};
typedef struct listLop LISTLOP;
/////////////////////////////////
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

