#include<bits/stdc++.h>
using namespace std;

int part(int n, int m) {
    if(m == n || m == 1) {
        return 1;
    } else if(m > n || m == 0) {
        return 0;
    } else {
        return part(n - 1, m - 1) + m * part(n - 1, m);
    }
}

int main() {
    int n, m;
    ifstream inputFile("input.txt");
    ofstream outputFile("output.txt");

    if(inputFile.is_open() && outputFile.is_open()) {
        inputFile >> n >> m;
        int c = part(n, m);
        outputFile << c;

        inputFile.close();
        outputFile.close();
        cout << "Output has been written to output.txt." << endl;
    } else {
        cout << "Failed to open input.txt or output.txt." << endl;
    }

    return 0;
}