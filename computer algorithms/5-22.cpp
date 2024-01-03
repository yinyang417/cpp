#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

struct Item 
{
    int value;
    int weight;
};

int n, c;
vector<Item> items;
vector<bool> curr, best;
int curr_value, best_value;

void bag(int i) 
{
    if(i >= n)
    {
        if(curr_value > best_value)
        {
            best_value = curr_value;
            best = curr;
        }
        return;
    }

    // include item i
    if(items[i].weight <= c)
    {
        curr[i] = true;
        curr_value += items[i].value;
        c -= items[i].weight;
        bag(i+1);
        // backtrack
        curr_value -= items[i].value;
        c += items[i].weight;
    }
    // don't include item i
    curr[i] = false;
    bag(i+1);
}

int main() 
{
    ifstream input("input.txt");
    input >> n >> c;
    items.resize(n);
    curr.resize(n);
    best.resize(n);
    for (int i = 0; i < n; ++i) 
    {
        input >> items[i].value;
    }
    for (int i = 0; i < n; ++i) 
    {
        input >> items[i].weight;
    }
    input.close();

    bag(0);

    ofstream output("output.txt");
    output << "最大价值: " << best_value << endl;
    output << "装入背包的物品编号: ";
    for (int i = 0; i < n; ++i) 
    {
        output << (best[i] ? "1" : "0") << " ";
    }
    output << endl;
    output.close();

    return 0;
}