#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

#include <chrono>
#include <queue>
#include <random>

using namespace std;

class ThreadSafeQueue{

private:
    queue<int>data_queue;
    mutex mtx;
    condition_variable cv;

public:

    void push(int value){
        unique_lock<mutex>lock(mtx);

        data_queue.push(move(value));
        cv.notify_one();
    }

    void wait_and_pop(int &value){
        unique_lock<mutex>lock(mtx);
        cv.wait(lock , [this]{ return !data_queue.empty(); });
        value = move(data_queue.front());
        data_queue.pop();
    }

    bool isEmpty(){
        unique_lock<mutex>lock(mtx);
        return data_queue.empty();
    }

};

int generateRandomNumber(){
    random_device rd; 
    mt19937 gen(rd()); 
    uniform_int_distribution<> distr(2, 25); 
    return distr(gen);
}

int main(){

    ThreadSafeQueue tsq;

    thread producer([&tsq](){

        while(true)
        {   
            int random = generateRandomNumber();
            tsq.push(random);
            this_thread::sleep_for(chrono::milliseconds(100));
        }
    });

    thread consumer([&tsq](){
        int value;
        while(true)
        {
            tsq.wait_and_pop(value);
            cout<<"Consumer value : "<<value<<endl;
        }
    });

    producer.join();
    consumer.join();

    return 0;
}