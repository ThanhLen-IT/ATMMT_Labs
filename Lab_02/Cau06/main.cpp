#include <iostream>
#include <vector>
#include <random>
#include <string>
#include <algorithm>
#include <cstdint>

#ifdef _MSC_VER
#include <intrin.h>
#endif

using namespace std;

typedef unsigned __int64 uint64;

// --- PHẦN 1: CẤU TRÚC 128-BIT ĐỂ XỬ LÝ SỐ MERSENNE 2^89-1 ---

struct Uint128 {
    uint64 hi, lo;

    bool operator<(const Uint128& other) const {
        if (hi != other.hi) return hi < other.hi;
        return lo < other.lo;
    }

    bool operator==(const Uint128& other) const {
        return hi == other.hi && lo == other.lo;
    }

    Uint128 operator-(uint64 val) const {
        Uint128 res = *this;
        if (res.lo < val) res.hi--;
        res.lo -= val;
        return res;
    }
};

// Hàm in số 128-bit ra màn hình
void printUint128(Uint128 n) {
    if (n.hi == 0 && n.lo == 0) { cout << "0"; return; }
    string s = "";
    Uint128 temp = n;
    while (temp.hi > 0 || temp.lo > 0) {
        uint64 rem = 0;
        uint64 newHi = temp.hi / 10;
        uint64 remHi = temp.hi % 10;
        uint64 newLo = _udiv128(remHi, temp.lo, 10, &rem);
        s += (char)('0' + rem);
        temp.hi = newHi; temp.lo = newLo;
    }
    reverse(s.begin(), s.end());
    cout << s;
}

// Các hàm toán học 128-bit hỗ trợ Miller-Rabin cho số lớn
Uint128 add_mod_128(Uint128 a, Uint128 b, Uint128 m) {
    Uint128 res;
    res.lo = a.lo + b.lo;
    res.hi = a.hi + b.hi + (res.lo < a.lo ? 1 : 0);
    if (!(res < m)) {
        uint64 borrow = (res.lo < m.lo ? 1 : 0);
        res.lo -= m.lo;
        res.hi -= (m.hi + borrow);
    }
    return res;
}

Uint128 mul_mod_128(Uint128 a, Uint128 b, Uint128 m) {
    Uint128 res = { 0, 0 };
    while (b.hi > 0 || b.lo > 0) {
        if (b.lo & 1) res = add_mod_128(res, a, m);
        a = add_mod_128(a, a, m);
        uint64 carry = (b.hi & 1);
        b.hi >>= 1; b.lo = (b.lo >> 1) | (carry << 63);
    }
    return res;
}

Uint128 pow_mod_128(Uint128 base, Uint128 exp, Uint128 mod) {
    Uint128 res = { 0, 1 };
    while (exp.hi > 0 || exp.lo > 0) {
        if (exp.lo & 1) res = mul_mod_128(res, base, mod);
        base = mul_mod_128(base, base, mod);
        uint64 carry = (exp.hi & 1);
        exp.hi >>= 1; exp.lo = (exp.lo >> 1) | (carry << 63);
    }
    return res;
}

bool is_prime_128(Uint128 n) {
    if (n.hi == 0 && n.lo < 2) return false;
    if (n.hi == 0 && (n.lo == 2 || n.lo == 3)) return true;
    if (n.lo % 2 == 0) return false;
    Uint128 d = n - 1; int r = 0;
    while (d.lo % 2 == 0) {
        uint64 carry = (d.hi & 1);
        d.hi >>= 1; d.lo = (d.lo >> 1) | (carry << 63);
        r++;
    }
    static const vector<uint64> bases = { 2, 3, 5, 7, 11, 13, 17, 19, 23 };
    for (uint64 a_val : bases) {
        Uint128 a = { 0, a_val };
        if (!(a < n)) break;
        Uint128 x = pow_mod_128(a, d, n);
        if (x == (Uint128{0, 1}) || x == (n - 1)) continue;
        bool composite = true;
        for (int i = 0; i < r - 1; i++) {
            x = mul_mod_128(x, x, n);
            if (x == (n - 1)) { composite = false; break; }
        }
        if (composite) return false;
    }
    return true;
}

// --- PHẦN 2: CÁC HÀM 64-BIT NGUYÊN BẢN CỦA BẠN ---

