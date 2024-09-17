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
            i++ , j++;
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
            i++, j++;
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
            i++,j++;
        }else if(j > 0){
            j = lps[j+1];
        }else{
            i++;
        }
    }

}


int main() {


    // Read the transmission1 file
    string filePath1 = " transmission1.txt";
    ifstream file1(filePath1);
    if(!file1.is_open()){
        cerr << "failed to open the file: " << filePath1 << endl;
        return 1;
    }
    string t1;
    stringstream buffer1;
    buffer1 << file1.rdbuf();  // Read all the content in the file
    t1 = buffer1.str();  // Convert the content of the buffer into a string
    file1.close();
    t1.erase(remove(t1.begin(),t1.end(), '\n'), t1.end()); // this is a preventive function in which we convert the transmission string we made into a single line string



    // Read the transmission2 file
    string filePath2 = " transmission2.txt";
    ifstream file2(filePath2);
    if(!file2.is_open()){
        cerr << "failed to open the file: " << filePath2 << endl;
        return 1;
    }
    string t2;
    stringstream buffer2;
    buffer2 << file2.rdbuf();  // Read all the content in the file
    t2 = buffer2.str();  // Convert the content of the buffer into a string
    file2.close();
    t2.erase(remove(t2.begin(),t2.end(), '\n'), t2.end());


    // Read the first mcode file
    string filePath3 = "mcode1.txt";
    ifstream file3(filePath3);
    if(!file3.is_open()){
        cerr << "failed to open the file: " << filePath3 << endl;
        return 1;
    }
    string m1;
    stringstream buffer3;
    buffer3 << file3.rdbuf();  // Read all the content in the file
    m1 = buffer3.str();  // Convert the content of the buffer into a string
    file3.close();



    // Read the second mcode file
    string filePath4 = "mcode2.txt";
    ifstream file4(filePath4);
    if(!file4.is_open()){
        cerr << "failed to open the file: " << filePath4 << endl;
        return 1;
    }
    string m2;
    stringstream buffer4;
    buffer4 << file4.rdbuf();  // Read all the content in the file
    m2 = buffer4.str(); // Convert the content of the buffer into a string
    file4.close();



    // Read the third mcode file
    string filePath5 = "mcode3.txt";
    ifstream file5(filePath5);
    if(!file5.is_open()){
        cerr << "failed to open the file: " << filePath5 << endl;
        return 1;
    }
    string m3;
    stringstream buffer5;
    buffer5 << file5.rdbuf();  // Read all the content in the file
    m3 = buffer5.str();  // Convert the content of the buffer into a string
    file5.close();


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
    return 0;

}
