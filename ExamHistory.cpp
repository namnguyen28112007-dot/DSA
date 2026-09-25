#include "ExamHistory.h"
#include "ExamValidation.h"
#include "Score.h"
ChiTietThi* taoChiTietThi(CauHoi* cauHoi,char dapAnSV){
    if(cauHoi==nullptr){
    return nullptr;
}
ChiTietThi* moi=new ChiTietThi;
moi->questionId=cauHoi->id;
moi->noiDung=cauHoi->noiDung;
moi->A=cauHoi->A;
moi->B=cauHoi->B;
moi->C=cauHoi->C;
moi->D=cauHoi->D;
moi->dapAnDung=cauHoi->dapAn;
moi->dapAnSV=dapAnSV;
return moi;
}
void themChiTietThi(
    BaiThi* baiThi,
    ChiTietThi* moi
){
    if(baiThi==nullptr||moi==nullptr){
        return;
    }
    if(baiThi->dsChiTiet==nullptr){
        baiThi->dsChiTiet=moi;
        return;
    }
    ChiTietThi*p=baiThi->dsChiTiet;
    while(p->next!=nullptr){
        p=p->next;
    }
    p->next=moi;
}
BaiThi*taoBaiThi( const std::string&maMH, int soCau){
    if(maMH.empty() || soCau <= 0){
        return nullptr;
    }
    BaiThi*baiThi=new BaiThi;
    baiThi->maMH=maMH;
    baiThi->soCau=soCau;
    baiThi->diem=0.0;
    baiThi->soCauDung=0;
    baiThi->dsChiTiet=nullptr;
    baiThi->trangThai=BAI_DANG_THI;
    baiThi->thoiGianConLai = 30 * 60;
    baiThi->phienDangMo=true;
    baiThi->next = nullptr;
    return baiThi;
}
void themBaiThiVaoLichSu( SinhVien* sv, BaiThi* baiThi){
    if(sv==nullptr||baiThi==nullptr){
        return;
    }
    baiThi->next = sv->lichSuThi;
    sv->lichSuThi = baiThi;
}
BaiThi* timBaiThi( SinhVien* sv, const std::string&maMH
){
    if(sv==nullptr){
        return nullptr;
    }
    BaiThi*p=sv->lichSuThi;
    while(p!=nullptr){
        if(p->maMH==maMH){
            return p;
        }
        p=p->next;
    }
    return nullptr;
}
void chamBaiThi(SinhVien* sv, BaiThi* baiThi){
    if(sv == nullptr || baiThi == nullptr){
        return;
    }
    int soDung = 0;
    ChiTietThi* p = baiThi->dsChiTiet;
    while(p != nullptr){
        if(p->dapAnSV != 'X' &&
           p->dapAnSV == p->dapAnDung){
            soDung++;
        }
        p = p->next;
    }
    baiThi->soCauDung = soDung;
    if(baiThi->trangThai == BAI_VI_PHAM){
        baiThi->diem = 0.0;
    } else {
        baiThi->diem =
            tinhDiem(soDung, baiThi->soCau);
        baiThi->trangThai = BAI_HOAN_THANH;
    }
    baiThi->phienDangMo = false;
    Diem* diemCu = findScore(sv, baiThi->maMH);
    if(diemCu == nullptr){
        addScore(sv, baiThi->maMH, baiThi->diem);
    } else {
        updateScore(sv, baiThi->maMH, baiThi->diem);
    }
}
#include <iostream>
#include "models.h"
#include "ExamHistory.h"

using namespace std;

int main() {

    // 1. Tao cau hoi de test
    CauHoi c1;
    c1.id = 1;
    c1.noiDung = "FIFO la nguyen tac cua cau truc nao?";
    c1.A = "Stack";
    c1.B = "Queue";
    c1.C = "Tree";
    c1.D = "Graph";
    c1.dapAn = 'B';

    CauHoi c2;
    c2.id = 2;
    c2.noiDung = "LIFO la nguyen tac cua cau truc nao?";
    c2.A = "Stack";
    c2.B = "Queue";
    c2.C = "Tree";
    c2.D = "Graph";
    c2.dapAn = 'A';

    // 2. Tao bai thi
    BaiThi* bt = taoBaiThi("CTDL", 2);
    
    // 3. Tao snapshot cau hoi
    ChiTietThi* ct1 = taoChiTietThi(&c1, 'B');
    ChiTietThi* ct2 = taoChiTietThi(&c2, 'C');

    // 4. Them 2 cau vao bai thi
    themChiTietThi(bt, ct1);
    themChiTietThi(bt, ct2);

    // Gia su sinh vien dung 1/2 cau
    bt->soCauDung = 1;
    bt->diem = 5.0;
    bt->trangThai = BAI_HOAN_THANH;
    bt->phienDangMo = false;

    // 5. Tao sinh vien
    SinhVien sv;
    sv.maSV = "SV001";
    sv.ho = "Nguyen";
    sv.ten = "Nam";

    // 6. Them bai thi vao lich su
    themBaiThiVaoLichSu(&sv, bt);

    // 7. In thong tin bai thi
    cout << "Ma mon: " << bt->maMH << endl;
    cout << "So cau: " << bt->soCau << endl;
    cout << "So cau dung: " << bt->soCauDung << endl;
    cout << "Diem: " << bt->diem << endl;

    // 8. Duyet danh sach ChiTietThi
    cout << "\nChi tiet bai thi:\n";
    ChiTietThi* p = bt->dsChiTiet;
    while (p != nullptr) {
        cout << "Cau " << p->questionId << endl;
        cout << p->noiDung << endl;
        cout << "Dap an dung: " << p->dapAnDung << endl;
        cout << "Dap an SV: " << p->dapAnSV << endl;
        cout << endl;

        p = p->next;
    }

    // 9. Test timBaiThi
    BaiThi* tim = timBaiThi(&sv, "CTDL");

    if (tim != nullptr) {
        cout << "Tim thay bai thi: " << tim->maMH << endl;
        cout << "Diem: " << tim->diem << endl;
    }
    else {
        cout << "Khong tim thay bai thi" << endl;
    }


    return 0;
}
