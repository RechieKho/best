#ifndef STRING_H
#define STRING_H

#define STR(t) String(t)

#include "BstObj.hpp"

class String: public BstObj
{
    std::string str;
public:
    String() = default;
    String(const std::string &text);
    String(const char *text);

    BstObj *get() const override;
    BstObj *get(const BstObj &key) const override;
    bool operator==(const BstObj &value) const override;
    
    bool operator==(const String &value);
    String operator+(const String &value);
    String &operator+=(const String &value);
    std::string to_native() const;
};

#endif