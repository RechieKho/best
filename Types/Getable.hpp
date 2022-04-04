#ifndef GETABLE_H
#define GETABLE_H

#include <string>

class Getable {
public:
    virtual Getable *Get(Getable *key = NULL) = 0;
    virtual std::string ToString() = 0;
};

#endif