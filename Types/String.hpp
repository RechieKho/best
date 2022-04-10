#ifndef STRING_H
#define STRING_H

#define STR(t) String(t)

#include "BstObj.hpp"

class String: public BstObj
{
    std::string str;
public:
    String() = default;
    String(std::string text);

    BstObj *Get(const BstObj &key) const override;
    BstObj *Copy() const override;
    std::string ToString() const override;
    std::string GetType() const override;
    bool operator==(const BstObj &value) const override;
    
    std::string ToNative() const;
};

#endif