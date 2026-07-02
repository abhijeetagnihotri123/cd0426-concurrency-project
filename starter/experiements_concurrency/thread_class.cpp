#include <iostream>
#include <thread>
#include <vector>

using namespace std;

class ThreadClass{

private:
    vector<thread>threads;

public:
    ThreadClass(){}
    ~ThreadClass(){
        for(thread &t : threads){
            t.join();
        }
    }

    void simulate(){
        threads.emplace_back(thread(&ThreadClass::run_function , this));
    }
    void run_function(){
        cout<<"Thread function running\n";
    }
};

int main(){

    ThreadClass t1;
    t1.simulate();
    return 0;
}