#include <algorithm>
#include "Cleaner.hpp"
#include <iostream>

void *Cleanable::operator new(size_t size){
    void *p = malloc(size);
    Cleaner::Register((Cleanable *)p);
    return p;
}

std::vector<Cleanable *> Cleaner::items = std::vector<Cleanable *>();

void Cleaner::Register(Cleanable *item){
    for(int i = 0; i < items.size(); i++) if(items[i] == item) return;
    items.push_back(item);
}

void Cleaner::Flush(){
    for(int i = 0; i<items.size(); i++){
        Cleanable *item = items[i];
        if(!item->ref_count) {
            items.erase(items.begin() + i);
            delete item;
        }
    }
}