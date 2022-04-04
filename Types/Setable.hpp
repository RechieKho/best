#ifndef SETABLE_H
#define SETABLE_H

#include "Getable.hpp"

class Setable : public Getable{
public:
    virtual void Set(Getable *key, Getable *value) = 0;
};

#endif