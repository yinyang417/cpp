#include<bits/stdc++.h>

using namespace std;

const int p = 64;
const int vmsize = 32 * 1024;//虚存容量32k
int address[p];	//地址流长度255个
int pageno[p];	//地址转换到页号

void init() 
{
	cout << "以下为虚拟地址流:" << endl;
	srand(time(0));
	cout << "页面地址流长度为：" << p << endl;
	for (int i = 0; i <= p; i++) 
	{
		int t = rand() % vmsize;			//随机生成地址
		address[i] = t;
		cout << "a["<<i<<"]="<<t;
		if (i % 4 == 3)cout << endl;
		else cout << "\t";
	}
	cout << endl;
	cout << "= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =" << endl;
}

//地址到页号的转换
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
		//判断该页面是否仍在内存中
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
			//在内存中，继续
			continue;
		}
		else 
		{
			//不在内存中，判断是否满了，要置换页面
			if (cnt == m) 
			{
				changeCnt++;
				//依次判断，取出最晚出现的调用进行替换
				int latestIdx = -1;
				int exchangeIdx = 0;
				for (int j = 0; j < cnt; j++) 
				{
					bool isExist = 0;
					for (int k = i+1; k <p; k++) 
					{
						if (pageno[k] == que[j]) 
						{
							isExist = 1;//出现过
							if (k > latestIdx) 
							{
								latestIdx = k;
								exchangeIdx = j;
							}
							break;
						}
					}
					//该页后续未使用
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
		//判断该页面是否仍在内存中
		bool f = 0;
		for (int k = 0; k < cnt; k++) {
			if (pageno[i] == que[k]) {
				f = 1;
				if (k == 0)break;		//原本就在尾部，不用动
				//在内存中，将其调整到链表尾部（数组0位置处）
				int temp = que[k];
				//整体挪移
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
			//不在内存中，判断是否满了，要置换页面
			if (cnt == m) {
				changeCnt++;
				//将首部淘汰，放入尾部，整体移动
				for (int x = cnt - 1; x > 0; x--) {
					que[x] = que[x-1];
				}
				que[0] = pageno[i];
			}
			else {
				//未满，放到链表的尾部
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
		//判断该页面是否仍在内存中
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
			//不在内存中，判断是否满了，要置换页面
			if (cnt == m) {
				changeCnt++;
				//将0淘汰，放入尾部，整体移动
				for (int x = 0; x<cnt-1; x++) {
					que[x] = que[x +1];
				}
				que[cnt - 1] = pageno[i];
			}
			else {
				//未满，放到链表的尾部
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
		cout << "选择算法(opt/lru/fifo):";
		string str;
		cin >> str;
		if (str == "opt") 
		{
				cout << "页面大小为1k字节时每个虚拟地址所对应的页号:" << endl;
				changeAddress(1);		//pagesize 1k进行转换
				cout << "分配给内存的页面数\t页面命中率" << endl;
				OPT(10);//实存10页
				cout << endl;
		}
		else if(str=="lru") 
		{
				cout << "页面大小为1k字节时每个虚拟地址所对应的页号:" << endl;
				changeAddress(1);		//pagesize 1k进行转换
				cout << "分配给内存的页面数\t页面命中率" << endl;
				LRU(10);//实存10页
				cout << endl;
		}
		else if (str == "fifo") 
		{
				cout << "页面大小为1k字节时每个虚拟地址所对应的页号:" << endl;
				changeAddress(1);		//pagesize 1k进行转换
				cout << "分配给内存的页面数\t页面命中率" << endl;
				fifo(10);//实存10页
				cout << endl;
		}
	}
	return 0;
}