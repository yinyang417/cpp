#include<bits/stdc++.h>

using namespace std;

const int RESOURCE_TYPES = 5;
const int PROCESS_NUMS = 5;
const int p = 5; // 进程数
const int r = 4; // 资源种类
int num = 1; // 需要分配资源的进程序号

// Process Control Block (PCB) structure
struct PCB
{
    int id;
    int priority;
    int cpuTime;
    int allTime;
    std::string state;
    int waitingTime;    // Added for performance metrics
    int turnaroundTime; // Added for performance metrics
    int submissionTime;
    int allocation[RESOURCE_TYPES];
    int claim[RESOURCE_TYPES];
};

// Function to initialize processes with random values
void InitializeProcesses(vector<PCB> &processes, int n)
{
    srand(time(0));
    for (int i = 0; i < n; ++i)
    {
        PCB process;
        process.id = i + 1;
        process.priority = rand() % 10; // 为简单起见，随机生成优先级
        process.cpuTime = 0;
        process.allTime = 3 + rand() % 5; // 随机生成所需的时间片
        process.state = "W";              // 初始状态为等待
        process.waitingTime = 0;
        process.turnaroundTime = 0;
        process.submissionTime = rand() % 15;
        printf("CLAIM OF PROCESS %d IS:", i + 1);
        for (int j = 0; j < RESOURCE_TYPES; j++)
            cin >> process.claim[i];
        processes.push_back(process);
    }
}

// Function to display the current state of processes
void DisplayCPUUsage(const vector<PCB> &processes)
{
    cout << "ID\tPriority\tCPU Time\tAll Time\tState\tWaiting Time\tTurnaround Time\n";
    for (const auto &process : processes)
    {
        cout << process.id << "\t" << process.priority << "\t\t"
             << process.cpuTime << "\t\t" << process.allTime << "\t\t"
             << process.state << "\t\t" << process.waitingTime << "\t\t"
             << process.turnaroundTime << endl;
    }
    cout << endl;
}

// Function to display the current state of processes
void DisplayResourceUsage(const vector<PCB> &processes)
{
    cout << "ID\tPriority\tCPU Time\tAll Time\tState\tWaiting Time\tTurnaround Time\n";
    for (const auto &process : processes)
    {
        cout << process.id << "\t" << process.priority << "\t\t"
             << process.cpuTime << "\t\t" << process.allTime << "\t\t"
             << process.state << "\t\t" << process.waitingTime << "\t\t"
             << process.turnaroundTime << endl;
    }
    cout << endl;
}

// Priority Scheduling Algorithm
void PriorityScheduling(vector<PCB> &processes, bool display)
{
    sort(processes.begin(), processes.end(), [](const PCB &a, const PCB &b)
         {
             return a.priority > b.priority; // 按优先级排序（高优先级优先）
         });

    int currentTime = 0;
    int waitingProcesses = processes.size();

    for (auto &currentprocess : processes)
    {
        while (true)
        {
            currentprocess.cpuTime++;
            currentTime++;

            for (auto &process : processes)
            {
                if (process.state == "F")
                    continue;
                process.waitingTime++;
            }
            currentprocess.waitingTime--;

            if (currentprocess.cpuTime >= currentprocess.allTime)
            {
                currentprocess.turnaroundTime = currentTime;
                currentprocess.state = "F";
                waitingProcesses--;
            }
            if (display)
            {
                cout << "Running Process " << currentprocess.id << endl;
                DisplayCPUUsage(processes);
            }
            if (currentprocess.cpuTime >= currentprocess.allTime)
                break;
        }
    }
}

// Round Robin Scheduling Algorithm
void RoundRobinScheduling(vector<PCB> &processes, bool display, int timeSlice)
{
    int currentTime = 0;
    int waitingProcess = processes.size();

    while (waitingProcess)
    {
        for (auto &currentprocess : processes)
        {
            if (currentprocess.state == "F")
                continue;

            currentprocess.waitingTime -= timeSlice;
            currentprocess.cpuTime += timeSlice;
            currentTime += timeSlice;

            for (auto &process : processes)
            {
                if (process.state == "F")
                    continue;
                process.waitingTime += timeSlice;
            }

            if (currentprocess.cpuTime >= currentprocess.allTime)
            {
                currentprocess.turnaroundTime = currentTime;
                currentprocess.state = "F";
                waitingProcess--;
            }

            if (display)
            {
                cout << "Running Process " << currentprocess.id << endl;
                DisplayCPUUsage(processes);
            }
        }
    }
}

// HRRN Scheduling Algorithm
void HRRNScheduling(vector<PCB> &processes, bool display)
{
    int currentTime = 0;
    int waitingProcesses = processes.size();

    while (waitingProcesses)
    {
        // 计算每个进程的响应比
        for (auto &process : processes)
        {
            double responseRatio = (currentTime - process.cpuTime + process.allTime) / static_cast<double>(process.allTime);
            process.priority = responseRatio;
            if (process.state == "F")
                continue;
            process.waitingTime++;
        }

        // 根据响应比排序进程（高响应比优先）
        sort(processes.begin(), processes.begin() + waitingProcesses, [](const PCB &a, const PCB &b)
             { return a.priority > b.priority; });

        // 运行响应比最高的进程
        auto &currentprocess = processes.front();

        currentprocess.waitingTime--;
        currentprocess.cpuTime++;
        currentTime++;

        if (currentprocess.cpuTime >= currentprocess.allTime)
        {
            currentprocess.turnaroundTime = currentTime - currentprocess.waitingTime;
            currentprocess.state = "F"; // 将进程状态设置为完成
            rotate(processes.begin(), processes.begin() + 1, processes.end());
            waitingProcesses--;
        }

        if (display)
        {
            cout << "Running Process " << currentprocess.id << endl;
            DisplayCPUUsage(processes);
        }
    }
}

