#include<bits/stdc++.h>
using namespace std;

typedef struct node {
	char data;
	struct node* firstchild;
	struct node* nextsibling;
}TreeNode, * Tree;

void CreateTree(Tree& t)
{
	char i;
	cin >> i;
	if (i == '#')
	{
		t = NULL;
	}
	else
	{
		t = new TreeNode;
		t->data = i;
		CreateTree(t->firstchild);
		CreateTree(t->nextsibling);
	}
}

int height(Tree& t)
{
	if (t == NULL)
	{
		return 0;
	}
	if (height(t->firstchild) + 1 > height(t->nextsibling))//������Ϊ��һ�㣬+1
	{
		return height(t->firstchild) + 1;
	}
	else
	{
		return height(t->nextsibling);
	}
}

int degree(Tree& t)//������ȱ���
{
	if (t == NULL)
	{
		return 0;
	}
	queue<TreeNode*> q;
	TreeNode* p;
	int max = 0;
	q.push(t);//���ڵ����
	while (!q.empty())
	{
		int deg = q.size();//��¼������
		for (int i = 0; i < deg; i++)
		{
			p = q.front();//p����
			q.pop();
			p = p->firstchild;
			while (p != NULL)//����һ������нڵ����
			{
				q.push(p);
				p = p->nextsibling;
			}
		}
		if (max < deg)//����������ֵ��max
		{
			max = deg;
		}
	}
	return max;
}

int main()
{
	Tree t;
	CreateTree(t);

	cout << "������ĸ߶��ǣ�";
	cout << height(t) << endl;
	cout << "������Ķ��ǣ�";
	cout << degree(t) << endl;
	return 0;
}

//abe#f##cg##d### 