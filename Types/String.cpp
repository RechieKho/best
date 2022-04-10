#include "String.hpp"
#include "Integer.hpp"
#include "Cleaner.hpp"

String::String(std::string text)
    : str(text)
{}

BstObj *String::Get(const BstObj &key) const{
    if(!key.ToString().compare("length")) return new Integer((int)str.length());
    else return nullptr;
}

BstObj *String::Copy() const{
    return new String(str);
}

std::string String::ToString() const{
    return str;
}

std::string String::GetType() const{
    return "String";
}

bool String::operator==(const BstObj &value) const{
    return !value.GetType().compare("String") && !str.compare(value.ToString());
}

std::string String::ToNative() const {
    return str;
}