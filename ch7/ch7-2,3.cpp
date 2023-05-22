#include<bits/stdc++.h>
#define DEFAULT_INFINITY 99
#define MAX 100
using namespace std;

typedef struct ElemNode {
	char data;
	int parent;
};

class UFSets
{
public:
	ElemNode* sets;
	int size;
	int Find(int e) const;
	int CollapsingFind(int e) const;
	UFSets(int es[], int n);
	virtual ~UFSets();
	char GetElem(int p)const;
	void Union(int a, int b);
	friend ostream& operator<<(ostream& out, const UFSets& t);
};

UFSets::UFSets(int es[], int n)
{
	size = n;
	sets = new ElemNode[size];
	for (int i = 0; i < size; i++)
	{
		sets[i].data = es[i];
		sets[i].parent = -1;
	}
}

UFSets::~UFSets()
{
	delete[]sets;
}

int UFSets::Find(int e) const
{
	int p = 0;
	while (p < size && sets[p].data != e)
	{
		p++;
	}
	if (p == size)
	{
		return -1;
	}
	while (sets[p].parent > -1)
	{
		p = sets[p].parent;
	}
	return p;
}

int UFSets::CollapsingFind(int e) const
{
	int i, k, p = 0;
	while (p < size && sets[p].data != e)
		p++;
	if (p == size)
	{
		return -1;
	}
	if (sets[p].parent < 0)
	{
		return p;
	}
	for (i = p; sets[i].parent >= 0; i = sets[i].parent);
	while (i != sets[p].parent)
	{
		k = sets[p].parent;
		sets[p].parent = i;
		p = k;
	}
	return i;
}

char UFSets::GetElem(int p) const
{
	return sets[p].data;
}

void UFSets::Union(int a, int b)
{
	int r1 = CollapsingFind(a);
	int r2 = CollapsingFind(b);
	if (r1 != r2 && r1 != -1 && r2 != -1)
	{
		int temp = sets[r1].parent + sets[r2].parent;
		if (sets[r1].parent <= sets[r2].parent)
		{
			sets[r2].parent = r1;
			sets[r1].parent = temp;
		}
		else
		{
			sets[r1].parent = r2;
			sets[r2].parent = temp;
		}
	}
}

ostream& operator<<(ostream& out, const UFSets& t)
{
	for (int i = 0; i < t.size; i++)
	{
		out << i << "   ";
	}
	out << endl;
	for (int j = 0; j < t.size; j++)
	{
		if (t.sets[j].parent < 0)
		{
			out << t.sets[j].parent << "  ";
		}
		else
		{
			out << t.sets[j].parent << "   ";
		}
	}
	out << endl;
	for (int k = 0; k < t.size; k++)
	{
		out << t.sets[k].data << "   ";
	}
	return out;
}

struct AdjMatrix {
	int vex[MAX];
	int arc[MAX][MAX];
	int vexnum, arcnum;
};

void create(AdjMatrix& t)
{
	t.vexnum = 6;
	t.arcnum = 9;
	for (int i = 0; i < t.vexnum; i++)
	{
		t.vex[i] = i;
	}
	for (int i = 0; i < t.vexnum; i++)//初始化
	{
		for (int j = 0; j < t.vexnum; j++)
		{
			t.arc[i][j] = DEFAULT_INFINITY;
		}
	}
	t.arc[0][1] = 34;
	t.arc[1][0] = t.arc[0][1];
	t.arc[0][2] = 46;
	t.arc[2][0] = t.arc[0][2];
	t.arc[0][5] = 19;
	t.arc[5][0] = t.arc[0][5];
	t.arc[1][4] = 12;
	t.arc[4][1] = t.arc[1][4];
	t.arc[2][3] = 17;
	t.arc[3][2] = t.arc[2][3];
	t.arc[2][5] = 25;
	t.arc[5][2] = t.arc[2][5];
	t.arc[3][4] = 38;
	t.arc[4][3] = t.arc[3][4];
	t.arc[3][5] = 25;
	t.arc[5][3] = t.arc[3][5];
	t.arc[4][5] = 26;
	t.arc[5][4] = t.arc[4][5];
}

void display(AdjMatrix& t)
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

void MSTKruskal(AdjMatrix& t, UFSets& e)
{
	int temp[MAX] = { 0 };
	int MSTarc[MAX][MAX] = { 0 };
	int count = 0;
	for (int i = 0; i < t.vexnum; i++)
	{
		for (int j = i; j < t.vexnum; j++)
		{
			if (t.arc[i][j] != DEFAULT_INFINITY)//将有效边放入temp
			{
				temp[count] = t.arc[i][j];
				count++;
			}
		}
	}
	sort(temp, temp + count);//将边的权重排序
	int count1 = 0;
	for (int i = 0; i < t.vexnum; i++)
	{
		for (int j = 0; j < t.vexnum; j++)
		{
			if (t.arc[i][j] != DEFAULT_INFINITY && temp[count1] == t.arc[i][j] && e.Find(i) != e.Find(j))
			{
				e.Union(i, j);//若两条边不在一个集合则放入同一个集合
				count1++;
				MSTarc[i][j] = t.arc[i][j];//将边添加进临时矩阵
				MSTarc[j][i] = t.arc[i][j];
			}
			else if (t.arc[i][j] != DEFAULT_INFINITY && temp[count1] == t.arc[i][j] && e.Find(i) == e.Find(j))
			{
				count1++;//在同一个集合则跳转到下一条边
			}
		}
	}
	for (int i = 0; i < t.vexnum; i++)
	{
		for (int j = 0; j < t.vexnum; j++)
		{
			cout << MSTarc[i][j] << "\t";//输出临时矩阵
		}
		cout << endl;
	}
}

