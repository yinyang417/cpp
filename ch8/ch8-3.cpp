#include <bits/stdc++.h>
using namespace std;
const int MAXSIZE = 13333;
const int EMPTY = -1;

struct HashNode
{
    int row;
    int col;
    int data;
};

class HashTable
{
public:
    HashNode *table;
    int maxsize;
    int conflict;
    int inserted;
    int findtimes;

    HashTable()
    {
        maxsize = MAXSIZE;
        table = new HashNode[maxsize];
        conflict = 0;
        inserted = 0;
        findtimes = 0;
        for (int i = 0; i < maxsize; i++)
        {
            table[i].row = EMPTY;
            table[i].col = EMPTY;
        }
    }

    int Hash(int row, int col)
    {
        int temp = row * 1000 + col;
        int p = 11987;
         return (temp%p+p)%p;
    }

    int Collision(int index, int count)
    {
        return (index + count * count);
    }

    void Insert(int row, int col, int data)
    {
        int index = Hash(row, col);
        int count = 0;
        while (table[index].row != EMPTY)
        {
            index = Collision(index, count);
            count++;
            conflict++;
        }
        table[index].row = row;
        table[index].col = col;
        table[index].data = data;
        inserted++;
    }

    void Find(int row, int col)
    {
        int index = Hash(row, col);
        int count = 0;
        while (table[index].row != row || table[index].col != col)
        {
            index = Collision(index, count);
            count++;
            findtimes++;
        }
        findtimes++;
        cout << table[index].data << endl;
    }
};

int main()
{
    HashTable h;
    int n = 10000;
    int row, col, data;

    int randomnum = 10000;
    int low = 1;
    int high = 1000;
    srand((unsigned)time(NULL));
    set<pair<int, int>> pairs;//随机生成10000组数据
    set<int> cs;
    vector<tuple<int, int, int>> triples;
    while (triples.size() < randomnum)
    {
        int a = rand() % (high - low + 1) + low;
        int b = rand() % (high - low + 1) + low;
        if (pairs.find(make_pair(a, b)) == pairs.end())
        {
            pairs.insert(make_pair(a, b));
            int c = rand() % (10000 - 1 + 1) + 1;
            while (cs.count(c) > 0)
            {
                c = rand() % (10000 - 1 + 1) + 1;
            }
            cs.insert(c);
            triples.emplace_back(make_tuple(a, b, c));
        }
    }

    for (int i = 0; i < n; i++)
    {
        row = get<0>(triples[i]);
        col = get<1>(triples[i]);
        data = get<2>(triples[i]);
        cout << row << " " << col << " " << data << endl;
        h.Insert(row, col, data);
    }

    cout << "生成了" << h.inserted << "个元素" << endl;
    cout << "冲突次数为" << h.conflict << endl;
    system("pause");
    for (int i = 0; i < n; i++)
    {
        row = get<0>(triples[i]);
        col = get<1>(triples[i]);
        h.Find(row, col);
    }
    cout <<"查找次数为"<< h.findtimes << endl;
    return 0;
}