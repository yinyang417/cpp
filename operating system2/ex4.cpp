#include<bits/stdc++.h>

using namespace std;

const string noname = "******";

struct file {
	string filename;
	string p_code;		//111可读可写可执行
	string p_code_tow;
	int file_length;
};

struct MFD {
	string username;
	file f[10];
}mfd[10];

int AFD[5];		//存放当前用户打开的文件的下标，初始化-1
int nowuser = -1;
int afdCnt = 0;	//当前已打开的文件数量

void init() {
	//初始化用户表和用户的文件
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			mfd[i].f[j].filename = noname;
			mfd[i].f[j].p_code = "000";
			mfd[i].f[j].p_code_tow = "000";
			mfd[i].f[j].file_length = 0;
		}
		mfd[i].username = "lv"+std::to_string(i);
	}	//mfd0
	mfd[0].f[0].filename = "good";
	mfd[0].f[0].p_code = "111";
	mfd[0].f[0].file_length = 101;
	mfd[0].f[1].filename = "kkk";
	mfd[0].f[1].p_code = "011";
	mfd[0].f[1].file_length = 51;
	mfd[0].f[2].filename = "test";
	mfd[0].f[2].p_code = "101";
	mfd[0].f[2].file_length = 775;
	mfd[0].f[3].filename = "hhh";
	mfd[0].f[3].p_code = "110";
	mfd[0].f[3].file_length = 46;
	//mfd1
	mfd[1].f[0].filename = "ppp";
	mfd[1].f[0].p_code = "000";
	mfd[1].f[0].file_length = 20;
	//初始化AFD为-1表示全部未打开，无文件
	for (int i = 0; i < 5; i++) {
		AFD[i] = -1;
	}
	nowuser = -1;
}

void selectUser() {
	cout << "当前系统中存在的用户：" << endl;
	for (int i = 0; i < 10; i++) {
		cout << mfd[i].username << endl;
	}
	while (true) {
		cout << "请输入您想要登录的用户姓名：";
		string name;
		cin >> name;
		bool f = 0;
		for (int i = 0; i < 10; i++) {
			if (mfd[i].username == name) {
				f = 1; nowuser = i; break;
			}
		}
		if (f == 0) {
			cout << "用户姓名输入错误！请重新输入！" << endl;
		}
		else {
			cout << "登录成功！" << endl;
			system("pause");
			break;
		}
	}
	system("cls");
}

void showfile() {
	cout << "文件名称\t读写执\t\t文件长度";
	cout << "\t\t当前已打开文件有("<<afdCnt<<"个,最多运行5个):";
	for (int i = 0; i < afdCnt; i++) {
		cout << mfd[nowuser].f[AFD[i]].filename<<"("<< mfd[nowuser].f[AFD[i]].p_code_tow <<")" << "  ";
	}
	cout << endl;
	for (int i = 0; i < 10; i++) {
		cout << mfd[nowuser].f[i].filename << "\t\t" << mfd[nowuser].f[i].p_code << "\t\t" << mfd[nowuser].f[i].file_length << endl;
	}
}

void showMenu() {
	cout << "用户" << mfd[nowuser].username << "您好！欢迎使用文件系统！" << endl;
	cout << "您的文件目录如下：\n";
	showfile();
	cout << "\n";
	cout << "*****您可以执行的操作(大写)*****\n";
	cout << "**CREATE-(1)----------新建文件**\n";
	cout << "**DELETE-(2)----------删除文件**\n";
	cout << "**OPEN---(3)----------打开文件**\n";
	cout << "**CLOSE--(4)----------关闭文件**\n";
	cout << "**READ---(5)----------读取文件**\n";
	cout << "**WRITE--(6)----------写入文件**\n";
	cout << "**RENAME-(7)--------重命名文件**\n";
	cout << "**CHANGE-(8)------更改文件权限**\n";
	cout << "**BYE----(9)----------关闭系统**\n";
	cout << "********************************\n";
}

