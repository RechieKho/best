#include "String.hpp"
#include "Integer.hpp"
#include "Cleaner.hpp"

String::String(std::string text)
    : m_data(text)
{}

const Getable *String::Get(const Getable *key) const{
    if(!key->ToString().compare("length")) return new Integer((int)m_data.length());
    else return nullptr;
}

std::string String::ToString() const{
    return m_data;
}

std::string String::GetType() const{
    return "String";
}

bool String::IsEqual(const Getable *value) const{
    return !value->GetType().compare("String") && !m_data.compare(value->ToString());
}

