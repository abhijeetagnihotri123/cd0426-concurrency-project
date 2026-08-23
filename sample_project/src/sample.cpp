#include "../include/sample.hpp"

sample_class::sample_class(int a , int b){
    this->a = a;
    this->b = b;
    std::cout<<"Constructor called\n";
}

sample_class::~sample_class(void){
    std::cout<<"Destructor called\n";
}

void sample_class::display(){
    std::cout<<"{ a : "<<this->a<<" , b : "<<this->b<<")\n";
}

int main(){

    sample_class s(1 , 2);
    s.display();

    return 0;
}