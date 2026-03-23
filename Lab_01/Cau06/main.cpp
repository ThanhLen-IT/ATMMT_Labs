#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <cctype>
#include <fstream>
#include <iomanip>

using namespace std;

// Tần suất chữ cái chuẩn của Tiếng Anh
const double ENGLISH_FREQS[26] = {
    0.08167, 0.01492, 0.02782, 0.04253, 0.12702,
    0.02228, 0.02015, 0.06094, 0.06966, 0.00015,
    0.00772, 0.04025, 0.02406, 0.06749, 0.07507,
    0.01929, 0.00095, 0.05987, 0.06327, 0.09056,
    0.02758, 0.00978, 0.02360, 0.00150, 0.01974, 0.00074
};

// Bước 1: Chuẩn hóa bản mã
string cleanText(const string& text) {
    string cleaned = "";
    for (char c : text) {
        if (isalpha(c)) {
            cleaned += tolower(c);
        }
    }
    return cleaned;
}

// Tính Chỉ số trùng hợp (Index of Coincidence - IoC)
double calculateIoC(const string& text) {
    int n = text.length();
    if (n <= 1) return 0.0;

    int freqs[26] = { 0 };
    for (char c : text) {
        freqs[c - 'a']++;
    }

    double ioc = 0.0;
    for (int i = 0; i < 26; i++) {
        ioc += freqs[i] * (freqs[i] - 1);
    }
    return ioc / (n * (n - 1));
}

// Bước 2: Đoán độ dài khóa dựa trên IoC
int guessKeyLength(const string& text, int maxLen = 20) {
    int bestLength = 1;
    double closestDiff = 1e9;

    cout << "\n--- Phan tich Chi so trung hop (IoC) ---\n";
    for (int k = 1; k <= maxLen; k++) {
        double avgIoc = 0.0;
        for (int i = 0; i < k; i++) {
            string column = "";
            for (size_t j = i; j < text.length(); j += k) {
                column += text[j];
            }
            avgIoc += calculateIoC(column);
        }
        avgIoc /= k;

        // In ra các IoC gần với mốc 0.065 của tiếng Anh
        if (abs(avgIoc - 0.065) < 0.015) {
            cout << "Do dai thu nghiem: " << setw(2) << k
                << " | IoC trung binh: " << fixed << setprecision(4) << avgIoc << "\n";
        }

        double diff = abs(avgIoc - 0.065);
        if (diff < closestDiff) {
            closestDiff = diff;
            bestLength = k;
        }
    }
    return bestLength;
}

// Tính thống kê Chi-bình phương
double calculateChiSquared(const string& text) {
    int n = text.length();
    int freqs[26] = { 0 };
    for (char c : text) {
        freqs[c - 'a']++;
    }

    double chiSq = 0.0;
    for (int i = 0; i < 26; i++) {
        double observed = freqs[i];
        double expected = n * ENGLISH_FREQS[i];
        if (expected > 0) {
            chiSq += ((observed - expected) * (observed - expected)) / expected;
        }
    }
    return chiSq;
}

// Bước 3: Tìm chính xác từng ký tự của khóa
string findVigenereKey(const string& text, int keyLength) {
    string key = "";
    for (int i = 0; i < keyLength; i++) {
        string column = "";
        for (size_t j = i; j < text.length(); j += keyLength) {
            column += text[j];
        }

        double minChiSq = 1e9;
        char bestChar = 'a';

        // Thử 26 phép dịch vòng cho mỗi cột
        for (int shift = 0; shift < 26; shift++) {
            string decryptedCol = "";
            for (char c : column) {
                // + 26 để tránh số âm khi chia lấy dư trong C++
                char decChar = ((c - 'a' - shift + 26) % 26) + 'a';
                decryptedCol += decChar;
            }
            double chiSq = calculateChiSquared(decryptedCol);

            if (chiSq < minChiSq) {
                minChiSq = chiSq;
                bestChar = shift + 'a';
            }
        }
        key += bestChar;
    }
    return key;
}

// Bước 4: Giải mã bản mã gốc
string decryptVigenere(const string& ciphertext, const string& key) {
    string plaintext = "";
    int keyIdx = 0;
    int keyLen = key.length();

    for (char c : ciphertext) {
        if (isalpha(c)) {
            char base = islower(c) ? 'a' : 'A';
            int shift = key[keyIdx % keyLen] - 'a';
            char decryptedChar = ((c - base - shift + 26) % 26) + base;
            plaintext += decryptedChar;
            keyIdx++;
        }
        else {
            plaintext += c; // Giữ nguyên khoảng trắng và dấu câu
        }
    }
    return plaintext;
}

int main() {
    cout << "=== CHUONG TRINH PHA MA VIGENERE (CIPHERTEXT-ONLY) ===\n";
    cout << "Ban muon nhap truc tiep (1) hay doc tu file (2)? Nhap 1 hoac 2: ";
    string choice;
    getline(cin, choice);

    string ciphertext = "";

    if (choice == "1") {
        cout << "Vui long nhap hoac dan ban ma (ciphertext) vao day, sau do an Enter:\n";
        getline(cin, ciphertext);
    }
    else {
        cout << "Nhap ten file (VD: ciphertext.txt): ";
        string filename;
        getline(cin, filename);
        ifstream file(filename);
        if (!file.is_open()) {
            cout << "Khong tim thay file hoac khong the mo file!\n";
            return 1;
        }
        string line;
        while (getline(file, line)) {
            ciphertext += line + "\n";
        }
        file.close();
    }

    string cleanedText = cleanText(ciphertext);
    if (cleanedText.length() < 20) {
        cout << "Ban ma qua ngan de phan tich thong ke chinh xac!\n";
        return 1;
    }

    int keyLength = guessKeyLength(cleanedText);
    cout << "\n=> DO DAI KHOA DU DOAN TOT NHAT: " << keyLength << "\n";

    string key = findVigenereKey(cleanedText, keyLength);

    // In hoa key cho dễ nhìn
    string upperKey = key;
    for (char& c : upperKey) c = toupper(c);

    cout << "=> KHOA (KEY) TIM DUOC: " << upperKey << "\n";

    string plaintext = decryptVigenere(ciphertext, key);
    cout << "\n==================================================\n";
    cout << "BAN RO (PLAINTEXT) KET QUA:\n";
    cout << "==================================================\n";
    cout << plaintext << "\n";
    cout << "==================================================\n";

    return 0;
}