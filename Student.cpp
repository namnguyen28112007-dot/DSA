#include "Student.h"
#include "Classroom.h"
#include <fstream>
#include <sstream>
#include <iostream>

SinhVien* findSinhVienGlobal(Lop* dsLop[], int n, const std::string& maSV){
    for(int i=0;i<n;i++){
        if(dsLop[i]==nullptr){
            continue;
        }
        SinhVien* p=dsLop[i]->dsSV;
        while(p!=nullptr){
            if(p->maSV==maSV){
                return p;
            }
            p=p->next;
        }
    }
    return nullptr;
}

bool addSinhVien(
    Lop* dsLop[], int n,
    const std::string& maLop,
    const std::string& maSV,
    const std::string& ho,
    const std::string& ten,
    const std::string& phai,
    const std::string& password
){
    Lop* lop=findLop(dsLop,n,maLop);
    if(lop==nullptr){
        return false;
    }
    if(findSinhVienGlobal(dsLop,n,maSV)!=nullptr){
        return false; // T02: MASV phai duy nhat toan he thong
    }
    SinhVien* moi=new SinhVien;
    moi->maSV=maSV;
    moi->ho=ho;
    moi->ten=ten;
    moi->phai=phai;
    moi->password=password;
    moi->dsDiem=nullptr;
    moi->lichSuThi=nullptr;
    moi->next=lop->dsSV;
    lop->dsSV=moi;
    return true;
}

LoginResult login(Lop* dsLop[], int n){
    std::string user,pass;
    std::cout<<"Ten dang nhap (GV hoac MASV): ";
    std::getline(std::cin,user);
    std::cout<<"Mat khau: ";
    std::getline(std::cin,pass);

    LoginResult kq;

    if(user=="GV"&&pass=="GV"){
        kq.role=TEACHER;
        kq.student=nullptr;
        return kq;
    }

    SinhVien* sv=findSinhVienGlobal(dsLop,n,user);
    if(sv!=nullptr&&sv->password==pass){
        kq.role=STUDENT;
        kq.student=sv;
    } else {
        kq.role=INVALID; // T04: sai pass -> bao sai, khong crash
        kq.student=nullptr;
    }
    return kq;
}

void saveSinhVien(Lop* dsLop[], int n, const std::string& path){
    std::ofstream f(path);
    if(!f.is_open()){
        return;
    }
    for(int i=0;i<n;i++){
        if(dsLop[i]==nullptr){
            continue;
        }
        SinhVien* p=dsLop[i]->dsSV;
        while(p!=nullptr){
            f<<dsLop[i]->maLop<<"|"<<p->maSV<<"|"<<p->ho<<"|"
             <<p->ten<<"|"<<p->phai<<"|"<<p->password<<"\n";
            p=p->next;
        }
    }
    f.close();
}

int loadSinhVien(Lop* dsLop[], int n, const std::string& path){
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
        std::string maLop,maSV,ho,ten,phai,pass;
        std::getline(ss,maLop,'|');
        std::getline(ss,maSV,'|');
        std::getline(ss,ho,'|');
        std::getline(ss,ten,'|');
        std::getline(ss,phai,'|');
        std::getline(ss,pass,'|');
        if(addSinhVien(dsLop,n,maLop,maSV,ho,ten,phai,pass)){
            soLuong++;
        }
    }
    f.close();
    return soLuong;
}
