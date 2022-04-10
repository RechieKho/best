#ifndef GETABLE_H
#define GETABLE_H

#include <string>
#include <iostream>

#include "Cleaner.hpp"

class Getable: public Cleanable{
public:
    virtual const Getable *Get(const Getable *key = NULL) const = 0;
    virtual std::string ToString() const = 0;
    virtual std::string GetType() const = 0;
    virtual bool IsEqual(const Getable *value) const = 0;
};

#endif