#include <iostream>
#include <string>
#include <map>
#include <iomanip>

using namespace std;

void countFrequency(string text) {
    map<char, int> freq;
    int total = 0;
    for (char c : text) {
        if (isalpha(c)) {
            freq[toupper(c)]++;
            total++;
        }
    }
    cout << "--- Thong ke tan suat xuat hien ---" << endl;
    
    for (map<char, int>::iterator it = freq.begin(); it != freq.end(); ++it) {
        char ch = it->first;
        int count = it->second;
        double p = (double)count / total * 100;
        cout << ch << ": " << fixed << setprecision(2) << p << "%" << endl;
    }
}


int main() {
  
    string cipherText = "PASTE_YOUR_CIPHERTEXT_HERE";

    if (cipherText == "PASTE_YOUR_CIPHERTEXT_HERE") {
        cout << "Vui long paste doan van ban ma hoa vao bien cipherText trong code!" << endl;
    }

    countFrequency(cipherText);

    system("pause");
    return 0;
}