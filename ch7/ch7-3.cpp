#include <bits/stdc++.h>
#define MAX 100
#define DEFAULT_INFINITY 999
using namespace std;

struct AdjMatrix
{
    int vex[MAX];
    int arc[MAX][MAX];
    int vexnum, arcnum;
};

void create(AdjMatrix &t, int n, int m)
{
    t.vexnum = n;
    t.arcnum = m;
    for (int i = 0; i < t.vexnum; i++)
    {
        t.vex[i] = i;
    }
    for (int i = 0; i < t.vexnum; i++)
    {
        for (int j = 0; j < t.vexnum; j++)
        {
            t.arc[i][j] = 999;
        }
    }
    for (int i = 0; i < t.vexnum; i++)
    {
        t.arc[i][i] = 0;
    }
    for (int i = 0; i < t.arcnum; i++)
    {
        int a, b, c;
        cin >> a >> b >> c;
        t.arc[a][b] = c;
        t.arc[b][a] = c;
    }
}

void diaplay(AdjMatrix &t)
{
    for (int i = 0; i < t.vexnum; i++)
    {
        for (int j = 0; j < t.vexnum; j++)
        {
            cout << t.arc[i][j] << "\t";
        }
        cout << endl;
    }
}

void ShortestPathFloyd(AdjMatrix &t, int v0, int v1)
{
    int dist[MAX][MAX];
    for (int i = 0; i < t.vexnum; i++)
    {
        for (int j = 0; j < t.vexnum; j++)
        {
            dist[i][j] = t.arc[i][j];
        }
    }

    for (int k = 0; k < t.vexnum; k++)
    {
        for (int i = 0; i < t.vexnum; i++)
        {
            for (int j = 0; j < t.vexnum; j++)
            {
                dist[i][j] = min(max(dist[i][k], dist[k][j]), dist[i][j]);
            }
        }
    }

    cout << "最大噪声值为：" << dist[v0][v1] << endl;
}

int main()
{
    AdjMatrix t;
    int n, m, k;
    int v0, v1;
    int temp;
    cout << "请输入顶点数、边数、询问次数：" << endl;
    cin >> n >> m >> k;
    cout << "请输入边的信息：" << endl;
    create(t, n, m);
    diaplay(t);
    for (int i = 0; i < k; i++)
    {
        cout << "请输入起点和终点：" << endl;
        cin >> v0 >> v1;
        ShortestPathFloyd(t, v0, v1);
    }
    return 0;
}

/*
7 9 1
0 1 50
0 2 60
1 3 120
1 4 90
2 5 50
3 6 70
3 5 80
4 6 40
5 6 140
*/