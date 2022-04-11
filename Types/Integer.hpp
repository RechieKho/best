#ifndef INTEGER_H
#define INTEGER_H

#define INT(n) Integer(n)

#include "BstObj.hpp"

class Integer: public BstObj{
    int num;
public:
    Integer();
    Integer(int number);

    BstObj *get() const override;
    BstObj *get(const BstObj &key) const override;
    bool operator==(const BstObj &value) const override;

    int to_native() const;
};

#endif