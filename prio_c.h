//
// Created by filipe on 06/09/2019.
//

#ifndef SO_2019_2_PRIO_C_H
#define SO_2019_2_PRIO_C_H


#include <vector>
#include "Task.h"
#include <list>
#include <iostream>
#include "Flow.h"

void prioc_callback(Flow *flow){
    if(!flow->startedFlow && !flow->queue.empty()){
        flow->initializeFlow();
        flow->executing = flow->getNext();
        flow->executing.startTask(flow->time);
    }else{
        if(flow->executing.status == STARTED && flow->executing.total_passed_time == flow->executing.duration){
            flow->executing.endTask(flow->time);
            flow->ended++;
            if(!flow->queue.empty()){
                flow->executing = flow->getNext();
                flow->executing.startTask(flow->time);
            }
        }

        if(flow->ended == flow->tasks.size() && flow->queue.empty()){
            flow->finalizeFlow();
        }
    }

    if(flow->executing.status == STARTED){
        flow->executing.runTask(flow->time);
    }
}


bool prioc_compare (const Task& first, const Task& second){
    return first.priority > second.priority;
}

void prioc_sortqueue_callback(Flow * flow){
    for (auto &task : flow->tasks) {
        if (task.time_in == flow->time) {
            flow->queue.push_back(task);
        }
    }
    flow->queue.sort(prioc_compare);
}

Flow PRIOc(std::vector<Task>& tasks){
    Flow prioc = Flow(tasks);
    prioc.callback = prioc_callback;
    prioc.sortqueue_callback = prioc_sortqueue_callback;
    prioc.start();
    return prioc;
}


#endif //SO_2019_2_PRIO_C_H
