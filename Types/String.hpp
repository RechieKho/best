#ifndef STRING_H
#define STRING_H

#include "Getable.hpp"

class String: public Getable
{
    std::string m_data;
public:
    String() = default;
    String(std::string text);

    const Getable *Get(const Getable *key = NULL) const override;
    std::string ToString() const override;
    std::string GetType() const override;
    bool IsEqual(const Getable *value) const override;
};

#endif