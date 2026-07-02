#include <iostream>
#include <thread>

using namespace std;

void function1(){
    cout<<"Thread without parameters\n";
}

void function2(int t){
    cout<<"Thread with copied value : "<<t<<endl;
}

void function3(int &a){
    cout<<"Thread with lvalue : "<<a<<endl;
    a += 132;
}

void function4(int &&a){
    cout<<"Thread with rvalue : "<<a<<endl;
}

int main(){

    int a = 132;
    thread t1(function1);
    thread t2(function2 , 1);
    thread t3(function3 , ref(a));
    thread t4(function4 , move(a));

    t1.join();
    t2.join();
    t3.join();
    t4.join();

    int b = 891;

    thread t5([&b](){
        b += 198;
        cout<<"Lambda function as a parameter\n";
    });

    t5.join();

    cout<<b<<endl;
    return 0;
}