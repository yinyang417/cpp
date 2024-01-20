#include <bits/stdc++.h>
using namespace std;
char ch = 'y'; // 是否启用银行家算法进行防止死锁？y/n
int m = 3;     // m类资源
int n = 5;     // n个进程数
// 要用到的数组
vector<int> available;          // 可利用资源向量,m个
vector<vector<int>> Max;        // 最大需求矩阵，n行m列
vector<vector<int>> allocation; // 分配矩阵，同上
vector<vector<int>> need;       // 需求矩阵，同上 Need［i,j］=Max［i,j］-Allocation［i,j］
vector<vector<int>> request;    // 第n个进程请求第m个资源
vector<int> worknow;            // 分配时第i个进程，m个资源初始还剩多少个可分配的数量。m个
vector<bool> finish;            // 系统是否有足够的资源分配,是否已经分配完毕？n个
vector<vector<int>> WaddA;      // W+A，若能够分配，分配后系统中拥有的资源，给下一个，n*m
vector<int> p;                  // 记录进程号,n个
vector<vector<int>> work;       // 记录表中你每一个进程的work n*m

void menu()
{
    cout << endl;
    cout << endl;
    cout << "\t  死锁观察与避免实验\n"
         << endl;
    cout << "\t| ==============================|" << endl;
    cout << "\t| 1. 初始化\t\t\t|" << endl;
    cout << "\t| 2. 查看当前资源分配表\t\t|" << endl;
    cout << "\t| 3. 请求资源\t\t\t|" << endl;
    cout << "\t| 4. 退出\t\t\t|" << endl;
}

void initArray()
{
    n = 5;
    m = 3;
    // 初始化全为0
    Max.resize(n);
    allocation.resize(n);
    need.resize(n);
    request.resize(n);
    WaddA.resize(n);
    work.resize(n);
    for (int i = 0; i < n; i++)
    {
        // n个进程初始化
        p.push_back(i);
        finish.push_back(false);
        for (int j = 0; j < m; j++)
        {
            if (i == 0)
            {
                // m个资源初始化
                worknow.push_back(0);
                available.push_back(0);
            }
            // 各类矩阵初始化
            Max[i].push_back(0);
            allocation[i].push_back(0);
            need[i].push_back(0);
            request[i].push_back(0);
            WaddA[i].push_back(0);
            work[i].push_back(0);
        }
    }
}

void init()
{
    initArray();

    vector<vector<int>> maxData = {{7, 3, 5}, {3, 2, 2}, {9, 0, 2}, {2, 2, 2}, {4, 3, 3}};
    vector<vector<int>> allocData = {{0, 1, 0}, {2, 0, 0}, {3, 0, 2}, {2, 1, 1}, {0, 0, 2}};

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            Max[i][j] = maxData[i][j];
            allocation[i][j] = allocData[i][j];
        }
    }

    vector<int> availableData = {3, 3, 2};
    for (int i = 0; i < m; i++) {
        available[i] = availableData[i];
    }

}

void print()
{
    // 生成need矩阵，第i个进程的第j个资源还需要多少
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            need[i][j] = Max[i][j] - allocation[i][j];
    // 输出每个进程需要的资源数量
    cout << "\tMax   \t|\t"
         << "\tAllo  \t|\t"
         << "\tNeed  \t|\t"
         << "\tAvalia\t" << endl;
    for (int i = 0; i < n; i++)
    {
        cout << "P" << i << "    \t";
        for (int j = 0; j < m; j++)
            cout << Max[i][j] << " ";
        cout << "\t\t\t";
        for (int j = 0; j < m; j++)
            cout << allocation[i][j] << " ";
        cout << "\t\t\t";
        for (int j = 0; j < m; j++)
            cout << need[i][j] << " ";
        cout << "\t\t\t";
        if (i == 0)
        {
            for (int i = 0; i < m; i++)
                cout << available[i] << " ";
            cout << endl;
        }
        else
            cout << endl;
    }
}

void print_sequence()
{
    cout << "\tWork   \t|\t"
         << "\tNeed  \t|\t"
         << "\tAllo  \t|\t"
         << "\tW+A  \t|\t"
         << "\tFinish\t" << endl;
    for (int i = 0; i < n; i++)
    {
        cout << "P" << i << "    \t";
        for (int j = 0; j < m; j++)
            cout << work[i][j] << " ";
        cout << "\t\t\t";
        for (int j = 0; j < m; j++)
            cout << need[i][j] << " ";
        cout << "\t\t\t";
        for (int j = 0; j < m; j++)
            cout << allocation[i][j] << " ";
        cout << "\t\t\t";
        for (int j = 0; j < m; j++)
            cout << WaddA[i][j] << " ";
        cout << "\t\t\t";
        cout << finish[i] << endl;
    }
}

