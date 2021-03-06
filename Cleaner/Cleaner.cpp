#include <algorithm>
#include "Cleaner.hpp"
#include <iostream>

void *Cleanable::operator new(size_t size){
    // static int count = 0;
    // count++;
    // std::cout << "Cleanable Start, count: " << count << std::endl;
    
    void *p = malloc(size);
    Cleaner::record((Cleanable *)p);
    return p;
}

void Cleanable::operator delete(void *p){
    // static int count = 0;
    // count ++;
    // std::cout << "Cleanable End, count: " << count << std::endl;

    free(p);
    Cleaner::unrecord((Cleanable *)p);
}

std::vector<Cleanable *> Cleaner::items = std::vector<Cleanable *>();

void Cleaner::record(Cleanable *item){
    for(int i = 0; i < items.size(); i++) if(items[i] == item) return;
    items.push_back(item);
}

void Cleaner::unrecord(Cleanable *item){
    for(int i = 0; i < items.size(); i++) if(items[i] == item) items.erase(items.begin() + i);
}

void Cleaner::flush(){
    for(int i = 0; i<items.size(); i++){
        Cleanable *item = items[i];
        if(!item->ref_count) {
            delete item;
        }
    }
}
