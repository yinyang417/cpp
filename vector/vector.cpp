#include"vector.h"
#include<iostream>
#include<cmath>

using namespace std;
#define SIZE 16

template<class T> Vector<T>::Vector(int n) :dimension(n), size(n + SIZE), data(NULL)//构造函数
{
	if (size > 0)
	{
		data = new T[size];
	}
}

template<class T> Vector<T>::Vector(const Vector<T>& v) :data(NULL), size(0)//复制构造函数
{
	data = new T[v.size];
	dimension = v.dimension;
	size = v.size;
	for (int i = 0; i < size; i++)
	{
		data[i] = v.data[i];
	}
}

template<class T> Vector<T>::~Vector()//析构函数
{
	delete[] data;
}

template<class T> auto Vector<T>::InnerProduction(const Vector<T>& v) const//求两个向量内积
{
	if (dimension == 0 || v.dimension == 0)
	{
		double temp = 0;
		return temp;
	}
	else if (dimension != v.dimension)
	{
		cout << "错误：维数不正确" << endl;
		exit(1);
	}
	else
	{
		double temp = data[0] * v.data[0];
		for (int i = 1; i < dimension; i++)
		{
			temp = temp + data[i] * v.data[i];
		}
		return temp;
	}
}

template<class T> auto Vector<T>::OuterProduction(const Vector<T>& v)//求两个向量外积
{
	if (dimension == 0 || v.dimension == 0)
	{
		Vector<T> v3(0);
		return v3;
	}
	else if (dimension != v.dimension)
	{
		cout << "错误：维数不正确" << endl;
		exit(1);
	}
	else if (dimension != 3)
	{
		cout << "错误：无法计算" << endl;
		exit(1);
	}
	else
	{
		Vector<T> v3(3);
		v3.data[0] = data[1] * v.data[2] - v.data[1] * data[2];
		v3.data[1] = data[2] * v.data[0] - v.data[2] * data[0];
		v3.data[2] = data[0] * v.data[1] - v.data[0] * data[1];
		return v3;
	}
}

template<class T> Vector<T>& Vector<T>::elevation(int n, int pos)//在pos位置插入n个维度
{
	T* old = data;
	data = new T[size + n];
	auto temp = dimension;
	dimension = dimension + n;
	for (int i = 0; i < temp; i++)
	{
		data[i] = old[i];
	}
	for (int i = dimension - 1; i > pos; i--)
	{
		data[i] = data[i - n];
	}
	for (int i = pos; i - pos < n; i++)
	{
		cout << "请输入数据" << endl;
		cin >> data[i];
	}
	return *this;
}

template<class T> Vector<T>& Vector<T>::reduction(int n)//在指定位置减少n个维度
{
	int b;
	if (n >= dimension)
	{
		data = NULL;
		dimension = 0;
		size = 0;
	}
	else
	{
		for (int i = 0; i < n; i++)
		{
			cout << "请输入要删除的维度(1--" << dimension << ")" << endl;
			cin >> b;
			for (int j = b - 1; j < dimension - 1; j++)
			{
				data[j] = data[j] + 1;
			}
			dimension = dimension - 1;
			cout << "目前向量为：" << *this << endl;
		}
	}
	return *this;
}

template<class T> bool Vector<T>::ZeroVectorJudge() const//判断向量是否为零向量
{
	if (dimension == 0)
	{
		return true;
	}
	else
	{
		for (int i = 0; i < dimension; i++)
		{
			if (data[i] != 0)
			{
				return false;
			}
			return true;
		}
	}
}

template<class T> bool Vector<T>::ParallelJudge(const Vector<T>& v) const//判断两个向量是否平行
{
	double temp;
	temp = data[0] / v.data[0];
	for (int i = 1; i < dimension; i++)
	{
		if (temp == data[i] / v.data[i]);
		else
		{
			return false;
		}
	}
	return true;
}

