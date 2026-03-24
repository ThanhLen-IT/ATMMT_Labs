#include <iostream>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;

string fake_aes_encrypt(string block, string key) {
    string cipher = block;
    for (int i = 0; i < block.length(); i++) {
        cipher[i] = block[i] ^ key[i % key.length()]; 
    }
    return cipher;
}

string xor_blocks(string block1, string block2) {
    string result = block1;
    for (int i = 0; i < block1.length(); i++) {
        result[i] = block1[i] ^ block2[i];
    }
    return result;
}

void print_hex(string label, string data) {
    cout << label << ": ";
    for (unsigned char c : data) {
        cout << hex << setw(2) << setfill('0') << (int)c << " ";
    }
    cout << dec << endl;
}

int main() {
    string key = "1234567890123456";
    string p_text = "UIT_LAB_UIT_LAB_UIT_LAB_UIT_LAB_";

    string block1 = p_text.substr(0, 16);
    string block2 = p_text.substr(16, 16);

    cout << "--- PHAN TICH CHE DO AES ---" << endl;
    cout << "Ban ro khoi 1: " << block1 << endl;
    cout << "Ban ro khoi 2: " << block2 << endl;
    cout << "----------------------------" << endl;

    string ct_ecb1 = fake_aes_encrypt(block1, key);
    string ct_ecb2 = fake_aes_encrypt(block2, key);

    print_hex("ECB Khoi 1", ct_ecb1);
    print_hex("ECB Khoi 2", ct_ecb2);
    cout << "=> NHAN XET: Hai khoi ban ma giong het nhau!" << endl;
    cout << endl;

   
    string iv = "initialvector123"; 
    string ct_cbc1 = fake_aes_encrypt(xor_blocks(block1, iv), key);

    string ct_cbc2 = fake_aes_encrypt(xor_blocks(block2, ct_cbc1), key);

    print_hex("CBC Khoi 1", ct_cbc1);
    print_hex("CBC Khoi 2", ct_cbc2);
    cout << "=> NHAN XET: Hai khoi ban ma da khac nhau hoan toan!" << endl;

    return 0;
}