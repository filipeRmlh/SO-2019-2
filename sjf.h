//
// Created by filipe on 05/09/2019.
//

#ifndef SO_2019_2_SJF_H
#define SO_2019_2_SJF_H

#include <vector>
#include "Task.h"
#include <list>
#include <iostream>
#include "Flow.h"

void sjf_callback(Flow *flow){
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

bool compare (const Task& first, const Task& second){
    return first.duration < second.duration;
}

void sjf_sortqueue_callback(Flow * flow){
    for (auto &task : flow->tasks) {
        if (task.time_in == flow->time) {
            flow->queue.push_back(task);
        }
    }
    flow->queue.sort(compare);
}

Flow SJF(std::vector<Task>& tasks){
    Flow sjf = Flow(tasks);
    sjf.callback = sjf_callback;
    sjf.sortqueue_callback=sjf_sortqueue_callback;
    sjf.start();
    return sjf;
}

#endif //SO_2019_2_RR_H