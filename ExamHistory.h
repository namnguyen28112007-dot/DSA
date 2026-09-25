#pragma once
#include "models.h"
ChiTietThi* taoChiTietThi( CauHoi* cauHoi, char dapAnSV);
void themChiTietThi(BaiThi* baiThi, ChiTietThi* moi);
BaiThi* taoBaiThi(const std::string&maMH, int soCau);
void themBaiThiVaoLichSu( SinhVien* sv, BaiThi* baiThi);
BaiThi* timBaiThi( SinhVien* sv, const std::string&maMH);
void chamBaiThi(SinhVien* sv, BaiThi* baiThi);
