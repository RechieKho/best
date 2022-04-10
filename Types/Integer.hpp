#ifndef INTEGER_H
#define INTEGER_H

#define INT(n) Integer(n)

#include "BstObj.hpp"

class Integer: public BstObj{
    int num;
public:
    Integer();
    Integer(int number);
    BstObj *Get(const BstObj &key) const override;
    BstObj *Copy() const override;
    std::string ToString() const override;
    std::string GetType() const override;
    bool operator==(const BstObj &value) const override;

    int ToNative() const;
};

#endif