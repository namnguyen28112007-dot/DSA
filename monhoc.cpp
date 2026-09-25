#include "monhoc.h"
#include "ExamValidation.h"
#include <iomanip>
#include <iostream>
#include <limits>

namespace {

// Khong nhan chuoi rong, chi co khoang trang, hoac ky tu tach file.
bool hopLeChuoi(const std::string& s) {
    bool coNoiDung = false;
    for (std::size_t i = 0; i < s.size(); i++) {
        char c = s[i];
        if (c == '|' || c == '\r' || c == '\n') return false;
        if (c != ' ' && c != '\t') coNoiDung = true;
    }
    return coNoiDung;
}

bool hopLeCauHoi(const std::string& noiDung,
                const std::string& A, const std::string& B,
                const std::string& C, const std::string& D,
                char dapAn) {
    return hopLeChuoi(noiDung) && hopLeChuoi(A) && hopLeChuoi(B) &&
           hopLeChuoi(C) && hopLeChuoi(D) && kiemTraDapAn(dapAn);
}


void xoaDanhSachCauHoi(CauHoi*& head) {
    while (head) {
        CauHoi* p = head;
        head = head->next;
        delete p;
    }
}

} // namespace

MonHoc* timMonHoc(MonHoc* dsMon, const std::string& maMH) {
    MonHoc* p = dsMon;
    while (p != nullptr) {
        if (p->maMH == maMH) return p;
        p = p->next;
    }
    return nullptr;
}

bool themMonHoc(MonHoc*& dsMon, const std::string& maMH,
                const std::string& tenMH) {
    if (!hopLeChuoi(maMH) || maMH.size() > 15 || !hopLeChuoi(tenMH)) {
        return false;
    }

    // Chen theo ma tang dan de giu thu tu hien thi nhu ban truoc.
    MonHoc* truoc = nullptr;
    MonHoc* p = dsMon;
    while (p != nullptr && p->maMH < maMH) {
        truoc = p;
        p = p->next;
    }
    if (p != nullptr && p->maMH == maMH) return false;

    MonHoc* moi = new MonHoc;
    moi->maMH = maMH;
    moi->tenMH = tenMH;
    moi->dsCHT = nullptr;
    moi->next = p;

    if (truoc == nullptr) dsMon = moi;
    else truoc->next = moi;
    return true;
}

bool suaMonHoc(MonHoc* dsMon, const std::string& maMH,
               const std::string& tenMoi) {
    if (!hopLeChuoi(tenMoi)) return false;
    MonHoc* p = timMonHoc(dsMon, maMH);
    if (p == nullptr) return false;
    p->tenMH = tenMoi;
    return true;
}

bool xoaMonHoc(MonHoc*& dsMon, const std::string& maMH) {
    MonHoc* truoc = nullptr;
    MonHoc* p = dsMon;
    while (p != nullptr && p->maMH != maMH) {
        truoc = p;
        p = p->next;
    }
    if (p == nullptr) return false;

    if (truoc == nullptr) dsMon = p->next;
    else truoc->next = p->next;

    xoaDanhSachCauHoi(p->dsCHT);
    delete p;
    return true;
}

void inDanhSachMonHoc(MonHoc* dsMon) {
    std::cout << std::left
              << std::setw(5) << "STT"
              << std::setw(18) << "MA MON"
              << std::setw(35) << "TEN MON"
              << std::setw(10) << "SO CAU" << '\n';
    std::cout << std::string(68, '-') << '\n';

    int stt = 1;
    for (MonHoc* p = dsMon; p != nullptr; p = p->next) {
        std::cout << std::left
                  << std::setw(5) << stt++
                  << std::setw(18) << p->maMH
                  << std::setw(35) << p->tenMH
                  << std::setw(10) << demCauHoi(p) << '\n';
    }
    if (dsMon == nullptr) std::cout << "Danh sach mon hoc rong.\n";
}

