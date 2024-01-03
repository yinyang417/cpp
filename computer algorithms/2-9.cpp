#include<bits/stdc++.h>
using namespace std;
 
void move(int n, char src, char medium, char dest, ofstream& outputFile) {
    if(n == 1) {
        outputFile << 1 << " " << src << " " << dest << endl;
    } else {
        move(n-1, src, dest, medium, outputFile);
        outputFile << n << " " << src << " " << dest << endl;
        move(n-1, medium, src, dest, outputFile);
    }
}
 
int main() {
    ifstream inputFile("input.txt");
    ofstream outputFile("output.txt");
    
    if(inputFile.is_open() && outputFile.is_open()) {
        int m;
        inputFile >> m;
        move(m, 'A', 'C', 'B', outputFile);

        inputFile.close();
        outputFile.close();
        cout << "Output has been written to output.txt." << endl;
    } else {
        cout << "Failed to open input.txt or output.txt." << endl;
    }
    
    return 0;
}