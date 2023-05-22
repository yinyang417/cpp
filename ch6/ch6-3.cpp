#include<bits/stdc++.h>

using namespace std;

typedef struct ElemNode {
	char data;
	int parent;
};

class UFSets
{
protected:
	ElemNode* sets;
	int size;
	int Find(char e) const;
	int CollapsingFind(char e) const;
public:
	UFSets(char es[], int n);
	virtual ~UFSets();
	char GetElem(int p)const;
	void Union(char a, char b);
	friend ostream& operator<<(ostream& out, const UFSets& t);
};

UFSets::UFSets(char es[], int n)
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

int UFSets::Find(char e) const
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

int UFSets::CollapsingFind(char e) const//路径压缩
{
	int i, k, p = 0;
	while (p < size && sets[p].data != e)//查找元素e
		p++;
	if (p == size)//查找失败
	{
		return -1;
	}
	if (sets[p].parent < 0)//根节点为自身
	{
		return p;
	}
	for (i = p; sets[i].parent >= 0; i = sets[i].parent);//根节点不是自身，顺着指针向上查找
	while (i != sets[p].parent)//将路径上每个节点的父节点都指向根节点
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

void UFSets::Union(char a, char b)
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


int main()
{
	const int n = 10;
	char c[] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j' };
	UFSets e(c, n);
	e.Union('a', 'b');
	cout << endl;
	cout << e << endl;
	e.Union('c', 'a');
	cout << endl;
	cout << e << endl;
	e.Union('d', 'e');
	cout << endl;
	cout << e << endl;
	e.Union('f', 'g');
	cout << endl;
	cout << e << endl;
	e.Union('g', 'h');
	cout << endl;
	cout << e << endl;
	e.Union('j', 'i');
	cout << endl;
	cout << e << endl;
	e.Union('g', 'c');
	cout << endl;
	cout << e << endl;
	return 0;
}
