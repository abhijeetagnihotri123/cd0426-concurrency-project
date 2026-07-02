#include <iostream>
#include <random>
#include "TrafficLight.h"

/* Implementation of class "MessageQueue" */


template <typename T>
T MessageQueue<T>::receive()
{
    // TODO: FP.5a : The method receive should use std::unique_lock<std::mutex> and _condition.wait() 
    std::unique_lock<std::mutex>lock(mutex_);
    // to wait for and receive new messages and pull them from the queue using move semantics. 
    cond_.wait(lock , [this]{return !queue_.empty();});
    // The received object should then be returned by the receive function. 
    T msg = std::move(queue_.front());

    queue_.pop_front();

    return msg;
}

template <typename T>
void MessageQueue<T>::send(T &&msg)
{
    std::lock_guard<std::mutex>lock(mutex_);
    // TODO: FP.4a : The method send should use the mechanisms std::lock_guard<std::mutex> 
    // as well as _condition.notify_one() to add a new message to the queue and afterwards send a notification.
    cond_.notify_one();
    queue_.push_back(std::move(msg));
}

/* Implementation of class "TrafficLight" */

 
TrafficLight::TrafficLight()
{
    _currentPhase = TrafficLightPhase::red;
}

void TrafficLight::waitForGreen()
{
    // TODO:FP.5b : add the implementation of the method waitForGreen, in which an infinite while-loop 
    while(true)
    {
    // runs and repeatedly calls the receive function on the message queue. 
       auto msg = message_queue_->receive();
    // Once it receives TrafficLightPhase::green, the method returns.
        if(msg == green){
            return;
        }
    }
}

TrafficLightPhase TrafficLight::getCurrentPhase()
{
    return _currentPhase;
}

void TrafficLight::simulate()
{
    // TODO: FP.2b : Finally, the private method „cycleThroughPhases“ should be started in a thread when the public method „simulate“ is called. To do this, use the thread queue in the base class. 
    threads.emplace_back(std::thread(&TrafficLight::cycleThroughPhases , this));
}

// virtual function which is executed in a thread
void TrafficLight::cycleThroughPhases()
{
    // TODO: FP.2a : Implement the function with an infinite loop that measures the time between two loop cycles 
    random_device rd; 
    mt19937 gen(rd()); 
    uniform_int_distribution<> distr(4, 6); 
    int current_threshold = distr(gen);

    auto last_update = std::chrono::system_clock::now();
    
    while(true){
        this_thread::sleep_for(chrono::milliseconds(1));
        int time_elapsed = chrono::duration_cast<chrono::seconds>(chrono::system_clock::now() - last_update).count();
        if(time_elapsed >= current_threshold){
         
            if(_currentPhase == red){
                _currentPhase = green;
            }
            else{
                _currentPhase = red;
            }
        }

        msg_queue->send(_currentPhase);
        
        last_update = std::chrono::system_clock::now()
        current_threshold = distr(gen);
    }

    // and toggles the current phase of the traffic light between red and green and sends an update method 
    // to the message queue using move semantics. The cycle duration should be a random value between 4 and 6 seconds. 
    // Also, the while-loop should use std::this_thread::sleep_for to wait 1ms between two cycles. 
}

