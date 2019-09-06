//
// Created by filipe on 05/09/2019.
//

#ifndef SO_2019_2_TASK_H
#define SO_2019_2_TASK_H

enum {CREATED=0,STARTED = 100, ENDED, PAUSED};

class Task{
public:
    int status=CREATED,
        id=-1,
        time_in=-1,
        duration=-1,
        priority=-1,
        time_start=-1,
        passed_time = 0,
        total_passed_time=0;
    void startTask(int time);
    void endTask(int time);
    void runTask(int time);
    void pauseTask(int time);
};

void Task::startTask(int time) {
    std::cout << "----------------------------" << std::endl;
    if(this->status==PAUSED){
        std::cout << "Continuando Tarefa " << this->id << std::endl;
    }
    else {
        std::cout << "Iniciando Tarefa " << this->id << std::endl;
    }
    if(this->status == CREATED){
        this->time_start=time;
    }
    this->status=STARTED;
}

void Task::pauseTask(int time){
    std::cout << "Pausando Tarefa "<<this->id << std::endl;
    this->status=PAUSED;
    this->passed_time=0;
}

void Task::endTask(int time){
    std::cout << "Finalizando Tarefa "<<this->id << std::endl;
    this->status = ENDED;
}

void Task::runTask(int time){
    std::cout << "Executando Tarefa " << this->id << " no tempo " << time << std::endl;
    this->total_passed_time++;
    this->passed_time++;
}

#endif //SO_2019_2_TASK_H
