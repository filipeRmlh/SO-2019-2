//
// Created by filipe on 06/09/2019.
//

#ifndef SO_2019_2_PRIO_P_H
#define SO_2019_2_PRIO_P_H


#include <vector>
#include "Task.h"
#include <list>
#include <iostream>
#include "Flow.h"

void priop_callback(Flow *flow){
    if(!flow->startedFlow && !flow->queue.empty()){
        flow->initializeFlow();
        flow->executing = flow->getNext();
        flow->executing.startTask(flow->time);
    }else{
        if(flow->executing.status == STARTED && flow->executing.total_passed_time == flow->executing.duration){
            flow->finalizeTaskAndStartNext();
        }

        if(!flow->queue.empty() && flow->executing.status == STARTED && (flow->queue.front().priority > flow->executing.priority)){
            flow->changeContext();
        }


        if(flow->ended == flow->tasks.size() && flow->queue.empty()){
            flow->finalizeFlow();
        }
    }

    if(flow->executing.status == STARTED){
        flow->executing.runTask(flow->time);
    }
}


bool priop_compare (const Task& first, const Task& second){
    return first.priority > second.priority;
}

void priop_sortqueue_callback(Flow * flow){
    for (auto &task : flow->tasks) {
        if (task.time_in == flow->time) {
            flow->queue.push_back(task);
        }
    }
    flow->queue.sort(priop_compare);
}

Flow PRIOp(std::vector<Task>& tasks){
    Flow prioc = Flow(tasks);
    prioc.callback = priop_callback;
    prioc.sortqueue_callback = priop_sortqueue_callback;
    prioc.start();
    return prioc;
}



#endif //SO_2019_2_PRIO_P_H
