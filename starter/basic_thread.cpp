#include <iostream>
#include <thread>
using namespace std;

void someLongFunction(int id){
    for(int i = 0 ; i < 65536 * 2 ; i++){

    }
    cout<<"Long Thread running in detached mode with ID: "<<id<<endl;
}

void somefunction(int id){
    cout<<"In thread function "<<id<<endl;
}

int main(){

    thread t1(somefunction , 1);
    thread t2(somefunction , 2);
    thread t3(someLongFunction , 3);
    t1.join();
    t2.join();
    t3.detach();
    return 0;
}