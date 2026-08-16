#include "fixed_memory.h"
#include <cassert>

using namespace std;

template<typename T>
class my_unique_ptr{

private:
    T *raw_ptr = nullptr;
    Memory *memory_allocator = nullptr;

public:
    my_unique_ptr(Memory *m){
        this->memory_allocator = m;
        this->raw_ptr = static_cast<T*>(this->memory_allocator->allocate_memory(sizeof(T)));
    }
    T *my_make_unique(){
        return this->raw_ptr;
    }
    ~my_unique_ptr(){
        if(this->raw_ptr && this->memory_allocator){
            this->raw_ptr->~T();
            this->memory_allocator->free_memory((void *)this->raw_ptr);
        }
    }
};

void test1(Memory *m){

    my_unique_ptr<int>block(m);

    int *ptr = block.my_make_unique();
    assert(ptr != nullptr);
    *ptr = 132;
    std::cout<<ptr<<" "<<*ptr<<std::endl;
    m->free_memory((void *)ptr);
    ptr = nullptr;
    cout<<"Test1 passed"<<endl;
}

#if 0

void test2(Memory *m){

    struct Data{
        int x,y;
    };
    
    my_unique_ptr<Data*>block(m);

    Data *d = (Data*)block.my_make_unique();
    assert(d != nullptr);
    d->x = 132;
    d->y = 264;
    std::cout<<d<<" "<<d->x<<" "<<d->y<<std::endl;
    m->free_memory((void *)d);
    d = nullptr;
    
    cout<<"Test2 passed"<<endl;
}

#endif

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
    //test2(m);
    test3(m);
    test4(m);
    
    return 0;
}