void MSTprim(AdjMatrix& t, int start)
{
	int MSTarc[MAX][MAX] = { 0 };
	int closearc[2][MAX] = { 0 };
	int pos;//最小边的位置
	int min = 100;
	int v = start;
	closearc[0][start] = 0;//初始化辅助数组
	closearc[1][start] = -1;
	for (int i = 0; i < t.vexnum; i++)
	{
		if (i != start)
		{
			closearc[0][i] = t.arc[start][i];
			closearc[1][i] = 0;
		}
	}
	pos = 0;//初始化最小边的位置
	for (int k = 0; k < t.vexnum - 1; k++)
	{
		for (int i = 0; i < t.vexnum; i++)
		{
			if (closearc[0][i] != 0 && closearc[0][i] < min)//找最小边并更新其位置
			{
				min = closearc[0][i];
				pos = i;
			}
		}
		closearc[0][pos] = 0;// 将找到的最小边的位置 pos 所对应的第一行置为 0

		MSTarc[closearc[1][pos]][pos] = min;//更新临时矩阵
		MSTarc[pos][closearc[1][pos]] = MSTarc[closearc[1][pos]][pos];

		v = pos;

		for (int i = 0; i < t.vexnum; i++)//更新辅助数组
		{
			if (closearc[0][i] != 0 && t.arc[v][i] < closearc[0][i])
			{
				closearc[0][i] = t.arc[v][i];
				closearc[1][i] = v;
			}
		}

		closearc[0][pos] = 0;
		min = 100;//初始化最小值
	}
	for (int i = 0; i < t.vexnum; i++)//输出临时矩阵
	{
		for (int j = 0; j < t.vexnum; j++)
		{
			cout << MSTarc[i][j] << "\t";
		}
		cout << endl;
	}
}

int visited[MAX] = { 0 };

struct edge {
	int vex1;
	int vex2;
	int weight;
};

void DFS(AdjMatrix& t, int start)
{
	int w;
	visited[start] = 1;
	for (w = 0; w < t.vexnum; w++)
	{
		if (t.arc[start][w] != DEFAULT_INFINITY && visited[w] == 0)
		{
			DFS(t, w);
		}
	}
}

bool connect(AdjMatrix& t)
{
	bool flag = true;
	int k;
	for (k = 0; k < t.vexnum; k++)
	{
		visited[k] = 0;
	}
	DFS(t, 0);
	for (k = 0; k < t.vexnum; k++)
	{
		if (visited[k] == 0)
		{
			flag = false;
		}
	}
	return flag;
}

void MSTbreakcircle(AdjMatrix& t)
{
	int i, j, k = 0, arc_num;
	edge temp;
	edge edges[MAX];

	for (i = 0; i < t.vexnum; i++)//获取图中所有边信息
	{
		for (j = 0; j < i; j++)
		{
			if (t.arc[i][j] != DEFAULT_INFINITY)
			{
				edges[k].vex1 = i;
				edges[k].vex2 = j;
				edges[k].weight = t.arc[i][j];
				k++;
			}
		}
	}

	for (i = 1; i < t.arcnum; i++)//将edges数组排序
	{
		temp = edges[i];
		for (j = i - 1; j >= 0 && edges[j].weight < temp.weight; j--)
		{
			edges[j + 1] = edges[j];
		}
		edges[j + 1] = temp;
	}

	k = 0;
	arc_num = t.arcnum;
	while (arc_num >= t.vexnum)
	{
		t.arc[edges[k].vex1][edges[k].vex2] = DEFAULT_INFINITY;//删除第k条边
		t.arc[edges[k].vex2][edges[k].vex1] = DEFAULT_INFINITY;
		if (connect(t))//若连通，则删除
		{
			arc_num--;
		}
		else//若不连通，则恢复
		{
			t.arc[edges[k].vex1][edges[k].vex2] = edges[k].weight;
			t.arc[edges[k].vex2][edges[k].vex1] = edges[k].weight;
		}
		k++;
	}
	t.arcnum = arc_num;
	display(t);//输出矩阵
}

int main()
{
	int tempvex[6] = { 0,1,2,3,4,5 };
	AdjMatrix t;
	UFSets e(tempvex, 6);
	create(t);
	display(t);
	cout << "克鲁斯卡尔算法最小生成树：" << endl;
	MSTKruskal(t, e);
	cout << "普利姆算法最小生成树：" << endl;
	MSTprim(t, 0);
	cout << "破圈法最小生成树：" << endl;
	MSTbreakcircle(t);

	return 0;
}