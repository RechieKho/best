#ifndef STRING_H
#define STRING_H

#include "Getable.hpp"

class String: public Getable
{
    std::string m_data;
public:
    String() = default;
    String(std::string text);
    Getable *Get(Getable *key = NULL) const override;
    std::string ToString() const override;
    std::string GetType() const override;
    bool IsEqual(Getable *value) const override;
};

#endif