#pragma once
#include "models.h"
#include <string>

// Tim diem cua sinh vien theo maMH. Tra ve nullptr neu chua thi.
Diem* findScore(SinhVien* sv, const std::string& maMH);

// True neu sinh vien da co diem mon nay (tuc da thi roi).
// Duoc goi truoc startExam ben module C de chan thi lai.
bool hasTaken(SinhVien* sv, const std::string& maMH);

// Ghi diem cho sinh vien. Tu choi neu da co diem mon do (chi thi 1 lan/mon).
// Day la noi DUY NHAT tao Diem moi - module C khong duoc tu new Diem.
bool addScore(SinhVien* sv, const std::string& maMH, double diem);

// In bang diem ca lop cho 1 mon hoc. Hien "Chua thi" thay vi 0.0.
void printClassScore(Lop* lop, const std::string& maMH);

// Luu / doc diem cua toan bo sinh vien trong dsLop.
void saveDiem(Lop* dsLop[], int n, const std::string& path);
int loadDiem(Lop* dsLop[], int n, const std::string& path);
