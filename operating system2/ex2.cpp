#include<bits/stdc++.h>

using namespace std;

const int RESOURCE_TYPES = 5;
const int PROCESS_NUMS = 5;
const int p = 5; // ������
const int r = 4; // ��Դ����
int num = 1; // ��Ҫ������Դ�Ľ������

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
        process.priority = rand() % 10; // Ϊ�����������������ȼ�
        process.cpuTime = 0;
        process.allTime = 3 + rand() % 5; // ������������ʱ��Ƭ
        process.state = "W";              // ��ʼ״̬Ϊ�ȴ�
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
             return a.priority > b.priority; // �����ȼ����򣨸����ȼ����ȣ�
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
        // ����ÿ�����̵���Ӧ��
        for (auto &process : processes)
        {
            double responseRatio = (currentTime - process.cpuTime + process.allTime) / static_cast<double>(process.allTime);
            process.priority = responseRatio;
            if (process.state == "F")
                continue;
            process.waitingTime++;
        }

        // ������Ӧ��������̣�����Ӧ�����ȣ�
        sort(processes.begin(), processes.begin() + waitingProcesses, [](const PCB &a, const PCB &b)
             { return a.priority > b.priority; });

        // ������Ӧ����ߵĽ���
        auto &currentprocess = processes.front();

        currentprocess.waitingTime--;
        currentprocess.cpuTime++;
        currentTime++;

        if (currentprocess.cpuTime >= currentprocess.allTime)
        {
            currentprocess.turnaroundTime = currentTime - currentprocess.waitingTime;
            currentprocess.state = "F"; // ������״̬����Ϊ���
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
    // ��ʼ��request����
    cout << "Input the number of request:" << endl;
    cin >> num;
    num -= 1; // �±��1
    cout << "Input the request vector:" << endl;
    for (int i = 0; i < r; i++)
        cin >> request[i];
}

void init_matrix(int maximum[p][r], int allocation[p][r], int need[p][r], int available[r], int request[r])
{
    // ��ʼ������
    cout << "Input the Allocation matrix:" << endl;
    for (int i = 0; i < p; i++)
        for (int j = 0; j < r; j++)
            cin >> allocation[i][j];
    cout << "Input the Need matrix:" << endl;
    for (int i = 0; i < p; i++)
        for (int j = 0; j < r; j++)
            cin >> need[i][j];
    // cout<<"Input the Max matrix:"<<endl;
    // Max���������Need��Allocation�����Ƶ��ó�
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
    // �������
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
        // ����Ƿ��д��ڵ��������
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
    // ��ȫ�Լ�麯��
    int finish[p] = {0}; // ��ʼ��finish����
    int work[r];         // ����available
    int lis[p];          // ������¼��ȫʱ�Ķ���
    int cnt = 0;
    for (int i = 0; i < r; i++)
        work[i] = available[i]; // ��ʼ��work����
    // ���з���
    // ѭ��p��
    for (int m = 0; m < p; m++)
    {
        for (int i = 0; i < p; i++)
        {
            // �����ǰ����ִ����ɣ�����
            if (finish[i] == 1)
                continue;
            // �ҵ�finish[i] = false
            else
            {
                // ���Need[i,j]<=Work[j]
                if (compare(need[i], work))
                {
                    for (int j = 0; j < r; j++)
                        work[j] += allocation[i][j];
                    finish[i] = 1;
                    lis[cnt++] = i + 1; // ����״̬���밲ȫ״̬������
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
            break; // �������F�Ľ��̣�����ϵͳ���ڲ���ȫ״̬
        }
        else
            continue;
    }
    if (flag)
    {
        cout << "ϵͳ���ڰ�ȫ״̬��" << endl;
        cout << "��ȫ����Ϊ:";
        for (int i = 0; i < p; i++)
            cout << lis[i] << ' ';
        cout << endl;
    }
    else
        cout << "ϵͳ���ڲ���ȫ״̬��" << endl;
    return flag;
}

void banker(int allocation[p][r], int need[p][r], int available[r], int request[r], int n)
{
    if (!compare(request, need[n]))
    {
        // �������Requesti[j]>Need[i][j],��Ϊ����
        cout << "����������Դ�ѳ��������������ֵ��" << endl;
        return;
    }
    else
    {
        // ���м��㷨(1)û�г���
        if (!compare(request, available))
        {
            // �������Requesti[j]>Available[j]����Ϊ����
            cout << "�����㹻��Դ������ȴ���" << endl;
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
                cout << "��ȫ������Դ��ʽ����" << endl;
            }
            else
            {
                cout << "����ȫ����Դ�������ϣ��ָ���ǰ״̬" << endl;
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
         << "���T0ʱ��ϵͳ�Ƿ��ڰ�ȫ״̬..." << endl;
    check_security(allocation, need, available);
    int flag = 1;
    while (flag)
    {
        cout << endl
             << "��������Դ�������м��㷨���..." << endl;
        init_request(request); // ��ʼ��request����
        banker(allocation, need, available, request, num);
        cout << "�Ƿ�������룿(����0�˳�):";
        cin >> flag;
    }

    return 0;
}
/*��������
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