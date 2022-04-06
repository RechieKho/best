#include <algorithm>
#include "Cleaner.hpp"
#include <iostream>

Cleanable::Cleanable(){
    Cleaner::Register(this);
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