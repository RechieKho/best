#include "String.hpp"
#include "Integer.hpp"
#include "Cleaner.hpp"

String::String(std::string text)
    : str(text)
{}

BstObj *String::get(const BstObj &key) const{
    if(!key.to_string().compare("length")) return new Integer((int)str.length());
    else return nullptr;
}

BstObj *String::copy() const{
    return new String(str);
}

std::string String::to_string() const{
    return str;
}

std::string String::get_type() const{
    return "String";
}

bool String::operator==(const BstObj &value) const{
    return !value.get_type().compare("String") && !str.compare(value.to_string());
}

std::string String::to_native() const {
    return str;
}