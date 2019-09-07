#include <iostream>
#include <utility>
#include <vector>
#include "fcfs.h"
#include "rr.h"
#include "sjf.h"
#include "srtf.h"
#include "prio_c.h"
#include "prio_p.h"
#include "prio_d.h"

using namespace std;

vector<Task> readInput();
void executeFlow(const string& name, Flow (*flowCall)(vector<Task>&), const vector<Task>& tasks);
void executeFlow(const string& name, Flow (*flowCall)(vector<Task>&,int), const vector<Task>& tasks, int option);

int main() {
    vector<Task> tasks = readInput();
    executeFlow("FCFS",FCFS,tasks);
    executeFlow("RR",RR,tasks,2);
    executeFlow("SJF",SJF,tasks);
    executeFlow("SRTF",SRTF,tasks);
    executeFlow("PRIOc",PRIOc,tasks);
    executeFlow("PRIOp",PRIOp,tasks);
    executeFlow("PRIOd",PRIOd,tasks,1);
    return 0;
}

vector<Task> readInput(){
    vector<Task> tasks;
    int N;
    cin >> N;
    int s;
    for(int i=0;i<(N);i++){
        cin >> s;
        auto task = Task();
        task.id = (i+1);
        task.time_in = s;
        tasks.push_back(task);
    }
    for(int i=0; i < (N);i++){
        cin >> s;
        tasks[i].duration = s;
    }
    for(int i=0; i < (N);i++){
        cin >> s;
        tasks[i].priority = s;
        tasks[i].dynamic_priority = s;
    }
    return tasks;
}


void executeFlow(const string& name, Flow (*flowCall)(vector<Task>&), const vector<Task>& tasks){
    cout << "\033[1;34m______________________"<<name<<"______________________\033[0m" << endl;
    Flow flow = flowCall((vector<struct Task> &) tasks);

    cout << "\033[33m--------------------Métricas:-------------------\033[0m" << endl;
    cout << "Tempo Médio: " << flow.avgTime << "; Trocas de Contexto: "<<flow.context_changes<<endl;
    cout<<"\n\n"<<endl;
}


void executeFlow(const string& name, Flow (*flowCall)(vector<Task>&,int), const vector<Task>& tasks,int option){
    cout << "\033[1;34m______________________"<<name<<"______________________\033[0m" << endl;
    Flow flow = flowCall((vector<struct Task> &) tasks,option);
    cout << "\033[33m--------------------Métricas:-------------------\033[0m" << endl;
    cout << "Tempo Médio: " << flow.avgTime << "; Trocas de Contexto: "<<flow.context_changes<<endl;
    cout<<"\n\n"<<endl;
}


