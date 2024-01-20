#include <bits/stdc++.h>
using namespace std;
char ch = 'y'; // �Ƿ��������м��㷨���з�ֹ������y/n
int m = 3;     // m����Դ
int n = 5;     // n��������
// Ҫ�õ�������
vector<int> available;          // ��������Դ����,m��
vector<vector<int>> Max;        // ����������n��m��
vector<vector<int>> allocation; // �������ͬ��
vector<vector<int>> need;       // �������ͬ�� Need��i,j��=Max��i,j��-Allocation��i,j��
vector<vector<int>> request;    // ��n�����������m����Դ
vector<int> worknow;            // ����ʱ��i�����̣�m����Դ��ʼ��ʣ���ٸ��ɷ����������m��
vector<bool> finish;            // ϵͳ�Ƿ����㹻����Դ����,�Ƿ��Ѿ�������ϣ�n��
vector<vector<int>> WaddA;      // W+A�����ܹ����䣬�����ϵͳ��ӵ�е���Դ������һ����n*m
vector<int> p;                  // ��¼���̺�,n��
vector<vector<int>> work;       // ��¼������ÿһ�����̵�work n*m

void menu()
{
    cout << endl;
    cout << endl;
    cout << "\t  �����۲������ʵ��\n"
         << endl;
    cout << "\t| ==============================|" << endl;
    cout << "\t| 1. ��ʼ��\t\t\t|" << endl;
    cout << "\t| 2. �鿴��ǰ��Դ�����\t\t|" << endl;
    cout << "\t| 3. ������Դ\t\t\t|" << endl;
    cout << "\t| 4. �˳�\t\t\t|" << endl;
}

