#ifndef GETABLE_H
#define GETABLE_H

#include <string>

#include "Cleaner.hpp"

// copies are all located at heap

class BstObj: public Cleanable{
public:
    virtual BstObj *Get(const BstObj &key) const = 0; // returns the value (copy) based on key
    virtual BstObj *Copy() const = 0; // return a copy of itself
    virtual std::string ToString() const = 0;
    virtual std::string GetType() const = 0;
    virtual bool operator==(const BstObj &value) const = 0;
};

#endif