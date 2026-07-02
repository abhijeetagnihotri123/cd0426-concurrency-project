#include <iostream>
#include <thread>
#include <future>
#include <mutex>
#include <vector>

using namespace std;

class MSG_QUEUE{

public:
    void send(int x){
        // lock_gaurd<mutex>lock(mtx);
        mtx.lock();
        cout<<"Here in queue : "<<x<<endl;
        mtx.unlock();
    }
private:
    mutex mtx;
};

class Calling_Class{

public:
    Calling_Class(){
        msg_queue = make_shared<MSG_QUEUE>();
    }
    ~Calling_Class(){
        for(thread &t : threads){
            t.join();
        }
    }
    void run_simulation_function(){
        threads.emplace_back(thread(&Calling_Class::simulation , this));
    }

    void simulation(){
        msg_queue->send(132);
    }

private:
    shared_ptr<MSG_QUEUE>msg_queue;
    vector<thread>threads;
};

int main(){

    Calling_Class cc;
    cc.run_simulation_function();

    return 0;
}