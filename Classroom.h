#pragma once
#include "models.h"
#include <string>

// ===== Quan ly danh sach Lop (mang con tro, toi da MAX_LOP) =====

// Tim lop theo maLop. Tra ve nullptr neu khong co.
Lop* findLop(Lop* dsLop[], int n, const std::string& maLop);

// Them lop moi. Tu choi neu maLop da ton tai hoac da day (n >= MAX_LOP).
// n duoc tang len 1 neu them thanh cong.
bool addLop(Lop* dsLop[], int& n, const std::string& maLop, const std::string& tenLop);

// In danh sach lop ra console.
void printDanhSachLop(Lop* dsLop[], int n);

// Luu danh sach lop xuong file (khong luu sinh vien o day).
void saveLop(Lop* dsLop[], int n, const std::string& path);

// Doc danh sach lop tu file. Tra ve so luong lop da doc duoc (= n moi).
int loadLop(Lop* dsLop[], const std::string& path);
