#ifndef STRING_H
#define STRING_H

#include "Getable.hpp"

class String: public Getable
{
    std::string m_data;
public:
    String() = default;
    String(std::string text);

    Getable *Get(const Getable &key) const override;
    Getable *Copy() const override;
    std::string ToString() const override;
    std::string GetType() const override;
    bool operator==(const Getable &value) const override;
    
    std::string ToNative() const;
};

#endif