#ifndef INTEGER_H
#define INTEGER_H

#include "Getable.hpp"

class Integer: public Getable{
    int m_data;
public:
    Integer();
    Integer(int number);
    Getable *Get(const Getable &key) const override;
    Getable *Copy() const override;
    std::string ToString() const override;
    std::string GetType() const override;
    bool operator==(const Getable &value) const override;

    int ToNative() const;
};

#endif