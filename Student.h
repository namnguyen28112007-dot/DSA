#pragma once
#include "models.h"
#include <string>

// ===== Vai tro dang nhap + ket qua login =====
enum VaiTro { TEACHER, STUDENT, INVALID, EXIT_APP };

struct LoginResult {
    VaiTro role = INVALID;
    SinhVien* student = nullptr; // chi khac nullptr khi role == STUDENT
};

// Tim sinh vien theo MASV tren toan he thong (duyet tat ca lop).
// Dung cho login va kiem tra MASV trung khi them SV moi.
SinhVien* findSinhVienGlobal(Lop* dsLop[], int n, const std::string& maSV);

// Them sinh vien vao dung lop theo maLop.
// Tu choi neu: khong tim thay lop, hoac MASV da ton tai (toan he thong).
bool addSinhVien(
    Lop* dsLop[], int n,
    const std::string& maLop,
    const std::string& maSV,
    const std::string& ho,
    const std::string& ten,
    const std::string& phai,
    const std::string& password
);

// Dang nhap: GV/GV -> TEACHER; MASV+password dung -> STUDENT; con lai -> INVALID.
LoginResult login(Lop* dsLop[], int n);

// Luu / doc danh sach sinh vien (lop phai duoc load truoc).
void saveSinhVien(Lop* dsLop[], int n, const std::string& path);
int loadSinhVien(Lop* dsLop[], int n, const std::string& path);
