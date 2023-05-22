#ifndef VECTOR_H
#define VECTOR_H
#include<iostream>
#include<cmath>

using namespace std;
#define SIZE 16


template <typename T> class Vector
{
public:
	//friend class T1;
	//template <typename T1> Vector(const Vector<T1>& temp)
	//{
	//	delete[] data;
	//	data = new T[temp.size*2];
	//	for (int i = 0; i < dimension; i++)
	//	{
	//		data[i] = temp.data[i];
	//	}
	//}
	Vector(const int n);//构造函数
	Vector(const Vector<T>& v);//复制构造函数
	~Vector();//析构函数

	auto InnerProduction(const Vector<T>& v)const;//求两个向量内积
	auto OuterProduction(const Vector<T>& v);//求两个向量外积

	Vector<T>& elevation(int n, int pos);//在pos位置插入n个维度
	Vector<T>& reduction(int n);//在指定位置减少n个维度

	bool ZeroVectorJudge()const;//判断向量是否为零向量
	bool ParallelJudge(const Vector<T>& v)const;//判断两个向量是否平行
	Vector<T> judge(const Vector<T>& v1, const Vector<T>& v2);//判断两个向量的关系

	template<class U> friend ostream& operator<<(ostream& out, const Vector<U>& v);//重载<<
	template<class U> friend istream& operator>>(istream& in, const Vector<U>& v);//重载>>
	//template <typename T1>
	template<class U> friend Vector<U> operator+(const Vector<U>& v1, const Vector<U>& v2);//重载+
	//template <typename T1>
	template<class U> friend Vector<T> operator-(const Vector<U>& v1, const Vector<U>& v2);//重载-
	template<class U> friend bool operator==(const Vector<U>& v1, const Vector<U>& v2);//重载==
	template<class U> friend bool operator!=(const Vector<U>& v1, const Vector<U>& v2);//重载!=

	//template <typename T1>
	Vector<T>& operator=(const Vector<T>& v);//重载=
	Vector<T>& operator+=(const Vector<T>& v);//重载+=

	T& operator[](int id);//重载[]
private:
	T* data;//向量的具体数据
	int dimension;//向量的维度
	int size;//向量的空间大小



	//void Error(const char* cs)const { cout << cs << endl; exit(1); }//错误信息报告
};

#endif