void createNewFile() {
	string name, code;
	while (true) {
		cout << "新建的文件名称是？\t";
		cin >> name;
		//检验是否同名
		bool samename = 0;
		for (int i = 0; i < 10; i++) {
			if (mfd[nowuser].f[i].filename == name) {
				samename = 1; break;
			}
		}
		if (samename) {
			cout << "文件名称重复，请重新输入！" << endl;
		}
		else break;
	}
	while (true) {
		cout << "新建的文件的权限为？(读写执)\t";
		cin >> code;
		if (code.length() != 3) {
			cout << "新建文件权限输入错误！请重新输入！" << endl;
		}
		else break;
	}
	bool success = 0;
	for (int i = 0; i < 10; i++) {
		if (mfd[nowuser].f[i].filename == noname){
			mfd[nowuser].f[i].filename = name;
			mfd[nowuser].f[i].p_code = code;
			mfd[nowuser].f[i].file_length = 0;
			success = 1;
			break;
		}
	}
	if (success) cout << "新建文件成功！" << endl;
	else cout << "用户文件已满，创建文件失败！" << endl;
	system("pause");
}

void deleteFile() {
	while (true) {
		cout << "请输入您想要删除的文件名称:\t";
		string name;
		cin >> name;
		int fileId = -1;
		bool isopen = 0;
		for (int i = 0; i < afdCnt; i++) {
			if (mfd[nowuser].f[AFD[i]].filename == name) {
				isopen = 1; fileId = i; break;
			}
		}
		if (isopen) {
			//文件已打开，需要关闭
			mfd[nowuser].f[fileId].p_code_tow = "000";AFD[--afdCnt] = -1;
		}
		bool search = 0;
		for (int i = 0; i < 10; i++) {
			if (mfd[nowuser].f[i].filename == name) {
				mfd[nowuser].f[i].filename = noname;
				mfd[nowuser].f[i].file_length = 0;
				mfd[nowuser].f[i].p_code ="000";
				search = 1;
				break;
			}
		}
		if (search) {
			cout << "文件删除成功！" << endl;break;
		}
		else cout << "文件名称输入错误，该文件不存在！请重新输入" << endl;
	}
	system("pause");
}

void openFile() {
	if (afdCnt == 5) {
		cout << "当前运行文件已满！无法打开文件！" << endl;
		system("pause");
		return;
	}
	int fileId = -1;			//打开文件的下标
	cout << "请输入想要打开的文件名称:";
	string name;
	cin >> name;
	bool isExist = 0;
	//检查文件是否存在
	for (int i = 0; i < 10; i++) {
		if (mfd[nowuser].f[i].filename == name) {
			isExist = 1; fileId = i; break;
		}
	}
	if (!isExist) {
		cout << "该文件不存在！"; system("pause");return;
	}
	bool isopen = 0;
	for (int i = 0; i < afdCnt; i++) {
		if (mfd[nowuser].f[AFD[i]].filename == name) {
			isopen = 1; break;
		}
	}
	if (isopen) {
		cout << "该文件已打开！";
		system("pause");
		return;
	}
	else {
		bool success = 1;
		while (true) {
			//cout << "请输入此次打开的二级保护码：";
			string code;
			code = mfd[nowuser].f[fileId].p_code;
			//cin >> code;
			//验证二级保护码
			for (int i = 0; i < 3; i++) {
				if (code[i] > mfd[nowuser].f[fileId].p_code[i]||code[i]<'0' || code[i]>'1') {
					success = 0; break;
				}
			}
			if (code.length() != 3)success = 0;
	 				if (success) {
				AFD[afdCnt++] = fileId;
				mfd[nowuser].f[fileId].p_code_tow = code;
				break;
			}
			else cout << "二级保护码必须为一级保护码的子集！请重新输入！" << endl;
		}
		cout << "文件打开成功！" << endl;
		system("pause");
	}
}

void closeFile() {
	int fileId = -1;			//关闭文件的下标
	cout << "请输入想要关闭的文件名称:";
	string name;
	cin >> name;
	bool isopen = 0;
	for (int i = 0; i < afdCnt; i++) {
		if (mfd[nowuser].f[AFD[i]].filename == name) {
			isopen = 1; fileId = AFD[i];break;
		}
	}
	if (isopen) {
		mfd[nowuser].f[fileId].p_code_tow = "000";
		AFD[--afdCnt] = -1;
	}
	else cout << "该文件未打开！关闭失败！" << endl;
	system("pause");
}

