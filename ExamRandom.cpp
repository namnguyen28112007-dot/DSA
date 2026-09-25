#include "ExamRandom.h"
#include <cstdlib>
void hoanVi(CauHoi*& a, CauHoi*& b){
    CauHoi*temp=a;
    a=b;
    b=temp;
}
int layCauHoiVaoMang(
    MonHoc* monHoc,
    CauHoi* ds[],
    int maxSize
){
    if(monHoc==nullptr){
        return 0;
    }
    CauHoi* p= monHoc->dsCHT;
    int n=0;
    while(p!=nullptr&&n<maxSize){
        ds[n]=p;
        n++;
        p=p->next;
    }
    return n;
} 
void tronCauHoi(CauHoi* ds[], int n){
        for (int i=n-1;i>0;i--){
            int j=rand()%(i+1);
            hoanVi(ds[i],ds[j]);
        }
    }
    
