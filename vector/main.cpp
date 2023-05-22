#include<bits/stdc++.h>
#include"vector.h"
#include"vector.cpp"
using namespace std;


int main()
{
	//system("pause");
	int n = 0;
	double a = 0;
	cout << "请输入第一个向量的维数" << endl;
	cin >> n;
	Vector<double> v1(n);
	cin >> v1;
	//v1.elevation(1,2);
	//Vector<double> v2(v1);
	cout << "请输入第二个向量的维数" << endl;
	cin >> n;
	Vector<double> v2(n);
	cin >> v2;
	//Vector<int> v2(n);
	//cin >> v2;
	//v2 += v1;
	//cout << v1.InnerProduction(v2) << endl;
	//cout << v1.OuterProduction(v2) << endl;
	//v1 = v2;
	//v1.judge(v1,v2);
	
	cout << v1[1] << endl;
	cout << v2 << endl;
	if (v1 != v2)
	{
		cout << "yes" << endl;
	}
	else
	{
		cout << "no" << endl;
	}
	//cout << v2 + v1 << endl;


	return 0;
}