void readFile() {
	int fileId = -1;			//关闭文件的下标
	cout << "请输入想要读取的文件名称:";
	string name;
	cin >> name;
	bool isopen = 0;
	for (int i = 0; i < afdCnt; i++) {
		if (mfd[nowuser].f[AFD[i]].filename == name) {
			isopen = 1; fileId = AFD[i]; break;
		}
	}
	if (isopen) {
		//检查是否有读取权限
		if (mfd[nowuser].f[fileId].p_code_tow[0] != '1') cout << "无读权限！读取文件失败！" << endl;
		else cout << "读取成功！该文件内容长度为:" << mfd[nowuser].f[fileId].file_length << endl;

	}
	else cout << "该文件未打开！读取失败！" << endl;
	system("pause");
}

void writeFile() {
	int fileId = -1;			//写文件的下标
	cout << "请输入想要读取的文件名称:";
	string name;
	cin >> name;
	bool isopen = 0;
	for (int i = 0; i < afdCnt; i++) {
		if (mfd[nowuser].f[AFD[i]].filename == name) {
			isopen = 1; fileId = AFD[i]; break;
		}
	}
	if (isopen) {
		//检查是否有写权限
		if (mfd[nowuser].f[fileId].p_code_tow[1] != '1') cout << "无写权限！写入文件失败！" << endl;
		else {
			cout << "请输入写入文件内容长度(9位以内):";
			int length = 0;
			cin >> length;
			mfd[nowuser].f[fileId].file_length += length;
			cout << "写入文件成功！";

		}
	}
	else cout << "该文件未打开！写入失败！" << endl;
	system("pause");
}

void renameFile() {
	while (true) {
		cout << "请输入想要重命名的文件名称:";
		string name;
		cin >> name;
		int fileId = -1;
		bool isExist = 0;
		//检查文件是否存在
		for (int i = 0; i < 10; i++) {
			if (mfd[nowuser].f[i].filename == name) {
				isExist = 1; fileId = i; break;
			}
		}
		if (isExist) {
			cout << "请输入新的名称：";
			string newname;
			cin >> newname;
			mfd[nowuser].f[fileId].filename = newname;
			cout << "文件重命名成功！" << endl;
			break;
		}
		else {
			cout << "文件同名，请重新命名！" << endl; break;
		}
	}
	system("pause");
}

void changeFile() {
	int fileId = -1;			//写文件的下标
	cout << "请输入想要更改权限的文件名称:";
	string name;
	cin >> name;
	bool isExist = 0;
	//检查文件是否存在
	for (int i = 0; i < 10; i++) {
		if (mfd[nowuser].f[i].filename == name) {
			isExist = 1; fileId = i; break;
		}
	}
	if (isExist) {
		bool isopen = 0;
		for (int i = 0; i < afdCnt; i++) {
			if (mfd[nowuser].f[AFD[i]].filename == name) {
				isopen = 1; fileId = AFD[i]; break;
			}
		}
		if (isopen) cout << "文件运行中，请先关闭文件！" << endl;
				else {
			cout << "请输入新的权限:";
			string code;
			cin >> code;
			if (code.length() != 3)cout << "输入错误！请重新输入！" << endl;
			else {
				mfd[nowuser].f[fileId].p_code = code;
				cout << "更改权限成功！" << endl;
			}
		}
	}
	else {
		cout << "该文件不存在！" << endl;
	}
	system("pause");
}

int main() {
	init();
	selectUser();
	bool bye = 0;
	int commond;
	while (bye==0) {
		showMenu();
		cout << "**请输入您想要执行的命令(数字1-7):";
		cin >> commond;
		switch (commond){
		case 1: 
			createNewFile();
			break;
		case 2:
			deleteFile();
			break;
		case 3:
			openFile();
			break;
		case 4:
			closeFile();
			break;
		case 5:
			readFile();
			break;
		case 6:
			writeFile();
			break;
		case 7:
			renameFile();
			break;
		case 8:
			changeFile();
			break;
		case 9:
			bye = 1;
			break;
		default:
			cout << "输入错误，请重新输入！" << endl;
			system("pause");
			break;
		}
		
		system("cls");

		if (bye == 1) {
			showfile();
			cout << "GOOD BYE!" << endl;
			break;
		}
	}
	return 0;
}

	

	
