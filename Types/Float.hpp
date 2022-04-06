#ifndef FLOAT_H
#define FLOAT_H

#include "Getable.hpp"

class Float: public Getable{
    float m_data;
public:
    Float() = default;
    Float(float number);
    Getable *Get(Getable *key = NULL) const override;
    std::string ToString() const override;
    std::string GetType() const override;
    float GetNumber();
    bool IsEqual(Getable *value) const override;
};

#endif