void initArray()
{
    n = 5;
    m = 3;
    // ��ʼ��ȫΪ0
    Max.resize(n);
    allocation.resize(n);
    need.resize(n);
    request.resize(n);
    WaddA.resize(n);
    work.resize(n);
    for (int i = 0; i < n; i++)
    {
        // n�����̳�ʼ��
        p.push_back(i);
        finish.push_back(false);
        for (int j = 0; j < m; j++)
        {
            if (i == 0)
            {
                // m����Դ��ʼ��
                worknow.push_back(0);
                available.push_back(0);
            }
            // ��������ʼ��
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
    // ����need���󣬵�i�����̵ĵ�j����Դ����Ҫ����
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            need[i][j] = Max[i][j] - allocation[i][j];
    // ���ÿ��������Ҫ����Դ����
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
    // ��ʼ��
    int w = 0;
    // ��ʼ��ǰ������Դ���������ϵͳ��ʣ�����Դ
    for (int j = 0; j < m; j++)
        worknow[j] = available[j];
    // �����н��̱�Ϊδ���
    for (int i = 0; i < n; i++)
        finish[i] = false;
    int count = 0;
    while (1)
    {
        // ÿ�μ���Ƿ����н��̾����
        for (int i = 0; i < n; i++)
        {
            if (finish[i] == false)
            {
                // ����δ��ɵ���̽���Ƿ����Ҫ��
                int f1 = 1;
                for (int j = 0; j < m; j++)
                {
                    // ������Ĵ��ڵ�ǰϵͳ�����е���Դ�����ܷ���
                    if (need[i][j] > worknow[j])
                    {
                        f1 = 0;
                    }
                }
                // �����Է���
                if (f1 == 1)
                {
                    for (int j = 0; j < m; j++)
                    {
                        // ��¼
                        work[i][j] = worknow[j];
                        // ���½��������ǰϵͳ��ӵ�е���Դ
                        worknow[j] = worknow[j] + allocation[i][j];
                        WaddA[i][j] = worknow[j];
                    }
                    finish[i] = true;
                    // ��¼���е�����
                    p[w++] = i;
                    count = 0;
                    cout << "��" << w << "��,�����" << i << endl;
                    print_sequence();
                }
            }
        }
        // ���ܹ����䣬���ѭ��n�֣���countΪn���˳�
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
    cout << "����������Դ�Ľ��̺�(0/1/2...):" << endl;
    int pid;
    while (true)
    {
        cin >> pid;
        if (pid < 0 || pid >= n)
            cout << "��������ȷ�Ľ��̺ţ�" << endl;
        else
            break;
    }
    cout << "����������Դ������(" << m << "����Դ,�ո����):";
    for (int j = 0; j < m; j++)
    {
        cin >> request[pid][j];
    }
    for (int j = 0; j < m; j++)
    {
        if (request[pid][j] > need[pid][j])
        {
            cout << "������Դ��������Need����,����ʧ��!" << endl;
            return;
        }
        else
        {
            if (request[pid][j] > available[j])
            {
                cout << "������Դ��������Aailable����,����ʧ��!" << endl;
                return;
            }
        }
    }
    cout << "��ʼ��Դ���������" << endl;
    print_sequence();
    // ���ŷָ�����Դ
    for (int j = 0; j < m; j++)
    {
        available[j] = available[j] - request[pid][j];
        allocation[pid][j] = allocation[pid][j] + request[pid][j];
        need[pid][j] = need[pid][j] - request[pid][j];
    }
    cout << "���Ž���Դ�������" << endl;
    print_sequence();
    cout << "���ϵͳ��ȫ��" << endl;
    bool safe = safety();
    if (safe == true)
    {
        // ��ӡ
        cout << "����һ����ȫ�ķ������У�\n"
             << endl;
        for (int i = 0; i < n; i++)
        {
            cout << p[i] << "->"[i == n - 1];
        }
        cout << "\n����ɹ�! !" << endl;
        isFinish = 1;
        return;
    }
    else
    {
        cout << "�˴�����ᵼ������������ʧ�ܣ���" << endl;
        // �ָ��ֳ���������
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
    cout << "����������Դ�Ľ��̺�(0/1/2...):\n";
    int pid;
    while (true)
    {
        cin >> pid;
        if (pid < 0 || pid >= n)
            cout << "��������ȷ�Ľ��̺ţ�" << endl;
        else
            break;
    }
    cout << "����������Դ������(" << m << "����Դ,�ո����):";
    for (int j = 0; j < m; j++)
    {
        cin >> request[pid][j];
    }
    for (int j = 0; j < m; j++)
    {
        if (request[pid][j] > need[pid][j])
        {
            cout << "������Դ��������Need����,����ʧ��!" << endl;
            return;
        }
        else
        {

            if (request[pid][j] > available[j])
            {
                cout << "������Դ��������Aailable����,����ʧ��!" << endl;
                return;
            }
        }
    }
    cout << "��ʼ��Դ���������" << endl;
    // �ָ�����Դ
    for (int j = 0; j < m; j++)
    {
        available[j] = available[j] - request[pid][j];
        allocation[pid][j] = allocation[pid][j] + request[pid][j];
        need[pid][j] = need[pid][j] - request[pid][j];
    }
    cout << "����Դ�������\n";
    print_sequence();
    // ����Ƿ�������
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
        cout << "������������ \n";
    else
        cout << "��ǰ��δ��������\n";
}

int main()
{
    int f = 1;
    cout << "�������Ƿ���Ҫ���÷�ֹ�����㷨�����м��㷨����(y/n)" << endl
         << "������(y/n):";
    cin >> ch;
    bool isinit = 0;
    while (1)
    {
        int select;
        menu();
        cout << "\n";
        if (isinit == 1)
            print(); // ʵʱ��ʾ
        cout << "\t  ��ѡ��:";
        cin >> select;
        switch (select)
        {
        case 1:
            init();
            isinit = 1;
            break;
        case 2:
            if (isinit == 0)
                cout << "���ȳ�ʼ����" << endl;
            else
                print();
            break;
        case 3:
        {
            if (isinit == 0)
                cout << "���ȳ�ʼ����" << endl;
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
���У�
1
1 0 2

�����У�
0
3 2 1
*/