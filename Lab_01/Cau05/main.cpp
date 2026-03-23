#include <iostream>
#include <string>
#include <cctype>

using namespace std;

class VigenereCipher {
public:
    //1. Chuẩn hóa khóa (Chỉ lấy chữ cái, chuyển về chữ hoa)

    string normalizeKey(string key) {
        string output = "";
        for (char c : key) {
            if (isalpha(c)) output += toupper(c);
        }
        return output.empty() ? "A" : output;
    }


    //2. Sinh chuỗi khóa lặp (Key Stream) đồng bộ với bản rõ

    string generateKeyStream(string text, string key) {
        string keyStream = "";
        string cleanKey = normalizeKey(key);
        int j = 0;

        for (int i = 0; i < text.length(); i++) {
            if (isalpha(text[i])) {
                keyStream += cleanKey[j % cleanKey.length()];
                j++;
            }
            else {
                keyStream += text[i]; // Giữ nguyên vị trí để khớp với text
            }
        }
        return keyStream;
    }

    //3.1. Hàm mã hóa

    string encrypt(string plaintext, string keyStream) {
        string ciphertext = "";
        for (int i = 0; i < plaintext.length(); i++) {
            if (isalpha(plaintext[i])) {
                char base = isupper(plaintext[i]) ? 'A' : 'a';
                // Công thức: Ci = (pi + ki) mod 26
                int p = plaintext[i] - base;
                int k = keyStream[i] - 'A';
                ciphertext += (char)((p + k) % 26 + base);
            }
            else {
                ciphertext += plaintext[i];
            }
        }
        return ciphertext;
    }

    //3.2. Hàm giải mã

    string decrypt(string ciphertext, string keyStream) {
        string plaintext = "";
        for (int i = 0; i < ciphertext.length(); i++) {
            if (isalpha(ciphertext[i])) {
                char base = isupper(ciphertext[i]) ? 'A' : 'a';
                // Công thức: pi = (Ci - ki + 26) mod 26
                int c = ciphertext[i] - base;
                int k = keyStream[i] - 'A';
                plaintext += (char)((c - k + 26) % 26 + base);
            }
            else {
                plaintext += ciphertext[i];
            }
        }
        return plaintext;
    }
};

int main() {
    VigenereCipher vc;
    string text, key, keyStream;
    int choice;

    cout << "VIGENERE\n";
    cout << "1. Ma hoa (Encrypt)\n2. Giai ma (Decrypt)\nChon: ";
    cin >> choice;
    cin.ignore();

    cout << "Nhap khoa: "; getline(cin, key);
    cout << "Nhap van ban: "; getline(cin, text);

    keyStream = vc.generateKeyStream(text, key);

    if (choice == 1) {
        cout << "\n--- TIEN TRINH MA HOA ---" << endl;
        //cout << "Key Stream: " << endl << keyStream << endl;
        cout << "Ket qua:    " <<  endl << vc.encrypt(text, keyStream) << endl;
    }
    else {
        cout << "\n--- TIEN TRINH GIAI MA ---" << endl;
        //cout << "Key Stream: " << keyStream << endl;
        cout << "Ket qua:    " << vc.decrypt(text, keyStream) << endl;
    }

    return 0;
}