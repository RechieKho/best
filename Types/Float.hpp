#ifndef FLOAT_H
#define FLOAT_H

#define FLT(n) Float(n)

#include "BstObj.hpp"

class Float: public BstObj{
    float num;
public:
    Float() = default;
    Float(float number);

    BstObj *Get(const BstObj &key) const override;
    BstObj *Copy() const override;
    std::string ToString() const override;
    std::string GetType() const override;
    bool operator==(const BstObj &value) const override;

    float ToNative() const;
};

#endif