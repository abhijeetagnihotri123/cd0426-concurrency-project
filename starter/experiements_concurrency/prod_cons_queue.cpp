#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

#include <chrono>
#include <queue>

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

int main(){

    ThreadSafeQueue tsq;

    thread producer([&tsq](){

        for(int i = 0 ; i < 10 ; i++){
            tsq.push(i);
            this_thread::sleep_for(chrono::milliseconds(100));
        }

    });

    thread consumer([&tsq](){
        int value;
        for(int i = 0 ; i < 10 ; i++){
            tsq.wait_and_pop(value);
            cout<<"Consumer value : "<<value<<endl;
        }
    });

    producer.join();
    consumer.join();

    return 0;
}