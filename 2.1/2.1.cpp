#include <iostream>
#include <string>
#include <vector>

using namespace std;


string caesar(string text, int k, bool encrypt) {
    string result = "";
    if (!encrypt) k = 26 - (k % 26);
    for (char& c : text) {
        if (isalpha(c)) {
            char base = isupper(c) ? 'A' : 'a';
            result += (char)((c - base + k) % 26 + base);
        }
        else {
            result += c; 
        }
    }
    return result;
}

void bruteForce(string ciphertext) {
    cout << "--- Ket qua Brute-force ---" << endl;
    for (int k = 1; k < 26; k++) {
        cout << "Key " << k << ": " << caesar(ciphertext, k, false) << endl;
        cout << "--------------------------" << endl;
    }
}

int main() {
    string cipher = "Max NBM bl t extwbgz bglmbmnmbhg..."; 
    bruteForce(cipher);
    return 0;
}