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

    BstObj *get(const BstObj &key) const override;
    BstObj *copy() const override;
    std::string to_string() const override;
    std::string get_type() const override;
    bool operator==(const BstObj &value) const override;
    
    std::string to_native() const;
};

#endif