bool safety()
{
    // 初始化
    int w = 0;
    // 初始当前可用资源等于输入的系统内剩余的资源
    for (int j = 0; j < m; j++)
        worknow[j] = available[j];
    // 将所有进程标为未完成
    for (int i = 0; i < n; i++)
        finish[i] = false;
    int count = 0;
    while (1)
    {
        // 每次检查是否所有进程均完成
        for (int i = 0; i < n; i++)
        {
            if (finish[i] == false)
            {
                // 若有未完成的试探其是否符合要求
                int f1 = 1;
                for (int j = 0; j < m; j++)
                {
                    // 若需求的大于当前系统内现有的资源，则不能分配
                    if (need[i][j] > worknow[j])
                    {
                        f1 = 0;
                    }
                }
                // 若可以分配
                if (f1 == 1)
                {
                    for (int j = 0; j < m; j++)
                    {
                        // 记录
                        work[i][j] = worknow[j];
                        // 更新结束分配后当前系统内拥有的资源
                        worknow[j] = worknow[j] + allocation[i][j];
                        WaddA[i][j] = worknow[j];
                    }
                    finish[i] = true;
                    // 记录可行的序列
                    p[w++] = i;
                    count = 0;
                    cout << "第" << w << "次,分配给" << i << endl;
                    print_sequence();
                }
            }
        }
        // 若能够分配，最多循环n轮，则count为n，退出
        count++;
        if (count >= n)
            break;
    }
    int flag = 1;
    for (int i = 0; i < n; i++)
        if (finish[i] == false)
            flag = 0;
    if (flag == 1)
        return true;
    else
        return false;
}

bool isFinish = 0;

void Banker()
{
    cout << "输入请求资源的进程号(0/1/2...):" << endl;
    int pid;
    while (true)
    {
        cin >> pid;
        if (pid < 0 || pid >= n)
            cout << "请输入正确的进程号！" << endl;
        else
            break;
    }
    cout << "输入请求资源的数量(" << m << "类资源,空格隔开):";
    for (int j = 0; j < m; j++)
    {
        cin >> request[pid][j];
    }
    for (int j = 0; j < m; j++)
    {
        if (request[pid][j] > need[pid][j])
        {
            cout << "请求资源数量大于Need数量,分配失败!" << endl;
            return;
        }
        else
        {
            if (request[pid][j] > available[j])
            {
                cout << "请求资源数量大于Aailable数量,分配失败!" << endl;
                return;
            }
        }
    }
    cout << "初始资源分配情况：" << endl;
    print_sequence();
    // 试着分给他资源
    for (int j = 0; j < m; j++)
    {
        available[j] = available[j] - request[pid][j];
        allocation[pid][j] = allocation[pid][j] + request[pid][j];
        need[pid][j] = need[pid][j] - request[pid][j];
    }
    cout << "试着将资源分配给他" << endl;
    print_sequence();
    cout << "检查系统安全性" << endl;
    bool safe = safety();
    if (safe == true)
    {
        // 打印
        cout << "存在一个安全的分配序列！\n"
             << endl;
        for (int i = 0; i < n; i++)
        {
            cout << p[i] << "->"[i == n - 1];
        }
        cout << "\n请求成功! !" << endl;
        isFinish = 1;
        return;
    }
    else
    {
        cout << "此次请求会导致死锁！请求失败！！" << endl;
        // 恢复现场，不分配
        for (int j = 0; j < m; j++)
        {
            available[j] = available[j] + request[pid][j];
            allocation[pid][j] = allocation[pid][j] - request[pid][j];
            need[pid][j] = need[pid][j] + request[pid][j];
        }
    }
}

void noPrevention()
{
    cout << "输入请求资源的进程号(0/1/2...):\n";
    int pid;
    while (true)
    {
        cin >> pid;
        if (pid < 0 || pid >= n)
            cout << "请输入正确的进程号！" << endl;
        else
            break;
    }
    cout << "输入请求资源的数量(" << m << "类资源,空格隔开):";
    for (int j = 0; j < m; j++)
    {
        cin >> request[pid][j];
    }
    for (int j = 0; j < m; j++)
    {
        if (request[pid][j] > need[pid][j])
        {
            cout << "请求资源数量大于Need数量,分配失败!" << endl;
            return;
        }
        else
        {

            if (request[pid][j] > available[j])
            {
                cout << "请求资源数量大于Aailable数量,分配失败!" << endl;
                return;
            }
        }
    }
    cout << "初始资源分配情况：" << endl;
    // 分给他资源
    for (int j = 0; j < m; j++)
    {
        available[j] = available[j] - request[pid][j];
        allocation[pid][j] = allocation[pid][j] + request[pid][j];
        need[pid][j] = need[pid][j] - request[pid][j];
    }
    cout << "将资源分配给他\n";
    print_sequence();
    // 检查是否发生死锁
    bool f = true;
    for (int i = 0; i < n; i++)
    {
        bool check = 0;
        for (int j = 0; j < m; j++)
        {
            if (available[j] < need[i][j])
            {
                check = 1;
                break;
            }
        }
        if (check == 0)
            f = false;
    }
    if (f)
        cout << "发生了死锁！ \n";
    else
        cout << "当前尚未发生死锁\n";
}

int main()
{
    int f = 1;
    cout << "请问您是否想要启用防止死锁算法（银行家算法）？(y/n)" << endl
         << "请输入(y/n):";
    cin >> ch;
    bool isinit = 0;
    while (1)
    {
        int select;
        menu();
        cout << "\n";
        if (isinit == 1)
            print(); // 实时显示
        cout << "\t  请选择:";
        cin >> select;
        switch (select)
        {
        case 1:
            init();
            isinit = 1;
            break;
        case 2:
            if (isinit == 0)
                cout << "请先初始化！" << endl;
            else
                print();
            break;
        case 3:
        {
            if (isinit == 0)
                cout << "请先初始化！" << endl;
            else
            {
                if (ch == 'y')
                {
                    Banker();
                }
                else
                {
                    noPrevention();
                }
            }
            break;
        }
        case 4:
            f = 0;
            break;
        }
        if (f == 0)
            break;
        system("pause");
        system("cls");
    }

    return 0;
}

/*
可行：
1
1 0 2

不可行：
0
3 2 1
*/