#include "Text.hpp"
#include "Integer.hpp"

Text::Text(std::string text)
    : m_data(text){}

Getable *Text::Get(Getable *key){
    if(!key->ToString().compare("length")) return new Integer((int)m_data.length());
    else return this;
}

std::string Text::ToString(){
    return m_data;
}
