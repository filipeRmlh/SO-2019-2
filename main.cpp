#include <iostream>
#include <vector>
#include "fcfs.h"
#include "rr.h"
#include "sjf.h"
#include "srtf.h"
#include "prio_c.h"
#include "prio_p.h"
#include "prio_d.h"

using namespace std;

vector<Task> readInput(int * N);

int main() {
    int N;
    vector<Task> tasks = readInput(&N);
    cout << "______________________FCFS______________________" << endl;
    FCFS(tasks);
    cout << endl;
    cout << "______________________RR______________________" << endl;
    RR(tasks,2);
    cout << endl;

    cout << "______________________SJF______________________" << endl;
    SJF(tasks);
    cout << endl;

    cout << "______________________SRTF______________________" << endl;
    SRTF(tasks);
    cout << endl;

    cout << "______________________PRIOc______________________" << endl;
    PRIOc(tasks);
    cout << endl;

    cout << "______________________PRIOp______________________" << endl;
    PRIOp(tasks);
    cout << endl;

    cout << "______________________PRIOd______________________" << endl;
    PRIOd(tasks,1);
    cout << endl;


    return 0;
}

vector<Task> readInput(int *N){
    vector<Task> tasks;
    cin >> *N;
    int s;
    for(int i=0;i<(*N);i++){
        cin >> s;
        auto task = Task();
        task.id = (i+1);
        task.time_in = s;
        tasks.push_back(task);
    }
    for(int i=0; i < (*N);i++){
        cin >> s;
        tasks[i].duration = s;
    }
    for(int i=0; i < (*N);i++){
        cin >> s;
        tasks[i].priority = s;
        tasks[i].dynamic_priority = s;
    }
    return tasks;
}


