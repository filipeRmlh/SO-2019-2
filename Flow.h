//
// Created by filipe on 06/09/2019.
//

#ifndef SO_2019_2_FLOW_H
#define SO_2019_2_FLOW_H

#include <list>
#include <iostream>
#include "Task.h"

class Flow {
public:
    bool startedFlow=false;
    Task executing = Task();
    std::list<Task> queue;
    std::vector<Task>& tasks;
    int ended = 0;
    int time=0;
    int quantum=0;
    int alpha=0;

    explicit Flow(const std::vector<Task>& tasks):tasks(const_cast<std::vector<Task> &>(tasks)){}
    explicit Flow(const std::vector<Task>& tasks,int quantum):tasks(const_cast<std::vector<Task> &>(tasks)),quantum(quantum){}
    void start();
    Task getNext();
    void initializeFlow();
    void finalizeFlow();
    void (*callback)(Flow*){};
    void (*sortqueue_callback)(Flow*)=nullptr;

};


void Flow::start(){
    while(true) {
        if(this->sortqueue_callback== nullptr) {
            for (auto &task : this->tasks) {
                if (task.time_in == this->time) {
                    this->queue.push_back(task);
                }
            }
        }else{
            this->sortqueue_callback(this);
        }
        try{
            this->callback(this);
        }catch (int e){
            if(e==22498)
                break;
            else
                std::cout << "Um erro inesperado ocorreu" << std::endl;
        }
        this->time++;
    }
}

Task Flow::getNext(){
    Task next = this->queue.front();
    this->queue.pop_front();
    return next;
}

void Flow::initializeFlow() {
    this->startedFlow = true;
    std::cout << "Iniciando Fluxo" << std::endl;
}

void Flow::finalizeFlow(){
    std::cout << "Finalizando fluxo" << std::endl;
    throw 22498;
}

#endif //SO_2019_2_FLOW_H
