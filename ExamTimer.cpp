#include "ExamTimer.h"
std::chrono::steady_clock::time_point batDauDemGio(){
    return std::chrono::steady_clock::now();
}
auto batDau=batDauDemGio;
long long tinhThoiGianDaQua(
    std::chrono::steady_clock::time_point batDau
){
    auto hienTai=std::chrono::steady_clock::now();
    auto khoangThoiGian=
    std::chrono::duration_cast<std::chrono::seconds>(
        hienTai-batDau
    );
    return khoangThoiGian.count();
}
long long tinhThoiGianConLai(
    std::chrono::steady_clock::time_point batDau,
    long long tongThoiGian
){
    long long daQua=tinhThoiGianDaQua(batDau);
    long long conLai=tongThoiGian-daQua;
    if(conLai<0){
        conLai=0;
    }
    return conLai;
}
bool hetThoiGian(
    std::chrono::steady_clock::time_point batDau,
    long long tongThoiGian
) {
    return tinhThoiGianConLai(batDau, tongThoiGian) <= 0;
}
#include <iostream>
#include <thread>
#include <chrono>

#include "ExamTimer.h"

using namespace std;

int main() {

    // Tong thoi gian test: 5 giay
    long long tongThoiGian = 5;

    // Bat dau dem gio
    auto batDau = batDauDemGio();

    cout << "Bat dau dem gio..." << endl;

    // Cho 2 giay
    this_thread::sleep_for(chrono::seconds(2));

    cout << "Da qua: "
         << tinhThoiGianDaQua(batDau)
         << " giay" << endl;

    cout << "Con lai: "
         << tinhThoiGianConLai(batDau, tongThoiGian)
         << " giay" << endl;

    if (hetThoiGian(batDau, tongThoiGian)) {
        cout << "Het gio!" << endl;
    }
    else {
        cout << "Chua het gio!" << endl;
    }


    // Cho them 4 giay
    this_thread::sleep_for(chrono::seconds(4));

    cout << "\nSau khi doi them 4 giay:" << endl;

    cout << "Da qua: "
         << tinhThoiGianDaQua(batDau)
         << " giay" << endl;

    cout << "Con lai: "
         << tinhThoiGianConLai(batDau, tongThoiGian)
         << " giay" << endl;

    if (hetThoiGian(batDau, tongThoiGian)) {
        cout << "Het gio!" << endl;
    }
    else {
        cout << "Chua het gio!" << endl;
    }

    return 0;
}