void giaiPhongDanhSachMonHoc(MonHoc*& dsMon) {
    while (dsMon != nullptr) {
        MonHoc* p = dsMon;
        dsMon = dsMon->next;
        xoaDanhSachCauHoi(p->dsCHT);
        delete p;
    }
}

// Giu ten cu de cac cho goi truoc day van bien dich; khong dung cay.
void giaiPhongCayMonHoc(MonHoc*& dsMon) {
    giaiPhongDanhSachMonHoc(dsMon);
}

int demCauHoi(const MonHoc* mh) {
    if (!mh) return 0;
    int count = 0;
    for (CauHoi* p = mh->dsCHT; p; p = p->next) ++count;
    return count;
}

bool chenCauHoiVoiId(MonHoc* mh, int id,
                     const std::string& noiDung,
                     const std::string& A,
                     const std::string& B,
                     const std::string& C,
                     const std::string& D,
                     char dapAn) {
    if (!mh || id <= 0) return false;
    dapAn = chuanHoaDapAn(dapAn);
    if (!hopLeCauHoi(noiDung, A, B, C, D, dapAn)) return false;
    if (timCauHoi(mh, id)) return false;

    CauHoi* node = new CauHoi;
    node->id = id;
    node->noiDung = noiDung;
    node->A = A;
    node->B = B;
    node->C = C;
    node->D = D;
    node->dapAn = dapAn;

    if (!mh->dsCHT) {
        mh->dsCHT = node;
    } else {
        CauHoi* tail = mh->dsCHT;
        while (tail->next) tail = tail->next;
        tail->next = node;
    }
    return true;
}

bool themCauHoi(MonHoc* mh, int& nextQuestionId,
                const std::string& noiDung,
                const std::string& A,
                const std::string& B,
                const std::string& C,
                const std::string& D,
                char dapAn) {
    if (!mh || nextQuestionId <= 0 ||
        nextQuestionId == std::numeric_limits<int>::max()) {
        return false;
    }

    if (!chenCauHoiVoiId(mh, nextQuestionId, noiDung, A, B, C, D, dapAn)) {
        return false;
    }

    nextQuestionId++;
    return true;
}

CauHoi* timCauHoi(MonHoc* mh, int id) {
    if (!mh) return nullptr;
    for (CauHoi* p = mh->dsCHT; p; p = p->next) {
        if (p->id == id) return p;
    }
    return nullptr;
}

bool suaCauHoi(MonHoc* mh, int id,
               const std::string& noiDung,
               const std::string& A,
               const std::string& B,
               const std::string& C,
               const std::string& D,
               char dapAn) {
    dapAn = chuanHoaDapAn(dapAn);
    if (!hopLeCauHoi(noiDung, A, B, C, D, dapAn)) return false;

    CauHoi* q = timCauHoi(mh, id);
    if (!q) return false;
    q->noiDung = noiDung;
    q->A = A;
    q->B = B;
    q->C = C;
    q->D = D;
    q->dapAn = dapAn;
    return true;
}

bool xoaCauHoi(MonHoc* mh, int id) {
    if (!mh) return false;
    CauHoi** pp = &mh->dsCHT;
    while (*pp && (*pp)->id != id) pp = &(*pp)->next;
    if (!*pp) return false;
    CauHoi* old = *pp;
    *pp = old->next;
    delete old;
    return true;
}

void inDanhSachCauHoi(const MonHoc* mh) {
    if (!mh) return;
    if (!mh->dsCHT) {
        std::cout << "Mon hoc chua co cau hoi.\n";
        return;
    }

    int stt = 1;
    for (CauHoi* q = mh->dsCHT; q; q = q->next) {
        std::cout << "\nCau " << stt++ << " - ID " << q->id << "\n";
        std::cout << q->noiDung << '\n';
        std::cout << "A. " << q->A << '\n';
        std::cout << "B. " << q->B << '\n';
        std::cout << "C. " << q->C << '\n';
        std::cout << "D. " << q->D << '\n';
        std::cout << "Dap an: " << q->dapAn << '\n';
    }
}
