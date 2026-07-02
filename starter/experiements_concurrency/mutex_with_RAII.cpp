#include <iostream>
#include <thread>
#include <mutex>

using namespace std;

int a = 0;

mutex mtx;

void function1(){
    lock_guard<mutex> lock(mtx);

    for(int i = 0 ; i < 1000000 ; i++){
        a++;
    }
}

void function2(){
    
    lock_guard<mutex> lock(mtx);
    for(int i = 0 ; i < 1000000 ; i++){
        a++;
    }
}

int main(){

    thread t1(function1);
    thread t2(function2);

    t1.join();
    t2.join();

    cout<<a<<endl;

    return 0;
}
