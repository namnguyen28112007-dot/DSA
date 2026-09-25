#include "monhoc.h"
#include "ExamValidation.h"

#include <iomanip>
#include <iostream>
#include <limits>

namespace {

// Khong nhan chuoi rong, chi co khoang trang, hoac ky tu tach file.
bool hopLeChuoi(const std::string& s) {
    return s.find_first_not_of(" \t\r\n") != std::string::npos &&
           s.find_first_of("|\r\n") == std::string::npos;
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

void inMonHocInorder(MonHoc* root, int& stt) {
    if (!root) return;
    inMonHocInorder(root->left, stt);
    std::cout << std::left
              << std::setw(5) << stt++
              << std::setw(18) << root->maMH
              << std::setw(35) << root->tenMH
              << std::setw(10) << demCauHoi(root) << '\n';
    inMonHocInorder(root->right, stt);
}

} // namespace

MonHoc* timMonHoc(MonHoc* root, const std::string& maMH) {
    while (root) {
        if (maMH == root->maMH) return root;
        root = (maMH < root->maMH) ? root->left : root->right;
    }
    return nullptr;
}

bool themMonHoc(MonHoc*& root, const std::string& maMH, const std::string& tenMH) {
    if (!hopLeChuoi(maMH) || maMH.size() > 15 || !hopLeChuoi(tenMH)) {
        return false;
    }
    if (!root) {
        root = new MonHoc;
        root->maMH = maMH;
        root->tenMH = tenMH;
        return true;
    }
    if (maMH == root->maMH) return false;
    if (maMH < root->maMH) return themMonHoc(root->left, maMH, tenMH);
    return themMonHoc(root->right, maMH, tenMH);
}

bool suaMonHoc(MonHoc* root, const std::string& maMH, const std::string& tenMoi) {
    if (!hopLeChuoi(tenMoi)) return false;
    MonHoc* mh = timMonHoc(root, maMH);
    if (!mh) return false;
    mh->tenMH = tenMoi;
    return true;
}

bool xoaMonHoc(MonHoc*& root, const std::string& maMH) {
    if (!root) return false;

    if (maMH < root->maMH) return xoaMonHoc(root->left, maMH);
    if (maMH > root->maMH) return xoaMonHoc(root->right, maMH);

    // Tim thay node can xoa.
    if (!root->left || !root->right) {
        MonHoc* old = root;
        root = root->left ? root->left : root->right;
        xoaDanhSachCauHoi(old->dsCHT);
        delete old;
        return true;
    }

    // Co 2 con: lay node nho nhat cua cay con phai.
    MonHoc** ppSucc = &root->right;
    while ((*ppSucc)->left) ppSucc = &(*ppSucc)->left;
    MonHoc* succ = *ppSucc;

    // Cac cau hoi cua mon cu se bi xoa cung mon.
    xoaDanhSachCauHoi(root->dsCHT);

    // Chuyen payload cua successor sang node hien tai.
    root->maMH = succ->maMH;
    root->tenMH = succ->tenMH;
    root->dsCHT = succ->dsCHT;
    succ->dsCHT = nullptr;

    // Tach successor khoi cay (successor khong co con trai).
    *ppSucc = succ->right;
    delete succ;
    return true;
}

void inDanhSachMonHoc(MonHoc* root) {
    std::cout << std::left
              << std::setw(5) << "STT"
              << std::setw(18) << "MA MON"
              << std::setw(35) << "TEN MON"
              << std::setw(10) << "SO CAU" << '\n';
    std::cout << std::string(68, '-') << '\n';
    int stt = 1;
    inMonHocInorder(root, stt);
    if (stt == 1) std::cout << "Danh sach mon hoc rong.\n";
}

void giaiPhongCayMonHoc(MonHoc*& root) {
    if (!root) return;
    giaiPhongCayMonHoc(root->left);
    giaiPhongCayMonHoc(root->right);
    xoaDanhSachCauHoi(root->dsCHT);
    delete root;
    root = nullptr;
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
