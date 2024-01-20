#include<bits/stdc++.h>

using namespace std;

const string noname = "******";

struct file {
	string filename;
	string p_code;		//111�ɶ���д��ִ��
	string p_code_tow;
	int file_length;
};

struct MFD {
	string username;
	file f[10];
}mfd[10];

int AFD[5];		//��ŵ�ǰ�û��򿪵��ļ����±꣬��ʼ��-1
int nowuser = -1;
int afdCnt = 0;	//��ǰ�Ѵ򿪵��ļ�����

void init() {
	//��ʼ���û�����û����ļ�
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
	//��ʼ��AFDΪ-1��ʾȫ��δ�򿪣����ļ�
	for (int i = 0; i < 5; i++) {
		AFD[i] = -1;
	}
	nowuser = -1;
}

void selectUser() {
	cout << "��ǰϵͳ�д��ڵ��û���" << endl;
	for (int i = 0; i < 10; i++) {
		cout << mfd[i].username << endl;
	}
	while (true) {
		cout << "����������Ҫ��¼���û�������";
		string name;
		cin >> name;
		bool f = 0;
		for (int i = 0; i < 10; i++) {
			if (mfd[i].username == name) {
				f = 1; nowuser = i; break;
			}
		}
		if (f == 0) {
			cout << "�û���������������������룡" << endl;
		}
		else {
			cout << "��¼�ɹ���" << endl;
			system("pause");
			break;
		}
	}
	system("cls");
}

void showfile() {
	cout << "�ļ�����\t��дִ\t\t�ļ�����";
	cout << "\t\t��ǰ�Ѵ��ļ���("<<afdCnt<<"��,�������5��):";
	for (int i = 0; i < afdCnt; i++) {
		cout << mfd[nowuser].f[AFD[i]].filename<<"("<< mfd[nowuser].f[AFD[i]].p_code_tow <<")" << "  ";
	}
	cout << endl;
	for (int i = 0; i < 10; i++) {
		cout << mfd[nowuser].f[i].filename << "\t\t" << mfd[nowuser].f[i].p_code << "\t\t" << mfd[nowuser].f[i].file_length << endl;
	}
}

void showMenu() {
	cout << "�û�" << mfd[nowuser].username << "���ã���ӭʹ���ļ�ϵͳ��" << endl;
	cout << "�����ļ�Ŀ¼���£�\n";
	showfile();
	cout << "\n";
	cout << "*****������ִ�еĲ���(��д)*****\n";
	cout << "**CREATE-(1)----------�½��ļ�**\n";
	cout << "**DELETE-(2)----------ɾ���ļ�**\n";
	cout << "**OPEN---(3)----------���ļ�**\n";
	cout << "**CLOSE--(4)----------�ر��ļ�**\n";
	cout << "**READ---(5)----------��ȡ�ļ�**\n";
	cout << "**WRITE--(6)----------д���ļ�**\n";
	cout << "**RENAME-(7)--------�������ļ�**\n";
	cout << "**CHANGE-(8)------�����ļ�Ȩ��**\n";
	cout << "**BYE----(9)----------�ر�ϵͳ**\n";
	cout << "********************************\n";
}

