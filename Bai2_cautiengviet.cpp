#include <iostream>
#include <string>
#include <unordered_map>

struct NutTu {
    std::string tu;
    NutTu* tiep;

    NutTu(const std::string& t) : tu(t), tiep(nullptr) {}
};

class Cau {
private:
    NutTu* dau;

public:
    Cau() : dau(nullptr) {}

    void chenTu(const std::string& tu) {
        NutTu* tuMoi = new NutTu(tu);
        if (!dau) {
            dau = tuMoi;
        } else {
            NutTu* hienTai = dau;
            while (hienTai->tiep) {
                hienTai = hienTai->tiep;
            }
            hienTai->tiep = tuMoi;
        }
    }

    std::string timTuXuatHienNhieuNhat() {
        std::unordered_map<std::string, int> demTu;
        NutTu* hienTai = dau;
        std::string tuNhieuNhat;
        int maxDem = 0;

        while (hienTai) {
            demTu[hienTai->tu]++;
            if (demTu[hienTai->tu] > maxDem) {
                maxDem = demTu[hienTai->tu];
                tuNhieuNhat = hienTai->tu;
            }
            hienTai = hienTai->tiep;
        }
        return tuNhieuNhat;
    }

    void xoaTuLap() {
        NutTu* hienTai = dau;
        while (hienTai && hienTai->tiep) {
            if (hienTai->tu == hienTai->tiep->tu) {
                NutTu* tuLap = hienTai->tiep;
                hienTai->tiep = hienTai->tiep->tiep;
                delete tuLap;
            } else {
                hienTai = hienTai->tiep;
            }
        }
    }

    int demTuVung() {
        std::unordered_map<std::string, bool> tuDuyNhat;
        NutTu* hienTai = dau;
        int dem = 0;

        while (hienTai) {
            if (!tuDuyNhat[hienTai->tu]) {
                tuDuyNhat[hienTai->tu] = true;
                dem++;
            }
            hienTai = hienTai->tiep;
        }
        return dem;
    }

    void inCau() const {
        NutTu* hienTai = dau;
        while (hienTai) {
            std::cout << hienTai->tu << " ";
            hienTai = hienTai->tiep;
        }
        std::cout << std::endl;
    }

    ~Cau() {
        while (dau) {
            NutTu* tam = dau;
            dau = dau->tiep;
            delete tam;
        }
    }
};

int main() {
    Cau cau;
    cau.chenTu("toi");
    cau.chenTu("la");
    cau.chenTu("sinh");
    cau.chenTu("vien");
    cau.chenTu("hust");
    cau.chenTu("hust");

    std::cout << "Cau ban dau: ";
    cau.inCau();

    std::cout << "Tu xuat hien nhieu nhat: " << cau.timTuXuatHienNhieuNhat() << '\n';

    cau.xoaTuLap();
    std::cout << "Cau sau khi loai bo tu lap: ";
    cau.inCau();

    std::cout << "So tu vung xuat hien trong cau: " << cau.demTuVung() << '\n';

    return 0;
}