template<class T> Vector<T> Vector<T>::judge(const Vector<T>& v1, const Vector<T>& v2)//判断两个向量的关系
{
	if (v1.ZeroVectorJudge() || v2.ZeroVectorJudge())
	{
		cout << "零向量的方向与任一向量平行，与任意向量共线，与任意向量垂直" << endl;
	}
	else if (v1.dimension == v2.dimension)
	{
		if (v1.InnerProduction(v2) == 0)
		{
			cout << "两向量垂直" << endl;
		}
		else if (v1.ParallelJudge(v2))
		{
			cout << "两向量平行或共线" << endl;
		}
		else
		{
			cout << "两向量无位置关系" << endl;
		}
	}
	else
	{
		cout << "维数不同无法判断" << endl;
	}
	return *this;
}

template<class T> ostream& operator<<(ostream& out, const Vector<T>& v)//重载<<
{
	if (v.dimension == 0)
	{
		cout << "(0)" << endl;
	}
	else
	{
		out << "(";
		for (int i = 0; i < v.dimension; i++)
		{
			out << v.data[i];
			if (i < v.dimension - 1)
			{
				out << ",";
			}
		}
		out << ")" << endl;
	}
	return out;
}

template<class T> istream& operator>>(istream& in, const Vector<T>& v)//重载>>
{
	for (int i = 0; i < v.dimension; i++)
	{
		cout << "请输入第" << i + 1 << "个数据" << endl;
		in >> v.data[i];
	}
	return in;
}

template<class T> Vector<T>& Vector<T>::operator=(const Vector<T>& v)//重载=
{
	delete[] data;
	size = v.size;
	data = new T[size];
	dimension = v.dimension;
	for (int i = 0; i < dimension; i++)
	{
		data[i] = v.data[i];
	}
	return *this;
}

template<class T> Vector<T> operator+(const Vector<T>& v1, const Vector<T>& v2)//重载+
{
	if (v2.dimension != v1.dimension)
	{
		cout << "错误：维数不正确" << endl;
		exit(1);
	}
	else
	{
		Vector<T> temp(v1.dimension);
		for (int i = 0; i < v1.dimension; i++)
		{
			temp.data[i] = v2.data[i] + v1.data[i];
		}
		return temp;
	}
}

template<class T> Vector<T> operator-(const Vector<T>& v1, const Vector<T>& v2)//重载-
{
	if (v1.dimension != v2.dimension)
	{
		cout << "错误：维数不正确" << endl;
		exit(1);
	}
	else
	{
		Vector<T> v3(v1.dimension);
		for (int i = 0; i < v1.dimension; i++)
		{
			v3.data[i] = v1.data[i] - v2.data[i];
		}
		return v3;
	}
}

template<class T> Vector<T>& Vector<T>::operator+=(const Vector<T>& v)//重载+=
{
	if (dimension != v.dimension)
	{
		cout << "错误：维数不正确" << endl;
		exit(1);
	}
	else
	{
		*this = *this + v;
		return *this;
	}
}

template<class T> bool operator==(const Vector<T>& v1, const Vector<T>& v2)//重载==
{
	if (v1.dimension == v2.dimension)
	{
		for (int i = 0; i < v1.dimension; i++)
		{
			if (v1.data[i] != v2.data[i])
			{
				return false;
			}
		}
		return true;
	}
	else
	{
		return false;
	}
}

template<class T> bool operator!=(const Vector<T>& v1, const Vector<T>& v2)//重载!=
{
	if (v1.dimension == v2.dimension)
	{
		for (int i = 0; i < v1.dimension; i++)
		{
			if (v1.data[i] != v2.data[i])
			{
				return true;
			}
		}
		return false;
	}
	else
	{
		return true;
	}
}

template<class T> T& Vector<T>::operator[](int id)//重载[]

{
	int temp = id - 1;
	if (id<=0 || id>dimension)
	{
		cout << "错误：维数不正确" << endl;
		exit(1);
	}
	else
	{
		return data[temp];
	}
}