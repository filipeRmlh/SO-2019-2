//
// Created by filipe on 07/09/2019.
//

#ifndef SO_2019_2_PRIO_D_H
#define SO_2019_2_PRIO_D_H


#include <vector>
#include "Task.h"
#include <list>
#include <iostream>
#include "Flow.h"

void priod_callback(Flow *flow){
    if(!flow->startedFlow && !flow->queue.empty()){
        flow->initializeFlow();
        flow->executing = flow->getNext();
        flow->executing.startTask(flow->time);
        flow->executing.dynamic_priority=flow->executing.priority;
    }else{
        flow->executing.dynamic_priority=flow->executing.priority;
        if(flow->executing.status == STARTED && flow->executing.total_passed_time == flow->executing.duration){
            flow->executing.endTask(flow->time);
            flow->ended++;
            if(!flow->queue.empty()){
                flow->executing = flow->getNext();
                flow->executing.startTask(flow->time);
            }
        }

        if(!flow->queue.empty() && flow->executing.status == STARTED && (flow->queue.front().dynamic_priority > flow->executing.dynamic_priority)){
            flow->executing.pauseTask(flow->time);
            flow->queue.push_back(flow->executing);
            flow->executing = flow->getNext();
            flow->executing.startTask(flow->time);
        }


        if(flow->ended == flow->tasks.size() && flow->queue.empty()){
            flow->finalizeFlow();
        }
    }

    if(flow->executing.status == STARTED){
        flow->executing.runTask(flow->time);
    }
}


bool priod_compare (const Task& first, const Task& second){
    return first.dynamic_priority > second.dynamic_priority;
}

void priod_sortqueue_callback(Flow * flow){
    for (auto &task : flow->tasks) {
        if (task.time_in == flow->time) {
            task.dynamic_priority += flow->alpha;
            flow->queue.push_back(task);
        }
    }
    flow->queue.sort(priod_compare);
}

Flow PRIOd(std::vector<Task>& tasks, int alpha){
    Flow priod = Flow(tasks);
    priod.alpha=alpha;
    priod.callback = priod_callback;
    priod.sortqueue_callback = priod_sortqueue_callback;
    priod.start();
    return priod;
}



#endif //SO_2019_2_PRIO_D_H
