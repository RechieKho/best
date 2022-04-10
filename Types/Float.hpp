#ifndef FLOAT_H
#define FLOAT_H

#define FLT(n) Float(n)

#include "BstObj.hpp"

class Float: public BstObj{
    float num;
public:
    Float() = default;
    Float(float number);

    BstObj *get(const BstObj &key) const override;
    BstObj *copy() const override;
    std::string to_string() const override;
    std::string get_type() const override;
    bool operator==(const BstObj &value) const override;

    float to_native() const;
};

#endif