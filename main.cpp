#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <string>
#include <vector>
using namespace std;

vector<int> funcLPS(string &p) {
    int m = p.length();
    vector<int> lps(m, 0);
    int i = 1, j = 0;

    while (i < m) {
        if (p[i] == p[j]) {
            lps[i] = j + 1;
            i++;
            j++;
        } else if (j > 0) {
            j = lps[j - 1];
        } else {
            lps[i] = 0;
            i++;
        }
    }
    return lps;
}

bool kmpBool(string &t, string &p) {
    int m = p.length(), n = t.length();
    vector<int> lps = funcLPS(p);
    int i = 0, j = 0;

    while (i < n) {
        if (t[i] == p[j]) {
            i++;
            j++;
        }

        if (j == m) {
            return true;
        } else if (i < n && p[j] != t[i]) {
            if (j != 0) {
                j = lps[j - 1];
            } else {
                i++;
            }
        }
    }
    return false;
}

int kmpPos(string &t, string &p) {
    int m = p.length(), n = t.length();
    vector<int> lps = funcLPS(p);
    int i = 0, j = 0;

    while (i < n) {
        if (p[j] == t[i]) {
            if (j == m - 1) {
                return i - m + 1;
            }
            i++;
            j++;
        } else if (j > 0) {
            j = lps[j - 1];
        } else {
            i++;
        }
    }
    return -1;
}

vector<int> expandPal(string& t, int left, int right) {
    while (left >= 0 && right < t.length() && t[left] == t[right]) {
        left--;
        right++;
    }
    vector<int> palindrome;
    palindrome.push_back(right - left - 1);
    palindrome.push_back(left + 1);
    palindrome.push_back(right - 1);
    return palindrome;
}

vector<int> maxPal(vector<int> palOdd, vector<int> palEven, vector<int> longPal) {
    if (palOdd[0] > longPal[0]) {
        longPal = palOdd;
    }
    if (palEven[0] > longPal[0]) {
        longPal = palEven;
    }
    return longPal;
}

vector<int> longestPalindrome(string& t) {
    int n = t.length();
    vector<int> longPal(3, 0);
    for (int i = 0; i < n; i++) {
        vector<int> palOdd = expandPal(t, i, i);
        vector<int> palEven = expandPal(t, i, i + 1);
        longPal = maxPal(palOdd, palEven, longPal);
    }
    return longPal;
}

string readFile(string filePath) {
    ifstream file(filePath);
    if (!file.is_open()) {
        cerr << "Failed to open the file: " << filePath << endl;
        return "";
    }
    string text;
    stringstream buffer;
    buffer << file.rdbuf();
    text = buffer.str();
    file.close();
    return text;
}

pair<int, int> longestCommonSubstring(const string &s1, const string &s2) {
    int n = s1.length();
    int m = s2.length();
    vector<vector<int> > dp(n + 1, vector<int>(m + 1, 0));
    int length = 0, endPos = 0;

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            if (s1[i - 1] == s2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
                if (dp[i][j] > length) {
                    length = dp[i][j];
                    endPos = i - 1;
                }
            }
        }
    }

    int startPos = endPos - length + 1;
    return make_pair(startPos + 1, endPos + 1); // Convertir a base 1
}

int main() {
    string filePath1 = "transmission1.txt";
    string t1 = readFile(filePath1);
    t1.erase(remove(t1.begin(), t1.end(), '\n'), t1.end());

    string filePath2 = "transmission2.txt";
    string t2 = readFile(filePath2);
    t2.erase(remove(t2.begin(), t2.end(), '\n'), t2.end());

    string filePath3 = "mcode1.txt";
    string m1 = readFile(filePath3);

    string filePath4 = "mcode2.txt";
    string m2 = readFile(filePath4);

    string filePath5 = "mcode3.txt";
    string m3 = readFile(filePath5);

    cout << "transmission1 comparison with mcodes: \n";
    cout << "mcode1: \n";
    if (kmpBool(t1, m1)) {
        cout << "true" << " pos:" << kmpPos(t1, m1) << endl << endl;
    } else {
        cout << "false" << endl << endl;
    }

    cout << "mcode2: \n";
    if (kmpBool(t1, m2)) {
        cout << "true" << " pos:" << kmpPos(t1, m2) << endl << endl;
    } else {
        cout << "false" << endl << endl;
    }

    cout << "mcode3: \n";
    if (kmpBool(t1, m3)) {
        cout << "true" << " pos:" << kmpPos(t1, m3) << endl << endl;
    } else {
        cout << "false" << endl << endl;
    }

    cout << "transmission2 comparison with mcodes: \n";
    cout << "mcode1: \n";
    if (kmpBool(t2, m1)) {
        cout << "true" << " pos:" << kmpPos(t2, m1) << endl << endl;
    } else {
        cout << "false" << endl << endl;
    }

    cout << "mcode2: \n";
    if (kmpBool(t2, m2)) {
        cout << "true" << " pos:" << kmpPos(t2, m2) << endl << endl;
    } else {
        cout << "false" << endl << endl;
    }

    cout << "mcode3: \n";
    if (kmpBool(t2, m3)) {
        cout << "true" << " pos:" << kmpPos(t2, m3) << endl << endl;
    } else {
        cout << "false" << endl << endl;
    }

    cout << "Position of the longest palindromic string in transmission1: \n";
    vector<int> palT1 = longestPalindrome(t1);
    cout << palT1[1] << " " << palT1[2] << endl << endl;

    cout << "Position of the longest palindromic string in transmission2: \n";
    vector<int> palT2 = longestPalindrome(t2);
    cout << palT2[1] << " " << palT2[2] << endl << endl;

    cout << "Position of the longest common substring in transmissions: \n";
    pair<int, int> common = longestCommonSubstring(t1, t2);
    cout << common.first << " " << common.second << endl;


    string commonSubstring = t1.substr(common.first - 1, common.second - common.first + 1);
    cout << "Longest common substring: " << commonSubstring << endl;

    return 0;
}
