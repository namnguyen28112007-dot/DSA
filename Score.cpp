#include "Score.h"
#include "Classroom.h"
#include "Student.h"
#include <fstream>
#include <sstream>
#include <iostream>

Diem* findScore(SinhVien* sv, const std::string& maMH){
    if(sv==nullptr){
        return nullptr;
    }
    Diem* p=sv->dsDiem;
    while(p!=nullptr){
        if(p->maMH==maMH){
            return p;
        }
        p=p->next;
    }
    return nullptr;
}

bool hasTaken(SinhVien* sv, const std::string& maMH){
    return findScore(sv,maMH)!=nullptr;
}

bool addScore(SinhVien* sv, const std::string& maMH, double diem){
    if(sv==nullptr){
        return false;
    }
    if(findScore(sv,maMH)!=nullptr){
        return false; // da co diem mon nay roi -> tu choi
    }
    Diem* moi=new Diem;
    moi->maMH=maMH;
    moi->diem=diem;
    moi->next=sv->dsDiem;
    sv->dsDiem=moi;
    return true;
}

void printClassScore(Lop* lop, const std::string& maMH){
    if(lop==nullptr){
        std::cout<<"Khong tim thay lop.\n";
        return;
    }
    int stt=1;
    std::cout<<"Bang diem mon "<<maMH<<" - Lop "<<lop->maLop<<"\n";
    for(SinhVien* sv=lop->dsSV; sv!=nullptr; sv=sv->next){
        std::cout<<stt++<<" | "<<sv->maSV<<" | "<<sv->ho<<" "<<sv->ten<<" | ";
        Diem* d=findScore(sv,maMH);
        if(d!=nullptr){
            std::cout<<d->diem;
        } else {
            std::cout<<"Chua thi"; // T09: khong hien 0.0
        }
        std::cout<<"\n";
    }
}

void saveDiem(Lop* dsLop[], int n, const std::string& path){
    std::ofstream f(path);
    if(!f.is_open()){
        return;
    }
    for(int i=0;i<n;i++){
        if(dsLop[i]==nullptr){
            continue;
        }
        for(SinhVien* sv=dsLop[i]->dsSV; sv!=nullptr; sv=sv->next){
            for(Diem* d=sv->dsDiem; d!=nullptr; d=d->next){
                f<<sv->maSV<<"|"<<d->maMH<<"|"<<d->diem<<"\n";
            }
        }
    }
    f.close();
}

int loadDiem(Lop* dsLop[], int n, const std::string& path){
    std::ifstream f(path);
    int soLuong=0;
    if(!f.is_open()){
        return 0;
    }
    std::string dong;
    while(std::getline(f,dong)){
        if(dong.empty()){
            continue;
        }
        std::stringstream ss(dong);
        std::string maSV,maMH,diemStr;
        std::getline(ss,maSV,'|');
        std::getline(ss,maMH,'|');
        std::getline(ss,diemStr,'|');
        SinhVien* sv=findSinhVienGlobal(dsLop,n,maSV);
        if(sv!=nullptr){
            double diem=std::stod(diemStr);
            if(addScore(sv,maMH,diem)){
                soLuong++;
            }
        }
    }
    f.close();
    return soLuong;
}
bool updateScore( SinhVien* sv,const std::string& maMH,double diem){
    if(!(diem >= 0 && diem <= 10)){
        return false;
    }
    Diem* p = findScore(sv, maMH);
    if(p == nullptr){
        return false;
    }
    p->diem = diem;
    return true;
}
