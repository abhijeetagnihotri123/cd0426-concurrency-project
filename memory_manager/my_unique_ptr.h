#ifndef MY_UNIQUE_PTR_H
#define MY_UNIQUE_PTR_H

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

#endif