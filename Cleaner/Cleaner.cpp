#include <algorithm>
#include "Cleaner.hpp"
#include <iostream>

void *Cleanable::operator new(size_t size){
    void *p = malloc(size);
    Cleaner::record((Cleanable *)p);
    return p;
}

std::vector<Cleanable *> Cleaner::items = std::vector<Cleanable *>();

void Cleaner::record(Cleanable *item){
    for(int i = 0; i < items.size(); i++) if(items[i] == item) return;
    items.push_back(item);
}

void Cleaner::flush(){
    for(int i = 0; i<items.size(); i++){
        Cleanable *item = items[i];
        if(!item->ref_count) {
            items.erase(items.begin() + i);
            delete item;
        }
    }
}