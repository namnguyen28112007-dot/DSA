#pragma once
#include "models.h"
void hoanVi(CauHoi*& a, CauHoi*& b);    
int layCauHoiVaoMang(
    MonHoc* monHoc,
    CauHoi* ds[],
    int maxSize
);
void tronCauHoi(CauHoi* ds[], int n);
