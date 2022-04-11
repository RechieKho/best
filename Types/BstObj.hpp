#ifndef GETABLE_H
#define GETABLE_H

#include <string>
#include <iostream>

#include "Cleaner.hpp"

// copies are all located at heap

class BstObj: public Cleanable{
public:
    virtual BstObj *get() const = 0; // returns type
    virtual BstObj *get(const BstObj &key) const = 0; // returns the value (copy) based on key
    virtual bool operator==(const BstObj &value) const = 0;
    virtual bool operator!=(const BstObj &value) const; // basically !(*this == value)
};

std::ostream& operator<<(std::ostream &stream, BstObj &entity);
std::ostream& operator<<(std::ostream &stream, const BstObj &entity);

#endif