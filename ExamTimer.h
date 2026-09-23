#pragma once
#include <chrono>
std::chrono::steady_clock::time_point batDauDemGio();
long long tinhThoiGianDaQua(
    std::chrono::steady_clock::time_point batDau
);
long long tinhThoiGianConLai(
    std::chrono::steady_clock::time_point batDau,
    long long tongThoiGian
);
bool hetThoiGian(
    std::chrono::steady_clock::time_point batDau,
    long long tongThoiGian
);