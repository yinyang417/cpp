#include <iostream>
#include <vector>
using namespace std;

// ��Ʒ���м�ֵ
struct Item {
    int weight;
    int value;
};

vector<Item> items;
vector<int> bestSolution;
vector<int> tempSolution;
int max_value = 0;

// �����㷨
void backtrack(int i, int sum_weight, int sum_value, int capacity) {
    // ����Ҷ�ڵ�,��ζ�ŵ��������һ�ֽⷨ
    if (i >= items.size()) {
        if (sum_value > max_value) {
            max_value = sum_value;
            bestSolution = tempSolution;
        }
        return;
    }
    // ������ǰ��Ʒi���뱳��
    backtrack(i + 1, sum_weight, sum_value, capacity);
    // ����Ʒi���뱳��
    if (sum_weight + items[i].weight <= capacity) { //�����Ǽ�֦
        tempSolution.push_back(i);
        backtrack(i + 1, sum_weight + items[i].weight, sum_value + items[i].value, capacity);
        tempSolution.pop_back();  //����
    }
}

int main() {
    // ����Ʒ�������Ԫ��
    items.push_back({2, 3});
    items.push_back({1, 2});
    items.push_back({3, 4});
    items.push_back({2, 2});

    int capacity = 5;

    backtrack(0, 0, 0, capacity);

    cout << "����ֵ: " << max_value << endl;
    cout << "װ�뱳������Ʒ���: ";
    for (int index : bestSolution)
        cout << index << " ";
    cout << endl;
    system("pause");
    return 0;
}