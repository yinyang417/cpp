#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
    int max_value = 0;
    vector<int> cur_result, best_result;
public:
    void backtrack(int weight_limit, vector<pair<int, int>> items, int cur_index = 0, int cur_weight = 0, int cur_value = 0) {
        if (cur_index >= items.size()) {
            return;
        }

        // 不把当前物品添加进解决方案
        backtrack(weight_limit, items, cur_index + 1, cur_weight, cur_value);

        // 把当前物品添加进解决方案
        cur_weight += items[cur_index].first;
        if (cur_weight <= weight_limit) {
            cur_result.push_back(cur_index);
            cur_value += items[cur_index].second;

            // 动态更新当前最优解
            if(cur_value > max_value) {
                max_value = cur_value;
                best_result = cur_result;
            }
            backtrack(weight_limit, items, cur_index + 1, cur_weight, cur_value);

            // 回溯之前的状态
            cur_result.pop_back();
        }
    }

    vector<int> solve(int weight_limit, vector<pair<int, int>> items) {
        backtrack(weight_limit, items);
        return best_result;
    }
};

int main() {
    Solution solution;
    vector<pair<int,int>> items = {{2, 3}, {1, 2}, {3, 4}, {2, 2}};
    int weight_limit = 5;
    vector<int> best_items = solution.solve(weight_limit, items);
    for(auto &item_index : best_items){
        cout << "Item index: " << item_index << ", Weight: " << items[item_index].first << ", Value: " << items[item_index].second << endl;
    }
    system("pause");
    return 0;
}
