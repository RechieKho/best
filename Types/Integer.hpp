#ifndef INTEGER_H
#define INTEGER_H

#include "Getable.hpp"

class Integer: public Getable{
    int m_data;
public:
    Integer(int number);
    Getable *Get(Getable *key = NULL) override;
    std::string ToString() override;
};

#endif