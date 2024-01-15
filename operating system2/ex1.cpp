#include<bits/stdc++.h>

using namespace std;

// ������̿��ƿ飨PCB��
struct PCB 
{
    string name;                // ������
    int priority;               // ����������������ʹ�ã�
    int timeQuantum;            // ��תʱ��Ƭ����ת��ʹ�ã�
    int burstTime;              // ����ʱ��
    int elapsedTime;            // ����CPUʱ��
    string state;               // ����״̬

    PCB(string n, int p, int tq, int bt)
        : name(n), priority(p), timeQuantum(tq), burstTime(bt), elapsedTime(0), state("����") {}
};

// ��ʾ������Ϣ
void displayProcessInfo(const vector<PCB>& processes) 
{
    cout << "����״̬:\n";
    for (const auto& p : processes) {
        cout << "������: "      << p.name
             << ", ʣ��ʱ��: "  << p.burstTime
             << ", ����ʱ��: "  << p.elapsedTime
             << ", ״̬: "      << p.state 
             << endl;
    }
}

// ����������
void priorityScheduling(vector<PCB>& processes) 
{
    while (!processes.empty()) 
    {
        // �����ȼ��Ӹߵ�������
        sort(processes.begin(), processes.end(),[](const PCB& a, const PCB& b) { return a.priority > b.priority; });

        // ��ȡ���ȼ���ߵĽ���
        PCB& currentProcess = processes[0];
        currentProcess.state = "����";
        currentProcess.elapsedTime++;
        currentProcess.burstTime--;
        currentProcess.priority -= 3;

        cout << "���н���: " << currentProcess.name << endl;
        displayProcessInfo(processes);

        // �������Ƿ����
        if (currentProcess.burstTime == 0) 
        {
            cout << "�������: " << currentProcess.name << endl;
            processes.erase(processes.begin());
        } 
        else 
        {
            currentProcess.state = "����";
        }
    }
}

// ��ת����
void roundRobinScheduling(vector<PCB>& processes) 
{
    queue<PCB*> readyQueue;
    for (auto& process : processes) 
    {
        readyQueue.push(&process);
    }

    while (!readyQueue.empty()) 
    {
        PCB* currentProcess = readyQueue.front();
        readyQueue.pop();
        currentProcess->state = "����";

        // ִ��һ��ʱ��Ƭ
        int timeSlice = min(currentProcess->timeQuantum, currentProcess->burstTime);
        currentProcess->elapsedTime += timeSlice;
        currentProcess->burstTime -= timeSlice;

        cout << "���н���: " << currentProcess->name << endl;
        displayProcessInfo(processes);

        // �������Ƿ����
        if (currentProcess->burstTime > 0) 
        {
            currentProcess->state = "����";
            readyQueue.push(currentProcess); // �Żض���ĩβ
        } 
        else 
        {
            cout << "�������: " << currentProcess->name << endl;
        }
    }
}

int main() 
{
    vector<PCB> processes = {
        PCB("����1", 10, 3, 5),
        PCB("����2", 15, 3, 3),
        PCB("����3", 5, 3, 2),
    };

    int choice;
    cout << "ѡ������㷨��\n1. ��������\n2. ��ת��\n����ѡ��(1��2):";
    cin >> choice;

    switch (choice) 
    {
        case 1:
            priorityScheduling(processes);
            break;
        case 2:
            roundRobinScheduling(processes);
            break;
        default:
            cout << "��Чѡ��" << endl;
    }

    system("pause");

    return 0;
}