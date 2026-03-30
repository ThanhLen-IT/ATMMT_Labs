#include <iostream>
#include <string>
#include <vector>

using namespace std;

string aes_process(string block, string key) {
    string out = block;
    for (int i = 0; i < block.length(); i++) {
        out[i] = block[i] ^ key[i % key.length()];
    }
    return out;
}

void check_errors(const string& original, const string& decrypted) {
    int corrupted_blocks = 0;
    for (size_t i = 0; i < original.length(); i += 16) {
        bool is_corrupted = false;
        for (size_t j = 0; j < 16 && (i + j) < original.length(); j++) {
            if (original[i + j] != decrypted[i + j]) {
                is_corrupted = true;
                break;
            }
        }
        if (is_corrupted) {
            corrupted_blocks++;
            cout << "Block " << (i / 16) + 1 << ": BI HONG!" << endl;
        }
    }
    cout << "==> Tong so khoi bi anh huong: " << corrupted_blocks << endl;
}

int main() {
    string plaintext(992, 'A');
    string key = "1234567890123456";
    string iv = "initialvector123";

    cout << "\n--- THI NGHIEM ECB ---" << endl;
    vector<string> ecb_cipher;
    for (int i = 0; i < plaintext.length(); i += 16) {
        ecb_cipher.push_back(aes_process(plaintext.substr(i, 16), key));
    }

    ecb_cipher[1][9] ^= 0x01;

    string ecb_decrypted = "";
    for (const auto& block : ecb_cipher) {
        ecb_decrypted += aes_process(block, key);
    }
    check_errors(plaintext, ecb_decrypted);

    cout << "\n--- THI NGHIEM CBC ---" << endl;
    vector<string> cbc_cipher;
    string prev_cipher = iv;

    for (int i = 0; i < plaintext.length(); i += 16) {
        string block = plaintext.substr(i, 16);
        for (int j = 0; j < 16; j++) block[j] ^= prev_cipher[j];
        string encrypted = aes_process(block, key);
        cbc_cipher.push_back(encrypted);
        prev_cipher = encrypted;
    }

    cbc_cipher[1][9] ^= 0x01;

    string cbc_decrypted = "";
    string prev_to_decrypt = iv;
    for (size_t i = 0; i < cbc_cipher.size(); i++) {
        string decrypted = aes_process(cbc_cipher[i], key);
        for (int j = 0; j < 16; j++) decrypted[j] ^= prev_to_decrypt[j];
        cbc_decrypted += decrypted;
        prev_to_decrypt = cbc_cipher[i];
    }
    check_errors(plaintext, cbc_decrypted);

    return 0;
}