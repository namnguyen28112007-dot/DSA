#include "Classroom.h"
#include <fstream>
#include <sstream>
#include <iostream>

Lop* findLop(Lop* dsLop[], int n, const std::string& maLop){
    for(int i=0;i<n;i++){
        if(dsLop[i]!=nullptr && dsLop[i]->maLop==maLop){
            return dsLop[i];
        }
    }
    return nullptr;
}

bool addLop(Lop* dsLop[], int& n, const std::string& maLop, const std::string& tenLop){
    if(n>=MAX_LOP){
        return false;
    }
    if(findLop(dsLop,n,maLop)!=nullptr){
        return false; // T01: ma lop trung -> tu choi
    }
    Lop* moi=new Lop;
    moi->maLop=maLop;
    moi->tenLop=tenLop;
    moi->dsSV=nullptr;
    dsLop[n]=moi;
    n++;
    return true;
}

void printDanhSachLop(Lop* dsLop[], int n){
    std::cout<<"Danh sach lop:\n";
    for(int i=0;i<n;i++){
        if(dsLop[i]!=nullptr){
            std::cout<<i+1<<". "<<dsLop[i]->maLop<<" - "<<dsLop[i]->tenLop<<"\n";
        }
    }
}

void saveLop(Lop* dsLop[], int n, const std::string& path){
    std::ofstream f(path);
    if(!f.is_open()){
        return;
    }
    for(int i=0;i<n;i++){
        if(dsLop[i]!=nullptr){
            f<<dsLop[i]->maLop<<"|"<<dsLop[i]->tenLop<<"\n";
        }
    }
    f.close();
}

int loadLop(Lop* dsLop[], const std::string& path){
    std::ifstream f(path);
    int n=0;
    if(!f.is_open()){
        return 0;
    }
    std::string dong;
    while(std::getline(f,dong)){
        if(dong.empty()){
            continue;
        }
        std::stringstream ss(dong);
        std::string maLop,tenLop;
        std::getline(ss,maLop,'|');
        std::getline(ss,tenLop,'|');
        addLop(dsLop,n,maLop,tenLop);
    }
    f.close();
    return n;
}
