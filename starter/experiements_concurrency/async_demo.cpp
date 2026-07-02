#include <iostream>
#include <thread>
#include <future>
#include <vector>
#include <algorithm>
#include <chrono>
#include <numeric>

using namespace std;

int getSum(int n){
    int sum = 0;
    for(int i = 1 ; i <= n ; i++){
        this_thread::sleep_for(chrono::milliseconds(5));
        sum += i;
    }
    return sum;
}

int main(){

    // future<int>f = async(launch::async , getSum , 100);
    // cout<<f.get()<<endl;

    vector<int>numbers(100);
    future<void>iotaFuture = async(launch::async , [&numbers](){
        iota(numbers.begin() , numbers.end() , 10);
    });

    iotaFuture.get();

    for(int i = 0 ; i < 100 ; i++){
        cout<<numbers[i]<<endl;
    }

    return 0;
}