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
	if (height(t->firstchild) + 1 > height(t->nextsibling))//左子树为下一层，+1
	{
		return height(t->firstchild) + 1;
	}
	else
	{
		return height(t->nextsibling);
	}
}

int degree(Tree& t)//广度优先遍历
{
	if (t == NULL)
	{
		return 0;
	}
	queue<TreeNode*> q;
	TreeNode* p;
	int max = 0;
	q.push(t);//根节点入队
	while (!q.empty())
	{
		int deg = q.size();//记录最大度数
		for (int i = 0; i < deg; i++)
		{
			p = q.front();//p出队
			q.pop();
			p = p->firstchild;
			while (p != NULL)//将下一层的所有节点入队
			{
				q.push(p);
				p = p->nextsibling;
			}
		}
		if (max < deg)//将最大度数赋值给max
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

	cout << "这棵树的高度是：";
	cout << height(t) << endl;
	cout << "这棵树的度是：";
	cout << degree(t) << endl;
	return 0;
}

//abe#f##cg##d### 