#ifndef FLOAT_H
#define FLOAT_H

#define FLT(n) Float(n)

#include "BstObj.hpp"

class Float: public BstObj{
    float num;
public:
    Float() = default;
    Float(const float &number);

    BstObj *get() const override;
    BstObj *get(const BstObj &key) const override;
    bool operator==(const BstObj &value) const override;

    float to_native() const;
};

#endif