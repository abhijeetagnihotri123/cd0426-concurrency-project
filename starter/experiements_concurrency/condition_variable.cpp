#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

using namespace std;

bool data_ready = false;

mutex mtx;
condition_variable cv;

void producer(){
    unique_lock<mutex> lock(mtx);

    data_ready = true;

    cout<<"Data produced"<<endl;

    cv.notify_one();
}

void consumer(){

    unique_lock<mutex> lock(mtx);
    
    cv.wait(lock, [] { return data_ready; });

    data_ready = false;
    cout<<"Data consumed\n";
}

int main(){

    thread t1(producer);
    thread t2(consumer);

    t1.join();
    t2.join();

    return 0;
}
