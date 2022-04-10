#ifndef GETABLE_H
#define GETABLE_H

#include <string>

#include "Cleaner.hpp"

// copies are all located at heap

class BstObj: public Cleanable{
public:
    virtual BstObj *get(const BstObj &key) const = 0; // returns the value (copy) based on key
    virtual BstObj *copy() const = 0; // return a copy of itself
    virtual std::string to_string() const = 0;
    virtual std::string get_type() const = 0;
    virtual bool operator==(const BstObj &value) const = 0;
};

#endif