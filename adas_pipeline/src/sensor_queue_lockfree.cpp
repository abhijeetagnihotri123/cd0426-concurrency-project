#include "sensor_queue_lockfree.hpp"

bool sensor_queue_lockfree::push(adas::SensorFrame *frame){
    
    bool result = true;
    size_t front = front_.load(std::memory_order_acquire);
    size_t rear = rear_.load(std::memory_order_acquire);
    size_t num_elements = num_elements_.load(std::memory_order_acquire);

    if(num_elements == capacity){
        std::cout<<"[Error ] : Queue full most stale packet dropped from queue\n";
        result = false;
        num_elements--;
        front = (front + 1) & (capacity - 1);
    }
    this->buffer[rear] = frame;
    num_elements++;
    rear = (rear + 1) & (capacity - 1);

    front_.store(front , std::memory_order_release);
    rear_.store(rear , std::memory_order_release);
    num_elements_.store(num_elements , std::memory_order_release);

    return result;
}

adas::SensorFrame* sensor_queue_lockfree::pop(){

    adas::SensorFrame *frame;
    size_t front = front_.load(std::memory_order_acquire);
    size_t rear = rear_.load(std::memory_order_acquire);
    size_t num_elements = num_elements_.load(std::memory_order_acquire);

    if(num_elements == 0){
        frame = nullptr;
    }
    else{
        frame = this->buffer[front];
        if(num_elements == 0){
            front = rear = EMPTY_BUFFER_INDEX_LF;
        }
        else{
            front = (front + 1) & (capacity - 1);
        }
        num_elements--;
    }

    front_.store(front , std::memory_order_release);
    rear_.store(rear , std::memory_order_release);
    num_elements_.store(num_elements , std::memory_order_release);

    return frame;
}

void sensor_queue_lockfree::display_queue(void){

    
    size_t temp_head = front_.load(std::memory_order_acquire);
    size_t temp_tail = rear_.load(std::memory_order_acquire);

    std::cout<<">>> ";
    while(temp_head != temp_tail){
        std::cout<<"{"<<this->buffer[temp_head]<<" , "<<temp_head<<"} , ";
        temp_head = (temp_head + 1)%capacity;
    }
    std::cout<<"{"<<this->buffer[temp_head]<<" , "<<temp_head<<"} <<< \n";

}

