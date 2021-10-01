#ifndef MIN_HEAP
#define MIN_HEAP

#include <iostream>
#include <netinet/in.h>
#include <time.h>

using std::exception;

#define BUFFER_SIZE 64

class heap_timer;

struct client_data{
    sockaddr_in address;
    int sockfd;
    char buf[BUFFER_SIZE];
    heap_timer* timer;
};

class heap_timer{
public:
    heap_timer(int delay){
        expire = time(NULL) + delay;
    }

public:
    time_t expire;
    void (*cb_func) (client_data*);
    client_data* user_data;
};

class time_heap{
public:
    time_heap(int cap) throw (std::exception) : capacity(cap),cur_size(0){
        array = new heap_timer* [capacity];
        if(!array){
            throw std::exception();
        }
        for(int i=0;i<capacity;++i){
            array[i] = NULL;
        }
    }
    time_heap(heap_timer** init_array,int size,int capacity) throw (std::exception):cur_size(size),capacity(capacity){
        if(capacity < size){
            throw std::exception;
        }
        array = heap_timer* [capacity];
        if(!array){
            throw std::exception;
        }
        for(int i=0;i<capacity;++i){
            array[i] = NULL;
        }
        if(size != 0){
            for(int i=0;i<size;++i){
                array[i] = init_array[i];
            }
            for(int i=(cur_size-1)/2;i>=0;--i){
                percolate_down(i);
            }
        }
    }

    ~time_heap(){
        for(int i=0;i<cur_size;++i){
            delete array[i];
        }
        delete[] array;
    }
public:
    void add_timer(heap_timer* timer) throw (std::exception){
        if(!timer){
            return;
        }
        if(cur_size >= capacity){
            resize();
        }
    }
}