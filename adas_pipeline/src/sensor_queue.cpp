#include "sensor_queue.hpp"

bool sensor_queue::push(const adas::SensorFrame frame){
    
    std::lock_guard<std::mutex>lock(mtx);
    bool result;

    if(this->size == capacity){
        std::cout<<"[Error ] : Queue full most stale packet dropped from queue\n";
        this->front = (this->front + 1) & (capacity - 1);
        this->size--;
        result = false;
    }
    else {
        if(this->size > 0){
            this->rear = (this->rear + 1) & (capacity - 1);
        }
        this->buffer[this->rear] = frame;
        this->size++;
        result = true;
    }
    cv.notify_one();
    return result;
}

adas::SensorFrame sensor_queue::pop(std::chrono::milliseconds timeout){
    
    std::unique_lock<std::mutex>lock(mtx);
    cv.wait_for(lock , timeout , [this]{return size>0;});

    adas::SensorFrame frame;

    frame = this->buffer[this->front];
    if(this->size == 1){
        this->front = this->rear = EMPTY_BUFFER_INDEX;
        this->size = EMPTY_BUFFER_SIZE;
    }
    else{
        this->front = (this->front + 1) & (capacity - 1);
        this->size--;
    }
    return frame;
}

void sensor_queue::display_queue(void){

    size_t temp_head = this->front;
    size_t temp_tail = this->rear;

    std::cout<<">>> ";
    while(temp_head != temp_tail){
        std::cout<<"{"<<this->buffer[temp_head]<<" , "<<temp_head<<"} , ";
        temp_head = (temp_head + 1)%capacity;
    }
    std::cout<<"{"<<this->buffer[temp_head]<<" , "<<temp_head<<"} <<< \n";

}

