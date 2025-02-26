#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

#define QUANTUM 20 //Queue Scheduler time
#define RRQUANTUM 5 //For round robin

using namespace std;

class Process {
    public:
        int id;
        int burst_time;
        int arrival_time;
        int priority;
        //int remaining_time;
        int waiting_time;
        int turnaround_time;
};

// (RR) scheduling
void roundRobin(queue<Process>& q, int& current_time, vector<Process>& completed_processes) {
    
    int queue_time = 20;
    while (queue_time > 0 && !q.empty()){
        
            Process p = q.front();
            q.pop();

            if (p.burst_time > queue_time){
                current_time += queue_time;
                p.burst_time -= queue_time;
                q.push(p);
                queue_time = queue_time - queue_time;
            } else {
                current_time += p.burst_time;
                p.turnaround_time = current_time - p.arrival_time;
                p.waiting_time = p.turnaround_time - p.burst_time;
                completed_processes.push_back(p);
                queue_time = queue_time - p.burst_time;
            }
    }

}

// (SJF) scheduling
void shortestJobFirst(vector<Process>& processes, int& current_time, vector<Process>& completed_processes) {

    int queue_time = 20;
    while (queue_time > 0 && !processes.empty()){
        
            //sort in ascending order
            sort(processes.begin(), processes.end(), [](Process a, Process b) {
                return a.burst_time < b.burst_time;
            });

            Process p = *processes.begin();
            processes.erase(processes.begin());

            if (p.burst_time > queue_time){
                current_time += queue_time;
                p.burst_time -= queue_time;
                processes.insert(processes.begin(), p);
                queue_time = queue_time - queue_time;
            } else {
                current_time += p.burst_time;
                p.turnaround_time = current_time - p.arrival_time;
                p.waiting_time = p.turnaround_time - p.burst_time;
                completed_processes.push_back(p);
                queue_time = queue_time - p.burst_time;
            }
        
    }


}

// (FIFO) scheduling
void firstInFirstOut(vector<Process>& processes, int& current_time, vector<Process>& completed_processes) {

    int queue_time = 20;
    while (queue_time > 0 && !processes.empty()){

            Process p = *processes.begin();
            processes.erase(processes.begin());

            if (p.burst_time > queue_time){
                current_time += queue_time;
                p.burst_time -= queue_time;
                processes.insert(processes.begin(), p);
                queue_time = queue_time - queue_time;
            } else {
                current_time += p.burst_time;
                p.turnaround_time = current_time - p.arrival_time;
                p.waiting_time = p.turnaround_time - p.burst_time;
                completed_processes.push_back(p);
                queue_time = queue_time - p.burst_time;
            }
    }

}

int main(void) {
    int n;
    cout << "Enter the number of processes: ";
    cin >> n;

    vector<Process> processes(n);
    for (int i = 0; i < n; i++) {
        cout << "Enter details for process " << i + 1 << ":\n";
        cout << "Burst time: ";
        cin >> processes[i].burst_time;
        cout << "Arrival time: ";
        cin >> processes[i].arrival_time;
        cout << "Priority (0-3): ";
        cin >> processes[i].priority;
        processes[i].id = i + 1;
    }

    // Separate processes into queues based on priority
    queue<Process> q0;
    vector<Process> q1, q2, q3;

    for (const auto &p : processes) {
        if (p.priority == 0) q0.push(p);
        else if (p.priority == 1) q1.push_back(p);
        else if (p.priority == 2) q2.push_back(p);
        else if (p.priority == 3) q3.push_back(p);
    }

    int current_time = 0;
    vector<Process> completed_processes;

    // multilevel queue scheduling
    while (!q0.empty() || !q1.empty() || !q2.empty() || !q3.empty()) {

        if (!q0.empty()) {
            roundRobin(q0, current_time, completed_processes);
        }
        if (!q1.empty()) {
            shortestJobFirst(q1, current_time, completed_processes);
        }
        if (!q2.empty()) {
            shortestJobFirst(q2, current_time, completed_processes);
        }
        if (!q3.empty()) {
            firstInFirstOut(q3, current_time, completed_processes);
        }
    }

    // Output
    cout << "\nProcess ID\tWaiting Time\tTurnaround Time\n";
    for (const auto& p : completed_processes) {
        cout << p.id << "\t\t" << p.waiting_time << "\t\t" << p.turnaround_time << "\n";
    }

    return 0;
}