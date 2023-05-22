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
	Vector(const int n);//���캯��
	Vector(const Vector<T>& v);//���ƹ��캯��
	~Vector();//��������

	auto InnerProduction(const Vector<T>& v)const;//�����������ڻ�
	auto OuterProduction(const Vector<T>& v);//�������������

	Vector<T>& elevation(int n, int pos);//��posλ�ò���n��ά��
	Vector<T>& reduction(int n);//��ָ��λ�ü���n��ά��

	bool ZeroVectorJudge()const;//�ж������Ƿ�Ϊ������
	bool ParallelJudge(const Vector<T>& v)const;//�ж����������Ƿ�ƽ��
	Vector<T> judge(const Vector<T>& v1, const Vector<T>& v2);//�ж����������Ĺ�ϵ

	template<class U> friend ostream& operator<<(ostream& out, const Vector<U>& v);//����<<
	template<class U> friend istream& operator>>(istream& in, const Vector<U>& v);//����>>
	//template <typename T1>
	template<class U> friend Vector<U> operator+(const Vector<U>& v1, const Vector<U>& v2);//����+
	//template <typename T1>
	template<class U> friend Vector<T> operator-(const Vector<U>& v1, const Vector<U>& v2);//����-
	template<class U> friend bool operator==(const Vector<U>& v1, const Vector<U>& v2);//����==
	template<class U> friend bool operator!=(const Vector<U>& v1, const Vector<U>& v2);//����!=

	//template <typename T1>
	Vector<T>& operator=(const Vector<T>& v);//����=
	Vector<T>& operator+=(const Vector<T>& v);//����+=

	T& operator[](int id);//����[]
private:
	T* data;//�����ľ�������
	int dimension;//������ά��
	int size;//�����Ŀռ��С



	//void Error(const char* cs)const { cout << cs << endl; exit(1); }//������Ϣ����
};

#endif