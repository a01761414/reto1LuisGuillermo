#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <string>
#include <vector>
using namespace std;


vector<int> funcLPS(string &p){ // Longest prefix function
    int m = p.length(); // we save the length of the pattern to use it later.

    vector<int> lps(m,0); // we initialize a vector or array full of zeros with the same size as our pattern.

    int i = 1, // our iterators, i is bigger so we can compare the index we are on(j) with the next index(i).
        j = 0;

    while(i < m){ // we determine our limit which is the length of the pattern.
        if(p[i] == p[j]){ // then we compare as I said.
            lps[i] = j+1; // if the condition is true we assign a number that constantly increases if this condition keeps entering.
            i++;
            j++;
        }else if(j > 0){ // if the past condition is not true then we check that j is bigger than 0.
            j = lps[j-1]; // if it's still 0 then we assign it the value of the previous value on the array we are completing.
        }else{ // if none of the above statements is done, we do the next steps.
            lps[i] = 0; // we assign a zero value to the array we are completing.
            i++;
        }
    }
    return lps; // when we finish the while we return that array, it could be full of zeros. Actually in all our cases its full of zeros.
}

bool kmpBool(string &t, string &p){ // knuth-morris-pratt function that returns true or false if there is a substring inside a text.
    int m = p.length(), n = t.length();
    vector<int> lps = funcLPS(p);
    int i = 0,
        j = 0;

    while(i < n){

        if(t[i] == p[j]){
            i++;
            j++;
        }

        if(j == m) {
            return true;
        }else if(i < n && p[j] != t[i]){
            if (j != 0) {
                j = lps[j - 1];
            } else {
                i++;
            }
        }
    }
    return false;
}

int kmpPos(string &t, string &p){ // knuth-morris-pratt function that returns the index in which the substring is found.
    int m = p.length(), n = t.length();
    vector<int> lps = funcLPS(p);
    int i = 0,
        j = 0;

    while(i < n){
        if(p[j] == t[i]){
            if(j == m-1){
                return i-m+1;
            }
            i++;
            j++;
        }else if(j > 0){
            j = lps[j+1];
        }else{
            i++;
        }
    }

}

vector<int> expandPal(string& t, int left, int right){
    while(left >= 0 && right < t.length() && t[left] == t[right]){
        left--;
        right++;
    }
    vector<int> palindrome = {right - left - 1, left + 1, right - 1};
    return palindrome;
}

vector<int> maxPal(vector<int> palOdd, vector<int> palEven, vector<int> longPal){
    if(palOdd[0] > longPal[0]){
        longPal = palOdd;
    }
    if(palEven[0] > longPal[0]){
        longPal = palEven;
    }
    return longPal;
}

vector<int> longestPalindrome(string& t){
    int n = t.length();
    vector<int> longPal(3,0);
    for(int i = 0; i < n; i++){
        vector<int> palOdd = expandPal(t, i, i);
        vector<int> palEven = expandPal(t, i, i+1);
        longPal = maxPal(palOdd, palEven, longPal);
    }
    return longPal;
}

string readFile(string filePath) {
    ifstream file(filePath);
    if(!file.is_open()){
        cerr << "failed to open the file: " << filePath << endl;
    }
    string text;
    stringstream buffer;
    buffer << file.rdbuf();  // Read all the content in the file
    text = buffer.str();  // Convert the content of the buffer into a string
    file.close();
    return text;
}


int main() { // Main function
    // Read the transmission1 file
    string filePath1 = "transmission1.txt";
    string t1 = readFile(filePath1);
    t1.erase(remove(t1.begin(),t1.end(), '\n'), t1.end()); // this is a preventive function in which we convert the transmission string we made into a single line string

    // Read the transmission2 file
    string filePath2 = "transmission2.txt";
    string t2 = readFile(filePath2);
    t2.erase(remove(t2.begin(),t2.end(), '\n'), t2.end());

    // Read the first mcode file
    string filePath3 = "mcode1.txt";
    string m1 = readFile(filePath3);

    // Read the second mcode file
    string filePath4 = "mcode2.txt";
    string m2 = readFile(filePath4);

    // Read the third mcode file
    string filePath5 = "mcode3.txt";
    string m3 = readFile(filePath5);


    // First part of the project; Return a "true/false" of there is a mcode inside a transmission
    //                            followed by a space and the position where it is.
    cout << "transmission1 comparison with mcodes: \n";
    cout << "mcode1: \n";
    if(kmpBool(t1, m1)){ // if statement to determine whether the mcode is found in the transmission, we use our bool kmp function.
        cout << "true" << " pos:" <<kmpPos(t1,m1) << endl << endl; // if it's true we call our index kmp funciton to determine in which index it is.
    }else{
        cout << "false" << endl << endl; // if there is no mcode inside the transmission we just return a false message.
    }

    cout << "mcode2: \n"; // we do it for every mcode in both transmissions.
    if(kmpBool(t1, m2)){
        cout << "true" << " pos:" << kmpPos(t1,m2) << endl << endl;
    }else{
        cout << "false" << endl << endl;
    }

    cout << "mcode3: \n";
    if(kmpBool(t1, m3)){
        cout << "true" << " pos:" << kmpPos(t1,m3) << endl << endl;
    }else{
        cout << "false" << endl << endl;
    }

    cout << "transmission2 comparison with mcodes: \n";
    cout << "mcode1: \n";
    if(kmpBool(t2, m1)){
        cout << "true" << " pos:" <<kmpPos(t2,m1) << endl << endl;
    }else{
        cout << "false" << endl << endl;
    }

    cout << "mcode2: \n";
    if(kmpBool(t2, m2)){
        cout << "true" << " pos:" << kmpPos(t2,m2) << endl << endl;
    }else{
        cout << "false" << endl << endl;
    }

    cout << "mcode3: \n";
    if(kmpBool(t2, m3)){
        cout << "true" << " pos:" << kmpPos(t2,m3) << endl << endl;
    }else{
        cout << "false" << endl << endl;
    }


    // Second part of the project; Return the initial and ending position of the longest palindromic string
    cout << "Position of the longest palindromic string in transmission1: \n";
    vector<int> palT1 = longestPalindrome(t1);
    cout << palT1[1] << " " << palT1[2] << endl << endl;

    cout << "Position of the longest palindromic string in transmission2: \n";
    vector<int> palT2 = longestPalindrome(t2);
    cout<< palT2[1] << " " << palT2[2] << endl << endl;

    return 0;
}