static uint64 mul_mod(uint64 a, uint64 b, uint64 mod) {
#if defined(__SIZEOF_INT128__) || defined(__GNUC__) || defined(__clang__)
    return (uint64)((__int128)a * b % mod);
#elif defined(_MSC_VER)
    unsigned long long high;
    unsigned long long low = _umul128(a, b, &high);
    unsigned long long rem = 0;
    (void)_udiv128(high, low, mod, &rem);
    return (uint64)rem;
#else
    uint64 result = 0; a %= mod;
    while (b) {
        if (b & 1) {
            if (result >= mod - a) result = result + a - mod;
            else result = result + a;
        }
        if (a >= mod - a) a = a + a - mod;
        else a = a + a;
        b >>= 1;
    }
    return result % mod;
#endif
}

uint64 power_modulo(uint64 base, uint64 exp, uint64 mod) {
    uint64 res = 1; base %= mod;
    while (exp > 0) {
        if (exp % 2 == 1) res = mul_mod(res, base, mod);
        base = mul_mod(base, base, mod);
        exp /= 2;
    }
    return res;
}

uint64 gcd_euclid(uint64 a, uint64 b) {
    while (b) { a %= b; swap(a, b); }
    return a;
}

bool is_prime_miller_rabin(uint64 n, int k = 10) {
    if (n < 2) return false;
    if (n == 2 || n == 3) return true;
    if (n % 2 == 0) return false;
    uint64 d = n - 1; int r = 0;
    while (d % 2 == 0) { d /= 2; r++; }
    static const vector<uint64> bases = { 2, 3, 5, 7, 11, 13, 17, 19, 23 };
    for (uint64 a : bases) {
        if (n <= a) break;
        uint64 x = power_modulo(a, d, n);
        if (x == 1 || x == n - 1) continue;
        bool composite = true;
        for (int i = 0; i < r - 1; i++) {
            x = mul_mod(x, x, n);
            if (x == n - 1) { composite = false; break; }
        }
        if (composite) return false;
    }
    return true;
}

// --- PHẦN 3: HÀM MAIN THỰC HIỆN ĐẦY ĐỦ CÁC YÊU CẦU ---

int main() {
    // 1. Tạo số nguyên tố 8, 16, 64 bits [cite: 383]
    cout << "--- 1. Tao so nguyen to ngau nhien ---" << endl;
    random_device rd; mt19937_64 gen(rd());
    auto gen_prime = [&](int bits) {
        uint64 min_v = (bits == 64) ? 0x8000000000000000ULL : (1ULL << (bits - 1));
        uint64 max_v = (bits == 64) ? 0xFFFFFFFFFFFFFFFFULL : (1ULL << bits) - 1;
        uniform_int_distribution<uint64> dis(min_v, max_v);
        while (true) {
            uint64 p = dis(gen) | 1;
            if (is_prime_miller_rabin(p)) return p;
        }
    };
    cout << "8-bits: " << gen_prime(8) << endl;
    cout << "16-bits: " << gen_prime(16) << endl;
    cout << "64-bits: " << gen_prime(64) << endl;

    // 2. Tìm 10 số nguyên tố lớn nhất < M10 (2^89 - 1) 
    cout << "\n--- 2. 10 so nguyen to lon nhat < M10 (2^89 - 1) ---" << endl;
    Uint128 m10 = { (1ULL << (89 - 64)) - 1, 0xFFFFFFFFFFFFFFFFULL }; // 2^89 - 1
    int count = 0; Uint128 curr = m10 - 2;
    while (count < 10) {
        if (is_prime_128(curr)) {
            cout << "#" << ++count << ": "; printUint128(curr); cout << endl;
        }
        curr = curr - 2;
    }

    // 3. Kiểm tra số nguyên tùy ý < 2^89 - 1 [cite: 385]
    cout << "\n--- 3. Kiem tra so nguyen tuy y < 2^89 - 1 ---" << endl;
    Uint128 testN = { 0, 24520949 }; // Ví dụ: Student ID 24520949
    cout << "Kiem tra so: "; printUint128(testN);
    if (is_prime_128(testN)) cout << " la so nguyen to." << endl;
    else cout << " khong phai la so nguyen to." << endl;

    // 4. GCD của 2 số lớn [cite: 386]
    cout << "\n--- 4. GCD ---" << endl;
    cout << "GCD(123456789012345, 987654321098765) = " << gcd_euclid(123456789012345, 987654321098765) << endl;

    // 5. Lũy thừa modulo x > 40 [cite: 387, 388]
    cout << "\n--- 5. Luy thua modulo (7^40 mod 19) ---" << endl;
    cout << "Ket qua: " << power_modulo(7, 40, 19) << endl;

    return 0;
}