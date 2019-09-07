//
// Created by filipe on 06/09/2019.
//

#ifndef SO_2019_2_SRTF_H
#define SO_2019_2_SRTF_H


#include <vector>
#include "Task.h"
#include <list>
#include <iostream>
#include "Flow.h"

void srtf_callback(Flow *flow){
    if(!flow->startedFlow && !flow->queue.empty()){
        flow->initializeFlow();
        flow->executing = flow->getNext();
        flow->executing.startTask(flow->time);
    }else{
        if(flow->executing.status == STARTED && flow->executing.total_passed_time == flow->executing.duration){
            flow->finalizeTaskAndStartNext();
        }

        if(!flow->queue.empty() && flow->executing.status == STARTED && flow->queue.front().duration < (flow->executing.duration-flow->executing.total_passed_time)){
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


bool srtf_compare (const Task& first, const Task& second){
    return first.duration < second.duration;
}

void srtf_sortqueue_callback(Flow * flow){
    for (auto &task : flow->tasks) {
        if (task.time_in == flow->time) {
            flow->queue.push_back(task);
        }
    }
    flow->queue.sort(srtf_compare);
}

Flow SRTF(std::vector<Task>& tasks){
    Flow srtf = Flow(tasks);
    srtf.callback = srtf_callback;
    srtf.sortqueue_callback = srtf_sortqueue_callback;
    srtf.start();
    return srtf;
}


#endif //SO_2019_2_SRTF_H
