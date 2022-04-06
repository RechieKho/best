#ifndef CLEANER_H
#define CLEANER_H

#include <vector>

class Cleanable{
public:
    Cleanable();
    virtual ~Cleanable() = default;
    int ref_count;
};

class Cleaner{
    static std::vector<Cleanable *> items;
public:
    
    static void Register(Cleanable *item);
    static void Flush();
    
};

#endif