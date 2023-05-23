#include<bits/stdc++.h>
using namespace std;

typedef struct node {
	int data;
	struct node* firstchild;
	struct node* nextsibling;
}TreeNode, * Tree;

void CreateTree(Tree& t)
{
	int i;
	cin >> i;
	if (i == -1)
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

bool IsSortTree(Tree& t)
{
	if (t == NULL)
	{
		return true;
	}
	if (t->firstchild != NULL && t->firstchild->data > t->data)
	{
		return false;
	}
	if (t->nextsibling != NULL && t->nextsibling->data < t->data)
	{
		return false;
	}
	return IsSortTree(t->firstchild) && IsSortTree(t->nextsibling);
}

void Insert(Tree& t, int x)
{
	if (t == NULL)
	{
		t = new TreeNode;
		t->data = x;
		t->firstchild = NULL;
		t->nextsibling = NULL;
		cout << "插入成功" << endl;
	}
	else
	{
		if (x < t->data)
		{
			Insert(t->firstchild, x);
		}
		else if(x > t->data)
		{
			Insert(t->nextsibling, x);
		}
		else
		{
			cout << "该节点已存在" << endl;
		}
	}
}

void displayM(Tree& t)
{
	if (t != NULL)
	{
		displayM(t->firstchild);
		cout << t->data << " ";
		displayM(t->nextsibling);
	}
}

void displayF(Tree& t)
{
	if (t != NULL)
	{
		cout << t->data << " ";
		displayF(t->firstchild);
		displayF(t->nextsibling);
	}
}

void Delete(Tree& t, int x)
{
	if (t == NULL)
	{
		cout << "该节点不存在" << endl;
	}
	else
	{
		if (x < t->data)
		{
			Delete(t->firstchild, x);
		}
		else if (x > t->data)
		{
			Delete(t->nextsibling, x);
		}
		else
		{
			if (t->firstchild == NULL)
			{
				t = t->nextsibling;
			}
			else if (t->nextsibling == NULL)
			{
				t = t->firstchild;
			}
			else
			{
				Tree p = t->firstchild;
				while (p->nextsibling != NULL)//找到左子树的最大节点
				{
					p = p->nextsibling;
				}
				p->nextsibling = t->nextsibling;//将右子树接到左子树的最大节点
				t = t->firstchild;//删除该节点,将左子树接到该节点
			}
			cout << "删除成功" << endl;
		}
	}
}

int main()
{
	Tree t;
	CreateTree(t);
	cout << "先序遍历：" << endl;
	displayF(t);
	cout << endl;
	cout << "中序遍历：" << endl;
	displayM(t);
	cout << endl;

	if (IsSortTree(t))
	{
		cout << "是二叉排序树" << endl;
		cout<<"请输入要插入的节点：";
		int x;
		cin >> x;
		Insert(t, x);
		cout << "先序遍历：" << endl;
		displayF(t);
		cout<<endl;
		cout << "中序遍历：" << endl;
		displayM(t);
		cout << endl;
		cout<<"请输入要删除的节点：";
		cin >> x;
		Delete(t, x);
		cout << "先序遍历：" << endl;
		displayF(t);
		cout << endl;
		cout << "中序遍历：" << endl;
		displayM(t);
		cout << endl;
	}
	else
	{
		cout << "不是二叉排序树" << endl;
		return 0;
	}
	
	return 0;
}

//yes:
//39 11 8 -1 -1 23 -1 34 -1 -1 68 46 -1 -1 75 71 -1 -1 86 -1 -1
//8 11 23 34 39 46 68 71 75 86
//no:
//8 1 -1 -1 3 -1 -1
//1 8 3