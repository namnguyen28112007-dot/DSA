#include "ExamValidation.h"
char chuanHoaDapAn(char dapAn){
    if(dapAn >= 'a' && dapAn <= 'd'){
        dapAn = dapAn - 'a' + 'A';
    }
    return dapAn;
}
bool kiemTraDapAn(char dapAn){
    dapAn = chuanHoaDapAn(dapAn);

    return dapAn >= 'A' && dapAn <= 'D';
}
double tinhDiem(int soCauDung, int tongSoCau){
    if(tongSoCau <= 0){
        return 0.0;
    }
    if(soCauDung < 0 || soCauDung > tongSoCau){
        return 0.0;
    }
    return static_cast<double>(soCauDung)
           / tongSoCau * 10.0;
}
