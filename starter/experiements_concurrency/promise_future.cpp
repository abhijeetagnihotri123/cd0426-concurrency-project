#include <iostream>
#include <thread>
#include <mutex>

#include <future>

using namespace std;

void generate_data(promise<int>&result){
    try{
        result.set_value(132);
    }catch(...){
        result.set_exception(current_exception());
    }
}

int main(){

    promise<int>result;
    future<int>future_value = result.get_future();

    thread t1(generate_data , ref(result));

    try{
        int value = future_value.get();
        cout<<value<<endl;
    }catch(exception &e){
        cout<<e.what()<<endl;
    }

    t1.join();
    return 0;
}