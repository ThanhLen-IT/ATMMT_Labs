#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

char matrix5x5[5][5];

string normalize(string s)
{
    string res = "";
    for (char c : s)
    {
        if (isalpha(c))
        {
            c = toupper(c);
            if (c == 'J') c = 'I';
            res += c;
        }
    }
    return res;
}

void createMatrix(string key)
{
    bool used[26] = { false };
    key = normalize(key);
    string temp = "";
    for (char c : key)
    {
        if (!used[c - 'A'])
        {
            temp += c;
            used[c - 'A'] = true;
        }
    }
    for (char c = 'A'; c <= 'Z'; c++)
    {
        if (c == 'J') continue;
        if (!used[c - 'A'])
        {
            temp += c;
            used[c - 'A'] = true;
        }
    }
    int k = 0;
    for (int i = 0; i < 5; i++)
        for (int j = 0; j < 5; j++)
            matrix5x5[i][j] = temp[k++];
}

void printMatrix()
{
    cout << "\nPlayfair Matrix 5x5:\n";
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++)
            cout << matrix5x5[i][j] << " ";
        cout << endl;
    }
}

void findPos(char c, int& r, int& c2)
{
    for (int i = 0; i < 5; i++)
        for (int j = 0; j < 5; j++)
            if (matrix5x5[i][j] == c)
            {
                r = i; c2 = j;
                return;
            }
}

vector<string> makePairs(string text)
{
    vector<string> pairs;
    for (int i = 0; i < text.length(); i++)
    {
        char a = text[i];
        char b;
        if (i + 1 < text.length())
            b = text[i + 1];
        else
            b = 'X';
        if (a == b)
        {
            pairs.push_back(string() + a + 'X');
        }
        else
        {
            pairs.push_back(string() + a + b);
            i++;
        }
    }
    if (pairs.back().length() == 1)
        pairs.back() += 'X';
    return pairs;
}

string formatOutput(string text)
{
    string res = "";
    for (int i = 0; i < text.length(); i++)
    {
        res += text[i];
        if ((i + 1) % 2 == 0 && i != text.length() - 1)
            res += ' ';
    }
    return res;
}

string encrypt(string plaintext)
{
    plaintext = normalize(plaintext);
    vector<string> pairs = makePairs(plaintext);
    string cipher = "";
    for (auto p : pairs)
    {
        int r1, c1, r2, c2;
        findPos(p[0], r1, c1);
        findPos(p[1], r2, c2);
        if (r1 == r2)
        {
            cipher += matrix5x5[r1][(c1 + 1) % 5];
            cipher += matrix5x5[r2][(c2 + 1) % 5];
        }
        else if (c1 == c2)
        {
            cipher += matrix5x5[(r1 + 1) % 5][c1];
            cipher += matrix5x5[(r2 + 1) % 5][c2];
        }
        else
        {
            cipher += matrix5x5[r1][c2];
            cipher += matrix5x5[r2][c1];
        }
    }
    return cipher;
}

string decrypt(string cipher)
{
    cipher = normalize(cipher);
    string plain = "";
    for (int i = 0; i < cipher.length(); i += 2)
    {
        int r1, c1, r2, c2;
        findPos(cipher[i], r1, c1);
        findPos(cipher[i + 1], r2, c2);
        if (r1 == r2)
        {
            plain += matrix5x5[r1][(c1 + 4) % 5];
            plain += matrix5x5[r2][(c2 + 4) % 5];
        }
        else if (c1 == c2)
        {
            plain += matrix5x5[(r1 + 4) % 5][c1];
            plain += matrix5x5[(r2 + 4) % 5][c2];
        }
        else
        {
            plain += matrix5x5[r1][c2];
            plain += matrix5x5[r2][c1];
        }
    }
    return plain;
}

int main()
{
    string key, text;
    int choice;
    cout << "===== PLAYFAIR CIPHER =====\n";
    cout << "Nhap key: ";
    getline(cin, key);
    createMatrix(key);
    printMatrix();
    cout << "\n1. Encrypt\n2. Decrypt\nChon: ";
    cin >> choice;
    cin.ignore();
    cout << "Nhap text: ";
    getline(cin, text);
    if (choice == 1)
    {
        string cipher = encrypt(text);
        cout << "\nCiphertext: " << formatOutput(cipher) << endl;
    }
    else
    {
        string plain = decrypt(text);
        cout << "\nPlaintext: " << formatOutput(plain) << endl;
    }
    return 0;
}