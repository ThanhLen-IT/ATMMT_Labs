#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <cmath>
#include <random>
#include <algorithm>
#include <cctype>
#include <filesystem>
using namespace std;

double quadScore[26][26][26][26];
double floorScore;

void loadQuadgrams(string filename)
{
    ifstream file(filename);
    if (!file)
    {
        cout << "Khong mo duoc file quadgrams.txt\n";
        exit(1);
    }
    string quad;
    double count, total = 0;
    map<string, double> freq;
    while (file >> quad >> count)
    {
        freq[quad] = count;
        total += count;
    }
    floorScore = log10(0.01 / total);
    for (int a = 0; a < 26; a++)
        for (int b = 0; b < 26; b++)
            for (int c = 0; c < 26; c++)
                for (int d = 0; d < 26; d++)
                    quadScore[a][b][c][d] = floorScore;
    for (auto& p : freq)
    {
        string q = p.first;
        quadScore[q[0] - 'A'][q[1] - 'A'][q[2] - 'A'][q[3] - 'A']
            = log10(p.second / total);
    }
    cout << "Load quadgrams OK!\n";
}

void decrypt(const vector<int>& cipher, const int key[], vector<int>& out)
{
    for (int i = 0; i < cipher.size(); i++)
        out[i] = key[cipher[i]];
}

double scoreText(const vector<int>& text)
{
    double score = 0;
    for (int i = 0; i + 3 < text.size(); i++)
    {
        score += quadScore[
            text[i]][text[i + 1]][text[i + 2]][text[i + 3]];
    }
    return score;
}

string toString(const vector<int>& v)
{
    string s;
    for (int x : v) s += char(x + 'A');
    return s;
}

string solve(const vector<int>& cipher)
{
    random_device rd;
    mt19937 rng(rd());
    int key[26], bestKey[26];
    for (int i = 0; i < 26; i++) key[i] = i;
    shuffle(key, key + 26, rng);
    vector<int> text(cipher.size());
    decrypt(cipher, key, text);
    double bestScore = scoreText(text);
    memcpy(bestKey, key, sizeof(key));
    int ITER = 200000;
    for (int it = 0; it < ITER; it++)
    {
        int a = rng() % 26;
        int b = rng() % 26;
        swap(key[a], key[b]);
        decrypt(cipher, key, text);
        double sc = scoreText(text);
        if (sc > bestScore)
        {
            bestScore = sc;
            memcpy(bestKey, key, sizeof(key));
        }
        else
        {
            swap(key[a], key[b]);
        }
        if (it % 50000 == 0)
            cout << "Iter: " << it << " Score: " << bestScore << endl;
    }
    decrypt(cipher, bestKey, text);
    return toString(text);
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    loadQuadgrams("quadgrams.txt");
    cout << "\nNhap ciphertext:\n";
    string input;
    getline(cin, input);
    string original = input;
    vector<int> cipher;
    vector<int> pos;
    for (int i = 0; i < input.size(); i++)
    {
        if (isalpha(input[i]))
        {
            cipher.push_back(toupper(input[i]) - 'A');
            pos.push_back(i);
        }
    }
    string decoded = solve(cipher);
    string result = original;
    int idx = 0;

    for (int i = 0; i < result.size(); i++)
    {
        if (isalpha(result[i]))
        {
            result[i] = decoded[idx++];
        }
    }
    cout << "\n=== KET QUA ===\n";
    cout << result << endl;
    return 0;
}