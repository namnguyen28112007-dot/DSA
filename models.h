#pragma once

#include <string>

constexpr int MAX_LOP = 10000;

// Trang thai bai thi.
constexpr int BAI_DANG_THI = 0;
constexpr int BAI_HOAN_THANH = 1;
constexpr int BAI_VI_PHAM = 2;

struct CauHoi {
    int id = 0;
    std::string noiDung;
    std::string A, B, C, D;
    char dapAn = 'A';
    CauHoi* next = nullptr;
};

struct MonHoc {
    std::string maMH;
    std::string tenMH;
    CauHoi* dsCHT = nullptr;
    MonHoc* left = nullptr;
    MonHoc* right = nullptr;
};

struct Diem {
    std::string maMH;
    double diem = 0.0;
    Diem* next = nullptr;
};

// Chi tiet mot cau hoi DUNG THEO DE THI ma sinh vien da nhin thay.
// Vi du: A tren de thi la dap an C goc => nguonA = 'C'.
struct ChiTietThi {
    int questionId = 0;
    std::string noiDung;
    std::string A, B, C, D;
    char dapAnDung = 'A';
    char dapAnSV = 'X';       // X = chua tra loi / het gio

    char nguonA = 'A';
    char nguonB = 'B';
    char nguonC = 'C';
    char nguonD = 'D';

    ChiTietThi* next = nullptr;
};

struct BaiThi {
    std::string maMH;
    double diem = 0.0;
    int soCau = 0;
    int soCauDung = 0;
    ChiTietThi* dsChiTiet = nullptr;

    // Khoi phuc bai thi dang do.
    int trangThai = BAI_HOAN_THANH;

    // So giay CON LAI duoc checkpoint xuong file.
    // Thoi gian may bi mat dien / chuong trinh bi tat KHONG bi tru.
    long long thoiGianConLai = 0;

    // So lan phien thi bi ngat bat thuong.
    int soLanGianDoan = 0;

    // true neu lan luu cuoi cung sinh vien dang o trong phien thi.
    // Neu lan sau khoi dong van true => ghi nhan mot lan gian doan.
    bool phienDangMo = false;

    BaiThi* next = nullptr;
};

struct SinhVien {
    std::string maSV;
    std::string ho;
    std::string ten;
    std::string phai;
    std::string password;
    Diem* dsDiem = nullptr;
    BaiThi* lichSuThi = nullptr;
    SinhVien* next = nullptr;
};

struct Lop {
    std::string maLop;
    std::string tenLop;
    SinhVien* dsSV = nullptr;
};
