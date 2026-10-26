#include "ExamPersistence.h"
#include <fstream>
#include <sstream>
bool luuLichSuThi(
    SinhVien* sv,
    const std::string& tenFile
){
    if(sv==nullptr){
        return false;
    }
    std::ofstream file(tenFile);
    if(!file.is_open()){
        return false;
    }
    BaiThi* p= sv->lichSuThi;
    while(p!=nullptr){
        file<<"BaiThi|"
            <<sv->maSV<<"|"
            <<p->maMH<<"|"
            <<p->diem<<"|"
            <<p->soCau<<"|"
            <<p->soCauDung<<"|"
            <<p->trangThai<<"|"
            <<p->thoiGianConLai<<"|"
            <<p->soLanGianDoan<<"|"
            <<p->phienDangMo
            <<"\n";
ChiTietThi*q = p->dsChiTiet;
while(q!=nullptr){
    file<<"ChiTiet|"
        <<q->questionId<<"|"
        <<q->noiDung<<"|"
        <<q->A<<"|"
        <<q->B<<"|"
        <<q->C<<"|"
        <<q->D<<"|"
        <<q->dapAnDung<<"|"
        <<q->dapAnSV
        <<"\n";
        q=q->next;
}
p=p->next;
}
file.close();
return true;
}
bool docLichSuThi(
    SinhVien* sv,
    const std::string& tenFile
){
    if(sv==nullptr){
        return false;
    }
    std::ifstream file(tenFile);
    if(!file.is_open()){
        return false;
    }
    std::string line;
    BaiThi* baiThiHienTai= nullptr;
    BaiThi* cuoi= sv->lichSuThi;
    if(cuoi != nullptr){
    while(cuoi->next != nullptr){
        cuoi = cuoi->next;
    }
}
    while(std::getline(file, line)){
        std::stringstream ss(line);
        std::string loai;
        std::getline(ss, loai, '|');
        if (loai == "BaiThi"){
            std::string maSV;
            std::string maMH;
            std::string diem;
            std::string soCau;
            std::string soCauDung;
            std::string trangThai;
            std::string thoiGianConLai;
            std::string soLanGianDoan;
            std::string phienDangMo;
            
            std::getline(ss,maSV,'|');
            std::getline(ss, maMH, '|');
            std::getline(ss, diem, '|');
            std::getline(ss, soCau, '|');
            std::getline(ss, soCauDung, '|');
            std::getline(ss, trangThai, '|');
            std::getline(ss, thoiGianConLai, '|');
            std::getline(ss, soLanGianDoan, '|');
            std::getline(ss, phienDangMo, '|');
        BaiThi* moi = new BaiThi;
        moi->maMH = maMH;
        moi->diem = std::stod(diem);
        moi->soCau = std::stoi(soCau);
        moi->soCauDung = std::stoi(soCauDung);
        moi->trangThai = std::stoi(trangThai);
        moi->thoiGianConLai = std::stoll(thoiGianConLai);
        moi->soLanGianDoan = std::stoi(soLanGianDoan);
        moi->phienDangMo = std::stoi(phienDangMo);
        if(sv->lichSuThi == nullptr){
    sv->lichSuThi = moi;
    cuoi = moi;
} else{
    cuoi->next = moi;
    cuoi = moi;
}
baiThiHienTai = moi;
        }
        else if(loai=="ChiTiet"&&baiThiHienTai!=nullptr){
            std::string questionId;
            std::string noiDung;
            std::string A;
            std::string B;
            std::string C;
            std::string D;
            std::string dapAnDung;
            std::string dapAnSV;

            std::getline(ss, questionId, '|');
            std::getline(ss, noiDung, '|');
            std::getline(ss, A, '|');
            std::getline(ss, B, '|');
            std::getline(ss, C, '|');
            std::getline(ss, D, '|');
            std::getline(ss, dapAnDung, '|');
            std::getline(ss, dapAnSV, '|');
            
            ChiTietThi* ct=new ChiTietThi;
            ct->questionId = std::stoi(questionId);
            ct->noiDung = noiDung;
            ct->A = A;
            ct->B = B;
            ct->C = C;
            ct->D = D;
            ct->dapAnDung = dapAnDung[0];
            ct->dapAnSV = dapAnSV[0];
            
            if(baiThiHienTai->dsChiTiet == nullptr){
                baiThiHienTai->dsChiTiet = ct;
}
else{
    ChiTietThi* q = baiThiHienTai->dsChiTiet;
    while(q->next != nullptr){
        q = q->next;
    }
    q->next = ct;
}
        }
    }
    file.close();
    return true;
}

