#include "ExamValidation.h"
#include <cctype>
bool kiemTraDapAn(char dapAn){
    dapAn=toupper(dapAn);
    return dapAn == 'A'||dapAn == 'B'||dapAn =='C'||dapAn =='D';
}
double tinhDiem(int soCauDung, int tongSoCau){
    if(tongSoCau<=0){
        return 0.0;
    }
    return (double)soCauDung/tongSoCau*10.0;
}