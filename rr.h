//
// Created by filipe on 05/09/2019.
//

#ifndef SO_2019_2_RR_H
#define SO_2019_2_RR_H

#include <vector>
#include "Task.h"
#include <list>
#include <iostream>
#include "Flow.h"

void rr_callback(Flow *flow){
    if(!flow->startedFlow && !flow->queue.empty()){
        flow->initializeFlow();
        flow->executing = flow->getNext();
        flow->executing.startTask(flow->time);
    }else{
        if(flow->executing.status == STARTED && flow->executing.total_passed_time == flow->executing.duration){
            flow->finalizeTaskAndStartNext();
        }

        if(!flow->queue.empty() && flow->executing.status == STARTED && flow->executing.passed_time==flow->quantum){
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

Flow RR(std::vector<Task>& tasks,int quantum){
    Flow rr = Flow(tasks,quantum);
    rr.callback = rr_callback;
    rr.start();
    return rr;
}

#endif //SO_2019_2_RR_H