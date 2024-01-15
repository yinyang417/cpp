#include<bits/stdc++.h>

using namespace std;

const int p = 64;
const int vmsize = 32 * 1024;//�������32k
int address[p];	//��ַ������255��
int pageno[p];	//��ַת����ҳ��

void init() 
{
	cout << "����Ϊ�����ַ��:" << endl;
	srand(time(0));
	cout << "ҳ���ַ������Ϊ��" << p << endl;
	for (int i = 0; i <= p; i++) 
	{
		int t = rand() % vmsize;			//������ɵ�ַ
		address[i] = t;
		cout << "a["<<i<<"]="<<t;
		if (i % 4 == 3)cout << endl;
		else cout << "\t";
	}
	cout << endl;
	cout << "= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =" << endl;
}

//��ַ��ҳ�ŵ�ת��
void changeAddress(int pagesize) 
{
	pagesize *= 1024;
	memset(pageno, 0, sizeof(pageno));
	for (int i = 0; i < p; i++) 
	{
		pageno[i] = address[i] / pagesize;
		cout << "pageno[" << i << "]=" << pageno[i];
		if (i % 4 == 3)cout << endl;
		else cout << "\t";
	}
	cout << endl;
}

void OPT(int m) 
{	
	int* que = new int[m];
	int cnt = 0;
	int changeCnt = 0;
	for (int i = 0; i <p; i++) 
	{
		//�жϸ�ҳ���Ƿ������ڴ���
		bool f = 0;
		for (int k = 0; k < cnt; k++) 
		{
			if (pageno[i] == que[k]) 
			{
				f = 1; break;
			}
		}
		if (f == 1) 
		{
			//���ڴ��У�����
			continue;
		}
		else 
		{
			//�����ڴ��У��ж��Ƿ����ˣ�Ҫ�û�ҳ��
			if (cnt == m) 
			{
				changeCnt++;
				//�����жϣ�ȡ��������ֵĵ��ý����滻
				int latestIdx = -1;
				int exchangeIdx = 0;
				for (int j = 0; j < cnt; j++) 
				{
					bool isExist = 0;
					for (int k = i+1; k <p; k++) 
					{
						if (pageno[k] == que[j]) 
						{
							isExist = 1;//���ֹ�
							if (k > latestIdx) 
							{
								latestIdx = k;
								exchangeIdx = j;
							}
							break;
						}
					}
					//��ҳ����δʹ��
					if (isExist == 0) 
					{
						exchangeIdx = j;
						break;
					}
				}
				que[exchangeIdx] = pageno[i];
			}
			else 
			{
				que[cnt++] = pageno[i];
			}
		}
}
	
	double score = 1 - ((double)changeCnt / p);
	cout << m<<"\t\t\t" << score << endl;
}

void LRU(int m) {
	int* que = new int[m];
	int cnt = 0;
	int changeCnt = 0;
	for (int i = 0; i < p; i++) {
		//�жϸ�ҳ���Ƿ������ڴ���
		bool f = 0;
		for (int k = 0; k < cnt; k++) {
			if (pageno[i] == que[k]) {
				f = 1;
				if (k == 0)break;		//ԭ������β�������ö�
				//���ڴ��У��������������β��������0λ�ô���
				int temp = que[k];
				//����Ų��
				for (int x = k-1; x >=0; x--) {
					que[x + 1] = que[x];
				}
				que[0] = temp;
				break;
			}
		}
		if (f == 1) {
			continue;
		}
		else {
			//�����ڴ��У��ж��Ƿ����ˣ�Ҫ�û�ҳ��
			if (cnt == m) {
				changeCnt++;
				//���ײ���̭������β���������ƶ�
				for (int x = cnt - 1; x > 0; x--) {
					que[x] = que[x-1];
				}
				que[0] = pageno[i];
			}
			else {
				//δ�����ŵ������β��
				for (int x = cnt; x > 0; x--) {
					que[x] = que[x - 1];
				}
				que[0] = pageno[i];
				cnt++;
			}
		}
}
	//cout <<"changeCnt:"<< changeCnt << endl;
	double score = 1 - ((double)changeCnt / p);
	cout << m << "\t\t\t" << score << endl;
}

void fifo(int m) {
	int* que = new int[m];
	int cnt = 0;
	int changeCnt = 0;
	for (int i = 0; i < p; i++) {
		//�жϸ�ҳ���Ƿ������ڴ���
		bool f = 0;
		for (int k = 0; k < cnt; k++) {
			if (pageno[i] == que[k]) {
				f = 1; break;
			}
		}
		if (f == 1) {
			continue;
		}
		else {
			//�����ڴ��У��ж��Ƿ����ˣ�Ҫ�û�ҳ��
			if (cnt == m) {
				changeCnt++;
				//��0��̭������β���������ƶ�
				for (int x = 0; x<cnt-1; x++) {
					que[x] = que[x +1];
				}
				que[cnt - 1] = pageno[i];
			}
			else {
				//δ�����ŵ������β��
				que[cnt++] = pageno[i];
			}
		}
	}
	//cout <<"changeCnt:"<< changeCnt << endl;
	double score = 1 - ((double)changeCnt / p);
	cout << m << "\t\t\t" << score << endl;
}

int main() {
	init();
	while (true) 
	{
		cout << "===================================================\n";
		cout << "ѡ���㷨(opt/lru/fifo):";
		string str;
		cin >> str;
		if (str == "opt") 
		{
				cout << "ҳ���СΪ1k�ֽ�ʱÿ�������ַ����Ӧ��ҳ��:" << endl;
				changeAddress(1);		//pagesize 1k����ת��
				cout << "������ڴ��ҳ����\tҳ��������" << endl;
				OPT(10);//ʵ��10ҳ
				cout << endl;
		}
		else if(str=="lru") 
		{
				cout << "ҳ���СΪ1k�ֽ�ʱÿ�������ַ����Ӧ��ҳ��:" << endl;
				changeAddress(1);		//pagesize 1k����ת��
				cout << "������ڴ��ҳ����\tҳ��������" << endl;
				LRU(10);//ʵ��10ҳ
				cout << endl;
		}
		else if (str == "fifo") 
		{
				cout << "ҳ���СΪ1k�ֽ�ʱÿ�������ַ����Ӧ��ҳ��:" << endl;
				changeAddress(1);		//pagesize 1k����ת��
				cout << "������ڴ��ҳ����\tҳ��������" << endl;
				fifo(10);//ʵ��10ҳ
				cout << endl;
		}
	}
	return 0;
}