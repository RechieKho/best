#ifndef INTEGER_H
#define INTEGER_H

#include "Getable.hpp"

class Integer: public Getable{
    int m_data;
public:
    Integer();
    Integer(int number);
    const Getable *Get(const Getable *key = NULL) const override;
    std::string ToString() const override;
    std::string GetType() const override;
    bool IsEqual(const Getable *value) const override;
    int GetNumber();
};

#endif