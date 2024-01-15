#include<bits/stdc++.h>

using namespace std;

// 定义进程控制块（PCB）
struct PCB 
{
    string name;                // 进程名
    int priority;               // 优先数（优先数法使用）
    int timeQuantum;            // 轮转时间片（轮转法使用）
    int burstTime;              // 运行时间
    int elapsedTime;            // 已用CPU时间
    string state;               // 进程状态

    PCB(string n, int p, int tq, int bt)
        : name(n), priority(p), timeQuantum(tq), burstTime(bt), elapsedTime(0), state("就绪") {}
};

// 显示进程信息
void displayProcessInfo(const vector<PCB>& processes) 
{
    cout << "进程状态:\n";
    for (const auto& p : processes) {
        cout << "进程名: "      << p.name
             << ", 剩余时间: "  << p.burstTime
             << ", 已用时间: "  << p.elapsedTime
             << ", 状态: "      << p.state 
             << endl;
    }
}

// 优先数调度
void priorityScheduling(vector<PCB>& processes) 
{
    while (!processes.empty()) 
    {
        // 按优先级从高到低排序
        sort(processes.begin(), processes.end(),[](const PCB& a, const PCB& b) { return a.priority > b.priority; });

        // 获取优先级最高的进程
        PCB& currentProcess = processes[0];
        currentProcess.state = "运行";
        currentProcess.elapsedTime++;
        currentProcess.burstTime--;
        currentProcess.priority -= 3;

        cout << "运行进程: " << currentProcess.name << endl;
        displayProcessInfo(processes);

        // 检查进程是否完成
        if (currentProcess.burstTime == 0) 
        {
            cout << "进程完成: " << currentProcess.name << endl;
            processes.erase(processes.begin());
        } 
        else 
        {
            currentProcess.state = "就绪";
        }
    }
}

// 轮转调度
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
        currentProcess->state = "运行";

        // 执行一个时间片
        int timeSlice = min(currentProcess->timeQuantum, currentProcess->burstTime);
        currentProcess->elapsedTime += timeSlice;
        currentProcess->burstTime -= timeSlice;

        cout << "运行进程: " << currentProcess->name << endl;
        displayProcessInfo(processes);

        // 检查进程是否完成
        if (currentProcess->burstTime > 0) 
        {
            currentProcess->state = "就绪";
            readyQueue.push(currentProcess); // 放回队列末尾
        } 
        else 
        {
            cout << "进程完成: " << currentProcess->name << endl;
        }
    }
}

int main() 
{
    vector<PCB> processes = {
        PCB("进程1", 10, 3, 5),
        PCB("进程2", 15, 3, 3),
        PCB("进程3", 5, 3, 2),
    };

    int choice;
    cout << "选择调度算法：\n1. 优先数法\n2. 轮转法\n输入选择(1或2):";
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
            cout << "无效选择。" << endl;
    }

    system("pause");

    return 0;
}