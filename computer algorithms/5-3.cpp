#include <iostream>
#include <vector>
using namespace std;

// 物品带有价值
struct Item {
    int weight;
    int value;
};

vector<Item> items;
vector<int> bestSolution;
vector<int> tempSolution;
int max_value = 0;

// 回溯算法
void backtrack(int i, int sum_weight, int sum_value, int capacity) {
    // 到达叶节点,意味着到达问题的一种解法
    if (i >= items.size()) {
        if (sum_value > max_value) {
            max_value = sum_value;
            bestSolution = tempSolution;
        }
        return;
    }
    // 不将当前物品i放入背包
    backtrack(i + 1, sum_weight, sum_value, capacity);
    // 将物品i放入背包
    if (sum_weight + items[i].weight <= capacity) { //等于是剪枝
        tempSolution.push_back(i);
        backtrack(i + 1, sum_weight + items[i].weight, sum_value + items[i].value, capacity);
        tempSolution.pop_back();  //回溯
    }
}

int main() {
    // 向物品数组添加元素
    items.push_back({2, 3});
    items.push_back({1, 2});
    items.push_back({3, 4});
    items.push_back({2, 2});

    int capacity = 5;

    backtrack(0, 0, 0, capacity);

    cout << "最大价值: " << max_value << endl;
    cout << "装入背包的物品序号: ";
    for (int index : bestSolution)
        cout << index << " ";
    cout << endl;
    system("pause");
    return 0;
}