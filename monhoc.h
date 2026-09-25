#pragma once

#include "models.h"
#include <string>

MonHoc* timMonHoc(MonHoc* dsMon, const std::string& maMH);// Giu nguyen ten ham de dung voi bai lam hien tai.
bool themMonHoc(MonHoc*& dsMon, const std::string& maMH, const std::string& tenMH);
bool suaMonHoc(MonHoc* dsMon, const std::string& maMH, const std::string& tenMoi);
bool xoaMonHoc(MonHoc*& dsMon, const std::string& maMH);// chi xoa trong danh sach. Noi goi phai chan xoa mon da co bai thi/diem.
void inDanhSachMonHoc(MonHoc* dsMon);
void giaiPhongDanhSachMonHoc(MonHoc*& dsMon);
void giaiPhongCayMonHoc(MonHoc*& dsMon);
int demCauHoi(const MonHoc* mh);
// nextQuestionId dung chung cho TOAN BO mon, chi tang khi them thanh cong.
// Khi doc du lieu, dat nextQuestionId lon hon ID lon nhat da doc.
bool themCauHoi(MonHoc* mh, int& nextQuestionId,
                const std::string& noiDung,
                const std::string& A,
                const std::string& B,
                const std::string& C,
                const std::string& D,
                char dapAn);
// Dung khi load file: giu nguyen ID cu. Chi kiem tra trung ID trong mon nay.
// Noi doc file can kiem tra ID duy nhat tren toan bo ngan hang.
bool chenCauHoiVoiId(MonHoc* mh, int id,
                     const std::string& noiDung,
                     const std::string& A,
                     const std::string& B,
                     const std::string& C,
                     const std::string& D,
                     char dapAn);
CauHoi* timCauHoi(MonHoc* mh, int id);
// Chi sua ngan hang. Noi goi xu ly cap nhat lich su va cham lai neu can.
bool suaCauHoi(MonHoc* mh, int id,
               const std::string& noiDung,
               const std::string& A,
               const std::string& B,
               const std::string& C,
               const std::string& D,
               char dapAn);
bool xoaCauHoi(MonHoc* mh, int id);
void inDanhSachCauHoi(const MonHoc* mh);
