#include <iostream>
#include <thread>
#include <mutex>

using namespace std;

int a = 0;

mutex mtx;

void function1(){
    mtx.lock();
    for(int i = 0 ; i < 1000000 ; i++){
        a++;
    }
    mtx.unlock();
}

void function2(){
    mtx.lock();
    for(int i = 0 ; i < 1000000 ; i++){
        a++;
    }
    mtx.unlock();
}

int main(){

    thread t1(function1);
    thread t2(function2);

    t1.join();
    t2.join();

    cout<<a<<endl;

    return 0;
}
