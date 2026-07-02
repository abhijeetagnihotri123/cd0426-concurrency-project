#include <iostream>
#include <thread>
#include <chrono>
#include <random>

using namespace std;



void check_for_time_duration(){

    
    random_device rd; 
    mt19937 gen(rd()); 
    uniform_int_distribution<> distr(4, 6); 
    int current_threshold = distr(gen);

    auto last_update = std::chrono::system_clock::now();
    while(true){
        this_thread::sleep_for(chrono::milliseconds(1));
        int time_elapsed = chrono::duration_cast<chrono::seconds>(chrono::system_clock::now() - last_update).count();
        cout<<time_elapsed<<" "<<current_threshold<<" ";
        if(time_elapsed >= current_threshold){
            cout<<"Here\n";
        }
        else{
            cout<<"Not Here\n";
        }
        current_threshold = distr(gen);
    }

}

int main(){
    auto last_update = std::chrono::system_clock::now();
    
    check_for_time_duration();

    return 0;
}