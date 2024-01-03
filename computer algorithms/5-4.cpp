#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

const int MAXN = 20;
int n;
double P[MAXN + 1][MAXN + 1], Q[MAXN + 1][MAXN + 1];
vector<bool> used(MAXN + 1, false);
double result = 0;

void backtrack(int idx, double sum) {
    if (idx > n) {
        result = max(result, sum);
        return;
    }

    for (int i = 1; i <= n; ++i) {
        if (!used[i]) {
            used[i] = true;
            double new_sum = sum + P[idx][i] * Q[i][idx];
            backtrack(idx + 1, new_sum);
            used[i] = false;
        }
    }
}

int main() {
    ifstream input("input.txt");
    input >> n;
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j)
            input >> P[i][j];
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j)
            input >> Q[i][j];

    input.close();

    backtrack(1, 0);
    
    ofstream output("output.txt");
    output << result;
    output.close();

    return 0;
}