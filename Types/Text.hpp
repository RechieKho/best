#ifndef TEXT_H
#define TEXT_H

#include "Getable.hpp"

class Text: public Getable
{
    std::string m_data;
public:
    Text(std::string text);
    Getable *Get(Getable *key = NULL) override;
    std::string ToString() override;
};

#endif