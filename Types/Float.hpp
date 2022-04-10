#ifndef FLOAT_H
#define FLOAT_H

#include "Getable.hpp"

class Float: public Getable{
    float m_data;
public:
    Float() = default;
    Float(float number);

    Getable *Get(const Getable &key) const override;
    Getable *Copy() const override;
    std::string ToString() const override;
    std::string GetType() const override;
    bool operator==(const Getable &value) const override;

    float ToNative() const;
};

#endif