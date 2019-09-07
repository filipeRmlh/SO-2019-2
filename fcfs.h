//
// Created by filipe on 05/09/2019.
//

#ifndef SO_2019_2_FCFS_H
#define SO_2019_2_FCFS_H

#include <vector>
#include "Task.h"
#include <list>
#include <iostream>
#include "Flow.h"

void fcfs_callback(Flow *flow){
    if(!flow->startedFlow && !flow->queue.empty()){
        flow->initializeFlow();
        flow->executing = flow->getNext();
        flow->executing.startTask(flow->time);
    }else{
        if(flow->executing.status == STARTED && flow->executing.total_passed_time == flow->executing.duration){
            flow->finalizeTaskAndStartNext();
        }
        if(flow->ended == flow->tasks.size() && flow->queue.empty()){
            flow->finalizeFlow();
        }
    }

    if(flow->executing.status == STARTED){
        flow->executing.runTask(flow->time);
    }
}

Flow FCFS(std::vector<Task>& tasks){
    Flow fcfs = Flow(tasks);
    fcfs.callback = fcfs_callback;
    fcfs.start();
    return fcfs;
}


#endif