void createNewFile() {
	string name, code;
	while (true) {
		cout << "�½����ļ������ǣ�\t";
		cin >> name;
		//�����Ƿ�ͬ��
		bool samename = 0;
		for (int i = 0; i < 10; i++) {
			if (mfd[nowuser].f[i].filename == name) {
				samename = 1; break;
			}
		}
		if (samename) {
			cout << "�ļ������ظ������������룡" << endl;
		}
		else break;
	}
	while (true) {
		cout << "�½����ļ���Ȩ��Ϊ��(��дִ)\t";
		cin >> code;
		if (code.length() != 3) {
			cout << "�½��ļ�Ȩ������������������룡" << endl;
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
	if (success) cout << "�½��ļ��ɹ���" << endl;
	else cout << "�û��ļ������������ļ�ʧ�ܣ�" << endl;
	system("pause");
}

void deleteFile() {
	while (true) {
		cout << "����������Ҫɾ�����ļ�����:\t";
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
			//�ļ��Ѵ򿪣���Ҫ�ر�
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
			cout << "�ļ�ɾ���ɹ���" << endl;break;
		}
		else cout << "�ļ�����������󣬸��ļ������ڣ�����������" << endl;
	}
	system("pause");
}

void openFile() {
	if (afdCnt == 5) {
		cout << "��ǰ�����ļ��������޷����ļ���" << endl;
		system("pause");
		return;
	}
	int fileId = -1;			//���ļ����±�
	cout << "��������Ҫ�򿪵��ļ�����:";
	string name;
	cin >> name;
	bool isExist = 0;
	//����ļ��Ƿ����
	for (int i = 0; i < 10; i++) {
		if (mfd[nowuser].f[i].filename == name) {
			isExist = 1; fileId = i; break;
		}
	}
	if (!isExist) {
		cout << "���ļ������ڣ�"; system("pause");return;
	}
	bool isopen = 0;
	for (int i = 0; i < afdCnt; i++) {
		if (mfd[nowuser].f[AFD[i]].filename == name) {
			isopen = 1; break;
		}
	}
	if (isopen) {
		cout << "���ļ��Ѵ򿪣�";
		system("pause");
		return;
	}
	else {
		bool success = 1;
		while (true) {
			//cout << "������˴δ򿪵Ķ��������룺";
			string code;
			code = mfd[nowuser].f[fileId].p_code;
			//cin >> code;
			//��֤����������
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
			else cout << "�������������Ϊһ����������Ӽ������������룡" << endl;
		}
		cout << "�ļ��򿪳ɹ���" << endl;
		system("pause");
	}
}

void closeFile() {
	int fileId = -1;			//�ر��ļ����±�
	cout << "��������Ҫ�رյ��ļ�����:";
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
	else cout << "���ļ�δ�򿪣��ر�ʧ�ܣ�" << endl;
	system("pause");
}

void readFile() {
	int fileId = -1;			//�ر��ļ����±�
	cout << "��������Ҫ��ȡ���ļ�����:";
	string name;
	cin >> name;
	bool isopen = 0;
	for (int i = 0; i < afdCnt; i++) {
		if (mfd[nowuser].f[AFD[i]].filename == name) {
			isopen = 1; fileId = AFD[i]; break;
		}
	}
	if (isopen) {
		//����Ƿ��ж�ȡȨ��
		if (mfd[nowuser].f[fileId].p_code_tow[0] != '1') cout << "�޶�Ȩ�ޣ���ȡ�ļ�ʧ�ܣ�" << endl;
		else cout << "��ȡ�ɹ������ļ����ݳ���Ϊ:" << mfd[nowuser].f[fileId].file_length << endl;

	}
	else cout << "���ļ�δ�򿪣���ȡʧ�ܣ�" << endl;
	system("pause");
}

void writeFile() {
	int fileId = -1;			//д�ļ����±�
	cout << "��������Ҫ��ȡ���ļ�����:";
	string name;
	cin >> name;
	bool isopen = 0;
	for (int i = 0; i < afdCnt; i++) {
		if (mfd[nowuser].f[AFD[i]].filename == name) {
			isopen = 1; fileId = AFD[i]; break;
		}
	}
	if (isopen) {
		//����Ƿ���дȨ��
		if (mfd[nowuser].f[fileId].p_code_tow[1] != '1') cout << "��дȨ�ޣ�д���ļ�ʧ�ܣ�" << endl;
		else {
			cout << "������д���ļ����ݳ���(9λ����):";
			int length = 0;
			cin >> length;
			mfd[nowuser].f[fileId].file_length += length;
			cout << "д���ļ��ɹ���";

		}
	}
	else cout << "���ļ�δ�򿪣�д��ʧ�ܣ�" << endl;
	system("pause");
}

void renameFile() {
	while (true) {
		cout << "��������Ҫ���������ļ�����:";
		string name;
		cin >> name;
		int fileId = -1;
		bool isExist = 0;
		//����ļ��Ƿ����
		for (int i = 0; i < 10; i++) {
			if (mfd[nowuser].f[i].filename == name) {
				isExist = 1; fileId = i; break;
			}
		}
		if (isExist) {
			cout << "�������µ����ƣ�";
			string newname;
			cin >> newname;
			mfd[nowuser].f[fileId].filename = newname;
			cout << "�ļ��������ɹ���" << endl;
			break;
		}
		else {
			cout << "�ļ�ͬ����������������" << endl; break;
		}
	}
	system("pause");
}

void changeFile() {
	int fileId = -1;			//д�ļ����±�
	cout << "��������Ҫ����Ȩ�޵��ļ�����:";
	string name;
	cin >> name;
	bool isExist = 0;
	//����ļ��Ƿ����
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
		if (isopen) cout << "�ļ������У����ȹر��ļ���" << endl;
				else {
			cout << "�������µ�Ȩ��:";
			string code;
			cin >> code;
			if (code.length() != 3)cout << "����������������룡" << endl;
			else {
				mfd[nowuser].f[fileId].p_code = code;
				cout << "����Ȩ�޳ɹ���" << endl;
			}
		}
	}
	else {
		cout << "���ļ������ڣ�" << endl;
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
		cout << "**����������Ҫִ�е�����(����1-7):";
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
			cout << "����������������룡" << endl;
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

	

	
