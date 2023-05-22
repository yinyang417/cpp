#include<bits/stdc++.h>
#define MAX 100
using namespace std;

struct ArcNode		//��
{
	int adjvex;
	ArcNode* next;
};

struct VexNode		//����
{
	int data;
	ArcNode* first;
};

struct AdjList		//�ڽӱ�
{
	VexNode AdjList[MAX];//��������
	int vexnum;
	int arcnum;
};

int Visited[MAX];
int Find[MAX];

void creat(AdjList& t)
{
	int i, j;
	ArcNode* p = NULL;
	ArcNode* q = NULL;
	cout << "�����붥�����ͱ���" << endl;
	cin >> t.vexnum >> t.arcnum;
	for (int k = 0; k < t.vexnum; k++)
	{
		t.AdjList[k].data = k;
		t.AdjList[k].first = NULL;
	}
	for (int k = 0; k < t.arcnum; k++)
	{
		cout << "������ߣ�vi,vj��" << endl;
		cin >> i >> j;
		p = new ArcNode;
		p->adjvex = j;
		p->next = t.AdjList[i].first;
		t.AdjList[i].first = p;
		q = new ArcNode;
		q->adjvex = i;
		q->next = t.AdjList[j].first;
		t.AdjList[j].first = q;
	}
}

void display(AdjList& t)
{
	ArcNode* p;
	for (int i = 0; i < t.vexnum; i++)
	{
		cout << t.AdjList[i].data << "-->";
		for (p = t.AdjList[i].first; p; p = p->next)
		{
			cout << p->adjvex;
			if (p->next != NULL)
			{
				cout << "-->";
			}
		}
		cout << endl;
	}
}

void DFS(AdjList& t, int i)
{
	ArcNode* p;
	Visited[i] = 1;
	for (p = t.AdjList[i].first; p; p = p->next)
	{
		if (Visited[p->adjvex] == 0)
		{
			DFS(t, p->adjvex);
		}
	}
}

void findpath(AdjList& t, int u, int v, int path[], int d)//�ʼʱdΪ-1
{
	int n;
	ArcNode* p;
	d++;
	path[d] = u;
	Find[u] = 1;
	if (u == v)
	{
		for (int i = 0; i < d; i++)
		{
			cout << path[i];
			if (i == d - 1)
			{
				cout << "-->" << v << endl;
			}
			else
			{
				cout << "-->";
			}
		}
	}
	p = t.AdjList[u].first;
	while (p != NULL)
	{
		n = p->adjvex;
		if (Find[n] == 0)//��p���ڽӵ�û�����������ݹ�
		{
			findpath(t, n, v, path, d);
		}
		p = p->next;//������������ת����һ���ڵ�
	}
	Find[u] = 0;//��ʼ���Ա��ҵ����е�·��
}

int main()
{
	AdjList t;
	creat(t);
	display(t);

	cout << "������Ҫ���������㣺" << endl;
	int a, b;
	int path[MAX];
	cin >> a >> b;
	DFS(t, a);

	if (Visited[b] == 0)
	{
		cout << "������·��" << endl;
	}
	else
	{
		cout << "����·��" << endl;
		findpath(t, a, b, path, -1);
	}

	return 0;
}

/*

7 5
0 1
0 2
1 2
0 5
3 4

*/