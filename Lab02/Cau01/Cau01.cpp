#include <iostream>
#include <iomanip>
#include <bitset>
#include <vector>

using namespace std;

unsigned char F_function(unsigned char right, unsigned char subkey) {
    return (right ^ subkey) & 0x0F;
}

void feistel_round(unsigned char& L, unsigned char& R, unsigned char subkey) {
    unsigned char L_old = L;
    unsigned char R_old = R;

    L = R_old;

    R = L_old ^ F_function(R_old, subkey);
}

void track_avalanche(unsigned char msg, unsigned char key) {
    unsigned char L = (msg >> 4) & 0x0F;
    unsigned char R = msg & 0x0F;

    unsigned char subkeys[4];
    subkeys[0] = key & 0x0F;
    subkeys[1] = (key >> 4) & 0x0F;
    subkeys[2] = (key + 1) & 0x0F;
    subkeys[3] = (key + 2) & 0x0F;

    cout << "Khoi tao: L=" << bitset<4>(L) << ", R=" << bitset<4>(R) << endl;

    for (int i = 0; i < 4; ++i) {
        feistel_round(L, R, subkeys[i]);
        cout << "Vong " << (i + 1) << ":    L=" << bitset<4>(L)
            << ", R=" << bitset<4>(R) << endl;
    }
}

int main() {
    unsigned char key = 0x12;

    cout << "--- Ma hoa M1 (0xAB) ---" << endl;
    track_avalanche(0xAB, key);

    cout << "\n--- Ma hoa M2 (0xAC) ---" << endl;
    track_avalanche(0xAC, key);

    return 0;
}