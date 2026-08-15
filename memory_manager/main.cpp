#include "fixed_memory.h"
#include "variable_memory.h"
#include <cassert>

using namespace std;

class Driver{

private:
    Memory *m;

public:
    Driver(Memory *);
    void *allocate_memory(size_t);
    void free_memory(void *);
    ~Driver();
};

Driver::Driver(Memory *m){
    this->m = m;
}

void *Driver::allocate_memory(size_t size){
    return this->m->allocate_memory(size);
}

void Driver::free_memory(void *ptr){
    this->m->free_memory(ptr);
}

Driver::~Driver(){
    this->m->~Memory();
}

struct Data{
    int x,y;
};

void function1(){
    cout<<"Sample function1"<<endl;
}

void function2(){
    cout<<"Sample Functino2"<<endl;
}
void function3(){
    cout<<"Sample Functino3"<<endl;
}

struct BiggerStruct{
    void (*fptr1)(void);
    void (*fptr2)(void);
    void (*fptr3)(void);
    int x;
    int y;
};

int main(){

    
    Driver d(new VariableMemory());
    int *ptr = (int*)d.allocate_memory(sizeof(int));

    if(ptr != nullptr){
        *ptr = 132;
        cout<<ptr<<" "<<*ptr<<endl;
    }

    BiggerStruct *data_ptr = (BiggerStruct*)d.allocate_memory(sizeof(BiggerStruct));
    if(data_ptr != nullptr){
        data_ptr->x = 132;
        data_ptr->y = 264;
        data_ptr->fptr1 = function1;
        data_ptr->fptr2 = function2;
        data_ptr->fptr3 = function3;

        cout<<data_ptr->x<<" "<<data_ptr->y<<endl;
        data_ptr->fptr1();
        data_ptr->fptr2();
        data_ptr->fptr3();

    }
    d.free_memory((void*)ptr);
    d.free_memory((void*)data_ptr);



    

    return 0;
}