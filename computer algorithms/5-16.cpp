#include <iostream>
#include <fstream>
#include <limits>
#include <vector>
#include <string>
using namespace std;

int n, target;
vector<int> nums;
int min_times = numeric_limits<int>::max();
string best_expr;

void backtrack(int idx, int value, int times, string expr) {
    if (value == target) {
        if (times < min_times) {
            min_times = times;
            best_expr = expr;
        }
        return;
    }

    if (idx == n) {
        return;
    }

    int next_value = nums[idx];
    string next_str = to_string(next_value);
    backtrack(idx + 1, value + next_value, times + 1, expr + " + " + next_str);
    backtrack(idx + 1, value - next_value, times + 1, expr + " - " + next_str);
    backtrack(idx + 1, value * next_value, times + 1, expr + " * " + next_str);

    if (value % next_value == 0) {
        backtrack(idx + 1, value / next_value, times + 1, expr + " / " + next_str);
    }
}

int main() {
    ifstream input("input.txt");
    input >> n >> target;
    nums.resize(n);
    for (int i = 0; i < n; ++i) {
        input >> nums[i];
    }
    input.close();

    for (int i = 0; i < n; ++i) {
        string first_num_str = to_string(nums[i]);
        backtrack(i + 1, nums[i], 0, first_num_str);
    }

    ofstream output("output.txt");
    output << "最少无优先级运算次数: " << min_times << endl;
    output << "最优无优先级运算表达式: " << best_expr << endl;
    output.close();

    return 0;
}