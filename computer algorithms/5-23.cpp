#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>
#include <iomanip>
#include <algorithm>
using namespace std;

struct Circle 
{
    int id;
    double radius;
};

vector<Circle> circles;
vector<int> curr, best;
double curr_length, best_length=1e8;
int n;

void dfs(int u, double sum) 
{
    if(u == n) 
    {
        if(sum < best_length) 
        {
            best_length = sum;
            best = curr;
        }
        return;
    }
    for(int i = 0; i < n; ++i) 
    {
        if(find(curr.begin(), curr.end(), i) == curr.end()) 
        {
            curr[u] = i;
            double new_sum = sum + 2*sqrt(circles[u].radius * circles[i].radius);
            if(new_sum < best_length) 
            {
                dfs(u+1, new_sum);
            }
            curr[u] = -1;
        }
    }
}

int main() 
{
    ifstream input("input.txt");
    input >> n;
    circles.resize(n);
    curr.resize(n, -1);
    best.resize(n, -1);
    for (int i = 0; i < n; ++i) 
    {
        circles[i].id = i;
        input >> circles[i].radius;
    }
    input.close();

    dfs(0, 0.0);

    ofstream output("output.txt");
    output << fixed << setprecision(5) << best_length << endl;
    output.close();

    return 0;
}