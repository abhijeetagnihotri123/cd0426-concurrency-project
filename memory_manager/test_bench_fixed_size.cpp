#include "fixed_memory.h"
#include <cassert>

using namespace std;

void test1(Memory *m){

    int *ptr = (int *)m->allocate_memory(sizeof(int));
    assert(ptr != nullptr);
    *ptr = 132;
    std::cout<<ptr<<" "<<*ptr<<std::endl;
    m->free_memory((void *)ptr);
    ptr = nullptr;
    cout<<"Test1 passed"<<endl;
}

void test2(Memory *m){

    struct Data{
        int x,y;
    };

    Data *d = (Data*)m->allocate_memory(sizeof(Data));
    assert(d != nullptr);
    d->x = 132;
    d->y = 264;
    std::cout<<d<<" "<<d->x<<" "<<d->y<<std::endl;
    m->free_memory((void *)d);
    d = nullptr;
    
    cout<<"Test2 passed"<<endl;
}

void test3(Memory *m){
    assert(!(m->free_memory((void *)0x1001)));
    
    cout<<"Test3 passed"<<endl;
}

void test4(Memory *m){
    char *fake_ptr = (char *)m->allocate_memory(sizeof(char));
    bool b1 = !(m->free_memory((void *)(fake_ptr + 3)));
    bool b2 = m->free_memory((void *)fake_ptr);
    assert(b1 && b2);
    cout<<"Test4 passed"<<endl;
}

int main(){

    Memory *m = new FixedMemory();
    
    test1(m);
    test2(m);
    test3(m);
    test4(m);
    
    return 0;
}
