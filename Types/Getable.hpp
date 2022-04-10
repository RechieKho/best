#ifndef GETABLE_H
#define GETABLE_H

#include <string>
#include <iostream>

#include "Cleaner.hpp"

// copies are all located at heap

class Getable: public Cleanable{
public:
    virtual Getable *Get(const Getable &key) const = 0; // returns the value (copy) based on key
    virtual Getable *Copy() const = 0; // return a copy of itself
    virtual std::string ToString() const = 0;
    virtual std::string GetType() const = 0;
    virtual bool operator==(const Getable &value) const = 0;
};

#endif