void init_request(int request[r])
{
    // 初始化request矩阵
    cout << "Input the number of request:" << endl;
    cin >> num;
    num -= 1; // 下标减1
    cout << "Input the request vector:" << endl;
    for (int i = 0; i < r; i++)
        cin >> request[i];
}

void init_matrix(int maximum[p][r], int allocation[p][r], int need[p][r], int available[r], int request[r])
{
    // 初始化函数
    cout << "Input the Allocation matrix:" << endl;
    for (int i = 0; i < p; i++)
        for (int j = 0; j < r; j++)
            cin >> allocation[i][j];
    cout << "Input the Need matrix:" << endl;
    for (int i = 0; i < p; i++)
        for (int j = 0; j < r; j++)
            cin >> need[i][j];
    // cout<<"Input the Max matrix:"<<endl;
    // Max矩阵可以由Need和Allocation矩阵推导得出
    // Max[i,j]= Need[i,j]+Allocation[i,j]
    for (int i = 0; i < p; i++)
        for (int j = 0; j < r; j++)
            maximum[i][j] = need[i][j] + allocation[i][j];
    cout << "Input the available vector:" << endl;
    for (int i = 0; i < r; i++)
        cin >> available[i];
}

void output_func(int allocation[p][r], int need[p][r], int available[r])
{
    // 输出函数
    cout << endl
         << "     "
         << "Allocation"
         << "     Need"
         << "        Available" << endl;
    for (int i = 0; i < p; i++)
    {
        cout << "P" << i + 1 << "   :";
        for (int j = 0; j < r; j++)
        {
            cout << allocation[i][j] << ' ';
        }
        cout << "     ";
        for (int j = 0; j < r; j++)
            cout << need[i][j] << ' ';
        if (i == 0)
        {
            cout << "     ";
            for (int k = 0; k < r; k++)
                cout << available[k] << ' ';
        }
        cout << endl;
    }
    cout << endl;
}

bool compare(int need[], int work[])
{
    bool flg = 1;
    for (int i = 0; i < r; i++)
    {
        // 检查是否有大于的情况存在
        if (need[i] > work[i])
        {
            flg = 0;
            break;
        }
    }
    return flg;
}

int check_security(int allocation[p][r], int need[p][r], int available[r])
{
    // 安全性检查函数
    int finish[p] = {0}; // 初始化finish向量
    int work[r];         // 拷贝available
    int lis[p];          // 用来记录安全时的队列
    int cnt = 0;
    for (int i = 0; i < r; i++)
        work[i] = available[i]; // 初始化work向量
    // 序列分配
    // 循环p次
    for (int m = 0; m < p; m++)
    {
        for (int i = 0; i < p; i++)
        {
            // 如果当前进程执行完成，跳过
            if (finish[i] == 1)
                continue;
            // 找到finish[i] = false
            else
            {
                // 如果Need[i,j]<=Work[j]
                if (compare(need[i], work))
                {
                    for (int j = 0; j < r; j++)
                        work[j] += allocation[i][j];
                    finish[i] = 1;
                    lis[cnt++] = i + 1; // 将该状态放入安全状态队列中
                    break;
                }
            }
        }
    }
    int flag = 1;
    for (int i = 0; i < r; i++)
    {
        if (finish[i] == 0)
        {
            flag = 0;
            break; // 如果存在F的进程，表明系统处于不安全状态
        }
        else
            continue;
    }
    if (flag)
    {
        cout << "系统处于安全状态！" << endl;
        cout << "安全序列为:";
        for (int i = 0; i < p; i++)
            cout << lis[i] << ' ';
        cout << endl;
    }
    else
        cout << "系统处于不安全状态！" << endl;
    return flag;
}

void banker(int allocation[p][r], int need[p][r], int available[r], int request[r], int n)
{
    if (!compare(request, need[n]))
    {
        // 如果存在Requesti[j]>Need[i][j],认为出错
        cout << "出错！所需资源已超过所宣布的最大值！" << endl;
        return;
    }
    else
    {
        // 银行家算法(1)没有出错
        if (!compare(request, available))
        {
            // 如果存在Requesti[j]>Available[j]，认为出错
            cout << "尚无足够资源，必须等待！" << endl;
            return;
        }
        else
        {
            for (int j = 0; j < r; j++)
            {
                available[j] -= request[j];
                allocation[n][j] += request[j];
                need[n][j] -= request[j];
            }
            if (check_security(allocation, need, available))
            {
                cout << "安全！将资源正式分配" << endl;
            }
            else
            {
                cout << "不安全！资源分配作废！恢复以前状态" << endl;
                for (int j = 0; j < r; j++)
                {
                    need[n][j] += request[j];
                    allocation[n][j] -= request[j];
                    available[j] += request[j];
                }
            }
        }
    }
    output_func(allocation, need, available);
}

int main()
{
    int maximum[p][r], allocation[p][r], need[p][r];
    int available[r], request[r];
    init_matrix(maximum, allocation, need, available, request);
    cout << endl
         << "检查T0时刻系统是否处于安全状态..." << endl;
    check_security(allocation, need, available);
    int flag = 1;
    while (flag)
    {
        cout << endl
             << "对请求资源进行银行家算法检查..." << endl;
        init_request(request); // 初始化request矩阵
        banker(allocation, need, available, request, num);
        cout << "是否继续输入？(输入0退出):";
        cin >> flag;
    }

    return 0;
}
/*测试数据
Allocation:
3 1 1 2
0 1 0 2
1 0 3 3
3 2 0 1
2 1 1 1
Need:
0 0 2 0
2 1 1 2
1 0 0 1
2 0 1 1
1 0 1 0
Available:
1 0 2 1
*/