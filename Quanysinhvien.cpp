#include <iostream>
#include <cstring> // dùng cho hàm strcmp

using namespace std;

// ngay thang nam
struct Ngay 
{
    int ngay, thang, nam;
};

// struct sinh vien
struct SinhVien 
{
    char maSV[8];
    char hoTen[50];
    int gioiTinh;
    Ngay ngaySinh;
    char diaChi[100];
    char lop[12];
    char khoa[7];
};

// struct node & list
struct Node 
{
    SinhVien data;
    Node* link;
};

struct List 
{
    Node* first;
    Node* last;
};

// khoi tao danh sach
void init(List &list) 
{
    list.first = nullptr;
    list.last = nullptr;
}

// nhap chuoi
void nhapChuoi(char arr[], int maxLength) 
{
    char ch;
    int i = 0;
    while (i < maxLength - 1) 
    {
        ch = getchar();
        if (ch == '\n') break;
        arr[i] = ch;
        i++;
    }
    arr[i] = '\0';
}

// nhap thong tin sinh vien
SinhVien nhapSinhVien() 
{
    SinhVien sv;
    cout << "Nhap ma sinh vien(toi da 8 ky tu): ";
    nhapChuoi(sv.maSV, 8);
    cin.ignore();

    cout << "Nhap ho ten: ";
    nhapChuoi(sv.hoTen, 50);

    cout << "Nhap gioi tinh (0: Nu, 1: Nam): ";
    cin >> sv.gioiTinh;

    cout << "Nhap ngay sinh (ngay thang nam): ";
    cin >> sv.ngaySinh.ngay >> sv.ngaySinh.thang >> sv.ngaySinh.nam;

    cout << "Nhap dia chi: ";
    cin.ignore();
    nhapChuoi(sv.diaChi, 100);

    cout << "Nhap lop: ";
    nhapChuoi(sv.lop, 12);

    cout << "Nhap khoa: ";
    nhapChuoi(sv.khoa, 7);

    return sv;
}

// node sinh vien
Node* taoNode(SinhVien sv) 
{
    Node* p = new Node;
    p->data = sv;
    p->link = nullptr;
    return p;
}

// add sinh vien vao danh sach
void themSinhVien(List &list, SinhVien sv) 
{
    Node* p = taoNode(sv);
    if (list.first == nullptr) 
    {
        list.first = list.last = p;
    } 
    else 
    {
        list.last->link = p;
        list.last = p;
    }
}

// in danh sach
void inDanhSach(List list) 
{
    Node* p = list.first;
    while (p != nullptr) 
    {
        cout << "Ma SV: " << p->data.maSV << "\n";
        cout << "Ho ten: " << p->data.hoTen << "\n";
        cout << "Gioi tinh: " << (p->data.gioiTinh ? "Nam" : "Nu") << "\n";
        cout << "Ngay sinh: " << p->data.ngaySinh.ngay << "/" << p->data.ngaySinh.thang << "/" << p->data.ngaySinh.nam << "\n";
        cout << "Dia chi: " << p->data.diaChi << "\n";
        cout << "Lop: " << p->data.lop << "\n";
        cout << "Khoa: " << p->data.khoa << "\n";
        cout << "----------------------------------------\n";
        p = p->link;
    }
}

// hàm thêm sinh viên vào danh sách đã được sắp xếp theo mã sinh viên
void themSinhVienVaoDSDaSapXep(List &list, SinhVien sv) 
{
    Node* p = taoNode(sv);
    // Nếu danh sách rỗng hoặc sinh viên mới nhỏ hơn đầu danh sách
    if (list.first == nullptr || strcmp(sv.maSV, list.first->data.maSV) < 0) 
    {
        p->link = list.first;
        list.first = p;
        if (list.last == nullptr) 
        {
            list.last = p;
        }
        return;
    }

    // Tìm vị trí để chèn sinh viên
    Node* current = list.first;
    while (current->link != nullptr && strcmp(sv.maSV, current->link->data.maSV) > 0) 
    {
        current = current->link;
    }

    p->link = current->link;
    current->link = p;

    // Cập nhật lại last nếu chèn vào cuối
    if (p->link == nullptr) 
    {
        list.last = p;
    }
}

// hàm kiểm tra
int main() 
{
    List list;
    init(list);

    int n;
    cout << "Nhap so luong sinh vien: ";
    cin >> n;
    cin.ignore();
    for (int i = 0; i < n; ++i) 
    {
        SinhVien sv = nhapSinhVien();
        themSinhVienVaoDSDaSapXep(list, sv); // thêm vào danh sách theo mã sinh viên đã được sắp xếp
    }

    cout << "Danh sach sinh vien da sap xep: \n";
    inDanhSach(list);

    // thêm sinh viên mới và sắp xếp
    cout << "Nhap sinh vien moi: \n";
    SinhVien sv = nhapSinhVien();
    themSinhVienVaoDSDaSapXep(list, sv);

    cout << "Danh sach sinh vien sau khi them va sap xep: \n";
    inDanhSach(list);

    return 0;
}
