#include <iostream>
#include <string>

using namespace std;

int modInverse(int a, int m) {
    for (int x = 1; x < m; x++)
        if (((a % m) * (x % m)) % m == 1) return x;
    return 1;
}

string encryptAffine(string p, int a, int b) {
    string c = "";
    for (char& ch : p) {
        if (isalpha(ch)) {
            char base = isupper(ch) ? 'A' : 'a';
            c += (char)((a * (ch - base) + b) % 26 + base);
        }
        else c += ch;
    }
    return c;
}

string decryptAffine(string c, int a, int b) {
    string p = "";
    int a_inv = modInverse(a, 26);
    for (char& ch : c) {
        if (isalpha(ch)) {
            char base = isupper(ch) ? 'A' : 'a';
            int val = (a_inv * (ch - base - b + 26)) % 26;
            p += (char)(val + base);
        }
        else p += ch;
    }
    return p;
}

int main() {
    int a = 5, b = 8;
    string plaintext = "Hello UIT";

    string cipher = encryptAffine(plaintext, a, b);
    cout << "Ciphertext: " << cipher << endl;
    cout << "Decrypted: " << decryptAffine(cipher, a, b) << endl;

    return 0;
}